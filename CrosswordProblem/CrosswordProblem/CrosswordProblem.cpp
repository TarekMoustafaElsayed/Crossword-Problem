#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool canplaceH(char crossword[10][10] , string current ,int i , int j ) {

    int rows = sizeof(crossword)/sizeof(crossword[0]);
    int cols = sizeof(crossword[0])/sizeof(crossword[0][0]);
    int crosswordSizeRows = rows;

    if (j - 1 >= 0 && crossword[i][j - 1] != '+') return false;

    if (j + current.length() < crosswordSizeRows && crossword[i][j + current.length()] != '+') return false;

    for (int x = 0; x < current.length(); x++) {
        if (x + j >= crosswordSizeRows) return false;

        if (crossword[i][x + j] == '-' || crossword[i][x + j] == current.at(x)) {
            continue;
        }
        else {
            return false;
        }
    }

    return true;
}

bool canplaceV(char crossword[10][10], string current, int i, int j) {

    int crosswordSizeColumns = sizeof(crossword[0]) / sizeof(crossword[0][0]);

    if (i - 1 >= 0 && crossword[i - 1][j] != '+') return false;

    if (i + current.length() < crosswordSizeColumns && crossword[i + current.length()][j] != 'x') return false;

    for (int x = 0; x < current.length(); x++) {
        if (x + i >= crosswordSizeColumns) return false;

        if (crossword[i + x][j] == '-' || crossword[i + x][j] == current.at(x)) {
            continue;
        }
        else {
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
            crossword[i][j + k] = current.at(k);
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
            crossword[i+k][j] = current.at(k);
        }
        else { 
            res[k] = false; 
        }
    }

    return res;
}

void unplaceH(char crossword[10][10], bool arr[], int i, int j) {

    int arrSize = sizeof(arr) / sizeof(bool);

    for (int k = 0; k < arrSize; k++) {
        if (arr[k]) {
            crossword[i][j + k] = '-';
        }
    }
}

void unplaceV(char crossword[10][10], bool arr[], int i, int j) {

    int arrSize = sizeof(arr) / sizeof(arr[0]);

    for (int k = 0; k < arrSize; k++) {
        if (arr[k]) {
            crossword[i+k][j] = '-';
        }
    }
}

void solveCrossword(char crossword[10][10], vector<string> words, int index) {

    if (index == words.size()) {
        cout << crossword;
        return;
    }

    string current = words[index];
 int rows = sizeof(crossword)/sizeof(crossword[0]);
    int cols = sizeof(crossword[0])/sizeof(crossword[0][0]);
    int crosswordSizeRows = rows;

    int crosswordSizeColumns = cols;

    for (int i = 0; i < crosswordSizeRows ; i++) {

        for (int j = 0; j < crosswordSizeColumns; j++) {

            if (crossword[i][j] == '-' || crossword[i][j] == current.at(0)) {
                if (canplaceH(crossword, current, i, j) == true) {

                    bool* wePlaced = placeH(crossword, current, i, j);
                    solveCrossword(crossword, words, index + 1);
                    unplaceH(crossword, wePlaced, i, j);
                    delete[] wePlaced;
                }

                if (canplaceV(crossword, current, i, j) == true) {

                    bool* wePlaced = placeV(crossword, current, i, j);
                    solveCrossword(crossword, words, index + 1);
                    unplaceV(crossword, wePlaced, i, j);
                    delete[] wePlaced;
                }
            }
        }

    }
}

int main()
{
    cout<<"running";
    const auto size =10;
vector<string> words = {"DELHI","ICELAND","ANKARA","LONDON"};
char matrix1[size][size] = {

{'+' ,'-' ,'+', '+','+','+' ,'+' ,'+', '+','+'}, //1
{'+' ,'-' ,'+', '+','+','+' ,'+' ,'+', '+','+'}, //2
{'+' ,'-' ,'+', '+','+','+' ,'+' ,'+', '+','+'}, //3
{'+' ,'-' ,'-', '-','-','-' ,'+' ,'+', '+','+'}, //4
{'+' ,'-' ,'+', '+','+','-' ,'+' ,'+', '+','+'}, //5
{'+' ,'-' ,'+', '+','+','-' ,'+' ,'+', '+','+'}, //6
{'+' ,'-' ,'+', '+','+','-' ,'+' ,'+', '+','+'}, //7
{'+' ,'+' ,'-', '-','-','-' ,'-' ,'-', '+','+'}, //8
{'+' ,'-' ,'+', '+','+','-' ,'+' ,'+', '+','+'}, //9
{'+' ,'-' ,'+', '+','+','-' ,'+' ,'+', '+','+'}, //10

};


solveCrossword(matrix1,words,0);



// vector<vector<char>> matrix2 = {{},{},{},{},{},{},{},{},{},{}};

}