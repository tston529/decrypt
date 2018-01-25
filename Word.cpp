#include "Word.h"
#include <string>
#include <map>
#include <unordered_map>

char alphabet[] = {'a','b','c','d','e','f',
                   'g','h','i','j','k','l',
                   'm','n','o','p','q','r',
                   's','t','u','v','w','x',
                   'y','z'};

Word::Word(std::string word){
  set_word(word);
}


void Word::set_word(std::string word){

  if(word.at(word.length()-1)==',')
    word.pop_back();

    
    //Make decoding other languages a tad easier by
    //  replacing characters with accents with a more
    //  familiar english equivalent
    for(unsigned int i = 0; i < word.length(); i++){
      const char*
            //   "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
            tr = "AAAAAAECEEEEIIIIDNOOOOOx0UUUUYPsaaaaaaeceeeeiiiiOnooooo/0uuuuypy";
      if ( word.at(i) >=192 ) {
        (word[i]) = tr[ word[i]-192 ];
      }
  }
  //Set the word
  word_str = word;

  //Set the word's length
  stats.first = word.length();

  //Set the word's unique letter amount (based on map size)
  /*
  Want to do: for each letter in the word, insert into the
  multimap the position of each instance of the letter
  */
  const char* temp = word.c_str();
  std::map<char, int> freq_map; //Counts frequency of each letter
  std::map<char, int> init_map; //Takes note of order of each letter's first appearance
  for(int i = 0; i < stats.first; i++){
     freq_map[temp[i]]++;
     std::pair<char, int> lett_pos (temp[i], i);
     pos_map.insert(lett_pos);
     if(!init_map.count(temp[i])){
       init_map[temp[i]] = i;
     }
  }
  
  //Creates the string's pattern (pattern -> abccdef, racecar -> abcdcba)
  // to be used in comparing the encoded with the dictionary word
  std::string pattern_builder="";
  for(int j = 0; j < stats.first; j++){
    if(init_map.count(temp[j]))
      pattern_builder+=alphabet[init_map[temp[j]]];
  }

   pattern = pattern_builder;

   stats.second = freq_map.size();

 }



char* removeAccented( char* str ) {
    char *p = str;
    while ( (*p)!=0 ) {
        const char*
        //   "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
        tr = "AAAAAAECEEEEIIIIDNOOOOOx0UUUUYPsaaaaaaeceeeeiiiiOnooooo/0uuuuypy";
        unsigned char ch = (*p);
        if ( ch >=192 ) {
            (*p) = tr[ ch-192 ];
        }
        ++p; // http://stackoverflow.com/questions/14094621/
    }
    return str;
}

