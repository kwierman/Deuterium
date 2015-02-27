#ifndef Deuterium_FileUtilities_h_
#define Deuterium_FileUtilities_h_

#include <string>
//#include <vector>

namespace Deuterium{

	namespace FileSystem{




		unsigned SwapWord(const unsigned& word);
		short SwapShort(const short& word);
		double SwapDouble(double word);

		template<typename SwapType>
		inline SwapType Swap2Bytes(const SwapType& word){
		    return (
		        ((word & 0xff00) >> 8) |
		        ((word & 0x00ff) << 8)
		    );
		}

		template<typename SwapType>
		inline SwapType Swap4Bytes(const SwapType& word){
		    return (
		        ((word & 0xff000000) >> 24) |
		        ((word & 0x00ff0000) >> 8) |
		        ((word & 0x0000ff00) << 8) |
		        ((word & 0x000000ff) << 24)
		    );
		}

		static const unsigned bitShortForm = 0x80000000;
		static const unsigned maskShortFormDataId = 0xfc000000;
		static const unsigned shiftShortFormDataId = 0;
		static const unsigned maskLongFormDataId = 0xfffc0000;
		static const unsigned shiftLongFormDataId = 0;
		static const unsigned maskShortFormData = 0x03ffffff;
		static const unsigned shiftShortFormData = 0;
		static const unsigned maskLongFormDataLength = 0x0003ffff;
		static const unsigned shiftLongFormDataLength = 0;


		std::string cwd();


	}
}



#endif //File Guardian
