//
// Created by mro7 on 12/11/2015.
//
#include <iostream>
#include <fstream>
#include <sstream>
//#include <rpcndr.h>
#include <stdlib.h>     /* atof */

#include "Decimate.h"
#include "KnowledgeBase.h"
#include "TreeNode.h"
#include "HashCode.h"

using namespace PCDec;
using namespace std;

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> SOURCE"
    << "Options:\n"
    << "\t-h,--help\t\tShow this help message\n"
    << "\t-o,--output OUTPUT\tSpecify the output file (default INPUT_dec_<CUBE_SIZE>.txt\n"
    << "\t-s,--cube_size SIZE\tSpecify the cube size, results in desired point density of 1 point per <SIZE>^3; default [0.1]\n"
    << "\t-v,--verbose\t The code will print a '.' every 10,000 points an 'o' every 1,000,000 points and an 'O' every 100,000,000 points"
    << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        show_usage(argv[0]);
        return 1;
    }
    std::string source = "none";
    std::string outfile = "none";
    int verbose = 0;
    double cube_size = 0.1;
    int error = 0;
    int counter = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        } else if ((arg == "-o") || (arg == "--output")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                outfile = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--output option requires one argument." << std::endl;
                return 1;
            }
        }else if ((arg == "-c") || (arg == "--cube_size")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                cube_size = atof(argv[++i]); // Increment 'i' so we don't get the argument as the next argv[i].
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--cube_size option requires one argument." << std::endl;
                return 1;
            }
        }else if ((arg == "-v") || (arg == "--verbose")) {
            verbose++;
        } else {
            source = argv[i];
        }
    }

    if(outfile == "none"){
        char buffer[source.length()+50]; // big enough... or at least should be
        sprintf(buffer, "%s_dec_%f.txt",source.data(),cube_size);
        outfile = buffer;
    }

    // Testing the command line options
    //cout << "o: " << outfile << " c: " <<cube_size << "s: "<< source << std::endl;
    //exit(0);

    BitHash<128> converter(cube_size);
    //BitTreeKnowledgeBase *kb = new BitTreeKnowledgeBase();
    VectorKnowledgeBase *kb = new VectorKnowledgeBase();
    std::vector<std::bitset<16> > hash;
    hash.clear();

    double x,y,z;

    ifstream file(source.data());
    ofstream output(outfile.data(),std::ofstream::out);
    if(file.is_open())
    {
        string line;
        while(getline(file, line))   //while  we  are not  yet  to  the end  of the  file
        {
            counter++;
            if(verbose!=0){ //print on verbose
                if(counter%100000000 == 0){
                    cout << "O";
                }else if(counter%1000000 == 0){
                    cout << "o";
                }else if(counter%10000 == 0){
                    cout << ".";
                }
            }

            std::istringstream input(line);
            input >> x >> y >> z;

            converter.convert(hash,x,y,z);

            if(error = kb->learn(&hash)) {
                if(error>0) {
                    output << line << endl;
                }else{
                    std::cerr << "Error assigning new memory; Only processed "<< counter << " lines; Exiting!";
                    break;

                }
            }
        }
        output.close();
        file.close();

    }
    else{
        cout<<"File  not opened \n";
    }

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