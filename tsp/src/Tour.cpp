// isape817 rasda103

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    first = nullptr;
}

Tour::~Tour()
{
    if ( first == nullptr ) {
        return;
    }

    Node* current = first->next;

      while (current != first){
        Node* next = current->next;
        delete current;
        current = next;
    }
    delete first;
    first = nullptr;
}

void Tour::show()
{
    if( first == nullptr ) {
        return;
    }

    Node* currentNode = first;
    do {
        std::cout << currentNode->point.toString() << endl;
        currentNode = currentNode->next;
    }
    while( currentNode != first );
}

void Tour::draw(QGraphicsScene *scene)
{
    if ( first == nullptr ) {
        return;
    }

    scene->clear();
    Node* currentNode = first;
    do {
        currentNode->point.drawTo( currentNode->next->point, scene );
        currentNode = currentNode->next;
    }
    while( currentNode != first );
}

int Tour::size()
{
    int size = 0;

    if ( first == nullptr ) {
        return size;
    }

    Node* currentNode = first;
    do {
        size++;
        currentNode = currentNode->next;
    }
    while( currentNode != first );
    return size;
}

double Tour::distance()
{
    double distance = 0;

    if ( first == nullptr ) {
        return distance;
    }

    Node* currentNode = first;
    do {
        distance += currentNode->point.distanceTo( currentNode->next->point );
        currentNode = currentNode->next;
    }
    while( currentNode != first );
    return distance;
}

void Tour::opt2() {
    bool startOver = true;
    while (startOver) {
        startOver = false;

        Node* outerCurrent = first->next;
        Node* prev = first;

        do {
            Node* innerCurrent = outerCurrent->next;

            do {
                bool shouldSwap = prev->point.distanceTo(innerCurrent->point) +
                        outerCurrent->point.distanceTo(innerCurrent->next->point) <
                        prev->point.distanceTo(outerCurrent->point) +
                        innerCurrent->point.distanceTo(innerCurrent->next->point);

                if (shouldSwap) {
                    startOver = true;
                    swap(outerCurrent, innerCurrent);
                }
            }
        }
    }
}

void Tour::swap(Node* start, Node* end) {

}

void Tour::insertNearest(Point p)
{
    if ( first == nullptr ) {
        first = new Node( p );
        first->next = first;
        return;
    }

    Node* currentNode = first;
    Node* nearest = first;
    double nearestDistance = first->point.distanceTo(p);

    do {
        double currentDistance = currentNode->point.distanceTo(p);
        if ( currentDistance <= nearestDistance ) {
            nearest = currentNode;
            nearestDistance = currentDistance;
        }

        currentNode = currentNode->next;
    } while( currentNode != first);

    Node* newNode = new Node(p, nearest->next);
    nearest->next = newNode;

}

void Tour::insertSmallest(Point p)
{
    if ( first == nullptr ) {
        first = new Node( p );
        first->next = first;
        return;
    }

    Node* currentNode = first;
    Node* nearest = first;
    double smallestDifference = distance();

    do {
        double currentDistance = currentNode->point.distanceTo(currentNode->next->point);
        double newDistance = currentNode->point.distanceTo(p) + p.distanceTo(currentNode->next->point);
        if ( newDistance - currentDistance <= smallestDifference ) {
            nearest = currentNode;
            smallestDifference = newDistance - currentDistance;
        }

        currentNode = currentNode->next;
    } while( currentNode != first);

    Node* newNode = new Node(p, nearest->next);
    nearest->next = newNode;
}
