#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <string>
#include <sstream>

using namespace std;

float barX = 200, barY = 465, barWidth = 80, barheight = 5;
float ballX = 235, ballY = 430, ballWH = 10, ballVelX = 0.4, ballVelY = 0.4;
const int brickAmount = 100;
int score = 0, chances = 3, previousScore = 0, highestScore = 0;
bool flag = true, flag2 = true;
int currentLevel = 1;
const int maxLevels = 3;
int bricksPerLevel[maxLevels] = {30, 60, 100};
float ballSpeedMultiplier[maxLevels] = {1.0, 1.5, 2.0};

struct bricks {
    float x;
    float y;
    float width;
    float height;
    bool isAlive = true;
};
bricks bricksArray[brickAmount];

void createBricks() {
    float brickX = 41, brickY = 50;
    int bricksToCreate = bricksPerLevel[currentLevel - 1];
    for (int i = 0; i < bricksToCreate; i++) {
        if (brickX > 400) {
            brickX = 41;
            brickY += 11;
        }
        bricksArray[i].x = brickX;
        bricksArray[i].y = brickY;
        bricksArray[i].width = 38.66;
        bricksArray[i].height = 10;
        bricksArray[i].isAlive = true;
        brickX += 39.66;
    }
}

void renderBricks() {
    int bricksToRender = bricksPerLevel[currentLevel - 1];
    glBegin(GL_QUADS);
    for (int i = 0; i < bricksToRender; i++) {
        if (bricksArray[i].isAlive) {
            if (currentLevel == 1) {
                glColor3ub(0, 255, 0); // Green bricks for level 1
            } else if (currentLevel == 2) {
                glColor3ub(255, 255, 0); // Yellow bricks for level 2
            } else if (currentLevel == 3) {
                glColor3ub(255, 0, 0); // Red bricks for level 3
            }
            glVertex2f(bricksArray[i].x, bricksArray[i].y);
            glVertex2f(bricksArray[i].x + bricksArray[i].width, bricksArray[i].y);
            glVertex2f(bricksArray[i].x + bricksArray[i].width, bricksArray[i].y + bricksArray[i].height);
            glVertex2f(bricksArray[i].x, bricksArray[i].y + bricksArray[i].height);
        }
    }
    glEnd();
}

void print(int a) {
    glColor3ub(255, 255, 255);
    glRasterPos2f(490, 40);
    stringstream ss;
    ss << a;
    string s = "Score: " + ss.str();
    int len = s.length();
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }
    glRasterPos2f(490, 70);
    stringstream ss2;
    ss2 << chances;
    string chance = "Chances left: " + ss2.str();
    for (int i = 0; i < chance.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, chance[i]);
    }
    glRasterPos2f(490, 100);
    stringstream ss3;
    ss3 << previousScore;
    string prevScore = "Previous score: " + ss3.str();
    for (int i = 0; i < prevScore.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, prevScore[i]);
    }
    glRasterPos2f(490, 130);
    stringstream ss4;
    ss4 << highestScore;
    string highScore = "Highest score: " + ss4.str();
    for (int i = 0; i < highScore.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, highScore[i]);
    }
    glRasterPos2f(490, 160);
    stringstream ss5;
    ss5 << currentLevel;
    string level = "Level: " + ss5.str();
    for (int i = 0; i < level.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, level[i]);
    }
}

void message(bool a) {
    if (a == false) {
        glColor3ub(255, 255, 255);
        glRasterPos2f(20, 400);
        stringstream ss;
        ss << previousScore;
        string s = "Game over. Your score: " + ss.str() + ". Click to start new game.";
        int len = s.length();
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        }
    }
}

void completeMessage(bool a) {
    if (a == false) {
        glColor3ub(255, 255, 255);
        glRasterPos2f(20, 400);
        stringstream ss;
        ss << score;
        string s = "STAGE COMPLETE. Your score: " + ss.str() + ". Click to start new game.";
        int len = s.length();
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
        }
    }
}

void congratulatoryMessage() {
    glColor3ub(255, 255, 0);
    glRasterPos2f(20, 400);
    string s = "Congratulations! You have successfully completed all the levels.";
    int len = s.length();
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    // Bar
    glBegin(GL_QUADS);
    glColor3ub(0, 128, 255); // Blue bar
    glVertex2f(barX, barY);
    glVertex2f(barX + barWidth, barY);
    glVertex2f(barX + barWidth, barY + barheight);
    glVertex2f(barX, barY + barheight);
    glEnd();

    // Ball
    glBegin(GL_QUADS);
    glColor3ub(255, 0, 128); // Pink ball
    glVertex2f(ballX, ballY);
    glVertex2f(ballX + ballWH, ballY);
    glVertex2f(ballX + ballWH, ballY + ballWH);
    glVertex2f(ballX, ballY + ballWH);
    glEnd();

    // Sidebar
    glBegin(GL_QUADS);
    glColor3ub(64, 64, 64); // Dark gray sidebar
    glVertex2f(480, 0);
    glVertex2f(480, 480);
    glVertex2f(485, 480);
    glVertex2f(485, 0);
    glEnd();

    // Render bricks
    renderBricks();

    // Display score, chances, and other information
    print(score);
    message(flag);
    completeMessage(flag2);

    if (currentLevel > maxLevels) {
        congratulatoryMessage();
    }

    glutSwapBuffers();
}

