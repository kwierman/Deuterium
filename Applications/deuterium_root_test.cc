#include "Deuterium/FileSystem/RootFile.hh"
using Deuterium::FileSystem::RootFile;

#include "Protium/Utilities/SignalCatching.hh"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]){

	Protium::Utilities::SignalCatcher::Instance().Setup();

	if(argc<2){
		std::cout<<"Specify a file"<<std::endl;
	}

	RootFile input(argv[1]);
	input.Open();
	std::cout<<"Reading Root File: "<<argv[1]<<std::endl;;
	input.Init();
	std::cout<<"pos"<<"\t"<<"nBytes"<<"\t"<<"version"<<"\t"<<"length"<<"\t"<<"datime"<<"\t"<<"keyLen"<<"\t"<<"cycle"<<"\t"<<"seekkey"<<"\t"<<"seekpdir"<<"\t"<<"name"<<"\t"<<"class_name"<<"\t"<<"title"<<std::endl;
	while(!input.eof() && input.IsOpen() )
		input.ReadRecord();
}