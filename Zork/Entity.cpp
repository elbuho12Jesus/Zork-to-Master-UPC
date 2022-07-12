#include "pch.h"
#include "Entity.h"
#include "utility/GlobalFunctions.h"

// TODO Entity
Entity::Entity(string name,string description, Type type, Entity* parent)
	:name(name),description(description),type(type),parent(parent)
{
	if (parent != NULL)
		parent->contains.push_back(this);
}

Entity::~Entity()
{	
	contains.clear();
}

// describe the object
void Entity::Look() const
{
	cout << name << "\n";
	cout << description << "\n";
}
// assign a new parent and delete the old one
void Entity::ChangeParentTo(Entity* new_parent)
{
	if (parent != NULL)
		parent->contains.remove(this);

	parent = new_parent;

	if (parent != NULL)
		parent->contains.push_back(this);
}
// returns true if the object is in the container
bool Entity::Exists(Entity* entity) const
{
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.cend(); ++it)
	{
		if ((*it) == entity)
			return true;
	}

	return false;
}
// search the container by type but only returns the first one that matches
Entity* Entity::Find(Type type) const
{
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.cend(); ++it)
	{
		if ((*it)->type == type)
			return *it;
	}

	return NULL;
}
// search the container by type and name
Entity* Entity::Find(const string name, Type type) const
{
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.cend(); ++it)
	{
		if ((*it)->type == type)
		{
			if (GlobalFunctions::SameText((*it)->name, name))
				return *it;
		}
	}

	return NULL;
}
// search the container by type
void Entity::FindAll(Type type, list<Entity*>& list_to_fill) const
{
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.cend(); ++it)
	{
		if ((*it)->type == type)
			list_to_fill.push_back(*it);
	}
}