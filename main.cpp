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
void print(const unordered_map<string, Word>&, const unordered_map <Word, string>&, unordered_map<string, int>&);

void decrypt(string, const unordered_map<string, Word>&, const unordered_map<Word, string>&, unordered_map<string, int>&);

unordered_map<char, char> delta;

int main()
{
  //Fill the delta map with pairs of the same character
  //  here, denoted with capital letters, e.g. {'A', 'A'}.
  //  This map will later contain decoded letters (to be 
  //  replaced with a lowercase letter, e.g. {'F', 'e'})
    char init_char='A';
    for(int i = 0; i < 26; i++){
        delta.insert({init_char, init_char});
        init_char++;
    }
    //My quick increment function stops outside of the 
    //  alphabet, because ASCII conventions, so I manually
    //  slap the comma and the space character pairs in.
    delta.insert({',',','});
    delta.insert({' ',' '});

    //The files to be read: the dictionary, and the encoded message
    string dict_name;
    cout << "Enter the name of the dictionary: " << endl;
    cin >> dict_name;
    string cipher;
    cout << "Enter the name of the encoded file: " << endl;
    cin >> cipher;

    unordered_map<string, Word> ciph_map; // map of ciphered words; 
                                          //     matches a string to a Word
    unordered_map<Word, string> dict_map; // map of valid english words from dictionary;
                                          //     matches a Word to a string

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
    ifstream c_file;
    c_file.open(cipher.c_str());

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
    c_file.close();

    print(ciph_map, dict_map, count_map); //Change this to print_to_file to get a complete text output
    decrypt(cipher, ciph_map, dict_map, count_map); //This modifies the map<char, char> delta

    //Reopen the cipher file to restart reading from the beginning,
    //  then print out the string character-by-character replacing
    //  each character in the file with what it is mapped onto in 
    //  the delta map.
    c_file.open(cipher.c_str());
    c_file >> std::noskipws;
    char toPrint;
    while(c_file>>toPrint){
        cout << delta[toPrint];
    }
    cout << endl;
    c_file.close();

    return 0;
}

/*********************************************/
/* The following 2 functions are comparable: */
/*                                           */
/* print_to_file outputs an exhaustive list  */
/*   of each match of a ciphered word to     */
/*   a file.                                 */
/*                                           */
/* print outputs the ciphered word with      */
/*   simply the number of matches it has     */
/*   to the console.                         */
/*                                           */
/* These may be deprecated or removed after  */
/*   decode works more fully.                */
/*********************************************/


/**************************/
/*     print_to_file      */
/**************************/

void print_to_file(ofstream &output, const unordered_map<string, Word> &ciph_map, const unordered_map<Word, string> &dict_map, unordered_map<string, int> &count_map){

  for ( auto x = ciph_map.begin(); x != ciph_map.end(); ++x ){// x = pair(encoded word, word obj)
    output << "\nSimilar words to: " << x->first << endl << "----------" << endl;
    output << "Pattern: " << x->second.get_pattern() << endl;

    for( auto y = dict_map.begin(); y != dict_map.end(); ++y){// y = pair(word obj, dictionary word)
        if((y->first.get_pattern()) == (x->second.get_pattern()) ){
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
/**************************/
/*         print          */
/**************************/
void print(const unordered_map<string, Word> &ciph_map, const unordered_map<Word, string> &dict_map, unordered_map<string, int> &count_map){

  for ( auto x = ciph_map.begin(); x != ciph_map.end(); ++x ){// x = pair(encoded word, word obj)

    for( auto y = dict_map.begin(); y != dict_map.end(); ++y){// y = pair(word obj, dictionary word)
        if((y->first.get_pattern()) == (x->second.get_pattern()) ){

            count_map[x->first] = count_map[x->first]+1;
        }

    }
  }
  
  for( auto z = count_map.begin(); z != count_map.end(); ++z){
      cout << z->first << " : " << z->second << endl;
  }
  cout << endl;
  
}

/*
Handy guide copypasta:

ciph_map->first  ==> ciphered string
ciph_map->second ==> ciphered Word object

dict_map->first  ==> dictionary Word object
dict_map->second ==> dictionary string

count_map->first ==> ciphered string
count_map->second => amount of results
*/

/**************************/
/*        decrypt         */
/* As of now, it runs one */
/* pass of an alphabet    */
/* cipher if it can find  */
/* a word with only a     */
/* single possibility.    */
/**************************/

void decrypt(string cipher, const unordered_map<string, Word> &ciph_map, const unordered_map<Word, string> &dict_map, unordered_map<string, int> &count_map){
    //int lowMatches=1;
    for ( auto x = ciph_map.begin(); x != ciph_map.end(); ++x ){
        if(count_map[x->first]==1){//initially check for a single match

            for( auto y = dict_map.begin(); y != dict_map.end(); ++y){// y = pair(word obj, dictionary word)
                if((y->first.get_pattern()) == (x->second.get_pattern()) ){//found the match again
                    int len = x->first.length();
                    for(int i = 0; i < len; i++){
                        delta[x->first[i]]=y->second[i];
                    }
                }//end if

            }//end for (dict_map)
            
        }

    }//end for (ciph_map)
}