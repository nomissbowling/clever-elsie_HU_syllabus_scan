#ifndef B_TEXT_PROCESSING_H
#define B_TEXT_PROCESSING_H
#include "txproc_mdl.hpp"
extern std::vector<std::string> h1;
void getln(std::ifstream&,std::string&);
void getln(std::string&,std::vector<std::string>&);
void preproc_tags(std::string&);
void ext_tbl(std::string&,std::ofstream&,std::vector<std::vector<std::string>>&);
#endif