#include <iostream>
#include <string>
#include <filesystem> 
#include <cstdlib> // this for the getenv
#include <unistd.h>//is the name of the header file that provides access to the POSIX operating system 


//---------------------------------------- Can delete. Good if we want windows compatablity.
#ifdef _WIN32
#define PATH_LIST_SEPARATOR ';'
#else
#define PATH_LIST_SEPARATOR ':'
#endif
//---------------------------------------


namespace fs = std::filesystem;

using namespace std;

void scan_directory_old(const fs::path& p,const string& str);
bool scan_directory(const fs::path& p, const string& command);
bool executepermissions(const fs::path& p);


//Old functions:

void scan_directory_old(const fs::path& p,const string& command) // Old version: From the cpp book not for the type coomand.
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
          //currently nothing
        }
      }
  }
}
void type_old(string str) //Old version
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


void echo(string str)
{
  str.erase(0,5);
  cout << str << "\n";
}


void type (string command) // Working progress
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
  //understand this part and scan_directory
  const char* path_env = getenv("PATH");
  stringstream ss(path_env);
  string dir;
  while (getline(ss, dir, PATH_LIST_SEPARATOR)){ // Windows add Linux
    if (scan_directory(dir, command)) return;
  }

  cout << command <<": not found\n";
}

bool scan_directory(const fs::path& p, const string& command)
{
    fs::path full = p / command;
    if (fs::exists(full) && executepermissions(full))
    {
        cout << command << " is " << full.string() << '\n';
        return true;
    }
    return false;
}

bool executepermissions(const fs::path& p)
{
  return ::access(p.c_str(),X_OK) == 0;
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
      type(command);
      continue;
    }
    cout << command << ": command not found" << "\n";
  }
  return 0;
}


/*
Commits: 
1.  
*/

/*
Expalines:

*/