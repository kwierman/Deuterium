#ifndef Deuterium_Directory_h_
#define Deuterium_Directory_h_


#include <string>
#include <vector>
#include <dirent.h>
#include <sstream>

#include "Deuterium/FileSystem/Path.hh"
#include "Deuterium/FileSystem/File.hh"
#include "Deuterium/FileSystem/FileUtilities.hh"

namespace Deuterium {

	namespace FileSystem {


		//! Implementation of directory methods
		class Directory : public Path {

			//! Holds content directory information
			std::vector<Directory> fDirEntries;

			//! Holds content file information
			std::vector<File> fFileEntries;


		public:
			//! Default directory constructor
			Directory();

			//! Construct directory with name
			//Directory(const std::string& dirName ) : Path(dirName) {}

			Directory(const Directory& other) : Path(other.GetName() ){}

			Directory(const Path& other) : Path(other) {}

			~Directory();

			//! Determines validity
			bool IsValid();
		    bool Read();
			unsigned GetNDirs();
			unsigned GetNFiles();
			File FileAt(unsigned i);
			Directory DirAt(unsigned i);
			//! Get back the absolute path
		};
	}
}


#endif //File Guardian