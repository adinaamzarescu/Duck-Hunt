#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"


using namespace std;
using namespace m1;


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

    time = 0;
    speed = 100;
    random = 0;
    next_round = 0;
    escape = 0;

    length_border = 1115;
    width_border = 610;

    directionMove1 = 1;
    directionMove2 = 1;
    directionMove3 = 1;

    next_round = 0;

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
    score_next_level = 5;

    // Duck
    // Body
    length_body = 100;
    tx_body = 200;
    ty_body = 100;
    angularMove = 3.14 * 0.25;

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

    // Killing spree
    squareSide = 50;
    ty_square = resolution.y - 80;
    tx_square = 50;
    scale_square = 0;
    scale_bool_square = 1;
    killing_spree = 0;
    angularKilling = 0;

    show_text = 0;
    timer = 0;

    show_over = 0;
    show_wow = 0;

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

    // Killing Spree 
    Mesh* square = object2D::CreateSquare("square", corner, squareSide, glm::vec3(1, 0, 1), true);
    AddMeshToList(square);

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

    // Show text for killing spree
    textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

    textRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 18);

    // Game over
    Mesh* mesh1 = new Mesh("sad");
    mesh1->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sad3.fbx");
    meshes[mesh1->GetMeshID()] = mesh1;

    Mesh* mesh2 = new Mesh("happy");
    mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "happy.fbx");
    meshes[mesh2->GetMeshID()] = mesh2;


}

void Tema1::DrawHUD()
{
    if (show_over == 1) {
        // If the game is over

        const float wellX = 250;
        const float wellY = 100;
        // Let's be supportive with everyone
        textRenderer->RenderText("GOOD GAME! WELL PLAYED!", wellX, wellY, 3.0f, glm::vec3(0.138, 0.043, 0.226));

        if (show_wow == 0) {
            // If the player lost
            const float over_top = 450;
            const float over_width = 200;
            textRenderer->RenderText("GAME OVER", over_top, over_width, 3.0f, kTextColor);
        }
        else {
            // If the player won
            const float wow_top = 300;
            const float wow_width = 200;
            textRenderer->RenderText("YOU ARE A CHAMPION!", wow_top, wow_width, 3.0f, kTextColor);
        }
        // Show the final score
        const float finalScoreTop = 500;
        const float finalScoreWidth = 600;
        textRenderer->RenderText(" FINAL SCORE =", finalScoreTop, finalScoreWidth, 1.0f, kTextColor);
        // Convert the float to a string
        stringstream ss;
        ss << scale_score;
        string str = ss.str();
        textRenderer->RenderText(str, finalScoreTop + 180, finalScoreWidth, 1.0f, kTextColor);
    }
    else {
        // Show the killing spree text
        if (killing_spree >= 5) {
            const float killingX = 5;
            const float killingY = 5;

            textRenderer->RenderText("Killing spree!", killingX, killingY, 1.0f, kTextColor);
        }

        // Show the score
        const float scoreTop = 170;
        const float scoreWidth = 1000;
        textRenderer->RenderText("Score =", scoreWidth, scoreTop, 1.0f, kTextColor);

        // Convert float to string
        stringstream ss;
        ss << scale_score;
        string str = ss.str();
        textRenderer->RenderText(str, scoreWidth + 90, scoreTop, 1.0f, kTextColor);

        // Announce the next round
        if (show_text == 1) {
            const float next_top = 550;
            const float next_width = 50;
            textRenderer->RenderText("Next Round", next_top, next_width, 1.0f, glm::vec3(0.255, 0.105, 0.180));
        }
    }
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
    DrawHUD();
    time += deltaTimeSeconds;
    visMatrix = glm::mat3(1);

    // Game over
    if (show_over == 1 && show_wow == 0) {

        // Render the sad face
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(0, 0);

        RenderMesh(meshes["sad"], glm::vec3(600, 300, 0), glm::vec3(300,300,0));
    }
    else if (show_over == 1 && show_wow == 1) {
        // Render the happy face
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(0, 0);

        RenderMesh(meshes["happy"], glm::vec3(600, 300, 0), glm::vec3(300, 300, 0));
    }
    else {
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
        modelMatrix *= transform2D::Scale(scale_score, width_score);
        RenderMesh2D(meshes["rectangle5"], shaders["VertexColor"], modelMatrix);

        // Killing spree
        angularKilling += deltaTimeSeconds * 0.5;

        // If 5 or more ducks are hit without missing
        if (killing_spree >= 5) {

            if (scale_bool_square == 1) {
                scale_square += deltaTimeSeconds * 0.5;
                if (scale_square >= 0.7) {
                    scale_bool_square = 0;
                }
            }

            if (scale_bool_square == 0) {
                scale_square -= deltaTimeSeconds * 0.5;
                if (scale_square < 0.1) {
                    scale_bool_square = 1;
                }
            }
        }
        else {
            scale_square = 0;
        }

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(tx_square, ty_square);

        modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
        modelMatrix *= transform2D::Scale(scale_square, scale_square);
        modelMatrix *= transform2D::Rotate(10 * angularKilling);
        modelMatrix *= transform2D::Translate(-squareSide / 2, -squareSide / 2);

        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        // Duck

        // After 10 seconds the duck will fly away
        // Or after the 3 bullets were shot without hitting the duck
        if (time > 5 || escape == 1) {
            angularMove = 3.14 * 0.5;
            ty_body += speed * 3 * deltaTimeSeconds;

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
                // If a duck escapes, the player loses a heart
                // and the killing spree is over
                life--;
                killing_spree = 0;
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

                // After a escapes the player gets 3 bullets
                bullet_nr = 3;
                scale_bullet1 = 1;
                scale_bullet2 = 1;
                scale_bullet3 = 1;

                escape = 0;
                next_round++;
                time = 0;
            }
        }

        if (duck_hit == 1) {
            directionMove1 = -1;

            time = 0;
            angularMove = 3.14 * 0.5 * 3.14;
            ty_body -= speed * 3 * deltaTimeSeconds;

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
                // After a duck is hit the player gets 3 bullets
                bullet_nr = 3;
                scale_bullet1 = 1;
                scale_bullet2 = 1;
                scale_bullet3 = 1;
                killing_spree++;

                // When next_round reaches 5 the player will
                // start a new round
                next_round++;

                // A "new" duck will appear
                duck_hit = 0;
            }
        }

        if (next_round >= 5) {
            speed += 100;
            // For the next round the score will be higher
            score_next_level += 1;
            show_text = 1;
            next_round = 0;
        }
        else {
            // Show the text for only 3 seconds
            timer += deltaTimeSeconds;
            if (timer > 3) {
                show_text = 0;
                timer = 0;
            }
        }

        // There are 4 possible directions

        if (directionMove1 == 1) {
            // At first each duck will more diagonally
            // at an pi/4 angle
            tx_body += speed * deltaTimeSeconds;
            ty_body += speed * deltaTimeSeconds;
            angularMove = 3.14 * 0.25;
            // Change direction when reaching the upper y border
            if (ty_body > width_border && tx_body < length_border)
                directionMove1 = 0;
            // Change direction when reaching the upper x border
            if (tx_body >= length_border && ty_body >= 0) {
                directionMove3 = 0;
                directionMove1 = -1;
            }

        }
        // The duck will rotate at a 3pi/4 angle
        if (directionMove1 == 0) {
            tx_body += speed * deltaTimeSeconds;
            angularMove = (3 / 4) * 3.14;
            ty_body -= speed * deltaTimeSeconds;
            // Change direction when reaching the upper x border
            if (tx_body >= length_border && ty_body >= 0) {
                directionMove2 = 0;
                directionMove1 = -1;
            }
            // Change direction when reaching the lower y border
            if (ty_body <= 0 && tx_body <= length_border) {
                directionMove1 = 1;
            }
        }
        // The duck will rotate at a 5pi/4 angle
        if (directionMove2 == 0) {
            tx_body -= speed * deltaTimeSeconds;
            angularMove = 3.14 * 5 / 4;
            ty_body -= speed * deltaTimeSeconds;
            // There are 2 cases
            // The duck reaches the lower y border first
            if (ty_body <= 0) {
                directionMove3 = 0;
                directionMove2 = 1;
            }
            // The duck reaches the lower x border first
            if (tx_body <= 0) {
                directionMove2 = 1;
                directionMove1 = 0;
            }
        }
        // The duck will rotate at a 7pi/4 angle
        if (directionMove3 == 0) {
            tx_body -= speed * deltaTimeSeconds;
            angularMove = (7 / 4) * 3.14;
            ty_body += speed * deltaTimeSeconds;
            // Change direction when reaching the lower x border
            if (tx_body <= 0) {
                directionMove1 = 1;
                directionMove3 = 1;
            }
            // Change direction when reaching the upper y border
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
    // If the player reached the maximum score
    if (scale_score >= width_score_frame) {
        show_wow = 1;
        GameOver();
    }
}


