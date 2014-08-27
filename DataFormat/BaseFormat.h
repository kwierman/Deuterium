#ifndef Deuterium_BaseFormat_h_
#define Deuterium_BaseFormat_h_

#include <vector>
#include <string>
#include <map>
#include <list>

namespace Deuterium{
	namespace DataFormat{


		//! Placeholder node type definition so that each node
		enum NodeType {
			stringtype,
			inttype,
			array_type,
			pair_type,
			list_type,
			dict_type
		};

		class DataNode;

		//! DataIterator points to a parent that is iterable
		class DataIterator{
			//! Point to parent node to iterate over
			DataNode* ptr;
		public:
			//! Copy from other iterator
			DataIterator(DataNode& other) : ptr(other.ptr) {}
			DataIterator(const DataIterator& other) : ptr(other.ptr) {}
			DataIterator& operator=(const DataIterator& other){
				this->ptr = other.ptr;
			}
			bool operator==(const DataIterator& other) const{
				//switch on child type and check over 
			}
			DataIterator& operator++(){

			}
			DataIterator& operator--(){
				
			}
			DataIterator& operator++(int index){

			}
			DataIterator& operator--(int index){
				
			}


		};

		class DataNode{
			NodeType fType;
			std::string fString;
			int fInt;
			std::vector<DataNode> fArray;
			std::list<DataNode> fList;
			DataNode* fPair;

		public:
			DataNode(const std:string& data) : fType(stringtype), fString(data), fPair(NULL), fInt(0){}

			NodeType GetNodeType(){return fType;}


		};


		class DataStructure{
			DataNode rootNode;
			DataIterator GetRootNodeIterator(){
				return DataIterator(rootNode);
			}
		};

	}
}
#endif //File Guardian
