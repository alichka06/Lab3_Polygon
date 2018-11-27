#ifndef POINTHEADERS_H_INCLUDED
#define POINTHEADERS_H_INCLUDED
using namespace std;
struct Line
{
    double la,lb,lc;
};

class Point{
    private:
        double x,y;
    public:
        Point();
        Point(double x_, double y_);
        bool setX(ifstream& f);
        bool setY(ifstream& f);
        double getX();
        double getY();
        Point& operator = (const Point p);
        bool operator != (const Point p) const;
        bool operator == (const Point p) const;
        int def(const Point& p1,const Point& p2) const;
        double getLen(const Point& p) const;
        double ang(const Point& a1, const Point& b2) const;
        void pSwap(Point& p);
        int is_s(Point a, Point b, Point p1, Point p2);
        bool is_inside(Point p[], int n) const;
        friend void getabc(Line& l, const Point& a, const Point& b);
        friend bool intersect(Line& k, Line& l, Point& a);
        friend void div( Point& a,  Point& b, Point p[], int n, Point up[], int& u, Point down[], int& d);
};

const int N=10001;

string getFileName(string t);
double getAns(Point& a, Point& b, Point p[], int n, Point ans11[], int& a1, Point ans22[], int& a2, int& k);
bool is_ok(Point p[], int n);
int cross(Point& a, Point& b, Point p[], int n);

#endif // POINTHEADERS_H_INCLUDED
