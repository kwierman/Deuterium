#ifndef Deuterium_Options_h_
#define Deuterium_Options_h_

namespace Deuterium{
	namespace Options{

/**
	To be used as follows:
	~~~~~~~~~~~~~~~~
	int main(int argc, char* argv[]){
		OptionList args(argc, argv);
		args.SetOption('h');
	}
	~~~~~~~~~~~~~~~~
**/

		struct Option{
			std::string long_opt;
			std::string value;
			bool required;
		};

		class OptionList{
			//! holds the raw data
			std::vector<std::string> raw;
			typedef std::vector<std::string>::iterator str_vec_it;
			//! holds the options
			std::map<char, Option> options;
			typedef std::map<char, Option>:iterator map_it;

			//! holds the program name
			std::string program_name;

		public:
			//! Construct the argument list from the program arguments
			OptionList(int argc, char* argv[]){
				program_name = argv[0];
				for(int i=1; i<argc, i++){
					raw.push_back(argv[i]);
				}
			}

			void setOption(const char& short_opt, 
				const std::string& long_opt, 
				const std::string& default_value, 
				const bool& required){

			}

			void parse(){
				//first, go through the map, and consume the raw tokens
				for(map_it it = options.begin(); it != options.end(); ++it){
					char req = (*it).first;

					//starting with the beginning of the list, look for option token


				}
			}

			void printUsage(){
				std::cout<<"Usage"


			}

		};
	}
}

#endif //File Guardian

