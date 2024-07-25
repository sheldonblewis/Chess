#include "player.h"

Player::Player(char color) : color(color) {}

char Player::getColor() const {
    return color;
}
