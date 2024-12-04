#include <stdlib.h>
#include <string.h>
#include "id3_utils.h"

/**
TODO: Add documention 
 */
TagData* create_tag_data() 
{
    TagData *data = (TagData *)malloc(sizeof(TagData));
    if (data) 
    {
        data->version = NULL;
        data->title = NULL;
	data->titleflag = 0;
	data->titlesize = 0;
        data->artist = NULL;
	data->artistflag = 0;
	data->artistsize = 0;
        data->album = NULL;
	data->albumflag = 0;
	data->albumsize = 0;
        data->year = NULL;
	data->yearflag = 0;
	data->yearsize = 0;
        data->comment = NULL;
	data->commentflag = 0;
	data->commentsize = 0;
        data->genre = NULL;
	data->genreflag = 0;
	data->genresize = 0;
        data->composer = NULL;
	data->composerflag = 0;
	data->composersize = 0;
        data->track = NULL;
	data->trackflag = 0;
	data->tracksize = 0;
        data->content = NULL;
	data->contentflag = 0;
	data->contentsize = 0;
        // Initialize other fields as needed
    }
    return data;
}

/**
TODO: Add documention as sample given
 */
void free_tag_data(TagData *data) {
    if (data) {
        //free(data->version);
        free(data->title);
        free(data->artist);
        free(data->album);
        free(data->year);
        free(data->comment);
        free(data->genre);
        free(data->track);
        free(data->composer);
        free(data->content);
        // Free other fields as needed
        free(data);
    }
}
