//
// Created by mro7 on 12/11/2015.
//
#include <iostream>
#include <fstream>
#include <sstream>
//#include <rpcndr.h>
#include <stdlib.h>     /* atof */
#include <map>
#include <array>



#include "Decimate.h"

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

    std::map<std::array<char,14>,bool> kb;  
    double x,y,z;

    ifstream file(source.data());
    ofstream output(outfile.data(),std::ofstream::out);
    if(file.is_open())
    {
        string line;
        std::istringstream input("");
        std::array<char,14> hash;
        hash.fill('_');

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

            input.str(line);
            input >> x >> y >> z;



	//hash
            hash[0]= static_cast<int32_t>(x/cube_size);
            hash[5]= static_cast<int32_t>(y/cube_size);
            hash[10]= static_cast<int32_t>(z/cube_size);
        //


            if(verbose){
               for(int i =0;i++;i<14){
               cout<<hash[i];
               }
               cout<<endl;
            }

            if(kb.insert(std::map<array<char,14>,bool>::value_type(hash,true)).second){ //emplace in c++11 is insert with implicit data_type container creation
               output << line << endl;
            }
        }
        output.close();
        file.close();

    }
    else{
        cout<<"File  not opened \n";
    }

}
