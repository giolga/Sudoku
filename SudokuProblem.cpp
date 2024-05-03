#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

const int STANDARD_SIZE = 9;
const int GIGANT_SIZE = 16;
const char VALUES[16] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};

void horizontal(vector<vector<char>>& sudokuTable, const int PUZZLE_SIZE) {
    //borders could be written without this loops AS WELL :)
    string horizont = (PUZZLE_SIZE == 16) ? "====" : "===";
    if(PUZZLE_SIZE == 16) {//nuthin special, for beauty
        for(int i = 0; i < PUZZLE_SIZE - 6; i++)
            cout << horizont;
        cout << "==" << endl;
    }
    else {
        for(int i = 0; i < PUZZLE_SIZE; i++)
            cout << horizont;
        cout << endl;
    }
}

void draw(vector<vector<char>>& sudokuTable, const int PUZZLE_SIZE) {

    const string sides = "||";
    int cntHorizontal = (PUZZLE_SIZE == 16) ? 3 : 2;
    int cntVertical = (PUZZLE_SIZE == 16) ? 3 : 2;
    const int grid = cntHorizontal;

    for(int i = 0; i < PUZZLE_SIZE; i++) {
        if(cntHorizontal == grid) {
            horizontal(sudokuTable, PUZZLE_SIZE);
            cntHorizontal = 0;
        } else {
            cntHorizontal++;
        }

        int cntVertical = grid;
        for(int j = 0; j < PUZZLE_SIZE; j++) {
            if(cntVertical == grid) {
                cout << sides;
                cntVertical = 0;
            } else cntVertical ++;

            cout << sudokuTable[i][j] << " ";

            if(j == 8 && grid == 2) cout << sides;
            if(j == 15 && grid == 3) cout << sides;
        }
        cout << endl;

        if(i == 8 && grid == 2) horizontal(sudokuTable, PUZZLE_SIZE);
        if(i == 15 && grid == 3) horizontal(sudokuTable, PUZZLE_SIZE);
    }
}


bool isValid(int rowz, int col, int val, vector<vector<char>>& sudokuTable, const int PUZZLE_SIZE) {
    // Checking val existence on a column/row
    for(int c =  0; c < PUZZLE_SIZE; c++)  
        if(sudokuTable[rowz][c] == val) return false;

    for(int r = 0; r < PUZZLE_SIZE; r++)  
        if(sudokuTable[r][col] == val) return false;

    int grid = 3;
    if(PUZZLE_SIZE == 16) grid = 4;

    int gridRow = floor(rowz /  grid) *  grid, gridCol = floor(col /  grid) *  grid;

    for(int r = gridRow; r < gridRow +  grid; r++) {
        for(int c = gridCol; c < gridCol +  grid; c++) {
            if(sudokuTable[r][c] == val) return false;
        }
    }

    return true;
}

bool startGame(int rowz, int col, vector<vector<char>>& sudokuTable,  const int PUZZLE_SIZE) {

    if(rowz == PUZZLE_SIZE - 1 && col == PUZZLE_SIZE) 
        return true;

    if(col == PUZZLE_SIZE) {
        col = 0;
        rowz++;
    }

    if(sudokuTable[rowz][col] > '0') return startGame(rowz, col + 1, sudokuTable, PUZZLE_SIZE);
    
    for(int i = 0; i < PUZZLE_SIZE; i++) {
        if(isValid(rowz,col, VALUES[i], sudokuTable, PUZZLE_SIZE)) {
            sudokuTable[rowz][col] = VALUES[i];
             if(startGame(rowz, col + 1, sudokuTable, PUZZLE_SIZE)) {
                return true;
             }
        }

        sudokuTable[rowz][col] = '0';
    }

    return false;
}

int getRandomNumber(int min, int max) {
    return rand() % (max - min) + min;
}

int getRandomNumber(const int PUZZLE_SIZE) {
    return (rand() % PUZZLE_SIZE);
}

void toChar(char *c, int digit ) {
    switch (digit) {
        case 10:
            *c = 'A';
            break;
        case 11:
            *c = 'B';
            break;
        case 12:
            *c = 'C';
            break;
        case 13:
            *c = 'D';
            break;
        case 14:
            *c = 'E';
            break;
        case 15:
            *c = 'F';
            break;
        case 16:
            *c = 'G';
            break;
        
        default:
            break;
    }
}

void generatePuzzle(int level, vector<vector<char>>& sudokuTable, const int  PUZZLE_SIZE) {
    int emptyCell = pow(PUZZLE_SIZE, 2) - level;
    cout << "Count empty cell " << emptyCell << endl; //Extra !!!

    while(emptyCell > 0) {
        int randomRow, randomColumn, digit;
        randomRow = getRandomNumber(PUZZLE_SIZE);
        randomColumn = getRandomNumber(PUZZLE_SIZE);
        digit = getRandomNumber(PUZZLE_SIZE) + 1;

        char c;
        if(digit < 10) c = char(digit + 48);
        else {
            toChar(&c, digit);
        }

        if(sudokuTable[randomRow][randomColumn] == '0') {
            bool valid = false;
            while(!valid) {
                if(sudokuTable[randomRow][randomColumn] != '0') {
                    sudokuTable[randomRow][randomColumn] = '0';
                    valid = true;

                    // cout << "Row " << randomRow << '\t' << randomColumn << '\t' << digit << endl;
                }

                randomRow = getRandomNumber(PUZZLE_SIZE);
                randomColumn = getRandomNumber(PUZZLE_SIZE);
                digit = getRandomNumber(PUZZLE_SIZE);
            }

        }
        else {
            sudokuTable[randomRow][randomColumn] = '0';
            //  cout << "Row " << randomRow << '\t' << randomColumn << '\t' << digit << endl;
        }
        emptyCell--;
    }

    draw(sudokuTable, PUZZLE_SIZE);

}

