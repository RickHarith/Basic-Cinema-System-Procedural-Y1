#include <iostream>
#include <fstream> //Allows for file handling
#include <string>
#include <vector>
using namespace std;

string FinalMovie, FinalScreen; //Globally declared strings to determine the movie the user chooses, as well as the screen they chose
int SeatCapacity;

class Movies { //Class for Movies, below are the private variables
	string Name;
	string Genre;
	string MainStar;
	int Year;
	int Runtime;

public:
	Movies(string name, string genre, string mainstar, int year, int runtime) { //Constructor
		Name = name;
		Genre = genre;
		MainStar = mainstar;
		Year = year;
		Runtime = runtime;
	}
	void setName(string name) { Name = name; } //Get method
	string getName() { return Name; } //Set method

	void setGenre(string genre) { Genre = genre; }
	string getGenre() { return Genre; }

	void setMainStar(string mainstar) { MainStar = mainstar; }
	string getMainStar() { return MainStar; }

	void setYear(int year) { Year = year; }
	int getYear() { return Year; }

	void getRuntime(int runtime) { Runtime = runtime; }
	int getRuntime() { return Runtime; }
};


class Schedule { //Schedule Class, this parent class is for movies that have only 3 SHOWINGS per day
protected:
	string Show1;
	string Show2;
	string Show3;
public:
	Schedule(string s1, string s2, string s3) { //Constructor
		Show1 = s1;
		Show2 = s2;
		Show3 = s3;
	}
	Schedule() { //No argument constructor for inheritance
		Show1 = "";
		Show2 = "";
		Show3 = "";
	}
	void setShow1(string s1) { Show1 = s1; } //Get method
	string getShow1() { return Show1; } //Set method

	void setShow2(string s2) { Show2 = s2; }
	string getShow2() { return Show2; }

	void setShow3(string s3) { Show3 = s3; }
	string getShow3() { return Show3; }
};

class Schedule2 : public Schedule { //Inheritance used, child class
	string Show4; //One new variable is added, this class is used for movies with 4 SHOWINGS per day
public:
	Schedule2(string s1, string s2, string s3, string s4) { //Constuctor
		Show1 = s1;
		Show2 = s2;
		Show3 = s3;
		Show4 = s4;
	}
	Schedule2() { //No argument constructor
		Show1 = "";
		Show2 = "";
		Show3 = "";
		Show4 = "";
	}
	void setShow4(string s4) { Show4 = s4; } //Get method
	string getShow4() { return Show4; } //Set method
};

vector<string> TicketTypes; //Vector for storing all the ticket types the user chooses, e.g. Adult ticket, senior ticket etc
vector<float> TotalPrices; //Vector for storing the prices of all the tickets chosen by the user, it is then added up and placed in the PriceSum variable
vector<int> TicketAmount; //Vector for amount of tickets bought by user, so it can be subtraced from the seat capacity, the sum is then placed into the TicketSum variable
float PriceSum = 0; //Empty global variable to store the final price sum of all tickets bought
int TicketSum = 0; //Empty global variable to store the final amount of tickets bought, used to be subtracted from seat capacity

void BuyingTickets(); //Function prototypes
string ScreenChoice();

void FinalPrint() { //Function that prints the information of the purchase, such as what tickets were bought, total price, which movie and screen
	string Email;
	for (auto& n : TicketAmount) //This sums up the amount of tickets the user bought
		TicketSum += n;
	int NewSeatCap = SeatCapacity - TicketSum; //NewSeatCap is the new variable created after the user has bought tickets
	if (NewSeatCap <= 0) { //If the tickets bought exceed the available seats, the program clears all values and goes back to previous function
		cout << "\nError: We're out of seats for this screen, please redo your booking.\n"<<endl;
		TicketTypes.clear(); //Clears vectors
		TotalPrices.clear();
		TicketAmount.clear();
		PriceSum = 0; //Resets the values in variables
		TicketSum = 0;
		ScreenChoice();
	}
	else { //If it does not exceed, program continues here
		cout << "\nTickets will be sent to the customer's email\nEmail: ";
		cin >> Email;
		cout << "\n[-----Seats remaining: " << NewSeatCap << "-----]" << endl;
		cout << "\nMovie Chosen: " << FinalMovie;
		cout << " " << "(" << FinalScreen << ")" << endl;
		for (int i = 0; i < TicketTypes.size(); i++) { //Iterates through the vector and prints the stored selected tickets
			cout << "\nSelected Ticket: " << TicketTypes[i];
		}
		cout << "\nTotal price paid: " << PriceSum << " pounds\n";
		cout << "\n[-----Payment was successful-----]\n";
	}
}

