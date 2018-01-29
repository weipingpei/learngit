/**
 * This file contains the implementations of the builtin functions provided by
 * the shell (or will, once you've finished implementing them all).
 */

#include "shell.h"
#include <iostream>

using namespace std;


int Shell::com_ls(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  DIR *dir;
  struct dirent *ptr;
  if (argv.size() == 1 && argv[0] == "ls") 
  {
    dir = opendir(".");
  }
  else if (argv.size() == 2 && argv[0] == "ls") 
  {
    if ((dir=opendir(argv[1].c_str())) == NULL)
    {
      perror("fail to opendir");
      return 1;
    }
  }
  else{
    perror("error command");
    return 1;
  }
  while((ptr = readdir(dir)) != NULL)
  {
    if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
      continue;
    printf("%s\n",ptr->d_name);
  }
  closedir(dir);

  // cout << "ls called" << endl; // delete when implemented
  return 0;

  //cout << "ls called" << endl; // delete when implemented
  //return 0;
}


int Shell::com_cd(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  cout << "cd called" << endl; // delete when implemented
  return 0;
}


int Shell::com_pwd(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  cout << "pwd called" << endl; // delete when implemented
  return 0;
}


int Shell::com_alias(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  cout << "alias called" << endl; // delete when implemented
  return 0;
}


int Shell::com_unalias(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  cout << "unalias called" << endl; // delete when implemented
  return 0;
}


int Shell::com_echo(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  cout << "echo called" << endl; // delete when implemented
  return 0;
}


int Shell::com_history(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  cout << "history called" << endl; // delete when implemented
  return 0;
}


int Shell::com_exit(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  cout << "exit called" << endl; // delete when implemented
  return 0;
}
