#ifndef Deuterium_Options_h_
#define Deuterium_Options_h_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>

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
			//char short_opt; (already included in map)
			std::string long_opt;
			bool was_set;
			std::string default_value;
			std::string set_value;
			std::string help_statement;
			int n_args;
			bool required;

			Option(std::string lopt, std::string def, std::string set, std::string help, int n, bool req) :
			long_opt(lopt), default_value(def), set_value(set), help_statement(help), n_args(n), required(req), was_set(false) {}
		};

		class OptionList{

			//! holds the raw data
			std::vector<std::string> raw;
			typedef std::vector<std::string>::iterator str_vec_it;
			
			//! holds the options
			std::map<char, Option> options;
			typedef std::map<char, Option>::iterator map_it;

			//! The program name (for printing help statement)
			std::string program_name;
			//! Additional Arguements handed to the program
			std::vector<std::string> additional_arguments;

		public:
			//! Construct the argument list from the program arguments
			OptionList(int argc, char* argv[]);

			//! Set an option to be parsed
			//! \param short_opt ShortOptionValue a character representing a short option. i.e, 'v' for -v
			//! \param long_opt LongOptionValue a string representing a long option. i.e. "verbose" for --verbose
			//! \param n_args NumberofArguments Integer number of arguments to hand to option
			void setOption(const char& short_opt,
				const std::string& long_opt,
				const unsigned& n_args,
				const bool& required,
				const std::string& default_value,
				const std::string& help_statement);

			//! Parse the program input for options
			void parse(){
				//	The new version
				for(str_vec_it it = raw.begin(); it!= raw.end(); ++it){
					if( isOption( *it ) )
						ParseOption( it);
					else
						additional_arguments.push_back( (*it));
				}
				//check the list to see if anything is required, but now met
				for(map_it it = options.begin(); it!= options.end(); it++){
					if( it->second.required && !(it->second.was_set)){
						std::cout<<"Error Option required: "<<it->first<<std::endl;
						exit(-1);
					}
				}

			}

			void printUsage(){
				/*
				std::cout<<"Usage: "<<this->program_name<<" [[<-short_option <option_value> >] [<--long_option <option_value> >] [remaining parameters]]"<<std::endl;
				std::cout<<"Options:"<<std::endl;
				std::cout<<"Short Option\tLong Option\t Default Value\t Required"<<std::endl;
				for(map_it it = options.begin(); it!= options.end(); ++it){
					std::cout<<it->first<<"\t"<<
					it->second.long_opt<<"\t"<<
					it->second.set_value<<"\t"<<
					(!it->second.required_met) <<"\t"<<std::endl;
				}
				*/
			}
		private://Helper Functions
			//! Checks to see if this is an option
			bool isOption(const std::string& input){
				if(input.size()>1)
					return input[0]=='-';
				return false;
			}
			//! Checks to see if this is a long option
			bool isLongOption(const std::string& input){
				if(input.size()>2)
					return isOption(input) && input[1]=='-';
				return false;
			}
			//! Looks to see if this is an option
			void ParseOption(str_vec_it& it){
				//branch on long option or short option.
				if(isLongOption(*it ) ){
					std::string long_opt = (*it).substr(2);
					for(map_it mit = options.begin(); mit!= options.end() ; ++mit){
						if( mit->second.long_opt == long_opt ){
							mit->second.was_set = true;
							ConsumeArguements(mit, it);
							return;
						}
					}
					std::cout<<"Warning: Unknown long option found: "<<long_opt<<std::endl;
					printUsage();
				}
				else{
					std::string short_opt = (*it).substr(1);
					for(int i=0; i< short_opt.size(); i++){
						map_it mit = options.find( short_opt[i] );
						if(mit == options.end() ){
							std::cout<<"Warning: Unkown short option: "<<short_opt[i];
							continue;
						}
						if(mit->first == 'h'){
							printUsage();
							exit(0);
						}
						mit->second.was_set= true;
						if(i==short_opt.size()-1)
							ConsumeArguements(mit, it);
					}
				}

			}

			void ConsumeArguements(map_it& mit, str_vec_it& sit){
				for(int n_args_consumed=0;n_args_consumed < mit->second.n_args; ++n_args_consumed ){
					//consume the argument
					str_vec_it tit = sit;
					tit++;
					if(mit->second.set_value.size()>0)
						mit->second.set_value.append(" ");
					mit->second.set_value.append(*tit);
					this->raw.erase(tit);
				}
			}


		};
	}
}

#endif //File Guardian

