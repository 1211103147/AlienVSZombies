
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

    void setObject(int x, int y, char ch);
    void setZombies(int x1, int y1, char Z);
    void removeObjectUp(int x, int y, char ch);
    void removeObjectDown(int x, int y, char ch);
    void removeObjectLeft(int x, int y, char ch);
    void removeObjectRight(int x, int y, char ch);
    char detectObjectUp(int x,int y);
    char detectObjectDown(int x,int y);
    char detectObjectLeft(int x,int y);
    char detectObjectRight(int x,int y);
};

class Alien
{
private:
    int x_, y_;
    char ch_;
    int dimX_,dimY_, zomb_;
    int hp_, atk_;
public:
    Alien();
    void start(Maps &maps);
    
    void moveUp(Maps &maps);
    void moveDown(Maps &maps);
    void moveLeft(Maps &maps);
    void moveRight(Maps &maps);
    
    void changeDim(int dimX,int dimY);
    void changeZomb(int zomB);
    
    void objectBehaviour(Maps &maps,char object);

    int getX() const;
    int getY() const;
    char getch() const;
    int getHP() const;
    int getATK() const;
};

class Zombies
{
private:
    int x1_, y1_;
    char Z_;
public:
    Zombies();
    void spawn(Maps &maps);

    int getX1() const;
    int getY1() const;
    char getZ() const;
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

void Maps::setObject(int x, int y, char ch)
{
    map_[dimY_ - y][x - 1] = ch;
}
void Maps::setZombies(int x1, int y1, char Z)
{
    map_[dimY_ - y1][x1 - 1] = Z;
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
    x_ = double(dimX_) /2 +1;
    y_ = double(dimY_) /2 +1;
    maps.setObject(x_, y_, ch_);
}

void Alien::moveUp(Maps &maps)
{
    while (y_< dimY_)
    {
        char object = maps.detectObjectUp(x_,y_);
        if (object == ' ' ||object == '.' ||object == '^')
        {}
        else if (object == 'v' ||object == '<' ||object == '>')
        {
            y_ = ++y_;
            maps.setObject(x_, y_, ch_);
            maps.removeObjectUp(x_, y_, ch_);
            Alien::objectBehaviour(maps,object);
            break;
        }
        else
        {
            Alien::objectBehaviour(maps,object);
            break;
        }
        y_ = ++y_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectUp(x_, y_, ch_);
    }
}
void Alien::moveDown(Maps &maps)
{
    while (y_> 1)
    {
        char object = maps.detectObjectDown(x_,y_);
        if (object == ' ' ||object == '.'||object == 'v')
        {}
        else if (object == '^' ||object == '<' ||object == '>')
        {
            y_ = --y_;
            maps.setObject(x_, y_, ch_);
            maps.removeObjectDown(x_, y_, ch_);
            Alien::objectBehaviour(maps,object);
            break;
        }
        else
        {
            Alien::objectBehaviour(maps,object);
            break;
        }
        y_ = --y_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectDown(x_, y_, ch_);
    }
}
void Alien::moveLeft(Maps &maps)
{
    while (x_> 1)
    {
        char object = maps.detectObjectLeft(x_,y_);
        if (object == ' ' ||object == '.'||object == '<')
        {}
        else if (object == 'v' ||object == '^' ||object == '>')
        {
            x_ = --x_;
            maps.setObject(x_, y_, ch_);
            maps.removeObjectLeft(x_, y_, ch_);
            Alien::objectBehaviour(maps,object);
            break;
        }
        else
        {
            Alien::objectBehaviour(maps,object);
            break;
        }
        x_ = --x_;
        maps.setObject(x_, y_, ch_);
        maps.removeObjectLeft(x_, y_, ch_);
    }
}
void Alien::moveRight(Maps &maps)
{
    while (x_< dimX_)
    {
        char object = maps.detectObjectRight(x_,y_);
        if (object == ' ' ||object == '.'||object == '>')
        {}
        else if (object == 'v' ||object == '<' ||object == '^')
        {
            x_ = ++x_;
            maps.setObject(x_, y_, ch_);
            maps.removeObjectRight(x_, y_, ch_);
            Alien::objectBehaviour(maps,object);
            break;
        }
        else
        {
            Alien::objectBehaviour(maps,object);
            break;
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

void Alien::objectBehaviour(Maps &board,char object)
{
    switch (object)
    {
    case '^':
        Alien::moveUp(board);
        break;
    case 'v':
        Alien::moveDown(board);
        break;
    case '<':
        Alien::moveLeft(board);
        break;
    case '>':
        Alien::moveRight(board);
        break;
    case 'h':
        /* code */
        break;
    case 'r':
        /* code */
        break;
    default:
        break;
    }
}
// let's there is a array that holds the life and attacks attributes of the aliens and also the upcoming zombies (zombies are not initialised yet)

Zombies::Zombies()
{
}

void Zombies::spawn(Maps &maps)
{
    for (int i = 1; i <= maps.getZombCount(); ++i)
    {
        char Z_ = '0' + i ;
        int x1_ = rand() % maps.getDimX();
        int y1_ = rand() % maps.getDimY();
        maps.setZombies(x1_,  y1_, Z_);
    }
}

int Zombies::getX1() const
{
    return x1_;
}
int Zombies::getY1() const
{
    return y1_;
}
char Zombies::getZ() const
{
    return Z_;
}

void LifeAttackDisplay(Alien &alien)
{
    int alienHP;
    int alienATK;

    alienHP = alien.getHP();
    alienATK = alien.getATK();

    cout << "Alien    : " << "Life :" << " " << alienHP << " , " << "Attack:" << " " << alienATK << " " << endl;
    //cout << "Zombie 1 : " << "Life :" << " " << "life" << " " << "Attack:" << " " << "attack" << " " << endl;
    //cout << "Zombie 2 : " << "Life :" << " " << "life" << " " << "Attack:" << " " << "attack" << " " << endl;
}

// saving the game
void Movement(Maps &board, Alien &attack)
{
    cout << "Movement: ";
    string move;
    cin >> move;
    
    if (move.compare("up") == 0)
    {
        attack.moveUp(board);
    }
    else if (move.compare("down") == 0)
    {
        attack.moveDown(board);
    }
    else if (move.compare("left") == 0)
    {
        attack.moveLeft(board);
    }
    else if (move.compare("right") == 0)
    {
        attack.moveRight(board);
    }
    else
    {
        cout << "error";
    }
}

void save_game(string file_name) {
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

void load_game(string file_name) {
    ifstream file;
    file.open(file_name);

    string loaded_data;
    while (getline(file, loaded_data)) {
        cout << loaded_data << endl;
    }

    file.close();
    cout << "Data loaded successfully from the file: " << file_name << endl;
}

// saving the progress in game

void Saved_CurrentGame() {
    cout << "Do you want to save the ongoing game (y/n)? ";
    char save_choice;
    cin >> save_choice;

    if (save_choice == 'y') {
        cout << "Enter the name of the game file: ";
        string file_name;
        cin >> file_name;
        save_game(file_name);
    } 
}

// loading the previously saved game

void LoadMenu() {
    cout << "Do you want to load a game (y/n)? ";
    char load_choice;
    cin >> load_choice;

    if (load_choice == 'y') {
        cout << "Enter the name of the game file: ";
        string file_name;
        cin >> file_name;
        load_game(file_name);
    }
}

void oneTurn(Maps &board,Alien &attack,Zombies &zombies)
{
    board.display();
    LifeAttackDisplay(attack);
    Movement(board, attack);
}
int mainMenu()
{
    int pick;
    cout << " ::==::==::==::==::==::==::==::==::" << endl;
    cout << " <= Welcome to Alien VS Zombies! =>" << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl << endl;
    cout << "Please pick an option below:       " << endl;
    cout << "1. Play the Game                   " << endl;
    cout << "2. Load File                       " << endl;
    cout << "3. Settings                        " << endl;
    cout << "4. Quit                            " << endl << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl;
    cout << endl << "=> ";
    cin >> pick;
    return pick;
}

void changeSettings(Maps &board,Alien &attack)
{
    int row;
    int column;
    int zombie;
    bool temp1 = true;
    bool temp2 = true;
    bool temp3 = true;
    cout << " ::==::==::==::==::==::==::==::==::" << endl;
    cout << "        Change Game Settings       " << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl << endl;
    cout << "Board Rows      : " << board.getDimY() << endl;
    cout << "Board Columns   : " << board.getDimX() << endl;
    cout << "Zombie Count    : " << board.getZombCount() << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl << endl;
    while (temp1 == true)
    {
        cout << "Board Rows => ";
        cin >> row;
        if (row%2==0)
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
        if (column%2==0)
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
    board.changeDim(column,row);
    attack.changeDim(column,row);
    board.changeZomb(zombie);
    attack.changeZomb(zombie);
    cout << endl << "Settings Updated !!" << endl;
}
void settingsMenu(Maps &board,Alien &attack)
{
    bool temp = true;
    char pick;
    cout << " ::==::==::==::==::==::==::==::==::" << endl;
    cout << "        Default Game Settings      " << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl << endl;
    cout << "Board Rows      : " << board.getDimY() << endl;
    cout << "Board Columns   : " << board.getDimX() << endl;
    cout << "Zombie Count    : " << board.getZombCount() << endl;
    cout << " ::==::==::==::==::==::==::==::==::" << endl << endl;
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
            changeSettings(board,attack);
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
void mainLoop(Maps &board,Alien &attack, Zombies& zombies)
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
            while (true)
            {
                oneTurn(board,attack, zombies);
                cout << endl;
            }
            break;
            
        case 2:
            LoadMenu();
            cout << endl;
            break;
            
        case 3:
            settingsMenu(board,attack);
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

int main()
{
    srand(time(NULL));
    Maps board;
    Alien attack;
    Zombies zombies;
    mainLoop(board,attack, zombies);
}