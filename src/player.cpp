#include <numbers>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>

#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "Player.hpp"
#include "Config.hpp"
#include "Math.hpp"

Player::Player(SDL_Texture* texture)
    : Entity(texture, {0, 0, 32, 32}, vector2<float>((Config::width / 2) - 16, (Config::height - 256 - 32))), yVelocity(0.f), jumping(false), score(SDL_GetTicks64())
{}

void Player::jump() {
    jumping = true;
    setYVelocity(-1.25f);
}

bool Player::isJumping() const {
    return jumping;
}

void Player::setJumping(bool jump) {
    jumping = jump;
}

// FIX: Doesn't work, I guess? More testing needed!
// Update: Kinda works now, but unsure if correct or not
bool Player::onGround(std::vector<Entity> grounds) {
    for (auto &e: grounds) {
        if (position.getY() + src.h - e.getPosition().getY() > 0.01f) {
            return false;
        }
    }

    return true;
}

void Player::setYVelocity(float y) {
    yVelocity = y;
}

float Player::getYVelocity() const {
    return yVelocity;
}

void Player::update(float deltaTime) {
    if (getYVelocity()) {
        if (getPosition().getY() + getYVelocity() <= Config::height - 256 - 32) {
            setY(getPosition().getY() + getYVelocity());
            setYVelocity(getYVelocity() + Config::gravity * deltaTime);
        } else {
            setYVelocity(0);
            setJumping(false);
        }
    } else {
        setJumping(false);
    }
}

void Player::reset() {
    setYVelocity(0.f);
    setJumping(false);
    setPosition(vector2<float>((Config::width / 2) - 16, (Config::height - 256 - 32)));
    score = SDL_GetTicks64();
}

unsigned int Player::getScore() const {
    return (SDL_GetTicks64() - score) / 1000;
}

