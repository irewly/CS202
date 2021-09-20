f/**
 * Assignment 1 - CS 202 (Fall 2020)
 * Description: The user will run the program with the second commandline
 * argument being the input filename (the cars csv file). The program will
 * then read in a CSV formatted car file containing relevant car info
 * through file stream. It will then cout the total number of cars read 
 * and a menu with four options that the user can select to perform with 
 * the file. The first two options allow the user to select a particular
 * brand of cars and sort those cars either by mpg or horsepower. It will
 * also give the user to option to store the list in a file through 
 * filestreams. The third option will store all the cars read in from the
 * csv file into a new file in a preformatted fashion. The last option 
 * exits the program.
 * Input: Input csv file name via commandline argument, option numbers, 
 * car brand number, output file names.  
 * Output: Cout total number of cars read, selection menu, car brands list,
 * cars sorted by mpg/horsepower, save to file message.
 * @author Irene Wang 5005298618
 **/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip> //for generating "select make" list

using namespace std;

/* ***********************************************************************
 * class_identifier: This struct contains all the corresponding variables
 * of information about a single car.
 * constructors: N/A
 * public members: string make, string model, double mpg, unsigned int 
 * cylinders, unsigned int displacement, unsigned int horsepower, 
 * unsigned int weight, unsigned int year, string origin
 * static members: N/A
 * ************************************************************************/
struct Car {
    string make;                ///< Manufacturer
    string model;               ///< Model
    double mpg;                 ///< Fuel Efficiency in MPG
    unsigned int cylinders;     ///< Number of cylinders
    unsigned int displacement;  ///< Displacement in cu
    unsigned int horsepower;    ///< Horsepower in hp
    unsigned int weight;        ///< Weight in lbs
    unsigned int year;          ///< Model year in yy format
    string origin;              ///< Country/Continent of Origin
};

// Function Prototypes:
int readFile(string iName, vector<Car> & cars);
void printCar (ostream& out, const Car car);
void sortListByMPG (vector<Car> & cars);
void sortListByHP (vector<Car> & cars);
void listByMakeMPG (const vector<Car> cars);
void listByMakeHP (const vector<Car> cars);
void saveToFile (const vector<Car>  cars, string filename);
int selectionMenu();
string selectMake(); //for printing car brand catalog
void swap(Car& L, Car& R); //swap function used for bubble sort

// Main Function
int main(int argc, char *argv[]) {
    vector<Car> cars;
    int n_cars, ch;
    string filename;

    if (argc != 2) {
        cout << "ERROR: Invalid Arguments \nUsage: a.out <filename>" << endl;
        return EXIT_FAILURE;
    }
    n_cars = readFile(string(argv[1]), cars);
    if (n_cars == 0) {
        return EXIT_FAILURE;
    }
    else {
        cout << "Read " << n_cars << " cars from file." << endl;
    }
    
    do {
        ch = selectionMenu();
        switch(ch) {
            case 1:
                listByMakeMPG(cars);
                break;

            case 2:
                listByMakeHP(cars);
                break;

            case 3:
                cout << "Enter filename : "; cin >> filename;
                saveToFile(cars, filename);
                cout << "All cars saved to file \"" << filename << "\"" << endl;
                break;

            default:
                break;
        }
    } while (ch != 0);
    return EXIT_SUCCESS;
};

//Function Definitions:

/* ***********************************************************************
 * function_identifier: This function will read in the csv file containing
 * cars and store each variable into the corresponding car struct variable
 * The car structs are then pushed back into the car vector for future use
 * parameters: String iName that the user will input as the csv filename,
 * the Vector of Car type cars used for storing the car structs.
 * return value: Returns the number of cars read (Car Vector size).
* ************************************************************************/
int readFile(string iName, vector<Car>& cars) {
    ifstream fin;
    Car car;
    string temp; //temporary string variable for storing/transfering info
    fin.open(iName.c_str());
    
    //If file fails to open, cout error message
    if(fin.fail()){
        cout << "Invalid Input File" << endl;
        return 0;
    }
    else{
        //Read in the first instruction line of csv file and store it in 
        //string variable temp so it doesn't interfere with the actual car data
        getline(fin,temp);
        //while loops uses getline to read in the car data line by line and store
        //each component into the car struct which is then individually pushed
        //into the cars vector
        while(!fin.eof()){
            getline(fin,car.make,' ');
            getline(fin,car.model,';');
            getline(fin,temp,';');
            car.mpg = stod(temp);
            getline(fin,temp,';');
            car.cylinders = stoi(temp);
            getline(fin,temp,';');
            car.displacement = stoi(temp);
            getline(fin,temp,';');
            car.horsepower = stoi(temp);
            getline(fin,temp,';');
            car.weight = stoi(temp);
            getline(fin,temp,';');
            car.year = stoi(temp);
            getline(fin,car.origin);
            cars.push_back(car);
        }
        //removes last struct since .eof reads past end of file (which means
        //one extra blank "car" struct read in at the end)
        cars.pop_back();
    }
    fin.close();
    return cars.size();
}

