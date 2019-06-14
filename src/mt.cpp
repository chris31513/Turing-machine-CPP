#include <list>
#include <typeinfo>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <iterator>
#include <boost/range/irange.hpp>
using namespace std;
using json = nlohmann::json;

class TM{
  
private:
  
  string str;
  json desc;
  vector<string> cinta;
  vector<vector<string>> trans;
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

  void showlist(list <string> g) { 
    list <string> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n'; 
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
    
    for(vector<string> c : this->desc["Transiciones"]){
      this->trans.push_back(c);
    }
    
    this->first_sym = this->cinta[2];

    this->i = 2;
    
  }

  void read_t(){
    this->l1.clear();
    this->i++;

    for(vector<string> c : this->trans){

      if(this->q == c[0] && this->first_sym == c[1]){

	if(c[4] == "R"){
	  this->q = c[2];
	  this->first_sym = this->cinta[this->i];
	  this->p_string.append(c[3]);
	  int ce = 0;

	  for(char& t : this->p_string){
	    string s(1,t);
	    this->l1.push_back(s);
	  }

	  this->l1.push_back(this->q);
	  string e = "";
	  
	  for(char& t : this->a){
	    string s(1,t);
	    this->l1.push_back(s);
	    if(ce > 0){
	      e.append(s);
	    }
	    ce++;
	  }
	  this->a = e;
	  this->l.push_back(this->l1);
	  this->read_t();
	  
	}

	if(c[4] == "L"){
	  this->q = c[2];
	  this->cinta.clear();

	  string e = "";
	  string r(1,this->p_string.at(0));
	  if(this->p_string.empty())
	    this->p_string.append(this->desc["Blanco"]);

	  if(r == this->desc["Blanco"]){
	    this->cinta.push_back(this->desc["Blanco"]);
	   
	  }else{
	    this->cinta.push_back(this->desc["Blanco"]);
	    this->cinta.push_back(this->desc["Blanco"]);
	    
	  }
	  for(int x = 0; x < this->p_string.length()-1; x++){
	    string v(1,this->p_string.at(x));
	    this->l1.push_back(v);
	    this->cinta.push_back(v);
	  }
	  
	  string y(1, this->p_string.at(this->p_string.length()-1));
	  this->l1.push_back(this->q);
	  this->l1.push_back(y);
	  this->cinta.push_back(y);
	  this->l1.push_back(c[3]);
	  this->cinta.push_back(c[3]);

	  for(char& o : this->a){
	    string t(1,o);
	    this->l1.push_back(t);
	    this->cinta.push_back(t);
	    e.append(t);
	  }

	  this->a.clear();
	  this->a.append(c[3]);
	  this->a.append(e);
	  this->cinta.push_back(this->desc["Blanco"]);
	  this->cinta.push_back(this->desc["Blanco"]);
	  this->l.push_back(this->l1);

	  string u = "";
	  for(int i = 0; i < this->p_string.length()-2; i++){
	    string p(1,this->p_string.at(i));
	    u.append(p);
	  }
	  this->p_string = u;
	  this->first_sym = this->cinta[this->i-2];
	  this->i = this->i-2;
	  this->read_t();
	}
      }
      
    }
    
  }

  void check(){
    for(vector<string> l : this->l){
      for(string s : l){
	cout<<s;
      }
      cout<<"\n";
    }

  }
};

int main(int argc, char** argv){
  string f = argv[1];
  string str = argv[2];
  TM tm(f, str);
  tm.write_string();
  tm.read_t();
  tm.check();
  return 0;
}
