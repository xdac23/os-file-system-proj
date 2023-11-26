#include <stdio.h>

#define NB_BLOCKS 512
#define BLOCK_SIZE 1024
#define NUM_DENTRY 10
#define STR_LEN 256
#define NO_FREE_BLK -2


/* Console help messages and errors */
extern const char *NO_ARGS_MSG;
extern const char *HELP_MSG;
extern const char *HELP_LIST;
extern const char *HELP_NEW;
extern const char *HELP_DELETE;
extern const char *HELP_FORMAT;
extern const char *HELP_OPEN;
extern const char *HELP_IMPORT;
extern const char *HELP_EXPORT;
extern const char *HELP_VIEW;
extern const char *command;
extern const char *MISS_IN_ARGS_MSG;


/* dentry table functions*/
typedef struct 
{
  int num;
  char str[STR_LEN];
} str_t;

void clear_entry(int i);

void init_dentry(void) ;

str_t *get_dentry() ;

char *return_entry(int i) ;

int check_entry(int i);

int return_first_entry() ;

int write_entry(int i, char *str);

int write_first_free(char *str);

int search_entry(char *str);

/* 
   FAT table functions
*/
void init_fat();

int *get_fat();

int eof_block(int i);

int next_block(int i);

int first_free_block();

int alloc_block();

int add_next_block(int b);

void clear_block(int i);

/* blocset functions*/
int block_offset(int b);

int read_block(int b, char *buf, FILE *fp);

int write_block(int bn, char *buf, FILE *fp);

/* oscafs functions */

FILE *open_fs(char *su_file);

void close_fs(FILE *fp);

int create_file(void *fp, char *file_name, size_t file_size);

size_t parse_size(char *size_arg);

void print_dentry();

void print_fat();

size_t calculate_blocks(size_t file_size);

int delete_file(char *file_name);

int display_file(char *filename, void *ptr);

int list_files(char option);

int format_memory(void *fp, char* filename);

int export_file(char *src_file, char *dest_file, void *fp_local);

int import_file(char *ext_filename, void *fp);

char *get_simplified_filename(char *filename);

int get_number_blks(char *file_name);

void print_block(int block_number, void *ptr);

 int display_help(char* command);