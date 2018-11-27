#include <bits/stdc++.h>
#include "pointHeaders.h"

using namespace std;

Point:: Point(){};
Point:: Point(double x_, double y_): x(x_), y(y_){};

bool Point::setX(ifstream& f)
{
    double x_;
    if (f >> x_) x=x_; else return 0;
    return 1;
};

bool Point::setY(ifstream& f)
{
    double y_;
    if (f >> y_) y=y_; else return 0;
    return 1;
};

double Point::getX(){ return x;}
double Point::getY(){ return y;}

Point& Point::operator = (const Point p)
{
     x=p.x;
     y=p.y;
     return *this;
};

bool Point::operator != (const Point p) const
{
    if (x==p.x && y==p.y) return false; else return true;
};

bool Point::operator == (const Point p) const
{
    if (x==p.x && y==p.y) return true; else return false;
};

double Point::getLen(const Point& p) const
{
    return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));
};
void Point::pSwap(Point& p)
{
    if ((p.x<x) || (x==p.x && y>p.y))  {double t=x; x=p.x; p.x=t; t=y; y=p.y; p.y=t;}
}

int Point::def(const Point& p1,const Point& p2) const
{
    double k=(p2.x-p1.x)*(y-p2.y)-(x-p2.x)*(p2.y-p1.y);
    if (k<0) return -1;
    if (k>0) return 1;
    if (k==0) return 0;
};

double Point::ang(const Point& a1, const Point& b2) const
{
    double x1=x-a1.x, y1=y-a1.y, x2=b2.x-x, y2=b2.y-y;
    return (x1*x2+y1*y2)/(a1.getLen(*this)*(*this).getLen(b2));
}

void div( Point& a,  Point& b, Point p[], int n, Point up[], int& u, Point down[], int& d)
{
    int k, t;
    k=p[0].def(a,b);
    for (int i=1; i<n; ++i)
    {
        t=p[i].def(a,b);
        if (t!=k) {t=i; break;}
    }
    for (int i=t; i<n+t; ++i )
    {
        k=p[(i+n)%n].def(a,b);
        if (k>0) {up[u]=p[(i+n)%n]; ++u;}
        if (k<0) {down[d]=p[(i+n)%n]; ++d;}
    }
    //так можна:
    //sort(up,up+u,[](Point a, Point b){if (a.x<b.x || (a.x==b.x && a.y<b.y)) return true; else return false;});
    //sort(down, down+d, [](Point a, Point b){if (a.x<b.x || (a.x==b.x && a.y<b.y)) return true; else return false;});
    return;
};


double getAns(Point& a, Point& b, Point p[], int n, Point ans11[], int& a1, Point ans22[], int& a2 , int& k)
{
    Point up[N], down[N];
    int u=0, d=0;

    a.pSwap(b);
    div(a,b,p,n,up,u,down,d);

    //for (int i=0; i<u; ++i)
    //    cout << "u " << up[i].getX() << " " << up[i].getY() << " ";
    //for (int i=0; i<d; ++i)
    //    cout << "d " << down[i].getX() << " " << down[i].getY() << " ";

    if (u==0 || d==0)
    {
        ans11[0]=a; ans11[1]=b; a1=2; k=1;
        return a.getLen(b);
    }


    int upBegin=-1, upEnd=-1, downBegin=-1, downEnd=-1;
    double t=-1;
    for (int i=0; i<u; ++i)
        if (a.ang(b,up[i])>t) {t=a.ang(b,up[i]); upBegin=i;};
    t=-1;
    for (int i=0; i<u; ++i)
        if (b.ang(a,up[i])>t) {t=b.ang(a,up[i]); upEnd=i;};
    t=-1;
    for (int i=0; i<d; ++i)
        if (a.ang(b,down[i])>t) {t=a.ang(b,down[i]); downBegin=i;};
    t=-1;
    for (int i=0; i<d; ++i)
        if (b.ang(a,down[i])>t) {t=b.ang(a,down[i]); downEnd=i;};

    //cout << "ggg " << upBegin << " " << upEnd << " " << downBegin << " " <<downEnd<<"\n";

    Point upB=a, upE=b, downB=a, downE=b;
    if (upEnd>upBegin) {Point f=upB; upB=upE; upE=f;}
    if (downEnd>downBegin) {Point f=downB; downB=downE; downE=f;}

    double ans1,ans2; bool cha=0;

    ans1=a.getLen(up[upBegin])+b.getLen(up[upEnd]);
    if (upEnd<upBegin) ans11[a1++]=b; else ans11[a1++]=a;
    ans11[a1++]=up[upBegin];
    if (upEnd<upBegin) {int f=upBegin; upBegin=upEnd; upEnd=f; cha=1;}
    for (int i=upBegin; i<upEnd; ++i)
    {
        ans1+=up[i].getLen(up[i+1]);
        ans11[a1++]=up[i+1];
    }
    if (cha==1) ans11[a1++]=a; else ans11[a1++]=b;

    cha=0;
    ans2=a.getLen(down[downBegin])+b.getLen(down[downEnd]);
    if (downEnd<downBegin) ans22[a2++]=b; else ans22[a2++]=a;
    ans22[a2++]=down[downBegin];
    if (downEnd<downBegin) {int f=downBegin; downBegin=downEnd; downEnd=f; cha=1;}
    for (int i=downBegin; i<downEnd; ++i)
    {
        ans2+=down[i].getLen(down[i+1]);
        ans22[a2++]=down[i+1];
    }
    if (cha==1) ans22[a2++]=a; else ans22[a2++]=b;

    if (ans1<ans2) k=1; else k=2;

    return min(ans1,ans2);
}

