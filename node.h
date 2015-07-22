#ifndef NODE_H
#define	NODE_H
#include <algorithm>
#include <set>
#include <iterator>
#include"node_info.h"
#include"simulator.h"

using namespace std;

class Node
{
public:
	const NodeInfo & info;
	Node(NodeInfo & _info): info(_info)
	{
		packetForwarded = packetReceived = false;
	}
	bool isForwarded()
	{
		return packetForwarded;
	}
	void received()
	{
		packetReceived = true;
	}
protected:
	bool packetForwarded;
	bool packetReceived;
	//int getCount;
};

class SBA: public Node
{
public:
	SBA(NodeInfo & _info): Node(_info)
	{
		neighborsToCover = set<int>(info.neighborList.begin(), info.neighborList.end());
	}
	void send(priority_queue<int> & Q, vector<SBA> & NodeList, int senderId )
	{
		SBA & sender = NodeList[senderId];
		set<int> senderNeighbors(sender.info.neighborList.begin(),sender.info.neighborList.end());
		senderNeighbors.insert(senderId);
		set<int> result;
		set_difference(neighborsToCover.begin(), neighborsToCover.end(), senderNeighbors.begin(), senderNeighbors.end(),
		inserter(result, result.end()));
		neighborsToCover = result;
		
		if(!packetReceived)
		{
			received();
			Q.push(info.id);
		}

	}
	void forward(priority_queue<int> & Q, vector<SBA> & NodeList)
	{
		if(!neighborsToCover.empty())
		{
			packetForwarded = true;
			broadcast(Q,NodeList);
		}
	}
	void broadcast(priority_queue<int> & Q, vector<SBA> & NodeList)
	{
		for(int i=0;i<info.neighborList.size();i++)
		{
			SBA & neighbor = NodeList[info.neighborList[i]];
			neighbor.send(Q,NodeList,info.id);
		}
	}
private:
	set<int> neighborsToCover;

};

#endif	/* NODE_H */