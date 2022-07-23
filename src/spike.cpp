#include <random>
#include <SDL2/SDL.h>

#include "Config.hpp"
#include "Math.hpp"
#include "Entity.hpp"
#include "Spike.hpp"

float Spike::xVelocity = 0.5f;

Entity Spike::create(SDL_Texture* texture, SDL_Rect src, vector2<float> position)
{
    return Entity(texture, src, position);
}

void Spike::spawn(std::vector<Entity>& spikes, SDL_Texture* texture) {
    auto last = spikes[spikes.size() - 1];
    if (last.getPosition().getX() < Config::width - (Config::width / (float) random())) {
        switch (random()) {
            case 1:
                spikes.push_back(create(texture, { 0, 0, 16, 8 }, vector2<float>(Config::width, Config::height - 256 - 8)));
                break;
            case 2:
                spikes.push_back(create(texture, { 0, 0, 16, 8 }, vector2<float>(Config::width, Config::height - 256 - 8)));
                spikes.push_back(create(texture, { 0, 0, 16, 8 }, vector2<float>(Config::width + 16, Config::height - 256 - 8)));
                break;
            case 3:
                spikes.push_back(create(texture, { 0, 0, 16, 8 }, vector2<float>(Config::width, Config::height - 256 - 8)));
                spikes.push_back(create(texture, { 0, 0, 16, 8 }, vector2<float>(Config::width + 16, Config::height - 256 - 8)));
                spikes.push_back(create(texture, { 0, 0, 16, 8 }, vector2<float>(Config::width + 32, Config::height - 256 - 8)));
                break;
            case 4:
                spikes.push_back(create(texture, { 0, 0, 16, 8 }, vector2<float>(Config::width, Config::height - 256 - 8)));
                spikes.push_back(create(texture, { 0, 0, 16, 8 }, vector2<float>(Config::width + 16, Config::height - 256 - 8)));
                spikes.push_back(create(texture, { 0, 0, 16, 8 }, vector2<float>(Config::width + 32, Config::height - 256 - 8)));
                spikes.push_back(create(texture, { 0, 0, 16, 8 }, vector2<float>(Config::width + 48, Config::height - 256 - 8)));
                break;
        }
    }
}

void Spike::update(std::vector<Entity>& spikes, float deltaTime) {
    for (auto& spike: spikes) {
        spike.setX(spike.getPosition().getX() - Spike::xVelocity);
    }
    xVelocity += 0.00001f * deltaTime;
}

// O(n), but it's not that bad.
// I'm not sure if this is the best way to do it, but it works.
void Spike::remove(std::vector<Entity>& spikes) {
    std::vector<unsigned int> indices;
    for (size_t i = 0; i < spikes.size(); i++) {
        if (spikes[i].getPosition().getX() + spikes[i].getSrc().w < 0) {
            indices.push_back(i);
        }
    }
    
    for (const auto& index: indices) {
        spikes.erase(spikes.begin() + index);
    }
}

unsigned int Spike::random() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,4); // distribution in range [1, 4]

    return dist6(rng);
}


bool Spike::isColliding(Entity& entity, std::vector<Entity>& spikes) {
       for (auto& spike: spikes) {
            if (entity.getPosition().getX() + entity.getSrc().w > spike.getPosition().getX() &&
                entity.getPosition().getX() < spike.getPosition().getX() + spike.getSrc().w &&
                entity.getPosition().getY() + entity.getSrc().h > spike.getPosition().getY() &&
                entity.getPosition().getY() < spike.getPosition().getY() + spike.getSrc().h) {
                return true;
            }
        }
        return false;
}

void Spike::reset(std::vector<Entity>& spikes) {
    xVelocity = 0.5f;
    spikes.clear();
}

