#include <fstream>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <dirent.h>
using namespace std;
    int main()
    {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir ("/home/fabrizio/Desktop/GitHubRepos/EDA/EDA-2019-01/EDATeoria/HW1/files")) != NULL) {
          while ((ent = readdir (dir)) != NULL) {
            //cout<<"ent: "<<ent->d_name<<endl;
            printf ("%s\n", ent->d_name);
          }
          closedir (dir);
        } else {
          perror ("");
          return EXIT_FAILURE;
        }
    }