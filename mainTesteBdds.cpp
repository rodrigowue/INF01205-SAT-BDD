
#include <cstdlib>
#include <iostream>
#include "gerentebdd.h"
#include "parser.h"

using namespace std;

int main(int argc, char *argv[])
{
    gerentebdd g;    
    set<string> conjunto_variaveis;
    string clause1,clause2;
    //Fetches main clause from the first file
    ifstream first_file("xor_um.aag");
    clause1 = aiger_reader(first_file);
    //Fetches main clause from the second file
    ifstream second_file("xor_dois.aag");
    clause2 = aiger_reader(second_file);
    cout << "-----------------------------------------" << endl;
    cout << clause1 << endl;
    cout << clause2 << endl;
    nodobdd *nd1=g.create_from_equation(clause1, conjunto_variaveis);
    nodobdd *nd2=g.create_from_equation(clause1, conjunto_variaveis);
    nodobdd *c=g.create_from_equation("c", conjunto_variaveis);
    nodobdd *nd3=g.cofactor(nd1, c, '+');
    nodobdd *nd4=g.cofactor(nd2, c, '-');
    if (nd3==nd4)
       {
       cout<<"seems to work"<<endl;
       }
    system("PAUSE");
    return EXIT_SUCCESS;
}
