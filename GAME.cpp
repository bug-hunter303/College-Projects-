#include<iostream>
#include<raylib.h>

using namespace std;



Color Green = Color{38,185,154,255};
Color Dark_Green = Color{20,160,133,255};
Color Light_Green = Color{129,204,184,255};
Color Yellow = Color{243,213,91,255};

int playerScore = 0 , cpuScore = 0;

class Ball{
        public:
        float x,y;
        int radius;
        int speedX,speedY;
       
    void Draw(){                                                                 //drawing the ball ( moving motion and stuffs )
         DrawCircle(x, y,radius, Yellow );         //making the ball
    }

    void Update(){
        x += speedX; //they increase the x and y direction of the ball by 7 pixels , 7 bcuz tala ball.speedx
        y += speedY;

        if ( y + radius >= GetScreenHeight() || y - radius <= 0){ // the ball doesnt go out of the screen but rebounds inside the window 
            speedY *= -1;
        }
        if(x+radius >= GetScreenWidth()) //cpu wins
        {
            cpuScore++;
            ResetBall();
        }
        if(x-radius <= 0)
        {
            playerScore++;
            ResetBall();
        }
    }

    void ResetBall()
    {
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speed_choices[2] = {-1,1};
        speedX *= speed_choices[GetRandomValue(0,1)];
        speedY *= speed_choices[GetRandomValue(0,1)];
    }
};

class Paddle{
    protected: // yo tala chai , the code makes the paddle not to go out of the game window 
        void LimitMovement() 
        {
             if(y <= 0){
            y=0;
        }
        if(y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
        }
    public:
    float x,y;
    float width,height;
    int speed;

    void Draw(){
         DrawRectangleRounded(Rectangle{x,y,width,height},0.8, 0, WHITE);   //making paddle  , right side wala ( we control this )
    }
    void Update(){  // moving the paddle 
        if(IsKeyDown(KEY_UP)){
            y = y-speed;
        }
        if(IsKeyDown(KEY_DOWN)){
            y = y+speed;
        }
        // yo tala chai , the code makes the paddle not to go out of the game window 
        LimitMovement();
    }
};

class CpuPaddle : public Paddle{  //inheritance use garera ball ra cpu bich aafai move garako
    public:

    void Update(int ball_y){
        if(y+height/2 > ball_y)
        {
            y = y - speed;
        }
        if(y + height/2 <= ball_y){
            y = y + speed;
        }
        LimitMovement();
    }

};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main(){
    

    cout<<"Starting the Game"<<endl;

    const int screen_width= 1280;                                       //making the resolution for the game
    const int screen_height= 800;
   

    InitWindow(screen_width,screen_height,"My Pong Gamee !");

    SetTargetFPS(60);                                                   //frame per sec matching for all computer resolution 
    
    //moves the ball
    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speedX = 7;
    ball.speedY = 7;

    //player paddle 
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width -10;
    player.y = screen_height/2 - player.height/2;
    player.speed = 6;

    //cpu paddle
    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height/2 - cpu.height/2;
    cpu.speed = 6;

    while (WindowShouldClose()==false)                                 //gameloop window
    {
        BeginDrawing();                                         //starts the window and everything is displayed here 

        //updating
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        //checking for collisions
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player.x,player.y,player.width,player.height}))
        {
            ball.speedX *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cpu.x,cpu.y,cpu.width,cpu.height}))
        {
            ball.speedX *= -1;
        }

        //drawing
        ClearBackground(Dark_Green);
        DrawRectangle(screen_width/2,0,screen_width/2,screen_height,Green);
        DrawLine(screen_width/2,0,screen_width/2, screen_height,WHITE); 
        DrawCircle(screen_width/2,screen_height/2,150,Light_Green);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i",cpuScore), screen_width/4 - 20,20,80,WHITE);  // displaying scores
        DrawText(TextFormat("%i",playerScore), 3 * screen_width/4 - 20,20,80,WHITE);

        EndDrawing();                                                          //ends the window and everything gets destroyed here 
    }
    

    CloseWindow();
}
