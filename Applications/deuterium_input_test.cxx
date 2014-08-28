
#include <iostream>

#include "Deuterium/DataFormat/BaseFormat.h"

int main(int argc, char* argv[]){

	//Ensure proper usage
	if(argc<2){
		std::cout<<"Usage: deuterium_input_test <filename>"<<std::endl;
		return -1;
	}

	Deuterium::DataFormat::DataNode data();


	std::cout<<sizeof(Deuterium::DataFormat::DataNode)<<std::endl;


	/*
	//Make sure the file exists
	Deuterium::FileSystem::File input(argv[1]);
	if(! input.IsValid() ){
		std::cout<<"Invalid filename"<<std::endl;
		return -1;
	}

	//Create 
	Deuterium::DataFormat::Parser<Deuterium::DataFormat::DOMParser> parser(input);
	parser.Read();

	if(!parser.IsGood() ){
		std::cout<<"Parser Encountered Error"<<std::endl;
		return -1;
	}

	Deuterium::DataFormat::Parser<Deuterium::DataFormat::DOMParser>::Iterator it=NULL;

	while(parser.HasNext() ){
		it = parser.GetNext();
		PrintDataNode(it);
	}
	*/
}