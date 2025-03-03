#pragma once
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
