#include <list>
#include <typeinfo>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <iterator>
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
	  					string d;
	  
	  					for(char& t : this->a){
	    					string s(1,t);
	    					this->l1.push_back(s);
	    					if(ce > 0){
	      						d.append(s);
	    					}
	    					ce++;
	  					}

	  					this->a = d;
	  					this->l.push_back(this->l1);
	  					this->read_t();
	  				}

	  				if(c[4] == "L"){
	  					this->q = c[2];
	  					this->cinta.clear();
	  					string t = this->p_string;
	  					string e = "";

	  					if(this->p_string.empty()){
	  						this->p_string.append(this->desc["Blanco"]);
	  					}
	  					string s(1,this->p_string.at(0));
	  					if(s == this->desc["Blanco"]){
	  						this->cinta.push_back(this->desc["Blanco"]);
	  					}else{
	  						this->cinta.push_back(this->desc["Blanco"]);
	  						this->cinta.push_back(this->desc["Blanco"]);
	  					}
	  			
	  					for(int i = 0; i < this->p_string.length()-1; i++){
	  						string v(1,this->p_string.at(i));
	  						this->l1.push_back(v);
	  						this->cinta.push_back(v);
	  					}

	  					this->l1.push_back(this->q);
	  					string x(1,this->p_string.at(this->p_string.length()-1));
	  					this->l1.push_back(x);
	  					this->cinta.push_back(x);
	  					this->l1.push_back(c[3]);
	  					this->cinta.push_back(c[3]);

	  					for(char& ch : this->a){
	  						string y(1,ch);
	  						this->l1.push_back(y);
	  						this->cinta.push_back(y);
	  						e.append(y);
	  					}

	  					this->a.clear();
	  					this->a.append(c[3]);
	  					this->a.append(e);
	  					this->cinta.push_back(this->desc["Blanco"]);
	  					this->cinta.push_back(this->desc["Blanco"]);
	  					this->l.push_back(this->l1);
	  					string f;

	  					for(int i = 0; i<this->p_string.length()-1; i++){
	  						string g(1,this->p_string.at(i));
	  						f += g;
	  					}

	  					this->p_string = f;
	  					this->i -= 2;
	  					this->first_sym = this->cinta[this->i];
	  					this->read_t();

	  				}
	  			}
			}

		}
	  
		

  		bool check(){

    		for(vector<string> l : this->l){

      			for(string s : l){

      				for(string fin : this->desc["Finales"]){

      					if(s.find(fin) != string::npos){
      						return true;
      					}

      				}

      			}

    		}
    		return false;

  		}

  		vector<string> to_string(){

  			vector<string> l;
  			string c;

  			if(this->check()){
  				cout<<"La cadena " << this->str << " fué aceptada. Las configuraciones son:"<<endl;

  				for(vector<string> v : this->l){

  					for(string s : v){

  						if(find(this->desc["Estados"].begin(),this->desc["Estados"].end(),s) != this->desc["Estados"].end()){
  							c.append("|" + s + "|");
  						}else{
  							c.append(s);
  						}

  					}
  					l.push_back(c);
  					c.clear();
  				}

  			}else{
  				cout<<"La cadena "<< this->str << " no fué aceptada. Las configuraciones son:"<<endl;
  				for(vector<string> v : this->l){

  					for(string s : v){

  						if(find(this->desc["Estados"].begin(),this->desc["Estados"].end(),s) != this->desc["Estados"].end()){
  							c.append("|" + s + "|");
  						}else{
  							c.append(s);
  						}

  					}
  					l.push_back(c);
  					c.clear();
  				}
  			}

  			return l;

  		}
};

int main(int argc, char** argv){

	string f = argv[1];
  	string str = argv[2];
  	TM tm(f, str);
  	tm.write_string();
  	tm.read_t();
  	for(string s : tm.to_string()){
  		cout<< "-> " << s << endl;
  	}
  	return 0;

}
