# searchfiles
Searches files in the Unix filesystem based on a certain pattern and applies a regular expression within them.
Solution has three main functions.
1. isRegExMatch(string s, string p)
	Function to implement regular expression. Implementation of complete regex is bigh project and research papers have been published around it.	
	I provided minimum implementation of regeular expression covering only "*" and ".". Even this implementation is well known problem of Dynamic Programming and its solution is already known. So, there is nothing new in this solution. Anyone who knows Dynamic Programming is certainly aware of this solution.
	
2. SearchFiles(const char* directory, const char* pattern, const char* regExpression)
	This function open the directory using opendir()/readdir() and matches the filename against given pattern using fnmatch().
	If filename matches pattern, then it checks if filename matches the given regular expression using isRegExMatch()

3. listSubdirectories()
		This function open the directory using opendir()/readdir() and finds out all sub directories and call SearchFiles() on each directory.

Scaling-up - We can scale up the application using multithreading or thread pool. Assume that we have a thread pool of 50 threads.
	- There will be one dedicated thread to get names of all Subdirectories and push names into queue.
	- Each worker thread will pop name of one sub-directory and find all files matching to given pattern and regular expression.
	
Compiling - Compile using g++ (g++ filename.cpp -o search)

