#ifndef Deuterium_Options_h_
#define Deuterium_Options_h_

#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace Deuterium{
	namespace Options{

/**
	To be used as follows:
	~~~~~~~~~~~~~~~~
	int main(int argc, char* argv[]){
		Deuterium::Options::OptionList opt(argc, argv);
		opt.setOption('l',"list","",false);
		opt.parse();
		opt.printUsage();
	}
	~~~~~~~~~~~~~~~~
**/

		//!TODO: move this to the interior of the option list.
		struct Option{
			std::string long_opt;
			std::string value;
			bool required_met;
		};

		class OptionList{
			//! holds the raw data
			std::vector<std::string> raw;
			typedef std::vector<std::string>::iterator str_vec_it;
			//! holds the options
			std::map<char, Option> options;
			typedef std::map<char, Option>::iterator map_it;

			//! holds the program name
			std::string program_name;
			std::vector<std::string> additional_arguments;

		public:
			//! Construct the argument list from the program arguments
			OptionList(int argc, char* argv[]){
				program_name = argv[0];
				for(int i=1; i<argc; i++){
					raw.push_back(argv[i]);
				}
				if(argc!= raw.size()+1){
					std::cout<<"WARNING: Arguments do not match raw data"<<std::endl;
					std::cout<<"\targc: "<<argc<<std::endl;
					std::cout<<"\traw: "<<raw.size()<<std::endl;
				}
			}

			void setOption(const char& short_opt, 
				const std::string& long_opt, 
				const std::string& default_value="\t", 
				const bool& required=false){
				Option opt;
				opt.long_opt = long_opt;
				opt.value = default_value;
				opt.required_met = !required;

				options.insert(std::make_pair(short_opt, opt) );
			}

			void parse(){

				map_it indicator = options.end();

				for(str_vec_it it = raw.begin(); it!= raw.end(); ++it){
					if( (*it)[0]=='-' ){//Begins with option delimiter
						if( (*it).size()>1 ){//Safety check
							if( (*it)[1]=='-' ){//Begins with long option delimiter
								//Set the iterator
								std::string long_opt = (*it).substr(2);
								indicator = options.end();
								for(map_it it2 = options.begin(); it2!= options.end() ; ++it2){
									if( it2->second.long_opt == long_opt ){
										indicator = it2;
										it2->second.required_met = true;
										}
								}
								if(indicator == options.end()){
									std::cout<<"Error: Unknown long option found: "<<long_opt<<std::endl;
									printUsage();
								}
							}
							else{//Does not begin with long option delimiter
								//set the iterator
								char short_opt = (*it).substr(1)[0];
								indicator = options.find(short_opt);
								if(indicator == options.end()){
									std::cout<<"Error: Unknown short option found: "<<short_opt<<std::endl;
									printUsage();
								}	
								else{
									indicator->second.required_met = true;
								}
							}
						}
					}
					else{//does not begin with option delimiter
						indicator->second.value = (*it);
						indicator = options.end();
					}
				}

				//check the options to make sure they're in line
				for(map_it it  = options.begin(); it!= options.end(); ++it){
					if( !it->second.required_met ){
						std::cout<<"ERROR: Required option: "<<it->second.long_opt<<" Not Set"<<std::endl;
						printUsage();
					}
				}
			}

			void printUsage(){
				std::cout<<"Usage: "<<this->program_name<<" [[<-short_option <option_value> >] [<--long_option <option_value> >] [remaining parameters]]"<<std::endl;
				std::cout<<"Options:"<<std::endl;
				std::cout<<"Short Option\tLong Option\t Default Value\t Required"<<std::endl;
				for(map_it it = options.begin(); it!= options.end(); ++it){
					std::cout<<it->first<<"\t"<<
					it->second.long_opt<<"\t"<<
					it->second.value<<"\t"<<
					(!it->second.required_met) <<"\t"<<std::endl;
				}
			}

		};
	}
}

#endif //File Guardian

