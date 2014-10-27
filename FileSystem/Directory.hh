#ifndef Deuterium_Directory_h_
#define Deuterium_Directory_h_


#include <string>
#include <vector>
#include <dirent.h>
#include <sstream>

#include "Deuterium/FileSystem/File.hh"
#include "Deuterium/FileSystem/FileUtilities.hh"

namespace Deuterium {

	namespace FileSystem {


		//! Implementation of directory methods
		class Directory{

			//! Holds content directory information
			std::vector<Directory> fDirEntries;

			//! Holds content file information
			std::vector<File> fFileEntries;

			//! Directory Name
			std::string fDirName;

		public:
			//! Default directory constructor
			Directory(){
				fDirName = cwd();
			}

			//! Construct directory with name
			Directory(const std::string& dirName ){
				fDirName = dirName;
			}

			Directory(const Directory& other){
				fDirName = other.GetName();
			}

			~Directory(){}

			std::string GetName() const{
				return fDirName;
			}

			//! Determines validity
			inline bool IsValid(){
				DIR* dir=NULL;
				dir = opendir(fDirName.c_str() );
				bool ret = (dir);				
				closedir(dir);
				return ret;
			}

		    bool Read(){
   				DIR* dir= opendir(fDirName.c_str() );
   				if(!dir || fDirEntries.size() )
   					return false;
				struct dirent *directoryEntry;
		    	while(directoryEntry = readdir(dir) ){
					std::string item = directoryEntry->d_name;
					//see if this is a directory
					Directory temp( GetAbsolutePath()+"/"+ item);
					if(temp.IsValid() ){
						if(item!="." && item!=".." ){
							fDirEntries.push_back(temp);
						}
					}
					else
						fFileEntries.push_back( File( GetAbsolutePath()+"/"+ item) ); 
		    	}
		    	closedir(dir);
		    	return true;
			}

			unsigned GetNDirs(){return fDirEntries.size(); }
			unsigned GetNFiles(){return fFileEntries.size(); }

			File FileAt(unsigned i){return fFileEntries[i];}
			Directory DirAt(unsigned i){return fDirEntries[i]; }


			//! Get back the absolute path
			std::string GetAbsolutePath(){

				if(this->fDirName.at(0) == '/' ){
					return fDirName;
				}
				fDirName = cwd() +"/"+ fDirName;
				return simplifyPath();
			}

			std::string simplifyPath(){
				std::vector<std::string> path;
				std::stringstream input(fDirName);
				std::string segment;
				while(std::getline(input, segment, '/')){
					if(segment.size() || segment != std::string(" ") )
	   					path.push_back(segment);
				}

				typedef std::vector<std::string>::iterator tokit;
				std::string here = ".";
				std::string before = "..";

				for(tokit it = path.begin(); it!=path.end(); ++it){
					if( (*it) ==  here){
						path.erase(it);
						it = path.begin();
						}
					else if( (*it) == before ){
						tokit retstatement = it;
						tokit tobeerased = it;
						path.erase(--tobeerased);
						path.erase(retstatement);
						it = path.begin();
					}
				}
				fDirName="";
				std::stringstream outbuffer;
				for(tokit it = path.begin(); it!=path.end(); ++it)
					if( (*it).size()>0 )
						outbuffer<<"/"<< std::string(*it);
				outbuffer>>fDirName;
				return fDirName;
			}

		};
	}
}


#endif //File Guardian