// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"



WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return this->words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::vector <std::string> suggestions;
    //add spacing of each part of the string to check if its two strings
    for(int i =0; i < word.length() -2; i++)
    {
        std::string temp = word;
        std::string str1 = temp.substr(0,i);
        std::string str2 = temp.substr(i,word.length()-1);
        if(wordExists(str1) && wordExists(str2))
            suggestions.push_back(str1+" "+str2);
    }
    //try swapping words around to check if the spelling mistake 
    for(int i = 0; i < word.length(); i ++)
    {
        std::string temp = word;
        std::swap(temp[i],temp[i+1]);
        if(wordExists(temp) && (std::find(suggestions.begin(), suggestions.end(), temp) == suggestions.end()))
            suggestions.push_back(temp);
    }
    //gonna change each char of the string to another letter of alphabet to check
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0 ; i < alphabet.length(); i++)
    {
        for(int x = 0; x < word.length(); x++)
        {
            std::string temp = word;
            temp[x] = alphabet[i];
            if(wordExists(temp) && (std::find(suggestions.begin(), suggestions.end(), temp) == suggestions.end()))
                suggestions.push_back(temp);
        }

    }
    //delete some of the character to check if they added extra character
    for(int i = 0 ; i < word.length(); i++)
    {
        std::string temp = word;
        temp.erase(i,1);
        if(wordExists(temp) && (std::find(suggestions.begin(), suggestions.end(), temp) ==suggestions.end()))
            suggestions.push_back(temp);
    }
    //inserts characters between each char
    for(int i = 0 ; i < alphabet.length(); i++)
    {
        for(int x = 0; x < word.length() ; x++)
        {
             std::string temp = word;
             temp.insert(x,1,alphabet[i]);
             if(wordExists(temp)&& (std::find(suggestions.begin(), suggestions.end(), temp) == suggestions.end()))
             suggestions.push_back(temp);
        }

        //add to the end of the word
        std::string temp = word;
        temp.insert(temp.end(),1,alphabet[i]);
        if(wordExists(temp) && (std::find(suggestions.begin(), suggestions.end(), temp) == suggestions.end()))
            suggestions.push_back(temp);
   }

   return suggestions;
} 


