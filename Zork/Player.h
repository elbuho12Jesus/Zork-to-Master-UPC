#pragma once
#include "Creature.h"


class Player :public Creature {
private:
	int lifes;

public:
	Player(std::string name, std::string description,Entity* parent, int life, int defence, int damageMin, int damageMax, Item* weapon, Item* armor, int lifes);
	~Player();
	bool Go(const list<string>& sentence) override;
	void Look(const list<string>& sentence) const override;
	bool Take(const list<string>& sentence) override;
	bool Drop(const list<string>& sentence) override;
	void Inventory() const override;
	bool Equip(const list<string>& sentence) override;
	bool UnEquip(const list<string>& sentence) override;
	bool Examine(const list<string>& sentence) const;
	bool Attack(const list<string>& sentence) override;
	bool Loot(const list<string>& sentence) override;
	bool Lock(const list<string>& sentence) override;
	bool UnLock(const list<string>& sentence) override;
	bool Read(const list<string>& sentence);	
	void Stats() const override;
	void Die() override;
	void Kill(const list<string>& sentence);
	int getLifes() { return lifes; }
};