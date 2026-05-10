#include <iostream>
#include <string>
#include <filesystem> 
#include <unistd.h>//is the name of the header file that provides access to the POSIX operating system 

namespace fs = std::filesystem;

using namespace std;

void scan_directory(const fs::path& p,const string& str);

void echo(string str)
{
  str.erase(0,5);
  cout << str << "\n";
}
void type(string str) //Works fine.
{
  str.erase(0,5);
  string builtin [] = {"echo","exit","type"};
  for(string command : builtin)
  {
    if(command == str)
    {
      cout << command << " is a shell builtin" << "\n";
      return;
    }
  }
  cout << str << ": not found" << "\n";
}


void typeExtanded (string command) // Working progress
{
  command.erase(0,5);
  string builtin [] = {"echo","exit","type"};
  for(string builtincommand : builtin)
  {
    if(builtincommand == command)
    {
      cout << command << " is a shell builtin" << "\n";
      return;
    }
  }
  fs::path p = fs::current_path(); //static function thats why we can imedatly call it. No need to constract a specific object instance.
  scan_directory(p,command); // Now we check for files with the same name as the command.

}

bool executepermissions(const fs::path& p)
{
  return ::access(p.c_str(),X_OK) == 0;
  //C-string = old C style string: array/pointer of char ending with '\0' (null terminator).
  //X_OK is a flag meaning “check execute permission”.
}
 
void scan_directory(const fs::path& p,const string& command)
{
  if(is_directory(p))
  {
      for(const fs::directory_entry& x: fs::directory_iterator(p)){
        const fs::path& f = x;
        if(f.filename() == command && executepermissions(f))
        {
          cout << command << " is " << f.string() << '\n';
          return;
        }
           
        else{
          //string n = f.extension().string();
          //if(n== ".cpp" || n==".C" || ".cxx")
          //cout << f.stem() << "is a C++ source file TESTTESTTEST\n";
          //SkipL the file exists but lacks execute permissions, skip it and continue to the next directory.
        }
      }
      cout << command <<": not found\n";

  }
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
    if(command.substr(0,5)== "type ")
    {
      typeExtanded(command);
      continue;
    }
    cout << command << ": command not found" << "\n";
  }
  return 0;
}


/*
Commit: 
1. New Loop for the REPL , add echo command and complety replaced cin with getline do to the stream object tokens are based on space and not a newline. 
2. Implemented the type builtin for shell. Type - write a description of command type.
3. Extended the type builtin command to search for executable files using PATH.
4. Fix: The Extended the type builtin command to search for executable files 
*/

/*
The PATH environment variable specifies a list of directories where the shell should look for executable programs.
For example, if the PATH is set to /dir1:/dir2:/dir3, the shell would search for executables in /dir1, then /dir2, and finally /dir3, in that order.
*/