#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// NUMBER OF RESERVATION STATIONS
const int Num_ADD_RS = 3;
const int Num_MULT_RS = 2;
const int Num_LOAD_RS = 3;

// Opcode value
const int AddOp = 0;
const int SubOp = 1;
const int MultOp = 2;
const int DivOp = 3;
const int LoadOp = 4;
const int LoopOp = 5;
const int EndLoopOp = 6;

// RESERVATION STATION LATENCY
const int ADD_Lat = 2;
const int MULT_Lat = 10;
const int Load_Lat = 2;
const int DIV_Lat = 40;

// Datapath Latency
const int ISSUE_Lat = 1;
const int WRITEBACK_Lat = 1;

// Global constants
int Clock = 0;
bool Done = true;
int Total_WRITEBACKS = 0;
int currentInst_ISSUE = 0;

// constant do not chane it it is there for bug fixex

const int operandInit = 1002;
const int RegStatusEmpty = 1000;
const int OperandAvailable = 1001;
const int OperandInit = 1002;

class ReservationStation {
    public:
        bool busy;
        int Qj;
        int Qk;
        int Vj;
        int Vk;
        int lat;
        int op;
        int result;
        bool resultReady;
        int instNum;
        int ISSUE_Lat;
        int WRITEBACK_Lat;

    public:
        ReservationStation();
        ReservationStation(int, int);
};
ReservationStation::ReservationStation() : busy(false), Qj(-1), Qk(-1), Vj(0), Vk(0), lat(0), op(-1), result(0), resultReady(false), instNum(-1), ISSUE_Lat(0), WRITEBACK_Lat(0) {}
ReservationStation::ReservationStation(int opcode, int operandInit) : busy(false), Qj(-1), Qk(-1), Vj(operandInit), Vk(operandInit), lat(0), op(opcode), result(0), resultReady(false), instNum(-1), ISSUE_Lat(0), WRITEBACK_Lat(0) {}

class RegisterStatus {
    public:
        bool busy;
        int Qi;
    public:
        RegisterStatus();
        RegisterStatus(int);
};
RegisterStatus::RegisterStatus() : busy(false), Qi(-1) {}
RegisterStatus::RegisterStatus(int q) : busy(true), Qi(q) {}


class Instruction {
public:
    int rd;
    int rs;
    int rt;
    int op;
    int issueClock;
    int executeClockBegin;
    int executeClockEnd;
    int writebackClock;
    int immediate;
public:
    Instruction();
    Instruction(int, int, int, int, int);
};

Instruction::Instruction() : rd(0), rs(0), rt(0), op(0), issueClock(0), executeClockBegin(0), executeClockEnd(0), writebackClock(0), immediate(0) {}
Instruction::Instruction(int rD, int rS, int rT, int opCode, int imm) : rd(rD), rs(rS), rt(rT), op(opCode), issueClock(0), executeClockBegin(0), executeClockEnd(0), writebackClock(0), immediate(imm) {}


// All function declaration 
void ISSUE(vector<Instruction>& instruction, vector<ReservationStation>& ResStation,vector<RegisterStatus>& RegisterStatus,vector<int>& Register );
void EXECUTE(vector<Instruction>& instruction, vector<ReservationStation>& ResStation,vector<RegisterStatus>& RegisterStatus,vector<int>& Register );
void WRITEBACK(vector<Instruction>& instruction, vector<ReservationStation>& ResStation,vector<RegisterStatus>& RegisterStatus,vector<int>& Register );
void repeatLoopInstructions(vector<Instruction>& instructions);

// Decoder functions
string Goto_Line_fetch(std::fstream& file, unsigned int num);

// Printer functions
void printRegisterStatus(vector<RegisterStatus> );
void printReservationStations(vector<ReservationStation> );
void printRegisters(vector<int> );
void printInstructions(vector<Instruction> );
void printTimingTable(vector<Instruction> );



