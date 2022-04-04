#include "header.h"
using namespace std;

// auto rd = std::random_device {}; 
// auto rng = std::default_random_engine { rd() };
auto rng = std::default_random_engine {};


int main(int args, char* argv[]){

    Brawl brawl;
    brawl.generateRandomFighters(5);
    brawl.printFightersNames();
    brawl.startBrawl();
    brawl.printFightersNames();

}

// **************** FIGHTER **********************
// Constructors and destructor for the Fighter class
Fighter::Fighter(){}
Fighter::~Fighter(){}

Fighter::Fighter(string name, int hp){
    setFighterName(name);
    setFighterHP(hp);
    setIsWinner(false);
    setIsEliminated(false);
}

// Getters and setters for name and hp of the fighter
string Fighter::getFighterName(){
    return this->fighterName;
}

void Fighter::setFighterName(string fighterName){
    this->fighterName = fighterName;
}

int Fighter::getFighterHP(){
     return this->fighterHP;
}

void Fighter::setFighterHP(int hp){
    this->fighterHP = hp;
}

// Getters and setters for bool variable
// that shows it the fighter is a winner of the brawl
// or is eliminated
bool Fighter::getIsWinner(){
    return this->isWinner;
}

void Fighter::setIsWinner(bool isWinner){
    this->isWinner = isWinner;
}

bool Fighter::getIsEliminated(){
     return this->isEliminated;
}

void Fighter::setIsEliminated(bool isEliminated){
    this->isEliminated = isEliminated;
}

// function that return how much damage the fighter will deal
int Fighter::dealDamage(){
    return generateRandomNumber(0, 20);
}


// **************** BRAWL **********************
// Constructors and destructors for the Brawl class
Brawl::Brawl(){}

Brawl::~Brawl(){}

// Getters and setters for vector of fighters
vector<Fighter> Brawl::getFighters(){
    return this->fighters;
}

void Brawl::setFighters(vector<Fighter>& fighters){
    this->fighters = fighters;
}

// Function used to generate random fighters from array of names,
// by given a number from the user
void Brawl::generateRandomFighters(int num){
    array<string, 5> names = {"Robert", "Brandon", "Dan", "Rick", "John"};
    for(int i = 0; i < num; i++){
        std::stringstream name;
        name << names[generateRandomNumber(0,4)] << i;
        Fighter f1(name.str(), 100);
        this->fighters.push_back(f1);
    }
}

// Function that fills the vector with
// fighters entered by the program's user
void Brawl::generateFighters(){
    int count;
    string name;
    cout << "Enter number of fighters: " << endl;
    count = getValidNumber();
    for(int i = 0; i < count; i++){
        cout << "Enter fighter " << i+1 << " name: " <<endl;
        cin >> name;
        Fighter f1(name, 100);
        this->fighters.push_back(f1);
    }
}

// Function that iterates over the vector and prints
// the names of fighters 
void Brawl::printFightersNames(){
    for(vector<Fighter>::iterator fighter = fighters.begin();
     fighter != fighters.end(); ++fighter){
        cout << "Figther: " << fighter->getFighterName() << endl; 
        // if(fighter->getIsEliminated() == 1) {
        //  cout << " elim "<<endl; 
        // } else {
        //  cout << " not elim" <<endl; 
        // }
     }
}

// Function that iterates over the vector and sets
// all of fighters' hp to full 
void Brawl::drinkAndHeal(){
     for(vector<Fighter>::iterator fighter = this->fighters.begin();
     fighter != this->fighters.end(); ++fighter){
         fighter->setFighterHP(100);
     }
}

// Function that shuffles the order of vector of fighters 
void Brawl::shuffleFightersOrder(){
    std::shuffle(std::begin(this->fighters), std::end(this->fighters), rng);
}

// Most important function of the program
// Starts a infinite loop and 
// then the fighters are matched in pairs and fight.
// And after each round the fighters are shuffled 
// and their hp is set to full until there is a winner of the brawl
void Brawl::startBrawl(){
    
    if(this->fighters.size() == 1){
        cout << "Need more than one fighter to start a brawl!" <<endl;
        return;
    }

    bool haveWinner = false;
    while(!haveWinner){
        int size = this->fighters.size();
        cout << "size " << size <<endl;
        if(size % 2 == 0){
            cout << "even " << size <<endl;
            // Even total number of fighters
            for(int i = 0; i < size; i+=2){
                // cout << i << " - " << i+1 <<endl;
                // cout << i << " - " << fighters[i].getFighterName() <<endl;
                // cout << i+1 << " - " << fighters[i+1].getFighterName() <<endl;
                fight(&this->fighters[i], &this->fighters[i+1]);
            }
        } else {
            cout << "oddc " << size <<endl;
            // Odd total number of fighters
             for(int i = 0; i < size-1; i+=2){ 
                fight(&fighters[i], &fighters[i+1]);
            }
        }

        this->removeLosers();
        this->shuffleFightersOrder();
        this->drinkAndHeal();

        if(this->fighters.size() == 1){
            haveWinner = true;
            cout << "****** Winner ******"<< endl;
            cout << "Winner is " << this->fighters[0].getFighterName() << endl;
        }        
    }
}

