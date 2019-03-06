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
#include <chrono>
#include <random>

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

size_t llRand()   // random number between 0 and 10^18
{
    std::random_device rd;              //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());             //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<size_t> dis(1, 1000000000000000);   // 1-10^15

    return dis(gen);
}



int main (int argc, char* argv[])
{

  if (argc==1) {
        std::cout << "wrong number of args. expects 3" << std::endl;
        return 0;}

	// initialize random seed
	srand (static_cast<unsigned>(time(NULL)));

	//read iterations and string length from argv
	const  int iterations = std::atoi(argv[1]);
	const  int str_length = std::atoi(argv[2]);
	const int readtoo 	  = std::atoi(argv[3]);
	std::string dummy_value = "";

	//create an empty map
  	std::map<size_t,std::string> myMap;

  	//populate the map
  	for (int counter = 0; counter < iterations; ++counter ) 
  	{
  		size_t index = llRand();
        auto value = random_string(str_length);
        myMap[index] = value;
  	}
  
  	std::cout << "Map populated with " << iterations << " elements." << std::endl;

    // benchmark for lookup time after balance
    
    size_t testKey = 424242424242424242;

    std::cout << "looking for my droids after balance... " ;
    //std::cout << std::chrono::high_resolution_clock::period::den << std::endl;
    auto start_time2 = std::chrono::high_resolution_clock::now();
    std::cout << myMap[testKey] << std::endl;
    auto end_time2 = std::chrono::high_resolution_clock::now();
    std::cout << "The droids found with a lookup time of "  ;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time2 - start_time2).count() << " nanoseconds" << std::endl;


  	// retrieve all data in random order if readtoo = 1
  	if (readtoo) {
	  	for (const auto& p : myMap)
			{
			  dummy_value = p.second;
			}
	}
  return 0;
}
