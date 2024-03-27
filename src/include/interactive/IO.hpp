#ifndef I_IO_H
#define I_IO_H
#include "../baseinclude.hpp"
#include "enum.hpp"
bool get_term(std::pair<int,int>&);
int get_id();
void print_vvs(std::vector<std::vector<std::string>>&);
void print_detail(std::vector<std::vector<std::string>>&,int);
#endif