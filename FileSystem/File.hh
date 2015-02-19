#ifndef Deuterium_File_hh_
#define Deuterium_File_hh_

//#include "Deuterium/FileSystem/StreamPolicies.hh"
#include "Deuterium/FileSystem/Path.hh"

#include "Deuterium/FileSystem/FileType.hh"


namespace Deuterium{

	namespace FileSystem{


		//
		class File : public Path{
		public:
			File(const Path& name) : Path(name) {}

		};

		template<class FileType>
		class FilePrototype : public FileType, public File {
		protected:
			typedef typename FileType::stream_type stream;
			using FileType::fData;
		public:
			FilePrototype(const Path& path) : File(path) {}

			bool IsGood(){
				return fData.good();
			}

			bool eof(){
				return fData.eof();
			}

			bool Open(){
				fData.open( Path::GetName().c_str(), std::ifstream::binary );
				return fData.is_open();
			}
			bool IsOpen() const{
				return fData.is_open();
			}
			bool Close(){
				fData.close();
				return !(fData.is_open());
			}

			stream& GetInternal(){
				return fData;
			}

			/*
			std::filebuf* GetInternal(){
				return fData.rdbuf();
			}
			*/

			bool Fail(){
				return fData.fail();
			}

			bool Bad(){
				return fData.bad();
			}

			bool operator!(){
				return (!fData);
			}

			operator bool(){
				return bool(fData);
			}
			void ClearFlags(){
				fData.clear();
			}
			void Fill(const char& x){
				fData.fill(x);
			}
		};

		typedef FilePrototype<InputFileType> InputFile;
		typedef FilePrototype<OutputFileType> OutputFile;

	}
}


#endif //Deuterium_File_h_