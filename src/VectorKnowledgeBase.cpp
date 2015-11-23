//
// Created by mro7 on 23/11/2015.
//

#include "KnowledgeBase.h"

namespace PCDec{


    //! Constructor, creates the root node of the tree
    VectorKnowledgeBase::VectorKnowledgeBase(){
    }
    //! Destroy the objects, the universe and everything
    VectorKnowledgeBase::~VectorKnowledgeBase(){
    }
    /*!
      \param position the bitset<16> vector representing the point's position.
      \return Returns 1(positive number) if it learned the new position, 0 if the position is already known
      or a negative number if an error occurred;
    */
    int VectorKnowledgeBase::learn(std::vector<std::bitset<16> > *position) {
        int result=-1;
        std::vector<bitset<16> >::iterator;
        it = find (known_positions.begin(), known_positions.end(), position);
        if (it != known_positions.end()) {
            result = 0;
        }else{
            std::vector<std::bitset<16> > * ptr = new (std::nothrow) std::vector<std::bitset<16> >(position);
            if(ptr != NULL){
                known_positions.push_back();
                result = 1;
            }else {
                result = -1;
            }
        }

        return result;

    }



}