#pragma once
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