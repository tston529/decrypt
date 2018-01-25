# Alphabet Cipher Decryption

A goofy side project to read from a dictionary list of your choice and spit out an decrypted message from a string encrypted with an alphabet cipher (a 1-to-1 character replacement).

## Getting Started

Here's a few tidbits of information that may or may not be useful to you.


### Prerequisites

C++14

### Installing

I've been compiling with g++, with C++14 (though I suspect C++11 should also work)

Just run the makefile.

## Running the tests

As of my last commit, it can spit out a file called out.txt - if you call that function in main.cpp - which contains an exhaustive list of every match the program finds among similarly-structured words.  Right now it will run one pass of the decode function which is only effective if there is only one match found for any given word.  More updates to come.
I've been using 'eng.txt' as my dictionary, but if you find a better one, feel free to use it (and modify the main.cpp to recognize another dictionary file)


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
