#ifndef SIZE_ENGINE
#define SIZE_ENGINE

#include "raylib.h"
#include <stdio.h>
#include <fstream>
#include "movement_engine.h"

// Structs
struct MonitorInfo {
    int monitor_id;
    int monitor_width;
    int monitor_height;
};

struct WindowInfo {
    // make sure to clamp to floor :)
    Vector2 minSize;
    Vector2 avgSize;
    Vector2 maxSize;
};

// Need a dynamic lerp
void LerpSizeOnVelocity(PlayerData* player, WindowInfo* window, MonitorInfo* monitor);

// Function Declarations
void ChangeScreenSize(MonitorInfo* monitor, int new_width, int new_height);


#endif