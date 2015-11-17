//
// Created by mro7 on 12/11/2015.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "Decimate.h"
#include "KnowledgeBase.h"
#include "TreeNode.h"
#include "HashCode.h"

using namespace PCDec;
using namespace std;

    int main(int argc, char *argv[]) {
        BitHash<30> converter(0.1);
        BitTreeKnowledgeBase *kb = new BitTreeKnowledgeBase();
        std::vector<std::bitset<16> > hash;
        hash.clear();

        double x,y,z;

        ifstream file("E:\\denbigh_1cm.txt");
        ofstream output("E:\\bit_tree_denbigh_10cm.txt",std::ofstream::out);
        if(file.is_open())
        {
            string line;
            while(getline(file, line))   //while  we  are not  yet  to  the end  of the  file
            {
                std::istringstream input(line);
                input >> x >> y >> z;

                converter.convert(hash,x,y,z);

                if(kb->learn(&hash)) {
                    output << line << endl;
                }/*else{
                    cout << "already seen the likes of '" << line << "'" << endl;
                }*/

            }
            output.close();
            file.close();

        }
        else
            cout<<"File  not opened \n";

        /* // some test code
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
        std::cout << "learning " << kb->learn(hash) << "\n";*/
    }