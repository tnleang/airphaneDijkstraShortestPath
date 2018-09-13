#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdlib>
#include <map>
#include <list>


using namespace std;

struct weightEdge
{
    int source, destination;
    double weight;
    int airlineCode;


    weightEdge(int s = -1, int d =1, double w = -1, int air = -1):source(s),destination(d),weight(w),airlineCode(air)
    {

    }

    friend
    bool operator <(const weightEdge &x, const weightEdge &y)
    {
        return x.weight > y.weight;
    }

};


class CoorDigraph
{
public:
    CoorDigraph(int v = 10);

    void addEdge(int source,int destination, double weight, int airlineCode = -1);
    int vertex() const;
    int edges() const;
    void resize(int v);
    list<weightEdge> getEdges(int source);
    void display();


private:
    int totalVertex;
    int totalEdge;

    map<int,list<weightEdge>> adj;
};


#endif // GRAPH_H
