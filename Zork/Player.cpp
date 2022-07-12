#include "pch.h"
#include "Player.h"
#include "Exit.h"
#include "Room.h"
#include "Item.h"
#include "utility/GlobalFunctions.h"

Player::Player(string name, string description, Entity* parent, int life, int defence, int damageMin, int damageMax, Item* weapon, Item* armor, int lifes)
	:Creature(name ,description,parent ,life ,  defence,  damageMin,  damageMax,weapon ,armor),lifes(lifes)
{
	type = Type::PLAYER;
}
Player::~Player() {};
// describe the object
void Player::Look(const list<string>& sentence) const
{
	if (sentence.size() > 1)
	{
		for (list<Entity*>::const_iterator it = parent->contains.begin(); it != parent->contains.cend(); ++it)
		{
			if (GlobalFunctions::SameText((*it)->getName(), *next(sentence.begin())) || ((*it)->getType() == Type::EXIT && GlobalFunctions::SameText(*next(sentence.begin()), ((Exit*)(*it))->GetNameFrom((Room*)parent))))
			{
				(*it)->Look();
				return;
			}
		}

		if (GlobalFunctions::SameText(*next(sentence.begin()), "me"))
		{
			cout << "\n" << name << "\n";
			cout << description << "\n";
		}
	}
	else
	{
		parent->Look();
	}
}
// goes to an existing exit( type Exit)
bool Player::Go(const list<string>& sentence)
{
	Exit* exit = GetRoom()->GetExit(*next(sentence.begin()));

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << *next(sentence.begin()) << "'.\n";
		return false;
	}

	if (exit->getLocked())
	{
		cout << "\nThat exit is locked.\n";
		return false;
	}

	cout << "\nYou take direction " << exit->GetNameFrom((Room*)parent) << "...\n";
	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));
	parent->Look();

	return true;
}
// describes the container of a parent of a ROOM or ITEM
bool Player::Take(const list<string>& sentence)
{
	if (sentence.size() == 4)
	{
		Item* item = (Item*)parent->Find(*next(sentence.begin(),3), Type::ITEM);
				
		if (item == NULL)
			item = (Item*)Find(*next(sentence.begin(), 3), Type::ITEM);

		if (item == NULL)
		{
			cout << "\nCannot find '" << *next(sentence.begin(), 3) << "' in this room or in your inventory.\n";
			return false;
		}

		Item* subitem = (Item*)item->Find(*next(sentence.begin()), Type::ITEM);

		if (subitem == NULL)
		{
			cout << "\n" << item->getName() << " does not contain '" << *next(sentence.begin()) << "'.\n";
			return false;
		}

		cout << "\nYou take " << subitem->getName() << " from " << item->getName() << ".\n";
		subitem->ChangeParentTo(this);
	}
	else if (sentence.size() == 2)
	{
		Item* item = (Item*)parent->Find(*next(sentence.begin()), Type::ITEM);

		if (item == NULL)
		{
			cout << "\nThere is no item here with that name.\n";
			return false;
		}

		cout << "\nYou take " << item->getName() << ".\n";
		item->ChangeParentTo(this);
	}

	return false;
}
// show the elements of your container 
void Player::Inventory() const
{
	list<Entity*> items;
	FindAll(Type::ITEM, items);

	if (items.size() == 0)
	{
		cout << "\nYou do not own any item.\n";
		return;
	}

	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		if (*it == weapon)
			cout << "\n" << (*it)->getName() << " (as weapon)";
		else if (*it == armor)
			cout << "\n" << (*it)->getName() << " (as armour)";
		else
			cout << "\n" << (*it)->getName();
	}

	cout << "\n";
}
// assign a type item object from your container to the parent's container
bool Player::Drop(const list<string>& sentence)
{
	if (sentence.size() == 2)
	{
		Item* item = (Item*)Find(*next(sentence.begin()), Type::ITEM);

		if (item == NULL)
		{
			cout << "\nThere is no item on you with that name.\n";
			return false;
		}

		cout << "\nYou drop " << item->getName() << "...\n";
		item->ChangeParentTo(parent);

		return true;
	}
	else if (sentence.size() == 4)
	{
		Item* item = (Item*)Find(*next(sentence.begin()), Type::ITEM);

		if (item == NULL)
		{
			cout << "\nCan not find '" << *next(sentence.begin()) << "' in your inventory.\n";
			return false;
		}

		Item* container = (Item*)parent->Find(*next(sentence.begin(),3), Type::ITEM);

		if (container == NULL)
		{
			container = (Item*)Find(*next(sentence.begin(), 3), Type::ITEM);
			cout << "\nCan not find '" << *next(sentence.begin(), 3) << "' in your inventory or in the room.\n";
			return false;
		}

		cout << "\nYou put " << item->getName() << " into " << container->getName() << ".\n";
		item->ChangeParentTo(container);

		return true;
	}

	return false;
}
// assigns an item to the WEAPON or ARMOR object of the player
bool Player::Equip(const list<string>& sentence)
{
	Item* item = (Item*)Find(*next(sentence.begin()), Type::ITEM);

	if (item == NULL)
	{
		cout << "\nCannot find '" << *next(sentence.begin()) << "' is not in your inventory.\n";
		return false;
	}

	switch (item->itemType)
	{
	case ItemType::WEAPON:
		weapon = item;
		break;

	case ItemType::ARMOR:
		armor = item;
		break;

	default:
		cout << "\n" << item->getName() << " cannot be equipped.\n";
		return false;
	}

	cout << "\nYou equip " << item->getName() << "...\n";

	return true;
}
// unassigns an item to the WEAPON or ARMOR object of the player
bool Player::UnEquip(const list<string>& sentence)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)Find(*next(sentence.begin()), Type::ITEM);

	if (item == NULL)
	{
		cout << "\n" << item->getName() << " is not in your inventory.\n";
		return false;
	}

	if (item == weapon)
		weapon = NULL;
	else if (item == armor)
		armor = NULL;
	else
	{
		cout << "\n" << item->getName() << " is not equipped.\n";
		return false;
	}

	cout << "\nYou un-equip " << item->getName() << "...\n";

	return true;
}
// check and describe if there is a creature in the room
bool Player::Examine(const list<string>& sentence) const
{
	Creature* target = (Creature*)parent->Find(*next(sentence.begin()), Type::CREATURE);

	if (target == NULL)
	{
		cout << "\n" << *next(sentence.begin()) << " is not here.\n";
		return false;
	}

	target->Inventory();
	target->Stats();

	return true;
}
// check if there is a target to attack
bool Player::Attack(const list<string>& sentence)
{
	Creature* target = (Creature*)parent->Find(*next(sentence.begin()), Type::CREATURE);

	if (target == NULL)
	{
		cout << "\n" << *next(sentence.begin()) << " is not here.";
		return false;
	}
	if (!target->IsAlive() && !target->die)
	{
		target->Stun();
		return false;
	}
		
	if (target->die)
	{
		target->Die();
		return false;
	}

	combat_target = target;
	cout << "\nYou jump to attack " << target->getName() << "!\n";
	return true;
}
// assigns the items of the dead creature to the player
bool Player::Loot(const list<string>& sentence)
{
	Creature* target = (Creature*)parent->Find(*next(sentence.begin()), Type::CREATURE);

	if (target == NULL)
	{
		cout << "\n" << *next(sentence.begin()) << " is not here.\n";
		return false;
	}

	if (target->IsAlive() == true && !target->die)
	{
		cout << "\n" << target->getName() << " cannot be looted until it is killed.\n";
		return false;
	}

	list<Entity*> items;
	target->FindAll(Type::ITEM, items);

	if (items.size() > 0)
	{
		cout << "\nYou loot " << target->getName() << "'s corpse:\n";

		for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
		{
			Item* i = (Item*)(*it);
			cout << "You find: " << i->getName() << "\n";
			i->ChangeParentTo(this);
		}
	}
	else
		cout << "\nYou loot " << target->getName() << "'s corpse, but find nothing there.\n";

	return true;
}
// is assigned to an Exit object (lock = true)
bool Player::Lock(const list<string>& sentence)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(*next(sentence.begin()));

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << *next(sentence.begin()) << "'.\n";
		return false;
	}

	if (exit->getLocked() == true)
	{
		cout << "\nThat exit is already locked.\n";
		return false;
	}

	Item* item = (Item*)Find(*next(sentence.begin(),3), Type::ITEM);

	if (item == NULL)
	{
		cout << "\nItem '" << *next(sentence.begin(), 3) << "' not found in your inventory.\n";
		return false;
	}

	if (exit->key != item)
	{
		cout << "\nItem '" << item->getName() << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
		return false;
	}

	cout << "\nYou lock " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->setLocked(true);

	return true;
}
// is assigned to an Exit object (lock = false)
bool Player::UnLock(const list<string>& sentence)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(*next(sentence.begin()));

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << *next(sentence.begin()) << "'.\n";
		return false;
	}

	if (exit->getLocked() == false)
	{
		cout << "\nThat exit is not locked.\n";
		return false;
	}

	Item* item = (Item*)Find(*next(sentence.begin(),3), Type::ITEM);

	if (item == NULL)
	{
		cout << "\nKey '" << *next(sentence.begin(),3) << "' not found in your inventory.\n";
		return false;
	}

	if (exit->key != item)
	{
		cout << "\nKey '" << item->getName() << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
		return false;
	}

	cout << "\nYou unlock " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->setLocked(false);

	return true;
}
// describes the player's stats
void Player::Stats() const {
	cout << "\nNumber Life: " << lifes;
	cout << "\nLife: " << life;
	cout << "\nAttack: (" << ((weapon) ? weapon->getName() : "no weapon") << ") ";
	cout << ((weapon) ? weapon->getAttackMin() : damageMin) << "-" << ((weapon) ? weapon->getAttackMax() : damageMax);
	cout << "\nProtection: (" << ((armor) ? armor->getName() : "no armour") << ") ";
	cout << ((armor) ? armor->getDefenceArmor() : defence);
	cout << "\n";
}
// assigns the creature as die = true
void Player::Kill(const list<string>& sentence) {
	Creature* target = (Creature*)parent->Find(*next(sentence.begin()),Type::CREATURE);
	if (!target) {
		cout << "There in not " << *next(sentence.begin()) << endl;
	}
	else {
		if (!target->IsAlive() && target->die != true) {
			target->Die();
			target->die = true;
		}
	}
}
// reduce the number of lives by one
void Player::Die() 
{
	
	Creature::Die();
	if (lifes > 0) {
		lifes = lifes - 1;
		life = 250;
	}	
}
// Read an object Item of type text
bool Player::Read(const list<string>& sentence) 
{
	Item* item = (Item*)Find(*next(sentence.begin()),Type::ITEM);
	if (item == NULL) 
	{
		cout << *next(sentence.begin()) << " is not in your inventory.\n";
		return false;
	}
		
	if (item->itemType != ItemType::TEXT)
	{
		cout << *next(sentence.begin()) << " can't be read.\n";
		return false;
	}
	if (item->itemType == ItemType::TEXT)
	{
		cout << item->getWritten();
	}

}

