#include <string.h>
#include "profs.h"

str_t dentry[NUM_DENTRY];

/*
 *  For a given entry i, sets the number and string fields to
 *  defaults (zero or number, empty string for string field)
 *
 *  parameters: 
 *      i: index of the entry
 *
 *  returns: N/A
 */

void clear_entry(int i) 
{
  dentry[i].str[0]= '\0';
  dentry[i].num = 0;
}

/*
 *  Set the initial values for all fields of each entry of the table
 * 
 *  parameters: N/A
 * 
 *  returns: N/A
 */
void init_dentry(void) 
{
    for(int i = 0; i < NUM_DENTRY; i++)
    {
        clear_entry(i);
    }
}

/*
 *  returns the whole dentry table
 * 
 *  parameters: N/A
 * 
 *  returns: dentry table
 */
str_t *get_dentry()
{
    return dentry;
}

/*
 *  Returns the file name (string field) of a given entry i
 * 
 *  parameters: 
 *      i: index of the table
 * 
 *  returns: string field of the table
 */
char *return_entry(int i)
{
    return dentry[i].str;
}

/*
 *  check if the field string of the entry i is empty
 * 
 *  returns: 1 if empty, 0 if not
 */
int check_entry(int i)
{
    return  dentry[i].str[0] != '\0';
}

/*
 *  returns the first empty entry, if it does not find any, r
 *  return NUM_DENTRY which means we reached the end with no success
 * 
 *  return: 
 *      index of the first free entry or
 *      NUM_DENTRY if not free plade
 */
int return_first_entry()
{
    for(int i = 0; i < NUM_DENTRY; i++)
    {   
        if (check_entry(i) == 0)
            return i;
    }

  return NUM_DENTRY;
}

/*
 *  writes a given string in the corresponding field at entry i
 * 
 *  parameters: 
 *      i: index of the entry
 *      str: string to copy in the entry
 * 
 *  returns: 
 *      the length of the written string
 */
int write_entry(int i, char *str)
{
    char *copied_string = strncpy(dentry[i].str, str, STR_LEN);

    // Its causing a horrible bug!!!!!
    // Overwrites the last character not caring about the length of the copied string
    // dentry[i].str[STR_LEN] = '\0';

    return strlen(copied_string);

}

/*
 *  copies a given string into the first empty available entry
 * 
 *  parameters: 
 *      str: string to copy in the entry
 * 
 *  returns: 
 *      the index of the entry where the string was copied
 *      if the index = NUM_dentry, there were not available empty entries
 */
int write_first_free(char *str) 
{
    int empty_index = return_first_entry();
 
    // Not available empty entries
    if (empty_index == NUM_DENTRY) 
        return NUM_DENTRY;

    write_entry(empty_index, str);
    // Is it necessary to add an error control for if write_entry returns 0?

    return empty_index;
}

/*
 *  Checks if the string str exists in the dentry table
 * 
 *  returns: 
 *      the index of the entry where the string was found or
 *      NUM_DENTRY if not found
 */
int search_entry(char *str)
{
    for (int i = 0; i < NUM_DENTRY; i++)
    {
        if (strcmp(dentry[i].str, str) == 0)
        {
            return i;
        }
    }
    return NUM_DENTRY;
}