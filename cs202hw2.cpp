/*
 * Name: Irene Wang, 5005298618, Assignment 3
 * Description: This is an interactive terminal ticket ordering program where
 * users can order tickets of rockets that goes to space. The admin can first
 * set the number of tickets available for each rocket ship (4 total). The 
 * user menu will then be displayed where the user can choose the rocket
 * they wish to purchase tickets for. The program will check for ticket
 * availability and then ask the user to either choose a different rocket
 * ship (if ticket is sold out), or input the passenger information for each
 * ticket (if ticket is available). If the passenger is a veteran, there is 
 * a 10% ticket price discount that will be applied. Price and rocket specs
 * are shown after each passenger information is inputed. After the user has
 * inputed information for all passengers, the total number of tickets 
 * purchased for each rocket will be shown and the program will prompt the 
 * user if they would like to order additional tickets. If yes ('y'), the 
 * whole ticket ordering program will run again. If not ('n'), the rocket 
 * speed and distance will be shown for all rockets that the user ordered
 * a ticket for. 
 * Input: Admin input number of initial available seats on each rocket. The
 * user will choose the rocket type, number of tickets they wish to purchase,
 * relevant passenger info for each ticket (first name & last name), veteran
 * or not, and if they wish to purchase more tickets ('y' or 'n'). 
 * Output: Admin rocket seat prompt, rocket seat availability, rocket types
 * and prices, user rocket selection echo statement, seat availability,
 * number of tickets prompt, passenger info prompts, passenger type prompt,
 * confirmation with passenger name, rocket specs, book more seats prompt,
 * rocket speed and distance. 
 */
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;
//-----------------------------------------------------------------
/* ***********************************************************************
 * class_identifier: This class contains all the corresponding passenger
 * information variables including their name and type, as well as getter
 * and setter functions for public access of these variables.
 * constructors: N/A
 * public members: functions: setName, getName, setPassengerType
 * private members: strings: Name, passengerType
 * ***********************************************************************/
class passenger
{
public:
	void setName(string first, string last);
	string getName();
	void setPassengerType(string type);
private:
	string Name; //variable to store passenger name
	string passengerType; //variable to store passenger type
};
/***************************************************
YOUR CODE HERE FOR PASSENGER
***************************************************/
//This function concatenates the first and last name strings provided by 
//the user and stores it inside the "Name" string variable.
void passenger::setName(string first, string last){
	Name = first + " " + last;
}
//This function returns the string variable "Name" to allow for public access.
string passenger::getName(){
	return Name;
}
//This function sets the passengerType variable inside the passenger struct
//to the user inputed passenger type "type" (either veteran or non-veteran).
void passenger::setPassengerType(string type){
	passengerType = type;
}
/***************************************************
/////END YOUR CODE//////////////////////////////////
***************************************************/

//-----------------------------------------------------------------
/* ***********************************************************************
 * class_identifier: This class contains all the rocket-related variables
 * including number of available seats, ticket price, rocke type, and 
 * various rocket specifications as well as corresponding getter and 
 * setter functions that allows for public access.
 * constructors: rocket constructor initializes bookedSeat to 0.
 * 
 * public members: 
 * 	functions: setSeats, getSeats, setTicketPrice, getTicketPrice, 
 *  checkRocketAvailability (same as getSeats), 
 * 	setRocketType, purchaseTicket, getBookedSeats, setVelocity, 
 * 	getVelocity, setFuelCapacity, setRocketSpecs, getRocketSpecs, 
 *  setTimereq, getTikmereq
 * 
 * private members: 
 * 	integers: ticketPrice, seats, bookedSeat
 *  doubles: timereq, acceleration, velocity, fuelCapacity, thrust
 *  strings: rocketType, propellant
 * ***********************************************************************/
class rocket
{
public:
	void setSeats(int s); 
	int getSeats();
	void setTicketPrice(int price);
	int getTicketPrice(); 
	int checkRocketAvailability();
	void setRocketType(string type);
	void purchaseTicket(); 
	int getBookedSeats(); 
	void setVelocity(double v); 
	double getVelocity(); 
	void setFuelCapacity(int fC);
	void setRocketSpecs(string p, double a, double t);
	void getRocketSpecs(); 
	void setTimereq(double time); 
	double getTimereq();
	rocket();
private:
	int ticketPrice;
	string rocketType;
	int seats;
	double timereq;
	int bookedSeat;

