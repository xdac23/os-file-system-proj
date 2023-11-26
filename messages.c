#include <string.h>
#include <stdio.h>

const char *NO_ARGS_MSG = 
    "ERROR  : Invalid Command \n"
    "NO ARGUMENT USED\n"
    "usage  : profs [--help] [--version] [--path]\n"
    "              <command> [<args>]\n"
    "\n"
    "Type `./profs [CMD] [OPTION] [FILENAME]' to DO operations :\n"
    "1.HELP       --  2.LIST       --   3.NEW \n"
    "4.Delete     --  5.FORMAT     --   6.OPEN   \n"
    "8.IMPORT     --  7.EXPORT     --   9.ViEW  \n\n" 
    "FOR MORE INFORMATION : Type 'profs --help' or 'profs -h' to list available subcommands.\n";
    
const char *MISS_IN_ARGS_MSG =
"\n\n"
"\t\t\tERROR : INVALID Command\n\n"
"ERRORS in the ARGUMENT or OPTIONS\n\n"
"Type `./profs [ARG] [OPTION] [FILENAME]' to DO operations :\n\n"
"ARG:"
    "\t1.HELP       --  2.LIST       --   3.NEW \n"
    "\t4.Delete     --  5.FORMAT     --   6.OPEN   \n"
    "\t8.IMPORT     --  7.EXPORT     --   9.ViEW  \n\n" 
"FOR MORE INFORMATION : Type 'profs --help' or 'profs -h' to list available subcommands.\n"
"\n\n"
"\t\t\t<-------------- TRY : -------------->\n\n"
;

