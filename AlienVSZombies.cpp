
// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT7L
// Names: MUHAMMAD HAIKAL AFIQ BIN RAFINGEI | AHMAD HAIKAL BIN EMRAN | MOHD AZRIY AKMALHAZIM BIN MOHD NAZARIEE
// IDs: 1211103141 | 12111103147 | 1211104288
// Emails: 1211103141@student.mmu.edu.my | 1211103147@student.mmu.edu.my | 1211104288@student.mmu.edu.my
// Phones: 0196710174 | 0172924339 | 0172071317
// *********************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

class Maps
{
private:
    vector<vector<char>> map_;
    int dimX_, dimY_, zomb_;

public:
    Maps();
    void init();
    void display() const;

    void changeDim(int dimX, int dimY);
    void changeZomb(int zomB);

    int getDimX() const;
    int getDimY() const;
    int getZombCount() const;
    char getObject(int x, int y);

    void setObject(int x, int y, char ch);
    void setZombies(int x1, int y1, char Z);
    void removeObjectUp(int x, int y, char ch);
    void removeObjectDown(int x, int y, char ch);
    void removeObjectLeft(int x, int y, char ch);
    void removeObjectRight(int x, int y, char ch);
    char detectObjectUp(int x, int y);
    char detectObjectDown(int x, int y);
    char detectObjectLeft(int x, int y);
    char detectObjectRight(int x, int y);
    void resetTrail();
};

class Zombies;

class Alien
{
private:
    int x_, y_;
    char ch_;
    int dimX_, dimY_, zomb_;
    int hp_, atk_;

public:
    Alien();
    void start(Maps &maps);

    void moveUp(Maps &maps, Zombies &zombie);
    void moveDown(Maps &maps, Zombies &zombie);
    void moveLeft(Maps &maps, Zombies &zombie);
    void moveRight(Maps &maps, Zombies &zombie);

    void changeDim(int dimX, int dimY);
    void changeZomb(int zomB);
    void changeHP(int hp);
    void minusHP(Maps &maps7);
    void resetATK();
    void addATK(int atk);

    void objectBehaviour(Maps &maps, Zombies &zombie, char object);

    int getX() const;
    int getY() const;
    char getch() const;
    int getHP() const;
    int getATK() const;
};

class Zombies
{
private:
    int xz_, yz_, hpz_, atkz_;
    char Z_;

public:
    vector<vector<int>> allzombies; // vector of vectors to store the all zombies
    vector<Zombies> zombiehp;
    vector<Zombies> zombieatk;
    Zombies();
    void spawn(Maps &maps);
    void initialZombHP(Maps &maps);
    void initialZombATK(Maps &maps);

    int getXZ() const;
    int getYZ() const;
    int getHPZ(int i);
    int getATKZ(int i);
    int getTotalHPZ(Maps map);
    char getZ() const;

    void changeHP(int i, int hp);

    void moveleft_z();
    void moveright_z();
    void movedown_z();
    void moveup_z();
    void moveupright_z();
    void moveupleft_z();
    void movedownright_z();
    void movedownleft_z();
    void move_z(Maps &maps, Alien &alien);
};

Maps::Maps()
{
    dimX_ = 15;
    dimY_ = 5;
    zomb_ = 2;
    init();
}

void Maps::init()
{
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
    cout << "   ::==::==::==::==::==::==::==::==::" << endl;
    cout << "   <=  Alien VS Zombies Gameplay!  =>" << endl;
    cout << "   ::==::==::==::==::==::==::==::==::" << endl;
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        cout << "   ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-+-";
        }
        cout << "+" << endl;
        cout << setw(2) << (dimY_ - i);
        for (int j = 0; j < dimX_; ++j)
        {
            cout << " | " << map_[i][j];
        }
        cout << " |" << endl;
    }

    cout << "   ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-+-";
    }
    cout << "+" << endl;

    cout << "   ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << "  ";
        if (digit == 0)
            cout << "  ";
        else
            cout << digit << " ";
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "   " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

void Maps::changeDim(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
    map_.clear();
    init();
}
void Maps::changeZomb(int zomB)
{
    zomb_ = zomB;
    map_.clear();
    init();
}

