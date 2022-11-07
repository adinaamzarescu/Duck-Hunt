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

        float length_border;
        float width_border;

        int directionMove1;
        int directionMove2;
        int directionMove3;
        int directionMove4;

        float length_score_frame;
        float width_score_frame;

        float length_score;
        float width_score;

        float tx_score;
        float ty_score;
        float scale_score;
        float score_next_level;

        float next_round;

        float length;
        float length1;
        float length2;
        float length3;

        float translateX;
        float translateY;
        float translateX1;
        float translateY1;
        float translateX2;
        float translateY2;

        float tx_grass;
        float ty_grass;

        float tx_bullet1;
        float ty_bullet1;
        float tx_bullet2;
        float ty_bullet2;
        float tx_bullet3;
        float ty_bullet3;

        float scale_bullet1;
        float scale_bullet2;
        float scale_bullet3;

        float tx_circle1;
        float ty_circle1;
        float tx_circle2;
        float ty_circle2;
        float tx_circle3;
        float ty_circle3;

        float scale_circle1;
        float scale_circle2;
        float scale_circle3;

        float length_body;
        float tx_body;
        float ty_body;
        float tx_wing1;
        float ty_wing1;
        float tx_wing2;
        float ty_wing2;
        float tx_head;
        float ty_head;
        float tx_beak;
        float ty_beak;

        double angularWing1;
        double angularWing2;
        int directionWing1;
        int directionWing2;

        double angularMove;

        // Killing spree
        float squareSide;
        float tx_square;
        float ty_square;
        float scale_square;
        int scale_bool_square;
        int killing_spree;

        int life;
        int bullet_nr;
        int hit;
        int duck_hit;
        int random;


        float length_grass;
        float width_grass;

        float length_bullet;
        float width_bullet;

        float time;
        float speed;

        int show_text;
        float timer;
        

        float cx;
        float cy;

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

            // Draw primitives mode
            GLenum polygonMode;

            // Colors
            const glm::vec3 kTextColor = NormalizedRGB(166, 172, 205);
            const glm::vec3 kBackgroundColor = NormalizedRGB(41, 45, 62);
    };
}   // namespace m1
