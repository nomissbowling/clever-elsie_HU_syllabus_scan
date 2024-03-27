#include"../include/backend.hpp"
using namespace std;
vector<string> h1 = {"授業科目名","担当教員名","開設期","曜日・時限・講義室","授業の方法","授業の方法 【詳細情報】","授業の目標・概要等","授業計画","教科書・参考書等","予習・復習への アドバイス","履修上の注意 受講条件等","成績評価の基準等"};

void backend(vector<vector<string>>&clist){
	ofstream ofs("syl.csv");
	for (int i = 0; i < (int)h1.size(); i++) 
		ofs << "\"" << h1[i] << "\""<< ",\n"[i == (int)h1.size() - 1];
	for (std::filesystem::directory_entry itr :std::filesystem::directory_iterator("syll")) {
		ifstream ifs(itr.path().string());
		string text;
		do {
			getline(ifs,text);
		} while (!ifs.eof());
		preproc_tags(text);
		ext_tbl(text,ofs,clist);
		ifs.close();
	}
	ofs.close();
}

