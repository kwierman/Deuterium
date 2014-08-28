#include "Deuterium/DataFormat/XMLFormat.h"

#include <sstream>

#include "Deuterium/DataFormat/BaseFormat.h"


void Deuterium::DataFormat::XMLFormat::Read(const std::string& input){
;
}

std::string Deuterium::DataFormat::XMLFormat::Write(){
	std::stringstream output;

	output<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<std::endl;
	for(DataIterator it = root->Begin(); it!=root->End(); ++it){
		WriteNode(output, 0, (*it));
	}
	return output.str();
}

void Deuterium::DataFormat::XMLFormat::WriteNode( std::stringstream& output, const unsigned& index, DataNode& node){

	//Here's where the branching occurs.

	//if it is a pair, then it is a named node with content.

	for(unsigned i=0; i< index; i++ )output<<"\t";
	switch(node.GetNodeType()){


		case DataNode::string_type:
			WriteStringNode(output, index+1, node);
			break;
		case DataNode::int_type:
			WriteIntNode(output, index+1, node);
			break;
		case DataNode::pair_type:
			WritePairNode(output, index+1, node);
			break;
		case DataNode::array_type:
			WriteArrayNode(output, index+1, node);
			break;
		case DataNode::list_type:
			WriteListNode(output, index+1, node);
			break;
		case DataNode::dict_type:
			WriteDictNode(output, index+1, node);
			break;
		default:
			WriteStringNode(output, index+1, node);
	};
}
void Deuterium::DataFormat::XMLFormat::WriteStringNode(std::stringstream& output, const unsigned& index, DataNode& node){
	output<<"\""<<node.GetString()<<"\"";
}
void Deuterium::DataFormat::XMLFormat::WriteIntNode(std::stringstream& output, const unsigned& index, DataNode& node){
	output<<node.GetInt();
}
void Deuterium::DataFormat::XMLFormat::WriteArrayNode(std::stringstream& output, const unsigned& index, DataNode& node){
	output<<"["<<std::endl;
	
	for(DataIterator it = node.Begin(); it!=node.End(); ++it){
		WriteNode(output, index+1, (*it));
		output<<","<<std::endl;
	}
	output<<"]"<<std::endl;
}
void Deuterium::DataFormat::XMLFormat::WriteListNode(std::stringstream& output, const unsigned& index, DataNode& node){
	output<<"["<<std::endl;
	
	for(DataIterator it = node.Begin(); it!=node.End(); ++it){
		WriteNode(output, index+1, (*it));
		output<<","<<std::endl;
	}
	output<<"]"<<std::endl;
}
void Deuterium::DataFormat::XMLFormat::WritePairNode(std::stringstream& output, const unsigned& index, DataNode& node){
	//check to see what's inside, then see what gets printed
	output<<"<";
	WriteStringNode( output, 0, node);
	//check to see the type of the companion object
	switch( *(node.Begin()).GetNodeType() ){
		case DataNode::dict_type:
			output<<" ";
			WriteDictNode(output, 0, *(node.Begin()) );

		case DataNode::none_type:

		case DataNode::list_type:
		default:

	};

	WriteStringNode(output, index, node);
	output<<" : ";
	WriteNode(output, index,  *(node.Begin()) );
}
void Deuterium::DataFormat::XMLFormat::WriteDictNode(std::stringstream& output, const unsigned& index, DataNode& node){
	output<<"{"<<std::endl;
	
	for(DataIterator it = node.Begin(); it!=node.End(); ++it){
		WriteNode(output, index+1, (*it));
		output<<","<<std::endl;
	}
	output<<"}"<<std::endl;
}