void Tema1::FrameEnd(){}

void Tema1::OnInputUpdate(float deltaTime, int mods){}


void Tema1::OnKeyPress(int key, int mods){}


void Tema1::OnKeyRelease(int key, int mods){}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    glm::ivec2 resolution = window->GetResolution();

    // When the resolution.x is 1280 the scaling of tx_body is 1:1
    // So in order to work for any resolution x_min is created
    float x_min = (float) 1280 / tx_body;

    // The difference between the left edge and the right one is 200
    float diffX = (float) 1280 / 200;

    // When the resolution.y is 720 the scaling of ty_body is 1:1
    // So in order to work for any resolution y_min is created
    float y_min = (float) 720 / ty_body;

    // If the mouse is between the edges of the virtual rectangle
    if (mouseX <= (resolution.x / x_min) + (resolution.x / diffX) && mouseX > (resolution.x / x_min) - 100) {
        if (mouseY <= resolution.y - (resolution.y / y_min) + 100 && mouseY >= resolution.y - (resolution.y / y_min) - 200) {
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
    // If the bullet was shot and the duck wasn't hit

    if (button == GLFW_MOUSE_BUTTON_2 && hit == 0) {
        // Remove bullet depending on which one was shot
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
            // After the 3rd bullet was shot the duck escapes
            escape = 1;
            break;
        default:
            // If all 3 bullets have been shot and the duck wasn't hit
            // the player loses a heart
            switch (life) {
            case 3:
                break;
            case 2:
                scale_circle1 = 0;
                break;
            case 1:
                scale_circle2 = 0;
                break;
            default:
                // If there are no hearts left the game ends
                scale_circle3 = 0;
                GameOver();
                break;
            }
            break;
        }
    }

    // If the bullet was shot and the duck was hit
    else if (button == GLFW_MOUSE_BUTTON_2 && hit == 1) {
        // The player still loses bullets, but they will get them back afterwards
        // The score is higher for each duck
        switch (bullet_nr) {
        case 3:
            scale_score += score_next_level;
            scale_bullet3 = 0;
            duck_hit = 1;
            break;
        case 2:
            scale_score += score_next_level;
            scale_bullet2 = 0;
            duck_hit = 1;
            break;
        case 1:
            scale_score += score_next_level;
            scale_bullet1 = 0;
            duck_hit = 1;
            break;
        default:
            break;
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods){}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY){}

void Tema1::GameOver() {
   show_over = 1;
}
