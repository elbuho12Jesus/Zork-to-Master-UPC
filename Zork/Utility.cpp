#include "pch.h"
#include "utility/Utility.h"


Utility::Utility()
{
	sentence.push_back("look");
}
// returns the list of statements
void Utility::getSentence(list<string>& senten) {
	senten = sentence;
}
// convert a sentence into a list of words
void Utility::setSentence(char* inputText) {
	char* next_token1 = NULL;
	char* token1 = NULL;
	token1 = strtok_s(inputText, " ", &next_token1);
	while (token1 != NULL)
	{
		if (token1 != NULL) {
			if ((unsigned)strlen(token1) > 0) {
				sentence.push_back(getLower(token1));				
			}
			token1 = strtok_s(NULL, " ", &next_token1);
		}
	}
	allImputText.push_back(inputText);
}
// delete the list
void Utility::clearSentence() {
	sentence.clear();
}
// convert a string to lowercase
string Utility::getLower(char* text) {
	int i = 0;
	string returnText;
	while (text[i]) {
		returnText.push_back(tolower(text[i]));
		i++;
	}
	return returnText;
}
// returns the size of the list
int Utility::sizeSentence() {
	return sentence.size();
}