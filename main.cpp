#include "Word.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

//Rather than spitting out a lengthy series of words and their potential matches
//  in a command prompt, just print to file.  This will be deprecated by the 
//  time the project progresses enough to narrow down options to potential
//  solutions to the overall problem (a successful or near-successful decryption)
void print_to_file(ofstream&, const unordered_map<string, Word>&, const unordered_map <Word, string>&, unordered_map<string, int>&);

unordered_map<char, char> delta;
  char alph[]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 
               'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
               's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

  char temp='A';

int main()
{
  //Fill the delta map with pairs of the same character
  //  here, denoted with capital letters, e.g. {'A', 'A'}.
  //  This map will later contain decoded letters (to be 
  //  replaced with a lowercase letter, e.g. {'F', 'e'})
  for(int i = 0; i < 26; i++){
    delta.insert({temp, temp});
    temp++;
  }
  //My quick increment function stops outside of the 
  //  alphabet, because ASCII conventions, so I manually
  //  slap the comma and the space character pairs in.
  delta.insert({',',','});
  delta.insert({' ',' '});

  //The files to be read: the dictionary, and the encoded message
  string dict_name = "enable1.txt";
  string cipher = "cipher.dat";

  unordered_map<string, Word> ciph_map; // map of ciphered words
  unordered_map<Word, string> dict_map; // map of valid english words from dictionary
  unordered_map<string, int> count_map; // map to keep track of results (amount of matches per ciphered word)


  //Open the dictionary, create an output file ("out.txt")
  ifstream d_file(dict_name);
  ofstream output;
  output.open("out.txt");



  //Read in every line in the dictionary (as var "temp")
  //  and create a Word object for each (giving each word
  //  stats and explicitly defining its traits)
  string temp;
  while(getline(d_file, temp)){
    Word word_obj(temp);
    pair<Word, string> count (word_obj, temp);
    dict_map.insert(count);
  }
  
  //Open the encoded message file
  ifstream c_file(cipher);

  //Similarly to the dictionary read function, read
  //  in every word in the message as a Word object
  //  to define its stats.
  string encoded_word;
  while(c_file >> encoded_word){
    Word word_obj(encoded_word);
    pair<std::string, Word> ciph (encoded_word, word_obj);
    ciph_map.insert(ciph);
    count_map[encoded_word] = 0;
  }

  print_to_file(output, ciph_map, dict_map, count_map);

  return 0;
}

void print_to_file(ofstream &output, const unordered_map<string, Word> &ciph_map, const unordered_map<Word, string> &dict_map, unordered_map<string, int> &count_map){

  for ( auto x = ciph_map.begin(); x != ciph_map.end(); ++x ){// x = pair(encoded word, word obj)
    //string compare_word;
    //cout << "\nSimilar words to: " << x->first << endl << "----------" << endl;
    //cout << "Pattern: " << x->second.get_pattern() << endl;
    output << "\nSimilar words to: " << x->first << endl << "----------" << endl;
    output << "Pattern: " << x->second.get_pattern() << endl;

    for( auto y = dict_map.begin(); y != dict_map.end(); ++y){// y = pair(word obj, dictionary word)
        if((y->first.get_pattern()) == (x->second.get_pattern()) ){
            //std::cout << y->second << endl;
            output << y->second << endl;
            count_map[x->first] = count_map[x->first]+1;
        }

    }
  }
  
  for( auto z = count_map.begin(); z != count_map.end(); ++z){
      cout << z->first << " : " << z->second << endl;
  }
  
  output.close();
}