#include <iostream>
#include "Constant.h"

using namespace std;

int player_score{};
int ai_score{};

class Ball {

private:
    float pos_x;
    float pos_y;
    float radius;
    int speed_x;
    int speed_y;
    Color color;

public:
    Ball(float pos_x, float pos_y, float radius, int speed_x, int speed_y, Color color) {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->radius = radius;
        this->speed_x = speed_x;
        this->speed_y = speed_y;
        this->color = color;
    }

    void draw() {
        DrawCircle(pos_x, pos_y, radius, color);
    }

    void update() {
        int width = GetScreenWidth();
        int height = GetScreenHeight();

        update_ball_pos();
        check_for_score(width);

        // change direction if colision with top or bottom
        if (pos_y >= height){
            speed_y *= -1;
            pos_y = height - radius;
        }else if (pos_y < 0) {
            speed_y *= -1;
            pos_y = radius;
        }
    }

    void check_for_score(int width) {
        if (pos_x >= width || pos_x < 0) {
            if (pos_x >= width) {
                player_score++;
            }
            else {
                ai_score++;
            }

            reset_pos();
        }
    }

    void update_ball_pos() {
        pos_x += speed_x;
        pos_y += speed_y;
    }

    void reset_pos() {
        pos_x = screen_center_x;
        pos_y = screen_center_y;

        if (speed_x > 0) {
            speed_x = ball_start_speed_x * -1;
        }
        else {
            speed_x = ball_start_speed_x;
        }

        if (speed_y > 0) {
            speed_y = ball_start_speed_y * -1;
        }
        else {
            speed_y = ball_start_speed_y;
        }
    };

    void change_x_direction() {
        // generate random value for speed value3
        int random_x = 1 + rand() % ball_max_speed_x;
        random_x = max(ball_min_speed_x, random_x);

        if (speed_x > 0) {
            speed_x = -random_x;
        }
        else {
            speed_x = random_x;
        }

        // generate random value for angle value
        int random_y = 1 + rand() % ball_max_speed_y;
        random_y = max(ball_min_speed_y, random_y);

        if (speed_y > 0) {
            speed_y = -random_y;
        }
        else {
            speed_y = random_y;
        }

        // genera random y direction
        int random_d = -1 + rand() % 2;
        if (random_d == -1) speed_y *= -1;

    }

    bool moving_right() {
        return speed_x > 0;
    }

    float get_l_site() {
        return pos_x - radius;
    }

    float get_r_site() {
        return pos_x + radius;
    }

    float get_u_site() {
        return pos_y - radius;
    }

    float get_d_site() {
        return pos_y + radius;
    }

    float get_radius() {
        return radius;
    }
};

class Paddle {
protected:
    float pos_x;
    float pos_y;
    float width;
    float height;
    int speed;
    Color color;


public:
    Paddle(float pos_x, float pos_y, float width, float height, int speed, Color color) {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->width = width;
        this->height = height;
        this->speed = speed;
        this->color = color;
    }

    void update() {
        if (IsKeyDown(KEY_UP) && pos_y > 0) {
            pos_y -= speed;
        }
        else if (IsKeyDown(KEY_DOWN) && pos_y + height < window_height) {
            pos_y += speed;
        }
    }

    void draw() {
        DrawRectangleRounded(Rectangle{ pos_x, pos_y, width, height }, paddle_rounding, 0, color);
    }

    float get_x() {
        return pos_x;
    }

    float get_y() {
        return pos_y;
    }

    float get_width() {
        return width;
    }

    float get_height() {
        return height;
    }
};

class AIPaddle : public Paddle {
public:
    AIPaddle(float pos_x, float pos_y, float width, float height, int speed, Color color) :Paddle(pos_x, pos_y, width, height, speed, color) {}

    void update(Ball ball) {
        if (ball.get_d_site() - height / 2 < pos_y ) pos_y -= ai_paddle_speed;
        if (ball.get_u_site() - height / 2 > pos_y ) pos_y += ai_paddle_speed;
    }
};


bool check_paddle_collision(Ball ball, Paddle paddle);
void draw_scene();

int main(){
    cout << "Game starting." << endl;
    InitWindow(window_width, window_height, "Pong");
    SetTargetFPS(60);

    Ball ball = Ball(screen_center_x, screen_center_y, ball_radius, ball_start_speed_x, ball_start_speed_y, ball_color);

    int paddle_center_y = screen_center_y - (paddle_height / 2);
    Paddle player = Paddle(p_wall_padding, paddle_center_y, paddle_width, paddle_height, player_paddle_speed, paddle_color);
    AIPaddle ai = AIPaddle(window_width - p_wall_padding - paddle_width, paddle_center_y, paddle_width, paddle_height, ai_paddle_speed, paddle_color);

    // game loop
    while (!WindowShouldClose()) {

        // update
        ball.update();
        player.update();
        ai.update(ball);

        // check for paddle colission
         if (check_paddle_collision(ball, player) || check_paddle_collision(ball, ai)) ball.change_x_direction();

        // draw
        BeginDrawing();
        draw_scene();
        ball.draw();
        player.draw();
        ai.draw();
        EndDrawing();
    }

    CloseWindow();

    cout << "Game ending" << endl;
}

void draw_scene() {
    int part = window_width / 3;
    int player_score_x_pos = part;
    int ai_score_x_pos = part * 2;

    ClearBackground(Dark_Green);
    DrawRectangle(0, 0, window_width / 2, window_height, first_color);
    DrawCircle(screen_center_x, screen_center_y, circle_radius, second_color);
    DrawLine(window_width / 2, 0, window_width / 2, window_height, fourth_color);
    DrawText(TextFormat("%i", player_score), player_score_x_pos, score_y_pos, score_font_size, fourth_color);
    DrawText(TextFormat("%i", ai_score), ai_score_x_pos, score_y_pos, score_font_size, fourth_color);
}

bool check_paddle_collision(Ball ball, Paddle paddle) {
    float b_l_site = ball.get_l_site();
    float b_r_site = ball.get_r_site();
    float b_u_site = ball.get_u_site();
    float b_d_site = ball.get_d_site();

    float p_x = paddle.get_x();
    float p_y = paddle.get_y();
    float p_w = paddle.get_width();
    float p_h = paddle.get_height();
    float p_y_s = p_y;
    float p_y_e = p_y + p_h;

    if (!(b_d_site >= p_y_s && b_u_site <= p_y_e)) {
        return false;
    }

    if (ball.moving_right()) {
        return b_r_site > p_x && b_r_site < p_x + p_w;
    }else {
         return b_l_site <= p_x + p_w && b_l_site >= p_x;
    } 
}

