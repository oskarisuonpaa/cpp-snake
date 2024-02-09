#include <iostream>
#include <conio.h>
#include <windows.h> 

const int WIDTH = 80, HEIGHT = 20;

int snakeHeadX, snakeHeadY, snakeTailX[100], snakeTailY[100], snakeLength, fruitX, fruitY;
enum snakeDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakeDirection direction;
bool isGameOver;

void init();
void input();
void update();
void draw();

int main() {
    init();

    while (!isGameOver) {
        input();
        update();
        draw();

        Sleep(100);
    }

    return 0;
}

void init() {
    isGameOver = false;
    direction = STOP;
    snakeHeadX = WIDTH / 2;
    snakeHeadY = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            direction = LEFT;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'w':
            direction = UP;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}

void update() {
    int previousX = snakeTailX[0], previousY = snakeTailY[0], previous2X, previous2Y;
    snakeTailX[0] = snakeHeadX;
    snakeTailY[0] = snakeHeadY;

    for (int i = 1; i < snakeLength; i++) {
        previous2X = snakeTailX[i];
        previous2Y = snakeTailY[i];
        snakeTailX[i] = previousX;
        snakeTailY[i] = previousY;
        previousX = previous2X;
        previousY = previous2Y;
    }

    switch (direction) {
        case LEFT:
            snakeHeadX--;
            break;
        case RIGHT:
            snakeHeadX++;
            break;
        case UP:
            snakeHeadY--;
            break;
        case DOWN:
            snakeHeadY++;
            break;
        case STOP:
            break;
    }

    if (snakeHeadX >= WIDTH) snakeHeadX = 0; else if (snakeHeadX < 0) snakeHeadX = WIDTH - 1;

    if (snakeHeadY >= HEIGHT) snakeHeadY = 0; else if (snakeHeadY < 0) snakeHeadY = HEIGHT - 1;

    for (int i = 0; i < snakeLength; i++) {
        if (snakeTailX[i] == snakeHeadX && snakeTailY[i] == snakeHeadY) {
            isGameOver = true;
        }
    }

    if (snakeHeadX == fruitX && snakeHeadY == fruitY) {
        snakeLength++;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

void draw() {
    system("cls");

    for (int i = 0; i < WIDTH + 2; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                std::cout << "#";
            }
            if (i == snakeHeadY && j == snakeHeadX) {
                std::cout << "O";
            } else if (i == fruitY && j == fruitX) {
                std::cout << "F";
            } else {
                bool isPrinted = false;
                for (int k = 0; k < snakeLength; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        std::cout << "o";
                        isPrinted = true;
                    }
                }
                if (!isPrinted) {
                    std::cout << " ";
                }
            }
            if (j == WIDTH - 1) {
                std::cout << "#";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < WIDTH + 2; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;

    std::cout << "Score: " << snakeLength << std::endl;
}
