#include <iostream>
#include <string>

using namespace std;
//using std::cout;
//using std::cin;


void echo(string str)
{
  //std::string out = str;
  str.erase(0,5);
  cout << str << "\n";
}

int main() {
  // Flush after every std::cout / std:cerr - flush means the buffer (like a waiter) is seding the string (wiater delevers the food from the kichen) 
  cout << unitbuf;
  cerr << unitbuf;
  string command="";
  while(cout << "$ " && getline(cin,command) && command != "exit") 
  {
    if(command.substr(0,5) == "echo ")
    {
      echo(command);
      continue;
    }
    cout << command << ": command not found" << "\n";
  }
  return 0;
}


/*
Commit: 
New Loop for the REPL , add echo command and complety replaced cin with getline do to the stream object tokens are based on space and not a newline. 
*/