//
// Created by mro7 on 09/11/2015.
//

#include <math.h>
#include <new>
#include "TreeNode.h"

namespace PCDec{
    //###################
    // BitTreeNode class
    //###################

        BitTreeNode::BitTreeNode(){
            for(int i=0; i<CACHE_SIZE;i++) {
                data[i].reset();
            }
            for(int i=0;i<LEAF_NUMBER;i++){
                BitTreeNode::pointers[i]= NULL;
            }

        }
        BitTreeNode::~BitTreeNode(){
            for(int i=0; i<LEAF_NUMBER;i++) {
                if(BitTreeNode::pointers[i]!= NULL) {
                    BitTreeNode::pointers[i]->~BitTreeNode();
                }
            }
        }
        //! The add function will check if the knowledge base already contains the item, add it otherwise
        //
        //  The check for branching is using a bitwise and to determine if the given path exists, see example 1
        //
        // Example 1:
        // stored data  0110 | 0101   note the stored data can have multiple paths active
        // current data 0010 | 0010   note the current data can only ever have one path active
        //
        // bitwise and  0010 | 0000   note only if the path was active the result is same as the current data
        //

        /*int BitTreeNode::add(std::vector<std::bitset<16> > * position){
            int result = -1; // set result to error
            int index = 0;
            std::bitset<16> current = position->back();
            position->pop_back();
            // ### level 0 ###
            if((current & BitTreeNode::data[index])==current){//check if the position has already been seen
                //### level 1 ###
                if(position->size()!=0){
                    index =1+log2(current.to_ulong()); //get the next index as log2 of the integer value of the bitset 1-16
                    current = position->back();
                    position->pop_back();
                    if((current & BitTreeNode::data[index])==current) {//check if the position has already been seen
                        //### level 2 ###
                        if (position->size() != 0) {
                            index = 1+16+(index-1)*16+log2(current.to_ulong()); //get the next index as log2 of the integer value of the bitset 1-16
                            current = position->back();
                            position->pop_back();
                            if((current & BitTreeNode::data[index])==current){//check if the position has already been seen
                                //### level 3 ###
                                if (position->size() != 0) {
                                    index = 1 + 16 + 256 + (index - 17) * 16 + log2(current.to_ulong());
                                    current = position->back();
                                    position->pop_back();
                                    if((current & BitTreeNode::data[index])==current){//check if the position has already been seen
                                        //### level 3 ###
                                        if (position->size() != 0) {
                                            long pt_index = (index - 273) * 16 + log2(current.to_ulong());
                                            if(pointers[pt_index]== NULL) {
                                                pointers[pt_index] = new BitTreeNode();
                                            }
                                            result = pointers[pt_index]->add(position);

                                        } else {
                                            result = 0;
                                        }
                                    }else {
                                        BitTreeNode::data[index] |= current; // set the correct path bit
                                        if (position->size() != 0) {
                                            long pt_index = (index - 273) * 16 + log2(current.to_ulong());
                                            pointers[pt_index] = new BitTreeNode();
                                            result = pointers[pt_index]->add(position);
                                        } else {
                                            result = 1;
                                        }
                                    }

                                }else {
                                    result = 0;
                                }
                            }else {
                                BitTreeNode::data[index] |= current; // set the correct path bit
                                //### level 3 ###
                                if(position->size()!=0) {
                                    index = 1 + 16 + 256 + (index - 17) * 16 + log2(current.to_ulong());
                                    std::bitset<16> current = position->back();
                                    position->pop_back();
                                    BitTreeNode::data[index] |= current; // set the correct path bit
                                    if (position->size() != 0) {
                                        long pt_index = (index - 273) * 16 + log2(current.to_ulong());
                                        pointers[pt_index] = new BitTreeNode();
                                        result = pointers[pt_index]->add(position);
                                    } else {
                                        result = 1;
                                    }
                                }else {
                                    result = 1;
                                }
                            }
                        }else {
                            result = 0;
                        }
                    }else{
                        BitTreeNode::data[index] |= current; // set the correct path bit
                        //### level 2 ###
                        if(position->size()!=0){
                            index = 1+16+(index-1)*16+log2(current.to_ulong()); //get the next index as log2 of the integer value of the bitset 17 is 16 +1
                            std::bitset<16> current = position->back();
                            position->pop_back();
                            BitTreeNode::data[index] |= current; // set the correct path bit
                            //### level 3 ###
                            if(position->size()!=0){
                                index = 1+16+256+(index-17)*16+log2(current.to_ulong());
                                std::bitset<16> current = position->back();
                                position->pop_back();
                                BitTreeNode::data[index] |= current; // set the correct path bit
                                if(position->size()!=0){
                                    long pt_index = (index-273)*16+log2(current.to_ulong());
                                    pointers[pt_index] = new BitTreeNode();
                                    result = pointers[pt_index]->add(position);
                                }else{
                                    result = 1;
                                }
                            }else{
                                result = 1;
                            }
                        }else{
                            result = 1;
                        }

                    }
                }else{
                    result = 0; // already seen the location
                }
            }else {//position has not been seen, it needs to be added
                BitTreeNode::data[index] |= current; // set the correct path bit
                //### level 1 ###
                if(position->size()!=0){
                    index =1+log2(current.to_ulong()); //get the next index as log2 of the integer value of the bitset
                    std::bitset<16> current = position->back();
                    position->pop_back();
                    BitTreeNode::data[index] |= current; // set the correct path bit
                    //### level 2 ###
                    if(position->size()!=0){
                        index = 1+16+(index-1)*16+log2(current.to_ulong()); //get the next index as log2 of the integer value of the bitset 17 is 16 +1
                        std::bitset<16> current = position->back();
                        position->pop_back();
                        BitTreeNode::data[index] |= current; // set the correct path bit
                        //### level 3 ###
                        if(position->size()!=0){
                            index = 1+16+256+(index-17)*16+log2(current.to_ulong());
                            std::bitset<16> current = position->back();
                            position->pop_back();
                            BitTreeNode::data[index] |= current; // set the correct path bit
                            if(position->size()!=0){
                                long pt_index = (index-273)*16+log2(current.to_ulong());
                                pointers[pt_index] = new BitTreeNode();
                                result = pointers[pt_index]->add(position);
                            }else{
                                result = 1;
                            }
                        }else{
                            result = 1;
                        }
                    }else{
                        result = 1;
                    }

                }else {
                    result = 1;
                }
            }




            return result;
        };*/
/*
    int BitTreeNode::add(std::vector<std::bitset<16> > * position){
        int result = -1; // set result to error
        int index = 0;
        std::bitset<16> current = position->back();
        position->pop_back();
        // ### level 0 ###
        if((current & BitTreeNode::data[index])==current){//check if the position has already been seen
            //### level 1 ###
            if(position->size()!=0){
                index =1+log2(current.to_ulong()); //get the next index as log2 of the integer value of the bitset 1-16
                current = position->back();
                position->pop_back();
                if((current & BitTreeNode::data[index])==current) {//check if the position has already been seen
                    //### level 2 ###
                    if (position->size() != 0) {
                        long pt_index = (index - 1) * 16 + log2(current.to_ulong());
                        if(pointers[pt_index]== NULL) {
                            pointers[pt_index] = new BitTreeNode();
                        }
                        result = pointers[pt_index]->add(position);
                    } else {
                        result = 0;
                    }
                }else {
                    BitTreeNode::data[index] |= current; // set the correct path bit
                    if (position->size() != 0) {
                        long pt_index = (index - 1) * 16 + log2(current.to_ulong());
                        pointers[pt_index] = new BitTreeNode();
                        result = pointers[pt_index]->add(position);
                    } else {
                        result = 1;
                    }
                }
            }else {
                result = 0;
            }


        }else {//position has not been seen, it needs to be added
            BitTreeNode::data[index] |= current; // set the correct path bit
            //### level 1 ###
            if(position->size()!=0) {
                index = 1 + log2(current.to_ulong()); //get the next index as log2 of the integer value of the bitset
                std::bitset<16> current = position->back();
                position->pop_back();
                BitTreeNode::data[index] |= current; // set the correct path bit
                //### level 2 ###
                 if (position->size() != 0) {
                     long pt_index = (index - 1) * 16 + log2(current.to_ulong());
                     pointers[pt_index] = new BitTreeNode();
                     result = pointers[pt_index]->add(position);
                 } else {
                     result = 1;
                 }

            } else {
                result = 1;
            }

            result = 1;
        }

        return result;
    };*/

    int BitTreeNode::add(std::vector<std::bitset<16> > * position){
        int result = -1; // set result to error
        int index = 0;
        std::bitset<16> current = position->back();
        position->pop_back();
        // ### level 0 ###
        if((current & BitTreeNode::data[index])==current){//check if the position has already been seen
            //### level 1 ###
                    if (position->size() != 0) {
                        long pt_index = log2(current.to_ulong());
                        if(pointers[pt_index]== NULL) {
                            pointers[pt_index] = new (std::nothrow) BitTreeNode();
                        }
                        if(pointers[pt_index] != NULL) { // error checking (only false if new failed)
                            result = pointers[pt_index]->add(position);
                        }else {
                            result = -1;
                        }
                    } else {
                        result = 0;
                    }
        }else {
            BitTreeNode::data[index] |= current; // set the correct path bit
            if (position->size() != 0) {
                long pt_index = log2(current.to_ulong());
                pointers[pt_index] = new (std::nothrow) BitTreeNode();
                if(pointers[pt_index] != NULL) { // error checking (only false if new failed)
                    result = pointers[pt_index]->add(position);
                }else {
                    result = -1;
                }
            } else {
                result = 1;
            }
        }


        return result;
    };

    };