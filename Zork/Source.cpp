// istream::getline example
#include "pch.h"
#include "utility/Utility.h"
#include "World.h"
#include "Player.h"



int main() {

	char inputText[256];	
	list<string> sentence;
	Utility sentence1 = Utility();
	World* world = new World();
	while (world->state) {
		if (sentence1.sizeSentence()==0) {
			cout << "< ";
			cin.getline(inputText, 256);
			sentence1.setSentence(inputText);						
		}	
		sentence1.getSentence(sentence);
		world->findText(sentence);
		sentence1.clearSentence();
		cout << endl;
	}
	
	
	

	printf(" lista %i", sentence.size());



	return 0;
}