int Maps::getDimX() const
{
    return dimX_;
}
int Maps::getDimY() const
{
    return dimY_;
}
int Maps::getZombCount() const
{
    return zomb_;
}
char Maps::getObject(int x, int y)
{
    return map_[dimY_ - y][x - 1];
}
void Maps::setObject(int x, int y, char ch) // set object to srand that's used
{
    map_[dimY_ - y][x - 1] = ch;
}
void Maps::setZombies(int xz, int yz, char Z)
{
    map_[yz][xz - 1] = Z;
}
void Maps::removeObjectUp(int x, int y, char ch)
{
    int delX = x;
    int delY = y - 1;
    map_[dimY_ - delY][delX - 1] = '.';
}
void Maps::removeObjectDown(int x, int y, char ch)
{
    int delX = x;
    int delY = y + 1;
    map_[dimY_ - delY][delX - 1] = '.';
}
void Maps::removeObjectLeft(int x, int y, char ch)
{
    int delX = x + 1;
    int delY = y;
    map_[dimY_ - delY][delX - 1] = '.';
}
void Maps::removeObjectRight(int x, int y, char ch)
{
    int delX = x - 1;
    int delY = y;
    map_[dimY_ - delY][delX - 1] = '.';
}
char Maps::detectObjectUp(int x, int y)
{
    int X = x;
    int Y = y + 1;
    return map_[dimY_ - Y][X - 1];
}
char Maps::detectObjectDown(int x, int y)
{
    int X = x;
    int Y = y - 1;
    return map_[dimY_ - Y][X - 1];
}
char Maps::detectObjectLeft(int x, int y)
{
    int X = x - 1;
    int Y = y;
    return map_[dimY_ - Y][X - 1];
}
char Maps::detectObjectRight(int x, int y)
{
    int X = x + 1;
    int Y = y;
    return map_[dimY_ - Y][X - 1];
}
void Maps::resetTrail() // reset trail with any random game objects(expect trail)
{
    char objects[] = {'^', '<', '>', 'v', 'h', 'p', 'r', ' ', ' ', ' ', ' '};
    int noOfObjects = 11;

    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            if (map_[i][j] == '.')
            {
                int objNo = rand() % noOfObjects;
                map_[i][j] = objects[objNo];
            }
        }
    }
}

Alien::Alien()
{
    dimX_ = 15;
    dimY_ = 5;
    zomb_ = 2;
    hp_ = 200;
    atk_ = 0;
    ch_ = 'A';
}

void Alien::start(Maps &maps)
{
    x_ = double(dimX_) / 2 + 1;
    y_ = double(dimY_) / 2 + 1;
    maps.setObject(x_, y_, ch_);
}

// alien's movements

