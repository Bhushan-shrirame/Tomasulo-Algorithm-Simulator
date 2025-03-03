#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <limits>
#include "structure_class/instruction.h"
#include "structure_class/register_status.h"
#include "structure_class/reservation_station.h"
using namespace std;
const int AddOp = 0;
const int SubOp = 1;
const int MultOp = 2;
const int DivOp = 3;
const int LoadOp = 4;
const int LoopOp = 5;
const int EndLoopOp = 6;


void decoder(vector<Instruction>& instructions){
        int n = 6; 
    // std::cout  << "Enter number of instructions : "; 
    // cin >> n;
    for(int i=1;i<n+1;i++){
        std::fstream filename("input.txt");
        string Inst = "";
        int current_line = 0;
        while(!filename.eof()){
            current_line++;
            getline(filename,Inst);
            if(current_line == i ) break;
        }
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
}