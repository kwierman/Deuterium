#include "Deuterium/FileSystem/Path.hh"
using Deuterium::FileSystem::Path;
#include "Deuterium/FileSystem/Directory.hh"
using Deuterium::FileSystem::Directory;
#include <iostream>

int main(int argc, char* argv[]){

	{
		Path here = Path::CWD();
		std::cout<<"Current Working Directory: "<<here.GetName()<<std::endl;
	}
	{
		Path here(".");
		std::cout<<"Current Working Directory: "<<here.GetName()<<std::endl;
		std::cout<<"Absolute Path: "<<here.GetAbsolutePath()<<std::endl;
		std::cout<<"Simplified Path: "<<here.simplifyPath()<<std::endl;
	}
	{
		Path here("..");
		std::cout<<"Parent Directory: "<<here.GetName()<<std::endl;
		std::cout<<"Absolute Path: "<<here.GetAbsolutePath()<<std::endl;
		std::cout<<"Simplified Path: "<<here.simplifyPath()<<std::endl;
	}
	{
		Directory here(".");
		here.Read();
		std::cout<<"Current Working Directory: "<<here.GetName()<<std::endl;
		std::cout<<"Absolute Path: "<<here.GetAbsolutePath()<<std::endl;
		std::cout<<"Simplified Path: "<<here.simplifyPath()<<std::endl;
		std::cout<<"Listing Directories..."<<std::endl;
		for(int i=0; i< here.GetNDirs();++i){
			std::cout<<"\t"<<here.DirAt(i).simplifyPath()<<std::endl;

		}
		std::cout<<"Listing Files..."<<std::endl;
		for(int i=0; i< here.GetNFiles();++i){
			std::cout<<"\t"<<here.FileAt(i).simplifyPath()<<std::endl;
		}
	}
}