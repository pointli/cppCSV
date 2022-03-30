#ifndef  _READCSV_H_
#define _READCSV_H_
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<sstream>
#include<cstdio>
using namespace std;
class ReadCSV {
private:
	string dataFile;
public:
	ReadCSV(string path) : dataFile(path) {}
	ReadCSV() :dataFile(string()) {}
	void SetFilePath(string path) {
		dataFile = path;
	}
	//从csv读取数据 存储为string类型。
	void LoadDataFromCSV(vector<vector<string>>& content) {
		ifstream ifs;
		ifs.open(dataFile.data());
		if (ifs.is_open()) {
			cout << dataFile << " opening successful." << endl;
		}
		else {
			cout << dataFile << " opening failed" << endl;
			return;
		}

		string line;
		//读取文件表头
		while (getline(ifs, line)) {
			string columElement;
			stringstream stream(line);
			content.push_back(vector<string>());
			while (getline(stream, columElement, ',')) {
				content.back().push_back(columElement);
			}
			//添加最后一个元素。由于读取最后一个空元素会跳出循环,例如a，空    只能读取到a，空出处没读到
			if (!stream && columElement.empty()) {
				content.back().push_back("");
			}
		}
		ifs.close();

		//校验程序
		//输出数据
		string checkFile = dataFile + "check.csv";
		string outputContent;
		ofstream ofs(checkFile.data());
		for (auto ite : content) {
			for (auto iite : ite) {
				outputContent+=iite;
				outputContent += ',';
			}
			outputContent.pop_back();
			outputContent.push_back('\n');
		}
		ofs << outputContent;
		ofs.close();

		cout << "checking date..." << endl;
		ifstream ifssour(dataFile.data());
		string strsour;
		ifstream ifscheck(checkFile.data());
		string strcheck;

		while (getline(ifssour, line)) {
			strsour += line;
		}
		ifssour.close();


		while (getline(ifscheck, line)) {
			strcheck += line;
		}
		ifscheck.close();
		if (strsour == strcheck) {
			cout << "load data sucessfully, data passs checking." << endl;
		}
		else {
			cout << "data loaded wrong!!!" << endl;
		}

		cout << content.size() << " lines of data have been loaded." << endl;
		remove(checkFile.data());
	}
};
#endif // ! _READCSVFILE_H_
