#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameEngine.h"

class State
{
public:
	virtual void Init(GameEngine* game) = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(GameEngine* game) = 0;
	virtual void Update(GameEngine* game) = 0;
	virtual void Draw(GameEngine* game) = 0;

	void ChangeState(GameEngine* game, State* state) {
		game->ChangeState(state);
	}

protected:
	State() { }
};

#endif
