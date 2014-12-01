#include "Deuterium/Options/Options.hh"


int main(int argc, char* argv[]){
	Deuterium::Options::OptionList opt(argc, argv);
	opt.setOption('l',"list","",false);

	opt.parse();
	opt.printUsage();


}