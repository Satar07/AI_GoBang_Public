//
// Created by Cyril on 2023/12/8.
//

#ifndef AI_BACKGAMMON_BENCHMARK_H
#define AI_BACKGAMMON_BENCHMARK_H

#define PROFILING 0
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer tt##__LINE__(name)
#define PROFILE_FUNCTION PROFILE_SCOPE(__PRETTY_FUNCTION__);
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION
#endif

#include <sstream>
#include <cstdint>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

struct ProfileResult {
    string Name;
    long long start, end;
    uint32_t TheadID;
};

class Instrumentor {
private:
    ofstream m_OutputStream;
    bool m_Fir;

public:
    Instrumentor() : m_Fir(true) {}

    void BeginSession(const string &filepath = "results.json");

    void EndSession();

    void WriteProfile(const ProfileResult &result);

    void WriteHeader();

    void WriteFooter();

    static Instrumentor &Get();
};


class InstrumentationTimer {
private:
    chrono::time_point<chrono::steady_clock> start;
    const char *m_hint;

public:
    explicit InstrumentationTimer(const char *hint);

    ~InstrumentationTimer();
};


#endif //AI_BACKGAMMON_BENCHMARK_H
