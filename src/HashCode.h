//
// Created by mro7 on 12/11/2015.
// The class contains the conversion between the position points to a hash
//

#ifndef DECIMATION_HASHCODE_H
#define DECIMATION_HASHCODE_H

#include <vector>
#include <bitset>
#include <cstdio>

namespace PCDec{

    //TODO: add an interface for hashes
    //class PositionHash



    //! The BitHash class converts XYZ position in double to a bitset vector
    // the default cube size is 10cm^3 ( assuming data in metres)
    // buffer determines the significand*3 for the position
    template <int BUFFER_SIZE>
    class BitHash{
        double cube_size;
    public:
        BitHash(double desired_cube_size=0.1){
            cube_size = desired_cube_size;
        }; //cube edge length relative to the original data
        int convert(std::vector<std::bitset<16> > &hash, double x, double y, double z){
            return static_convert(hash,x,y,z,cube_size,BUFFER_SIZE);
        }
        static int static_convert( std::vector<std::bitset<16> > &hash, double x, double y, double z, double ro, int buffer_size){
            char buffer[buffer_size];
            int no_error = 1;

            sprintf(buffer,"_%.0f_%.0f_%.0f|",x/ro,y/ro,z/ro);
            //std::cout << buffer << std::endl;
            int i = 0;
            for(char c = buffer[i];c!='|';c=buffer[++i]){ //each character
                switch (c) {
                    case '0' :
                        hash.push_back(std::bitset<16>(std::string("0000000000000001")));
                        break;
                    case '1' :
                        hash.push_back(std::bitset<16>(std::string("0000000000000010")));
                        break;
                    case '2' :
                        hash.push_back(std::bitset<16>(std::string("0000000000000100")));
                        break;
                    case '3' :
                        hash.push_back(std::bitset<16>(std::string("0000000000001000")));
                        break;
                    case '4' :
                        hash.push_back(std::bitset<16>(std::string("0000000000010000")));
                        break;
                    case '5' :
                        hash.push_back(std::bitset<16>(std::string("0000000000100000")));
                        break;
                    case '6' :
                        hash.push_back(std::bitset<16>(std::string("0000000001000000")));
                        break;
                    case '7' :
                        hash.push_back(std::bitset<16>(std::string("0000000010000000")));
                        break;
                    case '8' :
                        hash.push_back(std::bitset<16>(std::string("0000000100000000")));
                        break;
                    case '9' :
                        hash.push_back(std::bitset<16>(std::string("0000001000000000")));
                        break;
                    case '-' :
                        hash.push_back(std::bitset<16>(std::string("0000010000000000")));
                        break;
                    case '_' :
                        hash.push_back(std::bitset<16>(std::string("0000100000000000")));
                        break;
                    case 'e' :
                    case 'E' :
                        hash.push_back(std::bitset<16>(std::string("0001000000000000")));
                        break;
                    case '.' :
                        hash.push_back(std::bitset<16>(std::string("0010000000000000")));
                        break;
                    case ',' :
                        hash.push_back(std::bitset<16>(std::string("0100000000000000")));
                        break;
                    default:
                        hash.push_back(std::bitset<16>(std::string("1000000000000000")));
                        no_error = 0;

                } //end switch c

            }// end for each char


            return no_error;
        }



    };

}




#endif //DECIMATION_HASHCODE_H