void CardPayment() { //Funtion for card info input
	string CardNumber;
	string ExpiryDate;
	string SecCode;
	string CardOwner;
	cout << "\nCredit Card Infomation\n";
	cout << "Name: ";
	getline (cin>> ws, CardOwner); //getline used to ignore spaces since cin 
	cout << "Card Number: ";
	cin >> CardNumber;
	cout << "CVV: ";
	cin >> SecCode;
	cout << "Expiry Date: ";
	cin >> ExpiryDate;
	FinalPrint();
}

void PaymentMethod() { //Function for choosing payment method 
	string PaymentChoice;
	cout << "\nChoose your payment method:\n1. Card\n2. Cash\nPick a number (1 - 2): ";
	cin >> PaymentChoice;
	if (PaymentChoice == "1") {
		CardPayment();
	}
	else if (PaymentChoice == "2") {
		FinalPrint();
	}
	else {
		cout << "\nWrong input, please try again" << endl;
		PaymentMethod(); //If input is invalid, the function is called again to loop back to the beginning of it
	}
}

void FinalisePrice() { //Function to get all the chosen information
	cout << "Movie Chosen: " << FinalMovie;
	cout << " " << "(" << FinalScreen << ")" << endl;
	for (int i = 0; i < TicketTypes.size(); i++) { //Iterates through the vector and prints the stored selected tickets
		cout << "\nSelected Ticket: " << TicketTypes[i];
	}
	for (auto& n : TotalPrices) { //Sums up the total price from the tickets bought
		PriceSum += n;
	}
	cout << "\nYour total price is: " << PriceSum << " pounds\n";
	PaymentMethod();
}



void BuyMoreTickets() { //Function that asks if the user wishes to buy more tickets;
	string MoreTickets;
	cout << "\nBuy more tickets?\n1. Yes\n2. No" << endl << "Input: ";
	cin >> MoreTickets;
	if (MoreTickets == "1") {
		BuyingTickets();
	}
	else if (MoreTickets == "2") {
		FinalisePrice();
	}
	else{
		cout << "\nWrong input, please try again\n" << endl;
		BuyMoreTickets();
	}
}

void BuyingTickets() { //Function for choosing the different types of tickets
	string TicketChoices;
	cout << "\n[-----Seats left for booking: " << SeatCapacity << "-----]" << endl;
	cout << "\n!!!Make sure you do not overbook!!!\n";
	cout << "\nBuy Tickets\n" << endl << "Prices:" << endl << "1. Adults\n2. Seniors\n3. Children\n4. Students\n\nPick your ticket (1 - 4): ";
	cin >> TicketChoices;
	if (TicketChoices == "1") { //Each ticket appends different values to the vectors
		TicketAmount.push_back(1); //Amount of tickets
		TicketTypes.push_back("Adult Ticket"); //Name of ticket
		TotalPrices.push_back(9.50); //Price of ticket
		BuyMoreTickets();
	}
	else if (TicketChoices == "2") {
		TicketAmount.push_back(1);
		TicketTypes.push_back("Senior Ticket");
		TotalPrices.push_back(6.50);
		BuyMoreTickets();
	}
	else if (TicketChoices == "3") {
		TicketAmount.push_back(1);
		TicketTypes.push_back("Children Ticket");
		TotalPrices.push_back(5.50);
		BuyMoreTickets();
	}
	else if (TicketChoices == "4") {
		TicketAmount.push_back(1);
		TicketTypes.push_back("Student Ticket");
		TotalPrices.push_back(7.00);
		BuyMoreTickets();
	}
	else {
		cout << "\nWrong input, please try again\n" << endl;
		BuyingTickets();
	}
}

