#ifndef Deuterium_FileSystem_ORCAFile_hh_
#define Deuterium_FileSystem_ORCAFile_hh_

#include "Deuterium/FileSystem/File.hh"
#include "Deuterium/FileSystem/FileUtilities.hh"

#include <iostream>

namespace Deuterium{
	namespace FileSystem{

		class ORCAFile : public InputFile{
			std::string fHeader;
			bool fIsBigEndian;
		public:
			bool Read(void* buffer, size_t size ){
    			//if (! (fData && *fData))
        		//	return false;
    			if( eof() ) return false;

    			int remainingSize = size;
    			char* bufferPtr = reinterpret_cast<char*>(buffer);
    			while (remainingSize > 0) {
        			fData.read(bufferPtr, remainingSize);
        			int readSize = fData.gcount();
        			if (readSize > 0) {
            			bufferPtr += readSize;
            			remainingSize -= readSize;
        			}
        			if ((remainingSize > 0) && fData.eof()) {
            			fData.clear();
            			return false;
        			}
   				}
    			return (remainingSize == 0);
			}

			void Init(){
				unsigned int headerLen, headerSize;
				bool isBigEndian;
				isBigEndian = this->Read(&headerLen, sizeof(unsigned int) );
				isBigEndian = isBigEndian && this->Read(&headerSize, sizeof(unsigned int) );
				if(!isBigEndian){
					std::cout<<"Not an orca file, or trouble reading from file"<<std::endl;
					throw std::exception();
				}

				//Check for endianness
				if (headerLen & 0xffff0000) {
			        fIsBigEndian = true;
			        headerLen = SwapWord(headerLen);
			        headerSize = SwapWord(headerSize);
			    }
			    else
			        fIsBigEndian = false;

			    char* buffer = new char[headerLen*4];
			    this->Read(buffer, 4*(headerLen-2));
			    buffer[headerSize]='\0';

			    fHeader = buffer;

			    delete[] buffer;
			}

			bool GetNextData(unsigned int& dataId, std::vector<unsigned>& data){
				unsigned int fBuffer;
			    data.clear();

			    //process the first word
			    if(!(this->Read(&fBuffer, sizeof(unsigned int) )) ){
			        return false;
			    }
			    if(fIsBigEndian)
			        fBuffer = SwapWord(fBuffer);
			    if(fBuffer & bitShortForm) {
			        dataId = (fBuffer & maskShortFormDataId) >> shiftShortFormDataId;
			        data.push_back( (fBuffer & maskShortFormData) >> shiftShortFormData );
			    }
			    else {
			        dataId = (fBuffer & maskLongFormDataId) >> shiftLongFormDataId;
			        unsigned int length = (fBuffer & maskLongFormDataLength) >> shiftLongFormDataLength;
			        length -= 1;
			        data.resize(length);
			        for(std::vector<unsigned>::iterator it = data.begin(); it!=data.end(); ++it){
			            if(! this->Read(&fBuffer, sizeof(unsigned int))){
			                return false;
			            }            
			            if(fIsBigEndian) fBuffer = SwapWord(fBuffer);
			            (*it) = fBuffer;
			        }
			    }
			    return true;
			}
		public:
			ORCAFile(const Path& path) : InputFile(path) {}
			std::string GetHeader(){
				return fHeader;
			}
			

		};
	}

}


#endif //File Guardian