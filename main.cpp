#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <bits/stdc++.h>
#define SIZE_POINTERS 50

using namespace std;
extern FILE *yyin;

string create_clause_final(string clauses, char dic[3][255], int dic_size);

int main(int argc, char** argv)
	{
	string line;
	char delim[]=" ";
	if (argc < 1 ){
		cout << "call: ./main [*].aig" << endl;
	}
	ifstream myfile (argv[1]);

	if (0==(myfile.is_open())){
		cout << "Cannot open file:" << argv[1] << endl;
	}

	getline(myfile,line);
	std::vector<std::string> v;
        std::istringstream buf(line);
        for(std::string token; getline(buf, token, ' '); )
                 v.push_back(token);
        copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "_token "));
        std::cout << '\n';
	//check if header information (MILOA) is alright
    int M_header = atoi(v[1].c_str());
    int I_header = atoi(v[2].c_str());
    int L_header = atoi(v[3].c_str());
    int O_header = atoi(v[4].c_str());
    int A_header = atoi(v[5].c_str());
	cout << "Header Info: "               << endl;
	cout << "M (maximum variable index):" << v[1] << endl;
	cout << "I (number of inputs):"       << v[2] << endl;
	cout << "L (number of latches):"      << v[3] << endl;
	cout << "O (number of outputs):"      << v[4] << endl;
	cout << "A (number of AND gates):"    << v[5] << endl;
	cout << "----------------------------" << endl;
	cout << "Verifying if M=I+L+A" << endl;
	if (M_header!=I_header+L_header+A_header){
		cout << "ERROR: Invalid! M != I+L+A" << endl;
		exit(-1);
	}
	

	int inputs_ID[I_header], outputs_ID[O_header];

	//Primary Inputs
	for(int i=0; i<I_header; i++){
		getline(myfile,line);
		inputs_ID[i] = (atoi(line.c_str()))/2;
		cout << atoi(line.c_str()) << " //ID:" << inputs_ID[i] << endl;
	}
	
	//Primary Ouputs
	for (int i = 0; i < O_header; ++i)
	{
		getline(myfile,line);
		outputs_ID[i] = (atoi(line.c_str()))/2;
		cout << atoi(line.c_str()) << " //ID:" << outputs_ID[i] << endl;
	}


	char clauses [A_header][255]= {};
	
	//AIG Section
	for (int i = 0; i < A_header; ++i)
	{
		int abobrinha=0;
		getline(myfile,line);
		std::vector<std::string> v;
   		std::istringstream buf(line);
    	for(std::string token; getline(buf, token, ' '); )
        	v.push_back(token);
    	copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "_token "));
    	std::cout << '\n';
    	char qualquer[255];
    	int number=0;
    	if (atoi(v[0].c_str())%2==0)
    	{
    		number=(atoi(v[0].c_str()))/2;	
    		sprintf(qualquer,"%c",number+'A');
    		clauses[i][abobrinha]=qualquer[0];
    		abobrinha++;
    	}
    	else{
    		number=(atoi(v[0].c_str())-1)/2;
    		sprintf(qualquer,"%c",number+'A');
    		clauses[i][abobrinha]='!';
    		abobrinha++;
    		clauses[i][abobrinha]=qualquer[0];
    		abobrinha++;	
    	}
    	cout << qualquer << "=(";

    	clauses[i][abobrinha]='=';
    	abobrinha++;
    	clauses[i][abobrinha]='(';
    	abobrinha++;


    	for (int j = 1; j < (v.end() - v.begin()); ++j)
    	{
    		// cout << atoi(v[j].c_str()) << endl;
    		if (atoi(v[j].c_str())%2==0)
    		{	
    		number=(atoi(v[j].c_str()))/2;	
    		sprintf(qualquer,"%c",number+'A');
    		clauses[i][abobrinha]=qualquer[0];
    		abobrinha++;
    		}
    		else{
    		number=(atoi(v[j].c_str())-1)/2;
    		sprintf(qualquer,"%c",number+'A');
    		clauses[i][abobrinha]='!';
    		abobrinha++;
    		clauses[i][abobrinha]=qualquer[0];
    		abobrinha++;
    		}
    		
    		if(j!=(v.end() - v.begin())-1){
    		cout << qualquer << "+";
    		clauses[i][abobrinha]='+';
    		abobrinha++;
    		}
    		else{
    		cout << qualquer << "";		
    		}
    	}
    	cout << ")" << endl;
    	clauses[i][abobrinha]=')';
	}
	cout << "==================================" << endl;
	cout << "clauses:" << endl;
	for (int i = 0; i < A_header; ++i)
	{
		cout << clauses[i] << endl;
	}
	cout << "-----------------------------------" << endl;
	string last_clause = string(clauses[A_header-1]);
	string final = create_clause_final(last_clause, clauses, A_header);

	cout << "==================================" << endl;
	cout << "Final Clause:" << endl;
	cout << final << endl;



}

string create_clause_final(string clauses, char dic[3][255], int dic_size){
	string str;//<< clauses.at(0) << clauses.at(1);
	for(int i=2;i<clauses.length(); i++){
		if(clauses.at(i) >= 'A' && clauses.at(i) <= 'Z'){
			cout << "achei: " << clauses.at(i) << endl;
				//search_tokens
				int index=0;
				int found=0;
				int found_index=0;
				while(index<dic_size)
				{
					if (clauses.at(i) == dic[index][0])
					{
						found_index=index;
						found=1;
					}
					index++;
				}

				if(found==1){
					cout << dic[found_index] << endl;
					string new_clause = create_clause_final(string(dic[found_index]), dic, dic_size-2);
					cout << "new clause inserted: " << new_clause <<  endl;
					str += new_clause;
				} else {
					str += clauses.at(i);
				}
		} else {
			str += clauses.at(i);
		}
	}
	return str;
}