void getabc(Line& l, const Point& b, const Point& c)
{
    if (c.x==b.x) {l.la=1, l.lb=0, l.lc=-c.x; return;}
    if (c.y==b.y) {l.la=0, l.lb=1, l.lc=-c.y; return;}
    l.lb=-(c.x-b.x);
    l.la=(c.y-b.y);
    l.lc=b.y*(c.x-b.x)-(c.y-b.y)*b.x;
    return;
};

bool intersect(Line& k, Line& l, Point& a)
{
    if ((k.la==0 && l.la==0) || (k.lb==0 && l.lb==0)) return false;
    if (k.la==0 && l.lb==0) {a.y=-k.lc; a.x=-l.lc; return true;}
    if (l.la==0 && k.lb==0) {a.y=-l.lc; a.x=-k.lc; return true;}
    if (k.la==0) {a.y=-k.lc/k.lb; a.x=-l.lc/l.la-l.lb/l.la*a.y; return true;}
    if (l.la==0) {a.y=-l.lc/l.lb; a.x=-k.lc/k.la-k.lb/k.la*a.y; return true;}
    if (k.lb==0) {a.x=-k.lc/k.la; a.y=-l.la/l.lb*a.x-l.lc/l.lb; return true;}
    if (l.lb==0) {a.x=-l.lc/l.la; a.y=-k.la/k.lb*a.x-k.lc/k.lb; return true;}
    a.x=(l.lc*k.lb-k.lc*l.lb)/(k.la*l.lb-l.la*k.lb);
    a.y=-k.lc/k.lb-k.la/k.lb*a.x;
    return true;
};

int cross(Point& a, Point& b, Point p[], int n)
{
    Line l, ll;
    Point v, v1, v2;
    int p1=-1, p2=-1, crossP=0;

    getabc(l,a,b);
    //cout << l.la << " " << l.lb << " " << l.lc << "\n";
    for (int i=0; i<n; ++i)
    {
        getabc(ll,p[i],p[i+1]);
        if (l.la==ll.la && l.lb==ll.lb && l.lc==ll.lc) return false; //в≥др≥зок на сторон≥
        if (intersect(ll,l,v)) //отрим точку перетину
        {
            //cout << v.getX() << " " << v.getY() << " " << i <<"\n";
            int t=v.is_s(a,b,p[i],p[i+1]); //де ц€ точка
            //cout << "t " << t << "\n";
            if (t==1) ++crossP;
            if (t==0) {++crossP; if (p1==-1) v1=v, p1=i; else v2=v,p2=i;}
        }
    }
    //cout << "cross" << crossP << "\n";
    if (crossP==2 && p2==-1) return true;
    if (crossP==1 || crossP==0) return false;
    if (crossP==2)
    {
        if (p1==p2 && p1!=-1) return false;
        if (p2==p1+1)
        {
            if (v1==v2) return false; else return true;
        }
        return true;
    }
    if (crossP==3) return true;
}

int Point::is_s(Point a, Point b, Point p1, Point p2)
{
    p1.pSwap(p2);
    if (x<p1.x || x>p2.x) return -1;
    if (p1.y<=p2.y) if (!(y>=p1.y && y<=p2.y)) return -1;
    if (p2.y<=p1.y) if (!(y<=p1.y && y>=p2.y)) return -1;
    a.pSwap(b);
    if ((x==a.x && y==a.y) || (x==b.x && y==b.y)) return 0;
    if (x>=a.x && x<=b.x && ((a.y<=b.y && y>=a.y && y<=b.y) || (a.y>=b.y && y<=a.y && y>=b.y)))  return 1;
    return -1;
}

bool Point::is_inside(Point p[], int n) const
{
    Line l={1, 0, -x}, ll;
    Point v;
    int crUp=0, crDown=0;

    for (int i=0; i<n; ++i)
    {
        getabc(ll, p[i], p[i+1]);
        if (l.la==ll.la && l.lb==ll.lb && l.lc==ll.lc) return false;
        if (intersect(l,ll,v))
        {
            Point p1=p[i], p2=p[i+1];
            p1.pSwap(p2);
            //точка не нал в≥др≥зку p[i], p[i+1]
            if (v.x<p1.x || v.x>p2.x) continue;
            if (p1.y<=p2.y) if (!(v.y>=p1.y && v.y<=p2.y)) continue;
            if (p2.y<=p1.y) if (!(v.y<=p1.y && v.y>=p2.y)) continue;
            //пром≥нь вверх чи вниз
            if (v.y<y) crDown++;
            if (v.y>y) crUp++;
        }
    }
    if (crUp>0 && crDown>0) return true;
    return false;
}

