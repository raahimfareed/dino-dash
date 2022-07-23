#pragma once
#include <vector>
#include <SDL2/SDL.h>

#include "Entity.hpp"

struct Player: public Entity {
public:
    Player(SDL_Texture* texture);
    void jump();
    bool isJumping() const;
    void setJumping(bool jump);
    bool onGround(std::vector<Entity> grounds);
    void setYVelocity(float y);
    float getYVelocity() const;
    void update(float deltaTime);
    void reset();

    unsigned int getScore() const;

private:
    float yVelocity;
    bool jumping;
    std::uint64_t score;
};
