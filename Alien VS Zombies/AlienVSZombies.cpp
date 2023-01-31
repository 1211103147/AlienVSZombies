#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

class Maps
{
private:
    vector<vector<char>> map_;
    int dimX_, dimY_, up_, down_;
public:
    Maps(int dimX = 15, int dimY = 5);
    void init(int dimX, int dimY);
    void display() const;

    int getDimX() const;
    int getDimY() const;

    void setObject(int x, int y, char ch);
    void removeObjectUp(int x, int y, char ch);
    void removeObjectDown(int x, int y, char ch);
    void removeObjectLeft(int x, int y, char ch);
    void removeObjectRight(int x, int y, char ch);
};

class Alien
{
private:
    int x_, y_;
    char ch_;
public:
    Alien();
    int dimX = 15, dimY =5;
    void start(Maps &maps);
    void moveUp(Maps &maps);
    void moveDown(Maps &maps);
    void moveLeft(Maps &maps);
    void moveRight(Maps &maps);

    int getX() const;
    int getY() const;
    char getch() const;
};

Maps::Maps(int dimX, int dimY)
{
    init(dimX, dimY);
}

void Maps::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
    char objects[] = {'^', '<', '>', 'v', 'h', 'p', 'r', ' ', ' ', ' ', ' '};
    int noOfObjects = 11;
    map_.resize(dimY_);
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_);
    }

    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void Maps::display() const
{
    cout << " ::==::==::==::==::==::==::==::==::" << endl;
    cout << " <= Welcome to Alien VS Zombies! =>" << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl;
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        cout << " ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        cout << setw(1) << (dimY_ - i);
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }

    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

int Maps::getDimX() const
{
    return dimX_;
}
int Maps::getDimY() const
{
    return dimY_;
}

void Maps::setObject(int x, int y, char ch)
{
    map_[dimY_ - y][x - 1] = ch;
}
void Maps::removeObjectUp(int x, int y, char ch)
{
    Alien alien;
    int delX = x;
    int delY = y - 1;
    map_[dimY_ - delY][delX - 1] = '.';
}
void Maps::removeObjectDown(int x, int y, char ch)
{
    Alien alien;
    int delX = x;
    int delY = y + 1;
    map_[dimY_ - delY][delX - 1] = '.';
}
void Maps::removeObjectLeft(int x, int y, char ch)
{
    Alien alien;
    int delX = x + 1;
    int delY = y;
    map_[dimY_ - delY][delX - 1] = '.';
}
void Maps::removeObjectRight(int x, int y, char ch)
{
    Alien alien;
    int delX = x - 1;
    int delY = y;
    map_[dimY_ - delY][delX - 1] = '.';
}

Alien::Alien()
{}

void Alien::start(Maps &maps)
{
    char ch_= 'A';
    x_ = double(dimX) /2 +1;
    y_ = double(dimY) /2 +1;
    maps.setObject(x_, y_, ch_);
}
void Alien::moveUp(Maps &maps)
{
    Alien alien;
    char ch_ ='A';
    while (y_< dimY)
    {
        y_ = ++y_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectUp(x_, y_, ch_);
    }
}
void Alien::moveDown(Maps &maps)
{
    Alien alien;
    char ch_ ='A';
    while (y_> 1)
    {
        y_ = --y_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectDown(x_, y_, ch_);
    }
}
void Alien::moveLeft(Maps &maps)
{
    Alien alien;
    char ch_ ='A';
    while (x_> 1)
    {
        x_ = --x_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectLeft(x_, y_, ch_);
    }
}
void Alien::moveRight(Maps &maps)
{
    Alien alien;
    char ch_ ='A';
    while (x_< dimX)
    {
        x_ = ++x_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectRight(x_, y_, ch_);
    }
}

int Alien::getX() const
{
    return x_;
}
int Alien::getY() const
{
    return y_;
}

char Alien::getch() const
{
    return ch_;
}

void Run()
{
    Maps maps;
    Alien attack;
    attack.start(maps);
    maps.display();
    //attack.moveUp(maps);
    //attack.moveDown(maps);
    //attack.moveLeft(maps);
    //attack.moveRight(maps);
    maps.display();
}

int main()
{
    srand(time(NULL));
    Run();
}