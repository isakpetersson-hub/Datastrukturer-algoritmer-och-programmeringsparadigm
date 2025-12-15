#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    Tour();
    /*
     * Creates a tour with an empty first node
     */

    ~Tour();
    /*
     * Frees the memory from the entire tour, which includes the linked list of nodes
     */

    void show();
    /*
     * Prints a basic representation of the tour to stdout
     */

    void draw(QGraphicsScene* scene);
    /*
     * Uses QGraphics to create a graphical representation of the tour using the function DrawTo( Point p ) present in the Point class
     */

    int size();
    /*
     * Walks through the nodes in the tour and returns the total amount of nodes
     */

    double distance();
    /*
     * Walks through the nodes in the tour and returns the total distance
     */

    void opt2();
    /*
     * Goes through an existing tour and makes sure no path crosses another path
     */

    void swap(Node* start, Node* end);
    /*
     * Used to help with opt2, swaps nodes so that paths don't cross
     */

    void insertNearest(Point p);
    /*
     * Searches through the tour to find the node which is nearest to the point p, and then inserts p after that node
     */

    void insertSmallest(Point p);
    /*
     *Searches through the tour to find the place where if the point p is inserted, it results in the smallest possible increase in total distance
     */

private:
    Node* first; // Pointer to the first node in the tour
};

#endif // TOUR_H
