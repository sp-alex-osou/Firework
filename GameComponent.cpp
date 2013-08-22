#include "GameComponent.h"
#include "Game.h"

GameComponent::GameComponent(Game& game) : game(game), window(game.getDisplayWindow()) {}
GameComponent::~GameComponent() {}