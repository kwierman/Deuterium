#ifndef Deuterium_SaxParser_h_
#define Deuterium_SaxParser_h_

namespace Deuterium{
	namespace DataFormat{





		struct XMLNode{
			std::string fName; //! name for the node
			std::vector<XMLAttribute> fAttributes;//
			std::vector<XMLNode> fChildren; //! All of the children objects
			std::vector<std::string> fData;//! 
		};

		class XMLAttribute{
			std::string fKey;
			std::string fValue;
		};


		class SAXParser{

			void Read(){
				//attempt to read in the 
				XMLDeclarationProcessor bom;
				bom.process(fFileIterator);
				while(fFileIterator.HasNext() ){
					XMLElement el;
					el.process(fFileIterator);
				}
				//Nothing to be done on the outside... hopefully
			}
		};

		class SaxWriter{
			void Write(XMLNode& starterNode){
				
			}
		};
	}
}


#endif //Deuterium_SaxParser_h_