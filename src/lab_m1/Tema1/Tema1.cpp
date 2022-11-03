#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"


using namespace std;
using namespace m1;
/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);

    //length_over = 20000;
    //width_over = 20000;

    over = 0;
    direction = 1;

    tx_grass = 0;
    ty_grass = 0;

    tx_bullet1 = 0;
    ty_bullet1 = 0;
    tx_bullet2 = 0;
    ty_bullet2 = 0;
    tx_bullet3 = 0;
    ty_bullet3 = 0;

    scale_bullet1 = 1;
    scale_bullet2 = 1;
    scale_bullet3 = 1;

    tx_circle1 = 0;
    ty_circle1 = 0;
    tx_circle2 = 0;
    ty_circle2 = 0;
    tx_circle3 = 0;
    ty_circle3 = 0;

    scale_circle1 = 20;
    scale_circle2 = 20;
    scale_circle3 = 20;

    tx_score = 0;
    ty_score = 0;


    length_grass = 200;
    width_grass = 10000;

    length_bullet = 30;
    width_bullet = 10;

    length_score_frame = 50;
    width_score_frame = 250;

    length_score = 50;
    width_score = 0;

    length_body = 100;
    tx_body = 0;
    ty_body = 0;
    //tx_wing1 = tx_body + 50;
    //ty_wing1 = tx_body - 65;
    //tx_wing2 = ty_body + 10;
    //ty_wing2 = ty_body - 140;
    tx_wing1 = 0;
    ty_wing1 = 0;
    tx_wing2 = 0;
    ty_wing2 = 0;
    angularStep1 = 7;
    angularStep2 = 0;
    angularStep3 = 4.4;
    angularStep4 = 0;
    directionAngular1 = 1;
    directionAngular2 = 1;
    cx = corner.x + length_body / 2;
    cy = corner.y + length_body / 2;

    life = 3;
    bullet_nr = 3;
    hit = 0;
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    time = 0;

    // Grass
    Mesh* rectangle = object2D::CreateRectangle("rectangle", corner, length_grass, width_grass, glm::vec3(0, 1, 0), true);
    AddMeshToList(rectangle);

    // Lives
    Mesh* circle1 = object2D::CreateCircle("circle1", corner, glm::vec3(1, 0, 0), true);
    AddMeshToList(circle1);

    Mesh* circle2 = object2D::CreateCircle("circle2", corner, glm::vec3(1, 0, 0), true);
    AddMeshToList(circle2);

    Mesh* circle3 = object2D::CreateCircle("circle3", corner, glm::vec3(1, 0, 0), true);
    AddMeshToList(circle3);

    // Bullets
    Mesh* rectangle1 = object2D::CreateRectangle("rectangle1", corner, length_bullet, width_bullet, glm::vec3(0, 1, 0));
    AddMeshToList(rectangle1);

    Mesh* rectangle2 = object2D::CreateRectangle("rectangle2", corner, length_bullet, width_bullet, glm::vec3(0, 1, 0));
    AddMeshToList(rectangle2);

    Mesh* rectangle3 = object2D::CreateRectangle("rectangle3", corner, length_bullet, width_bullet, glm::vec3(0, 1, 0));
    AddMeshToList(rectangle3);

    // Score
    Mesh* rectangle4 = object2D::CreateRectangle("rectangle4", corner, length_score_frame, width_score_frame, glm::vec3(0.255, 0.255, 0.255));
    AddMeshToList(rectangle4);

    Mesh* rectangle5 = object2D::CreateRectangle("rectangle5", corner, length_score, width_score, glm::vec3(0, 0, 1), true);
    AddMeshToList(rectangle5);

    // Duck

    // Body
    Mesh* triangle1 = object2D::CreateTriangle("triangle1", corner, length_body, glm::vec3(0.139, 0.069, 0.019), true);
    AddMeshToList(triangle1);
    //Wings
    Mesh* triangle2 = object2D::CreateTriangle("triangle2", corner, length_body, glm::vec3(0.139, 0.069, 0.019), true);
    AddMeshToList(triangle2);

    Mesh* triangle3 = object2D::CreateTriangle("triangle3", corner, length_body, glm::vec3(0.139, 0.069, 0.019), true);
    AddMeshToList(triangle3);

    
}



// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}
//
//
//void Tema1::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
//{
//    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);
//
//    glEnable(GL_SCISSOR_TEST);
//    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);
//
//    // Clears the color buffer (using the previously set color) and depth buffer
//    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glDisable(GL_SCISSOR_TEST);
//
//    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
//    GetSceneCamera()->Update();
//}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{

    // Draw grass
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    // Draw lives
    tx_circle1 = 1110;
    ty_circle1 = 665;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx_circle1, ty_circle1);
    modelMatrix *= transform2D::Scale(scale_circle1, scale_circle1);
    RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);

    tx_circle2 = tx_circle1 - 50;
    ty_circle2 = 665;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx_circle2, ty_circle2);
    modelMatrix *= transform2D::Scale(scale_circle2, scale_circle2);
    RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

    tx_circle3 = tx_circle2 - 50;
    ty_circle3 = 665;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx_circle3, ty_circle3);
    modelMatrix *= transform2D::Scale(scale_circle3, scale_circle3);
    RenderMesh2D(meshes["circle3"], shaders["VertexColor"], modelMatrix);

    // Draw bullets

    tx_bullet1 = tx_circle1 + 50;
    ty_bullet1 = ty_circle1 - 16;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx_bullet1, ty_bullet1);
    modelMatrix *= transform2D::Scale(scale_bullet1, scale_bullet1);
    RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);

    tx_bullet2 = tx_bullet1 + 30;
    ty_bullet2 = ty_bullet1;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx_bullet2, ty_bullet2);
    modelMatrix *= transform2D::Scale(scale_bullet2, scale_bullet2);
    RenderMesh2D(meshes["rectangle2"], shaders["VertexColor"], modelMatrix);

    tx_bullet3 = tx_bullet2 + 30;
    ty_bullet3 = ty_bullet2;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx_bullet3, ty_bullet3);
    modelMatrix *= transform2D::Scale(scale_bullet3, scale_bullet3);
    RenderMesh2D(meshes["rectangle3"], shaders["VertexColor"], modelMatrix);

    // Draw Score

    tx_score = tx_circle3 - 20;
    ty_score = ty_circle3 - 100;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx_score, ty_score);
    RenderMesh2D(meshes["rectangle4"], shaders["VertexColor"], modelMatrix);

    tx_score = tx_circle3 - 20;
    ty_score = ty_circle3 - 100;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx_score, ty_score);
    RenderMesh2D(meshes["rectangle5"], shaders["VertexColor"], modelMatrix);

    time += deltaTimeSeconds;

    // Draw Duck
    // Body
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 500);

    if (direction == 1) {
        tx_body += deltaTimeSeconds * 150;
        if (tx_body >= 600) {
            direction = 0;
        }
    }

    if (direction == 0) {
        tx_body -= deltaTimeSeconds * 150;
        if (tx_body < 100) {
            direction = 1;
        }
    }

    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Rotate(6);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Scale(1.3, 0.7);

    modelMatrix *= transform2D::Translate(tx_body, ty_body);
    RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);

    // Wings

    // wing 1
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 550);

    //if (direction == 1) {
    //    tx_body += deltaTimeSeconds * 150;
    //    if (tx_body >= 600) {
    //        direction = 0;
    //    }
    //}

    //if (direction == 0) {
    //    tx_body -= deltaTimeSeconds * 150;
    //    if (tx_body < 100) {
    //        direction = 1;
    //    }
    //}

    //tx_wing1 = tx_body + 50;
    //ty_wing1 = tx_body - 65;

    tx_wing1 = tx_body;
    ty_wing1 = tx_body;


    if (directionAngular1 == 1) {
        angularStep1 += deltaTimeSeconds * 0.5;
        if (angularStep1 > 7.3)
            directionAngular1 = 0;
    }
    if (directionAngular1 == 0) {
        angularStep1 -= deltaTimeSeconds * 0.5;
        if (angularStep1 < 7)
            directionAngular1 = 1;
    }

    //modelMatrix *= transform2D::Translate(tx_wing1, ty_wing1);
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Rotate(-angularStep1);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Scale(0.5, 0.6);

    modelMatrix *= transform2D::Translate(tx_wing1, ty_wing1);
    RenderMesh2D(meshes["triangle2"], shaders["VertexColor"], modelMatrix);

    // wing 2
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 550);

    //if (direction == 1) {
    //    tx_body += deltaTimeSeconds * 150;
    //    if (tx_body >= 600) {
    //        direction = 0;
    //    }
    //}

    //if (direction == 0) {
    //    tx_body -= deltaTimeSeconds * 150;
    //    if (tx_body < 100) {
    //        direction = 1;
    //    }
    //}

    tx_wing2 = ty_body + 10;
    ty_wing2 = ty_body - 140;

    if (directionAngular2 == 1) {
        angularStep3 += deltaTimeSeconds * 0.5;
        if (angularStep3 > 4.7)
            directionAngular2 = 0;
    }
    if (directionAngular2 == 0) {
        angularStep3 -= deltaTimeSeconds * 0.5;
        if (angularStep3 < 4.4)
            directionAngular2 = 1;
    }


    modelMatrix *= transform2D::Translate(tx_wing2, ty_wing2);
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Rotate(angularStep3);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Scale(0.6, 0.5);

    modelMatrix *= transform2D::Translate(tx_wing2, ty_wing2);
    RenderMesh2D(meshes["triangle3"], shaders["VertexColor"], modelMatrix);

}


