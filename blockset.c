#include "profs.h"

/*
 *  Calculates the offset of dentry and fat table in memory
 
 *  return: position in file after dentry and fat (in bytes)
 */
int blocks_offset()
{
  return sizeof(str_t) * NUM_DENTRY + sizeof(int) * NB_BLOCKS; 
}

/*
 *  Calculates the offset of dentry, fat table in memory and a given number
 *  of blocks 
 * 
 *  return: position in file the tables and the blocks (in bytes)
 */
int block_offset(int b) 
{
  return sizeof(str_t) * NUM_DENTRY + sizeof(int) * NB_BLOCKS + b * BLOCK_SIZE;
}

/*
 *  reads the block number b in file fp into the buff string
 
 *  return value: number of elements readed
 */
int read_block(int b, char *buff, FILE *fp) 
{
  fseek(fp, block_offset(b), SEEK_SET);

  return fread(buff, 1, BLOCK_SIZE, fp);
}

/*
 *  writes the string buff into the block number nb
 *  of the file *fp
 *
 *  return value: number of elements written. 
 */
int write_block(int bn, char *buff, FILE *fp) 
{
  fseek(fp, block_offset(bn), SEEK_SET);
  return fwrite(buff, 1, BLOCK_SIZE, fp);
}
