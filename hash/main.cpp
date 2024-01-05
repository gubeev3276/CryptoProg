#include <iostream>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
 
using namespace std;
int main(){
	ifstream mfile;            
	string str;
	string strs="";
	string file = "Hashing";  
	mfile.open(file);          
	while (!mfile.eof()) {     
		getline(mfile, str);    // считываем строку
		strs = strs+str;        
	}
	cout <<"Text from file: "<<strs;
	string hashs;
	CryptoPP::Weak1::MD5 hashmd4;  
	CryptoPP::StringSource(strs, true, new CryptoPP::HashFilter(hashmd4,new CryptoPP::HexEncoder(new CryptoPP::StringSink(hashs)))); 
	cout << endl<<"Hash: "<<hashs<<endl; 
	
	//Проверка
	string test_str = "Kakoy to text";
	string test_hash;
	cout<<endl<<"Test text: "<<test_str<<endl;
	CryptoPP::Weak1::MD5 hashmd4_test;  
	CryptoPP::StringSource(test_str, true, new CryptoPP::HashFilter(hashmd4_test,new CryptoPP::HexEncoder(new 			CryptoPP::StringSink(test_hash))));
	cout<<"Hash: "<<test_hash<<endl;
	
}
