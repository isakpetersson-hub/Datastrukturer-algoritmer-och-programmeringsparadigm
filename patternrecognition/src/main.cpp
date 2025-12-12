// rasda103 isape817

/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"

void brute(const vector<Point>& points, QApplication& a, QGraphicsScene* scene, int N);
void fast(const vector<Point>& points, QApplication& a, QGraphicsScene* scene, int N);

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input12800.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    // Calls the diffrent functions
    //brute(points,a,scene, N);
    fast(points,a,scene, N);

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}
void fast(const vector<Point>& points, QApplication& a, QGraphicsScene* scene, int N){
    for (int i = 0 ; i < N ; i++){
        Point origo = points.at(i);
        vector<pair<float,Point>> slopes;
        for (int j = 0 ; j < N ; j++){
            if (i != j){
                // Calculate the angle between i and j and at it to the vector
               slopes.emplace_back(origo.slopeTo(points.at(j)),points.at(j));
            }
        }
        sort(slopes.begin(), slopes.end());
        // Sort the slopes by angle
        // If several entries with the same angle exist, they are on the same line
        for ( unsigned int k = 0 ; k < slopes.size() ; k++ ){
            if ( slopes[k].first == slopes[k+1].first){
                    if ( slopes[k].first == slopes[k+2].first){
                        render_line(scene, points.at(i), slopes[k].second);
                        a.processEvents(); // show rendered line
                    } else{
                        k++;
                }
            }
        }
    }
}
void brute(const vector<Point>& points, QApplication& a, QGraphicsScene* scene, int N){
    // iterate through all combinations of 4 points
    for (int i = 0 ; i < N-3 ; ++i) {
        for (int j = i+1 ; j < N-2 ; ++j) {
            for (int k = j+1 ; k < N-1 ; ++k) {
                //only consider fourth point if first three are collinear
                if (points.at(i).slopeTo(points.at(j)) == points.at(i).slopeTo(points.at(k))) {
                    for (int m{k+1} ; m < N ; ++m) {
                        if (points.at(i).slopeTo(points.at(j)) == points.at(i).slopeTo(points.at(m))) {
                            render_line(scene, points.at(i), points.at(m));
                            a.processEvents(); // show rendered line
                        }
                    }
                }
            }
        }
    }
}
