#include"Arduino.h"
#include "ArduinoSTL.h"
#include "stack"
//#include"calculate.h"
#include"interpreter.h"
using namespace std;
enum funcer {
	Val_int = 0,
	Val_string = 1,
	Val_bool = 2,
	Val_void = 3,
	Val_double = 4,
};
string Interpreter::to_string(double n)
{
  
	double m=n*10000;
  cout<<"input num is: "<<m<<endl;
  string toturn="";
  if(m==0)return "0";
  if(m<0){
    m=-m;
    toturn+="0-";
  }
  cout<<"m "<<m<<endl;
  int b=log10(m);
  if(b<4){
    toturn+="0.";
    for(int i=b;i<3;i++){
      toturn+="0";
    }
  }
  while(m>1&&b>=0){
    cout<<b<<" ";
    int a=m/pow(10,b);
    switch(a){
      case 0:{
        toturn+="0";
        break;
      }
      case 1:{
        toturn+="1";
        break;
      }
      case 2:{
        toturn+="2";
        break;
      }
      case 3:{
        toturn+="3";
        break;
      }
      case 4:{
        toturn+="4";
        break;
      }
      case 5:{
        toturn+="5";
        break;
      }
      case 6:{
        toturn+="6";
        break;
      }
      case 7:{
        toturn+="7";
        break;
      }
      case 8:{
        toturn+="8";
        break;
      }
      case 9:{
        toturn+="9";
        break;
      }
    }
    cout<<a<<endl;
    if(b==4){
      toturn+=".";
      cout<<"."<<endl;
      }
    m=m-a*pow(10,b);
    b--;
  }
  cout<<"turn is :"<<toturn<<endl;
	return toturn;
  
}
void Interpreter::initfunction(){
	F[0] = functioner("int",Val_void);
	F[1] = functioner("bool",Val_void);
	F[2] = functioner("string",Val_void);
	F[3] = functioner("cos",Val_double);
	F[4] = functioner("giver",Val_void);
}
int Interpreter::find_pair(string to_do,string left,string right){
	int num=0;bool flag=false;
	for(int i=0;i<=to_do.length();i++){
		if(to_do.substr(i,1)==left)num++;
		if(to_do.substr(i,1)==right)num--;
		if(num!=0)flag=true;
		if(num==0&&flag==true)return i;
	}
}
string Interpreter::exchange(string to_do){
	for(int i=0;i<=function_pos;i++){
		cout<<"check function: "<<F[i].name<<"	";
		string cur_name=F[i].name;
		while(to_do.find(cur_name.append("(")) != string::npos){
			string cur_operate=to_do.substr(to_do.find_first_of(cur_name.append("(")));
			int operate_end=cur_operate.find_first_of(")");
			cur_operate=cur_operate.substr(0,operate_end+1);
			cout<<"cur_operate "<<cur_operate<<" ";
			actuator(cur_operate);
			double retrun_values;
			switch(F[i].type){
				case Val_int:{
					retrun_values=F[i].returnint;
					break;
				}
				case Val_double:{
					retrun_values=F[i].returndouble;
					break;
				}
				case Val_bool:{
					retrun_values=F[i].returnbool;
					break;
				}
				default:{
					retrun_values=0;
					break;
				}
			}
			to_do=to_do.replace(to_do.find_first_of(cur_name.append("(")),cur_operate.length(),to_string(retrun_values));
			cout<<" to_do is "<<to_do<<" ";
		}
		cout<<"check over."<<endl;
	}
	cout<<"calculate function in to do is "<<to_do<<endl;
	cout<<"userdefinefunc_pos "<<userdefinefunc_pos<<endl;
	for(int i=1;i<=userdefinefunc_pos;i++){
		cout<<"check function: "<<K[i].name<<"	";
		string cur_name=K[i].name;
		while(to_do.find(cur_name.append("(")) != string::npos){
			string cur_operate=to_do.substr(to_do.find_first_of(cur_name.append("(")));
			int operate_end=cur_operate.find_first_of(")");
			cur_operate=cur_operate.substr(0,operate_end+1);
			cout<<"cur_operate "<<cur_operate<<" ";
			actuator(cur_operate);
			double retrun_values;
			switch(K[i].type){
				case Val_int:{
					retrun_values=K[i].returnint;
					break;
				}
				case Val_double:{
					retrun_values=K[i].returndouble;
					break;
				}
				case Val_bool:{
					retrun_values=K[i].returnbool;
					break;
				}
				default:{
					retrun_values=0;
					break;
				}
			}
			to_do=to_do.replace(to_do.find_first_of(cur_name.append("(")),cur_operate.length(),to_string(retrun_values));
			cout<<" to_do is "<<to_do<<" ";
		}
		cout<<"check over."<<endl;
	}
	cout<<"calculate user_define function in to do is "<<to_do<<endl;
	
	for(int i=1;i<=valuer_pos;i++){
		cout<<i<<endl;
		cout<<"cur_find "<<T[i].name<<" numer "<<T[i].forint<<endl;
		while(to_do.find(T[i].name) != string::npos){
			string houi=T[i].name;
			int cur_start=to_do.find(houi.append("$"));
			double retrun_values;
			switch(T[i].type){
				case Val_int:{
					retrun_values=T[i].forint;
					break;
				}
				case Val_double:{
					retrun_values=T[i].fordouble;
					break;
				}
				case Val_bool:{
					retrun_values=T[i].forbool;
					break;
				}
				default:{
					retrun_values=0;
					break;
				}
			}
			cout<<cur_start-1<<endl<<cur_start+T[i].name.length()+1<<endl;
			to_do=to_do.replace(cur_start-1,cur_start+T[i].name.length()+1,to_string(retrun_values));
			cout<<to_do<<endl;
		}
	}
	cout<<"after bring in variables is"<<to_do<<endl;
	return to_do;
}
double Interpreter::operexpression(string to_do){
	cout<<"operexpression is "<<to_do<<endl;
	to_do=exchange(to_do);
	Calculator cal;
	cal.infix=to_do;
	cal.calculate();
	cout<<"reslut is "<<cal.getResult()<<endl;
	return cal.getResult();
}
void Interpreter::actuator(string to_do){
	int point=0;
	while(!to_do.empty()){
		int keywords_start=point;
		int keywords_end=to_do.find_first_of('(');
		int operate_end=find_pair(to_do,"(",")");
		string cur_keyword=to_do.substr(keywords_start,keywords_end-keywords_start);
		cout<<"keyword:"<<cur_keyword<<endl;
		string cur_operate=to_do.substr(keywords_end+1,operate_end-keywords_end-1);
		cout<<"operate:"<<cur_operate<<endl;
		to_do=to_do.substr(operate_end+1);
		if(cur_keyword=="if"){
			bool cur_valuer;
			string cur_do = to_do.substr(1,find_pair(to_do,"{","}")-1);
			to_do=to_do.substr(find_pair(to_do,"{","}")+1);
			if(cur_operate=="true")cur_valuer=true;
			else if(cur_operate=="false")cur_valuer=false;
			else cur_valuer=operexpression(cur_operate);
			cout<<"cur_operate "<<cur_operate<<endl;
			if(cur_valuer){
				cout<<"if comes to true , than to run things in if_________________________________________________"<<endl;
				actuator(cur_do);
				
				cout<<"if is over _________________________________________________________________________________"<<endl;
			}
			else cout<<"if comes to false and in if things will not run"<<endl;
		}
		if(cur_keyword=="while"){
			bool cur_valuer;
			string cur_do = to_do.substr(1,find_pair(to_do,"{","}")-1);
			to_do=to_do.substr(find_pair(to_do,"{","}")+1);
			int valuer_pos_old=valuer_pos;
			cout<<valuer_pos<<endl;
			for(int i=1;i<=valuer_pos;i++){
				T_record[i].name=T[i].name;
				T_record[i].forint=T[i].forint;
				T_record[i].forstring=T[i].forstring;
				T_record[i].type=T[i].type;
				T_record[i].forbool=T[i].forbool;
				T_record[i].fordouble=T[i].fordouble;
			}
			
			if(cur_operate=="true")cur_valuer=true;
			else cur_valuer=operexpression(cur_operate);
			cout<<"cur_operate "<<cur_operate<<endl;
			cout<<"======================================== while start ========================================"<<endl;
			int times=0;
			while(cur_valuer){
				cout<<"true"<<endl;
				if(break_flag){
					break_flag=false;
					break;
				}
				if(return_flag){
					break;
				}
				cout<<"if comes to true , than to run things in while_______________________________________________"<<endl;
				actuator(cur_do);
				for(int i=valuer_pos_old;i<valuer_pos;i++){
					T[i].name="";
					T[i].forint=0;
					T[i].forstring="";
					T[i].forbool=0;
					T[i].fordouble=0;
					T[i].type=Val_void;
				}
				valuer_pos=valuer_pos_old;
				times++;
				cout<<"close "<<times<<" turn _________________________________________________________________________________"<<endl;
				cur_valuer=operexpression(cur_operate);
				if(!cur_valuer){
					for(int i=1;i<=valuer_pos;i++){
						T[i].name=T_record[i].name;
						T[i].forint=T_record[i].forint;
						T[i].forstring=T_record[i].forstring;
						T[i].type=T_record[i].type;
						T[i].forbool=T_record[i].forbool;
						T[i].fordouble=T_record[i].fordouble;
					}
				}
				else {
					for(int i=1;i<=valuer_pos;i++){
						T_record[i].name=T[i].name;
						T_record[i].forint=T[i].forint;
						T_record[i].forstring=T[i].forstring;
						T_record[i].type=T[i].type;
						T_record[i].forbool=T[i].forbool;
						T_record[i].fordouble=T[i].fordouble;
					}
				}
			}
			cout<<"========================================= while end ========================================="<<endl;
		}
		if(cur_keyword=="int"){
			string value_name=cur_operate.substr(1,cur_operate.find_first_of(',')-2);
			string value_tigh=cur_operate.substr(cur_operate.find_first_of(',')+1);
			cout<<"int start: "<< value_name <<" to be "<<value_tigh<<endl;			
			valuer_pos++;
			T[valuer_pos].name=value_name;
			T[valuer_pos].type=Val_int;
			T[valuer_pos].forint=operexpression(value_tigh);
			cout<<" init "<<T[valuer_pos].name<<" = "<<T[valuer_pos].forint<<endl;
		}
		if(cur_keyword=="double"){
			string value_name=cur_operate.substr(1,cur_operate.find_first_of(',')-2);
			string value_tigh=cur_operate.substr(cur_operate.find_first_of(',')+1);
			cout<<"int start: "<< value_name <<" to be "<<value_tigh<<endl;			
			valuer_pos++;
			T[valuer_pos].name=value_name;
			T[valuer_pos].type=Val_double;
			T[valuer_pos].fordouble=operexpression(value_tigh);
			cout<<" init "<<T[valuer_pos].name<<" = "<<T[valuer_pos].fordouble<<endl;
		}
		if(cur_keyword=="bool"){
			string value_name=cur_operate.substr(1,cur_operate.find_first_of(',')-2);
			string value_tigh=cur_operate.substr(cur_operate.find_first_of(',')+1);
			cout<<"bool start: "<< value_name <<" to be "<<value_tigh<<endl;
			bool cur_value;
			cur_value=operexpression(value_tigh);
			cout<<"bool to be :"<<cur_value<<endl;
			valuer_pos++;
			T[valuer_pos].name=value_name;
			T[valuer_pos].type=Val_bool;
			T[valuer_pos].forbool=cur_value;
			cout<<" init "<<value_name<<" = "<<T[valuer_pos].forbool<<endl;
		}
		if(cur_keyword=="string"){
			string value_name=cur_operate.substr(1,cur_operate.find_first_of(',')-2);
			string value_tigh=cur_operate.substr(cur_operate.find_first_of(',')+1);
			string cur_valuer;
			cout<<"string start: "<< value_name <<" to be "<<value_tigh<<endl;
			if(value_tigh.find('$')== string::npos){
				cur_valuer=value_tigh.substr(1,value_tigh.length()-2);
			}
			else{
				for(int i=1;i<=valuer_pos;i++){
					if(T[i].name==value_tigh.substr(1,value_tigh.find_first_of('$'))){
						cur_valuer=T[i].forstring;
						break;
					}
				}	
			}
			valuer_pos++;
			T[valuer_pos].name=value_name;
			T[valuer_pos].type=Val_string;
			T[valuer_pos].forstring=cur_valuer;
			cout<<" init "<<value_name<<" = "<<cur_valuer<<endl;
		}
		if(cur_keyword=="cos"){
			double cur_values=cos(operexpression(cur_operate));
			cout<<"cos start: "<< cur_operate <<endl;		
			F[3].returndouble=cur_values;
			cout<<" get cos( "<<cur_operate<<" ) = "<<cur_values<<endl;
		}
		if(cur_keyword=="giver"){
			string value_name=cur_operate.substr(1,cur_operate.find_first_of(',')-2);
			string value_tigh=cur_operate.substr(cur_operate.find_first_of(',')+1);
			cout<<"change start: "<< value_name <<" to be "<<value_tigh<<endl;	
			for(int i=1;i<=valuer_pos;i++){
				if(T[i].name==value_name){
					switch(T[valuer_pos].type){
						case Val_int:{
							T[valuer_pos].forint=operexpression(value_tigh);
							cout<<T[valuer_pos].name<<" is now "<<T[valuer_pos].forint<<endl;
							break;
						}
						case Val_double:{
							T[valuer_pos].fordouble=operexpression(value_tigh);
							cout<<T[valuer_pos].name<<" is now "<<T[valuer_pos].fordouble<<endl;
							break;
						}
						case Val_string:{
							T[valuer_pos].forstring=value_tigh.substr(1,value_tigh.length()-1);
							cout<<T[valuer_pos].name<<" is now "<<T[valuer_pos].forstring<<endl;
							break;
						}
						case Val_bool:{
							T[valuer_pos].forbool=operexpression(value_tigh);
							cout<<T[valuer_pos].name<<" is now "<<T[valuer_pos].forbool<<endl;
							break;
						}
					}
					break;
				}
			}
		}
		if(cur_keyword=="fout"){
			cout<<"Output"<<endl;
			string cur_operater=cur_operate;
			while(cur_operater.find(",")!= string::npos){
				string operate_name=cur_operater.substr(0,cur_operater.find_first_of(","));
				cout<<"operate_name "<<operate_name<<endl;
				if(operate_name.substr(0,1)=="\""){
					cout<<"======================================== Output start ========================================"<<endl;
					cout<<cur_operater.substr(1,operate_name.length()-2);
					cout<<"======================================== Output ends ========================================"<<endl;
				}
				else if(operate_name=="endl"){
					cout<<"======================================== Output start ========================================"<<endl;
					cout<<endl;
					cout<<"======================================== Output ends ========================================"<<endl;
				}
				else {
					double reslut=operexpression(operate_name);
					cout<<"======================================== Output start ========================================"<<endl;
					cout<<reslut;
					cout<<"======================================== Output ends ========================================"<<endl;
				};
				cur_operater=cur_operater.substr(cur_operater.find_first_of(",")+1);
			}
			string operate_name=cur_operater;
			cout<<"operate_name "<<operate_name<<endl;
			if(operate_name.substr(0,1)=="\""){
				cout<<"======================================== Output start ========================================"<<endl;
				cout<<cur_operater.substr(1,operate_name.length()-2);
				cout<<"======================================== Output ends ========================================"<<endl;
			}
			else if(operate_name=="endl"){
				cout<<"======================================== Output start ========================================"<<endl;
				cout<<endl;
				cout<<"======================================== Output ends ========================================"<<endl;
			}
			else {
				double reslut=operexpression(operate_name);
				cout<<"======================================== Output start ========================================"<<endl;
				cout<<reslut;
				cout<<"======================================== Output ends ========================================"<<endl;
			};
		}
		if(cur_keyword=="fin"){
			string cur_operater=cur_operate;
			while(cur_operater.find(",")!= string::npos){
				string operate_name=cur_operater.substr(1,cur_operater.find_first_of(",")-1);
				cout<<"operate_name :"<<operate_name<<endl;
				for(int i=1;i<=valuer_pos;i++){
					if(T[i].name==operate_name){
						switch(T[i].type){
							case Val_int:{
								cin>>T[i].forint;
								cout<<"have fin "<<operate_name<<" as "<<T[i].forint;
								break;
							}
							case Val_bool:{
								cin>>T[i].forbool;
								cout<<"have fin "<<operate_name<<" as "<<T[i].forbool;
								break;
							}
							case Val_double:{
								cin>>T[i].fordouble;
								cout<<"have fin "<<operate_name<<" as "<<T[i].fordouble;
								break;
							}
							case Val_string:{
								cin>>T[i].forstring;
								cout<<"have fin "<<operate_name<<" as "<<T[i].forstring;
								break;
							}
						}
						break;
					}
				}	
				cur_operater=cur_operater.substr(cur_operater.find_first_of(",")+1);
			}
			string operate_name=cur_operater;
			cout<<"operate_name "<<operate_name<<endl;
			for(int i=1;i<=valuer_pos;i++){
				if(T[i].name==operate_name){
					switch(T[i].type){
						case Val_int:{
							cin>>T[i].forint;
							cout<<"have fin "<<operate_name<<" as "<<T[i].forint;
							break;
						}
						case Val_bool:{
							cin>>T[i].forbool;
							cout<<"have fin "<<operate_name<<" as "<<T[i].forbool;
							break;
						}
						case Val_double:{
							cin>>T[i].fordouble;
							cout<<"have fin "<<operate_name<<" as "<<T[i].fordouble;
							break;
						}
						case Val_string:{
							cin>>T[i].forstring;
							cout<<"have fin "<<operate_name<<" as "<<T[i].forstring;
							break;
						}
					}
					break;
				}
			}	
		}
		if(cur_keyword=="return"){
			string value_name=cur_operate.substr(0,cur_operate.find_first_of(','));
			cout<<"return value_name "<<value_name<<endl;
			string value_tigh=cur_operate.substr(cur_operate.find_first_of(',')+1);
			for(int i=0;i<=userdefinefunc_pos;i++){
				if(K[i].name==value_name){
					switch(K[i].type){
						case Val_int:{
							K[i].returnint=operexpression(value_tigh);
							break;
						}
						case Val_bool:{
							K[i].returnbool=operexpression(value_tigh);
							break;
						}
						case Val_double:{
							K[i].returndouble=operexpression(value_tigh);
							break;
						}
						case Val_string:{
							K[i].returnstring=value_tigh.substr(1,value_tigh.length()-1);
							break;
						}
					}
					break;
				}
			}
			cout<<"function "<< value_name <<" returns :"<<value_tigh<<endl;			
			return_flag=true;
		}
		if(cur_keyword=="func"){
			userdefinefunc_pos++;
			string value_name=cur_operate.substr(0,cur_operate.find_first_of(','));
			K[userdefinefunc_pos].name=value_name;
			cout<<"value_name :"<<value_name<<endl;
			string value_tigh=cur_operate.substr(cur_operate.find_first_of(',')+1);
			cout<<"value_tigh :"<<value_tigh<<endl;
			if(value_tigh=="int"){
				K[userdefinefunc_pos].type=Val_int;
			}
			else if(value_tigh=="double"){
				K[userdefinefunc_pos].type=Val_double;
			}
			else if(value_tigh=="bool"){
				K[userdefinefunc_pos].type=Val_bool;
			}
			else if(value_tigh=="string"){
				K[userdefinefunc_pos].type=Val_string;
			}
			cout<<"type :"<<K[userdefinefunc_pos].type<<endl;
			string init_value = to_do.substr(1,find_pair(to_do,"(",")")-1);
			cout<<"init list: "<<init_value<<endl;
			to_do=to_do.substr(find_pair(to_do,"(",")"));
			string cur_do = to_do.substr(2,find_pair(to_do,"{","}")-2);
			K[userdefinefunc_pos].to_do=cur_do;
			cout<<"value to_do :"<<K[userdefinefunc_pos].to_do<<endl;
			to_do=to_do.substr(find_pair(to_do,"{","}")+1);
			string cur_operater=init_value;
			int valuer_num=1;
			while(cur_operater.find(",")!= string::npos){
				string operate_name=cur_operater.substr(0,cur_operater.find_first_of(","));
				cout<<"init "<<operate_name<<endl;
				if(operate_name.substr(0,3)=="int"){
					K[userdefinefunc_pos].init[valuer_num].name=cur_operater.substr(3,operate_name.length()-3);
					K[userdefinefunc_pos].init[valuer_num].type=Val_int;
				}
				else if(operate_name.substr(0,6)=="double"){
					K[userdefinefunc_pos].init[valuer_num].name=cur_operater.substr(6,operate_name.length()-6);
					K[userdefinefunc_pos].init[valuer_num].type=Val_double;
				}
				else if(operate_name.substr(0,4)=="bool"){
					K[userdefinefunc_pos].init[valuer_num].name=cur_operater.substr(4,operate_name.length()-4);
					K[userdefinefunc_pos].init[valuer_num].type=Val_bool;
				}
				else if(operate_name.substr(0,6)=="string"){
					K[userdefinefunc_pos].init[valuer_num].name=cur_operater.substr(6,operate_name.length()-6);
					K[userdefinefunc_pos].init[valuer_num].type=Val_string;
				}
				cur_operater=cur_operater.substr(cur_operater.find_first_of(",")+1);
				valuer_num++;
			}
			cout<<"single apramer"<<endl;
			string operate_name=cur_operater.substr(0,cur_operater.find_first_of(","));
			cout<<"init "<<operate_name<<endl;
			if(operate_name.substr(0,3)=="int"){
				K[userdefinefunc_pos].init[valuer_num].name=cur_operater.substr(3,operate_name.length()-3);
				K[userdefinefunc_pos].init[valuer_num].type=Val_int;
			}
			else if(operate_name.substr(0,6)=="double"){
				K[userdefinefunc_pos].init[valuer_num].name=cur_operater.substr(6,operate_name.length()-6);
				K[userdefinefunc_pos].init[valuer_num].type=Val_double;
			}
			else if(operate_name.substr(0,4)=="bool"){
				K[userdefinefunc_pos].init[valuer_num].name=cur_operater.substr(4,operate_name.length()-4);
				K[userdefinefunc_pos].init[valuer_num].type=Val_bool;
			}
			else if(operate_name.substr(0,6)=="string"){
				K[userdefinefunc_pos].init[valuer_num].name=cur_operater.substr(6,operate_name.length()-6);
				K[userdefinefunc_pos].init[valuer_num].type=Val_string;
			}
			K[userdefinefunc_pos].value_num=valuer_num;
			cout<<"func endl"<<endl;
			cout<<"to_do :"<<to_do<<endl;
		}
		if(cur_keyword=="break"){
			break_flag=true;
		}
		for(int k=1;k<=userdefinefunc_pos;k++){
			if(cur_keyword==K[k].name){
				cout<<K[k].name<<endl;
				cout<<"function to_do is "<<K[k].to_do<<endl;
				for(int i=1;i<=valuer_pos;i++){
					T_record[i].name=T[i].name;
					T_record[i].forint=T[i].forint;
					T_record[i].forstring=T[i].forstring;
					T_record[i].type=T[i].type;
					T_record[i].forbool=T[i].forbool;
					T_record[i].fordouble=T[i].fordouble;
				}
				int valuer_pos_old=valuer_pos;
				
				string cur_operater=cur_operate;
				for(int i=1;i<=K[k].value_num;i++){
					string operate_name;
					if(i==K[k].value_num)operate_name=cur_operater;
					else operate_name=cur_operater.substr(0,cur_operater.find_first_of(","));
					switch(K[k].init[i].type){
						case Val_int:{
							valuer_pos++;
							T[valuer_pos].name=K[k].init[i].name;
							T[valuer_pos].type=Val_int;
							T[valuer_pos].forint=operexpression(operate_name);
							cout<<" init "<<T[valuer_pos].name<<" = "<<T[valuer_pos].forint<<endl;
							break;
						}
						case Val_bool:{
							valuer_pos++;
							T[valuer_pos].name=K[k].init[i].name;
							T[valuer_pos].type=Val_bool;
							T[valuer_pos].forbool=operexpression(operate_name);
							cout<<" init "<<T[valuer_pos].name<<" = "<<T[valuer_pos].forbool<<endl;
							break;
						}
						case Val_double:{
							valuer_pos++;
							T[valuer_pos].name=K[k].init[i].name;
							T[valuer_pos].type=Val_double;
							T[valuer_pos].fordouble=operexpression(operate_name);
							cout<<" init "<<T[valuer_pos].name<<" = "<<T[valuer_pos].fordouble<<endl;
							break;
						}
						case Val_string:{
							valuer_pos++;
							T[valuer_pos].name=K[k].init[i].name;
							T[valuer_pos].type=Val_string;
							T[valuer_pos].forstring=operate_name.substr(1,operate_name.length()-1);
							cout<<" init "<<T[valuer_pos].name<<" = "<<T[valuer_pos].forstring<<endl;
							break;
						}
					}
					cur_operater=cur_operater.substr(cur_operater.find_first_of(",")+1);
				}
				actuator(K[k].to_do);
				return_flag=false;
				for(int i=1;i<=valuer_pos;i++){
					T[i].name=T_record[i].name;
					T[i].forint=T_record[i].forint;
					T[i].forstring=T_record[i].forstring;
					T[i].type=T_record[i].type;
					T[i].forbool=T_record[i].forbool;
					T[i].fordouble=T_record[i].fordouble;
				}
				valuer_pos=valuer_pos_old; 
				break;
			}
		}
	}
}