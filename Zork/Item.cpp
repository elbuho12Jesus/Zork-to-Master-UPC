#include "pch.h"
#include "Item.h"
#include "utility/GlobalFunctions.h"


Item::Item(string name, string description, Entity* parent, int AttackMax, int AttackMin, int defenceArmor, ItemType itemType=ItemType::COMMON)
	:Entity(name,description, Type::ITEM, parent),AttackMax(AttackMax),AttackMin(AttackMin),defenceArmor(defenceArmor), itemType(itemType)
{
	written = "";
}

Item::~Item()
{}
// describe the object
void Item::Look() const
{
	cout << "\n" << name << "\n";
	cout << description << "\n";

	list<Entity*> stuff;
	FindAll(Type::ITEM, stuff);

	if (stuff.size() > 0)
	{
		cout << "It contains: " << "\n";
		for (list<Entity*>::const_iterator it = stuff.begin(); it != stuff.cend(); ++it)
			cout << (*it)->getName() << "\n";
	}
}
// calculate item damage
int Item::GetValue() const
{
	return GlobalFunctions::Roll(AttackMin, AttackMax);
}