#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

int main(int argc, char* argv[]){

    if(argc < 3){
        return 0;
    }

    //cout << argv[1] <<  " " <<  argv[2];

    string targetOutput = argv[2];
    string targetInput = argv[1];

    ofstream output;
    output.open(targetOutput);
    if(!output){
        cout << "Error opening output file" << endl;
        return 1;

    }
    ifstream input{targetInput};
    if(!input){
        cout << "Error opening input file" << endl;
        return 1;
    }

    string line;
    string currToken;
    int lineCount = 0;
    int cCount = 0;
    //varcount is the same as line count of the input file * 3
    int varCount = 0;
    int placeHolder = 0;
    //starting place for points
    char currPoint = 'a';

    //list of all finished lines of mini Sat to be written
    vector<string> pPhrases;

    while (getline(input, line)) {
        
        //add phrases for line variable
        int startVar = (lineCount *3) + 1;
        int var2 = startVar + 1;
        int var3 = startVar + 2;
        string phrase1 = "" + to_string(startVar);
        phrase1.append(" ");
        phrase1 += to_string(var2);
        phrase1.append(" ");
        phrase1 += to_string(var3);
        phrase1.append(" 0");
        

        string phrase2 = "-" + to_string(startVar);
        phrase2.append(" -");
        phrase2 += to_string(var2);
        phrase2.append(" 0");

        string phrase3 = "-" + to_string(startVar);
        phrase3.append(" -");
        phrase3 += to_string(var3);
        phrase3.append(" 0");

        string phrase4 = "-" + to_string(var2);
        phrase4.append(" -");
        phrase4 += to_string(var3);
        phrase4.append(" 0");

        pPhrases.push_back(phrase1);
        pPhrases.push_back(phrase2);
        pPhrases.push_back(phrase3);
        pPhrases.push_back(phrase4);
        //call the parser to seperate tokens by whitespace 
        stringstream inStream (line);
        while(inStream >> currToken){
            //add phrases for each connecting point
            
            //getting starting point for the connecting point
            char nextPoint = currToken[0];
            int nP1 = nextPoint - 'a';
            nP1 = (nP1 *3) + 1;
            int nP2 = nP1 + 1;
            int nP3 = nP2 + 1;
            phrase1 = "-" + to_string(startVar) + " -" + to_string(nP1) + " 0";
            phrase2 = "-" + to_string(var2) + " -" + to_string(nP2) + " 0";
            phrase3 = "-" + to_string(var3) + " -" + to_string(nP3) + " 0";
            pPhrases.push_back(phrase1);
            pPhrases.push_back(phrase2);
            pPhrases.push_back(phrase3);
        }

        
        lineCount++;
        cout << "line " << lineCount << ": " << line << endl;
        currPoint++;

    }
	//cout << tokenList.size() << endl;
    
    varCount = lineCount* 3;
    int size = pPhrases.size();

    //header of miniSat File
    output << "p cnf " << varCount << " " << size << endl;
    
    for (int i = 0; i < size; i++){
        output << pPhrases.at(i) << endl;

    }
	
	output.close();
}
