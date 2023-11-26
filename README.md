# Operating Systems
## File system project

PROFS (PROject File System) is high level shell program for simulating a FAT-like file system by using a file as a storage unit.
PROFS program creates or updates a file called *profs-memory* which works as the storage unit. The total capacity of this storage is of 512 KBytes, or more precisely, 524288 bytes.

The program is able to do te following operations:

-Creating a file in the storage with a given name and size

-Delete a file in the storage

-Format the storage file

-Open a file in console

-List the files in the storage system. 

-Import and export files from fs memory to external system memory. 

-View the file allocation and DEntry tables.

# Project structure
The project repository contains the following files:
```
.
├── Makefile                
├── profs                     # Manual page 
├── profs.h                   # profs header C file
├── profs.c                   # main C file
├── fsfunctions.c             # Custom functions implementation
├── messages.c                # C file containing help messages
├── dentry.c                  # Functions for managing DEntry table
├── fat.c                     # Functions for managing FAT table
├── blockset.c                # Functions for managing blocks and pointers
└── README.md
```

# Execution requisites
In a linux environment, make sure you have the following installed prior to running the project
1. C/C++ compiler (`sudo apt install build-essential`)
2. make command (`sudo apt install make -y`).

# Setup 
### Manual page
From the project location, execute the following command:

`sudo cp profs /usr/share/man/ma1/profs`

This will add the custom manual to the functions documentation of linux. Execute `man profs` for print the complete program documentation.

### First compilation
In the project location, execute `make` to compile the program

### During runtime
After running some of the commands of the project (except for the --help option), the file *profs-memory* will be created, with an initial size of around 3 kB (dentry and fat tables size) and can reach a maximun size of 515 KB. This file works as a persistance storage location for the program, so any action performed during runtime will be saved in this file. This memory file can be deleted using the command `format`.

### After execution
In the program location run `make clean` to delete the files generated during compilation and other addional files.

# Commands and options
The following list display the list of all available commands of the program:

1. `$ profs --help` or `$./profs -h`
   
    Shows the general help of the program 


2. `$ profs list`
   
    Displays the list of files in the file system

    Additional options:
        --info or -i displays the blocks of memory of each file in the fs memory

3. `$ profs new <fileName> --size=sizeInBytes` or `profs new <fileName> -s sizeInBytes`
   
    Creates a file with the name fileName and the size sizeInByte in the fs memory. 

4. `$ profs delete <fileName>`
   
    Delete the file fileName from the fs memory

5. `$ profs format`

    Delete the storage file

6.  `$ profs open <fileName>`
   
    Displays the content of the fileName file in console

7.  `$ profs import <externalFile>` 
   
    Copy into the fs storage the externalFile file

8.  `$ profs export <internalFile> --dest=<destination>` or `$ profs export <internalFile> -d <destination>`

    Copy the file internalFile from the fs memory to the external location destination

9.  `$ profs view <tableName>`

    Displays the DENTRY table if tableName = dentry or the FAT table if tableName = fat.

# Implementation
The profs.c file contains the main function, which is responsible of the main flow of execution. Thanks to the getopt library, the command line arguments can be parsed and then the decision tree is executed with if statements.

The fsfunctions.c contains the functions for each command and additional helper functions for casting, printing and validating information.

Due time limitations, there are no management or documentation of error codes, even though all the functions returns 0 if the execution was successful or any other integer > 0 for each additional error. In the main function only two error codes are used, 0 for exit and 1 for a general error in execution (can be any error for any function).

The functions `open_fs` and `close_fs` are responsible for opening (or creating) and updating the profs-memory storage file, respectively. These functions are invoked in the main function directly.

The messages.c file contains the string constants containing the help messages and also the definition of the function `display_help` that is responsible of printing those messages.

The signature of functions provided in dentry.c, fat.c and blockset.c was not modified, so the program logic was creating takig as foundation those provided functions.

# Known and possible errors
1. Not all commands will display a specialize error message if the wrong options or arguments are provided. Therefore it may be possible execute the program writing a valid option value for a command that does not requiere that option.
2. The performance and behaviour of the program when working with big files was not tested (also applies for long terminal arguments).
3. The program logic was written in simple terms and with basic understanding of the C language. Refactoring/cleaning of different functions may be necessary.

# Licence
This project was implement as part of the course Operating Systems for the Master in Computer Networks offered at the Cnam university. Any copying without instructor's permission or any form of profit with this project is strictly prohibited.

*January 2023, Paris, France.*