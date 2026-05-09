// :)
#include <string>
using std::string;

#include <fstream>
using std::ifstream;

#include <iostream>
using std::cin, std::cout, std::endl, std::istream;

#include <unordered_map>
using std::unordered_map;

#include <vector>
using std::vector;


// Exists to do a search through a given string vector looking for a certain string value.
// Returns true if it finds a match and false otherwise.
bool isIn(string& value, vector<string>& list)
{
	for(int i = 0; i < list.size(); i++)
		if(value == list.at(i))
			return true;

	return false;
}

//
unordered_map<string,vector<string>> trainer(istream& trainingData)
{
	string lastWord = "";
	string nextWord;
	unordered_map<string, vector<string>> trainedMap;
	while(trainingData >> nextWord)
	{
		if(trainedMap.find(lastWord) == trainedMap.end())
		{
			vector<string> wordSet = {nextWord};
			trainedMap[lastWord] = wordSet;
		}
		else
		{
			//if(!isIn(nextWord,trainedMap.at(lastWord)))
				trainedMap.at(lastWord).push_back(nextWord);
		}
		lastWord = nextWord;
	}
	return trainedMap;
}

// The printMap function below exists exclusively for testing purposes to ensure data is mapped correctly.
// All it does is literally list out each map key and the associated words.
// As such, it is not active in the turned in version of the program, but remains in case testing is needed again.
void printMap(unordered_map<string,vector<string>>& toMap)
{
	for(auto& item : toMap)
	{
		cout << item.first << ": ";
		for(string word : item.second)
		{
			cout << word;
			if(word != item.second.at(item.second.size()-1))
				cout << ", ";
		}
		cout << endl;
	}
}

unordered_map<string, vector<string>> runTrainer(string fileName)
{
	ifstream file(fileName);
	unordered_map<string,vector<string>> trainedMap = trainer(file);
	file.close();
	return trainedMap;
}

string getRandomWordFromMap(unordered_map<string, vector<string>>& givenMap)
{
	srand(time(NULL));
	int randNum = rand()%(givenMap.size());
	int i = 0;
	for(auto item : givenMap)
	{
		if(i == randNum)
			return item.first;
		i++;
	}
	return "";
}

void makeSpeech(unordered_map<string, vector<string>>& speechMap, int numOfWords)
{
	string word = getRandomWordFromMap(speechMap);
	srand(time(NULL));
	for(int i = 0; i < numOfWords; i++)
	{
		int randNum = rand()%(speechMap.at(word).size());
		word = speechMap.at(word).at(randNum);
		cout << word << " ";
	}
	cout << endl;
}

int main(int argc,char* argv[])
{
	if(argc < 3)
	{
		cout << "Too few arguments given. Please provide arguments in the form of ./<program> <inputFileName> <numberOfWordsToPrint>" << endl;
		return 1;
	}

	int wordCount = atoi(argv[2]);
	unordered_map<string, vector<string>> bucket = runTrainer(argv[1]);
	//printMap(bucket);
	makeSpeech(bucket, wordCount);

	return 0;
}