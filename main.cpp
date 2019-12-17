#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
extern FILE *yyin;

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
	

	int inputs[I_header], outputs[O_header];

	//Primary Inputs
	for(int i=0; i<I_header; i++){
		getline(myfile,line);
		inputs[i] = atoi(line.c_str());
		cout << inputs[i] << endl;
	}
	
	//Primary Ouputs
	for (int i = 0; i < O_header; ++i)
	{
		getline(myfile,line);
		outputs[i] = atoi(line.c_str());
		cout << outputs[i] << endl;
	}

	//AIG Section
	for (int i = 0; i < A_header; ++i)
	{
		getline(myfile,line);
		std::vector<std::string> v;
   		std::istringstream buf(line);
    	for(std::string token; getline(buf, token, ' '); )
        	v.push_back(token);
    	copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "_token "));
    	std::cout << '\n';
    	
	}
}
