#include "../include/size_change_engine.h"
#include "raymath.h"
#include <iostream>


void LerpSizeOnVelocity(PlayerData* player, WindowInfo* window, MonitorInfo* monitor) {
    Vector2 curr_screen = (Vector2) {(float)GetScreenWidth(), (float)GetScreenHeight()};
    float vel_y = fabs(player->velocity.y);
    if (!vel_y) vel_y = 1.0f;

    if (player->velocity.y < -10) {
        // figure out screen size to set to 
        // negative velocity is downwards :)
        curr_screen.x -= vel_y*GetFrameTime();
        //std::cout << curr_screen.x << "\n";
        curr_screen.x = floor(curr_screen.x);

        curr_screen = Vector2Clamp(curr_screen, window->minSize, window->maxSize);

        ChangeScreenSize(monitor, (int)curr_screen.x, (int)curr_screen.y);
        return;
    }
    // STRETCH BACK TO NORMAL SIZE IN HERE
    if (!player->velocity.y/* && curr_screen.x < window->avgSize.x*/) {
        //curr_screen.x *= 1.25*GetFrameTime();
        ChangeScreenSize(monitor, (int)window->avgSize.x, (int)window->avgSize.y);
    }
}



/**
 * changes the screen size of the game around the center
 * 
 * pos_x and pos_y are where the point is ON the screen
 * new_width and new_height is the screen's new width and height respectively
 */
void ChangeScreenSize(MonitorInfo* monitor, int new_width, int new_height) 
{
    ///*
    if (GetMonitorWidth(monitor->monitor_id) != monitor->monitor_width) 
    {
        monitor->monitor_width = GetMonitorWidth(monitor->monitor_id);
        monitor->monitor_height = GetMonitorHeight(monitor->monitor_id);
    }
    //*/
   SetWindowPosition((monitor->monitor_width - new_width)/2, (monitor->monitor_height - new_height)/2);
   SetWindowSize(new_width, new_height);

}