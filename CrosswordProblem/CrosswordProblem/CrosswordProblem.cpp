#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool canplaceH(char crossword[10][10], string current, int i, int j) {
    int crosswordSizeRows = 10;

    if (j + current.length() > crosswordSizeRows) return false;

    for (int x = 0; x < current.length(); x++) {
        if (crossword[i][j + x] != '-' && crossword[i][j + x] != current[x]) {
            return false;
        }
    }

    return true;
}

bool canplaceV(char crossword[10][10], string current, int i, int j) {
    int crosswordSizeCols = 10;

    if (i + current.length() > crosswordSizeCols) return false;

    for (int x = 0; x < current.length(); x++) {
        if (crossword[i + x][j] != '-' && crossword[i + x][j] != current[x]) {
            return false;
        }
    }

    return true;
}


bool* placeH(char crossword[10][10], string current, int i, int j) {

    bool *res = new bool[current.length()];

    for (int k = 0; k < current.length(); k++) {
        if (crossword[i][j + k] == '-') {
            res[k] = true;
            crossword[i][j + k] = current[k];
        }
        else {
            res[k] = false;
        }
    }

    return res;
}

bool* placeV(char crossword[10][10], string current, int i, int j) {

    bool* res = new bool[current.length()];

    for (int k = 0; k < current.length(); k++) {
        if (crossword[i+k][j] == '-') {
            res[k] = true;
            crossword[i+k][j] = current[k];
        }
        else { 
            res[k] = false; 
        }
    }

    return res;
}

void unplaceH(char crossword[10][10], bool arr[], int i, int j , int len) {

    for (int k = 0; k < len ; k++) {
        if (arr[k]) {
            crossword[i][j + k] = '-';
        }
    }

    delete[] arr;
}

void unplaceV(char crossword[10][10], bool arr[], int i, int j , int len) {

    for (int k = 0; k < len; k++) {
        if (arr[k]) {
            crossword[i+k][j] = '-';
        }
    }

    delete[] arr;
}


void printCrossword(char crossword[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << crossword[i][j] << " ";
        }
        cout << endl;
    }
}

bool solveCrossword(char crossword[10][10], vector<string> words, int index) {

    if (index == words.size()) {
        printCrossword(crossword);
        return true;
    }

    string current = words[index];

    int crosswordSizeRows = 10;

    int crosswordSizeColumns = 10;

    for (int i = 0; i < crosswordSizeRows ; i++) {

        for (int j = 0; j < crosswordSizeColumns; j++) {

            if (crossword[i][j] == '-' || crossword[i][j] == current.at(0)) {
                if (canplaceH(crossword, current, i, j) == true) {

                    bool* wePlaced = placeH(crossword, current, i, j);
                    if (solveCrossword(crossword, words, index + 1)) {
                        delete[] wePlaced;
                        return true;
                    }
                    unplaceH(crossword, wePlaced, i, j, current.length());
                }

                if (canplaceV(crossword, current, i, j) == true) {

                    bool* wePlaced = placeV(crossword, current, i, j);
                    if (solveCrossword(crossword, words, index + 1)) {
                        delete[] wePlaced;
                        return true;
                    }
                    unplaceV(crossword, wePlaced, i, j, current.length());
                }
            }
        }

    }

    return false;
}

int main()
{
    cout << "running" << endl;

    vector<string> words = { "DELHI", "ICELAND", "ANKARA", "LONDON" };
    char crossword[10][10] = {
        {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
        {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
        {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
        {'+', '-', '-', '-', '-', '-', '+', '+', '+', '+'},
        {'+', '-', '+', '+', '+', '-', '+', '+', '+', '+'},
        {'+', '-', '+', '+', '+', '-', '+', '+', '+', '+'},
        {'+', '-', '+', '+', '+', '-', '+', '+', '+', '+'},
        {'+', '+', '-', '-', '-', '-', '-', '-', '+', '+'},
        {'+', '+', '+', '+', '+', '-', '+', '+', '+', '+'},
        {'+', '+', '+', '+', '+', '-', '+', '+', '+', '+'}
    };

    vector<string> words2 = { "PUNJAB","JHARKHAND","MIZORAM","MUMBAI" };
    char crossword2[10][10] = {

{'+' ,'-' ,'+', '+','+','+' ,'+' ,'+', '+','+'}, //1
{'+' ,'-' ,'+', '+','+','+' ,'+' ,'+', '+','+'}, //2
{'+' ,'-' ,'+', '+','+','+' ,'-' ,'+', '+','+'}, //3
{'+' ,'-' ,'-', '+','+','+' ,'-' ,'-', '+','+'}, //4
{'+' ,'-' ,'+', '+','+','+' ,'-' ,'+', '+','+'}, //5
{'+' ,'-' ,'+', '+','+','+' ,'-' ,'+', '+','+'}, //6
{'+' ,'-' ,'+', '+','+','+' ,'-' ,'+', '+','+'}, //7
{'+' ,'-' ,'+', '-','-','-' ,'-' ,'-', '-','+'}, //8
{'+' ,'-' ,'+', '+','+','+' ,'+' ,'+', '+','+'}, //9
{'+' ,'+' ,'+', '-','-','-' ,'-' ,'-', '-','-'}, //10

    };

    if (!solveCrossword(crossword, words, 0)) {
        cout << "No solution found." << endl;
    }

    cout << endl;

    if (!solveCrossword(crossword2, words2, 0)) {
        cout << "No solution found." << endl;
    }

    return 0;

}