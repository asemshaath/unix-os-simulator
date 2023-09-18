/*
    Asem Shaath
    CMSC 216 section 0201
    Project #6
    Larry Herman

    This file has all the functions that are required to create
    ournix operating system simulator. This project is to simulate 
    adding removing file/direcotry. It also moves towards every directory
    and leveas whatever directory the user wants. 

    I pledge on my honor that I have not given or received 
    any unauthorized assistance on this project.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ournix.h"

/*Helper functions prototypes
The description of each function 
is under the defenitions.
*/
void ls_helper(Directroy *dir, File *file);
int is_valid(const char *name);
File* file_exist(Ournix *const filesystem,const char *name);
Directroy* dir_exist(Ournix *const filesystem, const char *name);
void pwd_helper(Directroy *dir);
void rm_dir(Directroy *dir);
void rm_files(File *f);
int name_exist(Ournix *const filesystem, const char name[]);
int can_create(Ournix *const filesystem, const char name[]);
void free_dir(Directroy *dir);

/*helper functions defenition */

/*
    This function is used when we call rm to remove a directory,
    the purpose of this function is to remove all the files inside 
    that directory. 
*/
void rm_files(File *f) {
    if(f == NULL) {
        return;
    } 

    rm_files(f->next);
    f->parent = NULL;
    f->next = NULL;
    free(f->name);
    free(f);
}

/*
    This is a helper function for rm(). The purpose of 
    this function is to free each directory under that 
    direcory we need to delete.
*/
void free_dir(Directroy *dir) {
    dir->parent = NULL;
    dir->child = NULL;
    dir->next = NULL;
    dir->child_file = NULL;
    free(dir->name);
    free(dir);
}

/*
    This is a helper function function for rm(). The purpose
    of this function is to recurivly delete all the sub-direcories
    of the one we need to delete.
*/
void rm_dir(Directroy *dir) {
    Directroy *tmp = NULL;
    Directroy *c = NULL;

    if (dir == NULL) {
        return;
    }
    rm_files(dir->child_file);
    dir->child_file = NULL;

    if (dir->child != NULL) {
        rm_dir(dir->child);        
    }
    
    c = dir->next;
    while (c != NULL) {
        tmp = c;
        c = c->next;
        rm_dir(tmp);
    }
    free_dir(dir);
}

/*
    This is a helper function for touch() and mkdir().
    I implemented this function to check if we can create 
    a file or directory with that given name. 

    We are not able to create a file named '216' in grace 
    server, because we have a direcory with that name. Also,
    we can't create a file called '2/16' since it's an invalid 
    name.
*/
int can_create(Ournix *const filesystem, const char name[]) {
    /*is valid and name doesn't exist*/
    int res = 0;
    if (filesystem != NULL) {
        res = is_valid(name) && !name_exist(filesystem, name);
    }
    return res;
}

/*
    This function is a helper function for the helper 
    function can_create(). It basically checks if the given name
    exists in a file or a directory.  
*/
int name_exist(Ournix *const filesystem, const char name[]) {
    /* Check if file or directory exist */
    File *file = file_exist(filesystem,name);
    Directroy *dir = dir_exist(filesystem, name);
    int res = 0;
    
    if (file != NULL || dir != NULL){
        res = 1;
    }

    return res;
}

/*
    This is a helper function for pwd(). It recusrviley prints 
    the path of the current directory. 
*/
void pwd_helper(Directroy *dir){
    if (dir->parent == NULL) {
        printf("/");
    } else {
        pwd_helper(dir->parent);
        printf("%s/", dir->name);
    }
}

/*
This function takes the filesystem pointer and
the name of the directory to check whether that directory exist
in the current directory. If the name exist it will return 
a pointer of the directry, else it will return NULL.
*/
Directroy* dir_exist(Ournix *const filesystem, const char *name){
    Directroy *dir;
    Directroy *does_exist = NULL;

    /*Check if the name is in the files*/
    if (filesystem != NULL) {
        dir = filesystem->current->child;
        while (dir != NULL) {
            if (strcmp(name,dir->name) == 0) {
                does_exist = dir;
            }
            dir = dir->next;
        }
    }

    return does_exist;
}

/*
This function takes the filesystem pointer and
the name of the file to check whether that file exist
in the current directory. If the name exist it will return 
a pointer of the file, else it will return NULL.
*/
File* file_exist(Ournix *const filesystem, const char *name){
    File *file;
    File *does_exist = NULL;

    /*Check if the name is in the files*/
    if (filesystem != NULL) {
        
        file = filesystem->current->child_file;

        while (file != NULL) {
            if (strcmp(name, file->name) == 0) {
                does_exist = file;
            }
            file = file->next;
        }
    }

    return does_exist;
}

