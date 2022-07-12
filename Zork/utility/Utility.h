#pragma once
#include <string>
#include <list>


class Utility {
public:
	Utility(); 
	~Utility() {};
	void setSentence(char* inputText);
	void clearSentence();
	void getSentence(std::list<std::string> &senten);
	int sizeSentence();
	std::string getLower(char* text);
private:	
	std::list<std::string> sentence;
	std::list<std::string> allImputText;
	
};

