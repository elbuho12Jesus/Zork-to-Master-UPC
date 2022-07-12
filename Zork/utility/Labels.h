#pragma once
#include <iostream>
using namespace std;
void info()
{
    printf("\033[1m\tWelcome to ZORK!\n\n\033[0m");
    printf("\tYou are near a large dungeon, which is reputed to contain vast quantities of treasure.\n"); 
    printf("\tNaturally, you wish to acquire some of it.In order to do so, you must of course remove \n"); 
    printf("\tit from the dungeon.To receive full credit for it, you must deposit it safely in the trophy\n"); 
    printf("\tcase in the living room of the house.\n\n");
    printf("\tIn addition to valuables, the dungeon contains various objects which may or may not be useful\n"); 
    printf("\tin your attempt to get rich.You may need sources of light, since dungeons are often dark, and\n"); 
    printf("\tweapons, since dungeons often have unfriendly things wandering about.Reading material is\n"); 
    printf("\tscattered around the dungeon as well;  some of it is rumored to be useful.\n\n");
    printf("\tTo determine how successful you have been, a score is kept.When you find a valuable objectand\n"); 
    printf("\tpick it up, you receive a certain number of points, which depends on the difficulty of finding\n"); 
    printf("\tthe object.You receive extra points for transporting the treasure safely to the living roomand\n"); 
    printf("\tplacing it in the trophy case.In addition, some particularly interesting rooms have a value\n"); 
    printf("\tassociated with visiting them.The only penalty is for getting yourself killed, which you may\n"); 
    printf("\tdo only twice.\n\n");
    printf("\tOf special note is a thief(always carrying a large bag) who likes to wander around in the\n"); 
    printf("\tdungeon(he has never been seen by the light of day).He likes to take things.Since he steals\n"); 
    printf("\tfor pleasure rather than profitand is somewhat sadistic, he only takes things which you have\n"); 
    printf("\tseen.Although he prefers valuables, sometimes in his haste he may take something which is\n"); 
    printf("\tworthless.From time to time, he examines his takeand discards objects which he doesn't like.\n");
    printf("\tHe may occasionally stop in a room you are visiting, but more often he just wanders\n"); 
    printf("\tthroughand rips you off(he is a skilled pickpocket).\n\n");
    printf("\tYou hear in the distance the chirping of a song bird.\n");
}

