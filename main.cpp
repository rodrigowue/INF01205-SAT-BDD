#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#define SIZE_POINTERS 50

using namespace std;
extern FILE *yyin;

struct node {
    int id;
    struct node *pointing[SIZE_POINTERS];
};
struct node* newNode(int data);
void printNode(struct node *root);

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
    	char qualquer[255];
    	int number=0;
    	if (atoi(v[0].c_str())%2==0)
    	{
    		number=(atoi(v[0].c_str()))/2;	
    		sprintf(qualquer,"%c",number+'A');
    	}
    	else{
    		number=(atoi(v[0].c_str())-1)/2;
    		sprintf(qualquer,"%c",number+'a');
    		// strcpy(qualquer,itoa(number+32));	
    	}
    	cout << qualquer << "=(";
    	for (int j = 1; j < (v.end() - v.begin()); ++j)
    	{
    		// cout << atoi(v[j].c_str()) << endl;
    		if (atoi(v[j].c_str())%2==0)
    		{	
    		number=(atoi(v[j].c_str()))/2;	
    		sprintf(qualquer,"%c",number+'A');
    		}
    		else{
    		number=(atoi(v[j].c_str())-1)/2;
    		sprintf(qualquer,"%c",number+'a');
    		// strcpy(qualquer,itoa(number+32));	
    		}
    		
    		if(j!=(v.end() - v.begin())-1){
    		cout << qualquer << "+";	
    		}
    		else{
    		cout << qualquer << "";		
    		}
    	}
    	cout << ")" << endl;
    	
	}

        struct node *root = newNode(1);
        root->pointing[0]       = newNode(2);
        root->pointing[1]       = newNode(3);
        root->pointing[2]       = newNode(4);
        root->pointing[3]       = newNode(5);

        root->pointing[0]->pointing[0] = newNode(5);

        printNode(root->pointing[0]);
}

struct node* newNode(int data){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->id = data;
    for(int i = 0; i < SIZE_POINTERS; i++){
        node->pointing[i] = NULL;
    }
    return(node);
}

void printNode(struct node *root) {
    printf("%d --> ", root->id);
    for(int i = 0; i < SIZE_POINTERS; i++){
        if(root->pointing[i] != (void *) NULL){
            printf("%d ", root->pointing[i]->id);
        }
    }
    printf("\n");
}
