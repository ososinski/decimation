//
// Created by mro7 on 09/11/2015.
// This class is a knowledge base interface, an object that provides the memory capabilities for the decimation
// The interface defines the essential functionality
//

#ifndef DECIMATION_KNOWLEDGEBASE_H
#define DECIMATION_KNOWLEDGEBASE_H

#include <vector>
#include <bitset>
#include "TreeNode.h"

namespace PCDec{
    template <class HashType>
    class KnowledgeBase{
        public:
        //! The function that checks if the current position already exists
        /*!
          \param position The hash of the point's position.
          \return Returns 1(positive number) if it learned the new position, 0 if the position is already known
          or a negative number if an error occurred;
        */

            virtual int learn(HashType position);

    };

    //template <class NodeType>
    class BitTreeKnowledgeBase{

    public:
        BitTreeKnowledgeBase();
        ~BitTreeKnowledgeBase();
        int learn(std::vector<std::bitset<16> > position);

    private:
         BitTreeNode root;


    };

}

#endif //DECIMATION_KNOWLEDGEBASE_H
