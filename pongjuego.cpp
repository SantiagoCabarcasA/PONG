#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class cBall {
private:
    int x, y;
    int originalX, originalY;
    eDir direction;
public:
    cBall(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX; 
        y = posY;
        direction = STOP;
    }

    void Reset() {
        x = originalX; 
        y = originalY;
        direction = STOP;
    }

    void changeDirection(eDir d) {
        direction = d;
    }

    void randomDirection() {
        direction = (eDir)((rand() % 6) + 1);
    }

    inline int getX() { return x; }
    inline int getY() { return y; }
    inline eDir getDirection() { return direction; }

    void Move() {
        switch (direction) {
            case STOP: break;
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UPLEFT: x--; y--; break;
            case DOWNLEFT: x--; y++; break;
            case UPRIGHT: x++; y--; break;
            case DOWNRIGHT: x++; y++; break;
            default: break;
        }
    }

    friend ostream& operator<<(ostream& o, const cBall& c) {
        o << "Ball [" << c.x << "," << c.y << "] Direction: " << c.direction;
        return o;
    }
};

class cPaddle {
private:
    int x, y;
    int originalX, originalY;
public:
    cPaddle() { x = y = 0; }

    cPaddle(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }

    inline void Reset() { x = originalX; y = originalY; }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline void moveUp() { y--; }
    inline void moveDown() { y++; }

    friend ostream& operator<<(ostream& o, const cPaddle& c) {
        o << "Paddle [" << c.x << "," << c.y << "]";
        return o;
    }
};

class cGameManager {
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cBall* ball;
    cPaddle* player1;
    cPaddle* player2;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 

public:
    cGameManager(int w, int h) {
        srand(time(NULL));
        quit = false;
        up1 = 'w'; down1 = 's';
        up2 = 'i'; down2 = 'k';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new cBall(w / 2, h / 2);
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w - 2, h / 2 - 3);
    }

    ~cGameManager() {
        delete ball;
        delete player1;
        delete player2;
    }

    void ScoreUp(cPaddle* player) {
        if (player == player1) score1++;
        else if (player == player2) score2++;
        
        ball->Reset();
        player1->Reset();
        player2->Reset();
    }

    void ClearScreen() {
        COORD cursorPosition = { 0, 0 };
        SetConsoleCursorPosition(console, cursorPosition);
    }

    void Draw() {
        ClearScreen(); 

        for (int i = 0; i < width + 2; i++) cout << char(206);
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = player1->getX();
                int player2x = player2->getX();
                int player1y = player1->getY();
                int player2y = player2->getY();

                if (j == 0) cout << char(206);

                if (ballx == j && bally == i)
                    cout << "O"; 
                else if (player1x == j && (player1y <= i && i < player1y + 4))
                    cout << char(219); 
                else if (player2x == j && (player2y <= i && i < player2y + 4))
                    cout << char(219); 
                else
                    cout << " ";

                if (j == width - 1) cout << char(206);
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++) cout << char(206);
        cout << endl;

        cout << "Puntuacion 1: " << score1 << endl << "Puntuacion 2: " << score2 << endl;
    }

    void Input() {
        ball->Move();

        int player1y = player1->getY();
        int player2y = player2->getY();

        if (_kbhit()) {
            char current = _getch();
            if (current == up1 && player1y > 0)
                player1->moveUp();
            if (current == down1 && player1y + 4 < height)
                player1->moveDown();
            if (current == up2 && player2y > 0)
                player2->moveUp();
            if (current == down2 && player2y + 4 < height)
                player2->moveDown();
            if (ball->getDirection() == STOP)
                ball->randomDirection();
            if (current == 'q')
                quit = true;
        }
    }

    void Logic() {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        
        for (int i = 0; i < 4; i++) {
            if (ballx == player1x + 1 && bally == player1y + i)
                ball->changeDirection((eDir)((rand() % 3) + 4));
            if (ballx == player2x - 1 && bally == player2y + i)
                ball->changeDirection((eDir)((rand() % 3) + 1));
        }

        
        if (bally == height - 1)
            ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        if (bally == 0)
            ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        
        if (ballx == width - 1) ScoreUp(player1);
        if (ballx == 0) ScoreUp(player2);
    }

    void Run() {
        while (!quit) {
            Draw();
            Input();
            Logic();
            Sleep(12);
        }
    }
};

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;  
    info.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &info);
}


int main() {
	HideCursor();
    cGameManager c(40, 20);
    c.Run();
    return 0;
}


