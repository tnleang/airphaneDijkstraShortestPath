#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include "graph.h"
#include <limits>
#include <queue>
#include <stack>

using namespace std;

struct vertex
{
    int index;
    int airlineID;
    int source, destination;
    double weight;

    vertex(int i = -1,int t = -1,double w = 0):index(i),weight(w),destination(t)
    {}

    friend
    bool operator<(const vertex& x,const vertex& y)
    {
        return x.weight>y.weight;
    }

    friend
    ostream& operator<<(ostream& out,const vertex& x )
    {
        out<<x.destination<<"["<<x.weight<<"]";
        return out;
    }
};

class Dijkstra
{
public:
    Dijkstra();

    void dijkstra(CoorDigraph &g, int source);

    double distanceTo(int destination);
    stack<vertex> pathTo(int destination);

    vector<vertex> path(int destination);


private:
    int sourceID;
    vector<double> distances;
    vector<vertex> edgesG;
    priority_queue<vertex> pq;

};

#endif // DIJKSTRA_H