/*
This function takes a name to check if it's a valid name
for a file or a directory. If it has ., .., / it will be an 
invalid name for a file or directory. 
It returns 1 if it's valid and 0 if it's invalid.
*/
int is_valid(const char *name){

   /* result is assumed to be true (1) by default*/
   int res = 1;
   /*char first_letter = name[0];*/

   if (strcmp(name,"") == 0 ){
       res = 0;
   } else if(name == NULL){
       res = 0;
   } else if (  strcmp(name,".") == 0 ||
                strcmp(name,"..") == 0 ||
                strcmp(name,"/") == 0) {
        res = 0;
   } else if (  strchr(name, '.') != NULL ||
                strchr(name, '/') != NULL ) {
        res = 0;
   } else if (name[0] == '.' && strlen(name) > 1) {
       res = 1;
   }

   return res;
}

/*
This function takes directory pointer and file pointer.
The purpose of this function is to print the list of all the
files and directories in a sorted order. 
*/
void ls_helper(Directroy *dir, File *file){
        while (dir != NULL && file != NULL){
            /* print them in a sorted order */
            if (strcmp(dir->name, file->name) < 0){
                printf("%s/\n", dir->name);
                dir = dir->next;
            } else{
                printf("%s\n", file->name);
                file = file->next;
            }
        }
        while (dir != NULL){
            printf("%s/\n", dir->name);
            dir = dir->next;
        }
        while (file != NULL){
            printf("%s\n", file->name);
            file = file->next;
        }
}

/*required functions*/

/*
This function should be executed at the begginenig of
every simulation. The purpose of this function is to setup
the root directory and the current directory. Current directory
will be the root since it's done at the beggining of the simulation.
*/
void mkfs(Ournix *const filesystem){
    filesystem->root = malloc(sizeof(Directroy));
    filesystem->root->name = malloc(2*sizeof(char));

    strcpy(filesystem->root->name, "/");
    
    filesystem->root->child = NULL;
    filesystem->root->child_file = NULL;
    filesystem->root->parent = NULL;
    filesystem->root->next = NULL;
    
    filesystem->current = filesystem->root;
}

/*
This function add a new file to the current directories. It 
returns 1 if the file is added successfully, and 0 if the file 
is not added for some reasons such as invalid name (check is_valid() 
descreption) or that file were already exist in the current directory. 
*/
int touch(Ournix *const filesystem, const char name[]){
    File *tmp;
    File *curr, *pre;
    int result = 0;
    if(can_create(filesystem, name)){
        tmp = malloc(sizeof(File));
        tmp->name = malloc(strlen(name)+1);
        tmp->next = NULL;
        tmp->timestamp = 1;
        strcpy(tmp->name, name);
        tmp->parent = filesystem->current;
        curr = filesystem->current->child_file;
        pre = NULL;

        while (curr != NULL && strcmp(name, curr->name) > 0 ) {
            /* Get the right node*/
            /* It will be inserted between pre and curr */
            pre = curr;
            curr = curr->next;
        }
        if (pre == NULL) {
            tmp->timestamp = 1;
            tmp->next = curr;
            filesystem->current->child_file = tmp;
        } else if (curr == NULL) {
            tmp->timestamp = 1;
            pre->next = tmp;
        } else {
            tmp->timestamp = 1;
            pre->next = tmp;
            tmp->next = curr;
        }
        result = 1;
        
    } else if (file_exist(filesystem, name) != NULL) {
        tmp = file_exist(filesystem, name);
        tmp->timestamp = tmp->timestamp + 1;
        result = 1;
    }    
    return result;
}

/*
This function add a new directory to the current directories as a
subdirectory. It returns 1 if the directory is added successfully, 
and 0 if the directory is not added for some reasons such as invalid 
name (check is_valid() descreption) or that directory were already 
exist in the current directory. 
*/
int mkdir(Ournix *const filesystem, const char name[]){
    
    int result = 0;
    Directroy *tmp;
    Directroy *curr, *pre;

    if (can_create(filesystem, name)) {

        tmp = malloc(sizeof(Directroy));
        tmp->name = malloc(strlen(name)+1);
        tmp->parent = filesystem->current;
        tmp->child_file = NULL;
        tmp->child = NULL;
        strcpy(tmp->name, name);
        curr = filesystem->current->child;
        pre = NULL;
        while (curr != NULL && strcmp(name, curr->name) > 0 ) {
            /* Get the right node*/
            pre = curr;
            curr = curr->next;
        }
    
        if (pre == NULL) {
            tmp->next = curr;
            filesystem->current->child = tmp;
        } else if (curr == NULL) {
            pre->next = tmp;
        } else {
            pre->next = tmp;
            tmp->next = curr;
        }
        result = 1;
    } else if (dir_exist(filesystem, name) != NULL) {
        result = 1;
    }
    return result;
}

