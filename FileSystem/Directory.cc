#include "Deuterium/FileSystem/Directory.hh"
#include "Deuterium/FileSystem/File.hh"

//! Default directory constructor
Deuterium::FileSystem::Directory::Directory() : Path( Path::CWD() ){}

//! Construct directory with name


Deuterium::FileSystem::Directory::~Directory(){}

//! Determines validity
bool Deuterium::FileSystem::Directory::IsValid(){
	DIR* dir=NULL;
	dir = opendir(GetName().c_str() );
	bool ret = (dir);				
	closedir(dir);
	return ret;
}

bool Deuterium::FileSystem::Directory::Read(){
	DIR* dir= opendir(GetName().c_str() );
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

unsigned Deuterium::FileSystem::Directory::GetNDirs(){return fDirEntries.size(); }
unsigned Deuterium::FileSystem::Directory::GetNFiles(){return fFileEntries.size(); }

Deuterium::FileSystem::File Deuterium::FileSystem::Directory::FileAt(unsigned i){return fFileEntries[i];}
Deuterium::FileSystem::Directory Deuterium::FileSystem::Directory::DirAt(unsigned i){return fDirEntries[i]; }
