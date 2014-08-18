#ifndef Deuterium_File_h_
#define Deuterium_File_h_

#include <fstream>
#include <string>

namespace Deuterium{

	namespace FileSystem{

		class File{
			std::string fName;

		public:
			File(const File& other) : fName(other.GetName()){}

			//! Constructor for standard file
			File(const std::string& filepath): fName(filepath){}
			//! Constructor for standard file
			File(const char* filepath) : fName(filepath){}
			//! Constructor for finding a file with filename
			File(const std::string& path, const std::string& filename): fName(filename){}
			//! Constructor for
			virtual ~File(){}

			std::string GetName()const {return fName;}
		};



		//template< template<class, class> class ThreadingPolicy = Protium::Threads::InstanceLocked>
		//class File


	}
}


#endif //Deuterium_File_h_