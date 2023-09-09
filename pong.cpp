//
// Created by Michael Reyes on 8/28/23.
//

#include "pong.hpp"

float moveWithKey(float axis, float speed, KeyboardKey add, KeyboardKey sub){
    if(IsKeyDown(add)){
        axis += speed;
    }
    if(IsKeyDown(sub)) {
        axis -= speed;
    }
    return axis;
}

float edgeCollisionCheck(float axisPos, float oldAxisPos, int screenAxisLength, int spriteAxisLength, bool returnOldPos){
    if(axisPos < 0 || axisPos + (float)spriteAxisLength > (float)screenAxisLength){
        if(returnOldPos){
            return oldAxisPos;
        }
        else{
            return -1;
        }
    }
    else{
        return axisPos;
    }
}

void ballResetPos(pongBall* ballAddress){
    ballAddress->posX = 315.0f;
    ballAddress->posY = 235.0f;
    SetRandomSeed((int)GetTime());
    if(GetRandomValue(0, 1) == 0){
        ballAddress->movX = -1.0f;
    }
    else{
        ballAddress->movX = 1.0f;
    }
    ballAddress->movY = 0.0f;
}

bool checkCollision(pongBall ball, pongPaddle paddle){
    if(ball.posX + ball.movX + (float)ball.width > paddle.posX && ball.posX + ball.movX < paddle.posX + (float)paddle.width && ball.posY + ball.movY + (float)ball.height > paddle.posY && ball.posY + ball.movY < paddle.posY + (float)paddle.height){
        return true;
    }
    else{
        return false;
    }
}

void pongAI(pongBall* ballAddress, pongPaddle* paddleAddress){
    if(ballAddress->movY < 0.0f && paddleAddress->posY + 35.0f > ballAddress->posY || paddleAddress->posY + 35.0f > ballAddress->posY){
        paddleAddress->movY = -1.0f;
    }
    else if(ballAddress->movY > 0.0f && paddleAddress->posY + 65.0f < ballAddress->posY || paddleAddress->posY + 65.0f < ballAddress->posY){
        paddleAddress->movY = 1.0f;
    }
    else{
        paddleAddress->movY = 0.0f;
    }
}