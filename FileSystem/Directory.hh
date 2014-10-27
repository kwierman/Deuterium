#ifndef Deuterium_Directory_h_
#define Deuterium_Directory_h_


#include <string>
#include <vector>

#include "Deuterium/FileSystem/File.hh"


namespace Deuterium {

	namespace FileSystem {


		//! Implementation of directory methods
		class Directory{

			//! Data for holding directory information
			DIR* fDir;

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
			Directory() : fDir(NULL), fIsValid(false) {}

			//! Construct directory with name
			Directory(const std::string& dirName ) : fDir(NULL), fIsValid(false) {
				fDir = opendir(dirName.c_str() );
				fIsValid = (fDir);
				fDirName = dirName;
			}

			Directory(const Directory& other): fDir(NULL), fIsValid(false){
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
				struct dirent *directoryEntry;
		    	while(directoryEntry = readdir(fDir) ){
					std::string item = directoryEntry->d_name;

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
				//given the path, try and find it, and get back the absolute path
			}
		};
	}
}


#endif //File Guardian