/* ***********************************************************************
 * function_identifier: This function will cout the "select option" menu
 * and then prompt the user to input a number corresponding to the action 
 * they would like to perform to the file.
 * parameters: N/A
 * return value: Returns the option number the user inputed.
* ************************************************************************/
int selectionMenu(){
    int option;
    cout << endl;
    cout << "**** SELECT OPTION ****" << endl;
    cout << "1. Sort by MPG" << endl;
    cout << "2. Sort by Horsepower" << endl;
    cout << "3. Save all cars to file" << endl;
    cout << "0. Exit" << endl;
    cout << "***********************" << endl;
    cout << "Enter number : ";
    cin >> option;
    return option;
}

/* ***********************************************************************
 * function_identifier: This function will cout the "select make" menu
 * and then prompt the user to input a number corresponding to the car 
 * brand they would like to sort. 
 * parameters: Car vector cars containing all car structs
 * return value: Returns the "make" or car brand the user selected.
 * ***********************************************************************/
string selectMake(const vector<Car> cars){
    int number = 0; 
    string make;
    vector<string> makenames; //vector containing all car brand names
    bool notmatch = true;
    bool check = true;
    
    //for loop that goes through the entire cars vector to compare and add car
    //brands to the makenames vector
    for(int i = 0; i < cars.size(); i++){
        notmatch = true;
        for(int j = 0; j < makenames.size() && notmatch; j++){
            notmatch = false;
            if(cars[i].make != makenames[j]){
                notmatch = true;
            }
            else if(cars[i].make == makenames[j]){
                notmatch = false;
            }
        } 
        //if none of the brands in the makenames vector match the car's 
        //brand, it means the car's brand is new and need to be added to
        //the makenames vector
        if(notmatch == true){
            makenames.push_back(cars[i].make);
        }  
    }
    //cout select make list & prompt user for entry
    cout << "Select Make:" << endl;
    for(int i = 0; i < makenames.size(); i++){
        cout << left << setw(3) << i+1 << ": " << makenames[i] << endl;
    }
    cout << endl;
    //error check for invalid entries
    while(check){
        check = false;
        cout << "Enter number : ";
        cin >> number;
        if(number > 0 && number <= makenames.size()){
            make = makenames[number-1];
            return make;
        }
        else{
            cout << "Invalid entry, try again!" << endl;
            check = true;
        }
    }
}

/* ***********************************************************************
 * function_identifier: This function will print out the corresponding
 * information about a single car in a preformatted fashion to either the
 * terminal (cout) or to a file (ofstream).
 * parameters: ostream variable (either cout or fout to file), a single
 * car struct
 * return value: None, void function
* ************************************************************************/
void printCar (ostream &out, const Car car) {
    out << "Make : " << car.make << "\n";
    out << "Model : " << car.model << "\n";
    out << "Fuel Efficiency (MPG) : " << car.mpg << "\n";
    out << "Cylinders : " << car.cylinders << "\n";
    out << "Displacement (cu) : " << car.displacement << "\n";
    out << "Horsepower (hp) : " << car.horsepower << "\n";
    out << "Weight (lbs) : " << car.weight << "\n";
    out << "Model : 19" << car.year << "\n";
    out << "Origin: " << car.origin << "\n" << endl; 
}

/* ***********************************************************************
 * function_identifier: This function will save the list of car to a 
 * file with user specified name through ofstream.
 * parameters: Car Vector "cars" containing pertinent car structs, string
 * filename for output file
 * return value: None, void function
* ************************************************************************/
void saveToFile (const vector<Car>  cars, string filename){
    ofstream oFile;
    //open and print cars vector to file
    oFile.open(filename.c_str());
    for(int i = 0; i < cars.size(); i++){
        printCar (oFile, cars[i]);
    }
    if(oFile.fail()){
        cout << "Failed to create file" << endl;
    }
    oFile.close();
}

