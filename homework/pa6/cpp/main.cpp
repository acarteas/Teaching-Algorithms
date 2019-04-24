#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "StringSplitter.h"
using namespace std;

void encodeFile(string file_name)
{
}

void decodeFile(string file_name)
{
}

int main(int argc, char* argv[])
{
   if (argc != 3)
   {
      cout << "Expected format: PA6.exe <encode / decode> <file_name>" << endl;
      return 0;
   }

   if (string{ argv[1] } == "encode")
   {
      //encode ABC.txt to ABC.txt.coded
      encodeFile(string{ argv[2] });

      cout << "File encoded." << endl;
   }
   else if (string{ argv[1] } == "decode")
   {
      //decode ABC.txt.coded to ABC.decoded.txt
      decodeFile(string{ argv[2] });
      cout << "File decoded." << endl;
   }
   else
   {
      cout << "Unexpected command." << endl;
   }

}