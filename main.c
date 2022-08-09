#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>

#include <raylib.h>

typedef struct Position{
    float x;
    float y;
} posi;

typedef struct Motor{
   Vector2 position;
   Vector2 initial;
} motor;


int main(void){
    lua_State* L;
    L = luaL_newstate();
    luaL_openlibs(L);
    
    luaL_dofile(L, "ini.lua");
    luaL_dofile(L, "cell.lua");
    lua_getglobal(L, "wiwd");
    lua_getglobal(L, "wihg");


    const int ScWd = (int)lua_tointeger(L, -2);
    const int ScHg = (int)lua_tointeger(L, -1);

    InitWindow(ScWd, ScHg, "YASB");

    //cell`s statement ////////////
    motor *motors = (motor *)malloc(1000000*sizeof(motor));
    Texture2D motorCell = LoadTexture("sprites/motor.png");
    int motorCount = 0;


    
    


    SetTargetFPS(60);
    while(!WindowShouldClose()){

        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            motors[motorCount].position = GetMousePosition();
            motors[motorCount].initial = GetMousePosition();
            motorCount += 1;
        }

        for(int i = 0; i<motorCount; i++){
       
            lua_getglobal(L, "move");
             lua_pushnumber(L, motors[i].position.x);
             lua_pushnumber(L, motors[i].position.y);
             lua_pushnumber(L, motors[i].initial.x);
             lua_pushnumber(L, motors[i].initial.y);
            lua_call(L, 4 , 2);
            motors[i].position.x = (float)lua_tonumber(L, -2);
            motors[i].position.y = (float)lua_tonumber(L, -1);
            

        }
        

        BeginDrawing();
            ClearBackground(WHITE);

            for(int i = 0; i<motorCount; i++){


                 DrawTexture(motorCell, (int)motors[i].position.x, (int)motors[i].position.y, WHITE);
            }
        EndDrawing();
    }   
 


    CloseWindow();
    lua_close(L);

}

int spawnMot(motor *mot, int mc){

   
}