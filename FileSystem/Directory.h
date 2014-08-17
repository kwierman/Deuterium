#ifndef Deuterium_Directory_h_
#define Deuterium_Directory_h_

#include <dirent.h>
#include <string>
#include <vector>

#include "Deuterium/FileSystem/File.h"
#include "Protium/Threads/ThreadingPolicy.h"
#include "Protium/Threads/Mutex.h"


namespace Deuterium{

	namespace FileSystem{


		//! Implementation of directory methods
		class Directory{

			//! Data for holding directory information
			DIR* fDir;

			//! Data for holding directory content information
			struct dirent *fDirectoryEntry;

			//! Invalidates directory if non existent
			bool fIsValid;

			//! Holds content directory information
			std::vector<Directory> fDirEntries;

			//! Holds content file information
			std::vector<File> fFileEntries;

			//! Directory Name
			std::string fDirName;

		public:
			//! Default directory constructor
			Directory() : fDir(NULL), fDirectoryEntry(NULL), fIsValid(false) {}

			//! Construct directory with name
			Directory(const std::string& dirName ) : fDir(NULL), fDirectoryEntry(NULL), fIsValid(false) {
				fDir = opendir(dirName.c_str() );
				fIsValid = (fDir);
				fDirName = dirName;
			}

			Directory(const Directory& other): fDir(NULL), fDirectoryEntry(NULL), fIsValid(false){
				fDirName = other.GetName();
				fDir = opendir( fDirName.c_str() );
				fIsValid = (fDir);
			}

			~Directory(){
				if(fDir) closedir(fDir);
			}

			std::string GetName() const{
				return fDirName;
			}

			//! Determines validity
			inline bool IsValid(){return fIsValid;}

		    bool Read(){
		    	while(fDirectoryEntry = readdir(fDir) ){
					std::string item = fDirectoryEntry->d_name;

					//see if this is a directory
					Directory temp(item);
					if(temp.IsValid() )
						fDirEntries.push_back(temp);
					else
						fFileEntries.push_back( File(item) ); 
		    	}
			}

			unsigned GetNDirs(){return fDirEntries.size(); }
			unsigned GetNFiles(){return fFileEntries.size(); }

			File FileAt(unsigned i){return fFileEntries[i];}
			Directory DirAt(unsigned i){return fDirEntries[i]; }

			//! Get back the absolute path
			std::string GetAbsolutePath(){


			}
		};
	}
}


#endif //File Guardian