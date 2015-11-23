//
// Created by mro7 on 09/11/2015.
//

#ifndef DECIMATION_TREENODE_H
#define DECIMATION_TREENODE_H
#include <vector>
#include <bitset>


namespace PCDec{
    const int CACHE_SIZE = 1; // 16 * 16 * 16 + 16 * 16 + 17
    const int LEAF_NUMBER = 16; // 16 * 16 * 16
    class BitTreeNode {

    public:
        BitTreeNode();
        ~BitTreeNode();

        int add(std::vector<std::bitset<16> >  *position);

    private:
        std::bitset<16> data[CACHE_SIZE]; //3^level tree node 16 * 16 * 16 + 16 * 16 + 17 and the root
        BitTreeNode *pointers[LEAF_NUMBER]; //16 * 16 * 16 = 4096
        //int exists(std::bitset<16> value, int index);
    };
}


#endif //DECIMATION_BITTREENODE_H
