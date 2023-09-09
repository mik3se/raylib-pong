#include "pong.hpp"

int main() {
    const int screenWidth = 640;
    const int screenHeight = 480;

    int stuckCounter = 0;

    float frameRate;
    float deltaTime;
    float speed = 0.5f;
    double speedDivisor;

    bool ballInMotion = false;

    pongPaddle player1 = pongPaddle();
    pongPaddle player2 = pongPaddle();
    pongBall ball = pongBall();

    player1 = {10, 190, 10, 100, 0};
    player2 = {screenWidth - 20, 190, 10, 100, 0};
    ball = {315, 235, 10, 10, 0, 0};

    SetTraceLogLevel(LOG_ERROR);
    InitWindow(screenWidth, screenHeight, "pong - window");
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    while(!WindowShouldClose()){
        //Update
        deltaTime = GetFrameTime() * 1000.0f;
        frameRate = 1.0f/GetFrameTime();

        if(IsKeyPressed(KEY_SPACE)){
            if(!ballInMotion){
                ballInMotion = true;
                ballResetPos(&ball);
            }
            else{ballInMotion = false;}
        }

        if(edgeCollisionCheck(ball.movX + ball.posX, ball.posX, GetScreenWidth(), ball.width, false) == -1){ballResetPos(&ball);}
        else if(edgeCollisionCheck(ball.movY + ball.posY, ball.posY, GetScreenHeight(), ball.height, false) == -1 && stuckCounter < 5){
            ball.movY *= -1.0f;
            stuckCounter++;
        }
        else if(stuckCounter < 5 && (checkCollision(ball, player1) || checkCollision(ball, player2)) && edgeCollisionCheck(ball.movX + ball.posX, ball.posX, GetScreenWidth(), ball.width, false) != -1){
            if(checkCollision(ball, player1)){
                ball.movY = (ball.posY + (float)ball.height / 2.0f - player1.posY - (float)player1.height / 2.0f) / 50.0f;
            }
            else if(checkCollision(ball, player2)){
                ball.movY = (ball.posY + (float)ball.height / 2.0f - player2.posY - (float)player2.height / 2.0f) / 50.0f;
            }
            if(stuckCounter == 0){
                ball.movX *= -1.0f;
            }
            stuckCounter++;
            speedDivisor = sqrt(pow(ball.movX, 2) + pow(ball.movY, 2));
            ball.movX = (float)((double)ball.movX / speedDivisor);
            ball.movY = (float)((double)ball.movY / speedDivisor);
        }
        else if(ballInMotion || stuckCounter > 5){ball.posX += ball.movX * speed * deltaTime; ball.posY += ball.movY * speed * deltaTime; if(stuckCounter > 0){stuckCounter -= 1;}}

        //pongAI(&ball, &player1);
        pongAI(&ball, &player2);

        player1.posY = edgeCollisionCheck(moveWithKey(player1.posY, speed * deltaTime * 1.75f, KEY_S, KEY_W), player1.posY, GetScreenHeight(), player1.height, true);
        //player1.posY = edgeCollisionCheck(player1.posY + player1.movY * speed * deltaTime * 1.75f, player1.posY, GetScreenHeight(), player1.height, true);
        //player2.posY = edgeCollisionCheck(moveWithKey(player2.posY, speed * deltaTime * 1.75f, KEY_K, KEY_I), player2.posY, GetScreenHeight(), player2.height, true);
        player2.posY = edgeCollisionCheck(player2.posY + player2.movY * speed * deltaTime * 1.75f, player2.posY, GetScreenHeight(), player2.height, true);

        //Draw
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText(TextFormat("%d fps", (int)frameRate), 20, 10, 20, WHITE);
        DrawRectangle((int)player1.posX, (int)player1.posY, player1.width, player1.height, WHITE);
        DrawRectangle((int)player2.posX, (int)player2.posY, player2.width, player2.height, WHITE);
        DrawRectangle((int)ball.posX, (int)ball.posY, ball.width, ball.height, WHITE);

        EndDrawing();
    }

    return 0;
}
