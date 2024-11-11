#ifndef MOVEMENT
#define MOVEMENT

#include "raylib.h"
#include <vector>

#define G -9.81
//#define G -159

struct PlayerData {
    // the actual position of the character
    Vector2 pos;

    // the int position they hold
    int x;
    int y;

    // current velocity + min and max
    Vector2 velocity;
    Vector2 velocityMax;
    Vector2 velocityMin;

    // helpful variables
    bool grounded;
    Vector2 lastValid;
    float startTimeUngrounded;
    float speed;
};

void ToggleGrounded(PlayerData* player);
void MovePlayer(PlayerData* player, const std::vector<std::vector<int> >& mask);
void DrawPlayer(PlayerData* player);
bool CheckGrounded(PlayerData* player, const std::vector<std::vector<int> >& mask);
bool ValidSpace(PlayerData* player, const std::vector<std::vector<int> >& mask);
Vector2 LastValidPosition(PlayerData* player, const std::vector<std::vector<int> >& mask);







#endif