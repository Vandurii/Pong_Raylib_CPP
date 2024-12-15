
#include <raylib.h>

// colors
const Color Green = Color{ 38, 185, 154, 255 };
const Color Dark_Green = Color{ 20, 168, 133, 255 };
const Color Light_Green = Color{ 129, 204, 184, 255 };
const Color Yellow = Color{ 243, 185, 154, 255 };

// window
const int FPS_Target = 60;
const char title[]{ "Pong" };
const int target_FPS = 60;
const int window_width = 1280;
const int window_height = 800;

const int screen_center_x = window_width / 2;
const int screen_center_y = window_height / 2;

// ball
const int ball_radius = 15;
const int ball_start_speed_x = 10;
const int ball_min_speed_x = 10; 
const int ball_max_speed_x = 30; 
const int ball_start_speed_y = 0;
const int ball_min_speed_y = 6; 
const int ball_max_speed_y = 15; 
const Color ball_color = Yellow;

// paddle
const int paddle_width = 32;
const int paddle_height = 140;
const int p_wall_padding = 50;
const int ai_paddle_speed = 10;
const int player_paddle_speed = 20;
const int paddle_rounding = 8;
const Color paddle_color = WHITE;

// Scene
const int circle_radius = 100;
const int score_y_pos = 100;
const int score_font_size = 40;
const Color first_color = Green;
const Color second_color = Light_Green;
const Color third_color = Dark_Green;
const Color fourth_color = WHITE;

