#include <iostream>
#include <cstring>
#include <climits>
#define V 8					// 8 vertices





int MinDistance(int sd_set[], bool visited_set[])
{
    // initializes min value
    int min = INT_MAX;
    int min_index = -1;

    // go through the vertices and find the min values and min index
    for (int v = 0; v < V; v++)
    {
        if (!visited_set[v] && sd_set[v] <= min)
        {
            min = sd_set[v];
            min_index = v;
        }
    }

    return min_index;
}


void PrintSolution(int sd_set[], std::string city[], int source)
{
    puts("");

    for (int v = 0; v < V; v++)
    {
        std::cout << "distance from " << city[source] << " -> " << city[v] << " : " << sd_set[v] << std::endl;
    }
}


void Dijkstra(int graph[V][V], std::string city[], int source)
{
    // output -> shortest path "srouce -> i"
    int sd_set[V];

    // [i] will be true if [i] is a subset of shortest path
    bool visited_set[V];

    // initializes the result to inf.
    // initializes the shortest path checker to False
    for (int v = 0; v < V; v++)
    {
        sd_set[v] = INT_MAX;
        visited_set[v] = false;
    }

    // [source] is where the starting node is
    sd_set[source] = 0;

    // find shortest path for all V, O(V^2) time
    for (int counter = 0; counter < V - 1; counter++)
    {
        // process the frontier node with minimum cost
        int u = MinDistance(sd_set, visited_set);

        // mark the u "done" after processing
        visited_set[u] = true;

        // then updates the neibouring nodes of u
        for (int v = 0; v < V; v++)
        {
            if
                (
                    !visited_set[v]       &&                // not already in the shortest path set
                    graph[u][v]           &&                // there exists a path between u -> v
                    sd_set[u] != INT_MAX  &&                // filters out unreachable vertices
                    sd_set[u] + graph[u][v] < sd_set[v]     // traverse to u has a lower cost
                )
            {
                sd_set[v] = sd_set[u] + graph[u][v];
            }
        }
    }

    PrintSolution(sd_set, city, source);
}


int main()
{
	std::string city[V] = { "Ajax", "Brampton", "Markham", "Missisauga", "Pickering", "Richmond Hill", "Toronto", "Vaughan" };

    int graph[V][V]
    = {
            {0,0,30,0,10,25,0,0},
            {0,0,0,25,0,15,40,30},
            {30,0,0,0,15,15,25,20},
            {0,25,0,0,0,25,40,0},
            {10,0,15,0,0,16,20,20},
            {25,30,15,25,16,0,35,13},
            {0,43,30,45,20,35,0,30},
            {0,25,20,0,20,13,30,0}
    };

    int source = 4;

    Dijkstra(graph, city, source);
}