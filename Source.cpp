#include <iostream>
using namespace std;

class seat {
private:
	int seatNumber;
	bool reserved;
public:
	seat(int num);
	void setSeatNum(int num);
	int getSeatNum();
	void setReserved(int r);
	bool getReserved();
	void prinInfo();
};

class flight {
private:
	seat** seats;
	static int count;//to count how many seats are reserved
public:
	flight();
	bool isValid(int seatNumber);//function that checks if the seatNumber entered is vallid or not
	bool isReserved(int seatNumber);//function that checks if the seatNumber entered is reserved or empty

	void reserve_a_seat();
	void delete_a_reserved_seat();
	void delete_all_reserved_seats();
	void print_out_flight_seats_map();
	~flight();
};
int flight::count = 0;

void printMenu();

int main() {
	flight ABC;
	int option;
	printMenu();
	while (cin >> option && option != 5) {
		if (option == 1) {
			ABC.reserve_a_seat();
		}
		else if (option == 2) {
			ABC.delete_a_reserved_seat();
		}
		else if (option == 3) {
			ABC.delete_all_reserved_seats();
		}
		else if (option == 4) {
			ABC.print_out_flight_seats_map();
		}
		else {
			cout << "please enter valid option number" << endl;
		}
		cout << endl;
		printMenu();
	}
	return 0;
}

void printMenu() { //a function to print the menu of things you can do
	cout << "------------------------------------------\nMENU : " << endl;
	cout << "1. Reserve a new empty seat" << endl;
	cout << "2. Delete a reserved seat" << endl;
	cout << "3. Delete all reserved seats" << endl;
	cout << "4. Print out flight seat map" << endl;
	cout << "5. QUIT" << endl;
	cout << "enter a number : " << endl;

}

//class seat functions 
//seat class const.
seat::seat(int num) {
	seatNumber = num;
	reserved = false;
}
//seat number setter and getter 
void seat::setSeatNum(int num) {
	seatNumber = num;
}
int seat::getSeatNum() {
	return seatNumber;
}
//reserved setter and getter
void seat::setReserved(int r) {
	reserved = r;
}
bool seat::getReserved() {
	return reserved;
}
//func to print seat info 
void seat::prinInfo() {
	cout << "seat " << seatNumber << " : ";
	if (reserved) {
		cout << "reserved\t";
	}
	else {
		cout << "empty\t";
	}
}

//class flight functions
// 
//flight const. : allocate the multidimentional seat matrix 
flight::flight() { //we allocate the matrix first 3 rows have 2 cols and other rows have 4 cols
	seats = new seat * [9];
	for (int i = 0, snum = 11; i < 9; i++) {
		if (i < 3) {
			seats[i] = new seat[2]{ snum,snum + 1 };
			snum += 10;
		}
		else {
			seats[i] = new seat[4]{ snum,snum + 1,snum + 2,snum + 3 };
			snum += 10;
		}//end of if / else
	}//end of loop
}//end of const.

//func. to check if the seat number entered valid 
bool flight::isValid(int seatNumber) {
	for (int i = 0; i < 9; i++) {
		if (i < 3) { //checks if the seats number is in the first 3 rows
			for (int j = 0; j < 2; j++) {
				if (seats[i][j].getSeatNum() == seatNumber)
					return true;
			}
		}
		else { //if the seat number is in the other rows 
			for (int j = 0; j < 4; j++) {
				if (seats[i][j].getSeatNum() == seatNumber)
					return true;
			}//end of cols loop
		}//end of if/else
	}//end of if

	return false;
}

//func to check if the seat number entered reserved or empty
bool flight::isReserved(int seatNumber) {
	int row, col;
	col = seatNumber % 10;//to get the column number
	seatNumber = seatNumber / 10;
	row = seatNumber % 10;//to get the row number
	return seats[row - 1][col - 1].getReserved();// row-1 & col-1 because of the indexing
}

//funct to reserve a seat
void flight::reserve_a_seat() {
	int seatNumber, seatNum;

	if (count == 30) { //first we check if all seats are reserved or not so we dont get in an infinte loop
		cout << "all seats are reserved, thank u" << endl;
	}
	else {
		cout << "please enter seat number : " << endl;
		cin >> seatNumber;

		while (!isValid(seatNumber)) { //while loop to check if the entered seat number is valid
			cout << "please enter a valid seat number : " << endl;
			cin >> seatNumber;
		}

		while (isReserved(seatNumber)) { //while loop to check if the entered seat number is empty
			cout << "the seat is not empty, please enter another seat number : " << endl;
			cin >> seatNumber;
			while (!isValid(seatNumber)) { //while loop to check if the entered seat number is valid
				cout << "please enter a valid seat number : " << endl;
				cin >> seatNumber;
			}
		}
		seatNum = seatNumber;
		int row, col;
		col = seatNum % 10;//to get the column number
		seatNum = seatNum / 10;
		row = seatNum % 10;//to get the row number
		seats[row - 1][col - 1].setReserved(1);//now we reserved the seat
		cout << "seat " << seatNumber << " is reserved" << endl;
		count++;
	}//end of else

}

//func to delete a reserved seat 
void flight::delete_a_reserved_seat() {
	int seatNumber, seatNum;

	if (count == 0) { //first we check if all seats are empty or not so we dont get in an infinte loop
		cout << "you cant delete, all seats are empty" << endl;
	}
	else {
		cout << "please enter seat number : " << endl;
		cin >> seatNumber;

		while (!isValid(seatNumber)) { //while loop to check if the entered seat number is valid
			cout << "please enter a valid seat number : " << endl;
			cin >> seatNumber;
		}

		while (!isReserved(seatNumber)) { //while loop to check if the entered seat number is reserved
			cout << "the seat is empty, please enter another seat number : " << endl;
			cin >> seatNumber;
			while (!isValid(seatNumber)) { //while loop to check if the entered seat number is valid
				cout << "please enter a valid seat number : " << endl;
				cin >> seatNumber;
			}
		}

		seatNum = seatNumber;
		int row, col;
		col = seatNum % 10;//to get the column number
		seatNum = seatNum / 10;
		row = seatNum % 10;//to get the row number
		seats[row - 1][col - 1].setReserved(0);//now we deleted the reservation for the seat
		cout << "seat " << seatNumber << " is deleted" << endl;
		count--;
	}//end of else
}

//func to delete all reserved seats
void flight::delete_all_reserved_seats() {
	for (int i = 0; i < 9; i++) {
		if (i < 3) {
			for (int j = 0; j < 2; j++) {
				seats[i][j].setReserved(0);
			}
		}
		else {
			for (int j = 0; j < 4; j++) {
				seats[i][j].setReserved(0);
			}
		}
	}
	cout << "all reserved seats are deleted" << endl;
	count = 0;
}

//func to print flight seats map 
void flight::print_out_flight_seats_map() {
	cout << "total reserved seats : " << count << endl; // print how many seats is being reserved
	//now print seats map
	for (int i = 0; i < 9; i++) {
		if (i < 3) {
			for (int j = 0; j < 2; j++) {
				seats[i][j].prinInfo();
			}
			cout << endl;
		}
		else {
			for (int j = 0; j < 4; j++) {
				seats[i][j].prinInfo();
			}
			cout << endl;
		}
	}
}

//flight destructor : free the allocated memory
flight::~flight() { //now we free the alocated memory
	for (int i = 0; i < 9; i++) {
		delete[] seats[i];
	}
	delete[]seats;
}