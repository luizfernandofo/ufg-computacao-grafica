#ifndef GRAHAM_SCAN_HPP
#define GRAHAM_SCAN_HPP

#include <iostream>
#include <stack>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef struct point {
    int x, y;
} Point;

Point nextToTop(stack<Point> &S);

void swap(Point &p1, Point &p2);

int distSq(Point p1, Point p2);

int orientation(Point p, Point q, Point r);

int compare(const void *vp1, const void *vp2);

vector<Point> convexHull(Point points[], int n);

#endif // GRAHAM_SCAN_HPP
