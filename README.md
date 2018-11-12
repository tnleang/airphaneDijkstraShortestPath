# airphaneDijkstraShortestPath
A "real world" use of Dijkstra's Algorithm is trying to find the shortest path between any two
airports on the face of the planet. Having been a "frequent flyer" when I worked for the U.S.
Government, my "definition" of shortest path was the least amount of time spent in airports
waiting for a connecting flight. Hence, one time to make it to Washington, D.C. in the "shortest
time," I flew from Los Angeles to Chicago to New York to Dulles; as in no "direct flights" from
Los Angeles to Washington, D.C. were available that would get me in front of the Admiral with
enough time to spare. (The actual "shortest distance flight was Los Angeles to Atlanta to
Washington, D.C., but that had a five hour lay over in Atlanta and would have put me in
Washington, D.C. one hour before the meeting; conversely, my flight plan had just minutes so
spare between landing and take off and gave me hours to rest before the meeting)
You, and up to 2 partners, must implement Dijkstra'a algorithm to find the "shortest path"
between any two airports. http://openflights.org/data.html has all of the information that you will
need --- airport designators, airline designators, airline routes and so forth. If multiple airlines
serve the same route, such as Delta and British Airways from Los Angeles to London, BOTH
routes must be printed in order to give the end-user a choice of airlines (frequent flyer miles
really pay off!)
The input for your program must be a valid airport code for the origin and a valid airport code
for the destination.
The output must be an itinerary, such as:
Leave LAX (Los Angeles) on American Airways after flying 2,500 miles
Change planes at ANT (Atlanta) to American Airlines and fly 1,000 miles
Arrive at MIA (Miami)
