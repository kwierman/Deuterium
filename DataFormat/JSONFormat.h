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

		private:
			void WriteNode(const unsigned& index, DataNode& node);
			void WriteStringNode(std::stringstream& output, DataNode& node);
			void WriteIntNode(std::stringstream& output, DataNode& node);
			void WriteArrayNode(std::stringstream& output, DataNode& node);
			void WriteListNode(std::stringstream& output, DataNode& node);
			void WritePairNode(std::stringstream& output, DataNode& node);
			void WriteDictNode(std::stringstream& output, DataNode& node);

		};

	}
}

#endif //FILE GUARDIAN