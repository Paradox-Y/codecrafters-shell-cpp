#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib> // this for the getenv
#include <unistd.h>//is the name of the header file that provides access to the POSIX operating system 
#include <sstream>


void echo(std::string &str);

void type(std::string &line) //Old version
{
  std::stringstream ss(line);

  std::string type_cmd;
  ss >> type_cmd;

  std::string command;
  ss >> command;

  if(command.empty())
    return;
  
  const std::string builtin_commands[] = {"echo","exit","type"}; 

  for(const std::string& builtin : builtin_commands)
  {
    if(builtin == command)
    {
      std::cout << command << " is a shell builtin" << "\n";
      return;
    }
  }

  // -------------------------------------------------

  const char* path_raw = getenv("PATH");
  const std::string path_env = path_raw ? path_raw : "";

  if (!path_env.empty()) {
    std::stringstream ss_path(path_env);
    std::string path;
    while (std::getline(ss_path, path, ':')) {
      std::string full_path = path + '/' + command;
      if (access(full_path.c_str(), F_OK) == 0 && access(full_path.c_str(), X_OK) == 0) {
        std::cout << command << " is " << full_path << '\n';
        return;
      }
    }
  }


  std::cout << command << ": not found" << "\n";
}

 

void echo(std::string &line)
{
  line.erase(0,5);
  std::cout << line << "\n";
}


// int execute(std::string line) {
//   if (line.extension() == ".exe") {
//     std::cout << line.stem() << " is a Windows executable \n";
//   }
//
// }


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

    std::stringstream ss(line); 
    ss >> command;

    if(command == "exit")
    {
      break;
    }
    else if(command == "echo")
    {
      echo(line);
    }
    else if(command == "type") {
      type(line);
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
Added:
1.  Running External Programs: handle external programs that your shell needs to find and run.
*/

/*
Expalines:

*/