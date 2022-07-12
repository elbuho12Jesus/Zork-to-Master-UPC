#pragma once
#include "Entity.h"
class Exit;

class Room :public Entity
{
private:
	
public:	
	Room(std::string name, std::string description, Entity* parent);
	~Room();
	void Look() const override;

	Exit* GetExit(const string& direction) const;
};