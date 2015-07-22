#ifndef NODE_INFO_H
#define	NODE_INFO_H
#include<vector>
#include<cmath>

using namespace std;

class NodeInfo
{
public:
	double x,y;
	int id;
	static double transmissionRange;
	vector<int> neighborList;

	//methods
	NodeInfo(double _x, double _y, int _id): x(_x),y(_y),id(_id)
	{
	}
	bool isNeighbor(NodeInfo & aNode)
	{
		double distance = (x-aNode.x)*(x-aNode.x) + (y-aNode.y)*(y-aNode.y);
		return (distance <= transmissionRange*transmissionRange);
	}

};

#endif	/* NODE_INFO_H */