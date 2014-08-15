#ifndef Deuterium_Directory_h_
#define Deuterium_Directory_h_

#include <dirent.h>
#include <string>
#include <vector>

#include "Deuterium/File/File.h"

namespace Deuterium{

	namespace File{

		class Directory{
			Dir* currentDir;
			struct dirent *currentEnt;
			bool exists;
			std::vector<Directory> owned_dirs;
			std::vector<File> owned_files;

		public: 
			Directory() : currentDir(NULL) , currentEnt(NULL), exists(FALSE) {}

			Directory(const std::string& directoryName) : Directory() {
				currentDir = opendir(directoryName.c_str());

				exists = (currentDir);

			}

			bool IsValid(){return exists;}

			~Directory(){
				if(currentDir)
					closedir(currentDir);

			}

		    bool Read(){
		    	while(currentEnt = readdir(currentDir) ){
					std::string item = currentEnt->d_name;

					//see if this is a directory
					Directory temp(item);
					if(temp.IsValid() )
						owned_dirs.push_back(temp);
					else:
						owned_files.push_back( File(item) ); 
		    	}
			}

			unsigned GetNDirs(){return owned_dirs.size(); }
			unsigned GetNFiles(){return owned_files.size(); }

			File FileAt(unsigned i){return owned_files[i];}
			File DirAt(unsigned i){return owned_dirs[i]; }

		};
	}
}


#endif //File Guardian