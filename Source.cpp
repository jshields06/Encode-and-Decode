// C++ code that asks the user for a 4 digit number, then prompts them to encode or decode the number.
// After selecting whether or not to decode, code asks if user would like to encode another number.
// Code then asks user if they would like to clear the file.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// function declarations
void encrypt();
void decrypt();
void digits();
void decision();
void clearfile();

// global variables
int a, b, c, d;
int j = 0; // tracks numbers in file

// get and store digits
void digits() {
    fstream file("text.txt", ios::app); // open file, append mode
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    // get input for digits
    cout << "Enter a 4-digit number (Press Enter after each digit): ";
    cin >> a >> b >> c >> d;

    // validate each digit is valid (0-9)
    while (a / 10 != 0 || b / 10 != 0 || c / 10 != 0 || d / 10 != 0) {
        cout << "Enter a valid 4-digit number (each digit should be between 0-9): ";
        cin >> a >> b >> c >> d;
    }

    // store digits in file
    file << a << " " << b << " " << c << " " << d << endl;
    j++; // increment stored entries

    // close file
    file.close();
}

// encrypts digits stored in file
void encrypt() {
    ifstream file_in("text.txt");  // open file for reading
    if (!file_in) {
        cout << "Error opening file!" << endl;
        return;
    }

    // store all lines of digits from file
    vector<string> lines;
    string line;
    while (getline(file_in, line)) {
        lines.push_back(line);
    }
    file_in.close();  // close file after reading

    // open file for writing (clear existing content)
    ofstream file_out("text.txt", ios::trunc);
    if (!file_out) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    // encrypt each line, write to file
    for (string& line : lines) {
        istringstream iss(line);
        iss >> a >> b >> c >> d;

        // encrypt digit
        a = (a <= 2) ? a + 7 : a - 3;
        b = (b <= 2) ? b + 7 : b - 3;
        c = (c <= 2) ? c + 7 : c - 3;
        d = (d <= 2) ? d + 7 : d - 3;

        // write encrypted digits in file
        file_out << a << " " << b << " " << c << " " << d << endl;
    }

    file_out.close(); // close file after writing
    cout << "Encryption complete. Number encrypted is: " << a << b << c << d << endl;
}

// decrypts digits in file
void decrypt() {
    ifstream file_in("text.txt");  // open file for reading
    if (!file_in) {
        cout << "Error opening file!" << endl;
        return;
    }

    // store lines of digits from file
    vector<string> lines;
    string line;
    while (getline(file_in, line)) {
        lines.push_back(line);
    }
    file_in.close();  // close file after reading

    // open file for writing
    ofstream file_out("text.txt", ios::trunc);
    if (!file_out) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    // decrypt each line, write to file
    for (string& line : lines) {
        istringstream iss(line);
        iss >> a >> b >> c >> d;

        // decrypt each digit
        a = (a >= 7) ? a - 7 : a + 3;
        b = (b >= 7) ? b - 7 : b + 3;
        c = (c >= 7) ? c - 7 : c + 3;
        d = (d >= 7) ? d - 7 : d + 3;

        // write decrypted digits to file
        file_out << a << " " << b << " " << c << " " << d << endl;
    }

    file_out.close(); // close file
    cout << "Decryption complete. Number decrypted is: " << a << b << c << d << endl;
}

// handles user decisions (encrypt, decrypt, clear, exit)
void decision() {
    char decide;
    cout << "Would you like to encrypt a number? (Enter Y or N): ";
    cin >> decide;

    while (true) {
        if (decide == 'Y') {
            digits();  // get input and write to file
            encrypt(); // encrypt the input
            cout << "Would you like to decrypt this number? (Enter Y or N): ";
            cin >> decide;
            if (decide == 'Y') {
                decrypt(); // decrypt the input
                decision(); // ask for next decision
            }
            else if (decide != 'Y' && decide != 'N') {
                cout << "Please enter Y or N. ";
                cin >> decide;
            }
        }
        else if (decide == 'N') {
            cout << "Would you like to clear the file? (Enter C or N): ";
            cin >> decide;
            if (decide == 'C') {
                clearfile();
                exit(0); // end program after clearing
            }
            if (decide == 'N') {
                exit(0); // end without clearing
            }
        }
        else {
            cout << "Please enter Y or N. ";
            cin >> decide;
        }
    }
}

// clears file
void clearfile() {
    ofstream file("text.txt", ios::trunc);  // open file and truncate
    file.close();  // close file
}

int main() {
    decision();
    return 0;
}