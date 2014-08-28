#ifndef Deuterium_VirtualFormat_h_
#define Deuterium_VirtualFormat_h_

#include "Deuterium/DataFormat/BaseFormat.h"

namespace Deuterium{
	namespace DataFormat{


		class VirtualFormat{
		protected:
			DataNode* root;
		public:
			virtual void Read(const std::string& input)=0;
			virtual std::string Write()=0;
			void  SetNode(DataNode& node){root=&node;}
			VirtualFormat(){}
			virtual ~VirtualFormat(){}

		private:
			virtual void WriteNode(std::stringstream& output, const unsigned& index, DataNode& node)=0;
			virtual void WriteStringNode(std::stringstream& output, const unsigned& index, DataNode& node)=0;
			virtual void WriteIntNode(std::stringstream& output, const unsigned& index, DataNode& node)=0;
			virtual void WriteArrayNode(std::stringstream& output, const unsigned& index, DataNode& node)=0;
			virtual void WriteListNode(std::stringstream& output, const unsigned& index, DataNode& node)=0;
			virtual void WritePairNode(std::stringstream& output, const unsigned& index, DataNode& node)=0;
			virtual void WriteDictNode(std::stringstream& output, const unsigned& index, DataNode& node)=0;
		};
	}
}

#endif //File Guardian