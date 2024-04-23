#include "utils.hpp"

Point starting_point;

float distance_sqrd(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void swap(Point &p1, Point &p2) {
    Point aux = p1;
    p1 = p2;
    p2 = aux;
}

int orientation(Point p1, Point p2, Point p3) {
    int value = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
    if (value == 0)
        return 0;  // Collinear
    return value > 0 ? 1 : 2; // Clockwise | Counterclockwise
}

int get_min_y(std::vector<Point> points) {
    int min_y_index = 0;
    int min_y = points[0].y;

    for (int i = 0, size = points.size(); i < size; i++) {
        if (points[i].y < min_y || (points[i].y == min_y && points[i].x < points[min_y_index].x)) {
            min_y_index = i;
            min_y = points[i].y;
        }
    }
    return min_y_index;
}

int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *) vp1;
    Point *p2 = (Point *) vp2;

    // Orientation value = {0, 1, 2}
    int value = orientation(starting_point, *p1, *p2);

    if (value == 0)
        return (distance_sqrd(starting_point, *p2) >= distance_sqrd(starting_point, *p1)) ? -1 : 1;

    return (value == 2) ? -1: 1;
}

void sort_points_by_angle(std::vector<Point> points) {
    int min_y_index = get_min_y(points);
    swap(points[0], points[min_y_index]);
    qsort(&points[1], points.size() - 1, sizeof(Point), compare);
}

std::vector<Point> graham_scan(std::vector<Point> points) {
    std::vector<Point> a;
    std::stack<Point> stack;
    sort_points_by_angle(points);
    stack.push(points[0]);
    stack.push(points[1]);

    for (int i = 2, size = points.size(); i < size; i++) {
        // Point next = points[i] ;
        // Point current = stack.top();
        // stack.pop();
        // while (stack.top() != NULL && orientation(stack.top(), current, next)) {
        //     /* code */
        // }
    }
    
    return a;
}
