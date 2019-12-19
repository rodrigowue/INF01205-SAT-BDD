
#include <cstdlib>
#include <iostream>
#include "gerentebdd.h"
#include "parser.h"

using namespace std;

int main(int argc, char *argv[])
{

  system("clear");
    cout << "====================================================================" << endl;
    // cout << "Equivalence Checker using BDDs \n" << endl;

cout << " ▄▄▄       ██▓  ▄████ ▓█████  ██▀███         ▄▄▄▄   ▓█████▄ ▓█████▄ " << endl;
cout << "▒████▄    ▓██▒ ██▒ ▀█▒▓█   ▀ ▓██ ▒ ██▒      ▓█████▄ ▒██▀ ██▌▒██▀ ██▌" << endl;
cout << "▒██  ▀█▄  ▒██▒▒██░▄▄▄░▒███   ▓██ ░▄█ ▒      ▒██▒ ▄██░██   █▌░██   █▌" << endl;
cout << "░██▄▄▄▄██ ░██░░▓█  ██▓▒▓█  ▄ ▒██▀▀█▄        ▒██░█▀  ░▓█▄   ▌░▓█▄   ▌" << endl;
cout << " ▓█   ▓██▒░██░░▒▓███▀▒░▒████▒░██▓ ▒██▒      ░▓█  ▀█▓░▒████▓ ░▒████▓ " << endl;
cout << " ▒▒   ▓▒█░░▓   ░▒   ▒ ░░ ▒░ ░░ ▒▓ ░▒▓░      ░▒▓███▀▒ ▒▒▓  ▒  ▒▒▓  ▒ " << endl;
cout << "  ▒   ▒▒ ░ ▒ ░  ░   ░  ░ ░  ░  ░▒ ░ ▒░      ▒░▒   ░  ░ ▒  ▒  ░ ▒  ▒ " << endl;
cout << "  ░   ▒    ▒ ░░ ░   ░    ░     ░░   ░        ░    ░  ░ ░  ░  ░ ░  ░ " << endl;
cout << "      ░  ░ ░        ░    ░  ░   ░            ░         ░       ░    " << endl;
cout << "                                                  ░  ░       ░      " << endl;
cout << " ██▒   █▓▓█████  ██▀███   ██▓  █████▒██▓▓█████  ██▀███              " << endl;
cout << "▓██░   █▒▓█   ▀ ▓██ ▒ ██▒▓██▒▓██   ▒▓██▒▓█   ▀ ▓██ ▒ ██▒            " << endl;
cout << " ▓██  █▒░▒███   ▓██ ░▄█ ▒▒██▒▒████ ░▒██▒▒███   ▓██ ░▄█ ▒            " << endl;
cout << "  ▒██ █░░▒▓█  ▄ ▒██▀▀█▄  ░██░░▓█▒  ░░██░▒▓█  ▄ ▒██▀▀█▄              " << endl;
cout << "   ▒▀█░  ░▒████▒░██▓ ▒██▒░██░░▒█░   ░██░░▒████▒░██▓ ▒██▒            " << endl;
cout << "   ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░░▓   ▒ ░   ░▓  ░░ ▒░ ░░ ▒▓ ░▒▓░            " << endl;
cout << "   ░ ░░   ░ ░  ░  ░▒ ░ ▒░ ▒ ░ ░      ▒ ░ ░ ░  ░  ░▒ ░ ▒░            " << endl;
cout << "     ░░     ░     ░░   ░  ▒ ░ ░ ░    ▒ ░   ░     ░░   ░             " << endl;
cout << "      ░     ░  ░   ░      ░          ░     ░  ░   ░                 " << endl;
cout << "     ░                                                 " << endl;




    cout << "by: Rodolfo Viola, Rodrigo Franzoi, and Rodrigo Wuerdig" << endl;
    if (argc < 3 ){
        cout << "Insufficient agrtuments: ./bdd arg1.aag arg2.aag" << endl;
        return 0;
    }


    ifstream first_file(argv[1]);
    ifstream second_file(argv[2]);

    if (0==(first_file.is_open())){
        cout << "Cannot open file:" << argv[1] << endl;
        return 0;
    }

    if (0==(second_file.is_open())){
        cout << "Cannot open file:" << argv[2] << endl;
        return 0;
    }

    gerentebdd g;    
    set<string> conjunto_variaveis;
    string clause1,clause2;
    cout << "====================================================================" << endl;
    cout << "First File: " << (string) argv[1] << endl;
    //Fetches main clause from the first file
    clause1 = aiger_reader(first_file,65);
    cout << "CLAUSE 1:" << clause1 << endl;
    cout << "====================================================================" << endl;
    cout << "Second File: " << (string) argv[2] << endl;
    //Fetches main clause from the second file
    clause2 = aiger_reader(second_file,65);
    cout << "CLAUSE 2:" << clause2 << endl;
    // cout << "================================================================" << endl;
    // cout << clause1 << endl;
    // cout << clause2 << endl;
    string merged_clause, merged_clause2;
    cout << "====================================================================" << endl;


    merged_clause ="(!" + clause1 + "*!" + clause2 + "*!z)+(" + clause1 + "*" + clause2 + "*!z)+(" + clause1 + "*!" + clause2 + "*!z)+(!" + clause1 + "*" + clause2 + "*z)";
    merged_clause2="((!" + clause1 + "*!" + clause2 + "*!z)+(" + clause1 + "*" + clause2 + "*!z)+(" + clause1 + "*!" + clause2 + "*!z)+(!" + clause1 + "*" + clause2 + "*z))*(z)";
    cout << "Merged Clause:" << endl;
    cout << merged_clause << endl;

    nodobdd *nd1=g.create_from_equation(merged_clause, conjunto_variaveis);
    nodobdd *c=g.create_from_equation("z", conjunto_variaveis);
    nodobdd *nd2=g.cofactor(nd1, c, '+');
    //retrieves a constant zero
    nodobdd *nd4=g.getConstantZero();
    nodobdd *nd5=g.create_from_equation(merged_clause2, conjunto_variaveis);
    cout << "Constant zero address:" << nd4 << endl << "Added *(z) adress:" << nd5 << endl << "Co-factor Address:" << nd2 << endl;
    cout << "\033[0m----------------------------------------------------------------" << endl;
    if(nd2==nd4){
      cout << "Circuits are:" << endl;
      cout << "\033[5;32m▄▄▄ ..▄▄▄  ▄• ▄▌▪   ▌ ▐· ▄▄▄· ▄▄▌  ▄▄▄ . ▐ ▄ ▄▄▄▄▄" << endl;
      cout << "▀▄.▀·▐▀•▀█ █▪██▌██ ▪█·█▌▐█ ▀█ ██•  ▀▄.▀·•█▌▐█•██  " << endl;
      cout << "▐▀▀▪▄█▌·.█▌█▌▐█▌▐█·▐█▐█•▄█▀▀█ ██▪  ▐▀▀▪▄▐█▐▐▌ ▐█.▪" << endl;
      cout << "▐█▄▄▌▐█▪▄█·▐█▄█▌▐█▌ ███ ▐█ ▪▐▌▐█▌▐▌▐█▄▄▌██▐█▌ ▐█▌·" << endl;
      cout << " ▀▀▀ ·▀▀█.  ▀▀▀ ▀▀▀. ▀   ▀  ▀ .▀▀▀  ▀▀▀ ▀▀ █▪ ▀▀▀ " << endl;

    }
    else{
      cout << "Circuits are:" << endl;
      cout << "\033[5;31m·▄▄▄▄  ▪  ·▄▄▄·▄▄▄▄▄▄ .▄▄▄  ▄▄▄ . ▐ ▄ ▄▄▄▄▄" << endl;
      cout << "██▪ ██ ██ ▐▄▄·▐▄▄·▀▄.▀·▀▄ █·▀▄.▀·•█▌▐█•██  " << endl;
      cout << "▐█· ▐█▌▐█·██▪ ██▪ ▐▀▀▪▄▐▀▀▄ ▐▀▀▪▄▐█▐▐▌ ▐█.▪" << endl;
      cout << "██. ██ ▐█▌██▌.██▌.▐█▄▄▌▐█•█▌▐█▄▄▌██▐█▌ ▐█▌·" << endl;
      cout << "▀▀▀▀▀• ▀▀▀▀▀▀ ▀▀▀  ▀▀▀ .▀  ▀ ▀▀▀ ▀▀ █▪ ▀▀▀       " << endl;
    }
    cout << "\033[0m----------------------------------------------------------------" << endl;
    // printf("%d",*nd2->getConstantZero()); 
    return EXIT_SUCCESS;
}