void SchedulePicker() { //Function for picking the schedule
	string ScheduleChoice;
	cout << "Pick a Time (1 - 4): ";
	cin >> ScheduleChoice;
	if (ScheduleChoice == "1" || ScheduleChoice == "2" || ScheduleChoice == "3" || ScheduleChoice == "4") {
		BuyingTickets();
	}
	else {
		cout << "\nWrong input, please try again\n" << endl;
		SchedulePicker();
	}
}

void SchedulePicker2() { //Function for picking schedule
	string ScheduleChoice;
	cout << "Pick a Time (1 - 3): ";
	cin >> ScheduleChoice;
	if (ScheduleChoice == "1" || ScheduleChoice == "2" || ScheduleChoice == "3") {
		BuyingTickets();
	}
	else {
		cout << "\nWrong input, please try again\n" << endl;
		SchedulePicker2();
	}
}

string ScreenChoice();//Function prototype

string BookingMovieS1() { //Function for first screen movies
	string movieline;
	fstream movie;
	movie.open("Screen-1.txt"); //Reading the text file and printing it out
	if (movie.is_open()) {
		while (!movie.eof()) {
			getline(movie, movieline);
			cout << movieline << endl;
		}
		movie.close(); //Closes the text files
		string MovieChoice;
		cout << endl << "Pick a movie by number (1 - 4) / Return to screens (5): ";
		cin >> MovieChoice;
		if (MovieChoice == "1") {
			FinalMovie = "Doctor Strange in the Multiverse of Madness"; //Variable to store the final movie thats printed at the end of the program
			Movies m1("Doctor Strange in the Multiverse of Madness", "Action", "Benedict Cumberbatch", 2022, 126); //Object for setting information with the class
			cout << endl <<"Name: " << m1.getName() << endl << "Genre: " << m1.getGenre() << endl << "Main Star: " << m1.getMainStar() << endl << "Release Year: " << m1.getYear() << endl << "Runtime: " << m1.getRuntime()<<"m"<< endl; 
			// ^ Prints the info with get method from class
			Schedule2 ss1("10:15", "13:00", "15:40", "18:30"); //Object for setting the specific schedule function
			cout << "\nAvailable Times:" << endl << "1. " << ss1.getShow1() << endl << "2. " << ss1.getShow2() << endl << "3. " << ss1.getShow3() << endl << "4. " << ss1.getShow4() << endl;
			// ^ Prints the info with the get method from class
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "2") {
			FinalMovie = "The Black Phone";
			Movies m2 = Movies("The Black Phone", "Horror", "Ethan Hawke", 2022, 107);
			cout << endl << "Name: " << m2.getName() << endl <<"Genre: " <<  m2.getGenre() << endl << "Main Star: " << m2.getMainStar() << endl <<"Release Year: " << m2.getYear() << endl <<"Runtime: " << m2.getRuntime() << "m" << endl;
			Schedule2 ss2("10:15", "12:30", "14:45", "17:15");
			cout << "\nAvailable Times:" << endl << "1. " << ss2.getShow1() << endl << "2. " << ss2.getShow2() << endl << "3. " << ss2.getShow3() << endl << "4. " << ss2.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "3") {
			FinalMovie = "Elvis";
			Movies m3 = Movies("Elvis", "Musical", "Austin Butler", 2022, 160);
			cout << endl << "Name: " << m3.getName() << endl << "Genre: " << m3.getGenre() << endl << "Main Star: " << m3.getMainStar() << endl << "Release Year: " << m3.getYear() << endl << "Runtime: " << m3.getRuntime() << "m" << endl;
			Schedule ss3("10:15", "13:20", "16:30");
			cout << "\nAvailable Times:" << endl << "1. " << ss3.getShow1()<< endl << "2. " << ss3.getShow2() << endl << "3. " << ss3.getShow3() << endl;
			SchedulePicker2();
			return FinalMovie;
		}
		else if (MovieChoice == "4") {
			FinalMovie = "Jurassic World Dominion";
			Movies m4 = Movies("Jurassic World Dominion", "Chris Pratt", "Action", 2022, 150);
			cout << endl << "Name: " << m4.getName() << endl << "Genre: " << m4.getGenre() << endl << "Main Star: " << m4.getMainStar() << endl << "Release Year: " << m4.getYear() << endl << "Runtime: " << m4.getRuntime() << "m" << endl;
			Schedule2 ss4("10:15", "13:10", "16:10", "19:05");
			cout << "\nAvailable Times:" << endl << "1. " << ss4.getShow1() << endl << "2. " << ss4.getShow2() << endl << "3. " << ss4.getShow3() << endl << "4. " << ss4.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "5") {
			ScreenChoice(); //Goes back to ScreenChoice function
		}
		else {
			cout << "\nWrong input, please try again\n" << endl; //Invalid input loops the user back to the beginning of the function
			BookingMovieS1();
		}
	}
	else {
		cout << "Failed to open file.";
	}
}

