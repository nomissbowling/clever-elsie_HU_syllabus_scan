#include "../../include/backend/txproc_mdl.hpp"
using namespace std;
void format_tag(string&text){
	int rank=0;
	for(size_t i=0;i<text.size();i++){
		if(text[i]=='<')
			rank++;
		else if(text[i]=='\n'&&rank>0)
			text[i]=' ';
		else if(text[i]=='>')
			rank--;
	}
	return;
}
void align_tag(string&text,int m){
	int r=0;
	vector<string>tag={"DH","dh"};
	for(size_t i=1;i<text.size()-1;i++){
		if(text[i]=='t'||text[i]=='T'){
			if(text[i+1]==tag[0][m]||text[i+1]==tag[1][m])
				r+=(text[i-1]!='/'?text[i-1]=='<'?1:0:-1);
		}else if(r>0&&text[i]=='\n')
				text[i]=' ';
	}
}
void rm_tags(string&text){
	vector<string>patt={
		"<[/]{0,1}(TR|tr|head|HEAD|html|HTML|table|TABLE|body|BODY)[^>]*>",
		"<META[^>]*>",
		"<title[^>]*>[^<]*</title>",
		"\n{2}","&nbsp;"};
	for(size_t i=0;i<patt.size();i++){
		text=regex_replace(text,regex(patt[i]),"");
	}
	vector<string>num={"０","１","２","３","４","５","６","７","８","９"};
	vector<string>n={"0","1","2","3","4","5","6","7","8","9"};
	for(size_t i=0;i<num.size();i++)
		text=regex_replace(text,regex(num[i]),n[i]);
}