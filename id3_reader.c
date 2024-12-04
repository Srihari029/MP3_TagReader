/**
 * @file id3_reader.c
 * @brief Implementation of functions for reading ID3 tags from MP3 files.
 */

#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "id3_reader.h"
#include "error_handling.h"

/**
TODO: Add documention as sample given
 */

// conver little endian to big endian
void littletobig(char *ptr,int n){
    int i;
    char temp;
    for(i=0;i<n/2;i++){
        char temp = *(ptr + i);
        *(ptr + i) = *(ptr + (n-1-i));
        *(ptr + (n-1-i)) = temp;
    }
}

int check_id3_tag_presence(const char *filename)
{
	FILE *file_name = fopen(filename,"r");
	if(file_name == NULL)
		return FAILURE;
	char buffer[1],id3[4];
	int i=0;
		while(i<3)
		{
		    fread(buffer,1,1,file_name);
		    id3[i] = buffer[0];
		    i++;
		}
		id3[3] = '\0';
		if(strcmp(id3,"ID3") != 0)
		{
			return FAILURE;
		}
		return SUCCESS;
	}

TagData* read_id3_tags(const char *filename)
{
    TagData *tag = malloc(sizeof(TagData)); 	
    // Implementation for reading ID3 tags
    char tag_buffer[5], content[100];
    unsigned char ver[10];
    int i = 0;
    unsigned int size;

    // Open file in read mode
    FILE *file_name = fopen(filename,"r");
    if(file_name == NULL)
    {
	    printf("INFO : Audio file opening failed. Please check the audio file\n");
	    return NULL;
    }

    //check for ID3 tag
    if(check_id3_tag_presence(filename) == FAILURE)
    {
	    printf("File is not ID3 Version\n");
		    return NULL;
    }

    // To find ID3 version     
    fseek(file_name, 0, SEEK_SET);
    fread(ver, 1, 10, file_name);

    if(ver[3] == 2)
	    tag->version = "ID3v2.2";
    else if(ver[3] == 3)
	    tag->version = "ID3v2.3";
    else if(ver[3] == 4)
	    tag->version = "ID3v2.4";

    // Set file pointer to 10, skiping header files
    fseek(file_name,10,SEEK_SET);
    
    for(i=0 ; i < 15 ; i++)
    {
    	// read tag 
    	fread(tag_buffer,4,1,file_name);
    	tag_buffer[4] = '\0';
    	//printf("%s\n",tag_buffer);

	// Titile	
	if(strcmp(tag_buffer,"TIT2") == 0)
	{
    		//read size of content
    		fread(&size,sizeof(size),1,file_name);
    		littletobig((char*)&size,sizeof(size)); 	   
    		
		tag->titlesize = size;
		// skip 3 bytes
    		fseek(file_name,3,SEEK_CUR);
 	   	fread(content,size-1,1,file_name);
		content[size-1] = '\0';
		tag->title = malloc(size);
		if(!tag->title)
		{
			printf("Memory allocation failed\n");
			return NULL;
		}
    		strcpy(tag->title,content);
		tag->titleflag = 1;
    	}
	// Artist
	else if(strcmp(tag_buffer,"TPE1") == 0)
        {
                //read size of content
                fread(&size,sizeof(size),1,file_name);
                littletobig((char*)&size,sizeof(size));

    		tag->artistsize = size;
                // skip 3 bytes
                fseek(file_name,3,SEEK_CUR);

                fread(content,size-1,1,file_name);
                content[size-1] = '\0';
                tag->artist = malloc(size);
		if(!tag->artist)
		{
			printf("Memory allocation failed\n");
			return NULL;
		}
                strcpy(tag->artist,content);
                tag->artistflag = 1;
        }
	// Album
	else if(strcmp(tag_buffer,"TALB") == 0)
        {
                //read size of content
                fread(&size,sizeof(size),1,file_name);
                littletobig((char*)&size,sizeof(size));

    		tag->albumsize = size;
                // skip 3 bytes
                fseek(file_name,3,SEEK_CUR);

                fread(content,size-1,1,file_name);
		content[size-1] = '\0';
                tag->album = malloc(size);
		if(!tag->album)
		{
			printf("Memory allocation failed\n");
			return NULL;
		}
                strcpy(tag->album,content);
		tag->albumflag = 1;
        }
	// Year
	else if(strcmp(tag_buffer,"TYER") == 0)
        {
                //read size of content
                fread(&size,sizeof(size),1,file_name);
                littletobig((char*)&size,sizeof(size));

    		tag->yearsize = size;
                // skip 3 bytes
                fseek(file_name,3,SEEK_CUR);

                fread(content,size-1,1,file_name);
		content[size-1] = '\0';
                tag->year = malloc(size);
		if(!tag->year)
		{
			printf("Memory allocation failed\n");
			return NULL;
		}
                strcpy(tag->year,content);
		tag->yearflag = 1;
        }
	// Content
	else if(strcmp(tag_buffer,"TCON") == 0)
        {
                //read size of content
                fread(&size,sizeof(size),1,file_name);
                littletobig((char*)&size,sizeof(size));
    		
		tag->contentsize = size;
                // skip 3 bytes
                fseek(file_name,3,SEEK_CUR);

                fread(content,size-1,1,file_name);
                content[size-1] = '\0';
                tag->content = malloc(size);
		if(!tag->content)
		{
			printf("Memory allocation failed\n");
			return NULL;
		}
                strcpy(tag->content,content);
                tag->contentflag = 1;
        }
	// Composer
	else if(strcmp(tag_buffer,"TCOM") == 0)
        {
                //read size of content
                fread(&size,sizeof(size),1,file_name);
                littletobig((char*)&size,sizeof(size));
    		
		tag->composersize = size;
                // skip 3 bytes
                fseek(file_name,3,SEEK_CUR);

                fread(content,size-1,1,file_name);
		content[size-1] = '\0';
                tag->composer = malloc(size);
		if(!tag->composer)
		{
			printf("Memory allocation failed\n");
			return NULL;
		}
                strcpy(tag->composer,content);
		tag->composerflag = 1;
        }
	// Comment
	else if(strcmp(tag_buffer,"COMM") == 0)
        {
                //read size of content
                fread(&size,sizeof(size),1,file_name);
                littletobig((char*)&size,sizeof(size));

    		tag->commentsize = size;
                // skip 3 bytes
                fseek(file_name,3,SEEK_CUR);

                fread(content,size-1,1,file_name);
		content[size-1] = '\0';
                tag->comment = malloc(size);
		if(!tag->comment)
		{
			printf("Memory allocation failed\n");
			return NULL;
		}
                strcpy(tag->comment,content);
		tag->commentflag = 1;
        }
	// Track
	else if(strcmp(tag_buffer,"TRCK") == 0)
        {
                //read size of content
                fread(&size,sizeof(size),1,file_name);
                littletobig((char*)&size,sizeof(size));

    		tag->tracksize = size;
                // skip 3 bytes
                fseek(file_name,3,SEEK_CUR);

                fread(content,size-1,1,file_name);
		content[size-1] = '\0';
                tag->track = malloc(size);
		if(!tag->track)
		{
			printf("Memory allocation failed\n");
			return NULL;
		}
                strcpy(tag->track,content);
		tag->trackflag = 1;
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
    return tag;
    
}

/**
TODO: Add documention as sample given
 */
void display_metadata(const TagData *data)
{
    	// Implementation for displaying metadata
    	printf("ID3 TAGS\n\n");
        printf("%-10s : %-5s\n","Version",data->version);
	if(data->titleflag == 1)
        	printf("%-10s : %-5s\n","Title",data->title);
        if(data->artistflag == 1)
		printf("%-10s : %-5s\n","Artist",data->artist);
        if(data->albumflag == 1)
		printf("%-10s : %-5s\n","Album",data->album);
        if(data->yearflag == 1)
		printf("%-10s : %-5s\n","Year",data->year);
        if(data->contentflag == 1)
		printf("%-10s : %-5s\n","Content",data->content);
	if(data->composerflag == 1)
		printf("%-10s : %-5s\n","Composer",data->composer);
	if(data->commentflag == 1)
		printf("%-10s : %-5s\n","Comment",data->comment);
        if(data->trackflag == 1)
		printf("%-10s : %-5s\n","Track",data->track);
}

/**
TODO: Add documention as sample given
 */
void view_tags(const char *filename) {
    TagData *data = read_id3_tags(filename);
    if (!data) {
        printf("Failed to read ID3 tags.\n");
        return;
    }
    // Display data
    display_metadata(data);
    free_tag_data(data);
}
