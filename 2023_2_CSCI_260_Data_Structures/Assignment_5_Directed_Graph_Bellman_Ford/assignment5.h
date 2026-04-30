/**
 * @file assignment5.h
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

#include <cstddef>

// Nodes
struct node {
  int vertex;
  int weight;
  struct node* next;
};


struct Graph {
  int numVertices;
  struct node** adjLists;
};

// Function declarations
// Create a new node
struct node* createNode(int v, int w); 



// Create an empty graph with number of vertices passed
struct Graph* createAGraph(int vertices);

  

// Add edge in graph from vertex s to vertex d
void addEdge(struct Graph* graph, int s, int d, int w); 

  

// Print the graph
void printGraph(struct Graph* graph);


//depth-first search
void DFS(struct Graph* graph, int vertex, int vis[]);

  


//BFS
void BFS(struct Graph* graph, int startVertex);

      



void bellmanford(struct Graph* g,int s);




//cycle detection in directed graph
bool cycleDetect(struct Graph* graph,int vertex, int fin[], int vis[]);



//free memory 
void freegraph(struct Graph* graph);