	string propellant;
	double acceleration;
	double velocity;
	double fuelCapacity;
	double thrust;
};
/***************************************************
YOUR CODE HERE FOR ROCKET
***************************************************/
//constructor, initializes bookSeat to 0
rocket::rocket(){
	bookedSeat = 0;
}
//setter, sets seats equal to admin inputed integer "s"
void rocket::setSeats(int s){
	seats = s;
}
//getter, returns integer "seats" for public access
int rocket::getSeats(){
	return seats;
}
//setter, sets ticketPrice equal to "price" passed in from main
void rocket::setTicketPrice(int price){
	ticketPrice = price;
}
//getter, returns integer "ticketPrice" for public access
int rocket::getTicketPrice(){
	return ticketPrice;
}
//getter, returns integer "seats" for public access
//*same as getSeats function
int rocket::checkRocketAvailability(){
	return seats;
}
//setter, sets rocketType equal to "type" passed in from main
void rocket::setRocketType(string type){
	rocketType = type;
}
/* ***********************************************************************
 * function_identifier: This function will decrease "seats" by 1 and
 * increase "bookedSeat" by 1 each time it is called if "seats" is greater
 * than 0 (not sold out).
 * parameters: N/A
 * return value: N/A, void function
 * ***********************************************************************/
void rocket::purchaseTicket(){
	if(seats > 0){
		seats--;
		bookedSeat++;
	}
}
//getter, returns bookedSeat for public access
int rocket::getBookedSeats(){
	return bookedSeat;
}
//setter, sets velocity equal to "v" passed in from main
void rocket::setVelocity(double v){
	velocity = v;
}
//getter, returns velocity for public access
double rocket::getVelocity(){
	return velocity;
}
//setter, sets fuelCapacity to "fC" value passed in from main
void rocket::setFuelCapacity(int fC){
	fuelCapacity = fC;
}
/* ***********************************************************************
 * function_identifier: This function set the rocket specifications 
 * propellant, acceleration, and thrust equal to the values p, a, t, 
 * passed in from main.
 * parameters: string p (propellant), double a (acceleration), double t
 * (thrust)
 * return value: N/A, void function
 * ***********************************************************************/
void rocket::setRocketSpecs(string p, double a, double t){
	propellant = p;
	acceleration = a;
	thrust = t;
}
/* ***********************************************************************
 * function_identifier: This function will cout the various rocket specs 
 * (propellant, acceleration, thrust, fuelCapacity, velocity) in a 
 * preformated fashion to the terminal when it is called.
 * parameters: N/A
 * return value: N/A, void function
 * ***********************************************************************/
void rocket::getRocketSpecs(){
	cout << "Your Rocket Specs" << endl;
	cout << "Propellant Type: " << propellant << endl;
	cout << "Acceleration: " << acceleration << " m/s^2" << endl;
	cout << "Thrust: " << thrust << " Newtons" << endl;
	cout << "Fuel Capacity: " << fuelCapacity << " gallons" << endl;
	cout << "Velocity: " << velocity << " mph" << endl;
}
//setter, sets timereq equal to "time" passed in from main
void rocket::setTimereq(double time){
	timereq = time;
}
//getter, returns timereq for public access
double rocket::getTimereq(){
	return timereq;
}
/***************************************************
/////END YOUR CODE//////////////////////////////////
***************************************************/
//---------------------------------------------------------------
/* ***********************************************************************
 * class_identifier: This class contains all the functions and variable
 * associated with menus (greeting as well as rocket menu).
 * constructors: cout preformatted corresponding msg to the terminal 
 * (either admin or user)
 * public members: function: ShowRocketMenu
 * private members: integer: choice
 * ***********************************************************************/
class Menu
{
public:
	Menu(string msg);
	int ShowRocketMenu();
private:
	int choice;
};
/***************************************************
YOUR CODE HERE FOR MENU
***************************************************/
//constructor: couts greeting header message to the terminal
Menu::Menu(string msg){
	cout << "********************************" << endl;
	cout << msg << endl;
	cout << "********************************" << endl;
	cout << endl;
}
/* ***********************************************************************
 * function_identifier: This function will cout the rocket options to the
 * terminal, prompt the user to input their choice, and then return the 
 * user's choice.
 * parameters: N/A
 * return value: returns user choice "choice"
 * ***********************************************************************/
