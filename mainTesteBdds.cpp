
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
    cout << "================================================================" << endl;
    cout << "First File:" << endl;
    //Fetches main clause from the first file
    ifstream first_file("xor_um.aag");
    clause1 = aiger_reader(first_file,65);
    cout << "================================================================" << endl;
    cout << "Second File:" << endl;
    //Fetches main clause from the second file
    ifstream second_file("xor_dois.aag");
    clause2 = aiger_reader(second_file,65);
    cout << "================================================================" << endl;
    cout << clause1 << endl;
    cout << clause2 << endl;
    string merged_clause, merged_clause2;
    cout << "================================================================" << endl;


    merged_clause ="(!" + clause1 + "*!" + clause2 + "*!z)+(" + clause1 + "*" + clause2 + "*!z)+(" + clause1 + "*!" + clause2 + "*!z)+(!" + clause1 + "*" + clause2 + "*z)";
    merged_clause2="((!" + clause1 + "*!" + clause2 + "*!z)+(" + clause1 + "*" + clause2 + "*!z)+(" + clause1 + "*!" + clause2 + "*!z)+(!" + clause1 + "*" + clause2 + "*z))*(z)";
    cout << merged_clause << endl;

    nodobdd *nd1=g.create_from_equation(merged_clause, conjunto_variaveis);
    nodobdd *c=g.create_from_equation("z", conjunto_variaveis);
    nodobdd *nd2=g.cofactor(nd1, c, '+');
    //retrieves a constant zero
    nodobdd *nd4=g.getConstantZero();
    nodobdd *nd5=g.create_from_equation(merged_clause2, conjunto_variaveis);
    cout << "0=" << nd4 << endl << "Deve ser 0:" << nd5 << endl << "co-fator:" << nd2 << endl;
    cout << "----------------------------------------------------------------" << endl;
    if(nd2==nd4){
      cout << "Circuits are equivalent! :)" << endl;
    }
    else{
      cout << "Circuits are different! :(" << endl;
    }
    // printf("%d",*nd2->getConstantZero()); 
    return EXIT_SUCCESS;
}
