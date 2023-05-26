#ifndef Calculator_h
#define Calculator_h
#include"Arduino.h"
#include "ArduinoSTL.h"
#include "stack"
using namespace std;
class Calculator{
public:
	Calculator();
	void getFormat();					//琛ㄨ揪寮忚嚜瀹氫箟鏍囧噯鏍煎紡鍖?
	int getPrior(char c);				//鑾峰彇绠楁湳绗﹀彿浼樺厛绾?
	void getPostfix();					//鍚庣紑琛ㄨ揪寮忚浆鎹?
	void calResult();					//璁＄畻缁撴灉
	void calculate();					//璁＄畻鏂规硶
	double getResult();					//鑾峰彇缁撴灉
	
	string operatorSym;					//杩愮畻绗﹀彿
	string infix;						//琛ㄨ揪寮忕紦瀛?
	
private:
	vector<string> postfix;				//鍚庣紑琛ㄨ揪寮忓悜閲?
	stack<char> symStack;				//绗﹀彿鏍?
	stack<double> figStack;				//鏁板瓧鏍?
	string stdInfix;					//鑷畾涔夋爣鍑嗘牸寮忓寲琛ㄨ揪寮?
	double result;						//鏈€缁堣绠楃粨鏋?
};
#endif