#ifndef ID3_UTILS_H
#define ID3_UTILS_H

/**
 * @brief Structure to hold ID3 tag data.
 */
typedef struct {
    char *version; /**< Version of the ID3 tag */
    char *title;   /**< Title of the song */
    int titlesize;
    int titleflag;
    char *artist;  /**< Artist of the song */
    int artistsize;
    int artistflag;
    char *album;   /**< Album name */
    int albumsize;
    int albumflag;
    char *year;    /**< Year of release */
    int yearsize;
    int  yearflag;
    char *comment; /**< Comment */
    int commentsize;
    int commentflag;
    char *genre;   /**< Genre */
    int genresize;
    int genreflag;
    char *track;   /**< Track */
    int tracksize;
    int trackflag;
    char *content;  /* content tyoe*/
    int contentsize;
    int contentflag;
    char *composer; /* composer */
    int composersize;
    int composerflag;
    // Add other fields as needed
} TagData;

/**
 * @brief Creates a new TagData structure.
 * 
 * @return Pointer to the newly created TagData structure.
 */
TagData* create_tag_data();

/**
TODO: Add documention as sample given above
 */
void free_tag_data(TagData *data);

#endif // ID3_UTILS_H