int main() {
    
    //pdf instruction set
    // vector<Instruction> instructions = {
    //     Instruction(6,0,0, LoadOp, 34),
    //     Instruction(2,0,0, LoadOp, 45),
    //     Instruction(0, 2, 4, MultOp, 0),
    //     Instruction(8, 6, 2, SubOp, 0),
    //     Instruction(10, 0, 6, DivOp, 0),
    //     Instruction(6, 8, 2, AddOp, 0),
    // };

    // fibonaci insstruction set 
    // vector<Instruction> instructions = {
    //     // Instruction(1,0,0, LoadOp, 0),
    //     // Instruction(2,0,0, LoadOp, 0),
    //     // Instruction(3,0,0, LoadOp, 0),
    //     // Instruction(4,0,0, LoadOp, 1),
    //     Instruction(2, 0, 0, LoopOp,0),
    //     Instruction(5, 3, 4, AddOp, 0),
    //     Instruction(3, 1, 4, AddOp, 0),
    //     Instruction(4, 2, 5, AddOp, 0),
    //     Instruction(0, 0, 0, EndLoopOp,0)
    // };    
    // vector<Instruction> instructions = {
    //     // Instruction(1,0,0, LoadOp, 0),
    //     // Instruction(2,0,0, LoadOp, 0),
    //     // Instruction(3,0,0, LoadOp, 0),
    //     // Instruction(4,0,0, LoadOp, 1),
    //     Instruction(2, 0, 0, LoopOp,0),
    //     Instruction(1, 2, 3, AddOp, 0),
    //     Instruction(4, 5, 6, AddOp, 0),
    //     Instruction(7, 8, 9, AddOp, 0),
    //     Instruction(0, 0, 0, EndLoopOp,0)
    // };


    vector<Instruction> instructions;
    int n = 6;
    // std::cout  << "Enter number of instructions : "; 
    // cin >> n;
    for(int i=1;i<n+1;i++){
        std::fstream filename("input.txt");
        string Inst = Goto_Line_fetch(filename, i);
        string temp = "";
        vector<std::string> decode;
        for(int i=0;i<Inst.size();i++){
            if(Inst[i] == ':' || Inst[i] == ','|| Inst[i] == 'R'){
                if(temp == "") continue;
                decode.push_back(temp);
                temp.clear();
            }
            else{
                temp += Inst[i];
            }
        }
        decode.push_back(temp);
        for(auto i:decode){
            cout << i << " " ;
        }
        cout << endl;
        std::string operation = decode[0];
        if (operation == "FADD.D") {
            int r1 = std::stoi(decode[1]);
            int r2 = std::stoi(decode[2]);
            int r3 = std::stoi(decode[3]);
            instructions.push_back(Instruction(r1, r2, r3, AddOp, 0));
        }
        else if (operation == "FSUB.D") {
            int r1 = std::stoi(decode[1]);
            int r2 = std::stoi(decode[2]);
            int r3 = std::stoi(decode[3]);
            instructions.push_back(Instruction(r1, r2, r3, SubOp, 0));
        }
        else if (operation == "FDIV.D") {
            int r1 = std::stoi(decode[1]);
            int r2 = std::stoi(decode[2]);
            int r3 = std::stoi(decode[3]);
            instructions.push_back(Instruction(r1, r2, r3, DivOp, 0));
        }
        else if (operation == "FMUL.D") {
            int r1 = std::stoi(decode[1]);
            int r2 = std::stoi(decode[2]);
            int r3 = std::stoi(decode[3]);
            instructions.push_back(Instruction(r1, r2, r3, MultOp, 0));
        }
        else if (operation == "FLD") {
            int r1 = std::stoi(decode[1]);
            int r2 = std::stoi(decode[2]);
            instructions.push_back(Instruction(r1, 0, 0, LoadOp, r2));
        }
        else if (operation == "LOOP") {
            int r1 = std::stoi(decode[1]);
            instructions.push_back(Instruction(r1, 0, 0, LoopOp, 0));
        }
        else if (operation == "LOOPEND") {
            instructions.push_back(Instruction(0, 0, 0, EndLoopOp, 0));
        }
    }
    repeatLoopInstructions(instructions);

    // Output the modified instructions vector
    for (const auto& inst : instructions) {
        std::cout << "Instruction: " << inst.rd << " " << inst.rs << " " << inst.rt << " " << inst.op << " " << inst.immediate << endl;
    }

    // declaratio of all Resercation stataion
    vector<ReservationStation> ResStation = {
        ReservationStation(AddOp , operandInit),
        ReservationStation(AddOp , operandInit),
        ReservationStation(AddOp , operandInit),
        ReservationStation(MultOp , operandInit),
        ReservationStation(MultOp , operandInit),
        ReservationStation(LoadOp , operandInit),
        ReservationStation(LoadOp , operandInit),
        ReservationStation(LoadOp , operandInit),
    };

        RegisterStatus
            F0(RegStatusEmpty),F1(RegStatusEmpty),
            F2(RegStatusEmpty),F3(RegStatusEmpty),
            F4(RegStatusEmpty), F5(RegStatusEmpty),
            F6(RegStatusEmpty),F7(RegStatusEmpty),
            F8(RegStatusEmpty),F9(RegStatusEmpty),
            F10(RegStatusEmpty),F11(RegStatusEmpty),
            F12(RegStatusEmpty);

    vector<RegisterStatus> Registerstatus = {F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12};
    vector<int> Register = {5000,0,0,0,1,5,6,7,8,9,10,11,12};
    
    std::cout << "INITIAL VALUES:" << endl;
    printReservationStations(ResStation);
    printRegisters(Register);
    printRegisterStatus(Registerstatus);
    std::cout << endl;

    do{
        Clock++;
        // if(Clock == 59) break;
        ISSUE(instructions,ResStation,Registerstatus,Register);
        EXECUTE(instructions, ResStation, Registerstatus, Register);
        WRITEBACK(instructions,ResStation,Registerstatus,Register);
        
        // PRINT
        printRegisters(Register);
        printTimingTable(instructions);
        std::cout << endl;

        Done = false;
        if(Total_WRITEBACKS == instructions.size()) Done = true;

    }while(!Done);

    return 0;
}


