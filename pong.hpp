//
// Created by Michael Reyes on 8/28/23.
//

#include "raylib.h"
#include <iostream>
#include <cmath>

#ifndef PONG_PONG_HPP
#define PONG_PONG_HPP


class pong {

};

struct pongPaddle{
    float posX;
    float posY;
    int width;
    int height;
    float movY;
};

struct pongBall{
    float posX;
    float posY;
    int width;
    int height;
    float movX;
    float movY;
};

void ballResetPos(pongBall *ball);
void pongAI(pongBall* ballAddress, pongPaddle* paddleAddress);

bool checkCollision(pongBall ball, pongPaddle paddle);

float moveWithKey(float axis, float speed, KeyboardKey add, KeyboardKey sub);
float edgeCollisionCheck(float axisPos, float oldAxisPos, int screenAxisLength, int spriteAxisLength, bool returnOldPos);

#endif //PONG_PONG_HPP
