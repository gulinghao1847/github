//
//  main.c
//  570homework3
//
//  Created by linghao on 12-10-4.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"
#include "print_tree.h"
#define CHAR_NUM 50
#define CHAR_LEN 50
int msg_type=0;  //1: bst_file  2: bst_delete_file 3:avl_file  4:avl_delete_file;
int should_displayall=0;
int is_stdin=1;
char* file_name;


void process_avl(char* file_name, char* string_array){
    FILE* file;
    char temp_store_array[1026];
    avl_tree my_avl_tree=NULL;
    int is_taller=0;
    int depth=0;
    int i=0;
    int is_shorter=1;
    char is_right[30];
    clean_char_array(is_right);
    if (is_stdin==0) {                      //insert from  a file
        if ((file=fopen(file_name,"r"))==NULL) {
            fprintf(stderr,"can't open this file\n");
            exit(1);
        }
        
        //another function
        while (fgets(temp_store_array,1026,file)!=NULL) {
            i=i+1;
            clean_input(temp_store_array);
            //temp_store_array[strlen(temp_store_array)-1]='\0';
            my_avl_tree=insert_avl_tree(my_avl_tree,temp_store_array,&is_taller);
            if (should_displayall==1) {
                if(i!=1){
                  printf("\n");  
                }
                printf("Inserted \"%s\" (node %d):\n\n",temp_store_array,i);
                char a[256];
                strcpy(a,get_balance(my_avl_tree));
                printf("%s (%s)\n",my_avl_tree->key,a);
                print_avl_tree(my_avl_tree,depth,is_right);
                //printf("\n");
            }
        }
        
        //should display
        if (should_displayall==0) {
            char a[256];
            strcpy(a,get_balance(my_avl_tree));
            printf("%s (%s)\n",my_avl_tree->key,a);
            print_avl_tree(my_avl_tree,depth,is_right);
        }
    }
    else if(is_stdin==1){                     //insert from stdin
        while ((fgets(temp_store_array, 1026,stdin))!=NULL) {
            if (strlen(temp_store_array)>=1000) {
                fprintf(stderr,"the string is too long\n");
                exit(1);
            }
            i=i+1;
            clean_input(temp_store_array);
            my_avl_tree=insert_avl_tree(my_avl_tree,temp_store_array,&is_taller);
            if (should_displayall==1) {
                if (i!=1) {
                    printf("\n");
                }
                printf("Inserted \"%s\" (node %d):\n\n",temp_store_array,i);
                char a[5];
                strcpy(a,get_balance(my_avl_tree));
                printf("%s (%s)\n",my_avl_tree->key,a);
                print_avl_tree(my_avl_tree,depth,is_right);
                //printf("\n");
            }
        }
        if (should_displayall==0) {
            char a[256];
            strcpy(a,get_balance(my_avl_tree));
            printf("%s (%s)\n",my_avl_tree->key,a);
            print_avl_tree(my_avl_tree,depth,is_right);
        }
    }
    
    if (msg_type==4) {                  //delete all the elements from string_array, they are divided by  a space
        int where=0;        //indicate where we reach to in a char array
        int count=0;
        for (where=0;string_array[where]!='\0';) {
            char store_string[CHAR_LEN];
            int i=0;
            for (;string_array[where]!='\n'&&string_array[where]!='\0';where++,i++) {
                store_string[i]=string_array[where];
            }
            where++;
            store_string[i++]='\0';
            /*
            avl_tree_node* temp_node=find_avl_node(my_avl_tree,store_string);
            if (temp_node->left_child!=NULL&&temp_node->right_child!=NULL) {
                avl_tree_node* in_order_successor=find_in_order_successor(temp_node);
                char temp_char[1000];
                strcpy(temp_char,in_order_successor->key);
                my_avl_tree=delete_avl_tree(my_avl_tree,in_order_successor->key,&is_shorter);
                strcpy(temp_n
             ode->key,temp_char);
            }
            else
               my_avl_tree=delete_avl_tree(my_avl_tree,store_string,&is_shorter);
             */
            my_avl_tree=delete_option(my_avl_tree,store_string,is_shorter);
            count++;
            if (should_displayall==1) {
                printf("\n");
                printf("Deleted \"%s\":\n\n",store_string);
                if (my_avl_tree==NULL) {
                    printf("(EMPTY)\n");
                    //printf("\n");
                }
                else{
                    char a[5];
                    strcpy(a,get_balance(my_avl_tree));
                    printf("%s (%s)\n",my_avl_tree->key,a);
                    print_avl_tree(my_avl_tree,depth,is_right);
                }
                //printf("\n");
            }
        }
    }
    
}