void Alien::moveUp(Maps &maps, Zombies &zombie)
{
    while (y_ < dimY_)
    {
        char object = maps.detectObjectUp(x_, y_);
        if (object == ' ' || object == '.' || object == '^')
        {
            cout << "The alien is moving to the upward" << endl;
        }
        else if (object == 'v' || object == '<' || object == '>')
        {
            y_ = ++y_;
            maps.setObject(x_, y_, ch_);
            maps.removeObjectUp(x_, y_, ch_);
            Alien::objectBehaviour(maps, zombie, object);
            break;
        }
        else if (object == 'r')
        {
            char rock[] = {'h', 'p', '^', 'v', '<', '>', ' '};
            int noOfObject = 7;
            int ObjectNo = rand() % noOfObject;
            char stuff = rock[ObjectNo];
            maps.setObject(x_, y_ + 1, stuff);
            cout << "The alien encouter a rock. It stopped" << endl;
            cout << "Alien's turn ended" << endl;
            break;
        }
        else if(object=='1' || object =='2')
        {
            for(int i = 0; i < 2; i++)
            {
                if (object == zombie.allzombies[i][0])
                {
                    cout << "The alien encountered a zombie. It attacked the zombie." << endl;
                    cout << "Alien's turn ended" << endl;
                    break;
                }

                else
                {
                    cout<<"No zombie detected" << endl;
                    break;
                }
            }
        }
        else
        {
            Alien::objectBehaviour(maps, zombie, object);
        }
        x_ = ++x_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectRight(x_, y_, ch_);

    }
}
void Alien::moveDown(Maps &maps, Zombies &zombie)
{
    while (y_ > 1)
    {
        char object = maps.detectObjectDown(x_, y_);
        if (object == ' ' || object == '.' || object == 'v')
        {
            cout << "The alien is moving downward" << endl;
        }
        else if (object == '^' || object == '<' || object == '>')
        {
            y_ = --y_;
            maps.setObject(x_, y_, ch_);
            maps.removeObjectDown(x_, y_, ch_);
            Alien::objectBehaviour(maps, zombie, object);
            break;
        }
        else if (object == 'r')
        {
            char rock[] = {'h', 'p', '^', 'v', '<', '>', ' '};
            int noOfObject = 7;
            int ObjectNo = rand() % noOfObject;
            char stuff = rock[ObjectNo];
            maps.setObject(x_, y_ - 1, stuff);
            cout << "The alien encouter a rock. It stopped" << endl;
            cout << "Alien's turn ended" << endl;
            break;
        }
        else if(object=='1' || object =='2')
        {
            for(int i = 0; i < 2; i++)
            {
                if (object == zombie.allzombies[i][0])
                {
                    cout << "The alien encountered a zombie. It attacked the zombie." << endl;
                    cout << "Alien's turn ended" << endl;
                    break;
                }
                else
                {
                    cout<<"No zombie detected" << endl;
                    break;
                }
            }
        }
        else
        {
            Alien::objectBehaviour(maps, zombie, object);
        }
        x_ = ++x_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectRight(x_, y_, ch_);

    }
}
void Alien::moveLeft(Maps &maps, Zombies &zombie)
{
    while (x_ > 1)
    {
        char object = maps.detectObjectLeft(x_, y_);
        if (object == ' ' || object == '.' || object == '<')
        {
            cout << "The alien is moving to the left" << endl;
        }
        else if (object == 'v' || object == '^' || object == '>')
        {
            x_ = --x_;
            maps.setObject(x_, y_, ch_);
            maps.removeObjectLeft(x_, y_, ch_);
            Alien::objectBehaviour(maps, zombie, object);
            break;
        }
        else if (object == 'r')
        {
            char rock[] = {'h', 'p', '^', 'v', '<', '>', ' '};
            int noOfObject = 7;
            int ObjectNo = rand() % noOfObject;
            char stuff = rock[ObjectNo];
            maps.setObject(x_ - 1, y_, stuff);
            cout << "The alien encouter a rock. It stopped" << endl;
            cout << "Alien's turn ended" << endl;
            break;
        }
        else if(object=='1' || object =='2')
        {
            for(int i = 0; i < 2; i++)
            {
                if (object == zombie.allzombies[i][0])
                {
                    cout << "The alien encountered a zombie. It attacked the zombie." << endl;
                    cout << "Alien's turn ended" << endl;
                    break;
                }
                else
                {
                    cout<<"No zombie detected" << endl;
                    break;
                }
            }
        }
        else
        {
            Alien::objectBehaviour(maps, zombie, object);
        }
        x_ = ++x_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectRight(x_, y_, ch_);

    }
}
void Alien::moveRight(Maps &maps, Zombies &zombie)
{
    while (x_ < dimX_)
    {
        int xz_;
        int yz_;
        xz_ = zombie.getXZ();
        yz_ = zombie.getYZ();
        char object = maps.detectObjectRight(x_, y_);
        if (object == ' ' || object == '.' || object == '>')
        {
            cout << "The alien is moving to the right" << endl;
        }
        else if (object == 'v' || object == '<' || object == '^')
        {
            x_ = ++x_;
            maps.setObject(x_, y_, ch_);
            maps.removeObjectRight(x_, y_, ch_);
            Alien::objectBehaviour(maps, zombie, object);
            break;
        }
        else if (object == 'r')
        {
            char rock[] = {'h', 'p', '^', 'v', '<', '>', ' '};
            int noOfObject = 7;
            int ObjectNo = rand() % noOfObject;
            char stuff = rock[ObjectNo];
            maps.setObject(x_ + 1, y_, stuff);
            cout << "The alien encouter a rock. It stopped" << endl;
            cout << "Alien's turn ended" << endl;
            break;
        }
        else if(object=='1' || object =='2')
        {
            for(int i = 0; i < 2; i++)
            {
                if (object == zombie.allzombies[i][0])
                {
                    cout << "The alien encountered a zombie. It attacked the zombie." << endl;
                    cout << "Alien's turn ended" << endl;
                    break;
                }
                else
                {
                    cout<<"No zombie detected" << endl;
                    break;
                }
            }
        }

        else
        {
            Alien::objectBehaviour(maps, zombie, object);
        }
        x_ = ++x_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectRight(x_, y_, ch_);

    }
}

