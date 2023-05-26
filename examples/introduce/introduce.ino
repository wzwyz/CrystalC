#include "ArduinoSTL.h"
#include "stack"
#include"calculate.h"
#include"interpreter.h"
using namespace std;
void setup(){
  Serial.begin(9600);
  Interpreter prev;
	prev.initfunction();
  cout << "start." << endl;
	//freopen(argv[1],"r",stdin);
	string tolist;
	tolist=("int($c$,4)func(aser,int)(inta){return(aser,$a$+2)}int($b$,aser(3+$c$))while($b$<13){giver($b$,aser($b$))}fout($b$,endl)");
  
	//
  /*while($b$<13){giver($b$,aser($b$))}fout($b$,endl)
	while(true){
		string str;
		getline(cin,str);
		if(str.empty())break;
		for(int i=0;i<=str.length()-1;i++){
			if(str.substr(i,2)=="//"){
				str=str.substr(0,i);
				break;
			}
		}
		tolist.append(str);
	}
	bool quotation_flag=false;
	for(int i=0;i<=tolist.length();i++){
		if(tolist.substr(i,1)=="\""){
			if(quotation_flag==true)quotation_flag=false;
			else if(quotation_flag==false)quotation_flag=true;
		}
		if(quotation_flag==false&&tolist.substr(i,1)==" "){
			tolist.erase(i,1);
			i--;
		}
	}
	//cout<<tolist<<endl;*/
	 //
	/*string tolist;cin>>tolist;
	cout<<tolist<<endl;*/
	prev.actuator(tolist);
	cout<<prev.T[1].name<<" is "<<prev.T[1].forint<<endl;
	cout<<prev.T[2].name<<" is "<<prev.T[2].forint<<endl;
	//cout<<T[2].name<<" is "<<T[2].fordouble<<endl;
	return 0;
}
void loop(){

}