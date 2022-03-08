#include "Command.h"

Command::Command(Action fn, Game::CategoryType category)
{
	this->action = fn;
	this->category = category;
}
