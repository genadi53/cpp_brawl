#ifndef Fighters_H
#define Fighters_H

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

        int dealDamage();

    private:
        string fighterName;
        int fighterHP; 
        bool isWinner;
};

void generateRandomFighters(vector<Fighter>& fighters, int num);
void generateFighters(vector<Fighter>& fighters);
void drinkAndHeal(vector<Fighter>& fighters);
void printFightersNames(vector<Fighter>& fighters);
void printMenuOptions();
int getValidNumber();
int generateRandomNumber(int lower, int higher);
void shuffleFightersOrder(vector<Fighter>& fighters);
int generateRandomNumberWithRand(int lower, int higher);
void fight(vector<Fighter>& fighters, Fighter f1, Fighter f2);
void generateRandomPairs(int higher);
void startBrawl(vector<Fighter>& fighters);
int returnIndex(vector<Fighter>& fighters, Fighter f1);

#endif