#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "profs.h"

int main(int argc, char **argv)
{

  int opt_counter;
  int help = 0;
  int info = 0;
  char *subcommand = NULL;
  char *regular_arg = NULL;
  char *size_arg = NULL;
  char *name_arg = NULL;
  char *dest_arg = NULL;
  char options[3];
 
  /* No arguments or options provided */
  if (argc == 1) {
    printf("%s\n", NO_ARGS_MSG);  
    return EXIT_FAILURE;  
  }

  /* Parsing options and arguments*/
  while (1) 
  {
    
    int option_index = 0;
    char current_option;

    static struct option long_options[] = 
    {
        {"help",    no_argument,       NULL,  'h'},
        {"list",    no_argument,       NULL,  'l'},
        {"name",    required_argument, NULL,  'n'},
        {"size",    required_argument, NULL,  's'},
        {"dest",    required_argument, NULL,  'd'},
        {"info",    no_argument,       NULL,  'i'},
        {NULL,      0,                 NULL,    0}
    };

    opt_counter = getopt_long(argc, argv, "-:hln:s:d:i", long_options, &option_index);

    /* terminates the program if there are more than two options (- or --) */
    if (options[2])
    {
      printf("The number of options allowed was exceeded. Type profs --help for more information.\n");
      return EXIT_FAILURE;
    }

    /* exit the loop when all options and arguments where read or if the help option was provided */
    if (opt_counter == -1 || help)
      break;
  
    switch (opt_counter) 
    {
      /* Regular arguments (not options - or --) */
      case 1:
        if (!subcommand)
          subcommand = optarg;
        else if (subcommand && !regular_arg)
          regular_arg = optarg;
        break;

      /* options with no arguments*/
      case 'h': 
        current_option = opt_counter;
        help = 1;
        strncat(options, &current_option, 1);
        break;

      case 'l':
        current_option = opt_counter;
        strncat(options, &current_option, 1);
        break;

      case 'n':
        current_option = opt_counter;
        strncat(options, &current_option, 1);
        name_arg = optarg;
        break;

      case 's':
        current_option = opt_counter;
        strncat(options, &current_option, 1);
        size_arg = optarg;
        break;

      case 'd':
        current_option = opt_counter;
        strncat(options, &current_option, 1);
        dest_arg = optarg;
        break;

      case 'i': 
        current_option = opt_counter;
        info = 1;
        strncat(options, &current_option, 1);
        break;

      /* unknown option*/
      case '?':
        printf("Unknown option. Type profs --help for more information.\n");
        return EXIT_FAILURE;

      /* missing argument for a option*/
      case ':':
        printf("Missing argument for option %c.\n", optopt);
        return EXIT_FAILURE;

      /* another weird error */
      default:
        printf("Error in getopt function return: code 0%o\n", opt_counter);
      }
  }

    if (help)
    {

      display_help(subcommand);
      return EXIT_SUCCESS;
    }

    
    /* after this moment we use the memory file*/
    FILE *fp = open_fs("profs-memory");
    int command_code ;
    int exit_code = 0;

    if (fp == NULL)
    {
      dprintf(STDERR_FILENO, "Error trying to open the memory file\n");

      return EXIT_FAILURE;
    }

    /* NEW COMMAND */
    if (strcmp("new", subcommand) == 0)
    {
      if (regular_arg == NULL)
      {
        printf("Please provide a name for the file. Type 'profs new --help' for more information.\n");
        exit_code = 1;
      }
      else if(options[0] > 0 && options[0] != 's')
      {
        printf("Error with option '%c'. Type 'profs new --help' for more information", options[0]);
        exit_code = 1;
      }
      else if (options[0] != 's' && argc > 3 )
      {
        printf("Command '%s' only accepts the <fileName> argument. Type 'profs new -h' for more information.\n", subcommand);
        exit_code = 1;
      }
      else
      {
        command_code = create_file(fp, regular_arg, parse_size(size_arg));
        printf("File '%s' created succesfully.\n", regular_arg);
        exit_code = (command_code >= 1) ? 1 : 0;
      }
    }
    /* DELETE COMMAND*/
    else if (strcmp("delete", subcommand) == 0)
    {
      if (regular_arg == NULL)
      {
        printf("Please provide a name for the file. Type 'profs new --help for more information.\n");
        exit_code = 1;
      }
      else
      {
        command_code = delete_file(regular_arg);
        printf("File '%s' deleted succesfully.\n", regular_arg);
        exit_code = (command_code >= 1) ? 1 : 0;
      }
    }

    /* FORMAT COMMAND*/
    else if (strcmp("format", subcommand) == 0)
    {
      if (options[0])
      {
        printf("Format command does not accept any options. Type 'profs format --help' for more information.\n");
        exit_code = 1;
      }
      else
      {
        char buffer[2];

        printf("Are you sure you want to delete all files? (Y/n): ");
        fgets(buffer, sizeof buffer, stdin);

        if(strcmp(buffer, "Y") == 0){

          command_code = format_memory(fp, "profs-memory");
          printf("Memory formated\n");
          exit_code = (command_code >= 1) ? 1 : 0;
          return 0; // We have to exit here because memory doesnt exist anymore
          
        }
        else
          return 1;  
      }
    }

    /* OPEN COMMAND*/
    else if (strcmp("open", subcommand) == 0)
    {
      if (regular_arg == NULL)
      {
        printf("Please provide a name for the file. Type 'profs new --help for more information.\n");//NAME_is_missing_error
        exit_code = 1;
      }
      else
      {
        command_code = display_file(regular_arg, fp);
        exit_code = (command_code >= 1) ? 1 : 0;
      }
    }

    /* LIST COMMAND */
    else if (strcmp("list", subcommand) == 0)
    {
      
      if (options[0] && options[0] != 'i'){
        printf("%s Type 'profs list --help' for more informaiton.\n",MISS_IN_ARGS_MSG);//eror in options or qrrgument
        exit_code = 1;
      }
      else
      {
        command_code = list_files(options[0]);
        exit_code = (command_code >= 1) ? 1 : 0;
      }
    }

    /* IMPORT COMMAND */
    else if (strcmp("import", subcommand) == 0)
    {
      if (regular_arg == NULL || options[0])
      {
       printf("%s Type 'profs import --help' for more information.\n",MISS_IN_ARGS_MSG);//error in options qnd arrgument
      }
      else
      {
        
        command_code = import_file(regular_arg, fp);
        printf("File succesfully copied into profs.\n");
        exit_code = (command_code >= 1) ? 1 : 0;
      }
    }

    /* EXPORT COMMAND */
    else if (strcmp("export", subcommand) == 0)
    {
      if (regular_arg == NULL || options[0] != 'd')
      {
       printf("%s. Type 'profs export --help' for more information.\n",MISS_IN_ARGS_MSG);//error in options and arg
      }
      else
      {
        
        command_code = export_file(regular_arg, dest_arg, fp);
        printf("File %s succesfully copied to %s.\n", regular_arg, dest_arg);
        exit_code = (command_code >= 1) ? 1 : 0;
      }
    }

    /* VIEW COMMAND */
    else if(strcmp("view", subcommand) == 0)
    {
      if (!regular_arg){
        printf("profs: Please provide an argument for command view.\n");
        exit_code = 1;
      }
      else if (strcmp("dentry", regular_arg) == 0) 
      {
        print_dentry();
      }
      else if (strcmp("fat", regular_arg) == 0)
      {
        print_fat();
      }
      else
      {
        printf("Error: unknown subcommand %s. Type 'profs view --help' for more information.", regular_arg);
        exit_code = 1;
      }
    }
    else
    {
      printf("profs: '%s' is not a profs command. See 'profs --help'.\n", subcommand);
    }

    close_fs(fp);
   
  
  if(exit_code > 0)
  {
    printf("An error happened during execution.\n");
  }
   return exit_code;
}