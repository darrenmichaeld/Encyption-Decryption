#include <iostream>
#include <fstream>
using namespace std;

const int NUM_LETTERS = 26; // number of letters in the alphabet
const int NUM_DIGRAPHS = 676; // number of all possible digraphs
const int MAX_PATH_LENGTH = 100; // maximum length of a file path

void number_to_diagraph(int num, char& c1, char& c2) {

    c1 = num / NUM_LETTERS + 'A';
    c2 = num % NUM_LETTERS + 'A';
}

void numbers_to_text(int num1, int num2, char& c1, char& c2, char& c3, char& c4) {
    
    number_to_diagraph(num1, c1, c2);
    number_to_diagraph(num2, c3, c4);
}

int digraph_to_number(char c1, char c2) {

    int num1 = static_cast<int>(c1) - static_cast<int>('A');
    int num2 = static_cast<int>(c2) - static_cast<int>('A');
    return num1 * 26 + num2;
   
}

int encrypt_digraph_to_number(char c1, char c2, int key) {

    int enc = digraph_to_number(c1, c2); 
    return (enc + key) % NUM_DIGRAPHS; 
    
}

void encrypt_text_to_numbers(char c1, char c2, char c3, char c4, int key, int& num1, int& num2) {

    num1 = encrypt_digraph_to_number(c1,c2, key);
    num2 = encrypt_digraph_to_number(c3,c4, key);

}

int decrypt_digraph_to_number(char c1, char c2, int key) {

    int dec = digraph_to_number(c1, c2); 
    return (dec - key) % NUM_DIGRAPHS;

}

void decrypt_text_to_numbers(char c1, char c2, char c3, char c4, int key, int& num1, int& num2) {

    num1 = decrypt_digraph_to_number(c1,c2, key);
    num2 = decrypt_digraph_to_number(c3,c4, key);

}

int main() {

    cout << "Welcome to Lab3: Encryption & Decryption!" << endl;

    char file_path[MAX_PATH_LENGTH];
    cout << "Enter the input file name: ";
    cin >> file_path;
    ifstream fin(file_path);

    if (!fin) {
        cout << "Error: Can not open " << file_path << endl; 
        return -1;
    }

    int option, key;
    char c1, c2, c3, c4;

    fin >> option >> c1 >> c2 >> c3 >> c4 >> key;

    fin.close();

    if (option == 1) { // Encryption
        int num1, num2;
        char e1, e2, e3, e4;

        encrypt_text_to_numbers(c1, c2, c3, c4, key, num1, num2);
        numbers_to_text(num1, num2, e1, e2, e3, e4);

        cout << "The encrypted numbers are: " << num1 << " and " << num2 << endl;
        cout << "The encrypted text is: " << e1 << e2 << e3 << e4 << endl;
    }
    else if (option == 2) { // Decryption
        int num1, num2;
        char d1, d2, d3, d4;

        decrypt_text_to_numbers(c1, c2, c3, c4, key, num1, num2);
        numbers_to_text(num1, num2, d1, d2, d3, d4);

        cout << "The decrypted numbers are: " << num1 << " and " << num2 << endl;
        cout << "The decrypted text is: " << d1 << d2 << d3 << d4 << endl;
    }
    else {
        // You should not reach here
        cout << "Error: Invalid option " << option << endl;
        return -1;
    }

    return 0;
}