/* ***********************************************************************
 * function_identifier: This function is used to facilitate bubble sort.
 * parameters: Car struct "L" and Car struct "R"
 * return value: None, void function
* ************************************************************************/
void swap(Car& L, Car& R){
    Car temp = L;
    L = R;
    R = temp;
}

/* ***********************************************************************
 * function_identifier: This function is uses bubble sort to sort the 
 * list of cars according to their MPG in non-ascending order.
 * parameters: Car vector "cars" containing all pertinent car structs
 * return value: None, void function
* ************************************************************************/
void sortListByMPG (vector<Car>& cars){
    //bubble sort through cars vector utilizing swap function
    for(int x = 0; x < cars.size(); x++){
        for(int index = 0; index < cars.size()-1-x; index++){
            if(cars[index + 1].mpg > cars[index].mpg)
            {
                swap(cars[index + 1], cars[index]);
            }
        }
    }
}

/* ***********************************************************************
 * function_identifier: This function is uses bubble sort to sort the 
 * list of cars according to their horsepower in non-ascending order.
 * parameters: Car vector "cars" containing all pertinent car structs
 * return value: None, void function
* ************************************************************************/
void sortListByHP (vector<Car>& cars){
    //bubble sort through cars vector utilizing swap function
    for(int x = 0; x < cars.size(); x++){
        for(int index = 0; index < cars.size()-1-x; index++){
            if(cars[index + 1].horsepower > cars[index].horsepower)
            {
                swap(cars[index + 1], cars[index]);
            }
        }
    }
}

/* ***********************************************************************
 * function_identifier: This function utilizes several of the above
 * functions to generate and print out the list of cars of the user 
 * designated brand sorted by MPG.
 * parameters: Car vector "cars" containing all pertinent car structs
 * return value: None, void function
* ************************************************************************/
void listByMakeMPG (const vector<Car> cars){
    string makeName;
    string oName;
    char c;//temporary character used to store user response

    //obtain the user selected make name through selectMake function
    makeName = selectMake(cars);
    cout << "All cars made by " << makeName << " sorted by MPG..." << endl;
    cout << endl;
    //vector "brand" contains only "Car" structs of the user specified make
    vector<Car> brand;
    for(int i = 0; i < cars.size(); i++){
        if(cars[i].make == makeName)
            brand.push_back(cars[i]);
    }
    //sort custom "brand" vector by MPG and print to terminal
    sortListByMPG (brand);
    for(int j = 0; j < brand.size(); j++){
        printCar (cout, brand[j]);
    }
    //save to file prompt
    cout << "Save to file? [y/n] ? ";
    cin >> c;
    if(c == 'y'){
        cout << "Enter filename : ";
        cin >> oName;
        saveToFile(brand, oName);
        cout << "Data saved to file \"" << oName << "\"" << endl;
    }
}

/* ***********************************************************************
 * function_identifier: This function utilizes several of the above
 * functions to generate and print out the list of cars of the user 
 * designated brand sorted by horsepower.
 * parameters: Car vector "cars" containing all pertinent car structs
 * return value: None, void function
* ************************************************************************/
void listByMakeHP (const vector<Car> cars){
    string makeName;
    string oName;
    char c; //temporary character used to store user response
    
    //obtain the user selected make name through selectMake function
    makeName = selectMake(cars);
    cout << "All cars made by " << makeName << " sorted by horsepower..." << endl;
    cout << endl;
    //vector "brand" contains only "Car" structs of a specified make
    vector<Car> brand;
    for(int i = 0; i < cars.size(); i++){
        if(cars[i].make == makeName)
            brand.push_back(cars[i]);
    }
    //sort custom "brand" vector by horespower and print to terminal
    sortListByHP (brand);
    for(int j = 0; j < brand.size(); j++){
        printCar (cout, brand[j]);
    }
    //save to file prompt
    cout << "Save to file? [y/n] ? ";
    cin >> c;
    if(c == 'y'){
        cout << "Enter filename : ";
        cin >> oName;
        saveToFile(brand, oName);
        cout << "Data saved to file \"" << oName << "\"" << endl;
    }
}

