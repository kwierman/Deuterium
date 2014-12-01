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

		class OptionList{
			//! Minimum number of arguments required for program to function
			unsigned fMinArgument;

		public:
			//! Construct the argument list from the program arguments
			OptionList(int argc, char* argv[]){
				fArgv = argv;
				fArgc = argc;
			}
			OptionList& SetMinArgument(const unsigned& min){
				fMinArgument = min;
			}
			OptionList& SetOption(){
				return *this;
			}
			void Parse(){}

		};
	}
}

#endif //File Guardian

