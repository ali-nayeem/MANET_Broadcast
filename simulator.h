#ifndef SIMULATOR_H
#define	SIMULATOR_H
#include <queue> 
#include<vector>
#include <random>
#include"node_info.h"
using namespace std;
class Simulator
{
public:
	Simulator(double _X,double _Y,int _numberOfNodes): X(_X),Y(_Y), numberOfNodes(_numberOfNodes)
	{
		do
		{
			generateNodes();
			generateNeighborList();
		}while(!checkConnectivity());
	}
	void generateNodes()
	{
		//default_random_engine generatorX;
		//default_random_engine generatorY;
		//uniform_int_distribution<int> distributionX(0,(int)X);
		//uniform_real_distribution<double> distributionY(0.0,Y);
		nodeList.clear(); // a serious bug solved Alhamdulillah
		for(int i = 0; i<numberOfNodes ; i++)
		{
			nodeList.push_back( NodeInfo(distributionX(generatorX),distributionX(generatorX),i) );
		}
	}
	void generateNeighborList()
	{
		for(int i = 0; i< numberOfNodes; i++ )
		{
			for(int j = i+1; j<numberOfNodes; j++)
			{
				if(nodeList[i].isNeighbor(nodeList[j]))
				{
					nodeList[i].neighborList.push_back(j);
					nodeList[j].neighborList.push_back(i);
				}
			}
		}
	}
	bool checkConnectivity()
	{
		vector<int> visitedList(numberOfNodes,0);
		deque<int> Q;
		Q.push_back(0);
		visitedList[0]=1;
		while(!Q.empty())
		{
			int node = Q.front();
			Q.pop_front();
			for(int i=0; i<nodeList[node].neighborList.size();i++)
			{
				int neighbor = nodeList[node].neighborList[i];
				if(!visitedList[neighbor])
				{
					Q.push_back(neighbor);
					visitedList[neighbor]=1;
				}
			}
		}
		bool connected = true;
		for(int i=0;i<numberOfNodes;i++)
		{
			if(!visitedList[i])
			{
				connected = false;
				break;
			}
		}
		return connected;
	}
	template<class BALGO> void initiateBroadcast(int sourceId, vector<BALGO> & bAlgoList)
	{
		priority_queue<int> pQueue;
		for(int i=0; i<numberOfNodes;i++)
		{
			bAlgoList.push_back(BALGO(nodeList[i]));
		}

		bAlgoList[sourceId].received();
		//pQueue.push(sourceId);
		bAlgoList[sourceId].broadcast(pQueue, bAlgoList );
		while(!pQueue.empty())
		{
			BALGO & next = bAlgoList[pQueue.top()];
			pQueue.pop();
			next.forward(pQueue,bAlgoList);
		}
	}
	template<class BALGO> double calculateRedundancy(vector<BALGO> & bAlgoList)
	{
		double sumOfFraction=0;
                int totalForwardingNodes=0;
		for(int i=0;i<numberOfNodes;i++) //for each *forwarding* node
		{
                    if( bAlgoList[i].isForwarded() )
                    {
                        totalForwardingNodes++;
			int forwardingNeigbors=0;
			for(int j=0; j<bAlgoList[i].info.neighborList.size();j++) //for each neighbor
			{
				if( bAlgoList[ bAlgoList[i].info.neighborList[j] ].isForwarded() )
				{
					forwardingNeigbors++;
				}
			}
			sumOfFraction = sumOfFraction + 1.0*forwardingNeigbors/bAlgoList[i].info.neighborList.size();
                    }
		}
		return sumOfFraction/totalForwardingNodes;
	}
private:
	double X,Y;
	int numberOfNodes;
	vector<NodeInfo> nodeList;
	static default_random_engine generatorX;
		//default_random_engine generatorY;
	static uniform_int_distribution<int> distributionX;
};
#endif	/* SIMULATOR_H */