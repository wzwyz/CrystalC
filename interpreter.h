#ifndef Interpreter_h
#define Interpreter_h
#include"Arduino.h"
#include "ArduinoSTL.h"
#include "stack"
#include"calculate.h"
using namespace std;
struct valuer{
	int type;
	string name;
	int forint;
	double fordouble;
	string forstring;
	bool forbool;
};
struct functioner{
	string name;
	int type;
	int returnint;
	double returndouble;
	string returnstring;
	bool returnbool;
	functioner(string name="",int type=5):name(name),type(type) {}
};
struct userdefinefunc{
	int type;
	string name;
	int returnint;
	double returndouble;
	string returnstring;
	bool returnbool;
	string to_do;
	int value_num;
	valuer init[5];
};
class Interpreter{
  public:
    valuer T[20],T_record[20];
    functioner F[20];
    userdefinefunc K[5];
    string to_string(double n);
    void initfunction();
    int find_pair(string to_do,string left,string right);
    string exchange(string to_do);
    double operexpression(string to_do);
    void actuator(string to_do);
  private:
    int valuer_pos=0;
    int function_pos=4;
    int userdefinefunc_pos=0;
    bool return_flag=false;
    bool break_flag=false;
};
#endif