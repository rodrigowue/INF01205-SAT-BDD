#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
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
	cout << "Header Info: "               << endl;
	cout << "M (maximum variable index):" << v[1] << endl;
	cout << "I (number of inputs):"       << v[2] << endl;
	cout << "L (number of latches):"      << v[3] << endl;
	cout << "O (number of outputs):"      << v[4] << endl;
	cout << "A (number of AND gates):"    << v[5] << endl;
	cout << "----------------------------" << endl;
	cout << "Verifying if M=I+L+A" << endl;
	if (int(v[1])!=int(v[2])+int(v[3])+int(v[5])){
		cout << "ERROR: Invalid! M != I+L+A" << endl;
		exit(-1);
	}


	while(getline(myfile,line))
	{
	std::vector<std::string> v;
   	std::istringstream buf(line);
    	for(std::string token; getline(buf, token, ','); )
        	v.push_back(token);
    	copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "_token "));
    	std::cout << '\n';
	}
}
