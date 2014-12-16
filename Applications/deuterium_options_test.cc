#include "Deuterium/Options/Options.hh"


int main(int argc, char* argv[]){
	Deuterium::Options::OptionList opt(argc, argv);
	opt.setOption('h',"help",0,false,"","Print this help statement");

	//opt.setOption('l',"list","default",true);
	//opt.setOption('q',"queue","default",false);
	//opt.setOption('w',"wierd","default",false);
	//opt.setOption('e',"existential","default",false);
	//opt.setOption('r',"whatever","default",false);
	//opt.setOption('t',"this_thing","default",false);
	//opt.setOption('y',"yup","default",false);
	opt.parse();
}