void help() {
    printf("\033[1m\tUseful commands :\n\n\033[0m");
    printf("\tThe 'INFO' command prints information which might give some idea of what the game is about.\n");
    printf("\tThe 'QUIT' command prints your score and asks whether you wish to continue playing.\n");
    printf("\tThe 'INVENTORY' command lists the objects in your possession.\n");
    printf("\tThe 'LOOK' command prints a description of your surroundings.\n\n");
    printf("\033[1m\tCommand abbreviations :\n\n\033[0m");
    printf("\tThe 'INVENTORY' command may be abbreviated 'I'.\n");
    printf("\tThe 'LOOK' command may be abbreviated 'L'.\n");
    printf("\tThe 'QUIT' command may be abbreviated 'Q'.\n\n");
    printf("\033[1m\tContainment :\n\n\033[0m");
    printf("\tSome objects can contain other objects.Many such containers can be opened and closed.\n"); 
    printf("\tThe rest are always open.They may or may not be transparent.For you to access(e.g., take)\n"); 
    printf("\tan object which is in a container, the container must be open.For you to see such an object,\n"); 
    printf("\tthe container must be either open or transparent.Containers have a capacity, and objects have\n"); 
    printf("\tsizes;the number of objects which will fit therefore depends on their sizes.You may put any\n"); 
    printf("\tobject you have access to(it need not be in your hands) into any other object.At some point,\n"); 
    printf("\tthe program will attempt to pick it up if you don't already have it, which process may fail\n"); 
    printf("\tif you're carrying too much.Although containers can contain other containers, the program\n");
    printf("\tdoesn't access more than one level down.\n\n");
    printf("\033[1m\tFighting:\n\n\033[0m");
    printf("\tOccupants of the dungeon will, as a rule, fight back when attacked.In some cases, they may\n"); 
    printf("\tattack even if unprovoked.Useful verbs here are 'ATTACK <villain> WITH <weapon>', 'KILL',\n"); 
    printf("\tetc.Knife - throwing may or may not be useful.You have a fighting strength which varies \n"); 
    printf("\twith time.Being in a fight, getting killed, and being injured all lower this strength.\n"); 
    printf("\tStrength is regained with time.Thus, it is not a good idea to fight someone immediately\n");
    printf("\tafter being killed.Other details should become apparent after a few melees or deaths.\n\n");
    printf("\033[1m\tCommand parser :\n\n\033[0m");
    printf("\tA command is one line of text terminated by a carriage return.For reasons of simplicity,\n"); 
    printf("\tall words are distinguished by their first nine letters.All others are ignored.For example,\n"); 
    printf("\ttyping 'DISASSEMBLE THE ENCYCLOPEDIA' is not only meaningless, it also creates excess\n"); 
    printf("\teffort for your fingers.Note that this truncation may produce ambiguities in the\n");
    printf("\tinterpretation of longer words.\n");
    printf("\tYou are dealing with a fairly stupid parser, which understands the following types\n");
    printf("\tof things--\n\n");
    printf("\033[1m\tActions :\n\n\033[0m");
    printf("\tAmong the more obvious of these, such as TAKE, PUT, DROP, etc.\n");
    printf("\tFairly general forms of these may be used, such as PICK UP,\n");
    printf("\tPUT DOWN, etc.\n\n");
    printf("\033[1m\tDirections :\n\n\033[0m");
    printf("\tNORTH, SOUTH, UP, DOWN, etc.and their various abbreviations.\n");
    printf("\tOther more obscure directions(LAND, CROSS) are appropriate in\n");
    printf("\tonly certain situations.\n\n");    
    printf("\033[1m\tObjects :\n\n\033[0m");
    printf("\tMost objects have namesand can be referenced by them.\n\n");    
    printf("\033[1m\tAdjectives :\n\n\033[0m");
    printf("\tSome adjectives are understoodand required when there are\n");
    printf("\ttwo objects which can be referenced with the same 'name' (e.g.,\n");
    printf("\tDOORs, BUTTONs).\n\n");
    printf("\033[1m\tPrepositions :\n\n\033[0m");
    printf("\tIt may be necessary in some cases to include prepositions, but\n");
    printf("\tthe parser attempts to handle cases which aren't ambiguous\n");
    printf("\twithout.Thus 'GIVE CAR TO DEMON' will work, as will 'GIVE DEMON\n");
    printf("\tCAR'.  'GIVE CAR DEMON' probably won't do anything interesting.\n");
    printf("\tWhen a preposition is used, it should be appropriate;  'GIVE CAR \n");
    printf("\tWITH DEMON' won't parse.\n\n"); 
    printf("\033[1m\tSentences:\n\n\033[0m");
    printf("\tThe parser understands a reasonable number of syntactic construc -\n");
    printf("\ttions.In particular, multiple commands(separated by commas)\n");
    printf("\tcan be placed on the same line.\n\n");    
    printf("\033[1m\tAmbiguity :\n\n\033[0m");
    printf("\tThe parser tries to be clever about what to do in the case of\n");
    printf("\tactions which require objects that are not explicitly specified.\n");
    printf("\tIf there is only one possible object, the parser will assume\n");
    printf("\tthat it should be used.Otherwise, the parser will ask.\n");
    printf("\tMost questions asked by the parser can be answered.\n");
}
   
string westofhouseText = "This is an open field west of a white house, with a boarded front door.\nThere is a small mailbox here.\nA rubber mat saying 'Welcome to Zork!' lies by the door.";
string southofhouseText = "You are facing the south side of a white house.There is no door here, and all the windows are barred.";
string behindhouseText = "You are behind the white house.  In one corner of the house there is a small window which is slightly ajar.";
string kitchenText = "You are in the kitchen of the white house.  A table seems to have been used recently for the preparation of food."; 






    
    
    
    
    