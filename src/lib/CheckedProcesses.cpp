#include "CheckedProcesses.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

#include <algorithm>
#include "NotReadyException.h"

//TODO redo this with qt
pid_t proc_find(const char* name) 
{
	DIR* dir;
	struct dirent* ent;
	char* endptr;
	char buf[512];
	
	if (!(dir = opendir("/proc"))) {
		perror("can't open /proc");
		return -1;
	}
	
	while((ent = readdir(dir)) != NULL) {
		/* if endptr is not a null character, the directory is not
		 * entirely numeric, so ignore it */
		long lpid = strtol(ent->d_name, &endptr, 10);
		if (*endptr != '\0') {
			continue;
		}
		
		/* try to open the cmdline file */
		snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
		FILE* fp = fopen(buf, "r");
		
		if (fp) {
			if (fgets(buf, sizeof(buf), fp) != NULL) {
				/* check the first token in the file, the program name */
				char* first = strtok(buf, " ");
				if (!strcmp(first, name)) {
					fclose(fp);
					closedir(dir);
					return (pid_t)lpid;
				}
			}
			fclose(fp);
		}
		
	}
	
	closedir(dir);
	return -1;
}

bool CheckedProcesses::check()
{
	return std::all_of(std::begin(elements),
						std::end(elements),
						[] (Process& proc) 
	{ 
		bool val = proc_find(proc.name.c_str()) == -1;
		
		if(!val) throw NotReady(proc.timeout);
		return val; 
	});
}
