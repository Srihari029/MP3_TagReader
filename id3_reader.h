#ifndef ID3_READER_H
#define ID3_READER_H

#include "id3_utils.h"

/**
TODO: Add documention as sample given
 */
TagData* read_id3_tags(const char *filename);

/**
TODO: Add documention as sample given 
 */
void display_metadata(const TagData *data);

/**
TODO: Add documention as sample given
 */
void view_tags(const char *filename);

// Function to convert little endian to big endian
void littletobig(char *ptr,int n);

#endif // ID3_READER_H
