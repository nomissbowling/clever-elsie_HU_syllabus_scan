#include "../../include/interactive/IO.hpp"
using namespace std;
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
int get_id(){
	cout<<"put in ID to see detail."<<endl;
	cout<<"\tIf input was negative or over size, skip details"<<endl;
	int i;
	cin>>i;
	return i;
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
void print_detail(vector<vector<string>>&vvs,int i){
	if(i<0||vvs.size()<=i){
		return;
	}
	for(auto itr=vvs[i].begin();itr!=vvs[i].end();itr++){
		cout<<*itr<<endl;
	}
}