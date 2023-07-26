using namespace std;
#include <iostream>
#include "Xaffman.h"
#include "RLE.h"
#include "LZ78.h"
#include "BWT.h"
#include "MTF.h"
#include "Arif.h"

int main()
{

    ofstream output("out.txt");
    ifstream input; 
    input.open("txt.txt");
    string buf;
    string inp;
    string code;
    while (!input.eof()) {
        input >> buf;
        inp += buf;
    }
    inp.erase(inp.length()-1, 1);
    //cout << inp << endl;
    clock_t tStart = clock();

    /*HA
    code = HaffMan(inp);
    */
    /*AC
    code = Arifm(inp);
    */
    code = MTF(inp);
    output << code;

    /* BWT->MTF->HA
    code=BWT((char*)inp.c_str());
    code = MTF(code);
    code = HaffMan(code);
    output << code;
    */

    /*
    RLE->BWT->MTF->RLE->HA
    code = RLE(inp);
    code = BWT((char*)code.c_str());
    code = MTF(code);
    code = RLE(code);
    code = HaffMan(code);
    */
    
    
    /*BWT->MTF->AC
    code = BWT((char*)inp.c_str());
    code = MTF(code);
    code = Arifm(code);
    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    output << code;
    */
    


    return 0;
}
