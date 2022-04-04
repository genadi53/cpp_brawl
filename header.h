#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <random>
#include<ctime>
#include<cstdlib>

using namespace std;

class Fighter {
    public: 
        Fighter();
        Fighter(string name, int hp);
        ~Fighter();

        string getFighterName();
        void setFighterName(string fighterName);

        int getFighterHP();
        void setFighterHP(int hp);

        bool getIsWinner();
        void setIsWinner(bool isWinner);

        bool getIsEliminated();
        void setIsEliminated(bool isEliminated);

        int dealDamage();

    private:
        string fighterName;
        int fighterHP; 
        bool isWinner;
        bool isEliminated;
};

class Brawl {
    public: 
        Brawl();
        ~Brawl();

        vector<Fighter> getFighters();
        void setFighters(vector<Fighter>& fighters);

        void generateRandomFighters(int num);
        void generateFighters();
        void drinkAndHeal();
        void printFightersNames();
        void shuffleFightersOrder();
        void fight(Fighter* f1, Fighter* f2);
        void startBrawl();
        int returnIndex(string fighterName);
        void removeLosers();

    private:
      vector<Fighter> fighters;  
};


void printMenuOptions();
int getValidNumber();
int generateRandomNumber(int lower, int higher);
int generateRandomNumberWithRand(int lower, int higher);
void generateRandomPairs(int higher);
