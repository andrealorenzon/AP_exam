/*
std::map benchmark program
gets always 3 arguments:
1) numer_of_elements to put in the map 
2) length of string elements 
3) readtoo?(0/1) 0 = only populates the map, 1 = also read the values

COMPILE WITH -O0 to avoid optimization!

example

*/

#include <iostream>
#include <map>
#include <algorithm>

/*!< generates a random string of given length */
std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}





int main (int argc, char* argv[])
{
	// initialize random seed
	srand (time(NULL));

	//read iterations and string length from argv
	const  int iterations = std::atoi(argv[1]);
	const  int str_length = std::atoi(argv[2]);
	const int readtoo 	  = std::atoi(argv[3]);
	std::string dummy_value = "";

	//create an empty map
  	std::map<int,std::string> myMap;

  	//populate the map
  	for (int counter = 0; counter < iterations; ++counter ) 
  	{
  		long long int index = std::rand()*10^10+std::rand()*10*5+std::rand();
  		auto value = random_string(str_length);
  		myMap[index] = value;
  	}
  
  	std::cout << "Map populated with " << iterations << " elements." << std::endl;

  	// retrieve all data in random order if readtoo = 1
  	if (readtoo) {
	  	for (const auto& p : myMap)
			{
			  dummy_value = p.second;
			}
	}
  return 0;
}
