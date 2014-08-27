#ifndef Deuterium_BaseFormat_h_
#define Deuterium_BaseFormat_h_

namespace Deuterium{
	namespace DataFormat{

		struct DataNode{
			std::string name;
			std::vector<DataNode> Children;
		};

		template<class TypeType>
		struct DataNodeImpl : public DataNode {
			TypeType data;
		};

		typedef DataNodeImpl<std::string>  StringNode ;//to be described as "key" : "value"
		typedef DataNodeImpl< std::map<std::string,DataNode> >  ArrayNode ;// to be described as



		class DataStructure{
			DataNode rootNode;
		};

		class DataIterator{
			DataNode* ptr;
			void Insert();
			void Remove();

		};

	}
}
#endif //File Guardian
