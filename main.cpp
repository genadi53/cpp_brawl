#include "header.h"

using namespace std;

// auto rd = std::random_device {}; 
// auto rng = std::default_random_engine { rd() };
auto rng = std::default_random_engine {};

int main(int args, char* argv[]){
    vector<Fighter> fighters;
    Fighter f1("Tom", 100);
    generateRandomFighters(fighters, 5);
    printFightersNames(fighters);
    // startBrawl(fighters);
    returnIndex(fighters, f1);
   
    printFightersNames(fighters);


}

int returnIndex(vector<Fighter>& fighters, Fighter f1){

    string myString = f1.getFighterName();
    auto it = find_if(fighters.begin(), fighters.end(), [&myString]
    (const Fighter& fighter) {
        cout << "MS " << myString <<endl;
        cout << "NAME " << ((Fighter)fighter).getFighterName() <<endl;
        return ((Fighter)fighter).getFighterName() == myString;
        });

    if (it != fighters.end())
    {
        int index = std::distance(fighters.begin(), it);
        return index;
    }
    return -1;
}

int main2(){
    
    vector<Fighter> fighters;
    generateRandomFighters(fighters, 5);
    // generateFighters(fighters);
    printFightersNames(fighters);
    shuffleFightersOrder(fighters);

    cout << "After" <<endl;
    printFightersNames(fighters);

    // fight(fighters, fighters[0], fighters[1]);
    return 0;
}

// Constructors and destructor
Fighter::Fighter(){}
Fighter::~Fighter(){}

Fighter::Fighter(string name, int hp){
    setFighterName(name);
    setFighterHP(hp);
    setIsWinner(false);
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
bool Fighter::getIsWinner(){
    return this->isWinner;
}

void Fighter::setIsWinner(bool isWinner){
    this->isWinner = isWinner;
}

int Fighter::dealDamage(){
    return generateRandomNumber(0, 20);
}

void generateRandomFighters(vector<Fighter>& fighters, int num){
    array<string, 5> names = {"John", "Adam", "Aron", "Samuel", "Caleb"};
    for(int i = 0; i < num; i++){
        std::stringstream name;
        name << names[generateRandomNumber(0,4)] << i;
        // cout << name.str() << endl;
        Fighter f1(name.str(), 100);
        fighters.push_back(f1);
    }
}

void generateFighters(vector<Fighter>& fighters){
    int count;
    string name;
    cout << "Enter number of fighters: " << endl;
    count = getValidNumber();
    for(int i = 0; i < count; i++){
        cout << "Enter fighter " << i+1 << " name: " <<endl;
        cin >> name;
        Fighter f1(name, 100);
        fighters.push_back(f1);
    }
}

void printFightersNames(vector<Fighter>& fighters){
    for(vector<Fighter>::iterator fighter = fighters.begin();
     fighter != fighters.end(); ++fighter){
         cout << "Figther: " << fighter->getFighterName() << endl; 
     }
}

void drinkAndHeal(vector<Fighter>& fighters){
     for(vector<Fighter>::iterator fighter = fighters.begin();
     fighter != fighters.end(); ++fighter){
         fighter->setFighterHP(100);
     }
}

void fight(vector<Fighter>& fighters, Fighter f1, Fighter f2){
    bool isFightOver = false;
    int counter = 1;
    while(!isFightOver){
        int f1_damage = f1.dealDamage();
        int f2_damage = f2.dealDamage();

        cout << "\n" << "***** Round " << counter << " *****" << endl;
        cout << f1.getFighterName() << " dealt " << f1_damage <<
         " to " << f2.getFighterName() << endl;
        f2.setFighterHP(f2.getFighterHP() - f1_damage);
        cout << f1.getFighterName() << " has " << f1.getFighterHP() << "HP" << endl;
        cout << f2.getFighterName() << " has " << f2.getFighterHP() << "HP" << endl;

        if(f2.getFighterHP() <= 0){
            cout << f2.getFighterName() << " is knocked out" << endl;
            isFightOver = true;
            // remove from array
        } else {
            cout << f2.getFighterName() << " dealt " << f2_damage <<
            " to " << f1.getFighterName() << endl; 
            f1.setFighterHP(f1.getFighterHP() - f2_damage);
            cout << f1.getFighterName() << " has " << f1.getFighterHP() << "HP"<< endl;
            cout << f2.getFighterName() << " has " << f2.getFighterHP() << "HP" << endl;
            if(f1.getFighterHP() <= 0){
                cout << f1.getFighterName() << " is knocked out" << endl;
                isFightOver = true;
                // remove from array
            }
        } 
        counter++;
    }
}

void shuffleFightersOrder(vector<Fighter>& fighters){
    std::shuffle(std::begin(fighters), std::end(fighters), rng);
}

// prints the menu options for the loop in main function
void printMenuOptions(){
    cout << "***** Menu Options *****" << endl;
    cout << "1. Add New Fighters." << endl;     
    cout << "2. Generate Random Fighters." << endl;
    cout << "3. Print All Fighters' Names." << endl;         
    cout << "4. Start a brawl." << endl;
    cout << "5. Print Brawl Winner." << endl;
    // cout << "6. Save districts with no winners to file." << endl;
    // cout << "7. Print districts from file." << endl;
    cout << "8. Print options." << endl;
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

void startBrawl(vector<Fighter>& fighters){
    bool haveWinner = false;
    while(!haveWinner){
        int size = fighters.size();
        cout << "size " << size <<endl;
        if(size % 2 == 0){
            // Even total number of fighters
            for(int i = 0; i < size; i += 2){
                fight(fighters, fighters[i], fighters[i+1]);
            }
        } else {
            // Odd total number of fighters
             for(int i = 0; i < size-1; i += 2){ 
                fight(fighters, fighters[i], fighters[i+1]);
            }
        }

        if(fighters.size() == 1){
            haveWinner = true;
            cout << "****** Winner ******"<< endl;
            cout << "Winner is " << fighters[0].getFighterName() << endl;
            cout << "^^^^^^ Winner ^^^^^^"<< endl;

        } 
            
    }
}
