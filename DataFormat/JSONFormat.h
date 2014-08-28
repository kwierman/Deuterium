#ifndef Deuterium_JSONFormat_h_
#define Deuterium_JSONFormat_h_

#include "Deuterium/DataFormat/BaseFormat.h"

#include <string>
#include <sstream>

namespace Deuterium{
	namespace DataFormat{


		class JSONFormat {
			DataNode root;
		public:
			void Read(const std::string& input);
			std::string Write();
			void SetNode(DataNode& node){root=node;}

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