void ISSUE(vector<Instruction>& instruction, vector<ReservationStation>& ResStation,vector<RegisterStatus>& RegisterStatus,vector<int>& Register ){
    int r = 0;
    bool rsFree = false;

    if(currentInst_ISSUE >= instruction.size()) return ;
    
    r = instruction[currentInst_ISSUE].op;

    int RSAddStart = 0;
    int RSAddEnd = Num_ADD_RS;
    int RSSubStart = 0;
    int RSSubEnd = Num_ADD_RS;
    int RSMulStart = Num_ADD_RS;
    int RSMulEnd = Num_ADD_RS + Num_MULT_RS;
    int RSLoadStart =  Num_ADD_RS+Num_MULT_RS;
    int RSLoadEnd = Num_LOAD_RS + Num_ADD_RS + Num_MULT_RS;

    switch (r){
        case AddOp:
            for(int i = RSAddStart;i <RSAddEnd;i++){
                if(!ResStation[i].busy){
                    r = i;
                    currentInst_ISSUE++;
                    ResStation[i].op = AddOp;
                    rsFree = true;
                    break;
                }
            }
            if(!rsFree) return;
            break;
        case SubOp:
            for(int i = RSAddStart;i <RSAddEnd;i++){
                if(!ResStation[i].busy){
                    r = i;
                    currentInst_ISSUE++;
                    ResStation[i].op = SubOp;
                    rsFree = true;
                    break;
                }
            }
            if(!rsFree) return;
            break;
        case MultOp:
            for(int i = RSMulStart;i <RSMulEnd;i++){
                if(!ResStation[i].busy){
                    r = i;
                    currentInst_ISSUE++;
                    ResStation[i].op = MultOp;
                    rsFree = true;
                    break;
                }
            }
            if(!rsFree) return;
            break;        
        case DivOp:
            for(int i = RSMulStart;i <RSMulEnd;i++){
                if(!ResStation[i].busy){
                    r = i;
                    currentInst_ISSUE++;
                    ResStation[i].op = DivOp;
                    rsFree = true;
                    break;
                }
            }
            if(!rsFree) return;
            break;
        case LoadOp:
            for(int i = RSLoadStart;i <RSLoadEnd;i++){
                if(!ResStation[i].busy){
                    r = i;
                    currentInst_ISSUE++;
                    ResStation[i].op = LoadOp;
                    rsFree = true;
                    break;
                }
            }
            if(!rsFree) return;
            break;
    default:
        break;
    }
    if (instruction[currentInst_ISSUE - 1 ].op == LoadOp && RegisterStatus[instruction[currentInst_ISSUE-1].rd].Qi == RegStatusEmpty) {
        ResStation[r].Vj = instruction[currentInst_ISSUE -1].immediate;
        ResStation[r].Qj = OperandAvailable;
    }
    else{
        if(RegisterStatus[instruction[currentInst_ISSUE-1].rs].Qi == RegStatusEmpty){
            ResStation[r].Vj = Register[instruction[currentInst_ISSUE-1].rs];
            ResStation[r].Qj = OperandAvailable;
        }
        else{
            ResStation[r].Qj = RegisterStatus[instruction[currentInst_ISSUE-1].rs].Qi;
        }
        if(RegisterStatus[instruction[currentInst_ISSUE-1].rt].Qi == RegStatusEmpty){
            ResStation[r].Vk = Register[instruction[currentInst_ISSUE-1].rt];
            ResStation[r].Qk = OperandAvailable;
        }
        else{
            ResStation[r].Qk = RegisterStatus[instruction[currentInst_ISSUE-1].rt].Qi;
        }
    }
    ResStation[r].busy = true;
    ResStation[r].ISSUE_Lat = 0;
    ResStation[r].instNum = currentInst_ISSUE -1;
    instruction[currentInst_ISSUE -1].issueClock  = Clock;
    RegisterStatus[instruction[currentInst_ISSUE -1 ].rd].Qi = r;
    return ;

}
void EXECUTE(vector<Instruction>& instruction, vector<ReservationStation>& ResStation,vector<RegisterStatus>& RegisterStatus,vector<int>& Register ){
    for(int r=0;r<ResStation.size();r++){
        if(ResStation[r].busy == true){
            if(ResStation[r].ISSUE_Lat >= ISSUE_Lat){
                if(ResStation[r].Qj == OperandAvailable && ResStation[r].op == LoadOp){
                    if(instruction[ResStation[r].instNum].executeClockBegin == 0){
                        instruction[ResStation[r].instNum].executeClockBegin = Clock;
                    }
                    ResStation[r].lat++;
                    if(ResStation[r].lat == Load_Lat){
                        ResStation[r].result = ResStation[r].Vj;
                        ResStation[r].resultReady = true;
                        ResStation[r].lat = 0;
                        instruction[ResStation[r].instNum].executeClockEnd = Clock;
                        ResStation[r].ISSUE_Lat = 0;
                    }

                }
                else if(ResStation[r].Qj == OperandAvailable && ResStation[r].Qk == OperandAvailable){
                    if(instruction[ResStation[r].instNum].executeClockBegin == 0){
                        instruction[ResStation[r].instNum].executeClockBegin = Clock;
                    }
                    ResStation[r].lat++;
                    switch (ResStation[r].op)
                    {
                    case(AddOp):
                        if(ResStation[r].lat == ADD_Lat){
                            ResStation[r].result = ResStation[r].Vj + ResStation[r].Vk;
                            ResStation[r].resultReady = true;
                            ResStation[r].lat = 0;
                            instruction[ResStation[r].instNum].executeClockEnd = Clock;
                            ResStation[r].ISSUE_Lat = 0;
                        }
                        break;
                    case(SubOp):
                        if(ResStation[r].lat == ADD_Lat){
                            ResStation[r].result = ResStation[r].Vj - ResStation[r].Vk;
                            ResStation[r].resultReady = true;
                            ResStation[r].lat = 0;
                            instruction[ResStation[r].instNum].executeClockEnd = Clock;
                            ResStation[r].ISSUE_Lat = 0;
                        }
                        break;
                    case(MultOp):
                        if(ResStation[r].lat == MULT_Lat){
                            ResStation[r].result = ResStation[r].Vj * ResStation[r].Vk;
                            ResStation[r].resultReady = true;
                            ResStation[r].lat = 0;
                            instruction[ResStation[r].instNum].executeClockEnd = Clock;
                            ResStation[r].ISSUE_Lat = 0;
                        }
                        break;
                    case(DivOp):
                        if(ResStation[r].lat == DIV_Lat ){
                            ResStation[r].result = ResStation[r].Vj / ResStation[r].Vk;
                            ResStation[r].resultReady = true;
                            ResStation[r].lat = 0;
                            instruction[ResStation[r].instNum].executeClockEnd = Clock;
                            ResStation[r].ISSUE_Lat = 0;
                        }
                        break;
                    default:
                        break;
                    }

                }

            }
            else ResStation[r].ISSUE_Lat++;

        }
    }

}
void WRITEBACK(vector<Instruction>& INST,vector<ReservationStation>& RESSTATION,vector<RegisterStatus>& REGSTATUS, vector<int>& REG){
    for(int r=0;r<RESSTATION.size();r++){
        if(RESSTATION[r].resultReady){
            if(RESSTATION[r].WRITEBACK_Lat == WRITEBACK_Lat){
                if(INST[RESSTATION[r].instNum].writebackClock == 0)
                    INST[RESSTATION[r].instNum].writebackClock = Clock;
                for(int x=0;x<REG.size();x++) {
                    if (REGSTATUS[x].Qi == r) {
                        REG[x] = RESSTATION[r].result;
                        REGSTATUS[x].Qi = RegStatusEmpty;
                    }
                }
                for(int y=0;y<RESSTATION.size();y++){
                    if(RESSTATION[y].Qj==r){
                        RESSTATION[y].Vj=RESSTATION[r].result;
                        RESSTATION[y].Qj=OperandAvailable;
                    }
                    if(RESSTATION[y].Qk==r){
                        RESSTATION[y].Vk=RESSTATION[r].result;
                        RESSTATION[y].Qk=OperandAvailable;
                    }
                }
                RESSTATION[r].resultReady = false;
                RESSTATION[r].busy = false;
                RESSTATION[r].Qj = OperandInit;
                RESSTATION[r].Qk = OperandInit;
                RESSTATION[r].Vj = 0;
                RESSTATION[r].Vk = 0;
                RESSTATION[r].WRITEBACK_Lat = 0;
                Total_WRITEBACKS++;
            }
            else
                RESSTATION[r].WRITEBACK_Lat++;
        }
    }

}

