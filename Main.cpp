#include"ReadCSV.h"
using namespace std;
int main(int argc,char *argv[]) {
	vector<vector<string>> content;
	ReadCSV rc(argv[1]);
	rc.LoadDataFromCSV(content);
}