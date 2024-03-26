#include"../include/backend.hpp"
using namespace std;
vector<string> h1 = {"授業科目名","担当教員名","開設期","曜日・時限・講義室","授業の方法","授業の方法 【詳細情報】","授業の目標・概要等","授業計画","教科書・参考書等","予習・復習への アドバイス","履修上の注意 受講条件等","成績評価の基準等"};
void excludeString(string& input, const string& target) {
	size_t pos = 0;
	while ((pos = input.find(target, pos)) != string::npos) {
		input.replace(pos, target.length(), "");
		pos += target.length();
	}
	return;
}
void excluderegex(string&input, regex reg){
	input =regex_replace(input,reg,"");
	return;
}
void oneline_txt(ifstream&ifs,string&text){
	string s;
	ifs >> s;
	while(*(s.begin())==' '){
		s.erase(s.begin());
	}
	excludeString(s,"<br>");
	excludeString(s,"<BR>");
	if (*(s.begin()) != '\n')
		text+=s+'\n';
	return;
}
void make_close_tag_oneline(string&text){
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
void make_td_oneline(string&text){
	int r=0;
	for(size_t i=1;i<text.size()-1;i++){
		if(text[i]=='t'||text[i]=='T'){
			if(text[i+1]=='d'||text[i+1]=='D')
				r+=(text[i-1]!='/'?1:-1);
		}else if(r>0&&text[i]=='\n')
				text[i]=' ';
	}
}
void make_th_oneline(string&text){
	int r=0;
	for(size_t i=1;i<text.size()-1;i++){
		if(text[i]=='t'||text[i]=='T'){
			if(text[i+1]=='h'||text[i+1]=='H')
				r+=(text[i-1]!='/'?text[i-1]=='<'?1:0:-1);
		}else if(r>0&&text[i]=='\n')
				text[i]=' ';
	}
}
void remove_other_tag(string&text){
	vector<string>patt={"<tr>","</tr>","<TR>","</TR>","<head>","</head>","<HEAD>","</HEAD>","<HTML>","</HTML>","<html>","</html>","<META[^>]*>","<title>[^<]*</title>","<table[^>]*>","</table>","<TABLE[^>]*>","</TABLE>","<body[^>]*>","</body>","\n{2}","&nbsp;"};
	for(size_t i=0;i<patt.size();i++){
		excluderegex(text,regex(patt[i]));
	}
	vector<string>num={"０","１","２","３","４","５","６","７","８","９"};
	vector<string>n={"0","1","2","3","4","5","6","7","8","9"};
	for(size_t i=0;i<num.size();i++)
		text=regex_replace(text,regex(num[i]),n[i]);
}
void prepare_afile(string&text){
	make_close_tag_oneline(text);
	make_td_oneline(text);
	make_th_oneline(text);
	remove_other_tag(text);
}
void find_return(string&text,ofstream&ofs,vector<vector<string>>&clist){
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

void make_csv_classVec(vector<vector<string>>&clist){
	ofstream ofs("syl.csv");
	for (int i = 0; i < (int)h1.size(); i++) 
		ofs << "\"" << h1[i] << "\""<< ",\n"[i == (int)h1.size() - 1];
	for (std::filesystem::directory_entry itr :std::filesystem::directory_iterator("syll")) {
		ifstream ifs(itr.path().string());
		string text;
		do {
			oneline_txt(ifs,text);
		} while (!ifs.eof());
		prepare_afile(text);
		find_return(text,ofs,clist);
		ifs.close();
	}
	ofs.close();
}

