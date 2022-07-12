#include "pch.h"
#include "World.h"
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "utility/Labels.h"



World::World():state(true)
{
	Room* westOfHouse = new Room("West of House", westofhouseText,NULL);
	player = new Player("me", "player", westOfHouse, 250, 10, 5, 8, NULL, NULL, 3);

	Room* Forest1 = new Room("Forest", "This is a forest, with trees in all directions around you.",NULL);
	Room* southOfHouse = new Room("South of House", southofhouseText, NULL);

	Exit* westofwestOfHouse = new Exit("west","","none", westOfHouse, Forest1,false);	
	Exit* eastofwestOfHouse = new Exit("east", "", "west", westOfHouse, southOfHouse, true);

	
	Item* emailbox = new Item("mailbox", "You open the mailbox, revealing a small leaflet.", westOfHouse, 0, 0, 0, ItemType::STORAGE);
	Item* leaflet = new Item("leaflet", "leaflet", emailbox, 0, 0, 0, ItemType::TEXT);
	leaflet->setWritten("\tWELCOME TO ZORK\n");

	Room* behindhouse = new Room("Behind House", behindhouseText, NULL);
	Room* kitchen = new Room("Kitchen",kitchenText,NULL);

	Exit* northofsouthOfHouse = new Exit("north", "", "south", southOfHouse, behindhouse, false);
	Exit* openwindow = new Exit("window", "", "window", behindhouse, kitchen, false);

	Creature* minitroll = new Creature("minitroll","a tiny troll.",kitchen,100,3,4,5,NULL,NULL);


	
}


bool World::findText(list<string> sentence) {
	switch (sentence.size())
	{
	case 0:
	case 1:
	{
		if (*sentence.begin() == "info") {
			info();
			return true;
		}
		if (*sentence.begin() == "help") {
			help();
			return true;
		}
		if (*sentence.begin() == "look") {
			player->Look(sentence);
			return true;
		}		
		if (*sentence.begin() == "inventory") {
			player->Inventory();
			return true;
		}
		if (*sentence.begin() == "score") {
			player->Stats();
			return true;
		}		
		if (*sentence.begin() == "north") {
			sentence.push_back("north");
			player->Go(sentence);
			return true;
		}
		if (*sentence.begin() == "south") {
			sentence.push_back("south");
			player->Go(sentence);
			return true;
		}
		if (*sentence.begin() == "east") {
			sentence.push_back("east");
			player->Go(sentence);
			return true;
		}
		if (*sentence.begin() == "west") {
			sentence.push_back("west");
			player->Go(sentence);
			return true;
		}
		if (*sentence.begin() == "up") {
			sentence.push_back("up");
			player->Go(sentence);
			return true;
		}
		if (*sentence.begin() == "down") {
			sentence.push_back("down");
			player->Go(sentence);
			return true;
		}
		if (*sentence.begin() == "quit") {
			state = false;			
			return true;
		}
		break;
	}	
	case 2:
	{
		if (*sentence.begin() == "look") {
			player->Look(sentence);
			return true;
		}
		if (*sentence.begin() == "read") {
			player->Read(sentence);
			return true;
		}
		if (*sentence.begin() == "take") {
			player->Take(sentence);
			return true;
		}
		if (*sentence.begin() == "drop") {
			player->Drop(sentence);
			return true;
		}
		if (*sentence.begin() == "put") {
			player->Equip(sentence);
			return true;
		}
		if (*sentence.begin() == "attack") {
			if (player->Attack(sentence))
			{
				player->MakeAttack();
			}
			if (player->getLifes()==0) 
			{
				state = false;
			}
			return true;
		}
		if (*sentence.begin() == "kill") {
			player->Kill(sentence);
			return true;
		}
		if (*sentence.begin() == "loot") {
			player->Loot(sentence);
			return true;
		}		
		if (*sentence.begin() == "go" ) {
			player->Go(sentence);
			return true;
		}
		if (*sentence.begin() == "go") {
			player->Go(sentence);
			return true;
		}
		if (*sentence.begin() == "go" ) {
			player->Go(sentence);
			return true;
		}
		if (*sentence.begin() == "go" ) {
			player->Go(sentence);
			return true;			
		}
		break;
	}	
	case 3:
	{		
		if (*sentence.begin() == "pick" && *next(sentence.begin()) == "up") {
			sentence.pop_front();
			player->Equip(sentence);
			return true;
		}		
		if (*sentence.begin() == "put" && *next(sentence.begin()) == "down") {
			sentence.pop_front();
			player->Drop(sentence);
			return true;
		}
		break;
	}	
	case 4:
	{
		if (*sentence.begin() == "attack" && *next(sentence.begin(), 2) == "with") {
			if(player->Equip(list<string>{"equip", * next(sentence.begin(), 3)}))
			{
				if (player->Attack(sentence))
				{
					player->MakeAttack();
				}
				if (player->getLifes() == 0)
				{
					state = false;
				}
			}
				
			return true;
		}
		if (*sentence.begin() == "take" && *next(sentence.begin(), 2) == "of")
		{
			player->Take(sentence);
		}
		break;
	}	
	default:
		printf("unknown verb");
		break;
	}
	return false;
}