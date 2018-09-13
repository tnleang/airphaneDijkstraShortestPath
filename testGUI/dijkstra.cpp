#include "dijkstra.h"

Dijkstra::Dijkstra()
{

}

void Dijkstra::dijkstra(CoorDigraph &g, int source)
{
    sourceID = source;
    vertex v;
    distances.resize(g.vertex(),std::numeric_limits<double>::infinity());
    edgesG.resize(g.vertex());
    distances[source] = 0;
    pq.push(vertex(source));


    while(!pq.empty())
    {
        v = pq.top();
        pq.pop();
        for (const auto &e : g.getEdges(v.index))
            //list.begin ; !list.end() ; keep moving the node in the list
        {

            double alt = distances[v.index] + e.weight;
            if(alt < distances[e.destination])
            {
                distances[e.destination] = alt;
                pq.push(vertex(e.destination,alt));
                edgesG[e.destination] = v;
                edgesG[e.destination].destination = e.source;
                edgesG[e.destination].source = e.destination;
                edgesG[e.destination].weight = e.weight;
                edgesG[e.destination].airlineID = e.airlineCode;
            }
        }
    }
}

double Dijkstra::distanceTo(int destination)
{
    return distances[destination];
}

stack<vertex> Dijkstra::pathTo(int destination)
{
    stack<vertex> path;
    for(vertex v= edgesG[destination]; v.index != -1; v = edgesG[v.index])
    {
        path.push(v);
    }
    return path;
}
