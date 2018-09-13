#ifndef RUN_H
#define RUN_H

#include <iostream>
#include <cstdlib>
#include <QString>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QMap>
#include <vector>
#include <map>
#include <stack>

#include "graph.h"
#include "dijkstra.h"
#include "distanceformula.h"

using namespace std;

struct airport
{
    int ID;
    double lat, lon;
    string city, name;

    airport (int id = -1, string c = string(), string n = string()): ID(id), city(c), name(n)
    {}

    friend
    ostream& operator <<(ostream &out, const airport &x)
    {
        out << x.ID<<": "<<x.name << "(" << x.city << ")";
        return out;
    }
};

struct airline
{
    int ID;
    string name, country, ICAO;

    airline(int id = -1, string n = string(), string icao = string()):ID(id),name(n),ICAO(icao)
    {}

    friend
    ostream& operator <<(ostream &out, const airline &x)
    {
        out << x.name /*<<"[" << x.ICAO << "]"*/;
        return out;
    }
};


class Run
{
public:
    Run();
    void showPath(string from, string to);

    stack<vertex> getPath(string from, string to);
    map<string,int> getAirportList() const;
    airport getAirport(int index) const;
    int getAirportID(string iata) const;
    list<weightEdge> getEdges(int source);
    airline getAirline(int index) const;


private:

    CoorDigraph graph;
    map<string, int> airportID;
    map<int,airline> airlineID;
    map<int, airport> airportList;

    QMap<QString, QString> parse(QXmlStreamReader& reader);
};



#endif // RUN_H
