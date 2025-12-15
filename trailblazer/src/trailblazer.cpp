// isape817 rasda103

#include "costs.h"
#include <algorithm>
#include <queue>
#include "pqueue.h"
#include "trailblazer.h"

using namespace std;

vector<Node *> getValidNeighbours(const Vertex* const vertex) {
    // Used for BFS and DFS
    vector<Vertex*> neighbours;

    for (Edge* edge : vertex->arcs) {
        if (!edge->finish->visited && !(edge->finish->getColor() == YELLOW)) {
            neighbours.push_back(edge->finish);
        }
    }

    return neighbours;
}

void reconstructPath(Vertex* vertex, vector<Vertex*>& path) {
    while (vertex != nullptr) {
        path.push_back(vertex);
        vertex = vertex->previous;
    }

    reverse(path.begin(), path.end());
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
            reconstructPath(vertex, path);
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
            reconstructPath(vertex, path);
            break;
        }

        vector<Vertex*> neighbours = getValidNeighbours(vertex);
        if (!neighbours.empty()) {
           for (Vertex* v : neighbours) {
               // Marked yellow since they'll be in the queue now
               v->setColor(YELLOW);
               v->previous= vertex;
               vertexQueue.push(v);
            }
        }
    }

    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    PriorityQueue<Vertex*> vertexQueue;
    vector<Vertex*> path;

    vertexQueue.enqueue(start, 0);

    while (!vertexQueue.isEmpty()) {
        Vertex* vertex = vertexQueue.dequeue();

        vertex->setColor(GREEN);
        vertex->visited = true;

        if (vertex == end) {
            reconstructPath(vertex, path);
            break;
        }

        for (Edge* edge : vertex->arcs) {
            Vertex* next = edge->finish;
            if ((next->cost == 0) || (next->cost > edge->cost + vertex->cost)) {
                // Calculated cost is cheaper than current cost (or vertex hasn't been examined before)
                next->cost = edge->cost + vertex->cost;
                next->previous = vertex;
                vertexQueue.enqueue(next, next->cost);
                next->setColor(YELLOW);
            }
        }
    }

    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    vector<Vertex*> path;
    if (start == end)
        return path;

    PriorityQueue<Vertex*> vertexQueue;

    vertexQueue.enqueue(start, 0);

    while (!vertexQueue.isEmpty()) {
        Vertex* vertex = vertexQueue.dequeue();

        vertex->setColor(GREEN);
        vertex->visited = true;

        if (vertex == end) {
            // Reconstruct the path
            reconstructPath(vertex, path);
            break;
        }

        for (Edge* edge : vertex->arcs) {
            Vertex* next = edge->finish;
            if (next->visited)
                continue;

            if ((next->cost == 0) || (next->cost > edge->cost + vertex->cost)) {
                next->cost = edge->cost + vertex->cost;
                next->previous = vertex;

                vertexQueue.enqueue(next, next->cost + next->heuristic(end));
                next->setColor(YELLOW);
            }
        }
    }

    return path;
}
