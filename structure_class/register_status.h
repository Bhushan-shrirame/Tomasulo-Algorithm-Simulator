#pragma once
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

