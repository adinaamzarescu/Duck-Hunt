#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    // Initialize tx and ty (the translation steps)
    tx1 = 0;
    ty1 = 0;
    tx2 = 0;
    ty2 = 0;
    tx3 = 0;
    ty3 = 0;
    tx4 = 0;
    ty4 = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 0.1;
    scaleY = 0.1;

    // Initialize angularStep
    angularStep2 = 0;
    angularStep3 = 0;
    angularStep4 = 0;

    //boolean variabiles
    scaleBoolean = 1;
    direction = 1;
    directionX = 1;
    direction1 = 1;
    direction2 = 1;


    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0.107, 0.142, 0.035), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0.255, 0.020, 0.147), true);
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(square3);

    Mesh* square4 = object2D::CreateSquare("square4", corner, squareSide, glm::vec3(0, 1, 1), true);
    AddMeshToList(square4);
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{
    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(150, 250);
    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented.
    // Remember, the last matrix in the chain will take effect first!


    // Se muta de la stanga la dreapta
    if (directionX == 1) {
        tx1 += deltaTimeSeconds * 150;
        if (tx1 >= 600) {
            directionX = 0;
        }
    }

    if (directionX == 0) {
        tx1 -= deltaTimeSeconds * 150;
        if (tx1 < 100) {
            directionX = 1;
        }
    }


    modelMatrix *= transform2D::Translate(tx1, ty1);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    // Se muta la stanga, se mareste si se micsoreaza
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 350);

    if (scaleBoolean == 1) {
        scaleX += deltaTimeSeconds * 0.3;
        scaleY += deltaTimeSeconds * 0.3;
        if (scaleX >= 1 && scaleY >= 1) {
            scaleBoolean = 0;
        }
    }

    if (scaleBoolean == 0) {
        scaleX -= deltaTimeSeconds * 0.3;
        scaleY -= deltaTimeSeconds * 0.3;
        if (scaleX < 0.1 && scaleY < 0.1) {
            scaleBoolean = 1;
        }
    }

    tx2 += deltaTimeSeconds * 150;
    if (tx2 >= 600) {
        tx2 = 600;
    }
    modelMatrix *= transform2D::Translate(tx2, ty2);

    modelMatrix *= transform2D::Translate(cx, cy);
    if (tx2 >= 600) {
        modelMatrix *= transform2D::Scale(scaleX, scaleY);
    }
    modelMatrix *= transform2D::Translate(-cx, -cy);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);


    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented
    // Remember, the last matrix in the chain will take effect first!
 
    // Se roteste
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(650, 550);

    angularStep3 += deltaTimeSeconds * 0.5;
    modelMatrix *= transform2D::Translate(tx3, ty3);
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Rotate(5 * angularStep3);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

    // BONUS
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0);

    angularStep4 += deltaTimeSeconds * 0.5;
    modelMatrix *= transform2D::Scale(0.4, 0.4);

    if (direction1 == 1) {
        tx4 += deltaTimeSeconds * 50 + 1;
        ty4 += deltaTimeSeconds * 50;
        if (ty4 >= 200) {
            direction1 = 0;
        }
    }

    if (direction1 == 0) {
        tx4 += deltaTimeSeconds * 50 + 1;
        ty4 -= deltaTimeSeconds * 50;
        if (ty4 <= 0) {
            direction1 = 1;
        }
    }


    modelMatrix *= transform2D::Translate(tx4, ty4);
    angularStep4 -= deltaTimeSeconds * 0.89;
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Rotate(angularStep4);
    modelMatrix *= transform2D::Translate(-cx, -cy);

    RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
