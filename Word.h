#include <string>
#include <unordered_map>
class Word
{
private:
  std::string word_str;
  std::pair<int, int> stats;//first = length, second = unique letters
  std::unordered_multimap<char, int> pos_map;
  std::string pattern; //Order of appearance of letters: e.g. hello -> abccd, perspicacity -> abcdaefgfahi

public:
  //CONSTRUCTOR
  Word(std::string);

  //INSERT CREDENTIALS
  void set_word(std::string);

  //GETS
  std::string get_word() { return word_str; }
  int get_uniq() { return stats.second; }
  int get_len() { return stats.first; }
  std::string get_pattern() const { return pattern; };


  //OVERLOADED== OPERATOR (for use in hashing)
  bool operator==(const Word &i) const {
    return ( i.stats.first == this->stats.first //length
          && i.stats.second == this->stats.second ); // unique letters
    //Need a way to compare the values contained in the buckets
    // regardless of key value
  }

  //give access of private vars to the hash function
  friend struct std::hash<Word>;

};

//The hash. Simple enough to get the overloaded == operator to work.
// "That'll do, pig, that'll do."
namespace std{
  template<>
    struct hash<Word> {
        std::size_t operator()(const Word& k) const{
            return ((std::hash<std::string>()(k.word_str)
                   ^ (std::hash<int>()(k.stats.first) << 1)) >> 1) //length
                   ^ (std::hash<int>()(k.stats.second) << 1); //unique letters
        }
    };
}
