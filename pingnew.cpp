#include <iostream>
#include <conio.h>     // For _kbhit() and _getch()
#include <windows.h>   // For Sleep()

using namespace std;

const int width = 40;
const int height = 20;

int ballX, ballY;
int player1Y, player2Y;
int score1 = 0, score2 = 0;
int ballDirX = 1, ballDirY = 1;

bool quit = false;

void Setup() {
    ballX = width / 2;
    ballY = height / 2;
    player1Y = height / 2;
    player2Y = height / 2;
}

void Draw() {
    system("cls"); // clear screen

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0) cout << "#";

            if (x == ballX && y == ballY)
                cout << "O"; // Ball
            else if (x == 1 && (y == player1Y || y == player1Y - 1 || y == player1Y + 1))
                cout << "|"; // Player 1 paddle
            else if (x == width - 2 && (y == player2Y || y == player2Y - 1 || y == player2Y + 1))
                cout << "|"; // Player 2 paddle
            else
                cout << " ";

            if (x == width - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    cout << "Player 1: " << score1 << "  |  Player 2: " << score2 << endl;
    cout << "Controls: W/S (Player 1)  Up/Down Arrows (Player 2)" << endl;
}

void Input() {
    if (_kbhit()) {
        char current = _getch();
        switch (current) {
            case 'w':
            case 'W':
                if (player1Y > 1) player1Y--;
                break;
            case 's':
            case 'S':
                if (player1Y < height - 2) player1Y++;
                break;
            case 72: // up arrow
                if (player2Y > 1) player2Y--;
                break;
            case 80: // down arrow
                if (player2Y < height - 2) player2Y++;
                break;
            case 'q':
            case 'Q':
                quit = true;
                break;
        }
    }
}

void Logic() {
    ballX += ballDirX;
    ballY += ballDirY;

    // Top and bottom wall collision
    if (ballY == 0 || ballY == height - 1)
        ballDirY *= -1;

    // Paddle collision
    if (ballX == 2 && (ballY == player1Y || ballY == player1Y - 1 || ballY == player1Y + 1))
        ballDirX *= -1;
    if (ballX == width - 3 && (ballY == player2Y || ballY == player2Y - 1 || ballY == player2Y + 1))
        ballDirX *= -1;

    // Scoring
    if (ballX <= 0) {
        score2++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = 1;
    }
    if (ballX >= width - 1) {
        score1++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = -1;
    }
}

int main() {
    Setup();

    while (!quit) {
        Draw();
        Input();
        Logic();
        Sleep(50); // adjust speed
    }

    return 0;
}
