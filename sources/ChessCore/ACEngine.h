//
// Created by Cyril on 2023/11/28.
//
// Adapted from https://github.com/kimlongli/FiveChess/blob/master/FiveChess/ACSearcher.h
// License: https://github.com/kimlongli/FiveChess/blob/master/LICENSE.txt
//

#ifndef CPP_ACENGINE_H
#define CPP_ACENGINE_H


#include <string>
#include <vector>
#include <map>

using namespace std;

struct ACNode {
    ACNode(int p, char c)
            : ch(c),
              fail(-1),
              parent(p) {
    }

    char ch;
    map<char, int> sons;
    int fail;
    vector<int> output;
    int parent;
};

struct Pattern {
    const std::string word;
    int score;
};

class ACEngine {
public:
    ACEngine(std::initializer_list<Pattern> patterns);

    ~ACEngine();

    void BuildGotoTable();

    void BuildFailTable();

    int ACSearch(const string &text);

    void AddState(int parent, char ch);

private:
    int maxState;

    vector<ACNode> nodes;

    vector<string> patterns;

    vector<int> score;
};


#endif //CPP_ACENGINE_H
