#ifndef ORFile_h_
#define ORFile_h_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace OrcaRoot{
	class ORFile{
	public:
		ORFile(std::string& filepath);
		virtual ~ORFile();
		ORHeader* GetHeader(){return fHeader;}
		void Initialize();
		bool Read(void* buffer, size_t len);
		bool GetNextData(unsigned int& dataId, std::vector<unsigned int>& data);
	private:
		std::ifstream* fInput;
		std::string* fHeader;
		bool fIsBigEndian;
		unsigned int fCurrentWord;
	};
}

#endif //ORFile_h_
