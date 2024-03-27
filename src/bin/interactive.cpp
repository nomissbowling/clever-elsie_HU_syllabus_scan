#include "../include/interactive.hpp"
using namespace std;
void interactive_mode(vector<vector<string>>&clist){
	do{
		pair<int,int>T;
		if(get_term(T)){
			if(T.first==0&&T.second==0){
				return;
			}else
				continue;
		}
		vector<vector<string>> vvs;
		vvs_term(clist,vvs,T);
		print_vvs(vvs);
		print_detail(vvs,get_id());
	}while(true);
}
