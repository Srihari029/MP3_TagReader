/**
 * @file main.c
 * @brief Main entry point for the MP3 Tag Reader application.
 */

#include <stdio.h>
#include <string.h>
#include "main.h"
#include "id3_reader.h"
#include "id3_writer.h"
#include "error_handling.h"

/**
 * @brief Displays the help message for the MP3 Tag Reader application.
 */
void display_help() 
{
    printf("Usage: mp3tagreader [options] filename\n");
    printf("Options:\n");
    printf("Help          : ./a.out  -h  \n");
    printf("View tags     : ./a.out  -v  <mp3_filename>\n");
    printf("Edit tags     : ./a.out  -e  (-t/-T/-a/-A/-y/-c/-g)  <value>  <mp3_filename>\n");
    printf("T  -  Title\nA  -  Artist\na  -  Album\nY  -  Year\nC  -  Content\nt  -  Track\n");
}

/**
 * @brief Main function to handle command-line arguments and execute appropriate actions.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[]) 
{
    	// less than 2 arguments are not valid, display help menu 
    	if (argc < 2) 
    	{
    	        display_help();
 	        return 1;
    	}
    	// if "-h" ---> open help menu
    	if (strcmp(argv[1], "-h") == 0 && argc == 2) 
    	{
    		display_help();
    		return 0;
    	}
    	// if "-v" check for 3 arguments 
    	else if (strcmp(argv[1], "-v") == 0 && argc == 3) 
    	{
		char *mp3;
		mp3 = strstr(argv[2],".mp3");
		if(mp3 != NULL)
		{
			// if the file format is .mp3
			if(strcmp(mp3,".mp3") == 0)
				view_tags(argv[2]);
			else
				printf("Invalid audio file format\n");
			        return 0;
		}
		else
		{
			// if file is not in .mp3 format
			printf("Invalid audio file format\n");
			return 0;
		}
	
	}
	// if "-e" check for 5 arguments
	else if (strcmp(argv[1], "-e") == 0 && argc == 5) 
    	{
        	char *tag = argv[2];
        	char *filename = argv[4];
        	char *value = argv[3];

		char *mp3;
                mp3 = strstr(argv[4],".mp3");
                if(mp3 != NULL && strcmp(mp3,".mp3") == 0)
		{
        		if (edit_tag(filename, tag, value) != 0) 
			{
        			//display_error
				printf("Failed to edit tag.\n");
	        		return 1;
	        	}
	        	printf("Tag edited successfully.\n");
		}
		else
		{
                        // if file is not in .mp3 format
                        printf("Invalid audio file format\n");
                        return 0;
		}

	} 
	else
	{
		printf("Invalid arguments !\n");    
	        display_help();
        	return 1;
    	}
    	return 0;
}
