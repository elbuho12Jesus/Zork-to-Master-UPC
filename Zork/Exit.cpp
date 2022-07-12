#include "pch.h"
#include "Exit.h"
#include "Room.h"

Exit::Exit(string name, string description, string opposite_name, Room* origin, Room* destination, bool one_way=false)
	:Entity(name, description, Type::EXIT,(Entity*)origin),
	closed(false), locked(false), key(NULL), one_way(one_way), destination(destination), opposite_name(opposite_name)
{
	if (one_way == false)
	{		
		destination->contains.push_back(this);
	}		
}

Exit::~Exit()
{	
}
// describe the object
void Exit::Look() const
{
	cout << name << " to " << opposite_name << "\n";
	cout << description << "\n";
}
// returns the name of the object Exit according to the current parent
const string& Exit::GetNameFrom(const Room* room) const
{
	if (room == parent)
		return name;
	if (room == destination)
		return opposite_name;

	return name; 
}
// returns the object Room according to the current parent and object Exit
Room* Exit::GetDestinationFrom(const Room* room) const
{
	if (room == parent)
		return destination;
	if (room == destination && one_way==false)
		return (Room*)parent;

	return NULL;
}