#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "profs.h"

/*
 * Open tthe file, if is new initializes fat and dentry
 * if the file exists, read the fat and dentry tables
 *  
 */
FILE *open_fs(char *file_name) 
{
  FILE * fp;
  
  if ( (fp = fopen(file_name, "r+")) == NULL) 
  {
    if ( (fp = fopen(file_name, "w+")) == NULL) 
    {
      perror("Cannot open nor create the FS memory file");
      return NULL;
    } else { // create the file from zero
      printf("Creating from zero %s\n", file_name);
      init_dentry();
      init_fat();
    }
  } else { // Read fs already created
    rewind(fp);
    /* reads the dentry and fat tables from the memory and copy
    them into the respective arrays (in ram memory)*/
    fread(get_dentry(), sizeof(str_t), NUM_DENTRY, fp);
    fread(get_fat(), sizeof(int), NB_BLOCKS, fp);
  }
  return fp;
}

/*
 *  implemented a by professor
 * 
 */
void close_fs(FILE *fp)
{
  rewind(fp);

  /* update dentry and fat table in memory */
  fwrite(get_dentry(), sizeof(str_t), NUM_DENTRY, fp);
  fwrite(get_fat(), sizeof(int), NB_BLOCKS, fp);

  fclose(fp);
}

/*
 *  Creates a file of name file_name and size file_size
 *  into the fs virtual memory
 * 
 *  returns: -1 if no space en dentry, -2 if no blocks available
 *            0 if no error
 */
int create_file(void *fp, char *file_name, size_t file_size)
{
  /* error parsing the size argument */
  if (file_size == 0)
  {
    printf("Error parsing the size of options -s\n");
    return 1;
  }
 
  int entry_index, block_index;
  entry_index = write_first_free(file_name);
  /* no more place for new files in fs */
  if (entry_index == NUM_DENTRY)
    return 2;

  block_index = alloc_block();
  /* no more free blocks */
  if (block_index == NO_FREE_BLK)
    return 3;

  size_t total_blks = calculate_blocks(file_size);

  /* update dentry with the initial block */
	get_dentry()[entry_index].num = block_index; 


  char buffer[BLOCK_SIZE];

	for (int i = 0; i < total_blks; i++)
	{
		snprintf(buffer, BLOCK_SIZE, "[Bytes in block %d]", block_index);
		write_block(block_index, buffer, fp);

    /* avoid write an extra block in the last iteration*/
    if (total_blks - i > 1)
		  block_index = add_next_block(block_index);
	}

  return 0;

}

/* Parse a numeric string ino a size_t number*/
size_t parse_size(char *size_arg)
{
  char *ptr;

  if (!size_arg)
    return 1;

  return strtoul(size_arg, &ptr, 10);

}

/* what do you think it does? */
void print_dentry(){
  str_t *dentry = get_dentry();

  printf("  FILE NAME  | BLOCK #\n");
  for (int i = 0; i < NUM_DENTRY; i++)
  {
    printf("%12s | %d \n", dentry[i].str, dentry[i].num);
  }

  return;
}

/* what do you think it does? */
void print_fat(){
  int *fat = get_fat();

  printf("INDEX   | MEMORY BLOCK\n");
  for (int i = 0; i < 50; i++)
  {
    printf("%6d \t|  %d \n", i, fat[i]);
  }

  return;
}

/* Calculate the number of blocks required for a given file size in bytes */
size_t calculate_blocks(size_t file_size)
{
  size_t temp_blk = file_size / 1024;

  if (temp_blk == 0)
    return 1;
  else if (file_size % 1024 == 0)
    return temp_blk;
  else
    return temp_blk + 1;
}

/* Print in the terminal the content of a file */
int display_file(char *filename, void *ptr)
{
	char buffer[BLOCK_SIZE];
  int current_blk;
  int dentry_index = search_entry(filename);
  int number_blocks;
  

  if (dentry_index < NUM_DENTRY) 
	{
		current_blk = get_dentry()[dentry_index].num;

		while (1)
    {
      read_block(current_blk, buffer, ptr);   
      printf("%s", buffer);
      memset(buffer,0, BLOCK_SIZE);

    if (next_block(current_blk) == -1)
        break;
    
      current_blk = next_block(current_blk); 
    }
  
    return 0;
	}	
	
	return 1;
}

/* Print the content of a given block in console */
void print_block(int block_number, void *ptr)
{
  char buff[BLOCK_SIZE];
  read_block(block_number, buff, ptr);  
  printf("%s", buff);
}

/*
 *  Returns the number of blocks allocated for the file_name file
 *  or returns 0 if the file does not exist
 */
int get_number_blks(char *file_name)
{
  int dentry_ind = search_entry(file_name);

  if (dentry_ind == NUM_DENTRY)
    return 0;
  
  int current_block = get_dentry()[dentry_ind].num;
  int counter = 1; // If the entry exists, it has at least one block

 while (1)
    {
   
      if (next_block(current_block) == -1)
        break;

      current_block = next_block(current_block);
      counter++;
    }

    return counter;
}

