/**
 * @file assignment5.cpp
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
#include <queue>
#include <climits>
#include <stack>
#include "assignment5.h"


// function for creating node pointer in graph adjacency lists
// v is destination
// w is weight
// the list node is inserted in as the origin
// next is set it null
struct node* createNode(int v, int w){
  struct node* n = new node;
  n->vertex = v;
  n->weight = w;
  n->next = NULL;
  return n;
}



// Function for creating an empty graph pointer
// pass number of vertices
// creates adjacency lists with null pointer for each starting place in each list
struct Graph* createAGraph(int vertices){
  struct Graph* graph = new Graph;
  graph->numVertices = vertices;
  graph->adjLists = new node*[vertices]; 
  for (int i=0; i<vertices; i++){
    graph->adjLists[i] = NULL;
  }
    return graph;
}






// Add edge in graph from vertex s to vertex d, weight w
// creates new node passing destination and weight
// adds it to start of source's adjacency list
void addEdge(struct Graph* graph, int s, int d, int w){
  struct node* nnode = createNode(d, w);
  nnode->next = graph->adjLists[s];
  graph->adjLists[s] = nnode;
}

  




// Print the graph function
// goes through each adjacency list
// for each list, prints:
//  [source]-----([weight])---->[destination]
void printGraph(struct Graph* graph){
  for (int v=0; v<(graph->numVertices); v++){
    struct node* temp = graph->adjLists[v];
    while (temp != NULL){
      std::cout << v << "-----(" << temp->weight << ")---->" << temp->vertex << std::endl;
      temp = temp->next;
    }
    std::cout << std::endl;
  }
}





// function for depth first traversal
// pass pointer to graph, the starting vertex and an array the size of the graph all zeroes
void DFS(struct Graph* graph, int vertex, int vis[]){

  // create empty stack
  std::stack<int> st;

  // put starting vertex on stack, visit it and print it
  st.push(vertex);
  vis[vertex] = 1;
  std::cout << st.top() << "->";
  
  // while stack isnt empty
  // note top of stock, u
  // pop stack
  // point temp node at start of u's adjacency list
  //  then, while temp is not null,
  //  if v hasnt been visited, 
  //  push it to stack 
  //  DFS from u
  //  point temp to its next
  while (st.empty() != 1){
    int u = st.top();
    st.pop();
    node* temp = graph->adjLists[u];
    while (temp != NULL){
      if (vis[temp->vertex] == 0){
        st.push(temp->vertex);        // double push?
        DFS(graph, temp->vertex, vis);
      }
      temp = temp->next;
    }
  }
    return;
}
  







// function for breadth first traversal of graph
// pass pointer to graph and start vertex 
void BFS(struct Graph* graph, int startVertex){
  
  // create visited array size of the graph
  // set all to zero except startvertex
  int vis[graph->numVertices];
  for (int i=0; i <(graph->numVertices); i++){
    vis[i] = 0;
  }
  vis[startVertex] = 1;

  // start queue. push startvertex to it
  std::queue<int> q;
  q.push(startVertex);


  // while queue is not empty
  while (q.empty() != 1){
  // make currentvertex = to front of queue
  // print it
  // pop it
    int currentVertex = q.front();
    std::cout << currentVertex << "->";
    q.pop();

    // make temp node
    // go through adjacency list for currentertex
    // visit all in list and push them to queue
    node* temp = graph->adjLists[currentVertex];
    while (temp != NULL){
      if (vis[temp->vertex] == 0){
      q.push(temp->vertex);
      vis[temp->vertex] = 1;
      }
      temp = temp->next;
    }

  }

  // print end
    std::cout << "End" << std::endl;
    return;
}

      


// function for bellman-ford algorithm traversal and negative cycle detection of graph
// pass pointer to graph, and source vertex
void bellmanford(struct Graph* g,int s){


  // initalize 2 arrays, size = numvetices
  // shortest path all = int_max
  // predecessors all = -1
  // shortest to source = 0
  int shrt[g->numVertices];
  int pred[g->numVertices];
  for (int i=0; i<(g->numVertices); i++){
    shrt[i] = INT_MAX;
    pred[i] = -1;
  }
  shrt[s] = 0;


  // iterate numvetices-1 times
  // for each vertex in graph, relax it
  for (int i=0; i<((g->numVertices)-1); i++){

    // print iteration header
    std::cout << std::endl;
    std::cout << "For iteration " << i+1 << std::endl;

    // relax all edges
    for (int j=0; j<(g->numVertices); j++){

      // temp node starting at first node of first adjacencylist and going down as j increases
      node* temp = g->adjLists[j];

      while (temp != NULL){
        //relax

        // overflow avoidance:
        // if any variable is INT_MAX, a comparison using addition cannot be used. 
        // functionally, INT_MAX + a number is just INT_MAX
        if (shrt[temp->vertex] == INT_MAX && shrt[j] != INT_MAX){
          shrt[temp->vertex] = ((shrt[j]) + (temp->weight));
          pred[temp->vertex] = j;         
        } else if (shrt[j] != INT_MAX){
        
          if ((shrt[temp->vertex]) > ((shrt[j]) + (temp->weight))){
            shrt[temp->vertex] = ((shrt[j]) + (temp->weight));
            pred[temp->vertex] = j;
          }
        }
        // move to next node in current list
        temp = temp->next;
      }
    }

    // print out current iteration
    for (int i=0; i< g->numVertices; i++){
      std::cout << "Minimum cost distance to " << i << " is ";
      if (shrt[i] == INT_MAX){
        std::cout << "inf.";
      } else {
        std::cout << shrt[i];
      }
      std::cout << " and predecessor is " << pred[i] << std::endl;
    }
  }
  



  // cycle detect
  // 2 new arrays for one last run and comparison
  // copy contents of original arrays
  int shrt1[g->numVertices];
  int pred1[g->numVertices];
  for (int i=0; i<(g->numVertices); i++){
    shrt1[i] = shrt[i];
    pred1[i] = pred[i];
  }

  // run once
  for (int i=0; i<1; i++){

    // print header for negative cycle detect
    std::cout << std::endl;
    std::cout << "For iteration to detect negative cycles " << std::endl;

    // relax all edges
    for (int j=0; j<(g->numVertices); j++){

      // temp node starting at first node of first adjacencylist and going down
      node* temp = g->adjLists[j];

      while (temp != NULL){
        //relax

        // overflow avoidance
        if (shrt1[temp->vertex] == INT_MAX && shrt1[j] != INT_MAX){
          shrt1[temp->vertex] = ((shrt1[j]) + (temp->weight));
          pred1[temp->vertex] = j;         
        } else if (shrt1[j] != INT_MAX){
        
          if ((shrt1[temp->vertex]) > ((shrt1[j]) + (temp->weight))){
            shrt1[temp->vertex] = ((shrt1[j]) + (temp->weight));
            pred1[temp->vertex] = j;
          }
        }
        // move to next node in current list
        temp = temp->next;
      }
    }

    // print out current iteration
    for (int i=0; i< g->numVertices; i++){
      std::cout << "Minimum cost distance to " << i << " is ";
      if (shrt1[i] == INT_MAX){
        std::cout << "inf.";
      } else {
        std::cout << shrt1[i];
      }
      std::cout << " and predecessor is " << pred1[i] << std::endl;
    }
  }

  // compare shortest list arrays for change
  // one first change, print negative cycle detected and return
  for (int i=0; i < (g->numVertices); i++){
    if (shrt[i] != shrt1[i]){
      std::cout << "Negative cycle detected" << std::endl;
      return;
    } 
  }

    // if made it here, no cycle detected. print that
    std::cout << "No negative cycle detected" << std::endl;
    return;
}





//cycle detection in directed graph if traverse from a sourec node vertex
//pass pointer to graph, starting vertex and 2 arrays (fin and vis) size of graph each all set to 0
bool cycleDetect(struct Graph* graph,int vertex, int fin[], int vis[]){

    // print current vertex and visit it
    std::cout << vertex << "->";
    vis[vertex] = 1;

    // make temp node pointed at start of current vertex's adjacency list
    node* temp = graph->adjLists[vertex];

    // temp isnt null
    while (temp != NULL){

      // if temp hasnt been visited,
      //    call cycledetect from there
      //    if it returns true, 
      //        return true to this function call
      // else
      //    if temp hasnt been finished
      //        return true
      if (vis[temp->vertex] == 0){
        bool t = cycleDetect(graph, temp->vertex, fin, vis);
        if (t == true){
          return true;
        }
      } else {
        if (fin[temp->vertex] == 0){
          return true;
          }
        }

    // move temp to its next
    temp = temp->next;
    }

    // finish current vertex and return false
    fin[vertex] = 1;
    return false;
}






    //free memory
    //for each adjlist
    //    make a temp node pointed at front of list
    //    while temp isn't null, make a 2nd temp pointed at temp1's next
    //    delete temp1, then point it to temp2. repeat until they're all gone.
    //    delete the list itself. and then the graph.
void freegraph(struct Graph* graph){
    for (int i=0; i<(graph->numVertices); i++){
        struct node* temp1 = graph->adjLists[i];
        while (temp1 != NULL){
            struct node* temp2 = temp1->next;
            delete temp1;
            temp1 = temp2;
            if (temp1 != NULL){
            }
        }
    }
    delete[] graph->adjLists;
    delete graph;
    return;
}