void myInit(void) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark background
    glColor3f(0.0f, 0.0f, 0.0f);
    glViewport(0, 0, 760, 480);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 760.0, 480.0, 0.0);
}

bool checkCollision(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH) {
    if (aY + aH < bY)
        return false;
    else if (aY > bY + bH)
        return false;
    else if (aX + aW < bX)
        return false;
    else if (aX > bX + bW)
        return false;
    else
        return true;
}

void moveBall() {
    int bricksToCheck = bricksPerLevel[currentLevel - 1];
    bool allBricksBroken = true;
    for (int i = 0; i < bricksToCheck; i++) {
        if (bricksArray[i].isAlive) {
            allBricksBroken = false;
            break;
        }
    }

    if (allBricksBroken) {
        if (currentLevel < maxLevels) {
            currentLevel++;
            ballVelX *= ballSpeedMultiplier[currentLevel - 1];
            ballVelY *= ballSpeedMultiplier[currentLevel - 1];
            createBricks();
        } else {
            currentLevel++;
            ballVelX = 0;
            ballVelY = 0;
            congratulatoryMessage();
            glutPostRedisplay();
            return;
        }
    }

    ballX += ballVelX;
    for (int i = 0; i < bricksToCheck; i++) {
        if (bricksArray[i].isAlive == true) {
            if (checkCollision(ballX, ballY, ballWH, ballWH, bricksArray[i].x, bricksArray[i].y, bricksArray[i].width, bricksArray[i].height) == true) {
                ballVelX = -ballVelX;
                bricksArray[i].isAlive = false;
                score += 10;
                break;
            }
        }
    }
    ballY -= ballVelY;
    for (int i = 0; i < bricksToCheck; i++) {
        if (bricksArray[i].isAlive == true) {
            if (checkCollision(ballX, ballY, ballWH, ballWH, bricksArray[i].x, bricksArray[i].y, bricksArray[i].width, bricksArray[i].height) == true) {
                ballVelY = -ballVelY;
                bricksArray[i].isAlive = false;
                score += 10;
                break;
            }
        }
    }
    if (ballX < 0) {
        ballVelX = -ballVelX;
    } else if (ballX + ballWH > 480) {
        ballVelX = -ballVelX;
    }
    if (ballY < 0) {
        ballVelY = -ballVelY;
    } else if (ballY + ballWH > 480) {
        if (chances <= 1) {
            // Redirect to previous level
            if (currentLevel > 1) {
                currentLevel--;
                ballVelX = 0.4 * ballSpeedMultiplier[currentLevel - 1];
                ballVelY = 0.4 * ballSpeedMultiplier[currentLevel - 1];
                createBricks();
            } else {
                // Reset game if already at level 1
                barX = 200;
                barY = 465;
                ballX = 235;
                ballY = 430;
                ballVelX = 0;
                ballVelY = 0;
                previousScore = score;
                if (highestScore < score) {
                    highestScore = score;
                }
                chances = 3;
                score = 0;
                flag = false;
                Sleep(1000);
                message(flag);
            }
        } else {
            chances--; // Decrease chances
            ballX = 235;
            ballY = 430;
            if (ballVelY < 0) {
                ballVelY = -ballVelY;
            }
            Sleep(1000);
        }
    }
    if (checkCollision(ballX, ballY, ballWH, ballWH, barX, barY, barWidth, barheight) == true) {
        ballVelY = -ballVelY;
    }
    glutPostRedisplay();
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            barX -= 50;
            if (barX < 0) {
                barX = 0;
            }
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            barX += 50;
            if (barX + barWidth > 480) {
                barX = 480 - barWidth;
            }
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                flag = true;
                if (ballVelX <= 0 && ballVelY <= 0) {
                    ballVelX = 0.3;
                    ballVelY = 0.3;
                }
                glutIdleFunc(moveBall);
            }
            break;
        default:
            break;
    }
}

void motion(int x, int y) {
    float mouseX = static_cast<float>(x) / glutGet(GLUT_WINDOW_WIDTH);
    float mouseY = static_cast<float>(y) / glutGet(GLUT_WINDOW_HEIGHT);

    float newBarX = mouseX * (480 - barWidth);
    if (newBarX < 0) {
        barX = 0;
    } else if (newBarX + barWidth > 480) {
        barX = 480 - barWidth;
    } else {
        barX = newBarX;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(760, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Brick Breaker By Showrin,Ohee,Adnan");
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(keyboard);
    glutPassiveMotionFunc(motion);
    glutMouseFunc(mouse);

    createBricks();

    myInit();
    glutMainLoop();
}
