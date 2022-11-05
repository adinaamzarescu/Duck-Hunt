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

    logicSpace.x = 2;       // logic x
    logicSpace.y = 4;       // logic y
    logicSpace.width = 4;   // logic width
    logicSpace.height = 4;  // logic height

    glm::vec3 corner = glm::vec3(0, 0, 0);

    time = 0;
    random = 0;

    length_border = 1115;
    width_border = 610;

    directionMove1 = 1;
    directionMove2 = 1;
    directionMove3 = 1;
    directionMove4 = 1;

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
    width_score = 1;
    scale_score = 0;

    // Duck
    // Body
    length_body = 100;
    //tx_body = rand() % (int)length_border;
    tx_body = 200;
    ty_body = 100;
    //angularMove = 3.14 / 4;
    angularMove = atan2(width_border - window->GetResolution()[1] / 2, length_border - 300 - window->GetResolution()[0] / 2);
    // Wings
    tx_wing1 = tx_body / 2 - 50;
    ty_wing1 = tx_body / 2 - 113;
    tx_wing2 = ty_body / 2;
    ty_wing2 = ty_body / 2 - 113;

    angularWing1 = 7;
    angularWing2 = 4.4;
    directionWing1 = 1;
    directionWing2 = 1;

    // Head
    tx_head = tx_body / 2 + 20;
    ty_head = tx_body / 2 - 100;

    // Beak
    tx_beak = tx_body / 2 + 30;
    ty_beak = tx_body / 2 - 120;

    cx = corner.x + length_body / 2;
    cy = corner.y + length_body / 2;

    life = 3;
    bullet_nr = 3;
    hit = 1;
    duck_hit = 0;
    visMatrix = glm::mat3(1);

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

    // Head
    Mesh* circle4 = object2D::CreateCircle("circle4", corner, glm::vec3(0.085, 0.107, 0.047), true);
    AddMeshToList(circle4);

    // Beak
    Mesh* triangle4 = object2D::CreateTriangle("triangle4", corner, length_body, glm::vec3(0.255, 0.255, 0.102), true);
    AddMeshToList(triangle4);
    
}


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
    time += deltaTimeSeconds;
    visMatrix = glm::mat3(1);
    //visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

    // Draw grass
    //modelMatrix = glm::mat3(1);
    //modelMatrix *= transform2D::Translate(0, 0);
    //RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

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
    modelMatrix *= transform2D::Scale(scale_score, width_score);
    RenderMesh2D(meshes["rectangle5"], shaders["VertexColor"], modelMatrix);


    // Duck

    // After 10 seconds the duck will fly away
    if (time > 10) {
        angularMove = 3.14 * 0.5;
        ty_body += 300 * deltaTimeSeconds;

        directionMove1 = -1;
        directionMove2 = 1;
        directionMove3 = 1;

        // After some time a "new" duck will appear
        // from a random spot
        if (ty_body > width_border + 300) {
            tx_body = rand() % (int)length_border;
            ty_body = rand() % 100;
            // The angle will be different each time
            if (random == 0) {
                random = 1;
                directionMove1 = 1;
            }
            else {
                directionMove3 = 0;
                random = 0;
            }
            time = 0;
        }
    }

    if (duck_hit == 1) {
        directionMove1 = -1;

        time = 0;
        angularMove = 3.14 * 0.5 * 3.14;
        ty_body -= 300 * deltaTimeSeconds;

        directionMove2 = 1;
        directionMove3 = 1;
        if (ty_body < -100) {
            tx_body = rand() % (int)length_border;
            ty_body = rand() % 100;
            // The angle will be different each time
            if (random == 0) {
                random = 1;
                directionMove1 = 1;
            }
            else {
                directionMove3 = 0;
                random = 0;
            }
            duck_hit = 0;
        }
        
    }

    if (directionMove1 == 1) {
        tx_body += 100 * deltaTimeSeconds;
        ty_body += 100 * deltaTimeSeconds;
        angularMove = atan2(width_border - window->GetResolution()[1] / 2, length_border - 300 - window->GetResolution()[0] / 2);
        if (ty_body > width_border && tx_body < length_border)
            directionMove1 = 0;
        if (ty_body <= 0 && tx_body <= length_border)
            directionMove4 = 1;
        if (tx_body >= length_border && ty_body >= 0) {
            directionMove3 = 0;
            directionMove1 = -1;
        }

    }
    if (directionMove1 == 0) {
        tx_body += 100 * deltaTimeSeconds;
        angularMove = (3 / 4) * 3.14;
        //angularMove = atan2(width_border - 300 - window->GetResolution()[1] / 2, length_border - window->GetResolution()[0] / 2);
        ty_body -= 100 * deltaTimeSeconds;
        if (tx_body >= length_border && ty_body >= 0) {
            directionMove2 = 0;
            directionMove1 = -1;
        }
        if (ty_body <= 0 && tx_body <= length_border) {
            directionMove1 = 1;
        }
    }
    if (directionMove2 == 0) {
        tx_body -= 100 * deltaTimeSeconds;
        angularMove = 3.14 * 5 / 4;
        //angularMove = atan2(-width_border - window->GetResolution()[1] / 2, -length_border + 100 - window->GetResolution()[0] / 2);
        ty_body -= 100 * deltaTimeSeconds;
        if (ty_body <= 0) {
            directionMove3 = 0;
            directionMove2 = 1;
        }
        if (tx_body <= 0) {
            directionMove2 = 1;
            directionMove1 = 0;
        }
    }
    if (directionMove3 == 0) {
        tx_body -= 100 * deltaTimeSeconds;
        //angularMove = (7 / 4) * 3.14;
        angularMove = atan2(width_border - 300 - window->GetResolution()[1] / 2, -length_border - window->GetResolution()[0] / 2);
        ty_body += 100 * deltaTimeSeconds;
        if (tx_body <= 0) {
            directionMove1 = 1;
            directionMove3 = 1;
        }
        if (ty_body >= width_border) {
            directionMove3 = 1;
            directionMove2 = 0;
        }
    }


    modelMatrixBody = transform2D::Translate(tx_body + length_body / 2, ty_body + length_body / 2);
    modelMatrixBody *= transform2D::Rotate(angularMove);
    modelMatrixBody *= transform2D::Translate(-length_body / 2, -length_body / 2);

    // Wing1

    modelMatrixWing1 = modelMatrixBody * transform2D::Translate(tx_wing1, ty_wing1);
    if (directionWing1 == 1) {
        angularWing1 += deltaTimeSeconds * 0.5;
        if (angularWing1 > 7.3)
            directionWing1 = 0;
    }
    if (directionWing1 == 0) {
        angularWing1 -= deltaTimeSeconds * 0.5;
        if (angularWing1 < 7)
            directionWing1 = 1;
    }

    modelMatrixWing1 *= transform2D::Translate(cx, cy);
    modelMatrixWing1 *= transform2D::Rotate(-angularWing1);
    modelMatrixWing1 *= transform2D::Translate(-cx, -cy);
    modelMatrixWing1 *= transform2D::Scale(0.5, 0.6);

    RenderMesh2D(meshes["triangle2"], shaders["VertexColor"], modelMatrixWing1);

    // Wing2

    modelMatrixWing2 = modelMatrixBody * transform2D::Translate(tx_wing2, ty_wing2);
    if (directionWing2 == 1) {
        angularWing2 += deltaTimeSeconds * 0.5;
        if (angularWing2 > 4.7)
            directionWing2 = 0;
    }
    if (directionWing2 == 0) {
        angularWing2 -= deltaTimeSeconds * 0.5;
        if (angularWing2 < 4.4)
            directionWing2 = 1;
    }


    modelMatrixWing2 *= transform2D::Translate(cx, cy);
    modelMatrixWing2 *= transform2D::Rotate(angularWing2);
    modelMatrixWing2 *= transform2D::Translate(-cx, -cy);
    modelMatrixWing2 *= transform2D::Scale(0.6, 0.5);

    modelMatrixWing2 *= transform2D::Translate(tx_wing2, ty_wing2);
    RenderMesh2D(meshes["triangle3"], shaders["VertexColor"], modelMatrixWing2);

    // Head

    modelMatrixHead = modelMatrixBody * transform2D::Translate(tx_head, ty_head);
    modelMatrixHead *= transform2D::Scale(25, 25);
    RenderMesh2D(meshes["circle4"], shaders["VertexColor"], modelMatrixHead);

    // Beak

    modelMatrixBeak = modelMatrixBody * transform2D::Translate(tx_beak, ty_beak);
    modelMatrixBeak *= transform2D::Scale(0.3, 0.2);
    RenderMesh2D(meshes["triangle4"], shaders["VertexColor"], modelMatrixBeak);

    // Body
    modelMatrixBody *= transform2D::Scale(1.3, 0.7);
    RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrixBody);

}


void Tema1::FrameEnd()
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
    if (mouseX + deltaX + 100 >= tx_body && mouseX + deltaX + 100 <= (tx_body + length_body + 100)) {
        if (mouseY + deltaY + 300 >= ty_body && mouseY + deltaY + 300 <= (ty_body + length_body + 100)) {
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
            scale_score += 10;
            scale_bullet3 = 0;
            bullet_nr--;
            duck_hit = 1;
            break;
        case 2:
            scale_score += 10;
            scale_bullet2 = 0;
            bullet_nr--;
            duck_hit = 1;
            break;
        case 1:
            scale_score += 10;
            scale_bullet1 = 0;
            bullet_nr--;
            duck_hit = 1;
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
