#include "graph.h"

CoorDigraph::CoorDigraph(int v):totalVertex(v),totalEdge(0)
{

}

int CoorDigraph::edges() const
{
    return totalEdge;
}

int CoorDigraph::vertex() const
{
    return totalVertex;
}

void CoorDigraph::resize(int v)
{
    totalVertex = v;
}

void CoorDigraph::addEdge(int source,int destination, double weight, int airlineCode)
{
    adj[source].push_back(weightEdge(source,destination,weight,airlineCode));
    ++totalEdge;
}

list<weightEdge> CoorDigraph::getEdges(int source)
{
    return adj[source];
}

void CoorDigraph::display()
{
    for(const auto &x: adj)
    {
        cout << x.first <<"|";
        for(const auto &y: x.second)
            cout <<"--"<< y.weight << "-->" << y.destination<< " ";
        cout << endl;
    }
}
