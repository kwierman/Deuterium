#include "Deuterium/FileSystem/ORCAFile.hh"
using Deuterium::FileSystem::ORCAFile;

#include <iostream>
#include <vector>

int main(int argc, char* argv[]){

	if(argc<2){
		std::cout<<"Specify a file"<<std::endl;
	}

	ORCAFile input(argv[1]);
	input.Open();
	std::cout<<"Reading ORCA File: "<<argv[1];
	input.Init();
	std::cout<<input.GetHeader()<<std::endl;
	unsigned dataID;
	std::vector<unsigned> buffer;
	while(!input.eof()){
		if(!input.GetNextData(dataID, buffer) )
			break;
		std::cout<<"Record\tID:"<<dataID<<"\tLength:"<<buffer.size()<<std::endl;
		for(std::vector<unsigned>::iterator it = buffer.begin(); it!=buffer.end(); ++it){
			std::cout<<(*it)<<" ";
		}
		std::cout<<std::endl;
		if(!input.IsGood()) break;
		if(input.eof()) break;
	}
	std::cout<<"End of File"<<std::endl;
}