void generator(int difficulty, vector<vector<char>>& sudokuTable, const int  PUZZLE_SIZE) {
    int randomNumber = 0;

    switch (difficulty)
    {
        case 1:
            randomNumber = getRandomNumber(38, 50);
            break;
        case 2:
            randomNumber = getRandomNumber(30, 40);
            break;
        case 3:
            randomNumber = getRandomNumber(28, 35);
            break;
        case 4:
            randomNumber = 28;
            break;
        case 5:
            randomNumber = 17;
            break;
        default:
            randomNumber = getRandomNumber(130, 135);
            break;
    }

    cout << "Here is generated random number according to difficulty level:) " << randomNumber << "\n";
    int randomRow, randomColumn, digit;

    randomRow = getRandomNumber(PUZZLE_SIZE);
    randomColumn = getRandomNumber(PUZZLE_SIZE);
    digit = getRandomNumber(PUZZLE_SIZE);

    char c;
    if(digit < 10) c = char(digit + 48);
    else {
        toChar(&c, digit);
    }
    cout << "Generated random digit: " << digit << endl;
    cout << "character" << c << endl;

    sudokuTable[randomRow][randomColumn] = c;

    startGame(0, 0, sudokuTable, PUZZLE_SIZE);

    // for(int i = 0; i < *PUZZLE_SIZE; i++) {
    //     for(int j = 0; j < *PUZZLE_SIZE; j++) {
    //         cout << sudokuTable[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    generatePuzzle(randomNumber, sudokuTable, PUZZLE_SIZE);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "Choose difficulty level: \nEasy 1\nMedium 2\nHard 3\nExpert 4\nExtreme 5\nGiant 6\n";

    int difficulty;
    cin >> difficulty;

    int puzzleSize = (difficulty == 6) ? GIGANT_SIZE : STANDARD_SIZE;

    vector<vector<char>> sudokuTable(puzzleSize, vector<char>(puzzleSize, '0'));

    // for(int i = 0; i < puzzleSize; i++) {
    //     for(int j = 0; j < puzzleSize; j++)
    //         cout << sudokuTable[i][j] << " ";
    //     cout << endl;
    // }

    cout << "Solve sudoku pattern: y/n ";

    char action;
    cin >> action;

    if (action == 'y') {

        for (int i = 0; i < puzzleSize; i++) {
            char a;
            for (int j = 0; j < puzzleSize; j++) {
                cin >> a;
                sudokuTable[i][j] = a;
            }
        }

        if (startGame(0, 0, sudokuTable, puzzleSize)) draw(sudokuTable, puzzleSize);
        else {
            cout << "No such pattern can be solved \n";
        }
    }

    cout << "Generate sodoku pattern: y/n ";
    cin >> action;

    if(action == 'y') {
        generator(difficulty, sudokuTable, puzzleSize);

        cout << "Solve Sudoku: y/n ";
        cin >> action;

        if(action == 'y') {
            if(startGame(0, 0, sudokuTable, puzzleSize)) draw(sudokuTable, puzzleSize);
            else cout << "No such pattern can be solved \n";
        }
    }

    return 0;
}

/* 130-135
0 C 5 3 E 0 4 0 A 0 0 0 0 0 9 0
0 9 G E 6 3 0 C 5 D 2 0 7 0 4 A
A 0 0 2 G 9 F 8 0 0 4 E 0 1 5 0
0 0 6 D 5 0 1 0 F 0 0 0 0 C 2 E
0 0 C A 0 E 9 4 0 0 0 5 0 0 0 0
0 0 0 0 7 D C 0 0 E 0 8 4 3 0 5
G 3 0 0 8 0 0 0 9 0 0 F 0 0 0 0
D 1 0 8 0 0 0 0 2 0 6 0 9 7 0 0
3 0 0 0 C 8 5 0 0 9 0 0 0 0 F 7
8 2 F 7 B 0 E G 0 5 0 D 1 9 0 C
0 0 0 0 0 7 0 2 0 1 3 C A E 0 8
C E D 0 9 1 0 0 8 B 0 0 0 0 0 6
5 G 1 0 0 0 0 9 0 0 8 0 0 A 6 0
0 0 3 0 0 C 8 E 7 F 5 0 0 0 0 0
B 0 A C 0 F 0 5 D 6 1 9 0 0 0 2
0 0 0 9 2 G 6 1 0 A B 4 0 0 7 0
*/