#include <iostream>
#include <string>
#include <filesystem> 
#include <cstdlib> // this for the getenv
#include <unistd.h>//is the name of the header file that provides access to the POSIX operating system 
#include <sstream>


void echo(std::string str);

void type(std::string command) //Old version
{
  const std::string builtin_commands[] = {"echo","exit","type"}; 

  for(std::string builtin : builtin_commands)
  {
    if(builtin == command)
    {
      std::cout << command << " is a shell builtin" << "\n";
      return;
    }
  }

  // -------------------------------------------------

  const std::string path_env = getenv("PATH"); 
  if(path_env == "")
  {
    return;
  }
    

  std::stringstream ss_path(path_env);
  std::string path;
  while (std::getline(ss_path, path, ':')) {
    std::string full_path = path + '/' + command;
    if (access(full_path.c_str(), X_OK) == 0) {
      std::cout << command << " is " << full_path << std::endl;
      return;
    }
  }
  std::cout << command << ": not found" << "\n";
}

 

void echo(std::string command)
{
  std::cout << command << "\n";
}


int main() {
  // Flush after every std::cout / std:cerr - flush means the buffer (like a waiter) is seding the string (wiater delevers the food from the kichen) 
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string command;
  std::string line;



  while(true) 
  { 
    std::cout << "$ ";
    std::getline(std::cin,line);

    std::stringstream ss(line); // What does ss do?
    ss >> command;


    if(command == "exit")
    {
      break;
    }
    else if(command == "echo")
    {
      echo(command);
    }
    else if(command == "type")
    {
      type(command);
    }
    else
    {
      std::cout << command << ": command not found" << "\n";
    }
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