string BookingMovieS2() {
	string movieline;
	fstream movie;
	movie.open("Screen-2.txt");
	if (movie.is_open()) {
		while (!movie.eof()) {
			getline(movie, movieline);
			cout << movieline << endl;
		}
		movie.close();
		string MovieChoice;
		cout << endl << "Pick a movie by number (1 - 4) / Return to screens (5): ";
		cin >> MovieChoice;
		if (MovieChoice == "1") {
			FinalMovie = "Star Wars: A New Hope";
			Movies m1 = Movies("Star Wars: A New Hope", "Sci-Fi", "Mark Hamil", 1977, 121);
			cout << endl << "Name: " << m1.getName() << endl << "Genre: " << m1.getGenre() << endl << "Main Star: " << m1.getMainStar() << endl << "Release Year: " << m1.getYear() << endl << "Runtime: " << m1.getRuntime() << "m" << endl;
			Schedule2 ss1("10:15", "12:45", "15:15", "17:45");
			cout << "\nAvailable Times:" << endl << "1. " << ss1.getShow1() << endl << "2. " << ss1.getShow2() << endl << "3. " << ss1.getShow3() << endl << "4. " << ss1.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "2") {
			FinalMovie = "Star Wars: The Empire Strikes Back";
			Movies m2 = Movies("Star Wars: The Empire Strikes Back", "Sci-Fi", "Mark Hamil", 1980, 107);
			cout << endl << "Name: " << m2.getName() << endl << "Genre: " << m2.getGenre() << endl << "Main Star: " << m2.getMainStar() << endl << "Release Year: " << m2.getYear() << endl << "Runtime: " << m2.getRuntime() << "m" << endl;
			Schedule2 ss2("10:15", "12:45", "15:15", "17:45");
			cout << "\nAvailable Times:" << endl << "1. " << ss2.getShow1() << endl << "2. " << ss2.getShow2() << endl << "3. " << ss2.getShow3() << endl << "4. " << ss2.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "3") {
			FinalMovie = "Star Wars: The Phantom Menace";
			Movies m3 = Movies("Star Wars: The Phantom Menace", "Sci-Fi", "Jake Lloyd", 1991, 136);
			cout << endl << "Name: " << m3.getName() << endl << "Genre: " << m3.getGenre() << endl << "Main Star: " << m3.getMainStar() << endl << "Release Year: " << m3.getYear() << endl << "Runtime: " << m3.getRuntime() << "m" << endl;
			Schedule2 ss3("10:15", "13:00", "15:45","18:30");
			cout << "\nAvailable Times:" << endl << "1. " << ss3.getShow1() << endl << "2. " << ss3.getShow2() << endl << "3. " << ss3.getShow3() << endl << "4. " << ss3.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "4") {
			FinalMovie = "Star Wars: Revenge of the Sith";
			Movies m4 = Movies("Star Wars: Revenge of the Sith", "Sci-Fi", "Hayden Christensen", 2005, 140);
			cout << endl << "Name: " << m4.getName() << endl << "Genre: " << m4.getGenre() << endl << "Main Star: " << m4.getMainStar() << endl << "Release Year: " << m4.getYear() << endl << "Runtime: " << m4.getRuntime() << "m" << endl;
			Schedule2 ss4("10:15", "13:00", "15:45", "18:30");
			cout << "\nAvailable Times:" << endl << "1. " << ss4.getShow1() << endl << "2. " << ss4.getShow2() << endl << "3. " << ss4.getShow3() << endl << "4. " << ss4.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "5") {
			ScreenChoice();
		}
		else {
			cout << "\nWrong input, please try again\n" << endl;
			BookingMovieS2();
		}
	}
	else {
		cout << "Failed to open file.";
	}
}

