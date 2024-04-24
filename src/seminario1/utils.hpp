#ifndef UTILS_HPP
#define UTILS_HPP

#include <gl/gl.h>
#include <gl/glu.h>
#include <GL/glut.h>
#include <vector>
#include <stack>

typedef struct {
    int x, y;
} Point;

float distance_sqrd(Point p1, Point p2);

int orientation(Point p1, Point p2, Point p3);

void swap(Point &p1, Point &p2);

int get_min_y(std::vector<Point> points);

std::vector<Point> graham_scan(std::vector<Point> points);

#endif // UTILS_HPP