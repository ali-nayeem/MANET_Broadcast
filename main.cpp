#include<iostream>
#include <set>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>  
#include"node_info.h"
#include"simulator.h"
#include"node.h"

using namespace std;

/*******************PARAMETERS***********************/
#define TRANSMISSION_RANGE 21.0 
#define AX 100
//#define AY 100
//#define NUMBER_OF_NODES 70
#define NUMBER_OF_SCENARIO 1000
#define FRACTION_OF_SOURCE 1.0


/***********************STATIC MEMBERS*****************************/
double NodeInfo::transmissionRange = TRANSMISSION_RANGE;
default_random_engine Simulator::generatorX;
uniform_int_distribution<int> Simulator::distributionX(0,(int)AX);

// random generator function:
int myrandom (int i) { return rand()%i;}
double calculateRedundancy(int numOfNodes)
{
	vector<int> sourceList;
	for(int i=0;i<numOfNodes;i++)
	{
		sourceList.push_back(i);
	}
	double sum=0;
	for(int i=0;i<NUMBER_OF_SCENARIO;i++) //for each scenario
	{
		Simulator sim(AX,AX,numOfNodes);
		if(FRACTION_OF_SOURCE<1.0)
		{
			// using built-in random generator:
			random_shuffle ( sourceList.begin(), sourceList.end() );
		}
		for(int j=0;j<numOfNodes*FRACTION_OF_SOURCE;j++) //for each source node
		{
			vector <SBA> list;
			sim.initiateBroadcast(sourceList[j],list); //bottleneck
			sum = sum + sim.calculateRedundancy(list);
		}
	}
	return sum/(NUMBER_OF_SCENARIO*numOfNodes*FRACTION_OF_SOURCE);
}
int main()
{
	//srand ( unsigned ( std::time(0) ) );
	//Simulator sim(AX,AY,NUMBER_OF_NODES);
	//Simulator sim2(AX,AY,NUMBER_OF_NODES);
	//vector <SBA> list;
	//sim.initiateBroadcast(4,list);
	//cout<<sim.calculateRedundancy(list);
	cout<<TRANSMISSION_RANGE<<","<<NUMBER_OF_SCENARIO<<","<<FRACTION_OF_SOURCE<<", 70-200"<<endl;
	for(int i=70; i<=200; i+=10)
	{
		cout<<i<<","<<calculateRedundancy(i)<<endl;
	}

	return 0;
}