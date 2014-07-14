#include "Deuterium/DataFormat/BaseParser.h"


char Deuteruim::DataFormat::BaseParser::getNextChar(){
	char temp;
	fInputFile.read(&temp, sizeof(temp) );
	return temp;
}

std::string Deuteruim::DataFormat::BaseParser::getNextNChars(int n){
	std::string temp;
	fInputFile.read( &temp, sizeof(char)*n );
	return temp;
}