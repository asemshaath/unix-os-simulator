/*
    Asem Shaath
    CMSC 216 section 0201
    Project #6
    Larry Herman

    This file has the proporites of the ournix os structrue. 
    Look at the digram below:


    /  (Root directory)
    |
    |____216___216public___
          |           |
          |           |
          |           |_______discutions____examples
          |                                           
          |______project01/                           
          |           |
          |           |
          |           |______main.c -> tests.c                                
          |
          |______project02/
          |
          |
          |______file-description.txt

    I pledge on my honor that I have not given or received 
    any unauthorized assistance on this project.

*/

/*
  This struct is to keep track with our location, and
  to know what is the root (Very beggining).
*/
typedef struct ournix {
  struct dir *root; 
  struct dir *current; 
} Ournix;

/*
  This struct is to simualte the structure of the
  file by providing some proporties like the parent
  of the file and the name, etc.
*/
typedef struct file {
  struct dir *parent;
  struct file *next;
  char *name;
  int timestamp;
} File;

/*
  This struct is to simualte the structure of the
  directory by providing some proporties like the parent
  of the directory and the name, etc.
*/
typedef struct dir {
  struct dir *parent;
  struct dir *child;
  struct dir *next;
  struct file *child_file;
  char *name;
} Directroy;
