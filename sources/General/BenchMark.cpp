//
// Created by Cyril on 2023/12/8.
//

#include "BenchMark.h"

void Instrumentor::BeginSession(const string &filepath) {
    m_OutputStream.open(filepath);
    WriteHeader();
}

void Instrumentor::EndSession() {
    WriteFooter();
    m_OutputStream.close();
    m_Fir = true;
}

void Instrumentor::WriteProfile(const ProfileResult &result) {
    if (!m_Fir) { //not add ',' when first time
        m_OutputStream << ',';
    } else m_Fir = false;

    string name(result.Name);
    replace(name.begin(), name.end(), '"', '\'');
    m_OutputStream << R"({)";
    m_OutputStream << R"("cat":"function",)";
    m_OutputStream << R"("dur":)" << result.end - result.start << ",";
    m_OutputStream << R"("name":")" << name << "\",";
    m_OutputStream << R"("ph":"X",)";
    m_OutputStream << R"("pid":0,)";
    m_OutputStream << R"("tid":)" << result.TheadID << ",";
    m_OutputStream << R"("ts":)" << result.start;
    m_OutputStream << R"(})";
    m_OutputStream.flush();
}

void Instrumentor::WriteHeader() {
    m_OutputStream << R"({"otherData":{},"traceEvents":[)";
    m_OutputStream.flush();
}

void Instrumentor::WriteFooter() {
    m_OutputStream << "]}";
    m_OutputStream.flush();
}

Instrumentor &Instrumentor::Get() {
    static auto instance = new Instrumentor();
    return *instance;
}

InstrumentationTimer::InstrumentationTimer(const char *hint) : m_hint(hint) {
    start = chrono::steady_clock::now();
}

InstrumentationTimer::~InstrumentationTimer() {
    auto end = chrono::steady_clock::now();
    //cout << m_hint << ':' << static_cast<double>((end - start).count()) / 1e6 << "ms\n";
    long long llst = chrono::time_point_cast<chrono::microseconds>(start).time_since_epoch().count();
    long long lled = chrono::time_point_cast<chrono::microseconds>(end).time_since_epoch().count();

    uint32_t threadID = hash<std::thread::id>{}(std::this_thread::get_id());

    Instrumentor::Get().WriteProfile({m_hint, llst, lled, threadID});
}