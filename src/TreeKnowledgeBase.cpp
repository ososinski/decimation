//
// Created by mro7 on 09/11/2015.
//

#include "KnowledgeBase.h"
#include "TreeNode.h"




namespace PCDec{


        //! Constructor, creates the root node of the tree
        BitTreeKnowledgeBase::BitTreeKnowledgeBase(){
        }
        //! Destroy the objects, the universe and everything
        BitTreeKnowledgeBase::~BitTreeKnowledgeBase(){
        }
        /*!
          \param position the bitset<16> vector representing the point's position.
          \return Returns 1(positive number) if it learned the new position, 0 if the position is already known
          or a negative number if an error occurred;
        */
        int BitTreeKnowledgeBase::learn(std::vector<std::bitset<16> > position){
            return BitTreeKnowledgeBase::root.add(position);

        }



}