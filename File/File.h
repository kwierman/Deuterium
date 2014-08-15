#ifndef Deuterium_File_h_
#define Deuterium_File_h_

#include <ifstream>
#include <string>

namespace Deuterium{

	namespace File{

		class File{
			std::ifstream* fInput;
			unsigned currentWord;

		public:
			//! Constructor for standard file
			File(const std::string& filepath);
			//! Constructor for standard file
			File(const char* filepath);
			//! Constructor for finding a file with filename
			File(const std::string& path, const std::string& filename);
			//! Constructor for
			virtual ~File();
		
			bool Read(void* buffer, size_t len){
			    if (! (fInput && *fInput))
			        return false;
			    if(fInput->eof() ) return false;

			    int remainingSize = size;
			    char* bufferPtr = reinterpret_cast<char*>(buffer);
			    while (remainingSize > 0) {
			        fInput->read(bufferPtr, remainingSize);
			        int readSize = fInput->gcount();
			        if (readSize > 0) {
			            bufferPtr += readSize;
			            remainingSize -= readSize;
			        }
			        if ((remainingSize > 0) && fInput->eof()) {
			            fInput->clear();
			            return false;
			        }
			    }
			    return (remainingSize == 0);
			}
		};
	}
}


#endif //Deuterium_File_h_