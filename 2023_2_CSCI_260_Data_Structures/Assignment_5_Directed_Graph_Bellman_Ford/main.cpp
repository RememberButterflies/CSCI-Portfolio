/**
 * @file main.cpp
 * @author Patrick McGrath, VIU
 * @version 1.0
 * @date November, 2023
 * 
 *  Assignment #5 - Directed Graph (Bellman Ford) Program
 *  Copyright (C) 2023  Patrick McGrath
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include "assignment5.cpp"

// prompts
std::string intro = "Enter information about Directed Graph";
std::string qverts = "How many vertices are there?";
std::string qedges = "How many edges are there?";
std::string qsordes = "Enter source and destination for next edge";
std::string qweight = "Enter weight for the edge from ";
std::string opt = "Please enter a choice between 0 and 4";
std::string opt1 = "Enter 1 for breadth first search";
std::string opt2 = "Enter 2 for depth first search";
std::string opt3 = "Enter 3 to Detect cycle in the graph";
std::string opt4a = "Enter 4 to find shortest distance using Bellman Ford";
std::string opt4b = "and detect cycle if it is there";
std::string opt0 = "Enter 0 to exit";
std::string choice = "Enter your choice";



// helper function for displaying prompts
void options();
void options(){
    std::cout << opt << std::endl;
    std::cout << opt1 << std::endl;
    std::cout << opt2 << std::endl;
    std::cout << opt3 << std::endl;
    std::cout << opt4a << std::endl;
    std::cout << opt4b << std::endl;
    std::cout << opt0 << std::endl;
}



int main(){
    //allocate memory for the graph structure
    //allocate vertices to graph->numVertices
    //create array of pointers equal to number of vertices that are pointing towards structure node 
    //graph->adjLists =  (struct node **)malloc(vertices * sizeof(struct node*));
    //initialize each these pointers to NULL

    // make graph
    //   struct Graph* graph = new Graph;

    // intro
    std::cout << intro << std::endl;

    // getting number of vertices and edges
    int edges = 0;
    int verts = 0;
    std::cout << qverts << std::endl;
    std::cin >> verts;
    std::cout << qedges << std::endl;
    std::cin >> edges;

    struct Graph* graph = createAGraph(verts);
    // adding edges and vertices
    for (int i=1; i<=edges; i++){
        int sor;
        int des;
        int wgt;
        std::cout << qsordes << std::endl;
        std::cin >> sor;
        std::cin >> des;
        std::cout << qweight << sor << " to " << des << std::endl;
        std::cin >> wgt;
        addEdge(graph, sor, des, wgt);
    }

    // after adding edges, show graph
    printGraph(graph);



    // user interaction
    std::string input = "99";
    int tint;
    options();
    std::cout << choice << std::endl;
    std::cin >> input;
    // while loop, until input is 0, will repeat
    while (input != "0"){
        // convert input string to int for switch
        // if outside of range, sets to 99 to replay options
        tint = std::stoi(input);
        if (tint < 0 || tint > 4){
            tint = 99;
        }

        // switch cases
        switch (tint){
            int t2;
            case 1:     // BFS
                std::cout << "Enter a source node to start BFS" << std::endl;
                std::cin >> t2;
                BFS(graph, t2);
                break;
            case 2:     // DFS
                {std::cout << "Enter a source node to start DFS" << std::endl;
                std::cin >> t2;
                int vis[graph->numVertices];
                for (int i=0; i<(graph->numVertices); i++){
                    vis[i] = 0;
                }
                DFS(graph, t2, vis);
                }
                std::cout << "End" << std::endl;
                break;
            case 3:     // cycle detect
                {
                    int t4 = 0;
                    for (int i=0; i<(graph->numVertices); i++){
                        std::cout << "Cycle check for vertex " << i << std::endl;
                        int vis[graph->numVertices];
                        int fin[graph->numVertices];
                        for (int i=0; i< (graph->numVertices); i++){
                            vis[i] = 0;
                            fin[i] = 0;
                        }
                        bool t3 = cycleDetect(graph, i, fin, vis);
                        if (t3 == 1){
                            std::cout << i << ". Cycle detected" << std::endl;
                        }
                        t4 += t3;
                        std::cout << std::endl;
                    }
                    if (t4 == 0){
                        std::cout << "End. No cycle detected." << std::endl;
                    } else {
                        std::cout << "End. Cycle detected." << std::endl;
                    }
                }
                break;
            case 4:     // bellmanford
                std::cout << "Enter source node for finding shortest distance from" << std::endl;
                std::cin >> t2;
                bellmanford(graph, t2);
                break;
            case 99:    // repeat options
                options();
                break;
            default:
                break;
        }

        // input for next choice
        std::cout << choice << std::endl;
        std::cin >> input;
    }

    //free memory
    freegraph(graph);


    //goodbye
    std::cout << "Goodbye" << std::endl;
    return 0;
}