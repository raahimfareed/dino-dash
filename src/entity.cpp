#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"
#include "Math.hpp"


Entity::Entity(SDL_Texture* texture, SDL_Rect src, vector2<float> position)
    : texture(texture), src(src), position(position)
{}

SDL_Texture* Entity::getTexture() {
    return texture;
}

SDL_Rect Entity::getSrc() {
    return src;
}

vector2<float> Entity::getPosition() {
    return position;
}

void Entity::setPosition(float x, float y) {
    position = vector2<float>(x, y);
}

void Entity::setPosition(vector2<float> position) {
    this->position = position;
}

void Entity::setX(float x) {
    position.setX(x);
}

void Entity::setY(float y) {
    position.setY(y);
}