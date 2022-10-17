#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
int N = 0;

struct Point
{
    double x, y;
};


int sortX(const void* a, const void* b)
{
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->x - p2->x);
}


int sortY(const void* a, const void* b)
{
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->y - p2->y);
}


double dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}


double typoi(Point P[], int n)
{
    double min = 10000000000000000000;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (dist(P[i], P[j]) < min) {
                min = dist(P[i], P[j]);
            }
        }
    }
    return min;
}


double min(double x, double y)
{
    if (x < y) {
        return x;
    }
    else { return y; }
}


double closest(Point strip[], int size, double d)
{
    double min = d;

    qsort(strip, size, sizeof(Point), sortY);


    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            if (dist(strip[i], strip[j]) < min) {
                min = dist(strip[i], strip[j]);
            }
        }
    }
    return min;
}


double mediana(Point P[], int n)
{

    if (n <= 3) { return typoi(P, n); }

    int mid = n / 2;
    Point midPoint = P[mid];

    double dl = mediana(P, mid);
    double dr = mediana(P + mid, n - mid);


    double d = min(dl, dr);

    Point strip[6];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip[j] = P[i], j++;


    return min(d, closest(strip, j, d));
}


double closest(Point P[], int n)
{
    qsort(P, n, sizeof(Point), sortX);


    return mediana(P, n);
}


int main()
{
    Point P[] = { {2.5, 66}, {12, 30}, {40, -82}, {5, 1}, {12, 10}, {3, 4} };
    int n = sizeof(P) / sizeof(P[0]);
    cout << "The faster time is " << closest(P, n);
    return 0;
}