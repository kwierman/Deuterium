#include "JSONFormat.h"

#include <sstream>

void Deuterium::DataFormat::JSONFormat::Read(const std::string& input){

}

std::string Deuterium::DataFormat::JSONFormat::Write(){
	std::stringstream output;

	for(DataIterator it = root.Begin(); it!=root.End(); ++it){
		output<<"{"<<std::endl;

		output<<"}"<<std::endl;
	}

	return output.str();
}

void Deuterium::DataFormat::JSONFormat::WriteNode(const unsigned& index, DataNode& node){

}
void Deuterium::DataFormat::JSONFormat::WriteStringNode(std::stringstream& output, DataNode& node){

}
void Deuterium::DataFormat::JSONFormat::WriteIntNode(std::stringstream& output, DataNode& node){

}
void Deuterium::DataFormat::JSONFormat::WriteArrayNode(std::stringstream& output, DataNode& node){

}
void Deuterium::DataFormat::JSONFormat::WriteListNode(std::stringstream& output, DataNode& node){

}
void Deuterium::DataFormat::JSONFormat::WritePairNode(std::stringstream& output, DataNode& node){

}
void Deuterium::DataFormat::JSONFormat::WriteDictNode(std::stringstream& output, DataNode& node){

}