const char *HELP_MSG = 
    "HELP PAGE:"
    "\n"
    "This Page will help you to know a brief sammaries of commands\n\n"
    "Type `./profs [CMD] [OPTION] [FILENAME]' to DO FUNCTIONS BELLOW :\n"
    "1.HELP       --  2.LIST       --   3.CreateFile \n\n"
    "4.DeleteFile --  5.FORMAT     --   6.OpenFile   \n"
    "8.ImportFile --  7.ExportFile --   9.ViewTable   \n" 
    "\n\n"
    //----------------------------------------------------------------------------
    "ARGUMENTS and OPTIONS :"
    "\n\n\n"
    //-------------------
    //help operation
    "\t1_ HELP    : \n\n "
    "\t            Shows the general information of the program.\n\n"
    "\tUSAGE: profs [OPTION]\n"
    "\t\t ADDITIONAL OPTIONS:\n"
    "\t\t -h,   --help \n"
    "\n\n"
    //-------------------
    //list operation
    "\t2_ LIST    : \n\n "
    "\t            Displays the list of files in the file system with size.\n\n"
    "\tUSAGE: profs list [OPTION]\n"
    "\t\t ADDITIONAL OPTIONS:\n"
    "\t\t -d,   --details \n"
    "\n\n"
    //-------------------
    //New Operation
    "\t3_ NEW     : \n\n "
    "\t            Create a file with filename and size.\n\n"
    "\tUSAGE: profs new <filename> [OPTION]\n"
    "\t\t ADDITIONAL OPTIONS:\n"
    "\t\t -s,   --size\n"
    "\n\n"
    //------------------
    //Delete Operation
    "\t4_ DELETE  : \n\n "
    "\t            Delete a Filename from the fs memory.\n\n"
    "\tUSAGE: profs delete <filename>"
    "\n\n"
    //------------------
    //Format OPeration
    "\t5_ FORMAT  : \n\n "
    "\t            Delete all files in memory.\n\n"
    "\tUSAGE: profs format"
    "\n\n"
    //------------------
    //open operation
    "\t6_ OPEN    : \n\n "
    "\t            Display the content of the filename in fs memory.\n\n"
    "\tUSAGE: profs open <filename> \n"
    "\n\n"
    //------------------
    //inport operation
    "\t7_ IMPORT  : \n\n "
    "\t            Copy externalFile into the fs memory.\n\n"
    "\tUSAGE: profs import <externalFile> \n"
    "\n\n"
    //------------------
    //export operation
    "\t8_ EXPORT  : \n\n "
    "\t            Copy an internalFile from fs memory into external location destination.\n\n"
    "\tUSAGE: profs export <internalFile> [OPTION] <distination>\n"
    "\t\t ADDITIONAL OPTIONS:\n"
    "\t\t -d,   --dest \n"
    "\n\n"
    //------------------
    //viw operation
    "\t9_ VIEW   : \n\n "
    "\t            Displays the tables (Dentry,FAT).\n\n"
    "\tUSAGE: profs view <tablename> \n"
    "\n\n"
    //-----------------
    //FOOTER
    "For more details type 'profs -h [nameOfCMD]'\n\n\n\n"
    ;
 //------------------------------------------------------
    /*0_help help page*/
    const char *HELP_HELP = 
    "\n\n"
    "NAME \n"
    "\t\t HELP - Display information about  commands. "
    "\n\n"
    "SYNOPSIS \n"
    "\t\t ./profs [OPTION] [CMD]..."
    "\n\n"
    "DESCRIPTION \n"
    "\t\t HELP ARGUMENT Display information about  commands and a brief summaries of it."
    " \n\n "
    "\t\t OPTIONS :\n\n"
    "\t\t\t-h,  --help\n\n"
    "\t\t EXAMPLES : \n\n"
    "\t\t\t 1_ '*./profs -h list' \n\n"
    "\t\t\t 1_ '*./profs --help help '\n\n "    
    
    ;
    /*1_help list page*/
    const char *HELP_LIST = 
    "\n\n"
    "NAME \n"
    "\t\t list - Displays Files and Sizes"
    "\n\n"
    "SYNOPSIS \n"
    "\t\t ./profs list [OPTION]..."
    "\n\n"
    "\t\t ./profs l [OPTION]..."
    "\n\n"
    "DESCRIPTION \n"
    "\t\t List ARGUMENT displays the list of files in the file system and has additional opptions (details) \n\t\twhich displays the siwe in bytes of each file in the fs mempry \n\n "
    "\t\t ADDITIONAL OPTIONS :\n\n"
    "\t\t\t-d,  --details | displays size of each file\n\n"
    "\t\t EXAMPLES : \n\n"
    "\t\t\t 1_ '*./profs list' \n\n"
    "\t\t\t 1_ '*./profs list -d' | or | './profs list --details'\n\n "    
    
    ;
    /*2_NEW help page*/
     const char *HELP_NEW = 
    "\n\n"
    "NAME \n"
    "\t\t new - CREATE FILE "
    "\n\n"
    "SYNOPSIS \n"
    "\t\t ./profs new <fileName> [OPTION]..."
    "\n\n"
    "DESCRIPTION \n"
    "\t\t NEW ARGUMENT create a file with nale <fileName> and has additional opptions (size) \n\t\twhich configer the size siweInByte in the fs memory \n\n "
    "\t\t ADDITIONAL OPTIONS :\n\n"
    "\t\t\t-s,  --size |  Determines the size of created files\n\n"
    "\t\t EXAMPLES : \n\n"
    "\t\t\t 1_ '*./profs new <nameFile>' \n\n"
    "\t\t\t 1_ '*./profs new -s 123 ' | or | './profs new --size=123'\n\n " 
    ;

    /*3_DELETE help page*/
     const char *HELP_DELETE = 
    "\n\n"
    "NAME \n"
    "\t\t delete - Delete FILE "
    "\n\n"
    "SYNOPSIS \n"
    "\t\t ./profs delete <fileName> ..."
    "\n\n"
    "DESCRIPTION \n"
    "\t\t Delete ARGUMENT remove a file <fileName> from the fs memory\n\n "

    "\t\t EXAMPLES : \n\n"
    "\t\t\t 1_ '*./profs delete <nameFile>' \n\n" 
    ;  
     /*4_format help page*/
     const char *HELP_FORMAT = 
    "\n\n"
    "NAME \n"
    "\t\t format - DELETE ALL FILES"
    "\n\n"
    "SYNOPSIS \n"
    "\t\t ./profs format ..."
    "\n\n"
    "DESCRIPTION \n"
    "\t\t FORMAT  ARGUMENT removes all file in the fs memory \n\t\t NOTE:IT ASKS TO CONFIRM THE FORMAT OPERATION\n\n "
    "\t\t EXAMPLES : \n\n"
    "\t\t\t 1_ '*./profs format' \n"
    "\t\t\t Are you sure you want to delete all files? (Y/n)\n"
    "\t\t\t    'Y' \n\n"
    ;
      /*5_OPEN help page*/
     const char *HELP_OPEN = 
    "\n\n"
    "NAME \n"
    "\t\t open - VIEW FILE "
    "\n\n"
    "SYNOPSIS \n"
    "\t\t ./profs open <fileName> ..."
    "\n\n"
    "DESCRIPTION \n"
    "\t\t OPEN ARGUMENT Displays the content  a file <fileName> from the fs memory\n\n "

    "\t\t EXAMPLES : \n\n"
    "\t\t\t 1_ '*./profs open <nameFile>' \n\n" 
    ;  
    /*6_import help page*/
    const char *HELP_IMPORT = 
    "\n\n"
    "NAME \n"
    "\t\t import - COPY FILE TO FS MEMORY"
    "\n\n"
    "SYNOPSIS \n"
    "\t\t ./profs import <fileName>..."
    "\n\n"
    "DESCRIPTION \n"
    "\t\t IMPORT ARGUMENT Copy file from external system to the fs memory\n\n "
    "\t\t EXAMPLES : \n\n"
    "\t\t\t 1_ '*./profs import <externalFile>' \n\n"
    ;
     /*7_export help page*/
    const char *HELP_EXPORT = 
    "\n\n"
    "NAME \n"
    "\t\t export - COPY FILE TO EXTERNAL SYSTEM"
    "\n\n"
    "SYNOPSIS \n"
    "\t\t ./profs export <fileName> [OPTION] <destination> ..."
    "\n\n"
    "DESCRIPTION \n"
    "\t\t EXPORT ARGUMENT Copy file form internal fs memory to external system and has  options \n\t\twhich determine the destination of the file (location of exported file) \n\n "
    "\t\t ADDITIONAL OPTIONS :\n\n"
    "\t\t\t-d,  --dest | Determine the destination of the exported file\n\n"
    "\t\t EXAMPLES : \n\n"
    "\t\t\t 1_ '*./profs export <internalNameFile> -d <destination>' \n"
    "\t\t\t 1_ '*./profs export <internalNameFile> --dest=<destination>' \n\n"
     
    ;
     /*8_VIEW help page*/
    const char *HELP_VIEW = 
    "\n\n"
    "NAME \n"
    "\t\t view - Displays TABLES"
    "\n\n"
    "SYNOPSIS \n"
    "\t\t ./profs view <tableName>..."
    "\n\n"
    "DESCRIPTION \n"
    "\t\t VIEW ARGUMENT Displays the tables (DENTRY TABLE,FAT TABLR)\n\t\twhich give information about the allocated files in fs memory\n\n "
    "\t\t EXAMPLES : \n\n"
    "\t\t\t 1_ '*./profs view <fat>' \n"
    "\t\t\t 2_ '*./profs view <dentry>' \n\n"
    ;
   
 
    int display_help(char* command){  

        if(command == NULL){
            printf("%s\n", HELP_MSG); //GENERAL HELP PAGE 
            return 0;
        }
        
        if(strcmp(command, "list") == 0){
            printf("%s\n", HELP_LIST);//LIST HELP PAGE

        }
        else if(strcmp(command, "new")== 0){
            printf("%s\n", HELP_NEW);//NEW HELP PAGE
            
        }
        else if(strcmp(command, "delete")== 0){
            printf("%s\n", HELP_DELETE);//DELETE HELP PAGE
            
        }
        else if(strcmp(command, "format")== 0){
            printf("%s\n", HELP_FORMAT);//format HELP PAGE
            
        }
        else if(strcmp(command, "open")== 0){
            printf("%s\n", HELP_OPEN);//OPEN HELP PAGE
            
        }
        else if(strcmp(command, "export")== 0){
            printf("%s\n", HELP_EXPORT);//EXPORT HELP PAGE
            
        }
        else if(strcmp(command, "import")== 0){
            printf("%s\n", HELP_IMPORT);//IMPORT HELP PAGE
            
        }
        else if(strcmp(command, "view")== 0){
            printf("%s\n", HELP_VIEW);//VIEW HELP PAGE
            
        }

        return 0;
         
    }
