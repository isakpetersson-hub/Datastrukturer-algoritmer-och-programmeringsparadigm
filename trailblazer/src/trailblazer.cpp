// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include <algorithm>
#include <queue>
#include "trailblazer.h"
// TODO: include any other headers you need; remove this comment
using namespace std;

vector<Node *> getValidNeighbours(const Vertex* const vertex) {
    vector<Vertex*> neighbours;

    for (Edge* edge : vertex->arcs) {
        if (!edge->finish->visited && !(edge->finish->getColor() == YELLOW)) {
            neighbours.push_back(edge->finish);
        }
    }

    return neighbours;
}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    vector<Vertex*> path;
    Stack<Vertex*> vertexStack;
    vertexStack.push(start);

    while (!vertexStack.isEmpty()) {
        Vertex* vertex = vertexStack.pop();
        if (vertex == end) {
            // Reconstruct the path
            do {
                path.push_back(vertex);
                vertex = vertex->previous;
            } while (vertex != start);
            path.push_back(start);
            break;
            // Exit the loop since we have a path
        } else if (!vertex->visited) {
            vertex->visited = true;
            vertex->setColor(GREEN);
            vector<Vertex*> neighbours = getValidNeighbours(vertex);
            if (neighbours.empty()) {
                // There are no valid neighbours, abandon and mark gray until we get to the next branch
                while (vertex != vertexStack.top()->previous) {
                    vertex->setColor(GRAY);
                    vertex = vertex->previous;
                }
            } else {
                for (Vertex* v : neighbours) {
                    // Marked yellow since they'll be in the stack now
                    v->setColor(YELLOW);
                    v->previous = vertex;
                    vertexStack.push(v);
                }
            }
        }
    }

    reverse(path.begin(), path.end());

    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    queue<Vertex*> vertexQueue;
    vector<Vertex*> path;

    vertexQueue.push(start);

    while (!vertexQueue.empty()) {
        Vertex* vertex = vertexQueue.front();
        vertexQueue.pop();

        vertex->setColor(GREEN);
        vertex->visited = true;

        if (vertex == end) {
            // Reconstruct the path
            do {
                path.push_back(vertex);
                vertex = vertex->previous;
            } while (vertex != start);
            path.push_back(start);
            break;
        }

        vector<Vertex*> neighbours = getValidNeighbours(vertex);
        if (neighbours.empty()) {
            // do the dfs mark gray thing
        } else {
            for (Vertex* v : neighbours) {
                v->setColor(YELLOW);
                v->previous= vertex;
                vertexQueue.push(v);
            }
        }
    }

    reverse(path.begin(), path.end());

    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
