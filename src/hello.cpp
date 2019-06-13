#include <typeinfo>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
using json = nlohmann::json;

class TM{
  
private:
  
  string str;
  json desc;
  vector<string> cinta;
  vector<string> trans;
  string q;
  string first_sym;
  vector<vector<string>> l;
  vector<string> l1;
  string a;
  string p_string;
  int i;
  
public:

  TM(string file, string str){
    try{
      
      this->str = str;
      ifstream f(file);
      this->desc = json::parse(f);
      
    }catch(const std::exception& ex){
      
      cout << "Error, check the arguments\n";
      
    }
  }

  void write_string(){
    this->cinta.push_back(this->desc["Blanco"]);
    this->cinta.push_back(this->desc["Blanco"]);
    this->q = this->desc["Inicial"];
    int ce = 0;
    this->l1.push_back(this->q);
    
    for(char& c : this->str){
      string s(1,c);
      this->cinta.push_back(s);
      this->l1.push_back(s);
      
      if(ce > 0){

	this->a.append(s);
	
      }
      
      ce++;
    }

    this->l.push_back(this->l1);
    this->cinta.push_back(this->desc["Blanco"]);
    this->cinta.push_back(this->desc["Blanco"]);
    this->cinta.push_back(this->desc["Blanco"]);
    
    for(string c : this->desc["Transiciones"][0]){
      this->trans.push_back(c);
    }
    
    this->first_sym = this->cinta[2];

    this->i = 2;
    
  }

};

int main(int argc, char** argv){
  string f = argv[1];
  string str = argv[2];
  TM tm(f, str);
  tm.write_string();
  return 0;
}
