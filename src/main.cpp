#include<string>
#include<utility>
#include<cstdlib>
#include<cwchar>
#include<ranges>
#include<sstream>
#include<regex>
#include<vector>
#include<fstream>
#include<filesystem>
#include<iostream>
#include<map>
#include<set>
using namespace std;
using str = string;
template<class f> using vc=vector<f>;
template<class f> using vv=vc<vc<f>>;
template<class f> using v3=vc<vv<f>>;

void list_onload(v3<map<str,str>>&,int);
void interactive(v3<map<str,str>>&);

int main(int argc,char**argv) {
	v3<map<str,str>> clist(4,vv<map<str,str>>(7));
	list_onload(clist,argc);
	interactive(clist);
	system("clear");
}
static inline vc<str> h1 = {
	"開設期",
	"授業科目名",
	"担当教員名",
	"曜日・時限・講義室",
	"授業の方法",
	"授業の方法 【詳細情報】",
	"授業の目標・概要等",
	"授業計画",
	"教科書・参考書等",
	"予習・復習への アドバイス",
	"履修上の注意 受講条件等",
	"成績評価の基準等"
};
void print_light(const map<str,str>&s){
	static const vector P{1,2,3,4,6};
	cout<<h1[P[0]]<<" : ";
	cout<<"\033[31m"<<s.find(h1[P[0]])->second<<"\033[0m\n";
	for(auto const&p:P|views::drop(1))
		cout<<"\t"<<h1[p]<<" : "<<s.find(h1[p])->second<<"\n";
	cout<<endl;
}
void print_full(const map<str,str>&s){
	static const vector P{1,2,3,0,4,5,6,7,8,9,10,11};
	cout<<endl;
	system("clear");
	cout<<h1[P[0]]<<" : "<<s.find(h1[P[0]])->second<<"\n";
	for(auto const&p:P|views::drop(1))
		if(s.find(h1[p])!=s.end())
			cout<<h1[p]<<" : "<<s.find(h1[p])->second<<"\n\n";
	cout<<"Press any key to back"<<endl;
	str c;cin>>c;
}

void interactive_select(v3<map<str,str>>&clist,int grade,int term){
	bool loop=true;
	vc<map<str,str>>L;
	static const vc<str>terms{"通年","前期","1ターム","2ターム","後期","3ターム","4ターム"};
	switch(term){
		case 0:{
			for(int i=0;i<7;i++) for(auto x:clist[grade][i]) L.push_back(x);
		}break;
		case 1:
		case 4:{
			for(int i=0;i<3;i++) for(auto x:clist[grade][i+term]) L.push_back(x);
		}break;
		default:{
			for(auto x:clist[grade][term])L.push_back(x);
		}
	}
	do{
		system("clear");
		cout<<endl;
		for(int i=0;i<L.size();i++){
			cout<<i<<" : ";
			print_light(L[i]);
		}
		cout<<grade+1<<"年 "<<terms[term]<<"\n";
		cout<<"詳細を表示するにはIDを選択してください。\n";
		cout<<"\tターム選択の画面に戻るにはIDの範囲外の数値を入力してください。"<<endl;
		int id;cin>>id;
		if(id<0||L.size()<=id)loop=false;
		else print_full(L[id]);
	}while(loop);
}

void interactive_term(v3<map<str,str>>&clist,int grade){
	do{
		system("clear");
		cout<<grade+1<<"年:\n";
		cout<<"開講期間を入力してください\n";
		cout<<"\t前期は12, 後期は34, 通年は1234と入れてください。\n";
		cout<<"\tそれ以外を入力すると学年の選択画面に戻ります。"<<endl;
		int term;cin>>term;
		int arg_term;
		switch(term){
			case 1234:arg_term=0;break;
			case 12:arg_term=1;break;
			case 1:arg_term=2;break;
			case 2:arg_term=3;break;
			case 34:arg_term=4;break;
			case 3:arg_term=5;break;
			case 4:arg_term=6;break;
			default:return;break;
		}
		interactive_select(clist,grade,arg_term);
	}while(true);
}
void interactive(v3<map<str,str>>&clist){
	bool loop=true;
	do{
		system("clear");
		cout<<"学年を入れてください。";
		cout<<"\t1～4以外を入力すると終了します。"<<endl;
		int grade;cin>>grade;
		if(0<grade&&grade<5){
			interactive_term(clist,grade-1);
		}else loop=false;
	}while(loop);
}

