# Alphabet Cipher Decryption

A goofy side project to read from a dictionary list of your choice and spit out an decrypted message from a string encrypted with an alphabet cipher (a 1-to-1 character replacement).

## Getting Started

You can use whatever dictionaries you like, and if you want to encode something in an alphabet cipher yourself, knock yourself out.
The dictionaries I use come from the fine people at http://www.gwicks.net/dictionaries.htm, I just modified them to be usable on Windows.
Should you be running this on a Unix/Linux machine, you may want to get them directly from the source.

### Prerequisites

C++14

### Installing

I've been compiling with g++, with C++14 (though I suspect C++11 should also work)

Just run the makefile.

## Running the tests

As of my last commit, it can spit out a file called out.txt - if you call that function in main.cpp - which contains an exhaustive list of every match the program finds among similarly-structured words.  Right now it will run one pass of the decode function which is only effective if there is only one match found for any given word.  More updates to come.
I've been using 'eng.txt' as my dictionary, but if you find a better one, feel free to use it (and modify the main.cpp to recognize another dictionary file)

Enter the dictionary file, then the ciphered text file.


## Built With

* C++
* All the care and delicacy of a WWE Smackdown Wrestler taking on a cactus


## Contributing

HMU: tston529 (at) live (dot) kutztown (dot) edu

## Authors

* **Tyler Stoney** - *Initial work*

## License

No licensing as of yet, I doubt this is going anywhere. Feel free to use, modify, fiddle around with it, go nuts.

## Acknowledgments

* A tip of the hat to anyone who helps
* A wag of the finger to anyone who tries to pass off my garbage as their own garbage
* etc.

Again, credit for the dictionary lists goes to the http://www.gwicks.net/dictionaries.htm
