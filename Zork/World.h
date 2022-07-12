#pragma once
#include <list>
#include <string>
class Entity;
class Player;


class World {
public:
	World();
	~World() {};	
	bool findText(std::list<std::string> sentence);
	bool state;
private:
	list<Entity*> worlds;
	Player* player;
};

