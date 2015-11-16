//
// Created by mro7 on 12/11/2015.
//
#include <iostream>
#include "Decimate.h"
#include "KnowledgeBase.h"
#include "TreeNode.h"
#include "HashCode.h"

using namespace PCDec;

    int main(int argc, char *argv[]) {
        BitHash<30> converter(1);
        BitTreeKnowledgeBase *kb = new BitTreeKnowledgeBase();
        std::vector<std::bitset<16> > hash;
        hash.clear();
        std::cout << "convertion "<< converter.convert(hash,1,1,1) << "\n";
        std::cout << "learning " << kb->learn(hash) << "\n";
        hash.clear();
        std::cout << "convertion "<< converter.convert(hash,1,1,2) << "\n";
        std::cout << "learning " << kb->learn(hash) << "\n";
        hash.clear();
        std::cout << "convertion "<< converter.convert(hash,1,2,1) << "\n";
        std::cout << "learning " << kb->learn(hash) << "\n";
        hash.clear();
        std::cout << "convertion "<< converter.convert(hash,1,1,1) << "\n";
        std::cout << "learning " << kb->learn(hash) << "\n";
        hash.clear();
        std::cout << "convertion "<< converter.convert(hash,1,1,2) << "\n";
        std::cout << "learning " << kb->learn(hash) << "\n";
    }