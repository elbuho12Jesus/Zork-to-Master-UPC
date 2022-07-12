#pragma once
#include <string>
#include <list>

enum class Type
{
	PLAYER,
	ROOM,
	EXIT,
	CREATURE,
	NPC,
	ITEM
};

class Entity {
protected:
	Type type;
	std::string name;
	std::string description;	
public:
	Entity(std::string name, std::string description, Type type, Entity* parent);
	virtual ~Entity();
	virtual void Look() const;	

	void	ChangeParentTo(Entity* new_parent);
	bool    Exists(Entity* entity) const;
	Entity* Find(Type type) const;
	Entity* Find(const string name, Type type) const;
	void	FindAll(Type type, list<Entity*>& list_to_fill) const;
	std::string getName() { return name; }
	Type getType() { return type; }
	std::list<Entity*> contains;
	Entity* parent;
};