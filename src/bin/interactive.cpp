#include "../include/interactive.hpp"

using namespace std;
enum cid{
	c_title,teacher,term,date,method,detail_method,overview,plan,text,advice,condition,standard
};
bool get_term(pair<int,int>&T){
	int i,j;
	cout<<"Grade Term"<<endl;
	cout<<"\t12 and 34 use instead of Semester"<<endl;
	cout<<"\tIf both input was 0, exit this program"<<endl;
	cin>>i>>j;
	T=make_pair(i,j);
	if(i<1||4<i||(j!=12&&j!=34&&4<j)||j<1){
		if(i!=0||j!=0)
			cout<<"Invalid input"<<endl;
		return true;
	}
	return false;
}
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
					for(;itr!=s.end();itr++){
						if(*itr==*fb.begin()){
							t=1;
							break;
						}
					}
				}else{
					for(;itr!=s.end();itr++){
						if(*itr==*(fb.begin()+1)){
							t=1;
							break;
						}
					}
				}
				if((g==T.first)&&(t==1)){
					vvs.push_back(clist[i]);
				}
			}
		}
	}
}
void print_vvs(vector<vector<string>>&vvs){
	for(size_t i=0;i<vvs.size();i++){
		cout<<i<<" ";
		cout<<vvs[i][cid::c_title]<<" ";
		cout<<vvs[i][cid::teacher]<<" ";
		cout<<vvs[i][cid::term]<<" ";
		cout<<vvs[i][cid::date]<<" ";
		if(vvs[i][cid::standard].size())
			cout<<vvs[i][cid::standard]<<" ";
		cout<<endl;
	}
}
int get_id(){
	cout<<"put in ID to see detail."<<endl;
	cout<<"\tIf input was negative or over size, skip details"<<endl;
	int i;
	cin>>i;
	return i;
}
void print_detail(vector<vector<string>>&vvs,int i){
	if(i<0||vvs.size()<=i){
		return;
	}
	for(auto itr=vvs[i].begin();itr!=vvs[i].end();itr++){
		cout<<*itr<<endl;
	}
}
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
