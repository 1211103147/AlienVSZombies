
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
    char getObject(int x,int y);

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
    void changeHP(int hp);
    void resetATK();
    void addATK(int atk);
    
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
    int x1_, y1_, range;
    char Z_;
public:
    Zombies();
    void spawn(Maps &maps);

    int getX1() const;
    int getY1() const;
    char getZ() const;
    void move() const;
    int getrange() const;
    int setrange() const;
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
char Maps::getObject(int x,int y)
{
    return map_[dimY_ - y][x - 1];
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
            cout << "The alien is moving up" << endl;
            cout << "Alien's turn end"<< endl;
            break;
        }
        else if (object == 'r')
        {
            char rock[] = {'h','p','^','v','<','>',' '};
            int noOfObject = 7;
            int ObjectNo = rand() % noOfObject;
            char stuff = rock[ObjectNo];
            maps.setObject(x_,y_+1,stuff);
            cout << "The alien is moving up" << endl;
            cout << "The alien is stopped by a rock."<< endl;
            cout << "Alien's turn end"<< endl;
            break;
        }
        else
        {
            Alien::objectBehaviour(maps,object);
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
            cout << "The alien is moving down" << endl;
            cout << "Alien's turn end"<< endl;
            break;
        }
        else if (object == 'r')
        {
            char rock[] = {'h','p','^','v','<','>',' '};
            int noOfObject = 7;
            int ObjectNo = rand() % noOfObject;
            char stuff = rock[ObjectNo];
            maps.setObject(x_,y_-1,stuff);
            cout << "The alien is moving down" << endl;
            cout << "The alien is stopped by a rock."<< endl;
            cout << "Alien's turn end"<< endl;
            break;
        }
        else
        {
            Alien::objectBehaviour(maps,object);
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
            cout << "The alien is moving to the left"<< endl;
            cout << "Alien's turn end"<< endl;
            break;
        }
        else if (object == 'r')
        {
            char rock[] = {'h','p','^','v','<','>',' '};
            int noOfObject = 7;
            int ObjectNo = rand() % noOfObject;
            char stuff = rock[ObjectNo];
            maps.setObject(x_-1,y_,stuff);
            cout << "The alien is moving to the left" << endl;
            cout << "The alien is stopped by a rock."<< endl;
            cout << "Alien's turn end"<< endl;
            break;
        }
        else
        {
            Alien::objectBehaviour(maps,object);
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
            cout << "The alien is moving to the right"<< endl;
            cout << "Alien's turn end"<< endl;
            break;
        }
        else if (object == 'r')
        {
            char rock[] = {'h','p','^','v','<','>',' '};
            int noOfObject = 7;
            int ObjectNo = rand() % noOfObject;
            char stuff = rock[ObjectNo];
            maps.setObject(x_+1,y_,stuff);
            cout << "The alien is moving to the right" << endl;
            cout << "The alien is stopped by a rock."<< endl;
            cout << "Alien's turn end"<< endl;
            break;
        }
        else
        {
            Alien::objectBehaviour(maps,object);
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
    {}
    else if (hp_ >= 200)
    {
        hp_ = 200;
    }
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

void Alien::objectBehaviour(Maps &board,char object)
{
    switch (object)
    {
    case '^':
        Alien::addATK(20);
        Alien::moveUp(board);
        break;
    case 'v':
        Alien::addATK(20);
        Alien::moveDown(board);
        break;
    case '<':
        Alien::addATK(20);
        Alien::moveLeft(board);
        break;
    case '>':
        Alien::addATK(20);
        Alien::moveRight(board);
        break;
    case 'h':
        Alien::changeHP(20);
    case 'p':
        /* code */
        break;
    default:
        break;
    }
}

Zombies::Zombies()
{
}

void Zombies::spawn(Maps &maps) // placing the zombies on the maps
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

void Zombies::move() const
{

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

void Command(Maps &board, Alien &attack,bool &end)
{
    cout << "Command: ";
    string command;
    cin >> command;
    
    if (command.compare("up") == 0)
    {
        attack.moveUp(board);
    }
    else if (command.compare("down") == 0)
    {
        attack.moveDown(board);
    }
    else if (command.compare("left") == 0)
    {
        attack.moveLeft(board);
    }
    else if (command.compare("right") == 0)
    {
        attack.moveRight(board);
    }
    else if (command.compare("arrow") == 0)
    {
        bool loop = true;
        bool loop2 = true;
        int x,y;
        string direction;
        while (loop2 == true)
        {
            cout << "Enter Row: ";
            cin >> y;
            cout << "Enter Column: ";
            cin >> x;
            if (x > board.getDimX() || y > board.getDimY())
            {
                cout << "Please enter Row and Column within the board dimension." << endl << endl;
            }
            else if (board.getObject(x,y) != '^' && board.getObject(x,y) != 'v' && board.getObject(x,y) != '<' && board.getObject(x,y) != '>')
            {
                cout << "This Coordinate has no arrow." << endl << endl;
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
                board.setObject(x,y,'^');
                loop = false;
            }
            else if (direction.compare("down") == 0)
            {
                board.setObject(x,y,'v');
                loop = false;
            }
            else if (direction.compare("left") == 0)
            {
                board.setObject(x,y,'<');
                loop = false;
            }
            else if (direction.compare("right") == 0)
            {
                board.setObject(x,y,'>');
                loop = false;
            }
            else
            {
                cout << "Your direction input is invalid." << endl << endl;
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
        {}
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

void oneTurn(Maps &board,Alien &attack,Zombies &zombies,bool &end)
{
    board.display();
    LifeAttackDisplay(attack);
    Command(board,attack,end);
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
void mainLoop(Maps &board,Alien &attack, Zombies& zombies,bool &end)
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
                oneTurn(board,attack,zombies,end);
                cout << endl;
            }
            temp = false;
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
    bool end = false;
    mainLoop(board,attack,zombies,end);
}