#ifndef Deuterium_BaseFormat_h_
#define Deuterium_BaseFormat_h_

#include <vector>
#include <string>
#include <map>
#include <list>

#include "Protium/Allocation/SmallObject.h"

namespace Deuterium{
	namespace DataFormat{


		//! Placeholder node type definition so that each node can be concisely selected
		enum NodeType {
			string_type,
			int_type,
			array_type,
			pair_type,
			list_type,
			dict_type
		};

		class DataNode;

		typedef std::vector< DataNode, Protium::Allocation::STLAdapter< DataNode > > DataVector;

		typedef DataVector::iterator DataIterator;

		class DataNode : public ::Protium::Allocation::DefaultSmallObject {
			NodeType fType;
			std::string fString;
			int fInt;
			DataVector fArray;

		public:
			DataNode(const NodeType& type=list_type) : fType(type){}

			DataNode(const DataNode& other){
				fType = other.fType;
				fString = other.fString;
				fInt = other.fInt;
				fArray = other.fArray;
			}

			DataNode& operator=(const DataNode& other){
				fType = other.fType;
				fString = other.fString;
				fInt = other.fInt;
				fArray = other.fArray;
				return *this;
			}

			void SetInt(const int& x){fInt=x;}
			void SetString(const std::string& x){fString=x;}
			void Prepend( const DataNode& node){
				fArray.insert( fArray.begin(), node);
			}

			void Append(const DataNode& node){
				fArray.push_back(node);
			}

			void InsertBefore(const DataNode& node, const DataIterator& it){
				fArray.insert(it, node);
			}

			void InsertAfter(const DataNode& node, const DataIterator& it){
				DataIterator temp = it;
				fArray.insert(++temp, node);
			}

			DataIterator Begin(){
				return fArray.begin();
			}

			DataIterator End(){
				return fArray.end();
			}

			NodeType GetNodeType(){return fType;}

		};
	}
}
#endif //File Guardian