void repeatLoopInstructions(vector<Instruction>& instructions) {
    auto it = instructions.begin();
    while (it != instructions.end()) {
        auto loopStart = find_if(it, instructions.end(), [](const Instruction& inst) { return inst.op == LoopOp; });
        if (loopStart == instructions.end()) break;

        auto loopEnd = find_if(loopStart, instructions.end(), [](const Instruction& inst) { return inst.op == EndLoopOp; });
        if (loopEnd == instructions.end()) break;

        int n = loopStart->rd - 1; // Use rd for loop count
        vector<Instruction> temp(loopStart + 1, loopEnd);

        // Erase loop instructions first
        it = instructions.erase(loopEnd); // Remove EndLoopOp
        it = instructions.erase(loopStart); // Remove LoopOp

        // Insert repeated instructions
        it = instructions.insert(it, n * temp.size(), Instruction());
        auto insertPos = it;

        for (int i = 0; i < n; ++i) {
            insertPos = copy(temp.begin(), temp.end(), insertPos);
        }

        // Adjust iterator for next loop operation
        it += temp.size() * n;
    }
}


// Helper Functions
void printRegisterStatus(vector<RegisterStatus> RegisterStatusVector){
    std::cout << "Register Status: " << endl;
    for(int i=0; i<RegisterStatusVector.size(); i++)
         std::cout << RegisterStatusVector[i].Qi << ' ';
     std::cout << endl;
}
void printReservationStations(vector<ReservationStation> RSV){
    for(int i=0; i<RSV.size(); i++)
         std::cout << "RS #: " << i << "  Busy: " << RSV[i].busy << "  op: "<<
                RSV[i].op << "  Vj: " << RSV[i].Vj << "  Vk: " <<
                RSV[i].Vk << "  Qj: " << RSV[i].Qj << "  Qk: " <<
                RSV[i].Qk << endl;
}
void printRegisters(vector<int> RegistersVector){
    std::cout << "Register Content:" << endl;
    for(int i=0; i<RegistersVector.size(); i++)
         std::cout << RegistersVector[i] << ' ';
    std::cout << endl;
}
void printTimingTable(vector<Instruction> INST){
    char separator    = ' ';
    const int width     = 10;
    char lineSeperator = '-';
    const int lineWidth = 30;

    // Define column labels
    std::cout << left << setw(width) << setfill(separator) << "Inst";
    std::cout << left << setw(width) << setfill(separator) << "Issue";
    std::cout << left << setw(width) << setfill(separator) << "Execute";
    std::cout << left << setw(width) << setfill(separator) << "WB";
    std::cout << left << setw(width) << setfill(separator) << "SystemClock"
    << endl;
    std::cout << right << setw(width*5) << setfill(separator) << Clock;
    std::cout << endl;
    std::cout << left << setw(lineWidth) << setfill(lineSeperator);
    std::cout << endl;
    // Define Row Labels and values
    for(int i=0;i<INST.size();i++){
        std::cout << left  << setw(width) << setfill(separator) << i;
        std::cout << left << setw(width) << setfill(separator) << INST[i].issueClock;
        std::cout << INST[i].executeClockBegin <<  "-";
        std::cout << left << setw(width) << setfill(separator)  << INST[i].executeClockEnd;
        std::cout << left << setw(width) << setfill(separator) << INST[i].writebackClock;
        std::cout << endl;
    }

}

string Goto_Line_fetch(std::fstream& file, unsigned int num){
    int current_line = 0;
    std::string line= "";
    while(!file.eof()){
        current_line++;
        getline(file,line);
        if(current_line == num ) break;
    }
    return line;
}