void Tema1::FrameEnd()
{
}


void Tema1::DrawScene(glm::mat3 visMatrix)
{

 
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}


void Tema1::OnKeyPress(int key, int mods)
{


}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    //if (deltaX >= tx_body && deltaX <= (tx_body + length_body)) {
    //    if (deltaY >= ty_body && deltaY <= (ty_body + length_body)) {
    //        hit = 1;
    //    }
    //    else {
    //        hit = 0;
    //    }
    //}
    //else {
    //    hit = 0;
    //}

    if (deltaX >= tx_body && deltaX <= (tx_body + length_body)) {
        if (deltaY >= ty_body && deltaY <= (ty_body + length_body)) {
            hit = 1;
        }
        else {
            hit = 0;
        }
    }
    else {
        hit = 0;
    }

}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event

    if (button == GLFW_MOUSE_BUTTON_2 && hit == 0) {
        switch (bullet_nr) {
        case 3:
            scale_bullet3 = 0;
            bullet_nr--;
            break;
        case 2:
            scale_bullet2 = 0;
            bullet_nr--;
            break;
        case 1:
            scale_bullet1 = 0;
            bullet_nr--;
            break;
        default:
            life--;
            bullet_nr = 3;
            scale_bullet1 = 1;
            scale_bullet2 = 1;
            scale_bullet3 = 1;
            switch (life) {
            case 2:
                scale_circle1 = 0;
                break;
            case 1:
                scale_circle2 = 0;
                break;
            default:
                scale_circle3 = 0;
                GameOver();
                break;
            }
            break;
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_2 && hit == 1) {
        switch (bullet_nr) {
        case 3:
            width_score += 10;
            scale_bullet3 = 0;
            bullet_nr--;
            break;
        case 2:
            width_score += 10;
            scale_bullet2 = 0;
            bullet_nr--;
            break;
        case 1:
            width_score += 10;
            scale_bullet1 = 0;
            bullet_nr--;
            break;
        default:
            break;
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::GameOver() {

}