void Alien::changeDim(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
}
void Alien::changeZomb(int zomB)
{
    zomb_ = zomB;
}
void Alien::changeHP(int hp)
{
    hp_ = hp_ + hp;
    if (hp_ < 200)
    {
    }
    else if (hp_ >= 200)
    {
        hp_ = 200;
    }
}
void Alien::minusHP(Maps &maps)
{
    hp_ = hp_ - (5 * maps.getZombCount());
}
void Alien::resetATK()
{
    atk_ = 0;
}
void Alien::addATK(int atk)
{
    atk_ = atk_ + atk;
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
int Alien::getHP() const
{
    return hp_;
}
int Alien::getATK() const
{
    return atk_;
}

// object's behaviours within the board;

void Alien::objectBehaviour(Maps &board, Zombies &zombie, char object)
{
    int i = rand() % board.getZombCount();
    i = i + 1;
    switch (object)
    {
    case '^':
        Alien::addATK(20);
        cout << "Alien meet '^'." << endl;
        Alien::moveUp(board, zombie);
        break;
    case 'v':
        Alien::addATK(20);
        cout << "Alien meet 'v'." << endl;
        Alien::moveDown(board, zombie);
        break;
    case '<':
        Alien::addATK(20);
        cout << "Alien meet '<'." << endl;
        Alien::moveLeft(board, zombie);
        break;
    case '>':
        Alien::addATK(20);
        cout << "Alien meet '>'." << endl;
        Alien::moveRight(board, zombie);
        break;
    case 'h':
        Alien::changeHP(20);
        break;
    case 'p':
        zombie.changeHP(i, -20);
        break;
    default:
        break;
    }
}

// zombies' attributes

Zombies::Zombies()
{
    hpz_ = 100;
    atkz_ = 20;
}

// spawning the zombies onto the board

void Zombies::spawn(Maps &maps) // to place the zombie the in the board
{
    allzombies.resize(maps.getZombCount());

    for (int i = 1; i <= maps.getZombCount(); i++)
    {
        vector<int> zombie; // making a vector to store x1 and y1 value of the zombies
        for (int j = 0; j < 1; j++)
        {
            char Z_ = '0' + i; // to determined the nth zombies
            int xz_ = rand() % maps.getDimX();
            int yz_ = rand() % maps.getDimY();

            zombie.push_back(xz_); // generate a random x1
            zombie.push_back(yz_);
            maps.setZombies(xz_, yz_, Z_);
        }
        allzombies.push_back(zombie); // add the generated array to the vector of arrays
    }
    initialZombHP(maps);
    initialZombATK(maps);
}

void Zombies::initialZombHP(Maps &maps)
{
    zombiehp.resize(maps.getZombCount());
    int hpz = 100;
    for (int i = 1; i <= maps.getZombCount(); i++)
    {
        zombiehp[i].hpz_ = hpz;
    }
}

void Zombies::initialZombATK(Maps &maps)
{
    zombieatk.resize(maps.getZombCount());
    int atkz = 20;
    for (int i = 1; i <= maps.getZombCount(); i++) // to access each zombies in the vector
    {
        zombieatk[i].atkz_ = atkz;
    }
}

// get and set the x's and y's positional value for the zombies

int Zombies::getXZ() const
{
    return xz_;
}
int Zombies::getYZ() const
{
    return yz_;
}
int Zombies::getHPZ(int i)
{
    int hp = zombiehp[i].hpz_;
    return hp;
}
int Zombies::getATKZ(int i)
{
    int atk = zombieatk[i].atkz_;
    return atk;
}
int Zombies::getTotalHPZ(Maps maps)
{
    int total;
    for (int i = 1; i <= maps.getZombCount(); i++)
    {
        total += zombiehp[i].hpz_;
    }
    return total;
}
char Zombies::getZ() const
{
    return Z_;
}

void Zombies::changeHP(int i, int hp)
{
    zombiehp[i].hpz_ = zombiehp[i].hpz_ + hp;
}

// movements for the zombies to change the x and y values

void Zombies::moveleft_z()
{
    xz_ = xz_ - 1;
}

void Zombies::moveright_z()
{
    xz_ = xz_ + 1;
}

void Zombies::moveup_z()
{
    yz_ = yz_ + 1;
}

void Zombies::movedown_z()
{
    xz_ = xz_ - 1;
}

// moving diagnonally

// void Zombies::moveupleft_z()
//{
//     xz_ -= 1;
//     yz_ += 1;
// }

// void Zombies::moveupright_z()
//{
//     xz_ += 1;
//     yz_ += 1;
// }

// void Zombies::movedownleft_z()
//{
//     xz_ -= 1;
//     yz_ -= 1;
// }

// void Zombies::movedownright_z()
//{
//     xz_ += 1;
//     yz_ -= 1;
// }

// random movements for the zombies to change the values of char and setting the objects

// void Zombies::move_z(Maps &maps, Alien &Alien)
// {

//     for (int i = 1; i < size(allzombies); i++)
//     {
//         for (int j = 0; j < size(allzombies[i]); j++)
//         {
//             int random = rand() % 4;

//             if (random = 1)
//             {
//                 char objectleft = maps.detectObjectLeft(xz_, yz_);
//                 if (xz_ > 1)
//                 {
//                     moveleft_z();
//                     maps.setObject(xz_, yz_, allzombies[i][1]);
//                     maps.removeObjectLeft(xz_, yz_, allzombies[i][1]);
//                 }

//                 else
//                 {
//                     cout << "The zombie encounter wall. It stoped moving" << endl;
//                     cout << "Zombie " << allzombies[i][1] << "'s ended" << endl;
//                 }
//             }

//             else if (random = 2)
//             {
//                 char objectright = maps.detectObjectRight(xz_, yz_);
//                 if (xz_ < maps.getDimX())
//                 {
//                     moveright_z();
//                     maps.setObject(xz_, yz_, allzombies[i][1]);
//                     maps.removeObjectRight(xz_, yz_, allzombies[i][1]);
//                 }

//                 else
//                 {
//                     cout << "The zombie encounter wall. It stoped moving" << endl;
//                     cout << "Zombie " << allzombies[i][1] << "'s ended"<< endl;
//                 }
//             }

//             else if (random = 3)
//             {
//                 char objectdown = maps.detectObjectDown(xz_, yz_);
//                 movedown_z();
//                 if (yz_ > 1)
//                 {
//                     movedown_z();
//                     maps.setObject(xz_, yz_, allzombies[i][1]);
//                     maps.removeObjectDown(xz_, yz_, allzombies[i][1]);
//                 }

//                 else
//                 {
//                     cout << "The zombie encounter wall. It stoped moving" << endl;
//                     cout << "Zombie " << allzombies[i][1] << "'s ended"<< endl;
//                 }
//             }

//             else
//             {
//                 char objectup = maps.detectObjectUp(xz_, yz_);
//                 if (yz_ < maps.getDimY())
//                 {
//                     moveup_z();
//                     maps.setObject(xz_, yz_, allzombies[i][1]);
//                     maps.removeObjectUp(xz_, yz_, allzombies[i][1]);
//                 }

//                 else
//                 {
//                     cout << "The zombie encounter wall. It stoped moving" << endl;
//                     cout << "Zombie " << allzombies[i][1] << "'s turn ended"<< endl;
//                 }
//             }

//             // else if (random = 5)
//             // {
//             //     char objectz = maps.detectObjectUp(xz_, yz_);
//             //     char objectz = maps.detectObjectLeft(xz_, yz_);
//             //     if (objectz != '-' || objectz != '+' || objectz != '|')
//             //     {
//             //         moveupleft_z();
//             //         maps.setObject(xz_, yz_, allzombies[i][1]);
//             //         maps.removeObjectUp(xz_, yz_, allzombies[i][1]);
//             //     }

//             //     else
//             //     {
//             //         cout << "The zombie encounter wall. It stoped moving" << endl;
//             //         cout << "Zombie " << allzombies[i][1] << "'s ended"<< endl;
//             //     }
//             // }

//             // else if (random = 6)
//             // {
//             //     char objectz = maps.detectObjectUp(xz_, yz_);
//             //     char objectz = maps.detectObjectRight(xz_, yz_);
//             //     if (objectz != '-' || objectz != '+' || objectz != '|')
//             //     {
//             //         moveupright_z();
//             //         maps.setObject(xz_, yz_, allzombies[i][1]);
//             //         maps.removeObjectUp(xz_, yz_, allzombies[i][1]);
//             //     }

//             //     else
//             //     {
//             //         cout << "The zombie encounter wall. It stoped moving" << endl;
//             //         cout << "Zombie " << allzombies[i][1] << "'s ended"<< endl;
//             //     }
//             // }

//             // else if (random = 7)
//             // {
//             //     char objectz = maps.detectObjectDown(xz_, yz_);
//             //     char objectz = maps.detectObjectLeft(xz_, yz_);
//             //     if (objectz != '-' || objectz != '+' || objectz != '|')
//             //     {
//             //         movedownleft_z();
//             //         maps.setObject(xz_, yz_, allzombies[i][1]);
//             //         maps.removeObjectUp(xz_, yz_, allzombies[i][1]);
//             //     }

//             //     else
//             //     {
//             //         cout << "The zombie encounter wall. It stoped moving" << endl;
//             //         cout << "Zombie " << allzombies[i][1] << "'s ended"<< endl;
//             //     }
//             // }

//             // else
//             // {
//             //     char objectz = maps.detectObjectDown(xz_, yz_);
//             //     char objectz = maps.detectObjectRight(xz_, yz_);
//             //     if (objectz != '-' || objectz != '+' || objectz != '|')
//             //     {
//             //         movedownright_z();
//             //         maps.setObject(xz_, yz_, allzombies[i][1]);
//             //         maps.removeObjectUp(xz_, yz_, allzombies[i][1]);
//             //     }

//             //     else
//             //     {
//             //         cout << "The zombie encounter wall. It stoped moving" << endl;
//             //         cout << "Zombie " << allzombies[i][1] << "'s ended"<< endl;
//             //     }
//             //}
//         }
//     }
// }

// display attributes i.e health, attack, range, for the alien and also zombies

void LifeAttackDisplay(Maps &maps, Alien &alien, Zombies &zombie)
{
    int alienHP;
    int alienATK;

    alienHP = alien.getHP();
    alienATK = alien.getATK();

    cout << "Alien    : "
         << "Life : " << alienHP << " , "
         << "Attack:"
         << " " << alienATK << " " << endl;
    for (int i = 1; i <= maps.getZombCount(); i++) // to access each zombies
    {
        cout << "Zombie " << i << ": "
             << " Life : " << zombie.getHPZ(i) << " , "
             << "Attack : " << zombie.getATKZ(i) << endl;
    }
}

// saving the game

void save_game(string file_name)
{
    ofstream file;
    file.open(file_name);

    string data_to_save;
    cout << "Enter the data to save in the file: ";
    getline(cin, data_to_save);

    file << data_to_save;
    file.close();

    cout << "Data saved successfully in the file: " << file_name << endl;
}

// loading the game

void load_game(string file_name)
{
    ifstream file;
    file.open(file_name);

    string loaded_data;
    while (getline(file, loaded_data))
    {
        cout << loaded_data << endl;
    }

    file.close();
    cout << "Data loaded successfully from the file: " << file_name << endl;
}

// saving the progress in game

void Saved_CurrentGame()
{
    cout << "Do you want to save the ongoing game (y/n)? ";
    char save_choice;
    cin >> save_choice;

    if (save_choice == 'y')
    {
        cout << "Enter the name of the game file: ";
        string file_name;
        cin >> file_name;
        save_game(file_name);
    }
}

// loading the previously saved game

void LoadMenu()
{
    cout << "Do you want to load a game (y/n)? ";
    char load_choice;
    cin >> load_choice;

    if (load_choice == 'y')
    {
        cout << "Enter the name of the game file: ";
        string file_name;
        cin >> file_name;
        load_game(file_name);
    }
}

// user's commands for the gameplay

void Command(Maps &board, Alien &attack, Zombies &zombie, bool &end)
{
    cout << "Command: ";
    string command;
    cin >> command;

    if (command.compare("up") == 0)
    {
        cout << "The alien is moving upward." << endl;
        attack.moveUp(board, zombie);
    }
    else if (command.compare("down") == 0)
    {
        cout << "The alien is moving downward." << endl;
        attack.moveDown(board, zombie);
    }
    else if (command.compare("left") == 0)
    {
        cout << "The alien is moving to the left." << endl;
        attack.moveLeft(board, zombie);
    }
    else if (command.compare("right") == 0)
    {
        cout << "The alien is moving to the right." << endl;
        attack.moveRight(board, zombie);
    }
    else if (command.compare("arrow") == 0)
    {
        bool loop = true;
        bool loop2 = true;
        int x, y;
        string direction;
        while (loop2 == true)
        {
            cout << "Enter Row: ";
            cin >> y;
            cout << "Enter Column: ";
            cin >> x;
            if (x > board.getDimX() || y > board.getDimY())
            {
                cout << "Please enter Row and Column within the board dimension." << endl
                     << endl;
            }
            else if (board.getObject(x, y) != '^' && board.getObject(x, y) != 'v' && board.getObject(x, y) != '<' && board.getObject(x, y) != '>')
            {
                cout << "This Coordinate has no arrow." << endl
                     << endl;
            }
            else
            {
                loop2 = false;
            }
        }
        while (loop == true)
        {
            cout << "Enter Direction (up/down/left/right): ";
            cin >> direction;
            if (direction.compare("up") == 0)
            {
                board.setObject(x, y, '^');
                loop = false;
            }
            else if (direction.compare("down") == 0)
            {
                board.setObject(x, y, 'v');
                loop = false;
            }
            else if (direction.compare("left") == 0)
            {
                board.setObject(x, y, '<');
                loop = false;
            }
            else if (direction.compare("right") == 0)
            {
                board.setObject(x, y, '>');
                loop = false;
            }
            else
            {
                cout << "Your direction input is invalid." << endl
                     << endl;
            }
        }
    }
    else if (command.compare("help") == 0)
    {
        cout << "up    = Move alien upwards." << endl;
        cout << "down  = Move alien downwards." << endl;
        cout << "left  = Move alien towards the left." << endl;
        cout << "right = Move alien towards the right." << endl;
        cout << "arrow = Switch the direction of an arrow object in the game board." << endl;
        cout << "save  = Save the current game." << endl;
        cout << "load  = Load a saved game." << endl;
        cout << "help  = Display and explains all the commands." << endl;
        cout << "quit  = Quit the game." << endl;
    }
    else if (command.compare("save") == 0)
    {
        Saved_CurrentGame();
    }
    else if (command.compare("load") == 0)
    {
        LoadMenu();
    }
    else if (command.compare("quit") == 0)
    {
        char decision;
        cout << "Are you sure you want to stop playing? (y/n)" << endl;
        cin >> decision;
        if (decision == 'y')
        {
            end = true;
        }
        else if (decision == 'n')
        {
        }
        else
        {
            cout << "Please enter either y(YES) or n(NO)." << endl;
        }
    }
    else
    {
        cout << "Error, use command: help to learn about the commands.";
    }
}

// initialising the gameplay turn

void oneTurn(Maps &board, Alien &attack, Zombies &zombies, bool &end)
{
    board.resetTrail();
    board.display();
    LifeAttackDisplay(board, attack, zombies);
    Command(board, attack, zombies, end);
    attack.minusHP(board);
    // zombies.move_z(board, attack);

    if (attack.getHP() <= 0)
    {
        end = true;
        cout << "The Zombies Has Win the Game..";
    }
    else if (zombies.getTotalHPZ(board) <= 0)
    {
        end = true;
        cout << "Alien Has Win the Game!!";
    }
}

// the main menu for the game

int mainMenu()
{
    int pick;
    cout << " ::==::==::==::==::==::==::==::==::" << endl;
    cout << " <= Welcome to Alien VS Zombies! =>" << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl
         << endl;
    cout << "Please pick an option below:       " << endl;
    cout << "1. Play the Game                   " << endl;
    cout << "2. Load File                       " << endl;
    cout << "3. Settings                        " << endl;
    cout << "4. Quit                            " << endl
         << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl;
    cout << endl
         << "=> ";
    cin >> pick;
    return pick;
}

// changing the game's setting option for the user

void changeSettings(Maps &board, Alien &attack)
{
    int row;
    int column;
    int zombie;
    bool temp1 = true;
    bool temp2 = true;
    bool temp3 = true;
    cout << " ::==::==::==::==::==::==::==::==::" << endl;
    cout << "        Change Game Settings       " << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl
         << endl;
    cout << "Board Rows      : " << board.getDimY() << endl;
    cout << "Board Columns   : " << board.getDimX() << endl;
    cout << "Zombie Count    : " << board.getZombCount() << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl
         << endl;
    while (temp1 == true)
    {
        cout << "Board Rows => ";
        cin >> row;
        if (row % 2 == 0)
        {
            cout << "Please Enter Odd Number" << endl;
        }
        else
        {
            temp1 = false;
        }
    }
    while (temp2 == true)
    {
        cout << "Board Columns => ";
        cin >> column;
        if (column % 2 == 0)
        {
            cout << "Please Enter Odd Number" << endl;
        }
        else
        {
            temp2 = false;
        }
    }
    while (temp3 == true)
    {
        cout << "Enter number of zombies (1 - 9): ";
        cin >> zombie;
        if (zombie > 10)
        {
            cout << " " << endl;
            cout << "Number of zombie must below than 10" << endl;
        }
        else
        {
            temp3 = false;
        }
    }
    board.changeDim(column, row);
    attack.changeDim(column, row);
    board.changeZomb(zombie);
    attack.changeZomb(zombie);
    cout << endl
         << "Settings Updated !!" << endl;
}

// the main page for the user to change the setting

void settingsMenu(Maps &board, Alien &attack)
{
    bool temp = true;
    char pick;
    cout << " ::==::==::==::==::==::==::==::==::" << endl;
    cout << "        Default Game Settings      " << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl
         << endl;
    cout << "Board Rows      : " << board.getDimY() << endl;
    cout << "Board Columns   : " << board.getDimX() << endl;
    cout << "Zombie Count    : " << board.getZombCount() << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl
         << endl;
    while (temp == true)
    {
        cout << "Change Game Settings? (Y/N)" << endl;
        cout << "=> ";
        cin >> pick;
        pick = toupper(pick);
        switch (pick)
        {
        case 'Y':
            temp = false;
            changeSettings(board, attack);
            break;
        case 'N':
            temp = false;
            break;
        default:
            cout << "Please Input Either Y or N" << endl;
            break;
        }
    }
}

// the main loop for the game - options to start game / load / quit etc
void mainLoop(Maps &board, Alien &attack, Zombies &zombies, bool &end)
{
    bool temp = true;
    int option;
    while (temp == true)
    {
        option = mainMenu();
        switch (option)
        {
        case 1:
            attack.start(board);
            zombies.spawn(board);
            while (end == false)
            {
                oneTurn(board, attack, zombies, end);
                cout << endl;
            }
            temp = false;
            break;

        case 2:
            LoadMenu();
            cout << endl;
            break;

        case 3:
            settingsMenu(board, attack);
            cout << endl;
            break;

        case 4:
            temp = false;
            break;

        default:
            cout << "Invalid Option.." << endl;
            break;
        }
    }
}

// the game
int main()
{
    srand(time(NULL));
    Maps board;
    Alien attack;
    Zombies zombies;
    bool end = false;
    mainLoop(board, attack, zombies, end);
}