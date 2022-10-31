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
    float squareSide = 100;

    length = 100;

    length_grass = 200;
    width_grass = 10000;

    length_body = 100;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    //cx = corner.x + length / 2;
    //cy = corner.y + length / 2;


    // Create the grass
    Mesh* rectangle = object2D::CreateRectangle("rectangle", corner, length_grass, width_grass, glm::vec3(0, 1, 0), true);
    AddMeshToList(rectangle);

    // Create the body
    Mesh* triangle1 = object2D::CreateTriangle("triangle1", corner, length_body, glm::vec3(1, 0, 0), true);
    AddMeshToList(triangle1);

    // Create the wings
    Mesh* triangle2 = object2D::CreateTriangle("triangle2", corner, length_body, glm::vec3(0, 1, 1), true);
    AddMeshToList(triangle2);

    Mesh* triangle3 = object2D::CreateTriangle("triangle3", corner, length_body, glm::vec3(0.139, 0.069, 0.019), true);
    AddMeshToList(triangle3);

    // Create head
    Mesh* circle = object2D::CreateCircle("circle", corner, glm::vec3(0.085, 0.107, 0.047), true);
    AddMeshToList(circle);


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


    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    DrawScene(visMatrix);

}

void Tema1::DrawScene(glm::mat3 visMatrix)
{
    // Draw the grass
    modelMatrix = glm::mat3(1);
    //modelMatrix *= transform2D::Translate(0, 0);

    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    // Draw the duck

    // Body
    //translateX = 200;
    //translateY = 400;
    //angularStep = 4;

    //modelMatrix = visMatrix * transform2D::Translate(translateX + (length_body * 0.4), translateY + (length_body * 0.5));
    //modelMatrix *= transform2D::Rotate(angularStep);
    //modelMatrix *= transform2D::Scale(0.008 * length_body, 0.008 * length_body);
    //RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);

    //// Wings

    //modelMatrix = visMatrix * transform2D::Translate(translateX + (length_body * 0.4), translateY + (length_body * 0.5));
    //modelMatrix *= transform2D::Rotate(angularStep);
    //modelMatrix *= transform2D::Scale(0.008 * length_body, 0.008 * length_body);
    //RenderMesh2D(meshes["triangle2"], shaders["VertexColor"], modelMatrix);
    //angularStep = 2;

    //angularStep = length_body * 0.001;

    //modelMatrix = visMatrix * transform2D::Translate(translateX + (length_body * 0.4), translateY + (length_body * 0.4));
    //modelMatrix *= transform2D::Rotate(angularStep);
    //modelMatrix *= transform2D::Scale(0.008 * length_body, 0.008 * length_body);
    //RenderMesh2D(meshes["triangle3"], shaders["VertexColor"], modelMatrix);

    //// Head

    //angularStep = 2;

    //modelMatrix = visMatrix * transform2D::Translate(translateX + (length_body * 1.2), translateY + (length_body * 0.09));
    //modelMatrix *= transform2D::Rotate(angularStep);
    //modelMatrix *= transform2D::Scale(0.25 * length_body, 0.25 * length_body);
    //RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);


}

// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
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
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
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


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
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
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