string BookingMovieS3() {
	string movieline;
	fstream movie;
	movie.open("Screen-3.txt");
	if (movie.is_open()) {
		while (!movie.eof()) {
			getline(movie, movieline);
			cout << movieline << endl;
		}
		movie.close();
		string MovieChoice;
		cout << endl << "Pick a movie by number (1 - 4) / Return to screens (5): ";
		cin >> MovieChoice;
		if (MovieChoice == "1") {
			FinalMovie = "Donnie Darko";
			Movies m1 = Movies("Donnie Darko", "Fantasy", "Jake Gyllenhaal", 2001, 113);
			cout << endl << "Name: " << m1.getName() << endl << "Genre: " << m1.getGenre() << endl << "Main Star: " << m1.getMainStar() << endl << "Release Year: " << m1.getYear() << endl << "Runtime: " << m1.getRuntime() << "m" << endl;
			Schedule2 ss1("10:15", "12:45", "15:15", "17:45");
			cout << "\nAvailable Times:" << endl << "1. " << ss1.getShow1() << endl << "2. " << ss1.getShow2() << endl << "3. " << ss1.getShow3() << endl << "4. " << ss1.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "2") {
			FinalMovie = "Mulholland Drive";
			Movies m2 = Movies("Mulholland Drive", "Mystery", "Naomi Watts", 2001, 147);
			cout << endl << "Name: " << m2.getName() << endl << "Genre: " << m2.getGenre() << endl << "Main Star: " << m2.getMainStar() << endl << "Release Year: " << m2.getYear() << endl << "Runtime: " << m2.getRuntime() << "m" << endl;
			Schedule2 ss2("10:15", "12:45", "15:10", "17:30");
			cout << "\nAvailable Times:" << endl << "1. " << ss2.getShow1() << endl << "2. " << ss2.getShow2() << endl << "3. " << ss2.getShow3() << endl << "4. " << ss2.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "3") {
			FinalMovie = "Taxi Driver";
			Movies m3 = Movies("Taxi Driver", "Drama", "Robert De Niro", 1976, 114);
			cout << endl << "Name: " << m3.getName() << endl << "Genre: " << m3.getGenre() << endl << "Main Star: " << m3.getMainStar() << endl << "Release Year: " << m3.getYear() << endl << "Runtime: " << m3.getRuntime() << "m" << endl;
			Schedule2 ss3("10:15", "12:40", "15:00", "17:20");
			cout << "\nAvailable Times:" << endl << "1. " << ss3.getShow1() << endl << "2. " << ss3.getShow2() << endl << "3. " << ss3.getShow3() << endl << "4. " << ss3.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "4") {
			FinalMovie = "Drive";
			Movies m4 = Movies("Drive", "Drama", "Ryan Gosling", 2011, 160);
			cout << endl << "Name: " << m4.getName() << endl << "Genre: " << m4.getGenre() << endl << "Main Star: " << m4.getMainStar() << endl << "Release Year: " << m4.getYear() << endl << "Runtime: " << m4.getRuntime() << "m" << endl;
			Schedule2 ss4("10:15", "12:20", "14:30", "17:35");
			cout << "\nAvailable Times:" << endl << "1. " << ss4.getShow1() << endl << "2. " << ss4.getShow2() << endl << "3. " << ss4.getShow3() << endl << "4. " << ss4.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "5") {
			ScreenChoice();
		}
		else {
			cout << "\nWrong input, please try again\n" << endl;
			BookingMovieS3();
		}
	}
	else {
		cout << "Failed to open file.";
	}
}


