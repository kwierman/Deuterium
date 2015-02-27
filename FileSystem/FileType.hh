#ifndef Deuterium_FileSystem_FileType_hh_
#define Deuterium_FileSystem_FileType_hh_

#include <fstream>

namespace Deuterium{
	namespace FileSystem{

		struct UnknownFileType{
			typedef std::fstream stream_type;
			stream_type fData;
		};


		struct InputFileType{
			typedef std::ifstream stream_type;
			std::ifstream fData;

			stream_type& GetInternal(){
				return fData;
			}
			long Count(){
				return fData.gcount();
			}
			std::string GetChars(const unsigned& n){
				char str[n];
				fData.get(str,n);
				std::string output = str;
				return output;
			}
			std::string GetLine(const unsigned& maxChars, const char& delim){
				char str[maxChars];
				fData.getline(str,maxChars, delim);
				std::string output = str;
				return output;
			}

			void Ignore(const unsigned& n, const char& c){
				fData.ignore(n,c);
			}
			char peek(){
				return fData.peek();
			}
			
			template<typename T, int n>
			std::vector<T> Read(){
				T buffer[n];
				fData.read(buffer,n);
				std::vector<T> buffer2;
				return buffer2;
			}
			
			std::vector<char> ReadSome(const unsigned& s, int n){
				char buffer[n];
				fData.readsome(buffer, n);
				std::vector<char> buf;
				for(int i=0; i< n;i++)buf.push_back(buffer[i]);
				//delete[] buffer;
				return buf;
			}
			
			void Put(const char& c){
				fData.putback(c);
			}
			void UnGet(){
				fData.unget();
			}
			int StreamPos(){
				return fData.tellg();
			}
			void PutStreamPos(const unsigned& n ){
				fData.seekg(n);
			}
			void PutStreamPosFromBegin(const unsigned& n){
				fData.seekg(n, std::ios_base::beg);
			}
			void PutStreamPosFromEnd(const unsigned& n){
				fData.seekg(n, std::ios_base::end);
			}
			void PutStreamPosFromCurrentPosition(const unsigned& n){
				fData.seekg(n, std::ios_base::cur);
			}
		};

		struct OutputFileType{
			typedef std::ofstream stream_type;
			stream_type fData;

			stream_type& GetInternal(){
				return fData;
			}
			void putChar(const char& c){
				fData.put(c);
			}
			void Write(std::vector<char>& buff){
				fData.write(&buff[0], buff.size());
			}

			void Flush(){
				fData.flush();
			}
		};
	}
}


#endif //File Guardian