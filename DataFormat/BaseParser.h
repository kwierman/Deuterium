#ifndef Deuterium_BaseParser_h_
#define Deuterium_BaseParser_h_

namespace Deuterium{
	namespace DataFormat{


		using Deuterium::File::File;

		//parsers are meant to read in files one character at a time, and 


		struct ParserObject{
		};

		struct DictonaryObject{

		};

		struct PairObject{

		};

		struct ArrayObject{

		};



		//! Base class for defining how to read in serialized data
		class BaseParser{
		private:
			std::string fFileName;
			std::iostream fFileStream;
		public:
			//! Constructor for parsing in data from a string
			BaseParser(std::string input);
			//! Constructor for parsing in data from a file
			BaseParser(File& input );

			char getNextChar();
			
			std::string GetNextNChars(int n);
		};


		class BaseNodalParser{

		};
	}
}


#endif //Deuterium_BaseParser_h_