void process_bst(char* file_name,char* string_array){
    FILE* file;
    char temp_store_array[1026];
    My_search_tree search_tree=NULL;
    int depth=0;
    int i=0;
    char is_right[30];
    clean_char_array(is_right);
    if (is_stdin==0) {
        //printf("here\n");
        if ((file=fopen(file_name,"r"))==NULL) {
            fprintf(stderr,"can't open this file\n");
            exit(1);
        }
        while (fgets(temp_store_array,1026,file)!=NULL) {
            i=i+1;
            clean_input(temp_store_array);
            //printf("here\n");
            search_tree=insert_binary_search_tree(search_tree,temp_store_array);
            //printf("here\n");
            if (should_displayall==1) {
                if (i!=1) {
                    printf("\n");
                }
                printf("Inserted \"%s\" (node %d):\n\n",temp_store_array,i);
                printf("%s\n",search_tree->key);
                print_bst_tree(search_tree,depth,is_right);
                //printf("\n");
            }
        }
        if (should_displayall==0) {
            printf("%s\n",search_tree->key);
            print_bst_tree(search_tree,depth,is_right);
        }
     }
     else if(is_stdin==1){                     //insert from stdin
           while ((fgets(temp_store_array, 1026,stdin))!=NULL) {
               if (strlen(temp_store_array)>=1000) {
                   fprintf(stderr,"the string is too long\n");
                   exit(1);
               }
                i=i+1;
                clean_input(temp_store_array);
                search_tree=insert_binary_search_tree(search_tree,temp_store_array);
                if (should_displayall==1) {
                    if (i!=1) {
                        printf("\n");
                    }
                    printf("Inserted \"%s\" (node %d):\n\n",temp_store_array,i);
                    printf("%s\n",search_tree->key);
                    if (search_tree==NULL) {
                        printf("(EMPTY)\n");
                    }
                    else
                        print_bst_tree(search_tree,depth,is_right);
                    //printf("\n");
                }
            }
            if (should_displayall==0) {
                printf("%s\n",search_tree->key);
                print_bst_tree(search_tree,depth,is_right);
            }
     }
     if (msg_type==2) {                  //delete all the elements from string_array, they are divided by  a space
        int where=0;        //indicate where we reach to in a char array
        int count=0;
        for (where=0;string_array[where]!='\0';) {
            char store_string[CHAR_LEN];
            int i=0;
            for (;string_array[where]!='\n'&&string_array[where]!='\0';where++,i++) {
                store_string[i]=string_array[where];
            }
            where++;
            store_string[i++]='\0';
            search_tree=delete_binary_search_tree(search_tree,store_string);
            count++;
            if (should_displayall==1) {
                printf("\n");
                printf("Deleted \"%s\":\n\n",store_string);
                if (search_tree==NULL) {
                    printf("(EMPTY)\n");
                    //printf("\n");
                }
                else{
                    printf("%s\n",search_tree->key);
                    print_bst_tree(search_tree,depth,is_right);
                }
                //printf("\n");
            }
        }
    }

}

void Usage(){
    fprintf(stderr,"  the right form is\n hw3 bst -displayall file\n hw3 bst_delete -displayall string1 string2 ... stringN file \n hw3 avl -displayall file\n hw3 avl_delete -displayall string1 string2 ... stringN file\n");
    exit(1);
}


int check_if_displayall(char* input){
    if (input[0]=='-') {
        if(strcmp(input,"-displayall")==0){
            should_displayall=1;
            return 1;
        }
        else{
            fprintf(stderr,"the format is wrong");
            Usage();
        }
    }
    return 0;
}

void process_option(int argc,char* argv[],char* string_array){
    if (argc==1) {
        fprintf(stderr,"lose a command\n");
        Usage();
    }
    
    argc--,argv++;
    
    if (strcmp(*argv,"bst")==0) {
        msg_type=1;
    }
    else if (strcmp(*argv,"bst_delete")==0) {
        msg_type=2;
    }
    else if (strcmp(*argv,"avl")==0) {
        msg_type=3;
    }
    else if (strcmp(*argv,"avl_delete")==0) {
        msg_type=4;
    }
    else{
        fprintf(stderr,"the format is wrong,lose arguments\n");
        Usage();
    }
    
    if (argc==1&&(msg_type==2||msg_type==4)) {
        fprintf(stderr,"too few arguments\n");
        Usage();
    }
    else if(argc==1&&(msg_type==1||msg_type==3)){
        return;
    }
    //the fisrt argument is done
    
    argc--,argv++;
    if (check_if_displayall(*argv)==1) {
        should_displayall=1;
        argc--,argv++;
    }
    if (argc<1) {
        return;
    }
    
    //printf("done  %d\n",argc);
    for (;argc>0&&(*argv)[0]!='-';argc--,argv++) {
        if ((argc==1)||((argc==2)&&(*(argv+1))[0]=='-')) {     //
            strcpy(file_name,*argv);
            is_stdin=0;
            //printf("get here\n");
            //return;
        }
        else{
            //printf("here1\n");
            //*string_array=(char*)malloc(20*sizeof(char));
            if (strlen(*argv)>=1000) {
                fprintf(stderr,"the string is too long");
                Usage();
            }
            strcat(string_array,*argv);
            strcat(string_array,"\n");
            //printf("end\n");
        }
    }
    //printf("done\n");
    if (argc>1) {
        fprintf(stderr,"too many arguments\n");
        Usage();
    }
    if (argc==1) {
        if (check_if_displayall(*argv)==1) {
        }
        else{
            fprintf(stderr,"too many arguments\n");
            Usage();
        }
    }
    return;
}

int main(int argc, char* argv[]){
    char* string_use=(char*)malloc(CHAR_LEN*CHAR_NUM*sizeof(char));
    file_name=(char*)malloc(256*sizeof(char));
    process_option(argc,argv,string_use);
    //printf("this is is_stdin:%d\nthis is should_display:%d\nthis is msg_type:%d\nthis is string_use:%s\nfile_name:%s
    //\n",is_stdin,should_displayall,msg_type,string_use,file_name);
    if ((msg_type==2||msg_type==4)&&strlen(string_use)<=1) {
        fprintf(stderr,"please enter some arguments for delete\n");
        Usage();
    }
    if (msg_type==1||msg_type==2) {
        process_bst(file_name,string_use);
    }
    else if(msg_type==3||msg_type==4){
        process_avl(file_name,string_use);
    }
    return 1;
}
