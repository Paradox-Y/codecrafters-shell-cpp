#include <iostream>
#include <string>

using std::cout;
using std::cin;

int main() {
  // Flush after every std::cout / std:cerr  UNDERSTAND THIS
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;


  std::string command="";
  while(true)
  {
    cout << "$ ";
    cin >> command;
    if(command == "exit")
      return 0;
    cout << command << ": command not found" << "\n";
  }

}
