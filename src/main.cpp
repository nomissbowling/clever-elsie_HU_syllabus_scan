#include "include/backend.hpp"
#include "include/interactive.hpp"
using namespace std;
int main(int argc,char**argv) {
	vector<vector<string>>clist;
	backend(clist,argc);
	interactive_mode(clist);
}