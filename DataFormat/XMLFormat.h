#ifndef Deuterium_XMLFormat_h_
#define Deuterium_XMLFormat_h_

#include <string>
#include <sstream>

#include "Deuterium/DataFormat/VirtualFormat.h"

namespace Deuterium{
	namespace DataFormat{

		class DataNode;

		class XMLFormat : public VirtualFormat{
		public:
			void Read(const std::string& input);
			std::string Write();
			XMLFormat(){}
			~XMLFormat(){};

		private:
			void WriteNode(std::stringstream& output, const unsigned& index, DataNode& node);
			void WriteStringNode(std::stringstream& output, const unsigned& index, DataNode& node);
			void WriteIntNode(std::stringstream& output, const unsigned& index, DataNode& node);
			void WriteArrayNode(std::stringstream& output, const unsigned& index, DataNode& node);
			void WriteListNode(std::stringstream& output, const unsigned& index, DataNode& node);
			void WritePairNode(std::stringstream& output, const unsigned& index, DataNode& node);
			void WriteDictNode(std::stringstream& output, const unsigned& index, DataNode& node);

		};

	}
}

#endif //FILE GUARDIAN