/*
 *  Returns the number of blocks allocated for the file_name file
 *  or returns 0 if the file does not exist
 */
int list_files(char option)
{
  int with_info = (option == 'i') ? 1 : 0;

  for (int i = 0; i < NUM_DENTRY; i++ ){
    if (check_entry(i)){
      printf("%s", return_entry(i));

      if (with_info)
        printf("\t(%d blocks)\n", get_number_blks(return_entry(i)));
      else
        printf("\n");
    }
  }
    return 0;
}

/*
 *  Delete the references in dentry and fat of a given file
 *
 *  
 */
int delete_file(char *file_name) 
{
  int dentry_ind = search_entry(file_name);

  if (dentry_ind == NUM_DENTRY)
    return 1;

  
  int current_block = get_dentry()[dentry_ind].num;
  int number_blocks = get_number_blks(file_name);
  int temp_block;

  /* delete dentry entry */
  clear_entry(dentry_ind);

  /* delete the fat sequence of blocks*/
  for(int i = 0; i < number_blocks; i++){
    temp_block = next_block(current_block);
    clear_block(current_block);
    current_block = temp_block;
    }
  
  return 0;
  
}

/* Delete the profs-memory file */
int format_memory(void *fp, char* filename)
{

  fclose(fp);

  if (remove(filename) != 0)
  {
    printf("Error formating memory.\n");
    return 1;
  };

  return 0;

}

/* Copy a file from the internal profs memory to a given location in external storage location */
int export_file(char *src_file, char *dest_file, void *fp_local)
{
  FILE *fp_ext;
  int local_file_ind = search_entry(src_file);

 
	if ( (fp_ext = fopen(dest_file, "wb")) == NULL) 
	{
    perror("Cannot open or create the destination file.\n");
		return 1;
	} 

  if (local_file_ind == NUM_DENTRY)
  {
    printf("The source file does not exists.\n");
    fclose(fp_ext);
    return 2;
  }

  char buffer[BLOCK_SIZE];
  char dest_buff[BLOCK_SIZE];
  int ext_block_number = 0;
  int current_blk = get_dentry()[local_file_ind].num;
  int no_blocks = get_number_blks(src_file);


  while (1)
	{	
		read_block(current_blk, buffer, fp_local);
    fseek(fp_ext, ext_block_number * BLOCK_SIZE, SEEK_SET);
    fprintf(fp_ext, "%s", buffer); // or "%d\nd";
    current_blk = next_block(current_blk);

    if (current_blk == -1) {
      break;
    }
    ext_block_number++;
  }

	fclose (fp_ext);
	return 0;
}

/* Copy a external file into the fs memory */
int import_file(char *ext_filename, void *fp)
{
  FILE *fp_ext;

	if ( (fp_ext = fopen(ext_filename, "rb")) == NULL) 
	{
    perror("Cannot open the external file.\n");
		return 1;
	} 

   /* Get size of source file*/
  fseek(fp_ext, 0L, SEEK_END);
  long file_size = ftell(fp_ext);
  rewind(fp_ext);

  /* empty file */
  if (file_size == 0)
    return 1;

  int entry_index, block_index;
 
  char *newfilename = get_simplified_filename(ext_filename);
 
  entry_index = write_first_free(newfilename);
  /* no more place for new files in */
  if (entry_index == NUM_DENTRY)
    return 2;

  block_index = alloc_block();
  /* no more free blocks */
  if (block_index == NO_FREE_BLK)
    return 3;

  size_t total_blks = calculate_blocks(file_size);

  printf("Importing %ld bits of data into %lu blocks of memory...\n", file_size, total_blks);
  
  /* update dentry with the initial block */
	get_dentry()[entry_index].num = block_index; 

	char buffer[BLOCK_SIZE];

  for (int i = 0; i < total_blks; i++)
	{

    fread(buffer, BLOCK_SIZE, 1, fp_ext); 
		write_block(block_index, buffer, fp);
    memset(buffer, 0, BLOCK_SIZE);

    /* avoid write an extra block in the last iteration*/
    if (total_blks - i > 1)
		  block_index = add_next_block(block_index);
      
  }

  fclose(fp_ext);
  return 0;
}

/* Removes the path /--/--/filename of the file */
char *get_simplified_filename(char *filename)
{
  
  if (filename[0] != '/')
  {
    return filename;
  }

  // Function obtained from: https://stackoverflow.com/questions/21978592/how-to-get-the-last-part-of-a-string-in-c
  int n = strlen(filename);
  char* suffix = filename + n;

  while (0 < n && filename[--n] != '/');
    if (filename[n] == '/') 
    {
      suffix = filename + n + 1;
      filename[n] = '\0';
    }

    printf("The new filename is: %s\n", suffix);
    return suffix;
}