/*
This function lists all of the files and directories that are 
located in the specfied location by the parameter 'name'. It
returns 1 once the list is successfully printed;otherwise, it returns
0 when they are not printed for a reason such as filesystem was NULL
or name wasn't valid.
*/
int ls(Ournix *const filesystem, const char name[]){
    
    Directroy *dir;
    File *file;
    int result = 0;

    if (filesystem != NULL) {
        
        if (strcmp(name, ".") == 0 || strcmp(name, "") == 0) {
            /* print same level files and directories */
            dir = filesystem->current->child;
            file = filesystem->current->child_file;
            ls_helper(dir, file);
            result = 1;
        } else if (strcmp(name, "..") == 0) {
            dir = filesystem->current->parent->child;
            file = filesystem->current->parent->child_file;
            ls_helper(dir, file);
            result = 1;
        } else if (strcmp(name, "/") == 0){
            dir = filesystem->root->child;
            file = filesystem->root->child_file;
            ls_helper(dir, file);
            result = 1;
        } else {
            /*Iterate through the files and dirs*/
            file = file_exist(filesystem, name);
            dir = dir_exist(filesystem, name);

            if (file != NULL){
                printf("%s %d\n", file->name, file->timestamp);
                result = 1;
            } else if (dir != NULL){

                file = dir->child_file;
                dir = dir->child;
                
                ls_helper(dir, file);
                result = 1;
            }
        }
    }
    return result;
}

/*
This function changes the current directory to the 
specfied location by the parameter 'name'. 
It returns 1 if the directory changed succedfully, 
otherwise; it returns 0. 
*/
int cd(Ournix *const filesystem, const char name[]){
    Directroy *dir;
    int result = 0;

    if (filesystem != NULL) {
        if(strcmp(name, "") !=0 || name != NULL){
            if(strcmp(name, ".") == 0){
                result = 1;
            } else if (strcmp(name, "..") == 0) {
                filesystem->current = filesystem->current->parent;
                result = 1;
            } else if (strcmp(name, "/") == 0) {
                filesystem->current = filesystem->root;
                result = 1;
            } else {
                dir = filesystem->current->child;
                while (dir != NULL) {
                    if (strcmp(name, dir->name) == 0) {
                        filesystem->current = dir;
                        result = 1;
                    }
                    dir = dir->next;
                }
            }
        }
    }
    return result;
}

/*
This function prints the whole path of the current
directory. It doesn't return anything.
*/
void pwd(Ournix *const filesystem){

    Directroy *curr = filesystem->current;

    if(filesystem != NULL){

        if(filesystem->current != filesystem->root){
            pwd_helper(curr->parent);
            printf("%s\n", curr->name );
        } else {
            printf("/\n");
        }
    }
}

/*
    This function removes a specifc file or directory.
    The name of that will be in the parameter 'name'. The 
    function returns 1 if the file or directory is succesfully
    removed; otherwise, it returns 0. 

*/
int rm(Ournix *const filesystem, const char name[]){
    int result = 0;
    Directroy *dir, *prev ,*cur;
    File *file, *pre, *curr; 
    if (filesystem != NULL) {

       /*File is found? DELETE IT*/
        if ((file = file_exist(filesystem, name)) != NULL) {

            curr = filesystem->current->child_file;
            pre = NULL;

            while (curr != file) {
                pre = curr;
                curr = curr->next;
            }

            /*Delete the file*/

            if (pre == NULL) {
                filesystem->current->child_file = curr->next;
                curr->next = NULL;
                curr->parent = NULL;
                free(curr->name);
                free(curr);
            } else {
                pre->next = curr->next;
                curr->next = NULL;
                curr->parent = NULL;
                free(curr->name);
                free(curr);
            }            
        }

        if ((dir = dir_exist(filesystem, name)) != NULL) {

            cur = filesystem->current->child;
            prev = NULL;

            while (cur != dir) {
                prev = cur;
                cur = cur->next;
            }

            /*Delete the directory*/
            if (prev == NULL) {
                filesystem->current->child = cur->next;
                cur->next = NULL;
                cur->parent = NULL;
            } else {
                prev->next = cur->next;
                cur->next = NULL;
                cur->parent = NULL;
            }

            rm_dir(dir->child);
            free_dir(cur);
        }
    }

    return result;
}

/*
    This function removes the whole file system. All files and
    directories that the user create get deleted by calling this
    function.
*/
void rmfs(Ournix *const filesystem){
    rm_dir(filesystem->root);
}
