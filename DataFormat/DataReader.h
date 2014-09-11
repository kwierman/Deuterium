#ifndef Deuterium_DataReader_h_
#define Deuterium_DataReader_h_

namespace Deuterium{
	namespace DataFormat{

		class XMLReader{

			//the document root
			DataDocument fRootData;
			//the root processor in the processor tree
			DataProcessor fRootProc;
			//the current processor in the tree
			DataProcessor* fCurrentProc;

			//Process the whole input
			void Process(const std::string&);
			//process an individual character
			void ProcessCharacter(const char&);
			//set the processor 
			void SetProcessor(DataProcessor*);
			
			
		};
	}
}

#endif //File guardian