#include "Deuterium/DataFormat/JSONFormat.h"
//#include "Deuterium/DataFormat/BaseFormat.h"


#include <sstream>

void Deuterium::DataFormat::JSONFormat::Read(const std::string& input){

}

std::string Deuterium::DataFormat::JSONFormat::Write(){
	std::stringstream output;
	output<<"{"<<std::endl;
	
	unsigned nnodes = root->GetNNodes();
	unsigned index = 0;
	for(DataIterator it = root->Begin(); it!=root->End(); ++it){
		WriteNode(output, 1, (*it));
		if(++index<nnodes)
			output<<","<<std::endl;
		else
			output<<std::endl;
	}
	output<<"}"<<std::endl;
	return output.str();
}

void Deuterium::DataFormat::JSONFormat::WriteNode( std::stringstream& output, const unsigned& index, DataNode& node){
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
void Deuterium::DataFormat::JSONFormat::WriteStringNode(std::stringstream& output, const unsigned& index, DataNode& node){
	output<<"\""<<node.GetString()<<"\"";
}
void Deuterium::DataFormat::JSONFormat::WriteIntNode(std::stringstream& output, const unsigned& index, DataNode& node){
	output<<node.GetInt();
}
void Deuterium::DataFormat::JSONFormat::WriteArrayNode(std::stringstream& output, const unsigned& index, DataNode& node){
	output<<"{"<<std::endl;
	
	for(DataIterator it = node.Begin(); it!=node.End(); ++it){
		WriteNode(output, index+1, (*it));
		output<<","<<std::endl;
	}
	output<<"}"<<std::endl;
}
void Deuterium::DataFormat::JSONFormat::WriteListNode(std::stringstream& output, const unsigned& index, DataNode& node){
	output<<"["<<std::endl;
	
	for(DataIterator it = node.Begin(); it!=node.End(); ++it){
		WriteNode(output, index+1, (*it));
		output<<","<<std::endl;
	}
	output<<"]"<<std::endl;
}
void Deuterium::DataFormat::JSONFormat::WritePairNode(std::stringstream& output, const unsigned& index, DataNode& node){
	WriteStringNode(output, index, node);
	output<<" : ";
	WriteNode(output, index,  *(node.Begin()) );
}
void Deuterium::DataFormat::JSONFormat::WriteDictNode(std::stringstream& output, const unsigned& index, DataNode& node){
	output<<"{"<<std::endl;
	
	for(DataIterator it = node.Begin(); it!=node.End(); ++it){
		WriteNode(output, index+1, (*it));
		output<<","<<std::endl;
	}
	output<<"}"<<std::endl;
}