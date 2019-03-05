#include "binary_tree.h"
#include <iostream>

std::string random_string( size_t length ) /*!< generates a random string of given length, for benchmarking purposes */
{
    auto randchar = []() -> char  //neat lambda function
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

    //test removeNode

        std::cout << "\nTEST remove node with two children:\n";
        Tree<int, int> tree2;
        tree2.insert(10, 1);
        tree2.insert(6, 1);
        tree2.insert(16,1);
        tree2.insert(14, 1);
        tree2.insert(18, 1);
        tree2.insert(4, 1);
        tree2.insert(2, 1);
        tree2.insert(19, 1);

    std::cout << "Remove node 212 and 18.\n";
        tree2.removeNode(212);
        tree2.removeNode(18);
        tree2.listNodes();
    std::cout << "\nremoveNode test completed\n";
    //test llRand
    //std::cout << "llRand test: --> " << llRand() << std::endl;

    //read iterations and string length from argv
    const  int iterations = std::atoi(argv[1]);
    const  int str_length = std::atoi(argv[2]);
    const  int readtoo    = std::atoi(argv[3]);
    std::string dummy_value = "";

    //create an empty tree
    Tree <size_t,std::string> myMap;



    //populate the map
    for (int counter = 0; counter < iterations; ++counter )
    {
        size_t index = llRand();
        auto value = random_string(str_length);
        myMap.insert(index, value);
    }

    size_t testKey = 424242424242424242;

    myMap.insert(testKey,"These are indeed the droids you are looking for.");
/*
    std::cout << "Tree populated with " << iterations << " elements." << std::endl;

    // retrieve all data in random order if readtoo = 1
    if (readtoo) {
          std::cout << "My tree: \n ---------- \n" << myMap << std::endl;
    }

    // lookup time before balance:

    std::cout << "looking for my droids before tree balance... " ;
    auto start_time = std::chrono::high_resolution_clock::now();
    std::cout << myMap.find(testKey)->value << std::endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "The droids found with a lookup time of "  ;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " nanosec" << std::endl;


    //test
    //auto v = myMap.arrayOfNodes();
    std::cout << "Tree height before balance: " << myMap.height << std::endl;
    myMap.balance();
    std::cout << "Tree height after balance: " << myMap.height << std::endl;

    // benchmark for lookup time after balance

    std::cout << "looking for my droids after balance... " ;
    //std::cout << std::chrono::high_resolution_clock::period::den << std::endl;
    auto start_time2 = std::chrono::high_resolution_clock::now();
    std::cout << myMap.find(testKey)->value << std::endl;
    auto end_time2 = std::chrono::high_resolution_clock::now();
    std::cout << "The droids found with a lookup time of "  ;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time2 - start_time2).count() << " nanoseconds" << std::endl;
*/
    std::cout << " ---------- copy/move semantics test -----------" << std::endl;
    
    auto tree3(myMap);
    
    std::cout << tree3 << " --- \n" << tree3.height;
    tree3.balance();
    std::cout << "balanced : " << tree3.height << std::endl;
  return 0;
}
