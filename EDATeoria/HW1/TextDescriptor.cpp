#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include<bits/stdc++.h> 
#include <dirent.h>
using namespace std;

void print_vec_string(vector<string> doc){
	for (int i = 0; i < doc.size(); i++){
		cout<<doc[i]<<endl;
	}
}

void print_vec_dic(vector<string> dic){
	for (int i = 0; i < dic.size(); i++){
		cout<<dic[i]<<" - ";
	}
	cout<<""<<endl;
}

void print_vec_int(vector<int> vec){
	for (int i = 0; i < vec.size(); i++){
		cout<<vec[i]<<" - ";
	}
	cout<<""<<endl;
}

string safeVC(vector<int> vc){
	string tempo;
	for (int i = 0; i < vc.size(); i++){
		tempo=tempo+to_string(vc[i])+" - ";
	}
	return tempo;
}

vector<string> clean_document(vector<string> doc, vector<string> stopw, vector<string> punct){
	string delim=" ";
	string temporal;
	for (int i = 0; i < doc.size(); i++){
		for (int k = 0; k < punct.size(); k++){
			boost::erase_all(doc[i], punct[k]);
		}
		for (int j = 0; j < stopw.size(); j++){
			boost::to_lower(doc[i]);

			string word;
			stringstream iss(doc[i]);
		    while (iss >> word){
		    	boost::erase_all(word," ");
		    	if (stopw[j]==word)
		    	{
		    		boost::erase_all(word, stopw[j]);
		    	}
		    	if (word.size()!=0)
		    	{
		    		temporal=temporal+word+delim;
		    	}
		    }
		    doc[i]=temporal;
		    temporal.clear();
		}
	}
	//print_doc(doc);
	return doc;
}

vector<string> genDic(vector<string> doc,vector<string> dictionary){
	int cont=0;
	for (int i = 0; i < doc.size(); i++){
		string word;
		stringstream iss(doc[i]);
		while (iss >> word){
			for (int j = 0; j < dictionary.size(); j++){
				if (word==dictionary[j]){
					cont++;
				}
			}
			if (cont==0){
				dictionary.push_back(word);
			}
			cont=0;
		}
	}
	return dictionary;
}

int get_pos(string word,vector<string> dictionary){
	for (int i = 0; i < dictionary.size(); i++)
	{
		if (word==dictionary[i])
		{
			return i;
		}
	}
}

vector<int> genVC(vector<string> doc, vector<string>dictionary, vector<int>VC){
	int tempo;
	for (int i = 0; i < dictionary.size(); i++){
		VC.push_back(0);
	}
	for (int i = 0; i < doc.size(); ++i)
	{
		string word;
		stringstream iss(doc[i]);
		while (iss >> word){
			tempo=get_pos(word,dictionary);
			VC[tempo]++;
		}
	}
	return VC;
}

int main() 
{
	string line; 

	vector<string> StopWords;
    ifstream readfile("stopwords.txt");
    if (readfile.is_open()){
    	while(getline(readfile,line)){
    		StopWords.push_back(line);
    	}
    	readfile.close();
    }

    vector<string> PunctuationList;
    ifstream readfile2("Punctuation.txt");
    if (readfile2.is_open()){
    	while(getline(readfile2,line)){
    		PunctuationList.push_back(line);
    	}
    	readfile2.close();
    }
    //A B C R
    vector<string> Letters;
    Letters.push_back("A");
    Letters.push_back("B");
    Letters.push_back("C");
    Letters.push_back("R");
    vector<string> dictionary;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("/home/fabrizio/Desktop/GitHubRepos/EDA/EDA-2019-01/EDATeoria/HW1/files")) != NULL) {
    	while ((ent = readdir (dir)) != NULL) {
    		string docname=ent->d_name;
            vector<string> document;
            cout<<"docname: "<<docname<<endl;
            ifstream readfile3(docname);
		    if (readfile3.is_open()){
		    	while(getline(readfile3,line)){
		    		document.push_back(line);
		    	}
		    	readfile3.close();
		    }
		    //cout<<"files: "<<endl;
		    //print_vec_string(document);
		    document=clean_document(document,StopWords,PunctuationList);
		    dictionary = genDic(document,dictionary);

        }
        closedir (dir);
    } else {
        perror ("");
    	return EXIT_FAILURE;
    }
    cout<<"print dic"<<endl;
    print_vec_dic(dictionary);
/////////////////////////////////////////////////////////////////
	vector<string> ListOfVC;
    if ((dir = opendir ("/home/fabrizio/Desktop/GitHubRepos/EDA/EDA-2019-01/EDATeoria/HW1/files")) != NULL) {
    	while ((ent = readdir (dir)) != NULL) {
	    	//printf ("%s\n", ent->d_name);
	    	vector<string> document;
		    ifstream readfile3(ent->d_name);
		    if (readfile3.is_open()){
		    	while(getline(readfile3,line)){
		    		document.push_back(line);
		    	}
		    	readfile3.close();
		    }
		    vector<int> VC;
			VC=genVC(document,dictionary,VC);
			string tempoVC=safeVC(VC);
			ListOfVC.push_back(tempoVC);
		}
		closedir (dir);
	} else {
		perror ("");
	  	return EXIT_FAILURE;
	}




    //lista de stop words guardada en el vector StopWords
    //lista de Punctuation guardada en el vector PunctuationList

    //leer un documento test para probar el borrado de signos de puntuacion y stop words
    //falta hacerlo con multiples text files

    /*cout<<"----------------original file---------------------"<<endl;
    
    vector<string> document;
    ifstream readfile3("test.txt");
    if (readfile3.is_open()){
    	while(getline(readfile3,line)){
    		document.push_back(line);
    	}
    	readfile3.close();
    }
    document=clean_document(document,StopWords,PunctuationList);
*/
/*	cout<<"---------------dictionary print--------------- "<<endl;
	vector<string> dictionary;
	dictionary = genDic(document,dictionary);
	print_vec_dic(dictionary);*/
	/*cout<<"-----------------VC print------------------- "<<endl;
	vector<int> VC; // modificar a matriz
	VC=genVC(document,dictionary,VC);
	print_vec_int(VC);*/
/*	string tempoVC=safeVC(VC);

	vector<string> ListOfVC;

	for (int i = 0; i < 1; i++)
	{
		ListOfVC.push_back(tempoVC);
	}
*/
	ofstream VCFile;
	VCFile.open("VCFile.txt");
	for (int i = 0; i < ListOfVC.size(); i++)
	{
		VCFile << ListOfVC[i] << endl;
	}

}