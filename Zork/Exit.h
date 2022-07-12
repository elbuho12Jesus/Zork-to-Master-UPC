#pragma once
#include "Entity.h"

class Room;

class Exit : public Entity 
{
private:
	bool one_way;
	bool closed;
	bool locked;
	string opposite_name;
	Room* destination;	
	
public:
	Exit(std::string name, std::string description, std::string opposite_name, Room* origin, Room* destination, bool one_way);
	~Exit();
	void Look() const override;

	const string& GetNameFrom(const Room* room) const;
	Room* GetDestinationFrom(const Room* room) const;
	bool getLocked(){return locked;}
	void setLocked(bool state) { locked = state; };
	Entity* key;
};