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

string safeVC(vector<int> vc, string namefile){
	string tempo;
	tempo=tempo+namefile+": ";
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
	//creacion de vector con la lista de stop words
	vector<string> StopWords;
    ifstream readfile("stopwords.txt");
    if (readfile.is_open()){
    	while(getline(readfile,line)){
    		StopWords.push_back(line);
    	}
    	readfile.close();
    }
    //creacion de vector con lista de signos de puntuacion
    vector<string> PunctuationList;
    ifstream readfile2("Punctuation.txt");
    if (readfile2.is_open()){
    	while(getline(readfile2,line)){
    		PunctuationList.push_back(line);
    	}
    	readfile2.close();
    }

    vector<string> dictionary; //vector que contendra la lista de palabras
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("/home/fabrizio/Desktop/GitHubRepos/EDA/EDA-2019-01/EDATeoria/HW1/files")) != NULL) {
    	while ((ent = readdir (dir)) != NULL) {
    		string docname=ent->d_name;
            vector<string> document;
            ifstream readfile3(docname);
		    if (readfile3.is_open()){
		    	while(getline(readfile3,line)){
		    		document.push_back(line);
		    	}
		    	readfile3.close();
		    }
		    document=clean_document(document,StopWords,PunctuationList);
		    dictionary = genDic(document,dictionary);
        }
        closedir (dir);
    } else {
        perror ("");
    	return EXIT_FAILURE;
    }
    //Generacion de un txt con la lista de palabras en el diccionario
    ofstream DiccFile;
	DiccFile.open("DiccFile.txt");

	for (int i = 0; i < dictionary.size(); i++){
		DiccFile<<dictionary[i]<<" - ";
	}
	DiccFile.close();

/////////////////////////////////////////////////////////////////
	vector<string> ListOfVC;
    if ((dir = opendir ("/home/fabrizio/Desktop/GitHubRepos/EDA/EDA-2019-01/EDATeoria/HW1/files")) != NULL) {
    	while ((ent = readdir (dir)) != NULL) {
	    	vector<string> document;
	    	string docname=ent->d_name;
	    	if (docname.size()>3)
	    	{
			    ifstream readfile3(docname);
			    if (readfile3.is_open()){
			    	while(getline(readfile3,line)){
			    		document.push_back(line);
			    	}
			    	readfile3.close();
			    }
			}
		    //documento guardado
		    document=clean_document(document,StopWords,PunctuationList);
		    vector<int> VC;
			VC=genVC(document,dictionary,VC);
			string tempoVC=safeVC(VC, ent->d_name);
			ListOfVC.push_back(tempoVC);
		}
		closedir (dir);
	} else {
		perror ("");
	  	return EXIT_FAILURE;
	}
	ofstream VCFile;
	VCFile.open("VCFile.txt");
	for (int i = 0; i < ListOfVC.size(); i++)
	{
		VCFile << ListOfVC[i] << endl;
	}

}