int Menu::ShowRocketMenu(){
	bool check = true; //for error check while loop
	//rocket menu
	cout << " Rocket options are :" << endl;
	cout << " 1. Cold-Gas Rocket and the ticket price is $10000" << endl;
	cout << " 2. Chemical Rocket and the ticket price is $12000" << endl;
	cout << " 3. Thermoelectric Rocket and the ticket price is $15000" << endl;
	cout << " 4. Hybrid Rocket and the ticket price is $16000" << endl;
	cout << endl;
	//error check for user input of choice
	cout << "Enter your choice" << endl;
	while(check){
		cin >> choice;
		if(1 <= choice && choice <= 4){
			check = false;
			return choice;
		}
		else{
			cout << "Incorrect selection. Try Again!" << endl;
			check = true;
		}
	}
}
/***************************************************
/////END YOUR CODE//////////////////////////////////
***************************************************/
//--------------------------------------------------------------

int main()
{
	double travelDistance = 238855;
	double totalprice; //price with no discount
	double discount = 0.10; //price discount for veteran 10%
	double topay; //final price after discount
	int choice; //choice selection from rocket menu
	int seaT; //selection of number of seats- basically to set seats from admin
	const int psize = 20; //max total number of passengers
	char ch; // for yes/no option to get more tickets
	double remainingDistance; //to store the reamining distance
   //Creating Objects of Rocket class
	rocket Obj[4];
	//Obj[0] is Cold Gas
	//Obj[1] is Chemical
	//Obj[2] is Thermoelectric
	//Obj[3] is Hybrid

	Menu menu("Welcome Admin- Set seats to \n YOU CAN FLY TO SPACE");
	Obj[0].setRocketType("Cold-Gas");
	cout << "Enter number of seats in Cold-Gas Rocket " << endl;
	cin >> seaT;
	//psize = psize + seaT;
	Obj[0].setSeats(seaT);
	Obj[0].setTicketPrice(10000);
	Obj[0].setFuelCapacity(773000);
	Obj[0].setRocketSpecs("Hydrogen", 12.9, 12.1);
	Obj[0].setVelocity(25000);
	//----------Setting Values of Each Rocket---------------------
	Obj[1].setRocketType("Chemical");
	cout << "Enter number of seats in Chemical Rocket " << endl;
	cin >> seaT;
	//psize = psize + seaT;
	Obj[1].setSeats(seaT);
	Obj[1].setTicketPrice(12000);
	Obj[1].setFuelCapacity(759320);
	Obj[1].setRocketSpecs("Hypergolic", 12.1, 12.2);
	Obj[1].setVelocity(21000);
	//------------------------------
	Obj[2].setRocketType("Thermoelectric");
	cout << "Enter number of seats in Thermoelectric Rocket " << endl;
	cin >> seaT;
	//psize = psize + seaT;
	Obj[2].setSeats(seaT);
	Obj[2].setTicketPrice(15000);
	Obj[2].setFuelCapacity(657200);
	Obj[2].setRocketSpecs("Hydrazine", 38.1, 12.1);
	Obj[2].setVelocity(21000);
	//------------------------------
	Obj[3].setRocketType("Hybrid");
	cout << "Enter number of seats in Hybrid Rocket " << endl;
	cin >> seaT;
	//psize = psize + seaT;
	Obj[3].setSeats(seaT);
	Obj[3].setTicketPrice(16000);
	Obj[3].setFuelCapacity(521400);
	Obj[3].setRocketSpecs("Oxidizers", 100.2, 100.1);
	Obj[3].setVelocity(28000);
	
	//------------------------------
	passenger psg[psize]; //20 total passengers created. Not all may be used. 
	//------------------------------
	string fname, lname;
	//Temp vars for names
	char ptype;
	int st, i = 0, Bookst, j;
	//PType is a temp for storing Passeneger Types (1 Veteran or 2 NonVeteran)
	//ptype changed to char to account for error checking non-numerical symbols.
	//St is for storing how many seats are availible
	//BookSt is for storing how many tickets someone wants to purchase
	//I is the total passenger count. Everytime a passenger is created,
		//... the ith passenger is updated and then i is incremented. 
		//psg[0] is the first passenger
		//psg[1] is the second, etc...
        //psg[i] will always be on the correct passenger 
        
	/***************************************************
	YOUR CODE HERE FOR MAIN()
	***************************************************/
    //Main do while loop containing the user ticket ordering program
	do{
		bool check = true;//used for error check loops
		cout << endl << endl;
		Menu userMenu("Welcome to YOU CAN FLY TO SPACE");
		cout << endl;
		//cout seat availability menu
		cout << "Status of seats availability" << endl;
		cout << "Cold-Gas Rocket is available with : " << Obj[0].getSeats() << " Passengers" << endl;
		cout << "Chemical Rocket is available with : " << Obj[1].getSeats() << " Passengers" << endl;
		cout << "Thermoelectric Rocket is available with : " << Obj[2].getSeats() << " Passengers" << endl;
		cout << "Hybrid Rocket is available with : " << Obj[3].getSeats() << " Passengers" << endl;
		cout << endl;
		//call ShowRocketMenu and depending on choice cout confirmation message
		choice = menu.ShowRocketMenu();
		switch(choice){
			case 1:
				cout << "You selected Cold-Gas Rocket and the ticket price is $10000" << endl;
				break;
			case 2:
				cout << "You selected Chemical Rocket and the ticket price is $12000" << endl;
				break;
			case 3:
				cout << "You selected Thermoelectric Rocket and the ticket price is $15000" << endl;
				break;
			case 4:
				cout << "You selected Hybrid Rocket and the ticket price is $16000" << endl;
				break;
		}
		//st set equal to amount of avaialble seats in the user selected rocket
		st = Obj[choice - 1].getSeats();
		cout << "Checking seat availability..." << endl << endl;
		//seat availability check
		if(st == 0){
			cout << "No seat is available" << endl;
		}
		//if tickets not sold out, proceed to number of tickets and passenger info
		else{
			cout << "Available seats are : " << st << endl;
			cout << "Enter number of tickets : between the range of 1 - " << st << endl;
			cin >> Bookst;
			//error check for number of tickets input
			while(check){
				if(Bookst > st){
					cout << "Number of seats entered exceeds the number of seats available..." << endl;
					cout << "Enter number of tickets : between the range of 1 - " << st << endl;
					cin >> Bookst;
				}
				else if(Bookst <= 0){
					cout << "Please input valid number of tickets!" << endl;
					cout << "Enter number of tickets : between the range of 1 - " << st << endl;
					cin >> Bookst;
				}
				else{
					check = false;
				}
			}
			//for loop to update number of availale seats and number of booked seats for the user selected rocket
			for(j = 0; j < Bookst; j++){
				Obj[choice - 1].purchaseTicket();
			}	
			cout << endl;
			//passenger info loop
			for(i = 0; i < Bookst; i++){
				cout << "Enter details of passenger " << i + 1 << endl << endl;
				cout << "Enter your First name" << endl;
				cin >> fname;
				cout << "Enter your Last name" << endl;
				cin >> lname;
				cout << "Saving Passenger" << endl << endl;
				psg[i].setName(fname, lname);
				//do while loop for passenger type (veteran or nonveteran)
				do{
					check = false;
					cout << "Select your passenger type" << endl;
					cout << "1. Veteran" << endl;
					cout << "2. Nonveteran" << endl << endl;
					cout << "Enter your selection : ";
					cin >> ptype;
					//error check for invalid passenger type input
					if(ptype != '1' && ptype != '2'){
						cout << "Incorrect selection. Try again!" << endl;
						check = true;
					}
				}while(check);
				//price caculations depending on user passenger type
				totalprice = Obj[choice - 1].getTicketPrice();
				topay = Obj[choice - 1].getTicketPrice() * (1-discount);
				//cout ticket price to the terminal
				if(ptype == '1'){
					psg[i].setPassengerType("Veteran");
					cout << "Your ticket price with 10% discount is $" << topay << endl;
				}
				else if(ptype == '2'){
					psg[i].setPassengerType("Nonveteran");
					cout << "Your ticket price is $" << totalprice << endl;
				}
				cout << endl;
				//confirmation feedback message
				cout << "Dear " << psg[i].getName() << " - your seat is reserved successfully" << endl;
				cout << endl;
				//call getRocketSpecs to cout corresponding rocket specs to the terminal
				Obj[choice - 1].getRocketSpecs();
				cout << endl << endl;
			}
		}
		//cout book more seats message, if yes ('y'), loop runs again
		cout << "Do you want to Book More Seats (y/n)" << endl;
		cin >> ch;
	}while(ch == 'y');
	/***************************************************
	/////END YOUR CODE//////////////////////////////////
	***************************************************/
	
	double time;
	//checking for launching .....
	cout << "Booked seats for Cold-Gas Rocket: " << Obj[0].getBookedSeats() << endl;
	cout << "Booked seats for Chemical Rocket: " << Obj[1].getBookedSeats() << endl;
	cout << "Booked seats for Thermoelectric Rocket: " << Obj[2].getBookedSeats() << endl;
	cout << "Booked seats for Hybrid Rocket: " << Obj[3].getBookedSeats() << endl;
	cout << endl << endl;

	if (Obj[0].getBookedSeats() > 0)
	{
		cout << "Dear Cold-Gas Rocket passengers, your Rocket is ready to take off ..." << endl;
		cout << "Distance of your destination is " << travelDistance << " miles" << endl;
		time = travelDistance / Obj[0].getVelocity();
		Obj[0].setTimereq(time);
		cout << "Time taking to reach your destination will be " << time << " Hours" << endl;
		cout << "Wishing you a very Happy Journey" << endl << endl;
	}
	if (Obj[1].getBookedSeats() > 0)
	{
		cout << "Dear Chemical Rocket passengers, your Rocket is ready to take off ..." << endl;
		cout << "Distance of your destination is " << travelDistance << " miles" << endl;
		time = travelDistance / Obj[1].getVelocity();
		Obj[1].setTimereq(time);
		cout << "Time taking to reach your destination will be " << time << " Hours" << endl;
		cout << "Wishing you a very Happy Journey" << endl;
	}
	if (Obj[2].getBookedSeats() > 0)
	{
		cout << "Dear Thermoelectric Rocket passengers, your Rocket is ready to take off ..." << endl;
		cout << "Distance of your destination is " << travelDistance << " miles" << endl;
		time = travelDistance / Obj[2].getVelocity();
		Obj[2].setTimereq(time);
		cout << "Time taking to reach your destination will be " << time << " Hours" << endl;
		cout << "Wishing you a very Happy Journey" << endl;
	}
	if (Obj[3].getBookedSeats() > 0)
	{
		cout << "Dear Hybrid Rocket passengers , your Rocket is ready to take off ..." << endl;
		cout << "Distance of your destination is " << travelDistance << " miles" << endl;
		time = travelDistance / Obj[3].getVelocity();
		Obj[3].setTimereq(time);
		cout << "Time taking to reach your destination will be " << time << " Hours" << endl;
		cout << "Wishing you a very Happy Journey" << endl;
	}
	cout << endl << endl;
	if (Obj[0].getBookedSeats() > 0)
	{
		for (double k = 1; k <= Obj[0].getTimereq(); k++)
		{
			remainingDistance = travelDistance - (Obj[0].getVelocity() * k);
			cout << "Dear Cold-Gas Rocket passengers ... " << endl;
			cout << "Distance travelled after " << k << " hours is " << (Obj[0].getVelocity() * k) << " miles" << endl;
			cout << "Remaining distance is " << remainingDistance << " miles" << endl;
		}
		cout << "Dear Cold-Gas Rocket passengers, we are landing on destination" << endl << endl;
	}
	if (Obj[1].getBookedSeats() > 0)
	{
		for (double k = 1; k <= Obj[1].getTimereq(); k++)
		{
			remainingDistance = travelDistance - (Obj[1].getVelocity() * k);
			cout << "Dear Chemical Rocket passengers ... " << endl;
			cout << "Distance travelled after " << k << " hours is " << (Obj[1].getVelocity() * k) << " miles" << endl;
			cout << "Remaining distance is " << remainingDistance << " miles" << endl;
		}
		cout << "Dear Chemical Rocket passengers, we are landing on destination" << endl << endl;
	}
	if (Obj[2].getBookedSeats() > 0)
	{
		for (double k = 1; k <= Obj[2].getTimereq(); k++)
		{
			remainingDistance = travelDistance - (Obj[2].getVelocity() * k);
			cout << "Dear Thermoelectric Rocket passengers ... " << endl;
			cout << "Distance travelled after " << k << " hours is " << (Obj[2].getVelocity() * k) << " miles" << endl;
			cout << "Remaining distance is " << remainingDistance << " miles" << endl;
		}
		cout << "Dear Thermoelectric Rocket passengers, we are landing on destination" << endl << endl;
	}
	if (Obj[3].getBookedSeats() > 0)
	{
		for (double k = 1; k <= Obj[3].getTimereq(); k++)
		{
			remainingDistance = travelDistance - (Obj[3].getVelocity() * k);
			cout << "Dear Hybrid Rocket passengers ... " << endl;
			cout << "Distance travelled after " << k << " hours is " << (Obj[3].getVelocity() * k) << " miles" << endl;
			cout << "Remaining distance is " << remainingDistance << " miles" << endl;
		}
		cout << "Dear Hybrid Rocket passengers, we are landing on destination" << endl << endl;
	}
}
