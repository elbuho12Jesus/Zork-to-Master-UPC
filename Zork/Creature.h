#pragma once
#include "Entity.h"
class Room;
class Item;
class Creature :public Entity {
protected:	
	int defence;
	int damageMax;
	int damageMin;
	
	
public:
	Creature(std::string name, std::string description,Entity* parent ,int life, int defence, int damageMin,int damageMax, Item* weapon ,Item* armor);
	~Creature() {};
	virtual bool Go(const list<string>& sentence);
	virtual void Look(const list<string>& sentence) const;
	virtual bool Take(const list<string>& sentence);
	virtual bool Drop(const list<string>& sentence);
	virtual void Inventory() const;
	virtual bool Equip(const list<string>& sentence);
	virtual bool UnEquip(const list<string>& sentence);	
	virtual bool Lock(const list<string>& sentence);
	virtual bool UnLock(const list<string>& sentence);
	virtual void Combat();
	

	virtual bool Attack(const list<string>& sentence);
	void MakeAttack();
	int ReceiveAttack(int damage);
	virtual void Die();
	void Stun();
	virtual bool Loot(const list<string>& sentence);
	virtual void Stats() const;

	Room* GetRoom() const;
	bool PlayerInRoom() const;
	bool IsAlive() const;
	Item* weapon;
	Item* armor;
	Creature* combat_target;
	int life;
	bool die;
};