string BookingMovieS4() {
	string movieline;
	fstream movie;
	movie.open("Screen-4.txt");
	if (movie.is_open()) {
		while (!movie.eof()) {
			getline(movie, movieline);
			cout << movieline << endl;
		}
		movie.close();
		string MovieChoice;
		cout << endl << "Pick a movie by number (1 - 4) / Return to screens (5): ";
		cin >> MovieChoice;
		if (MovieChoice == "1") {
			FinalMovie = "Fight Club";
			Movies m1 = Movies("Fight Club", "Drama", "Brad Pitt", 1999, 139);
			cout << endl << "Name: " << m1.getName() << endl << "Genre: " << m1.getGenre() << endl << "Main Star: " << m1.getMainStar() << endl << "Release Year: " << m1.getYear() << endl << "Runtime: " << m1.getRuntime() << "m" << endl;
			Schedule2 ss1("10:15", "13:00", "15:45", "18:30");
			cout << "\nAvailable Times:" << endl << "1. " << ss1.getShow1() << endl << "2. " << ss1.getShow2() << endl << "3. " << ss1.getShow3() << endl << "4. " << ss1.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "2") {
			FinalMovie = "Se7en";
			Movies m2 = Movies("Se7en", "Crime", "Brad Pitt", 1995, 127);
			cout << endl << "Name: " << m2.getName() << endl << "Genre: " << m2.getGenre() << endl << "Main Star: " << m2.getMainStar() << endl << "Release Year: " << m2.getYear() << endl << "Runtime: " << m2.getRuntime() << "m" << endl;
			Schedule2 ss2("10:15", "13:00", "15:45", "18:20");
			cout << "\nAvailable Times:" << endl << "1. " << ss2.getShow1() << endl << "2. " << ss2.getShow2() << endl << "3. " << ss2.getShow3() << endl << "4. " << ss2.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "3") {
			FinalMovie = "The Silence of the Lambs";
			Movies m3 = Movies("The Silence of the Lambs", "Horror", "Anthony Hopkins", 1991, 118);
			cout << endl << "Name: " << m3.getName() << endl << "Genre: " << m3.getGenre() << endl << "Main Star: " << m3.getMainStar() << endl << "Release Year: " << m3.getYear() << endl << "Runtime: " << m3.getRuntime() << "m" << endl;
			Schedule2 ss3("10:15", "12:40", "15:10", "17:40");
			cout << "\nAvailable Times:" << endl << "1. " << ss3.getShow1() << endl << "2. " << ss3.getShow2() << endl << "3. " << ss3.getShow3() << endl << "4. " << ss3.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "4") {
			FinalMovie = "Climax";
			Movies m4 = Movies("Climax", "Musical", "Sofia Boutella", 2018, 97);
			cout << endl << "Name: " << m4.getName() << endl << "Genre: " << m4.getGenre() << endl << "Main Star: " << m4.getMainStar() << endl << "Release Year: " << m4.getYear() << endl << "Runtime: " << m4.getRuntime() << "m" << endl;
			Schedule2 ss4("10:15", "12:20", "14:30", "16:40");
			cout << "\nAvailable Times:" << endl << "1. " << ss4.getShow1() << endl << "2. " << ss4.getShow2() << endl << "3. " << ss4.getShow3() << endl << "4. " << ss4.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "5") {
			ScreenChoice();
		}
		else {
			cout << "\nWrong input, please try again\n" << endl;
			BookingMovieS4();
		}
	}
	else {
		cout << "Failed to open file.";
	}
}

