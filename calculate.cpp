#include"Arduino.h"
#include "ArduinoSTL.h"
#include "stack"
#include"calculate.h"
using namespace std;
enum ABS_ODEVITY {
	ABS_ODD = 1,
	ABS_EVEN = 2,
};
//绠楁湳绗﹀彿浼樺厛鏉冪瓑绾?
enum PRIO_LV {
	PRIO_LV0 = 0,
	PRIO_LV1 = 1,
	PRIO_LV2 = 2,
	PRIO_LV3 = 3,
	PRIO_LV4 = 4,
	PRIO_LV5 = 5,
	PRIO_LV6 = 6,
};
//鏋勯€犲嚱鏁帮紝鍒濆鍖栨垚鍛樺彉閲?
Calculator::Calculator() {
	operatorSym = "鏀寔杩愮畻绗︼細+, - , *, /, %锛堢櫨鍒嗗彿锛? ^锛堝箓娆℃柟锛? | |锛堢粷瀵瑰€硷級锛岋紒锛堥樁涔橈級,c,s,t銆傚叾浠栫鍙凤細( ) [ ] { }";
	result = 0.0;
}
//琛ㄨ揪寮忚嚜瀹氫箟鏍囧噯鏍煎紡鍖?
void Calculator::getFormat() {
	
	stdInfix = infix;
  /*
	for (size_t i = 0; i < stdInfix.size(); i++) {
		if (stdInfix[i] == '-' || stdInfix[i] == '+') {
			if (i == 0) {
				stdInfix.insert(0, 1, '0');
			}
			else if (stdInfix[i - 1] == '(') {
				stdInfix.insert(i, 1, '0');
			}
		}
	}*/
}
//鑾峰彇绠楁湳绗﹀彿浼樺厛绾?
int Calculator::getPrior(char c) {
	if (c == 'O' || c == 'A' ) {
		return PRIO_LV1;
	}
	else if (c == '<' || c == '>' || c== 'B' || c=='S' || c=='E') {
		return PRIO_LV2;
	}
	else if (c == '+' || c == '-') {
		return PRIO_LV3;
	}
	else if (c == '*' || c == '/') {
		return PRIO_LV4;
	}
	else if (c == '%' || c == '^') {
		return PRIO_LV5;
	}
	else if (c == '!'||c=='T'||c=='C'||c=='S') {
		return PRIO_LV6;
	}
	else {
		return PRIO_LV0;
	}
	//else { cout << c << 闈炴硶绗﹀彿锛?<< endl; }
}
//鍚庣紑琛ㄨ揪寮忚浆鎹?
void Calculator::getPostfix() {
	
	int absNumeber = ABS_ODD;				//缁濆鍊肩鍙蜂釜鏁扮殑濂囧伓鎬?
	string tmp;
	
	//for (int i = 0; i < stdInfix.length(); i++) {
	for (size_t i = 0; i < stdInfix.size(); i++) {					//string.size()杩斿洖size_type绫诲瀷锛岄伩鍏嶄笅鏍囪繍绠楁椂鐨勭被鍨嬫孩鍑?
		tmp = "";
		switch (stdInfix[i]) {
		case 'A':
		case 'O':
		case 'E':
		case '<':
		case '>':
		case 'S':
		case 'B':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '^':
		case '!':
			if (symStack.empty() || symStack.top() == '(' || symStack.top() == '[' || symStack.top() == '{' || (symStack.top() == '|' && absNumeber == ABS_ODD)) {
				symStack.push(stdInfix[i]);
			}
			else {
				while (!symStack.empty() && (getPrior(symStack.top()) >= getPrior(stdInfix[i]))) {
					tmp += symStack.top();
					postfix.push_back(tmp);
					symStack.pop();
					tmp = "";
				}
				symStack.push(stdInfix[i]);
			}
			break;
		case '|':
			if (absNumeber == ABS_ODD) {
				symStack.push(stdInfix[i]);
				absNumeber = ABS_EVEN;
			}
			else{
				while (!symStack.empty() && symStack.top() != '|') {
					tmp += symStack.top();
					postfix.push_back(tmp);
					symStack.pop();
					tmp = "";
				}
				if (!symStack.empty() && symStack.top() == '|') {
					tmp += symStack.top();
					postfix.push_back(tmp);						//宸︾粷瀵瑰€肩鍙?|'鍔犲叆鍚庣紑琛ㄨ揪寮忥紝鐢ㄤ簬缁濆鍊肩殑妫€娴嬭绠?
					symStack.pop();
					absNumeber = ABS_ODD;
				}
			}
			break;
		case '(':
		case '[':
		case '{':
			symStack.push(stdInfix[i]);
			break;
		case ')':
			while (!symStack.empty() && symStack.top() != '(') {
				tmp += symStack.top();
				postfix.push_back(tmp);
				symStack.pop();
				tmp = "";
			}
			if (!symStack.empty() && symStack.top() == '(') {
				symStack.pop();							//灏嗗乏鎷彿鍑烘爤涓㈠純
			}
			break;
		case ']':
			while (!symStack.empty() && symStack.top() != '[') {
				tmp += symStack.top();
				postfix.push_back(tmp);
				symStack.pop();
				tmp = "";
			}
			if (!symStack.empty() && symStack.top() == '[') {
				symStack.pop();							//灏嗗乏鎷彿鍑烘爤涓㈠純
			}
			break;
		case '}':
			while (!symStack.empty() && symStack.top() != '{') {
				tmp += symStack.top();
				postfix.push_back(tmp);
				symStack.pop();
				tmp = "";
			}
			if (!symStack.empty() && symStack.top() == '{') {
				symStack.pop();							//灏嗗乏鎷彿鍑烘爤涓㈠純
			}
			break;
		default:
			if ((stdInfix[i] >= '0' && stdInfix[i] <= '9')) {
				tmp += stdInfix[i];
				while (i + 1 < stdInfix.length() && (stdInfix[i + 1] >= '0' && stdInfix[i + 1] <= '9' || stdInfix[i + 1] == '.')) {		//灏忔暟澶勭悊
					
					tmp += stdInfix[i + 1];			//鏄繛缁殑鏁板瓧锛屽垯杩藉姞
					i++;
				}
				if (tmp[tmp.length() - 1] == '.') {
					tmp += '0';						//灏唜.鍋歺.0澶勭悊
				}
				postfix.push_back(tmp);
			}
			break;
		}//end switch
	}//end for
	
	//if(!symStack.empty()) {
	while (!symStack.empty()) {						//灏嗘爤涓墿浣欑鍙峰姞鍏ュ悗缂€琛ㄨ揪寮?
		tmp = "";
		tmp += symStack.top();
		postfix.push_back(tmp);
		symStack.pop();
	}
}
//鑾峰彇杩愮畻缁撴灉
void Calculator::calResult() {
	
	string tmp;
	double number = 0;
	double op1 = 0, op2 = 0;
	
	for (int i = 0; i < postfix.size(); i++) {
		tmp = postfix[i];
		if (tmp[0] >= '0' && tmp[0] <= '9') {
			number = atof(tmp.c_str());
			figStack.push(number);
		}
		else if (postfix[i] == "<") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push((op1 < op2));
		}
		else if (postfix[i] == ">") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push((op1 > op2));
		}
		else if (postfix[i] == "B") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push((op1 >= op2));
		}
		else if (postfix[i] == "S") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push((op1 <= op2));
		}
		else if (postfix[i] == "E") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push((op1 == op2));
		}
		else if (postfix[i] == "A") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push((op1 && op2));
		}
		else if (postfix[i] == "O") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push((op1 || op2));
		}
		else if (postfix[i] == "+") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push(op1 + op2);
		}
		else if (postfix[i] == "-") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push(op1 - op2);
		}
		else if (postfix[i] == "*") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push(op1* op2);
		}
		else if (postfix[i] == "/") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop(); 
			}
			if (op2 != 0) {
				///闄ゆ暟涓嶄负0锛屾湭鍋氬鐞嗭紝榛樿
			}
			figStack.push(op1 / op2);
		}
		else if (postfix[i] == "%") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push(fmod(op1, op2));			//鍙繘琛屽皬鏁版眰浣?
		}
		else if (postfix[i] == "^") {
			if (!figStack.empty()) {
				op2 = figStack.top();
				figStack.pop();
			}
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push(pow(op1, op2));
		}
		else if (postfix[i] == "|") {
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			figStack.push(abs(op1));
		}
		else if (postfix[i] == "!") {
			if (!figStack.empty()) {
				op1 = figStack.top();
				figStack.pop();
			}
			if (op1 > 0) {
				//闃朵箻鏁板簲澶т簬锛涗负灏忔暟鏃?杞寲涓烘暣鏁版眰闃?
				double factorial = 1;
				for (int i = 1; i <= op1; ++i)
				{
					factorial *= i;
				}
				op1 = factorial;
			}
			figStack.push(op1);
		}
	}//end for
	if (!figStack.empty()) {
		result = figStack.top();
	}
}
//璁＄畻鏂规硶
void Calculator::calculate() {
	
	getFormat();				//琛ㄨ揪寮忚嚜瀹氫箟鏍囧噯鏍煎紡鍖?
	getPostfix();				//鍚庣紑琛ㄨ揪寮忚浆鎹?
	calResult();				//鑾峰彇绠楁湳缁撴灉
}
//鑾峰彇缁撴灉
double Calculator::getResult() {
	return result;
}