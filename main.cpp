#include <iostream>
#include <cstring>
#include <stdio.h>
#include <dirent.h>
#include <fnmatch.h>

void printHelp() {
  std::cout <<"\n./search <path> <pattern> <regex>" <<std::endl;
  std::cout<<"\nExample:"<<std::endl;
  std::cout <<"./search /home/neel '*.cpp' 'hello.*'" << std::endl;
}

bool isRegExMatch(std::string s, std::string p) {
	int n = s.length(), m = p.length();    
	bool **states = new bool* [n+1];
	for ( int i = 0; i <= n; ++i) {
		states[i] = new bool[m+1];
	}
	for ( int i = 0; i <= n; ++i) {
		for ( int j = 0; j <= m; ++j)
			states[i][j] = false;            
	}
	states[0][0] = true;
	
	for(int i = 0; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(p[j-1] == '*'){
				states[i][j] = states[i][j-2] || (i > 0 && (s[i-1] == p[j-2] || p[j-2] == '.') && states[i-1][j]);
			}
			else{
				states[i][j] = i > 0 && states[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.');
			}
		}
	}
	
	bool retVal = states[n][m];
	
	for ( int i = 0; i <= n; ++i)
		delete [] states[i];
	delete [] states;
	
	return retVal;
}

void SearchFiles(const char* directory, const char* pattern, const char* regExpression) {
    DIR* dir;
    struct dirent* entry;

    if ((dir = opendir(directory)) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (fnmatch(pattern, entry->d_name, 0) == 0) {                
				if (isRegExMatch(entry->d_name, regExpression)) {
					std::cout << "    " << entry->d_name << std::endl;
				}				
            }
        }
        closedir(dir);
    } else {
        std::cout << "Error opening directory" << directory << std::endl;
    }
}

void listSubdirectories(const char *path, const char* pattern, const char* regExpression) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char subdir_path[PATH_MAX];
                snprintf(subdir_path, sizeof(subdir_path), "%s/%s", path, entry->d_name);
                printf("Subdirectory: %s\n", subdir_path);
                SearchFiles(subdir_path, pattern, regExpression);
                listSubdirectories(subdir_path, pattern, regExpression);
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {

    if (argc != 4) {
      printHelp();
      return 0;
    }
	
    std::string directoryPath = argv[1];
    std::string filePattern   = argv[2];
    std::string regExpression = argv[3];
	
    SearchFiles(directoryPath.c_str(), filePattern.c_str(), regExpression.c_str());
    listSubdirectories(directoryPath.c_str(), filePattern.c_str(), regExpression.c_str());

    return 0;
}
