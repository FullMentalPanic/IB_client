#include "SymbolContracts.h"

#include <fstream>
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <iostream>

using namespace std;

SymbolContracts::SymbolContracts(string filename, int basetickID )
{
    read_csv(filename, basetickID);
}
SymbolContracts::SymbolContracts(string filename)
{
    read_csv(filename);
}
SymbolContracts::SymbolContracts()
{
    total = 0;
}
SymbolContracts::~SymbolContracts()
{
    contracts.clear();
    tickIDs.clear();
    BidSize.clear();
    AskSize.clear();
    BidPrice.clear();
    AskPrice.clear();
    LastPrice.clear();

    contracts.shrink_to_fit();
    tickIDs.shrink_to_fit();
    BidSize.shrink_to_fit();
    AskSize.shrink_to_fit();
    BidPrice.shrink_to_fit();
    AskPrice.shrink_to_fit();
    LastPrice.shrink_to_fit();


}

void SymbolContracts::DisplayContracts(){
    for (int i = 0; i < contracts.size(); i++)
        cout << tickIDs[i] << ':' << contracts[i].symbol << ' '<<contracts[i].secType << ' '<<contracts[i].currency << ' '<<contracts[i].exchange << ' '<<contracts[i].primaryExchange << ' '<< endl;
}

void SymbolContracts::DisplayPrice(){
    for (int i = 0; i < LastPrice.size(); i++)
        cout << i << ':' << LastPrice[i] << endl;
    
}

void SymbolContracts::read_csv(string filename, int basetickID){

    ifstream myFile(filename);
    if(!myFile.is_open()) throw runtime_error("Could not open file");
    string line, word;
    vector<string> colnames, row; 
    Contract temp;

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, line);
        // Create a stringstream from line
        stringstream ss(line);
        // Extract each column name
        while(getline(ss, word, ',')){
            colnames.push_back(word);
        }
    }

    int count = 0;
    while(getline(myFile, line))
    {
        // Create a stringstream of the current line
        stringstream ss(line);
        row.clear();
        while (getline(ss, word, ',')){
            row.push_back(word);
        }
        temp.symbol = row[0];
        temp.secType = row[1];
        temp.currency = row[2];
        temp.exchange = row[3];
        temp.primaryExchange = row[4];

        contracts.push_back(temp);
        tickIDs.push_back (count + basetickID);
        BidSize.push_back(0);
        AskSize.push_back(0);
        BidPrice.push_back(0.0);
        AskPrice.push_back(0.0);
        LastPrice.push_back(0.0);
        count++;
        
    }
    total = count; 
    // Close file
    myFile.close();

}
