#include <graphics.h>
#include <conio.h>
#include <stdio.h>

// Game constants
const int screen_width = 640;
const int screen_height = 480;
const int paddle_width = 100;
const int paddle_height = 10;
const int ball_size = 10;
const int brick_rows = 5;
const int brick_cols = 8;
const int brick_width = 60;
const int brick_height = 20;

// Paddle and ball positions
int paddle_x = screen_width / 2 - paddle_width / 2;
int paddle_y = screen_height - 40;
int ball_x = screen_width / 2, ball_y = screen_height / 2;
int ball_speed_x = 5, ball_speed_y = -5;
int score = 0;

// Bricks grid
int bricks[brick_rows][brick_cols];

// Function to initialize bricks
void initBricks() {
    for (int i = 0; i < brick_rows; i++) {
        for (int j = 0; j < brick_cols; j++) {
            bricks[i][j] = 1;  // All bricks are initially intact
        }
    }
}

// Function to draw paddle, ball, and bricks
void drawGame() {
    // Clear screen
    cleardevice();

    // Draw paddle
    setcolor(WHITE);
    rectangle(paddle_x, paddle_y, paddle_x + paddle_width, paddle_y + paddle_height);
    floodfill(paddle_x + 1, paddle_y + 1, WHITE);

    // Draw ball
    setcolor(WHITE);
    rectangle(ball_x, ball_y, ball_x + ball_size, ball_y + ball_size);
    floodfill(ball_x + 1, ball_y + 1, WHITE);

    // Draw bricks
    for (int i = 0; i < brick_rows; i++) {
        for (int j = 0; j < brick_cols; j++) {
            if (bricks[i][j] == 1) {
                int brick_x = j * brick_width + 50;
                int brick_y = i * brick_height + 50;
                setcolor(RED);
                rectangle(brick_x, brick_y, brick_x + brick_width, brick_y + brick_height);
                floodfill(brick_x + 1, brick_y + 1, RED);
            }
        }
    }

    // Display score
    char score_str[20];
    sprintf(score_str, "Score: %d", score);
    outtextxy(10, 10, score_str);
}

// Function to handle ball movement and collisions
void updateBall() {
    // Move ball
    ball_x += ball_speed_x;
    ball_y += ball_speed_y;

    // Ball collision with screen borders
    if (ball_x <= 0 || ball_x >= screen_width - ball_size) {
        ball_speed_x = -ball_speed_x;
    }
    if (ball_y <= 0) {
        ball_speed_y = -ball_speed_y;
    }

    // Ball collision with paddle
    if (ball_y + ball_size >= paddle_y && ball_x + ball_size >= paddle_x && ball_x <= paddle_x + paddle_width) {
        ball_speed_y = -ball_speed_y;
    }

    // Ball collision with bricks
    for (int i = 0; i < brick_rows; i++) {
        for (int j = 0; j < brick_cols; j++) {
            if (bricks[i][j] == 1) {
                int brick_x = j * brick_width + 50;
                int brick_y = i * brick_height + 50;
                if (ball_x + ball_size >= brick_x && ball_x <= brick_x + brick_width &&
                    ball_y + ball_size >= brick_y && ball_y <= brick_y + brick_height) {
                    ball_speed_y = -ball_speed_y;
                    bricks[i][j] = 0;  // Brick is destroyed
                    score += 10;  // Increment score
                }
            }
        }
    }

    // Check for game over (ball falls off the bottom)
    if (ball_y >= screen_height) {
        outtextxy(screen_width / 2 - 50, screen_height / 2, (char*)"Game Over");
        delay(2000);
        exit(0);
    }
}

// Function to control paddle movement
void controlPaddle() {
    // Move paddle left or right using arrow keys
    if (GetAsyncKeyState(VK_LEFT) && paddle_x > 0) {
        paddle_x -= 10;
    }
    if (GetAsyncKeyState(VK_RIGHT) && paddle_x < screen_width - paddle_width) {
        paddle_x += 10;
    }
}

// Main game loop
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // Initialize bricks
    initBricks();

    // Game loop
    while (1) {
        controlPaddle();
        updateBall();
        drawGame();
        delay(30);  // Control ball speed

        // Check for exit key (Esc)
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
    }

    // End game
    getch();
    closegraph();
    return 0;
}