// Function that takes two fighters as arguments
// and in a loop they deal damage to each other
// until the HP of one of them is <= 0
void Brawl::fight(Fighter* f1, Fighter* f2){
    bool isFightOver = false;
    int counter = 1;
 
    cout << "**************************" <<endl;
    cout << f1->getFighterName() <<endl;
    cout << f2->getFighterName() <<endl;
    cout << "**************************" <<endl;
    while(!isFightOver){
        int f1_damage = f1->dealDamage();
        int f2_damage = f2->dealDamage();

        cout << "\n" << "***** Round " << counter << " *****" << endl;
        cout << f1->getFighterName() << " dealt " << f1_damage <<
         " to " << f2->getFighterName() << endl;
        f2->setFighterHP(f2->getFighterHP() - f1_damage);
        cout << f1->getFighterName() << " has " << f1->getFighterHP() << "HP" << endl;
        cout << f2->getFighterName() << " has " << f2->getFighterHP() << "HP" << endl;

        if(f2->getFighterHP() <= 0){
            f2->setIsEliminated(true);
            cout << f2->getFighterName() << " is knocked out" << endl;
            // remove from array
            isFightOver = true;
        } else {
            cout << f2->getFighterName() << " dealt " << f2_damage <<
            " to " << f1->getFighterName() << endl; 
            f1->setFighterHP(f1->getFighterHP() - f2_damage);
            cout << f1->getFighterName() << " has " << f1->getFighterHP() << "HP"<< endl;
            cout << f2->getFighterName() << " has " << f2->getFighterHP() << "HP" << endl;
            if(f1->getFighterHP() <= 0){
                f1->setIsEliminated(true);
                cout << f1->getFighterName() << " is knocked out" << endl;
                // remove from array
                isFightOver = true;
            }
        } 
        counter++;
    }
}

// Function that removes the eliminated fighter by replacing 
// the vector with new one populated only with the winners of fights
void Brawl::removeLosers(){
    
  vector<Fighter> winers;
  
  for(int i = 0; i < fighters.size(); i++){
        if(!this->fighters[i].getIsEliminated()){
            winers.push_back(this->fighters[i]);
        }    
    }
    this->setFighters(winers);
}

// Function that returns the index of fighter by given name
int Brawl::returnIndex(string fighterName){

    // string myString = f1.getFighterName();
    auto it = find_if(this->fighters.begin(), this->fighters.end(), [&fighterName]
    (const Fighter& fighter) {
        // cout << "MS " << myString <<endl;
        // cout << "NAME " << ((Fighter)fighter).getFighterName() <<endl;
        return ((Fighter)fighter).getFighterName() == fighterName;
        });

    if (it != fighters.end())
    {
        int index = std::distance(this->fighters.begin(), it);
        return index;
    }
    return -1;
}

// Function that iterates over the vector and prints the name of the winner  
void Brawl::printFightersNames(){
    for(vector<Fighter>::iterator fighter = fighters.begin();
     fighter != fighters.end(); ++fighter){
        if(fighter->getIsWinner() == 1) {
            cout << "****** Winner ******"<< endl;
            cout << "Figther: " << fighter->getFighterName() << " is the Winner" << endl; 
        }
     }
}

// ******************** HELPER FUNCS *************************
// prints the menu options for the loop in main function
void printMenuOptions(){
    cout << "***** Menu Options *****" << endl;
    cout << "1. Add New Fighters." << endl;     
    cout << "2. Generate Random Fighters." << endl;
    cout << "3. Print All Fighters' Names." << endl;         
    cout << "4. Start a brawl." << endl;
    cout << "5. Print Brawl Winner." << endl;
    cout << "6. Print options." << endl;
    cout << "0. Exit." << endl;            
}

// helper function for generating random number in range
int generateRandomNumber(int lower, int higher){

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(lower, higher);
    return distr(generator);
}

// helper function for generating random number in range
int generateRandomNumberWithRand(int lower, int higher){
    static bool first = true;
       if (first) 
       {  
          //seeding for the first time only!
          srand(time(NULL)); 
          first = false;
       }
    return lower + rand() % (( higher + 1 ) - lower);
    // return lower + (std::rand() % (higher - lower + 1 ));
}

// helper function for limiting the user input to be only positive numbers
int getValidNumber(){
    int n;
    cin >> n;
    while ((cin.fail() || n < 0)){
        cin.clear();
        cin.ignore();
        cout << "Not a valid number. Please enter new: ";
        cin >> n;
    }
    return n;
}

void generateRandomPairs(int higher){
    srand(time(0));
    int lower = 0;
    int* arr = new int[higher];
    for(int i = 0; i < higher; i++){
        arr[i] = i;
        // cout << i << " - " << arr[i]  << endl;
    }
    
    int j = 0;
    int temp = 0;

    for(int i = 0; i < higher; i++){
        j = (rand() % higher)+1;
        temp = arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    
    // cout << "After" <<endl;
    for(int i = 0; i < higher; i++){
        // cout << i << " - " << arr[i]  << endl;
    }
}
