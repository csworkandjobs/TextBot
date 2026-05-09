// copy your functioning basic_text_generation.cpp
// and add in your new features
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
// Not used in this particular edition of the program, but it will be useful if I want to change
// to a more memory-saving version that does not store duplicates, instead simply weighting
// the duplicate words to be heavier when the word choice is being made.
// Ex. A word that appears twice in the training data will have a weight of two in its
// spot rather than literally having two places in the words vector.
bool isIn(string& value, vector<string>& list)
{
	for(int i = 0; i < list.size(); i++)
		if(value == list.at(i))
			return true;

	return false;
}

// This turns a given input file into a mapped dataset.
unordered_map<string,vector<string>> trainer(istream& trainingData)
{
	string lastWord = ""; //The first word uses "" as its starting point.
	string nextWord;
	unordered_map<string, vector<string>> trainedMap;
	while(trainingData >> nextWord) //Continues grabbing individual words until it reaches the end of the file.
	{
		if(trainedMap.find(lastWord) == trainedMap.end()) //If a new word is found that has not been mapped for association, it is given a new entry.  Each entry is unique.
		{
			vector<string> wordSet = {nextWord};
			trainedMap[lastWord] = wordSet;
		}
		else
		{
			//if(!isIn(nextWord,trainedMap.at(lastWord)))		//This is the original version of my code excluded duplicates of word associations.  I removed this when I realized it would affect word choice.
				//trainedMap.at(lastWord).push_back(nextWord);  // I have kept the code here since it can easily be adapted into a weighted association map that is less memory intensive.

			trainedMap.at(lastWord).push_back(nextWord); //This is the current version of the word associations.  It does not have protections against duplicate words.  It is unfriendly to memory, but it allows for the map to reflect how words have different levels of commonality.
		}
		lastWord = nextWord; //Simply preparing for the next round which will use a different word to map associations off of.
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

//This simply takes a filename, opens it, maps it, then closes it.
//It is just meant to remove the need to open and close files in the main method.
unordered_map<string, vector<string>> runTrainer(string fileName)
{
	ifstream file(fileName);
	unordered_map<string,vector<string>> trainedMap = trainer(file);
	file.close();
	return trainedMap;
}

//This is used to get a random starting word.  Since maps are not the most friendly in
// allowing for random points to be chosen, this basically brute forces a way to get a
// random word from the map.  It just picks a number in range, then iterates until
// it has iterated enough times to reach the chosen number.
// This is not ideal, but it was fairly quick to code and still doesn't take long since it only runs once.
// I tried letting it just return the first item hoping the unordered_map would return a
// different first item each time, but this was not the case.
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
	return ""; //This line will never be accessed unless the program is supplied an empty map.
}

// This is the speech generator.  It takes in a map and an instructed number of words then outputs.
void makeSpeech(unordered_map<string, vector<string>>& speechMap, int numOfWords)
{
	string word = getRandomWordFromMap(speechMap); // Finding the first word randomly.
	srand(time(NULL));
	for(int i = 0; i < numOfWords; i++) // Chooses more words until it meets the perscribed number of words.
	{
		int randNum = rand()%(speechMap.at(word).size()); // Choosing the next word randomly from the words that followed in the training data.
		word = speechMap.at(word).at(randNum);
		cout << word << " "; //Just formatting to add spaces between words.
	}
	cout << endl;
}

//This is the same as the normal trainer, except that it takes in an existing map instead of creating a new one.
// This allows it to take in the pretrained map and give more training.
// If necessary in the future, this can be fairly easily merged with the normal trainer so that there is only one training function.
void addMoreData(unordered_map<string, vector<string>>& trainedMap, istream& trainingData)
{
	string lastWord = ""; //The first word uses "" as its starting point.
	string nextWord;
	while(trainingData >> nextWord) //Continues grabbing individual words until it reaches the end of the file.
	{
		if(trainedMap.find(lastWord) == trainedMap.end()) //If a new word is found that has not been mapped for association, it is given a new entry.  Each entry is unique.
		{
			vector<string> wordSet = {nextWord};
			trainedMap[lastWord] = wordSet;
		}
		else
		{
			trainedMap.at(lastWord).push_back(nextWord); //This adds word associations.  It does not have protections against duplicate words.  It is unfriendly to memory, but it allows for the map to reflect how words have different levels of commonality.
		}
		lastWord = nextWord; //Simply preparing for the next round which will use a different word to map associations off of.
	}
}

//This is nearly identical to the function that takes in a file name, trains data, and returns a map,
// except this one opens files, sends an existing map off to be further trained with that file, then closes the file.
void addMoreDataStart(unordered_map<string, vector<string>>& speechMap, string fileName)
{
	ifstream file(fileName);
	addMoreData(speechMap,file);
	file.close();
}

int main(int argc,char* argv[])
{
	if(argc < 2) //Ensures sufficient arguments are given.
	{
		cout << "Too few arguments given. Please provide arguments in the form of ./<program> <numberOfWordsToPrint> <inputFileName>" << endl;
		cout << "Please note that the <inputFileName> section is optional as a considerable amount of training information has already been provided. As many files as desired may be given." << endl;
		return 1;
	}

	int wordCount = atoi(argv[1]); //Extracts the perscribed word count.
	unordered_map<string, vector<string>> bucket = runTrainer("classicNovelsTrainingData.custom-input.txt");//Trains the map on my custom gathered data.
	for(int i = 2; i < argc; i++)
	{
		addMoreDataStart(bucket,argv[i]);
	}
	makeSpeech(bucket, wordCount); //Generates speech based on mapped data.

	return 0;
}