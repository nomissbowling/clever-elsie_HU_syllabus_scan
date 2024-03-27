#include "../../include/interactive/IR.hpp"
using namespace std;
void vvs_term(vector<vector<string>>&clist,vector<vector<string>>&vvs,pair<int,int>&T){
	for(size_t i=0;i<clist.size();i++){
		if(clist[i][cid::term].size()){
			string s=clist[i][cid::term];
			if(T.second<10){
				int g=-1,t=-1;
				auto itr=s.begin();
				for(;itr!=s.end();itr++){
					if('0'<=*itr&&*itr<='9'){
						if(g==-1){
							g=*itr-'0';
						}else
							t=*itr-'0';
					}
					if(t>0)break;
				}
				if((g==T.first)&&(t==T.second)){
					vvs.push_back(clist[i]);
				}
			}else{
				int g=-1,t=0;
				string fb="前後";
				auto itr=s.begin();
				for(;itr!=s.end();itr++){
					if('0'<=*itr&&*itr<='9'){
						g=*itr-'0';
						break;
					}
				}
				if(T.second==12){
					t=(regex_search(s,regex("前期"))?1:0);
				}else{
					t=(regex_search(s,regex("後期"))?1:0);
				}
				if((g==T.first)&&(t==1)){
					vvs.push_back(clist[i]);
				}
			}
		}
	}
}