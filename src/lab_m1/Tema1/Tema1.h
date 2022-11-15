#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"

using namespace std;

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;


        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void GameOver();


    protected:

        // The border
        float length_border = 0;
        float width_border = 0;

        // The 4 possible directions (2 for directionMove1)
        int directionMove1 = 0;
        int directionMove2 = 0;
        int directionMove3 = 0;

        // Score
        float length_score_frame = 0;
        float width_score_frame = 0;

        float length_score = 0;
        float width_score = 0;

        float tx_score = 0;
        float ty_score = 0;
        float scale_score = 0;
        float score_next_level = 0;

        // Gameplay variables
        float next_round = 0;
        int escape = 0;
        int life = 0;
        int bullet_nr = 0;
        int hit = 0;
        int duck_hit = 0;
        int random = 0;

        float time = 0;
        float speed = 0;

        // Grass
        float tx_grass = 0;
        float ty_grass = 0;
        float length_grass = 0;
        float width_grass = 0;

        // Bullets
        float tx_bullet1 = 0;
        float ty_bullet1 = 0;
        float tx_bullet2 = 0;
        float ty_bullet2 = 0;
        float tx_bullet3 = 0;
        float ty_bullet3 = 0;

        float scale_bullet1 = 0;
        float scale_bullet2 = 0;
        float scale_bullet3 = 0;

        float length_bullet = 0;
        float width_bullet = 0;

        // Lives
        float tx_circle1 = 0;
        float ty_circle1 = 0;
        float tx_circle2 = 0;
        float ty_circle2 = 0;
        float tx_circle3 = 0;
        float ty_circle3 = 0;

        float scale_circle1 = 0;
        float scale_circle2 = 0;
        float scale_circle3 = 0;

        // Body
        float length_body = 0;
        float tx_body = 0;
        float ty_body = 0;

        // Wing
        float tx_wing1 = 0;
        float ty_wing1 = 0;
        float tx_wing2 = 0;
        float ty_wing2 = 0;
        double angularWing1 = 0;
        double angularWing2 = 0;
        int directionWing1 = 0;
        int directionWing2 = 0;

        // Head
        float tx_head = 0;
        float ty_head = 0;

        // Beak
        float tx_beak = 0;
        float ty_beak = 0;

        // Rotation for the duck
        double angularMove = 0;

        // Killing spree
        float squareSide = 0;
        float tx_square = 0;
        float ty_square = 0;
        float scale_square = 0;
        int scale_bool_square = 0;
        int killing_spree = 0;
        float angularKilling = 0;

        int show_text = 0;
        float timer = 0;

        // Game over
        int show_over = 0;
        float tx_over = 0;
        float ty_over = 0;
        float scale_over = 0;
        float length_over = 0;
        float width_over = 0;
        // Game won
        int show_wow = 0;

        float cx = 0;
        float cy = 0;

        glm::mat3 modelMatrix, visMatrix;
        glm::mat3 modelMatrixBody;
        glm::mat3 modelMatrixWing1;
        glm::mat3 modelMatrixWing2;
        glm::mat3 modelMatrixHead;
        glm::mat3 modelMatrixBeak;

        // Killing spree text
        void DrawHUD();
    private:
        // The actual renderer object
        gfxc::TextRenderer* textRenderer;

        // Colors
        const glm::vec3 kTextColor = NormalizedRGB(166, 172, 205);
        const glm::vec3 kBackgroundColor = NormalizedRGB(41, 45, 62);
    };
}   // namespace m1
