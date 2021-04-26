// g_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
// the program wich generated the input file is in the g_proj_generator folder

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iterator>
#include <limits>
#include <utility>
#include <algorithm>
using namespace std;


vector<int> dijkstra(int begin, int end, vector<vector<pair<int, double>>>& edges)
{
    vector<double> distances(edges.size(), -1); //vector, where the ith element means how much steps needed to reach the ith node
    vector<int> previous(edges.size(), -1); //vector, where the ith element means which was the node visited before the ith node
    vector<int> gray;  //vector, where the elements are the nodes that are gray at the moment
    distances[begin] = 0;   //the begin node is 0 steps far from itself
    gray.push_back(begin);   //first the only gray node is the begin node

    while (gray.size() != 0)
    {
        int i = 0;  // look for the element of gray that has the minimum distance from the begin node
        for (int j = 1; j < gray.size(); j++)
        {
            if (distances[gray[j]] < distances[gray[i]])
            {
                i = j;
            }
        }
        int current = gray[i]; //choose the next node where we take a step
        gray.erase(gray.begin() + i); //delete the current node from gray

        vector<pair<int, double>> neighbours = edges[current]; //the neighbours of the current node

        for (int j = 0; j < neighbours.size(); ++j)  //look at the neighbours of the current node
        {
            if (distances[neighbours[j].first] < 0) //if its a new node in gray, we
            {
                gray.push_back(neighbours[j].first);   //add it to gray
                distances[neighbours[j].first] = distances[current] + neighbours[j].second;  //with distance of the way we came here
                previous[neighbours[j].first] = current;   //and save that the node from wich we came here was the current node
            }
            else if (distances[neighbours[j].first] > distances[current] + neighbours[j].second)  //if it is already in gray, we need to know if we found a shorter path to it, or not
            {
                distances[neighbours[j].first] = distances[current] + neighbours[j].second;  //if the new path is shorter we modify the distance and the previous node of this node
                previous[neighbours[j].first] = current;
            }
        }
    }

    vector<int> path;

    if (previous[end] < 0)   // Cannot reach end
    {
        return path;    //return an empty path
    }
    path.push_back(end);    // Can reach end
    int temp=end;
    while (temp != begin)     //make the shortest path from end to begin
    {
        temp = previous[temp];
        path.push_back(temp);
    }
    reverse(path.begin(), path.end());   //reverse this shortest path to get what we need

    return path;
}


int main()
{
    vector<vector<pair<int, double>>> edges; // http://www.cplusplus.com/reference/utility/pair/

    std::ifstream input("input.txt");
    if (input.is_open())
    {
        int begin;
        int end;
        int n;
        int m;

        input >> begin >> end >> n >> m;  //The first line of the generated input file includes the begin node, the end node, the number of nodes and the number of edges
        edges.resize(n);

        for (int i = 0; i < m; ++i)   //read in the edges (from, to, length)
        {
            int a, b;
            double len;
            input >> a >> b >> len;
            edges[a].push_back(make_pair(b, len));
        }

        vector<int> shortest_path = dijkstra(begin, end, edges);

        std::ofstream output("dijkstra.txt");
        if (output.is_open())
        {
            std::copy(shortest_path.begin(), shortest_path.end(), std::ostream_iterator<int>(output, "\n"));
        }
        else { std::cout << "Could not open output file\n"; }

    }
    else { std::cout << "Could not open input file\n"; }

    return 0;
}
