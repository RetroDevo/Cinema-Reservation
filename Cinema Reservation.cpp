#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <limits>
#include <sstream>
#include <fstream>
using namespace std;

const int ROW_SEATS = 8;
const int COLUMN_SEATS = 14;

struct Booking {
	int id;
	string fullName;
    string birthday;
    char gender;
    string seats;
};

void display_seats(string seats[ROW_SEATS][COLUMN_SEATS], char& rows);
bool book_seats(string seats[ROW_SEATS][COLUMN_SEATS], int& row, int& col, char& c, char& rows);
bool cancel_seats(string seats[ROW_SEATS][COLUMN_SEATS], int& row, int& col, char& c, char& rows);
void loadBookedSeats(string seats[ROW_SEATS][COLUMN_SEATS]);
bool updateBookingsFile(int row, int col, string nameToVerify);
void search_specific_seat(string seats[ROW_SEATS][COLUMN_SEATS], char& rows);
void search_record();
void display_all_records();
string to_string(int value);
void thank();

int main(){
    int row, col;
    char rows = '1', c = 'Y', book1;
    string action;
    string *actionPtr = &action;
    string seats[ROW_SEATS][COLUMN_SEATS] = {{"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"},
                    {"[01]", "[02]", "[03]", "[04]", "[05]", "[06]", "[07]", "[08]", "[09]", "[10]", "[11]", "[12]", "[13]", "[14]"}};
   
    loadBookedSeats(seats);

    while (true) {
      system("cls");
      rows = '1';
        display_seats(seats, rows);

        cout << "\nMenu: \n 1. Book Seat\n 2. Cancel Booking\n 3. Search Specific Seat\n 4. Search Record\n 5. Display All Records\n 6. Exit\n Choose an option: ";
        cin >> *actionPtr;

        if (action == "1") {
        	bool bookAnother = false;
            do{
            	bookAnother = book_seats(seats, row, col, c, rows);
        	}while (bookAnother);
        } else if (action == "2") {
            do{
            	if (!cancel_seats(seats, row, col, c, rows)) continue;
        		break;
        	}while (true);
        } else if (action == "3") {
    		search_specific_seat(seats, rows);
		} else if (action == "4") {
    		search_record();
		} else if (action == "5") {
			display_all_records();
        } else if (action == "6") {
            thank();
            break;
		} else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}

void display_seats(string seats[ROW_SEATS][COLUMN_SEATS], char& rows) {
	cout<< endl << setw(76) <<"Welcome to Kenly Rogers Cinema Ticket Reservation Program!\n";
    cout<< "     [===============================================================================]\n";
    cout<< "     [------------------------------------DISPLAY------------------------------------]\n";
    cout<< "     [===============================================================================]\n"<< endl;
    for (int i = 0; i < 8; ++i) {
        cout << "Row " << rows << ":  ";
        ++rows;
        for (int j = 0; j < 14; ++j) {
            cout << seats[i][j];
            if (j == 3 || j == 9) { 
                cout << "    ";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

bool book_seats(string seats[ROW_SEATS][COLUMN_SEATS], int& row, int& col, char& c, char& rows){
    while (true) { 
        bool validInput = false; 
        while (!validInput) {
            cout << endl << "Enter Row & Column (e.g., 2 5 for Row 2, Column 5): ";
            if (cin >> row >> col) {
                if (row >= 1 && row <= ROW_SEATS && col >= 1 && col <= COLUMN_SEATS) {
                    --row; 
                    --col;
                    if (seats[row][col] == "\033[32m[XX]\033[0m") { 
                        cout << endl << "The Seat is not available. Please choose another seat." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        break; 
                    } else {
                        validInput = true;
                    }
                } else {
                    cout << "Please pick a valid seat within the range Row 1-" << ROW_SEATS << ", Column 1-" << COLUMN_SEATS << "." << endl;
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter numbers only." << endl;
            }
        }
        if (validInput) { 
            break; 
        }
    }

	Booking booking;
	
	cout << "Enter Student ID: ";
	while (!(cin >> booking.id) || booking.id < 0) {
    	cin.clear();
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	cout << "Invalid input. Please enter your student ID" <<endl;
    	cout << "(e.g., 202011567) : ";
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool isValidName;
	do {
    	cout << "Enter Full Name: ";
    	getline(cin, booking.fullName);

    	isValidName = true;
    	for (size_t i = 0; i < booking.fullName.length(); ++i) {
        	char &c = booking.fullName[i];
        	if (isdigit(c)) {
        	    cout << "Error: Name should not contain numbers. Please enter again." << endl;
        	    isValidName = false;
        	    break;
        	}
        	c = toupper(c);
    	}
	} while (!isValidName);

    bool isValidDate;
	string dateInput;

	do {
    	cout << "Enter Birthday (YYYY-MM-DD): ";
    	getline(cin, dateInput);

    	isValidDate = true; 

    	if (dateInput.length() != 10 || dateInput[4] != '-' || dateInput[7] != '-') {
    	    isValidDate = false;
    	} else {
   	    	for (int i = 0; i < dateInput.length(); ++i) {
            	if (i == 4 || i == 7) continue;

            	if (!isdigit(dateInput[i])) {
                	isValidDate = false;
                	break;
            	}
        	}
    	}

    	if (!isValidDate) {
        	cout << "Invalid date format. Please enter the date in YYYY-MM-DD format." << endl;
    	}

	} while (!isValidDate);
	booking.birthday = dateInput;
    
    char genderInput;
    bool validGender = false;

	cout << "Enter gender [M/F]: ";
	while (!validGender) {
    	cin >> genderInput;
    	genderInput = toupper(genderInput);

    	if (genderInput == 'M' || genderInput == 'F') {
        	validGender = true;
    	} else {
        	cout << "Invalid input. Please enter 'M' or 'F': ";
        	if (cin.peek() == '\n') cin.ignore();
    	}
	}
	booking.gender = genderInput;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	booking.seats = "Row " + to_string(row + 1) + " Seat " + to_string(col + 1); 
    seats[row][col] = "\033[32m[XX]\033[0m";
    
    ofstream outFile("bookings.txt", ios::app);
    outFile << booking.id << ", "
            << booking.fullName << ", "
            << booking.birthday << ", "
            << booking.gender << ", "
            << booking.seats << endl;
    outFile.close();

    seats[row][col] = "\033[32m[XX]\033[0m";
    system("cls");

    rows = '1';
    display_seats(seats, rows);
    cout << endl << "Seat Booked!" << endl;
    
	cout << endl << "Do You Want To Book Another Seat? [Y/N]: " << endl;
	char yesOrNoValue;
    char *yesOrNo = &yesOrNoValue;

	while (true) {
    	cin >> *yesOrNo;
    	*yesOrNo = toupper(*yesOrNo);

    	if (*yesOrNo == 'Y' || *yesOrNo == 'N') {
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	break;
    	} else {
        	cout << "Invalid input. Please press 'Y' for Yes or 'N' to go back to menu: ";
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
	}
    return *yesOrNo == 'Y';
}

bool cancel_seats(string seats[ROW_SEATS][COLUMN_SEATS], int& row, int& col, char& c, char& rows) {
    bool validRowCol = false;
	
	while (!validRowCol) {
    	cout << endl << "Enter Row & Column to Cancel: ";
    	if (cin >> row >> col) {
        	if (row >= 1 && row <= ROW_SEATS && col >= 1 && col <= COLUMN_SEATS) {
            	validRowCol = true;
        	} else {
            	cout << "Please pick a valid seat within the range Row 1-" << ROW_SEATS << ", Column 1-" << COLUMN_SEATS << "." << endl;
            	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	}
    	} else {
        	cout << "Invalid input. Please enter numbers only." << endl;
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
	}
    
    --row;
    --col;
    
	if (seats[row][col] != "\033[32m[XX]\033[0m") {
	    cout << endl << "The Seat is not currently booked." << endl;
	
	    bool validSeat = false;
	    while (!validSeat) {
	        cout << "Would you like to try canceling another seat? (Y/N): ";
	        cin >> c;
	        c = toupper(c);
	
	        if (c == 'Y') {
	            validSeat = true;
	            return false; 
	        } else if (c == 'N') {
	            validSeat = true; 
	            return true; 
	        } else {
	            cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No." << endl;
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        }
	    }
	}
    cout << "Enter your name for verification: ";
	cin.ignore();
    string nameToVerify;
    getline(cin, nameToVerify);
    for (int i = 0; i < nameToVerify.length(); ++i) {
    	nameToVerify[i] = toupper(nameToVerify[i]);
	}
    nameToVerify.erase(0, nameToVerify.find_first_not_of(" \t"));
  	nameToVerify.erase(nameToVerify.find_last_not_of(" \t") + 1);

    bool nameVerified = false;
    ifstream inFile("bookings.txt");
    string line;
    
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, fullName, birthday, genderStr, seatInfo;
        
        getline(ss, idStr, ',');
    	ss.ignore();
    	getline(ss, fullName, ',');
    	ss.ignore();
    	getline(ss, birthday, ',');
    	ss.ignore();
    	getline(ss, genderStr, ',');
    	ss.ignore();
    	getline(ss, seatInfo);

	int bookedRow, bookedCol;
    	if (sscanf(seatInfo.c_str(), "Row %d Seat %d", &bookedRow, &bookedCol) == 2) {

    	if (nameToVerify == fullName && bookedRow == row + 1 && bookedCol == col + 1) {
        nameVerified = true;
        break;
    	    }
    	}
	}
	inFile.close();

    if (!nameVerified) {
        cout << "Name verification failed or seat was not booked under this name." << endl;
        return false;
    }

    if (seats[row][col] != "\033[32m[XX]\033[0m") {
        cout << endl << "The Seat is not currently booked." << endl;
        return true;
    }

    stringstream seatNum;
    seatNum << "[" << (col < 9 ? "0" : "") << (col + 1) << "]";
    seats[row][col] = seatNum.str();

    updateBookingsFile(row + 1, col + 1, nameToVerify);
    
	system("cls");
	rows = '1';
	display_seats(seats, rows);
	cout << endl << "Seat Cancellation Successful!" << endl;

	bool cancelSeat = false;
	while (!cancelSeat) {
	    cout << endl << "Do You Want To Cancel Another Seat? (Y/N): ";
	    cin >> c;
	    c = toupper(c);
	
	    if (c == 'Y' || c == 'N') {
	        cancelSeat = true;
	    } else {
	        cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No." << endl;
	        cin.clear(); 
	        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    }
	}
	
	if (c == 'Y') {
	    return false; 
	} else {
	    return true;
	}

}

void loadBookedSeats(string seats[ROW_SEATS][COLUMN_SEATS]) {
    ifstream inFile("bookings.txt");
    if (!inFile.is_open()) {
        cout << "Failed to open bookings.txt" << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int id;
        char gender;
        string fullName, birthday, seatInfo, tempGender;


        ss >> id; 
        ss.ignore(2); 
        getline(ss, fullName, ',');
        ss.ignore(1); 
        getline(ss, birthday, ',');
        ss.ignore(1);
        getline(ss, tempGender, ',');
        gender = tempGender[0]; 
        ss.ignore(1); 
        getline(ss, seatInfo);

        cout << "Processing booking ID " << id << " for seat: " << seatInfo << " (" << gender << ")" << endl;

        int row, col;
        if (sscanf(seatInfo.c_str(), "Row %d Seat %d", &row, &col) == 2) {
            --row; --col;
            if (row >= 0 && row < ROW_SEATS && col >= 0 && col < COLUMN_SEATS) {
                seats[row][col] = "\033[32m[XX]\033[0m";
                cout << "Marked Row " << row+1 << " Seat " << col+1 << " as booked." << endl;
            }
        }
    }
    inFile.close();
}

bool updateBookingsFile(int row, int col, string nameToVerify) {
    bool found = false;
    ifstream inFile("bookings.txt");
    ofstream tempFile("temp_bookings.txt");

    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files." << endl;
        return false;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, fullName, birthday, gender, seatInfo;
        
        getline(ss, idStr, ',');
        ss.ignore();
        getline(ss, fullName, ',');
        ss.ignore();
        getline(ss, birthday, ',');
        ss.ignore();
        getline(ss, gender, ',');
        ss.ignore();
        getline(ss, seatInfo);

        string currentSeat = "Row " + to_string(row) + " Seat " + to_string(col);

        if (fullName == nameToVerify && seatInfo.find(currentSeat) != string::npos) {
            found = true;
        } else {
            tempFile << line << '\n';
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("bookings.txt");
        rename("temp_bookings.txt", "bookings.txt");
    } else {
        remove("temp_bookings.txt");
    }

    return found;
}

void search_specific_seat(string seats[ROW_SEATS][COLUMN_SEATS], char& rows) {
    int searchRowVal, searchColVal;
    int *searchRow = &searchRowVal;
    int *searchCol = &searchColVal;
    bool searchRowColVer = false;
    
    while (!searchRowColVer) {
        cout << "Enter Row & Column: ";
        if (cin >> *searchRow >> *searchCol) {
            if(*searchRow >= 1 && *searchRow <= ROW_SEATS && *searchCol >= 1 && *searchCol <= COLUMN_SEATS) {
                searchRowColVer = true;
            } else {
                cout << "Invalid seat location. Please enter row 1-" << ROW_SEATS << " and column 1-" << COLUMN_SEATS << "." << endl;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter integers only." << endl;
        }
    }

    system("cls");
	rows = '1';
	
    cout<< endl << "     [===============================================================================]\n";
    cout<< "     [------------------------------------DISPLAY------------------------------------]\n";
    cout<< "     [===============================================================================]\n"<< endl;

    for (int i = 0; i < ROW_SEATS; ++i) {
        cout << "Row " << rows << ":  ";
        ++rows;
        for (int j = 0; j < COLUMN_SEATS; ++j) {
            bool isSearchedSeat = *searchRow == i + 1 && *searchCol == j + 1;
            bool isReserved = seats[i][j] == "\033[32m[XX]\033[0m";
            if (isSearchedSeat) {
                cout << (isReserved ? "\033[32m[XX]\033[0m" : "\033[32m" + seats[i][j] + "\033[0m");
            } else {
                cout << (isReserved ? "\033[90m[XX]\033[0m" : "\033[90m" + seats[i][j] + "\033[0m");
            }

            if (j == 3 || j == 9) {
                cout << "    ";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << "\033[0m"; 
    cin.ignore(); 
    cout << "Press any key to return to the menu...";
    cin.get(); 
}

void search_record() {
    int searchIDP;
    int *searchID = &searchIDP;
    char searchAgainP;
    char *searchAgain = &searchAgainP;
    do {
    	bool verID = false;
    	system("cls");
    	do{
            cout << "Enter your ID to search for your reserved seat (or enter '0' to return to menu): ";
            if (!(cin >> *searchID)) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input. Please enter a valid ID or '0' to return to menu.\n";
            } else if (*searchID == 0) {
                return; 
            } else {
                verID = true; 
            }
        } while (!verID);

        ifstream inFile("bookings.txt");
        if (!inFile.is_open()) {
            cout << "Failed to open bookings.txt" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(inFile, line)) {
            stringstream ss(line);
            int id;
            string idStr, fullName, birthday, seatInfo;
            char gender;
            getline(ss, idStr, ',');
            stringstream idConvert(idStr); 
            idConvert >> id;
            ss.ignore();
            getline(ss, fullName, ',');
            ss.ignore();
            getline(ss, birthday, ',');
            ss.ignore();
            ss >> gender; 
            ss.ignore(2); 
            getline(ss, seatInfo);

            if (id == *searchID) {
                cout << "Booking found: " << seatInfo << " for " << fullName << " (" << gender << ")" << endl;
                found = true;
            }
        }
        inFile.close();

        if (!found) {
            cout << "No booking found for ID " << searchID << "." << endl;
        }


		bool tryAgainVer = false;
		while (!tryAgainVer){
			cout << "Do you wish to search again? (Y/N): ";
        	cin >> *searchAgain;
        	*searchAgain = toupper(*searchAgain);
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');	
        	
        	if (*searchAgain == 'Y' || *searchAgain == 'N'){
        		tryAgainVer = true;
			} else {
				cout << "Invalid input. Please enter 'Y' or 'N'." <<endl;
			}
		}
    } while (*searchAgain == 'Y');

    cout << "Press any key to return to the menu...";
    cin.get();
}

void display_all_records() {
	system("cls");
    ifstream inFile("bookings.txt");
    if (!inFile.is_open()) {
        cout << "Failed to open bookings.txt" << endl;
        cout << "Press any key to return to the menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    cout << endl << "============================================ All Records =============================================" << endl;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int id;
        char gender;
        string fullName, birthday, seatInfo;

        ss >> id; 
        ss.ignore(); 
        getline(ss, fullName, ','); 
        ss.ignore();
        getline(ss, birthday, ','); 
        ss.ignore(); 
        ss >> gender; 
        ss.ignore(2); 
        getline(ss, seatInfo); 

        cout << "ID: " << id << ", Name: " << fullName << ", Birthday: " << birthday << ", Gender: " << gender << ", Seat: " << seatInfo << endl;
    }
    cout << "======================================================================================================" << endl;
    cout << "Press any key to return to the menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    inFile.close();
}

string to_string(int value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

void thank(){
	system("cls");
            cout << setw(75) <<"============================================" <<endl;
            cout << setw(68) <<"Thank you for using our program!" <<endl;
            cout << setw(75) <<"============================================" <<endl;
        	cout << setw(70) <<"If there are any concerns, contact: " <<endl;
			cout << setw(48) <<"Mark Eron Diaz" <<endl;
			cout << setw(58) <<"Contact No.: 09157897360" <<endl;
			cout << setw(60) <<"Email: markeron5@gmail.com" <<endl;
			cout << setw(75) <<"============================================" <<endl;
			cout << setw(59) <<"Fetalver, Christian Lloyd" <<endl;
			cout << setw(55) <<"Dela Pena, Sean Kenly" <<endl;
			cout << setw(54) <<"Obmerga, John Janiel" <<endl;
			cout << setw(53) <<"Parocha, Vince John" <<endl;
			cout << setw(75) <<"============================================" <<endl;
}
