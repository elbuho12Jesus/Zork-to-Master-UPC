#pragma once
#include "Entity.h"

enum class ItemType
{
	COMMON,
	WEAPON,
	ARMOR,
	TEXT,
	STORAGE
};

class Item: public Entity
{
private:
	int AttackMax;
	int AttackMin;
	int defenceArmor;
	std::string written;

public:
	Item(std::string name, std::string description,Entity* parent, int AttackMax, int AttackMin, int defenceArmor, ItemType itemType);
	~Item();
	ItemType itemType;
	void Look() const override;
	int GetValue() const;
	int getAttackMax() { return AttackMax; }
	int getAttackMin() { return AttackMin; }
	int getDefenceArmor() { return defenceArmor; }
	std::string getWritten() { return written; }
	void setWritten(std::string wri) { written = wri; }
};