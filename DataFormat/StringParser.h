#ifndef Deuterium_StringParser_h_
#define Deuterium_StringParser_h_

#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h> 

#include <iostream>

namespace Deuterium{

	namespace DataFormat{

		template<typename T>
		class StringParser{
			std::string fData;
			std::vector<std::string> fTokens;
			std::vector<T> fDataAsVector;

		public:
			StringParser(const std::string& input) : fData(input) {} 
			
			StringParser& delimit(char delim){
				//split on 
				std::stringstream ss(fData);
    			std::string item;
    			while (std::getline(ss, item, delim)) {
        			fTokens.push_back(item);
    			}
				return *this;
			}

			StringParser& makerange(char delim){

				for(std::vector<std::string>::iterator it = fTokens.begin(); it!=fTokens.end(); ++it){
					std::size_t found = it->find(delim);
					if(found!=std::string::npos){
						std::cout<<"Found delimiter in :"<<(*it)<<std::endl;
						std::string first = it->substr(0,found);
						std::string second = it->substr(found+1, std::string::npos);
						//(*it) = first;
						unsigned firstInt = atoi(first.c_str() );
						unsigned secondInt = atoi(second.c_str() );
						while(firstInt<=secondInt)fDataAsVector.push_back(firstInt++);
					}
					else{
						fDataAsVector.push_back(atoi((*it).c_str() ));

					}

				}
				return *this;
			}

			std::vector<T> AsVector(){
				//fDataAsVector.clear();


				return fDataAsVector;
			}
		};
	}
}



#endif //File Guardian