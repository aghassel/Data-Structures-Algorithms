#include <stdio.h>
#include <stdlib.h>

// Global variable controls amount of console output. Set to non-zero if you
// want lots of information while program runs.
// (This variable is updated by an assignment in main().)
int verbose = 0;

typedef int Que_data;        // create queue filled with ints

#include "QueArry.h"
#define MAXVERTEX 12         // Set maximum number of vertices
#include "GraphBasic.h"


void breadthFirstSearch(int start)
// Do breadth-first search of global graph
{
    int i;
    int unvisitedVertex;
    Queue *ToVisit = create_queue(MAXVERTEX + 1);

    //mark first node as visited
    Vertices[start]->visited = GREY;

    //display vertex
    displayVertex(start);

    //insert vertex index in queue
    insert(ToVisit, start);

    while (!isQueueEmpty(ToVisit)) {
        //get vertex from front of unvisited queue
        int tempVertex;
        removefront(ToVisit, &tempVertex);

        //no adjacent vertex found
        while ((unvisitedVertex = getAdjUnvisitedVertex(tempVertex)) != -1) {
            Vertices[unvisitedVertex]->visited = GREY;
            displayVertex(unvisitedVertex);
            insert(ToVisit, unvisitedVertex);
        }
    }

    putchar('\n');
    printf("List of vertices that were not visited\n");
    for (i = 0; i < vertexCount; i++)
        if (Vertices[i]->visited == GREEN) displayVertex(i);
    putchar('\n');

    //queue is empty, search is complete, reset all visited flag
    resetVisitFlags();
    destroy_queue(&ToVisit);
}//BreadthFirstSearch()

//edge Remover
float delete(char startPOS, char endPOS) {
    int start, end;

    start = vertex_index_from_label(startPOS);
    end = vertex_index_from_label(endPOS);

    //returns -1 if start or end is -1
    if (start == -1 || end == -1) return -1;
    else {
        //edge checker
        if ((start < vertexCount) && (end <= vertexCount)) {
            if (adjMatrix[start][end] == 0) {
                if (verbose) printf("No edge to remove\n");
                return 0;
            }
            adjMatrix[start][end] = 0;

            if (verbose)
                printf("Remove edge between %c (%d) and %c (%d)\\n", Vertices[start]->label, start,
                       Vertices[end]->label,
                       end);
        }
    }
    return 0;
}

int main(void) {
    int v;
    char s, e;

    verbose = 0;            // Set to be talkative/not talkative during build

    resetGraph();
    addVertexLabels("SABCDEF");

    addEdgeByLabel('S', 'A');
    addEdgeByLabel('S', 'B');
    addEdgeByLabel('S', 'C');
    addEdgeByLabel('A', 'D');
    addEdgeByLabel('B', 'D');
    addEdgeByLabel('C', 'D');
    addEdgeByLabel('D', 'E');
    addEdgeByLabel('E', 'F');

    verbose = 1;            // now be talkative

    if (verbose) {
        // Display resulting adjacency matrix
        printf("Adjacency Matrix:\n");
        printAdjMatrix();
        putchar('\n');
    }

    printf("Breadth-first searches, starting at each vertex\n");
    for (v = 0; v < MAXVERTEX; v++) {
        printf("Breadth First Search starting at vertex %c (%d):\n",
               Vertices[v]->label, v);
        breadthFirstSearch(v);
    }

    //asking for what vertex to delete
    printf("Enter starting and ending position of vertex to delete (seperated by commas):\n");
    scanf("%c, %c", &s, &e);

    //deleting vertex defined by user
    delete(s, e);

    printf("Second demonstration - this time with islands\n");
    verbose = 1;
    resetGraph();
    addVertexLabels("PQRSTUV");
    addEdgeByLabel('P', 'Q');
    addEdgeByLabel('P', 'R');
    addEdgeByLabel('R', 'Q');
    addEdgeByLabel('S', 'T');
    addEdgeByLabel('S', 'U');
    addEdgeByLabel('S', 'V');
    addEdgeByLabel('T', 'U');
    addEdgeByLabel('T', 'V');
    addEdgeByLabel('V', 'W');
    verbose = 1;            // now be talkative

    if (verbose) {
        // Display resulting adjacency matrix
        printf("Adjacency Matrix:\n");
        printAdjMatrix();
        putchar('\n');
    }

    printf("Breadth-first searches, starting at each vertex\n");
    for (v = 0; v < MAXVERTEX; v++) {
        printf("Breadth First Search starting at vertex %c (%d):\n",
               Vertices[v]->label, v);
        breadthFirstSearch(v);
    }

    printf("\n=====================================================\n");
    printf("Third demonstration - this time with directed edges.\n");
    resetGraph();
    addVertexLabels("ABCDEFG");

    addDirectedEdge(0, 1);        // A - B
    addDirectedEdge(0, 2);        // A - C
    addDirectedEdge(0, 6);        // A - G
    addDirectedEdge(1, 3);        // B - D
    addDirectedEdge(2, 6);        // C - G
    addDirectedEdge(3, 4);        // D - E
    addDirectedEdge(3, 5);        // D - F
    addDirectedEdge(5, 6);        // F - G
    addDirectedEdge(5, 4);        // F - E

    verbose = 1;            // now be talkative

    if (verbose) {
        // Display resulting adjacency matrix
        printf("Adjacency Matrix:\n");
        printAdjMatrix();
        putchar('\n');
    }

    printf("Breadth-first searches, starting at each vertex\n");
    for (v = 0; v < MAXVERTEX; v++) {
        printf("Breadth First Search starting at vertex %d:\n", v);
        breadthFirstSearch(v);
    }

    printf("\n=====================================================\n");
    printf("Fourth demonstration - with weighted directed edges.\n");
    resetGraph();
    addVertexLabels("ABCDEFG");

    addWeightedDirectedEdge(0, 1, 10);        // A - B
    addWeightedDirectedEdge(0, 2, 20);        // A - C
    addWeightedDirectedEdge(0, 6, 30);        // A - G
    addWeightedDirectedEdge(1, 3, 40);        // B - D
    addWeightedDirectedEdge(2, 6, 50);        // C - G
    addWeightedDirectedEdge(3, 4, 60);        // D - E
    addWeightedDirectedEdge(3, 5, 70);        // D - F
    addWeightedDirectedEdge(5, 6, 80);        // F - G
    addWeightedDirectedEdge(5, 4, 90);        // F - E

    verbose = 1;            // now be talkative

    if (verbose) {
        // Display resulting adjacency matrix
        printf("Adjacency Matrix:\n");
        printAdjMatrix();
        putchar('\n');
    }

    printf("Breadth-first searches, starting at each vertex\n");
    for (v = 0; v < MAXVERTEX; v++) {
        printf("Breadth First Search starting at vertex %d:\n", v);
        breadthFirstSearch(v);
    }
    return 0;
}//main()
