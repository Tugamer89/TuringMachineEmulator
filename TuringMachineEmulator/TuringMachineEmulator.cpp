#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;


enum Cell {
    BLANK = '_',
    LOW = '0',
    HIGH = '1'
};

enum Move {
    LEFT = -1,
    STAY,
    RIGHT
};

struct ProgramLine {
    char currentStatus;
    Cell currentValue;
    char newStatus;
    Cell newValue;
    Move move;

    bool isInit = false;
    long long int index = 0;
};

struct HalfProgramLine {
    char newStatus;
    Cell newValue;
    Move move;
    bool error = false;
};


class Memory {
private:
    vector<Cell> memory;

public:
    long long int index;

    Memory() {}

    void move(Move movement) {
        index += movement;

        if (index < 0) {
            memory.insert(memory.begin(), BLANK);
            index++;
        }
        else if (index >= memory.size())
            memory.push_back(BLANK);
    }

    void print() {
        for (int i = 0; i < memory.size(); i++) {
            if (i == index)
                cout << "[";
            cout << static_cast<char>(memory[i]);
            if (i == index)
                cout << "]";
        }
    }

    Cell readValue() {
        return memory[index];
    }

    void writeValue(Cell value) {
        memory[index] = value;
    }

    void loadFromFile(string filePath) {
        ifstream inFile(filePath);

        if (!inFile.is_open()) {
            cerr << "Impossible to open file " << filePath << endl;
            return;
        }

        char cellChar;
        while (inFile.get(cellChar)) {
            Cell cell = static_cast<Cell>(cellChar);
            memory.push_back(cell);
        }

        inFile.close();
    }

    void saveToFile(string filePath) {
        ofstream outFile(filePath);

        if (!outFile.is_open()) {
            cerr << "Impossible to open file " << filePath << endl;
            return;
        }

        for (Cell cell : memory)
            outFile << static_cast<char>(cell);

        outFile.close();
    }
};



class Program {
private:
    vector<ProgramLine> program;
    ProgramLine currentProgramLine;

public:
    Program() {}

    HalfProgramLine search(char status, Cell value) {
        for (ProgramLine prgLine : program)
            if (!prgLine.isInit && prgLine.currentStatus == status && prgLine.currentValue == value) {
                currentProgramLine = prgLine;
                return { prgLine.newStatus, prgLine.newValue, prgLine.move };
            }
        return { status, value, STAY, true };
    }

    ProgramLine initLine() {
        for (ProgramLine prgLine : program)
            if (prgLine.isInit)
                return prgLine;
        return program[0];
    }

    void print() {
        cout << currentProgramLine.currentStatus << " " <<
            static_cast<char>(currentProgramLine.currentValue) << " " <<
            currentProgramLine.newStatus << " "
            << static_cast<char>(currentProgramLine.newValue) << " "
            << currentProgramLine.move;
    }

    void loadFromFile(string filePath) {
        map<char, Move> moveMap;
        moveMap['>'] = RIGHT;
        moveMap['<'] = LEFT;
        moveMap['-'] = STAY;

        map<char, Cell> cellMap;
        cellMap['0'] = LOW;
        cellMap['1'] = HIGH;
        cellMap['_'] = BLANK;

        ifstream inFile(filePath);

        if (!inFile.is_open()) {
            cerr << "Impossible to open file " << filePath << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            if (line.empty() || line[0] == '#')
                continue;

            istringstream iss(line);
            string token;

            ProgramLine programLine;

            iss >> programLine.currentStatus >> token;
            programLine.currentValue = cellMap[token[0]];

            iss >> programLine.newStatus >> token;

            if (programLine.newStatus == '-') {
                programLine.isInit = true;
                programLine.index = stoll(token);
            }
            else {
                programLine.newValue = cellMap[token[0]];

                iss >> token;
                programLine.move = moveMap[token[0]];
            }

            program.push_back(programLine);
        }

        inFile.close();
    }
};



class Head {
private:
    Memory memory;
    Program program;

    char status;

public:
    Head() {}

    bool executeNext() {
        HalfProgramLine prgLine = program.search(status, memory.readValue());

#ifdef _DEBUG
        memory.print();
        cout << "  ->  ";
#endif

        status = prgLine.newStatus;
        memory.writeValue(prgLine.newValue);
        memory.move(prgLine.move);

#ifdef _DEBUG
        program.print();
        cout << "  ->  ";
        memory.print();
        cout << endl;
#endif

        return !prgLine.error;
    }

    void initialize(string programFilePath, string memoryFilePath) {
        program.loadFromFile(programFilePath);
        memory.loadFromFile(memoryFilePath);

        ProgramLine initLine = program.initLine();
        status = initLine.currentStatus;
        memory.index = initLine.index;
    }

    void save(string memoryFilePath) {
        memory.saveToFile(memoryFilePath);
    }
};



class TuringMachine {
private:
    string programFilePath;
    string memoryFilePath;
    Head head;

public:
    TuringMachine(string programFilePath, string memoryFilePath) : programFilePath(programFilePath), memoryFilePath(memoryFilePath) {}

    void execute() {
        head.initialize(programFilePath, memoryFilePath);
        while (true) {
            if (!head.executeNext())
                break;
        }
        head.save(memoryFilePath);
    }
};



int main(int argc, char** argv) {
    string prgPath, memPath;

    if (argc < 3) {
        cout << "Insert program path: ";
        cin >> prgPath;
        cout << "Insert memory path: ";
        cin >> memPath;
    }
    else {
        prgPath = argv[1];
        memPath = argv[2];
    }

    cout << endl;
    TuringMachine tMachine(prgPath, memPath);
    tMachine.execute();
    cout << "\nProgram ended!" << endl;

    return 0;
}