string BookingMovieS5() {
	string movieline;
	fstream movie;
	movie.open("Screen-5.txt");
	if (movie.is_open()) {
		while (!movie.eof()) {
			getline(movie, movieline);
			cout << movieline << endl;
		}
		movie.close();
		string MovieChoice;
		cout << endl << "Pick a movie by number (1 - 4) / Return to screens (5): ";
		cin >> MovieChoice;
		if (MovieChoice == "1") {
			FinalMovie = "Oldboy";
			Movies m1 = Movies("Oldboy", "Mystery", "Choi Min-sik", 2003, 120);
			cout << endl << "Name: " << m1.getName() << endl << "Genre: " << m1.getGenre() << endl << "Main Star: " << m1.getMainStar() << endl << "Release Year: " << m1.getYear() << endl << "Runtime: " << m1.getRuntime() << "m" << endl;
			Schedule2 ss1("10:15", "12:40", "15:05", "17:30");
			cout << "\nAvailable Times:" << endl << "1. " << ss1.getShow1() << endl << "2. " << ss1.getShow2() << endl << "3. " << ss1.getShow3() << endl << "4. " << ss1.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "2") {
			FinalMovie = "Parasite";
			Movies m2 = Movies("Parasite", "Thriller", "Choi Woo-shik", 2019, 137);
			cout << endl << "Name: " << m2.getName() << endl << "Genre: " << m2.getGenre() << endl << "Main Star: " << m2.getMainStar() << endl << "Release Year: " << m2.getYear() << endl << "Runtime: " << m2.getRuntime() << "m" << endl;
			Schedule2 ss2("10:15", "13:00", "15:45", "18:30");
			cout << "\nAvailable Times:" << endl << "1. " << ss2.getShow1() << endl << "2. " << ss2.getShow2() << endl << "3. " << ss2.getShow3() << endl << "4. " << ss2.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "3") {
			FinalMovie = "Shoplifters";
			Movies m3 = Movies("Shoplifters", "Drama", "Sakuya Ando", 2018, 121);
			cout << endl << "Name: " << m3.getName() << endl << "Genre: " << m3.getGenre() << endl << "Main Star: " << m3.getMainStar() << endl << "Release Year: " << m3.getYear() << endl << "Runtime: " << m3.getRuntime() << "m" << endl;
			Schedule2 ss3("10:15", "12:50", "15:20", "17:45");
			cout << "\nAvailable Times:" << endl << "1. " << ss3.getShow1() << endl << "2. " << ss3.getShow2() << endl << "3. " << ss3.getShow3() << endl << "4. " << ss3.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "4") {
			FinalMovie = "Kung Fu Hustle";
			Movies m4 = Movies("Kung Fu Hustle", "Comedy", "Stephen Chow", 2004, 99);
			cout << endl << "Name: " << m4.getName() << endl << "Genre: " << m4.getGenre() << endl << "Main Star: " << m4.getMainStar() << endl << "Release Year: " << m4.getYear() << endl << "Runtime: " << m4.getRuntime() << "m" << endl;
			Schedule2 ss4("10:15", "12:30", "14:40", "17:00");
			cout << "\nAvailable Times:" << endl << "1. " << ss4.getShow1() << endl << "2. " << ss4.getShow2() << endl << "3. " << ss4.getShow3() << endl << "4. " << ss4.getShow4() << endl;
			SchedulePicker();
			return FinalMovie;
		}
		else if (MovieChoice == "5") {
			ScreenChoice();
		}
		else {
			cout << "\nWrong input, please try again\n" << endl;
			BookingMovieS5();
		}
	}
	else {
		cout << "Failed to open file.";
	}
}

