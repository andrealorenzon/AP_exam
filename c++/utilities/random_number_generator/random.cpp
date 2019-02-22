#include <iostream>
#include <random>
#include <set>

using namespace std;

long long int llRand()   // random number between 0 and 10^18
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<long long int> dis(1, 1000000000000000000);   // 10^18
    
    return dis(gen);
}

int main(int argc, char const *argv[])
{
	std::set<int>Totale;

	for (int i=0; i <1000000;i++ ){
		Totale.insert(llRand());
	}


	cout << Totale.size();
	return 0;
}