struct _html;
struct html{
	vector<_html>inner;
};
struct _html{
	bool is_str;
	string innnerText;
	html innerHTML;
	_html():is_str(false){}
};
static inline const set<str> vtag({"br","hr","img","input","link","meta","area","base","col","embed","param","source","track","wbr","BR","HR","IMG","INPUT","LINK","META","AREA","BASE","COL","EMBED","PARAM","SOURCE","TRACK","WBR"});
void recursive_html(html&par,string end,string&page,size_t&cur){
	str buf;
	for(size_t i=cur;i<page.size();cur=++i){
		if(page[i]=='<'){
			size_t close=i;
			for(;close<page.size();close++)if(page[close]=='>')break;
			if(page[i+1]=='/'){
				str etag(page.begin()+i,page.begin()+close+1);
				for(auto&x:etag)
					x=tolower(x);
				if(etag==end){
					cur=close;
					return;
				}
			}else{
				string tag,TAG(page.begin()+i,page.begin()+close+1);
				for(size_t i=1;i<TAG.size();i++)
					if(TAG[i]=='>'||TAG[i]==' '||TAG[i]=='\t'||TAG[i]=='\n')
						break;
					else tag.push_back(TAG[i]);
				if(vtag.contains(tag)){
					_html val; smatch mt;
					val.is_str=true;
					val.innnerText=TAG;
					par.inner.push_back(val);
					i=cur=close;
				}else{
					_html push;
					str etag=str("</")+tag+">";
					for(auto&x:etag)
						x=tolower(x);
					i=cur=close+1;
					recursive_html(push.innerHTML,etag,page,cur);
					i=cur;
					par.inner.push_back(push);
				}
			}
		}else{
			buf.push_back(page[i]);
			if((i+1<page.size()&&page[i+1]=='<')||i+1==page.size()){
				bool has_printable=false;
				for(const auto x:buf)
					if((!iscntrl(x)&&!isblank(x))||x>127){
						has_printable=true;
						break;
					}
				if(has_printable){
					_html push;
					push.is_str=true;
					push.innnerText=move(buf);
					par.inner.push_back(push);
				}
			}
		}
	}
}
html construct_html(vc<str>&file){
	html ret;
	size_t cur=0;
	str page;
	static const vector<pair<regex,const char*>>
		REGEX({
			{regex("&nbsp;"), " "},
			{regex("&amp;"), "&"},
			{regex("&quot;"),"\""},
			{regex("&apos;"),"'"},
			{regex("&lt;"),"<"},
			{regex("&gt;"),">"},
			{regex("<(BR|br)>"),"\n"},
			{regex("\r"),""},
			{regex("（"),"("},
			{regex("）"),")"},
			{regex("&lsquo;"),"‘"},
			{regex("&rsquo;"),"’"},
			{regex("&ldquo;"),"“"},
			{regex("&rdquo;"),"”"}
		});
	for(auto&x:file){
		for(const auto& [src,dst]:REGEX)
			x=regex_replace(x,src,dst);
		page.insert(page.end(),x.begin(),x.end());
	}
	recursive_html(ret,string(""),page,cur);
	return ret;
}
bool find_h1(ofstream&ofs,string&tag,vc<str>&page){
	for(int i=0;i<page.size()-1;i++)
	if(page[i].find(tag)<page[i].size()){
		str x=page[i+1];
		x=regex_replace(x,regex("\n"),"\\n");
		ofs<<"\""<<tag<<"\":\""<<x<<"\",\n";
		return true;
	}
	return false;
}
void HTML2VS(html&h,vc<str>&vs){
	for(auto&x:h.inner){
		if(x.is_str) vs.push_back(x.innnerText);
		else HTML2VS(x.innerHTML,vs);
	}
}

void read_json(ifstream&ifs,v3<map<str,str>>&clist){
	str buf;
	static const vector E{"０","１","２","３","４","５","６","７","８","９"};
	static const vector F{"0","1","2","3","4","5","6","7","8","9"};
	static const vc<str> grades({"1年","2年","3年","4年"});
	static const vc<str> terms({"通年","(前期)","1ターム","2ターム","(後期)","3ターム","4ターム"});
	size_t cur=0;
	do{
		getline(ifs,buf);
		if(buf.find("__CLASS__",cur)<buf.size()){
			vc<str>vbuf;
			do{
				getline(ifs,buf);
				if((cur=buf.find("}"))<buf.size()){
					break;
				}
				vbuf.push_back(move(buf));
			}while(!ifs.eof());
			buf.clear();
			map<str,str> mbuf;
			for(int i=0;i<10;i++)
				vbuf[0]=regex_replace(vbuf[0],regex(E[i]),F[i]);
			for(int i=0;i<vbuf.size();i++){
				int j=i;
				if(vbuf[i].find(h1[i])>=vbuf[i].size()){
					for(int k=0;k<h1.size();k++)
						if(vbuf[i].find(h1[k])<vbuf[i].size()){
							j=k;
							break;
						}
				}
				size_t l=vbuf[i].find(":\"")+2;
				size_t r=vbuf[i].find("\"",l);
				str tar(vbuf[i].begin()+l,vbuf[i].begin()+r);
				tar=regex_replace(tar,regex("\\\\n"),"\n");
				mbuf.insert(make_pair(h1[j],tar));
			}
			int grade=0,term=0;
			for(int i=0;i<4;i++)
				if(mbuf[h1[0]].find(grades[i])<mbuf[h1[0]].size()){
					grade=i;
					break;
				}
			for(int i=0;i<terms.size();i++)
				if(mbuf[h1[0]].find(terms[i])<mbuf[h1[0]].size()){
					term=i;
					break;
				}
			clist[grade][term].push_back(move(mbuf));
		}
	}while(!ifs.eof());
}
void list_onload(v3<map<str,str>>&clist,int mode){
	if(mode==1){// needed prepare structed data of classes
		ofstream ofs("syl.json");
		ofs<<"{\n";
		for(auto itr : filesystem::directory_iterator("syll")){
			ifstream file(itr.path().string());
			vc<str> vs_file;
			do{
				str buf;
				getline(file,buf);
				bool has_printable=false;
				for(const auto x:buf)
					if((!iscntrl(x)&&!isblank(x))||x>127){
						has_printable=true;
						break;
					}
				if(has_printable) vs_file.emplace_back(move(buf));
			}while(!file.eof());
			html page=construct_html(vs_file);
			vc<str> vs;
			HTML2VS(page,vs);
			ofs<<"\"__CLASS__\" : {\n";
			for(auto&x:h1) find_h1(ofs,x,vs);
			ofs<<"},\n";
		}
		ofs<<"\n}\n";
		ofs.close();
	}
	// use structed data of classes
	ifstream ifs("syl.json");
	read_json(ifs,clist);
}