string ScreenChoice() { //Function for user to choose screens
	int Choice1;
	cout << "Choose a screen" << endl;
	cout << "1. Screen 1 (IMAX)\n2. Screen 2 (IMAX 3D)\n3. Screen 3 (Standard)\n4. Screen 4 (Standard)\n5. Screen 5 (VIP)\nPlease choose a number: ";
	cin >> Choice1;
	if (Choice1 == 1) {
		FinalScreen = "Screen 1 IMAX"; //Specific value of screen
		SeatCapacity = 5; //Each screen has it's own capacity
		BookingMovieS1();
		return FinalScreen; //Returns the value of which screen the user has chosen
	}
	else if (Choice1 == 2) {
		FinalScreen = "Screen 2 IMAX 3D";
		SeatCapacity = 82;
		BookingMovieS2();
		return FinalScreen;
	}
	else if (Choice1 == 3) {
		FinalScreen = "Screen 3 Standard";
		SeatCapacity = 24;
		BookingMovieS3();
		return FinalScreen;
	}
	else if (Choice1 == 4) {
		FinalScreen = "Screen 4 Standard";
		SeatCapacity = 56;
		BookingMovieS4();
		return FinalScreen;
	}
	else if (Choice1 == 5) {
		FinalScreen = "Screen 5 VIP";
		SeatCapacity = 100;
		BookingMovieS5();
		return FinalScreen;
	}
	else {
		cout << "\nWrong input, please try again\n" << endl;
		ScreenChoice();
	}
}

void StartOptions();

void AddMovies() { //Adding movies to the program
	string AName;
	string ARelease;
	string AGenre;
	string AStar;
	string ARuntime;
	string AScreen;
	cout << "Type in the movie name: ";
	getline(cin >> ws, AName);
	cout << "Type in the release year: ";
	cin >> ARelease;
	cout << "Type in the genre: ";
	cin >> AGenre;
	cout << "Type in the main star: ";
	getline(cin >> ws, AStar);
	cout << "Type in the runtime in minutes: ";
	cin >> ARuntime;
	cout << "Type in the screen type: ";
	cin >> AScreen;
	fstream UpcomingMovie;
	UpcomingMovie.open("UpcomingMovie.txt", ios::app); //Opens upcoming movie text file
	if (UpcomingMovie.is_open()) {
		UpcomingMovie << AName << " (" << ARelease << ")" << ", " << AGenre << ", " << AStar << ", " << ARuntime << "m, " << "[" << AScreen << "]."<<endl; //<--Adds movies in file, formatted like this
		UpcomingMovie.close();
		cout << "\n[------Movie has been added successfully-----]\n";
		StartOptions();
	}
	else {
		cout << "File cannot be opened.";
	}
}

void SeeUpcomingMovie() { //Function to see upcoming movies or newly added movies
	cout << "\n[-----Upcoming Movies-----]\n";
	string MovieLine;
	fstream UMovie;
	UMovie.open("UpcomingMovie.txt");
	if (UMovie.is_open()) {
		while (!UMovie.eof()) { //While its not end of file, the code below will be executed
			getline(UMovie, MovieLine);
			cout << MovieLine << endl;
		}
		UMovie.close();
		StartOptions();
	}
	else {
		cout << "File cannot be opened.";
	}
}

void StartOptions() { //Beginning function to let user choose the first few options
	string Choice1;
	cout << "Welcome to the Movie Booking System"<<endl;
	cout << "1. Book a Movie\n2. Add a Movie\n3. See Upcoming Movies\nPlease choose a number: ";
	cin >> Choice1;
	if (Choice1 == "1") {
		ScreenChoice();
	}
	else if (Choice1 == "2") {
		AddMovies();
	}
	else if (Choice1 == "3") {
		SeeUpcomingMovie();
	}
	else {
		cout << "\nWrong input, please try again\n" << endl;
		StartOptions();
	}
}

int main() {
	StartOptions();
}