#include "../../include/backend/text_processing.hpp"
using namespace std;
void getln(ifstream&ifs,string&text){
	string s;
	ifs >> s;
	while(*(s.begin())==' '){
		s.erase(s.begin());
	}
	text=regex_replace(text,regex("<(BR|br)>"),"");
	if (*(s.begin()) != '\n')
		text+=s+'\n';
	return;
}
void getln(string&s,vector<string>&vs){
	while(s.size()>0){
		if(*(s.begin())=='\n'){
			break;
		}
		auto itr=s.begin()+1;
		for(;itr!=s.end()-1;itr++){
			if(*itr=='\"'){
				if(*(itr+1)==','||*(itr+1)=='\n'){
					itr++;
					break;
				}
			}
		}
		string token(s.begin()+1,itr-1);
		s.erase(s.begin(),itr+1);
		vs.push_back(token);
	}
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
