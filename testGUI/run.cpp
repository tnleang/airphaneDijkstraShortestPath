#include "run.h"

Run::Run()
{
    QFile airportIn("airports.xml");
    QFile routeIn("routes.xml");
    QFile airlineIn("airlines.xml");
    if(!airportIn.open(QFile::ReadOnly | QFile::Text))
    {
       qDebug() << "Cannot read airport file" << airportIn.errorString();
       exit(0);
    }
    if(!routeIn.open(QFile::ReadOnly | QFile::Text))
    {
       qDebug() << "Cannot read airport file" << routeIn.errorString();
       exit(0);
    }
    if(!airlineIn.open(QFile::ReadOnly | QFile::Text))
    {
       qDebug() << "Cannot read airport file" << airlineIn.errorString();
       exit(0);
    }
    QXmlStreamReader reader(&airportIn);
    QList< QMap<QString,QString> > info;
    int count = 0; //counting the total airport
    /* We'll parse the XML until we reach end of it.*/
    //reader.readNext();

    while(!reader.atEnd())
    {
        count++;
        reader.readNextStartElement();
        if(reader.tokenType() == QXmlStreamReader::StartDocument)
        {
            qDebug()<<"Just read a Start Document Token";
            continue;
        }
        if(reader.name() != "airport")
            continue;
        info.append(parse(reader));

        airport airportVertex(info.last().value("id").toInt(),
                              info.last().value("city").toStdString(),
                              info.last().value("iata").toStdString());  //convert QString to std::string
        airportVertex.lat = info.last().value("latitude").toDouble();
        airportVertex.lon = info.last().value("longitude").toDouble();
        airportID[airportVertex.name] = airportVertex.ID;
        airportList[airportVertex.ID] = airportVertex;

    }

    reader.setDevice(&airlineIn);
    while(!reader.atEnd())
    {
        reader.readNextStartElement();
        if(reader.tokenType() == QXmlStreamReader::StartDocument)
        {
            qDebug()<<"Just read a Start Document Token";
            continue;
        }
        if(reader.name() != "airline")
            continue;
        info.append(parse(reader));
        airlineID[info.last().value("airlineid").toInt()] = airline(info.last().value("airlineid").toInt(),
                                                                    info.last().value("name").toStdString(),
                                                                    info.last().value("icao").toStdString());
    }

    reader.setDevice(&routeIn);
    while(!reader.atEnd())
    {
        reader.readNextStartElement();
        if(reader.tokenType() == QXmlStreamReader::StartDocument)
        {
            qDebug()<<"Just read a Start Document Token";
            continue;
        }
        if(reader.name() != "route")
            continue;
        info.append(parse(reader));

        int source = info.last().value("sourceAirportID").toInt();
        int destination =info.last().value("destinationAirportID").toInt();
        graph.addEdge(airportList[source].ID,
                      airportList[destination].ID,
                      distanceCalculation(airportList[source].lat,
                                          airportList[source].lon,
                                          airportList[destination].lat,
                                          airportList[destination].lon)
                      ,info.last().value("airlineID").toInt());
    }
    graph.resize(9541);



}



QMap<QString, QString> Run::parse(QXmlStreamReader& reader)
{
    QMap<QString, QString> airport;

    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement
     */
    reader.readNext();
    while(reader.tokenType() != QXmlStreamReader::EndElement)
    {
        airport[reader.name().toString()] = reader.readElementText();
        //qDebug()<<reader.name().toString()<<" = "<<airport[reader.name().toString()];
        reader.readNext();
        if(reader.hasError())
        {
            qDebug()<<reader.errorString();
            exit(0);
        }
    }

    return airport;
}

stack<vertex> Run::getPath(string from, string to)
{
    Dijkstra dij;
    dij.dijkstra(graph, airportID[from]);
    stack<vertex> pathTo = dij.pathTo(airportID[to]);
    return pathTo;
}


void Run::showPath(string from, string to)
{
    Dijkstra dij;
    dij.dijkstra(graph, airportID[from]);
    cout << "From " << airportList[airportID[from]].name<< " " <<airportList[airportID[from]].city <<endl;
    cout << "Distance is "<< dij.distanceTo(airportList[airportID[to]].ID) << endl;
    cout << "To " <<airportList[airportID[to]].name <<" "<< airportList[airportID[to]].city <<endl;

    stack<vertex> pathTo = dij.pathTo(airportID[to]);
    while(!pathTo.empty())
    {
        vertex v = pathTo.top();
        pathTo.pop();
        cout << "From "<<airportList[v.destination].name<<"("<<airportList[v.destination].city << ") to ";
        cout << airportList[v.source].name<<"("<<airportList[v.source].city << ")";
        cout << " for " << v.weight << " miles";
        for(auto x: graph.getEdges(v.source))
            if(v.destination == x.destination)
                if (airlineID[x.airlineCode].name != "")
                cout <<"\n\t" << "  " << airlineID[x.airlineCode];
        cout << endl<<endl<<endl;

        cout << endl;

    }
}

map<string,int> Run::getAirportList() const
{
    return airportID;
}

airport Run::getAirport(int index) const
{
    return airportList.at(index);
}

int Run::getAirportID(string iata) const
{
    return airportID.at(iata);
}
list<weightEdge> Run::getEdges(int source)
{
    return graph.getEdges(source);
}
airline Run::getAirline(int index) const
{
    return airlineID.at(index);
}
