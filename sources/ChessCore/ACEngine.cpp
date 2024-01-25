//
// Created by Cyril on 2023/11/28.
//
// Adapted from https://github.com/kimlongli/FiveChess/blob/master/FiveChess/ACSearcher.cpp
// License: https://github.com/kimlongli/FiveChess/blob/master/LICENSE.txt
//

#include "ACEngine.h"
#include <cassert>


ACEngine::ACEngine(std::initializer_list<Pattern> patterns) : maxState(0) {
    AddState(-1, 'a');
    nodes[0].fail = -1;
    vector<string> patternStrs;
    for (const auto &p: patterns) {
        patternStrs.push_back(p.word);
        score.push_back(p.score);
    }
    this->patterns = patternStrs;
    BuildGotoTable();
    BuildFailTable();
}

ACEngine::~ACEngine() = default;

void ACEngine::BuildGotoTable() {
    assert(!nodes.empty());
    for (auto i = 0; i < static_cast<int>(patterns.size()); i++) {
        int currentIndex = 0;
        for (char j: patterns[i]) {
            if (nodes[currentIndex].sons.find(j) == nodes[currentIndex].sons.end()) {
                nodes[currentIndex].sons[j] = ++maxState;
                AddState(currentIndex, j);
                currentIndex = maxState;
            } else {
                currentIndex = nodes[currentIndex].sons[j];
            }
        }
        nodes[currentIndex].output.push_back(i);
    }
}

void ACEngine::BuildFailTable() {
    assert(!nodes.empty());
    vector<int> midNodesIndex;
    ACNode root = nodes[0];
    map<char, int>::iterator iter1, iter2;
    for (iter1 = root.sons.begin(); iter1 != root.sons.end(); iter1++) {
        nodes[iter1->second].fail = 0;
        ACNode &currentNode = nodes[iter1->second];
        for (iter2 = currentNode.sons.begin(); iter2 != currentNode.sons.end(); iter2++) {
            midNodesIndex.push_back(iter2->second);
        }
    }
    while (!midNodesIndex.empty()) {
        vector<int> newMidNodesIndex;
        unsigned int i;
        for (i = 0; i < midNodesIndex.size(); i++) {
            ACNode &currentNode = nodes[midNodesIndex[i]];
            int currentFail = nodes[currentNode.parent].fail;
            while (true) {
                ACNode &currentFailNode = nodes[currentFail];
                if (currentFailNode.sons.find(currentNode.ch) != currentFailNode.sons.end()) {
                    currentNode.fail = currentFailNode.sons.find(currentNode.ch)->second;
                    if (!nodes[currentNode.fail].output.empty()) {
                        currentNode.output.insert(currentNode.output.end(), nodes[currentNode.fail].output.begin(),
                                                  nodes[currentNode.fail].output.end());
                    }
                    break;
                } else {
                    currentFail = currentFailNode.fail;
                }
                if (currentFail == -1) {
                    currentNode.fail = 0;
                    break;
                }
            }
            for (iter1 = currentNode.sons.begin(); iter1 != currentNode.sons.end(); iter1++) {
                newMidNodesIndex.push_back(iter1->second);
            }
        }
        midNodesIndex = newMidNodesIndex;
    }
}

int ACEngine::ACSearch(const string &text) {
    vector<int> result;
    int ret = 0;
    int currentIndex = 0;
    map<char, int>::iterator tmpIter;
    for (unsigned int i = 0; i < text.size();) {
        if ((tmpIter = nodes[currentIndex].sons.find(text[i])) != nodes[currentIndex].sons.end()) {
            currentIndex = tmpIter->second;
            i++;
        } else {
            while (nodes[currentIndex].fail != -1 &&
                   nodes[currentIndex].sons.find(text[i]) == nodes[currentIndex].sons.end()) {
                currentIndex = nodes[currentIndex].fail;
            }
            if (nodes[currentIndex].sons.find(text[i]) == nodes[currentIndex].sons.end()) {
                i++;
            }
        }
        if (!nodes[currentIndex].output.empty()) {
            result.insert(result.end(), nodes[currentIndex].output.begin(), nodes[currentIndex].output.end());
        }
    }
    for (auto i: result) {
        ret += score[i];
    }
    return ret;
}

void ACEngine::AddState(int parent, char ch) {
    nodes.emplace_back(parent, ch);
    assert(nodes.size() - 1 == static_cast<long long unsigned int>(maxState));
}
