/**
 * This file contains the implementations of the builtin functions provided by
 * the shell (or will, once you've finished implementing them all).
 */

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>

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
}


int Shell::com_cd(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  int return_value;
  if (argv.size() == 1 && argv[0] == "cd")
  {
    printf("cd \n");
    return_value = chdir( getenv("HOME"));
    printf("%d\n", return_value);
  }
  else if (argv.size() == 2 && argv[0] == "cd")
  {
    if (argv[1] == "~" || argv[1] == " ")
    {
      return_value = chdir(getenv("HOME"));
    }
    else{
      return_value = chdir(argv[1].c_str());
      if (return_value != 0)
      {
        perror("cd");
        return 1;
      }
    }
  }
  else{
    perror("error command");
    return 1;
  }
  //cout << "cd called" << endl; // delete when implemented
  return 0;
}


int Shell::com_pwd(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  char* currentDirectory;
  currentDirectory = (char*) malloc(1024 * sizeof(char));
  if (argv[0] == "pwd" && argv.size() == 1)
  { 
    printf("%s\n", getcwd(currentDirectory, 1024) );
    free(currentDirectory);
    return 0;
  }
  else{
    free(currentDirectory);
    return 1;
  }
 // free(currentDirectory);
  // cout << "pwd called" << endl; // delete when implemented
 // return 0;
}


int Shell::com_alias(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  vector<string>::iterator token;
  string::size_type eq_pos;
  token = argv.begin();
  
  if (token->substr(0) == "alias" && argv.size() == 1)
  {
    map<string, string>::iterator it;
    it = aliases.begin();
    while(it != aliases.end()){
	    printf("%s = %s \n", it->first.c_str(), it->second.c_str());
	    it++;
    }
    return 0;
  }
  else if (argv.size() == 2){
	token ++;
	eq_pos = token->find('=');
	if(eq_pos == string::npos){
		return 1;
	}
	else{
		string key = token->substr(0, eq_pos);
		string value = token->substr(eq_pos + 1);
		aliases[key] =value;
		return 0;
	}
  }
  else{
	  return 1;
  }

  // cout << "alias called" << endl; // delete when implemented
 // return 0;
}


int Shell::com_unalias(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  vector<string>::iterator token;
  token = argv.begin();
  if (argv.size() == 1)
  {
    return 1;
  }
  else if (argv.size() ==2)
  {
    if (argv[1] == "-a")
    {
      aliases.erase(aliases.begin(), aliases.end());
      return 0;
    }
    else if (aliases.find(argv[1]) != aliases.end())
    {
      aliases.erase(argv[1]);
      return 0;
    }
    else{
      return 1;
    }
  }
  else{
    return 1;
  }
  // cout << "unalias called" << endl; // delete when implemented
  
}


int Shell::com_echo(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  if (argv.size() == 1 && argv[0] == "echo")
  {
    printf("\n");
  }
  else{
    for (unsigned i = 1; i < argv.size(); ++i)
    {
      printf("%s ",argv[i].c_str());
    }
    printf("\n");
  }
  // cout << "echo called" << endl; // delete when implemented
  return 0;
}


int Shell::com_history(vector<string>& argv) {
//   // TODO: YOUR CODE GOES HERE
  if (argv[0] == "history" && argv.size() == 1)
  {
    register HIST_ENTRY ** his_list;
    his_list = history_list();
    if (his_list)
    {
      for (int i = 0; his_list[i]; ++i)
      {
        printf(" %d  %s\n", i+history_base, his_list[i]->line);
      }
    }
    return 0;
   }else {
    return 1;  
   }

//   cout << "history called" << endl; // delete when implemented
   return 0;
 }


int Shell::com_exit(vector<string>& argv) {
  // TODO: YOUR CODE GOES HERE
  if(argv[0] == "exit")
  {
    exit(0);
  }
  // cout << "exit called" << endl; // delete when implemented
  return 0;
}
