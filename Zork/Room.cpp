#include "pch.h"
#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "Creature.h"
#include "utility/GlobalFunctions.h"

Room::Room(string name, string description, Entity* parent=NULL)
:Entity(name,description, Type::ROOM , parent)
{

}

Room::~Room()
{
}

// describe the object
void Room::Look() const
{
	cout << "\n" << name << "\n";
	cout << description;

	// List exits 
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.cend(); ++it)
	{
		if ((*it)->getType() == Type::EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (ex->GetNameFrom(this)!="none") {
				cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->name;
			}			
		}
	}

	// List items 
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.cend(); ++it)
	{
		if ((*it)->getType() == Type::ITEM)
		{
			Item* item = (Item*)*it;
			cout << "\nThere is an item here: " << item->getName();
		}
	}

	// List creatures 
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.cend(); ++it)
	{
		if ((*it)->getType() == Type::CREATURE)
		{
			Creature* cr = (Creature*)*it;
			cout << "\nThere is someone else here: " << cr->getName();
			if (cr->IsAlive() == false && cr->die)
				cout << " (dead)";
			if (cr->IsAlive() == false && !cr->die)
				cout << " (stun)";
		}
	}

	cout << "\n";
}
// returns the first output that matches the entered name
Exit* Room::GetExit(const string& direction) const
{
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.cend(); ++it)
	{
		if ((*it)->getType() == Type::EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (GlobalFunctions::SameText(ex->GetNameFrom(this), direction))
				return ex;
		}
	}

	return NULL;
}