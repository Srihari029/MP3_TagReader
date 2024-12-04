/**
 * @file id3_writer.c
 * @brief Implementation of functions for writing and editing ID3 tags in MP3 files.
 */

#include "main.h"
#include <stdio.h>
#include <string.h>
#include "id3_writer.h"
#include "id3_reader.h"
#include "id3_utils.h"

/**
 * @brief Writes the ID3 tags to an MP3 file.
 * 
 * @param filename The name of the MP3 file.
 * @param data Pointer to the TagData structure containing the ID3 tags.
 * @return 0 on success, non-zero on failure.
 */


/** TODO: Add documentation as sample given above */
int edit_tag(const char *filename, const char *tag, const char *value) {
    	TagData *data = read_id3_tags(filename);
    	if (!data) {
    	    	return FAILURE;
    	}
    	// Implementation for writing ID3 tags to file
	char tag_buffer[5];	
	int newlen = strlen(value) + 1;
	unsigned int size,i,j;

    	FILE *file_name;	
    	file_name = fopen(filename,"r+");
    	if(file_name == NULL)
   	{
		printf("INFO : Audio file not found\n");
		return FAILURE;
    	}
	// Skip 10 bytes of header
	fseek(file_name,10,SEEK_SET);
    	switch(tag[0])
    	{
		// Title edit
		case 'T':
			for(i = 0;i < 8; i++)
			{	
				fread(tag_buffer,4,1,file_name);
        			tag_buffer[4] = '\0';
				if(strcmp(tag_buffer,"TIT2") == 0)
        			{	
                			// Skip size
					fseek(file_name,4,SEEK_CUR);
                                	// skip 3 bytes
                                	fseek(file_name,3,SEEK_CUR);
					fwrite(value,data->titlesize - 1,1,file_name);
				}
				else
        			{
                			//read size of content
					fread(&size,sizeof(size),1,file_name);
                			littletobig((char*)&size,sizeof(size));
                			// skip 3 bytes
                			fseek(file_name,3,SEEK_CUR);
               				fseek(file_name,size-1,SEEK_CUR);
        			}
			}
			printf("----------------------------------EDIT OPTION-----------------------------------------\n");
			printf("-----------------------------You have chosen %s------------------------------------\n","Title");
			printf("%30s : %s\n","Title",value);
			printf("--------------------------------------------------------------------------------------\n");
			break;

		// Album edit	
		case 'a':
                        for(i = 0;i < 8; i++)
                        {
                                fread(tag_buffer,4,1,file_name);
        			tag_buffer[4] = '\0';
                                if(strcmp(tag_buffer,"TALB") == 0)
                                {
                                        // Skip size
                                        fseek(file_name,4,SEEK_CUR);
                                        // skip 3 bytes
                                        fseek(file_name,3,SEEK_CUR);
                                        fwrite(value,data->albumsize - 1,1,file_name);
                                }
                                else
                                {
                                        //read size of content
                                        fread(&size,sizeof(size),1,file_name);
                                        littletobig((char*)&size,sizeof(size));
                                        // skip 3 bytes
                                        fseek(file_name,3,SEEK_CUR);
                                        fseek(file_name,size-1,SEEK_CUR);
                                }
                        }
			printf("----------------------------------EDIT OPTION-----------------------------------------\n");
			printf("-----------------------------You have chosen %s------------------------------------\n","Album");
			printf("%30s : %s\n","Title",value);
			printf("--------------------------------------------------------------------------------------\n");
			break;

		// Artist edit	
		case 'A':
                        for(i = 0;i < 8; i++)
                        {
                                fread(tag_buffer,4,1,file_name);
        			tag_buffer[4] = '\0';
                                if(strcmp(tag_buffer,"TPE1") == 0)
                                {
                                        // Skip size
                                        fseek(file_name,4,SEEK_CUR);
                                        // skip 3 bytes
                                        fseek(file_name,3,SEEK_CUR);
                                        fwrite(value,data->artistsize-1,1,file_name);
                                }
                                else
                                {
                                        //read size of content
                                        fread(&size,sizeof(size),1,file_name);
                                        littletobig((char*)&size,sizeof(size));
                                        // skip 3 bytes
                                        fseek(file_name,3,SEEK_CUR);
                                        fseek(file_name,size-1,SEEK_CUR);
                                }
                        }
			printf("----------------------------------EDIT OPTION-----------------------------------------\n");
			printf("----------------------------You have chosen %s------------------------------------\n","Artist");
			printf("%30s : %s\n","Title",value);
			printf("--------------------------------------------------------------------------------------\n");
			break;

		// Year edit	
		case 'Y':
			// Check if year contains only digits
			for(i=0;i<newlen-1;i++)
			{
				if(!(isdigit(value[i])))
				{
					printf("INFO : Year must contain only digits\n");
					return FAILURE;
				}
			}
                        for(i = 0;i < 8; i++)
                        {
                                fread(tag_buffer,4,1,file_name);
        			tag_buffer[4] = '\0';
                                if(strcmp(tag_buffer,"TYER") == 0)
                                {
                                        // Skip size
                                        fseek(file_name,4,SEEK_CUR);
                                        // skip 3 bytes
                                        fseek(file_name,3,SEEK_CUR);
                                        fwrite(value,data->yearsize-1,1,file_name);
                                }
                                else
                                {
                                        //read size of content
                                        fread(&size,sizeof(size),1,file_name);
                                        littletobig((char*)&size,sizeof(size));
                                        // skip 3 bytes
                                        fseek(file_name,3,SEEK_CUR);
                                        fseek(file_name,size-1,SEEK_CUR);
                                }
                        }
			printf("----------------------------------EDIT OPTION-----------------------------------------\n");
			printf("------------------------------You have chosen %s------------------------------------\n","Year");
			printf("%30s : %s\n","Title",value);
			printf("--------------------------------------------------------------------------------------\n");
			break;

		// Content edit
		case 'C':
                        for(i = 0;i < 8; i++)
                        {
                                fread(tag_buffer,4,1,file_name);
        			tag_buffer[4] = '\0';
                                if(strcmp(tag_buffer,"TCON") == 0)
                                {
                                        // Skip size
                                        fseek(file_name,4,SEEK_CUR);
                                        // skip 3 bytes
                                        fseek(file_name,3,SEEK_CUR);
                                        fwrite(value,data->contentsize - 1,1,file_name);
                                }
                                else
                                {
                                        //read size of content
                                        fread(&size,sizeof(size),1,file_name);
                                        littletobig((char*)&size,sizeof(size));
                                        // skip 3 bytes
                                        fseek(file_name,3,SEEK_CUR);
                                        fseek(file_name,size-1,SEEK_CUR);
                                }
                        }
			printf("----------------------------------EDIT OPTION-----------------------------------------\n");
			printf("---------------------------You have chosen %s------------------------------------\n","Content");
			printf("%30s : %s\n","Title",value);
			printf("--------------------------------------------------------------------------------------\n");
			break;

		// Track edit	
		case 't':
                        for(i = 0;i < 8; i++)
                        {
                                fread(tag_buffer,4,1,file_name);
        			tag_buffer[4] = '\0';
                                if(strcmp(tag_buffer,"TRCK") == 0)
                                {
                                        // Skip size
                                        fseek(file_name,4,SEEK_CUR);
                                        // skip 3 bytes
                                        fseek(file_name,3,SEEK_CUR);
                                        fwrite(value,data->tracksize - 1,1,file_name);
                                }
                                else
                                {
                                        //read size of content
                                        fread(&size,sizeof(size),1,file_name);
                                        littletobig((char*)&size,sizeof(size));
                                        // skip 3 bytes
                                        fseek(file_name,3,SEEK_CUR);
                                        fseek(file_name,size-1,SEEK_CUR);
                                }
                        }
			printf("----------------------------------EDIT OPTION-----------------------------------------\n");
			printf("-----------------------------You have chosen %s------------------------------------\n","Track");
			printf("%30s : %s\n","Title",value);
			printf("--------------------------------------------------------------------------------------\n");
			break;

		default:
			printf("Please choose from given option\n./a.out -h ---> for help\n");

	}
	return SUCCESS;
}
