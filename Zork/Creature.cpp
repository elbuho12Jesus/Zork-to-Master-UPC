#include "pch.h"
#include "Creature.h"
#include "Item.h"
#include "Exit.h"
#include "Room.h"
#include "Player.h"
#include "utility/GlobalFunctions.h"

Creature::Creature(string name, string description, Entity* parent,int life, int defence, int damageMin, int damageMax, Item* weapon, Item* armor)
	:Entity(name, description, Type::CREATURE, parent),
	life(life),defence(defence), damageMin(damageMin),damageMax(damageMax),weapon(weapon),armor(armor)
{
	combat_target = NULL;
	die = false;
}

// check the amount of life(energy) of the creature is positive
bool Creature::IsAlive() const
{
	return life > 0;
}
// goes to an existing exit( type Exit)
bool Creature::Go(const list<string>& sentence)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(*next(sentence.begin()));

	if (exit == NULL)
		return false;

	if (PlayerInRoom())
		cout << name << "goes " << *next(sentence.begin()) << "...\n";

	ChangeParentTo(exit->GetDestinationFrom((Room*)parent));

	return true;
}
// describes the container of a parent of a ROOM or ITEM
 void Creature::Look(const list<string>& sentence) const
{
	if (IsAlive() && die!=true)
	{
		cout << name << "\n";
		cout << description << "\n";
	}
	else if (IsAlive() && die != false)
	{
		cout << name << "'s body\n";
		cout << "Here lies stun: " << description << "\n";
	}
	else
	{
		cout << name << "'s corpse\n";
		cout << "Here lies dead: " << description << "\n";
	}
}
// takes an object from its parent's container and adds it to your container
bool Creature::Take(const list<string>& sentence)
{
	if (!IsAlive())
		return false;	
	Item* item = (Item*)parent->Find(*next(sentence.begin()), Type::ITEM);
	if (sentence.size() > 1)
	{
		if (item == NULL)
			item = (Item*)Find(*next(sentence.begin()), Type::ITEM);

		if (item == NULL)
			return false;

		Item* subitem = (Item*)item->Find(*next(sentence.begin(),3), Type::ITEM);

		if (subitem == NULL)
			return false;

		if (PlayerInRoom())
			cout << name << " looks into " << item->getName() << "...\n";

		item = subitem;
	}

	if (item == NULL)
		return false;

	if (PlayerInRoom())
		cout << name << " takes " << item->getName() << ".\n";

	item->ChangeParentTo(this);

	return true;
}
// show the elements of your container 
void Creature::Inventory() const
{
	list<Entity*> items;
	FindAll(Type::ITEM, items);

	if (items.size() == 0)
	{
		cout << name << " does not own any items\n";
		return;
	}

	cout << "\n" << name << " owns:\n";
	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		if (*it == weapon)
			cout << (*it)->getName() << " (AS WEAPON)\n";
		else if (*it == armor)
			cout << (*it)->getName() << " (AS ARMOR)\n";
		else
			cout << (*it)->getName() << "\n";
	}
}
// assigns an item to the WEAPON or ARMOR object of the creature
bool Creature::Equip(const list<string>& sentence)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)Find(*next(sentence.begin()), Type::ITEM);

	if (item == NULL)
		return false;

	switch (item->itemType)
	{
	case ItemType::WEAPON:
		weapon = item;
		break;

	case ItemType::ARMOR:
		armor = item;
		break;

	default:
		return false;
	}

	if (PlayerInRoom())
		cout << name << " equips " << item->getName() << "...\n";

	return true;
}
// unassigns an item to the WEAPON or ARMOR object of the creature
bool Creature::UnEquip(const list<string>& sentence)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)Find(*next(sentence.begin()), Type::ITEM);

	if (item == NULL)
		return false;

	if (item == weapon)
		weapon = NULL;
	else if (item == armor)
		armor = NULL;
	else
		return false;

	if (PlayerInRoom())
		cout << name << " un-equips " << item->getName() << "...\n";

	return true;
}
// is assigned to an Exit object (lock = true)
bool Creature::Lock(const list<string>& sentence)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(*next(sentence.begin()));

	if (exit == NULL || exit->getLocked() == true)
		return false;

	Item* item = (Item*)Find(*next(sentence.begin(),3), Type::ITEM);

	if (item == NULL || exit->key != item)
		return false;

	if (PlayerInRoom())
		cout << "\n" << name << "locks " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->setLocked(true);

	return true;
}
// is assigned to an Exit object (lock = false)
bool Creature::UnLock(const list<string>& sentence)
{
	if (!IsAlive())
		return false;

	Exit* exit = GetRoom()->GetExit(*next(sentence.begin()));

	if (exit == NULL || exit->getLocked() == false)
		return false;

	Item* item = (Item*)Find(*next(sentence.begin(),3), Type::ITEM);

	if (item == NULL || exit->key != item)
		return false;

	if (PlayerInRoom())
		cout << "\n" << name << "unlocks " << exit->GetNameFrom((Room*)parent) << "...\n";

	exit->setLocked(false);

	return true;
}
// assign a type item object from your container to the parent's container
bool Creature::Drop(const list<string>& sentence)
{
	if (!IsAlive())
		return false;

	Item* item = (Item*)Find(*next(sentence.begin()), Type::ITEM);

	if (item == NULL)
		return false;

	if (PlayerInRoom())
		cout << name << " drops " << item->getName() << "...\n";

	item->ChangeParentTo(parent);

	return true;
}
// return the player's parent
Room* Creature::GetRoom() const
{
	return (Room*)parent;
}
// return true if the player is in the (ROOM) parent's container of creature current
bool Creature::PlayerInRoom() const
{
	return parent->Find(Type::PLAYER) != NULL;
}
// start a fight between objects of type creatures
void Creature::Combat()
{
	if (combat_target != NULL)
	{
		if (parent->Exists(combat_target) == true)
			MakeAttack();
		else
			combat_target = NULL;
	}
}
// check if there is a target to attack
bool Creature::Attack(const list<string>& sentence)
{
	Creature* target = (Creature*)parent->Find(*next(sentence.begin()), Type::CREATURE);

	if (target == NULL)
		return false;	
	
	combat_target = target;
	cout << "\n" << name << " attacks " << target->name << "!\n";
	return true;
}
// loop of fight between creatures
void Creature::MakeAttack()
{
	if (!IsAlive() || !combat_target->IsAlive())
	{
		combat_target = combat_target->combat_target = NULL;

	}
	else {

	int result = (weapon) ? weapon->GetValue() + GlobalFunctions::Roll(damageMin, damageMax) : GlobalFunctions::Roll(damageMin, damageMax);

	if (PlayerInRoom())
		cout << name << " attacks " << combat_target->name << " for " << result << "\n";

	combat_target->ReceiveAttack(result);

	// make the attacker react and take me as a target
	if (combat_target->combat_target == NULL)
		combat_target->combat_target = this;	
	combat_target->MakeAttack();
	}
}
// Calculation of damage that the target will receive
int Creature::ReceiveAttack(int damage)
{
	int prot = (armor) ? armor->GetValue()+defence : defence;
	int received = (damage - prot)>0? damage - prot:0;

	life -= received;

	if (PlayerInRoom())
		cout << name << " is hit for " << received << " damage (" << prot << " blocked) \n";

	if (IsAlive() == false && type != Type::PLAYER)	
		Stun();
	if (IsAlive() == false && type == Type::PLAYER)		
		this->Die();
	
		

	return received;
}
// describe that object have the life <=0
void Creature::Stun()
{
	if (PlayerInRoom())
		cout << name << " stun.\n";
}
// describe that object was die <=0
void Creature::Die()
{
	if (PlayerInRoom())
		cout << name << " dies.\n";	
}
// assigns the items of the dead creature
bool Creature::Loot(const list<string>& sentence)
{
	Creature* target = (Creature*)parent->Find(*next(sentence.begin()), Type::CREATURE);
	Creature& x = *target;
	if (&x && target->IsAlive() == false) {
		delete target;
		return false;
	}
	else {
		list<Entity*> items;
		target->FindAll(Type::ITEM, items);

		for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
		{
			Item* i = (Item*)(*it);
			i->ChangeParentTo(this);
		}

		cout << "\n" << name << " loots " << target->name << "'s corpse\n";

		return true;
	}	
}
// describes the creature's stats
void Creature::Stats() const
{	
	cout << "\nLife: " << life;
	cout << "\nAttack: (" << ((weapon) ? weapon->getName() : "no weapon") << ") ";
	cout << ((weapon) ? weapon->getAttackMin() : damageMin) << "-" << ((weapon) ? weapon->getAttackMax() : damageMax);
	cout << "\nProtection: (" << ((armor) ? armor->getName() : "no armour") << ") ";
	cout << ((armor) ? armor->getDefenceArmor() : defence);
	cout << "\n";
}