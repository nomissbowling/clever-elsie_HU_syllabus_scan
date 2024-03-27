#include "../../include/backend/text_processing.hpp"
using namespace std;
void getline(ifstream&ifs,string&text){
	string s;
	ifs >> s;
	while(*(s.begin())==' '){
		s.erase(s.begin());
	}
	regex_replace(text,regex("<(br|BR)>"),"");
	if (*(s.begin()) != '\n')
		text+=s+'\n';
	return;
}
void preproc_tags(string&text){
	format_tag(text);
	align_tag(text,0);
	align_tag(text,1);
	rm_tags(text);
}
void ext_tbl(string&text,ofstream&ofs,vector<vector<string>>&clist){
	vector<string>res(h1.size());
	for(size_t i=0;i<h1.size();i++){
		size_t pos=text.find(h1[i])+h1[i].size();
		for(size_t h=pos;h<text.size()-2;h++){
			if(text[h]=='<'){
				if(text[h+1]=='t'||text[h+1]=='T'){
					if(text[h+2]=='d'||text[h+2]=='D'){
						pos=h+3;
						break;
					}
				}
			}
		}
		for(size_t h=pos;h<text.size()-1;h++){
			if(text[h]=='>'){
				pos=h+1;
				break;
			}
		}
		string s;
		for(size_t h=pos;text[h]!='<';h++)
			s.push_back(text[h]);
		ofs<<"\""<<s<<"\""<<",\n"[i==h1.size()-1];
		res[i]=s;
	}
	clist.push_back(res);
}
