#include "../include/movement_engine.h"
#include "raymath.h"
#include <math.h>
#include <iostream>

void ToggleGrounded(PlayerData* player) {
    if (player->grounded) {
        player->startTimeUngrounded = GetTime();
        player->grounded = false;
        return;
    }
    player->grounded = true;
    player->startTimeUngrounded = -1.0f;
    player->lastValid = player->pos;
}

void MovePlayer(PlayerData* player, const std::vector<std::vector<int> >& mask) {
    Vector2 vel = { float(IsKeyDown(KEY_D)-IsKeyDown(KEY_A))*player->speed };
    if (IsKeyDown(KEY_SPACE) && player->grounded) { 
        vel.y = 5;
    }
    player->velocity.x += vel.x;
    player->velocity.y += vel.y;
    if (!IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
        player->velocity.x = 0;
    }
    if (!IsKeyDown(KEY_SPACE) && player->grounded) {
        player->velocity.y = 0;
    }

    // X velocity change
    player->velocity = Vector2Clamp(player->velocity, player->velocityMin, player->velocityMax); //GetFrameTime()
    if (!player->grounded)
        player->pos.x += 0.5 * player->velocity.x * GetFrameTime();
    else
        player->pos.x += player->velocity.x * GetFrameTime();

    // make player grounded or ungrounded based on falling
    // currently will be buggy because if the player goes beyond bounds shit will be fucked
    if (!player->grounded && CheckGrounded(player, mask)) {
        ToggleGrounded(player);
    }
    if (player->grounded && !CheckGrounded(player, mask)) {
        ToggleGrounded(player);
    }

    // Y velocity
    if (player->velocity.y>0 && player->grounded) {
        ToggleGrounded(player);
    }
    if (!player->grounded) {
        player->velocity.y += G * GetFrameTime();
        player->pos.y -= player->velocity.y * GetFrameTime();   // y' = ∆y = v + a*t --> y = y_prev + ∆y
    }

    // check if grounded & reset state if needed
    // See diagram for how this works
    if (!ValidSpace(player, mask)) {
        player->pos = LastValidPosition(player, mask);
    }

}

void DrawPlayer(PlayerData* player) {
    DrawRectangle(player->x, player->y, 1, 1, SKYBLUE);
}


bool CheckGrounded(PlayerData* player, const std::vector<std::vector<int> >& mask) {
    if (mask[player->x][player->y+1])
        return true;
    return false;
}

bool ValidSpace(PlayerData* player, const std::vector<std::vector<int> >& mask) {
    player->x = floor(player->pos.x);
    player->y = floor(player->pos.y);
    if (player->x > mask.size()-1 || player->y > mask[0].size()-1)
        return false;
    if (!mask[player->x][player->y])
        return true;
    return false;
}

// lets go horrible recursion
Vector2 LastValidPosition(PlayerData* player, const std::vector<std::vector<int> >& mask) {
    if (player->pos.x > mask.size()-1) player->pos.x = (float)mask.size()-1.5f;
    if (player->pos.y > mask[0].size()-1) player->pos.y = (float)mask[0].size()-1.5f;
	if (ValidSpace(player, mask)) {
		return Vector2{(float)player->x + 0.5f, (float)player->y + 0.5f};
	}
	// determine where to check based on velocity strength
    Vector2 vel = Vector2Normalize(player->velocity);
    vel.x *= 0.5f;
    vel.y *= 0.5f;

    // based on this, recurse until the position is valid
    // how to do ... the thing with.......... acceleration :(
    player->pos.x -= vel.x;
    player->pos.y -= vel.y + G * GetFrameTime();
    return LastValidPosition(player, mask);
}