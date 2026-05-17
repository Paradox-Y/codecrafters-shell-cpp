#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib> // this for the getenv
#include <unistd.h>//is the name of the header file that provides access to the POSIX operating system 
#include <sstream>
#include <vector>
#include <sys/wait.h> // concurrence


void echo(std::string &str);
int execute(std::string line);


void type(std::string &line) //Old version
{
  std::stringstream ss(line);

  std::string type_cmd;
  ss >> type_cmd; //this just saves the type part of the string stream

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
      if (access(full_path.c_str(), X_OK) == 0) {
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
  std::cout << line << '\n';
}


int execute(std::string line) {
  // 1. Extract all words from the input line safely
  std::stringstream ss(line);
  std::string word;
  std::vector<std::string> string_args;

  // This automatically splits by spaces! No manual character checking needed.
  while (ss >> word) {
    string_args.push_back(word);
  }

  if (string_args.empty()) {
    return 1;
  }

  // Assuming the first word they typed is the command (e.g., "ls")
  std::string command = string_args[0];

  // 2. Build the C-style args array required by execv
  std::vector<char*> args;
  for (size_t i = 0; i < string_args.size(); ++i) {
    args.push_back(const_cast<char*>(string_args[i].c_str()));
  }
  args.push_back(nullptr); // Critical: Array must end with NULL







  const char* path_raw = getenv("PATH");
  const std::string path_env = path_raw ? path_raw : "";

  if (!path_env.empty()) {
    std::stringstream ss_path(path_env);
    std::string path;
    while (std::getline(ss_path, path, ':')) {
      std::string full_path = path + '/' + command;
      if (access(full_path.c_str(), X_OK) == 0) {
        // 4. FORK so your shell stays alive!  ------------------------------------------Learn
        pid_t pid = fork();

        if (pid == 0) {
          // --- CHILD PROCESS ---
          // This clone completely replaces itself with the new program
          execv(full_path.c_str(), args.data());

          // If execv reaches this line, it means it failed to run
          std::cerr << "execv failed\n";
          exit(1); // Kill the broken child process
        }
        else if (pid > 0) {
          // --- PARENT PROCESS (Your Shell) ---
          // Pause and wait for the child process to finish its job
          int status;
          waitpid(pid, &status, 0);

          return 0; // Return to main() so the shell can print the next '$ '
        }
        else {
          // --- ERROR ---
          std::cerr << "fork failed\n";
          return 1;
        }//-----------------------------------------------------------------------------------Learn
      }
    }
  }
  return 1;
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
      if (execute(line)==1)
        std::cout << command << ": command not found" << std::endl;
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

Copile with this:
g++ -std=c++17 -Wall -Werror -pedantic main.cpp -o main
*/