#include "Deuterium/Options/Options.hh"


Deuterium::Options::OptionList::OptionList(int argc, char* argv[]){
	program_name = argv[0];
	for(int i=1; i<argc; i++){
		raw.push_back(argv[i]);
	}
	if(argc!= raw.size()+1){
		std::cout<<"WARNING: Arguments do not match raw data"<<std::endl;
		std::cout<<"\targc: "<<argc<<std::endl;
		std::cout<<"\traw: "<<raw.size()<<std::endl;
	}
	this->setOption('h',"help",0,false,"","Print this help statement");
}

void Deuterium::Options::OptionList::setOption(const char& short_opt,
	const std::string& long_opt,
	const unsigned& n_args=0,
	const bool& required=false,
	const std::string& default_value="",
	const std::string& help_statement=""){
	Option opt(long_opt, default_value, "", help_statement, n_args, required);
	options.insert(std::make_pair(short_opt, opt) );
}
