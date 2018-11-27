#include <bits/stdc++.h>
#include "pointHeaders.h"

using namespace std;

int main()
{
    cout << "Alina Fedyna. This program calculates minimal distance between two points not crossing the polygon\n";

    ifstream fi; ofstream fo;
    string fName;
    while (!fi.is_open()) //вхідний файл
    {
        fName=getFileName("input");
        if (fName=="") fName="input.txt";
        fi.open(fName);
        if (!fi.is_open()) cout << "Pass is incorrect\n";
    }

    fName=getFileName("output"); // вихідний файл
    if (fName=="") fName="output.txt";
    fo.open(fName);

    Point p[N]; // точки многокутника
    int n=0;
    p[0].setX(fi), p[0].setY(fi);
    do{
        ++n;
        p[n].setX(fi);
        p[n].setY(fi);
    } while (p[n]!=p[0]);

    if (!is_ok(p,n)) return fo <<"Polygon is not correct", 0; // перевірка на опуклість


    Point a,b;
    while (a.setX(fi)) //обробка точок
    {
        a.setY(fi); b.setX(fi); b.setY(fi);
        if (a.is_inside(p,n) || b.is_inside(p,n)) fo << "Error: the point is inside the polygon\n";
        else
        {
            if (cross(a,b,p,n))
            {
                Point ans1[N], ans2[N];
                int ansN1=0, ansN2=0,k=0;
                fo << getAns(a,b,p,n,ans1,ansN1,ans2,ansN2,k) << ": ";
                if (k==1)
                    for (int i=0; i<ansN1; i++)
                        fo << ans1[i].getX() << " " << ans1[i].getY() << " ";
                else{
                    for (int i=0; i<ansN2; i++)
                        fo << ans2[i].getX() << " " << ans2[i].getY() << " ";
                }
                fo << "\n";
            }
            else
            {
                fo << a.getLen(b) << ": ";
                fo << a.getX() << " " << a.getY() << " " << b.getX() << " " << b.getY() << "\n";
            }
        }
    }

    fi.close();
    fo.close();
    return 0;
}

string getFileName(string t)
{
    string name;
    cout << "Enter pass to " << t <<" file: ";
    getline(cin, name);
    return name;
}

/*
bool is_ok(Point p[], int n)
{
    if (n<3) return true;
    int flag, k;
    flag=p[2].def(p[0],p[1]);
    for (int i=3; i<=n; ++i)
    {
        k=p[i].def(p[i-2],p[i-1]);
        if (flag!=k) return false;
    }
    k=p[1].def(p[n-1],p[n]);
    if (flag!=k) return false;
    return true;
}
*/
bool is_ok(Point p[], int n)
{
    if (n<3) return true;
    int flag=0, k;

    int ff=2;
    while (flag==0 && ff<=n)
    {
        flag=p[ff].def(p[ff-2],p[ff-1]);
        ++ff;
    }
    if (flag==0) k=p[1].def(p[n-1],p[n]);
    if (flag==0) return false;
    for (int i=2; i<=n; ++i)
    {
        k=p[i].def(p[i-2],p[i-1]);
        if (flag!=k && k!=0) return false;
    }
    k=p[1].def(p[n-1],p[n]);
    if (flag!=k) return false;
    return true;
}

