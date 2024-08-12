#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point start;
    Point end;
} LineSegment;

bool arePointsEqual(Point p1, Point p2) {
    return fabs(p1.x - p2.x) < DBL_EPSILON && fabs(p1.y - p2.y) < DBL_EPSILON;
}

bool isPointOnLineSegment(Point p, LineSegment ls) {
    // Check if the point is on the line segment
    double crossProduct = (p.y - ls.start.y) * (ls.end.x - ls.start.x) -
                          (p.x - ls.start.x) * (ls.end.y - ls.start.y);
    
    if (fabs(crossProduct) > DBL_EPSILON)
        return false;

    double dotProduct = (p.x - ls.start.x) * (ls.end.x - ls.start.x) +
                        (p.y - ls.start.y) * (ls.end.y - ls.start.y);
    
    if (dotProduct < 0)
        return false;

    double squaredLength = (ls.end.x - ls.start.x) * (ls.end.x - ls.start.x) +
                           (ls.end.y - ls.start.y) * (ls.end.y - ls.start.y);
    
    if (dotProduct > squaredLength)
        return false;

    return true;
}

bool findIntersection(LineSegment ls1, LineSegment ls2, Point* intersection) {
    double x1 = ls1.start.x, y1 = ls1.start.y;
    double x2 = ls1.end.x, y2 = ls1.end.y;
    double x3 = ls2.start.x, y3 = ls2.start.y;
    double x4 = ls2.end.x, y4 = ls2.end.y;

    double denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    
    if (fabs(denom) < DBL_EPSILON) {
        // Lines are parallel
        return false;
    }

    double ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom;
    double ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom;

    if (ua < 0 || ua > 1 || ub < 0 || ub > 1) {
        // Intersection point is outside of both line segments
        return false;
    }

    intersection->x = x1 + ua * (x2 - x1);
    intersection->y = y1 + ua * (y2 - y1);

    return true;
}

int main() {
    LineSegment ls1 = {{0, 0}, {5, 5}};
    LineSegment ls2 = {{0, 5}, {5, 0}};
    Point intersection;

    if (findIntersection(ls1, ls2, &intersection)) {
        printf("Intersection point: (%.2f, %.2f)\n", intersection.x, intersection.y);
    } else {
        printf("No intersection found.\n");
    }

    return 0;
}