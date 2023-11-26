#include "profs.h"

#define FREE_BLK    0
#define EOF_BLK    -1

// Error Values
// #define NO_FREE_BLK   -2
#define NOT_EOF       -3

int fat[NB_BLOCKS];


/*
 *  initializes all entries of the FAT table with the FREE_BLOCK value
 *
 *  returns: N/A
 */
void init_fat() 
{

  for (int i = 0; i < NB_BLOCKS; i++){

    fat[i] = FREE_BLK;

  }
}

/*
 *  Set the entry i of fat table equal to FREE_BLK
 *
 */
void clear_block(int i) 
{
  fat[i] = FREE_BLK;
}


/*
 *  returns the whole FAT table
 *
 *  parameters: N/A
 *
 *  returns: fat table
 */
int *get_fat() 
{
  return fat;
}

/*
 *  returns true if the entry is the last block of a file
 *  i.e. if its value is EOF_BLK (-1)
 *
 *  parameters: 
 *    i: index of the block to check
 *
 *  returns: 1 if its the last block, 0 if not
 */
int eof_block(int i) 
{
  return fat[i] == EOF_BLK;
}

/*
 *  returns the value of the block at a given index
 *  which means the next memory block of the file
 *
 *  returns: the value of the entry
 */
int next_block(int i)
{
  return fat[i];
}

/*
 *  returns the index of the first available block, i.e.
 *  the first block with the FREE_BLK value in it
 *
 *  parameters: N/A
 *
 *  returns: the index of the first free block 
 *  or NO_FREE_BLK value if there's no free blocks
 */
int first_free_block()
{

  for (int i = 0; i < NB_BLOCKS; i++){

    if (fat[i] == FREE_BLK){
      return i;
    }
  }

  return NO_FREE_BLK;
}

/*
 *  search for a free block and writes the EOF_BLK value
 *
 *  parameters: N/A
 *
 *  returns: the index of the allocated block
 *  or NO_FREE_BLK value if there's no free blocks
 */
int alloc_block() 
{
  int free_block_index = first_free_block();

  if (free_block_index == NO_FREE_BLK){

    return NO_FREE_BLK;
  }

  fat[free_block_index] = EOF_BLK;

  return free_block_index;

}

/*
 *  allocates a empty block as a next block of a given block
 *
 *  parameters:
 *    b = first block
 *
 *  returns:
 *    the index of the second block or
 *    NOT_EOF if the first block had a different value from EOF_BLK or
 *    NO_FREE_BLK if there's not additional free blocks to allocate
 */
int add_next_block(int b) 
{
  int next_block_index = first_free_block();

  // First block need to be the last EOF value
  if (fat[b] != EOF_BLK){
    return NOT_EOF;
  }
  
  if (next_block_index == NO_FREE_BLK) {
    return NO_FREE_BLK;
  }
 
  fat[b] = next_block_index;
  fat[next_block_index] = EOF_BLK;
  
  return next_block_index;
    
}
