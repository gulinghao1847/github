//
//  print_tree.c
//  570homework3
//
//  Created by linghao on 12-10-11.
//  Copyright (c) 2012年 linghao. All rights reserved.
//
//#include "print_tree.h"
//#include "BST.h"
#include <string.h>
#include "print_tree.h"
#include <stdio.h>
#include <stdlib.h>
void clean_char_array(char* array){
    int j=0;
    for (j=(int)strlen(array);j>=0;j--) {
        array[j]='\0';
    }
}


// the code below is copied from my 570_homework_2
void clean_input(char* input){          //remove all leading and trailing <space> <CR> <TAB>
    char* use_ptr;
    char* head_ptr;
    char* tail_ptr;
    if (input==NULL) {
        return;
    }
    use_ptr=head_ptr=tail_ptr=input;
    for (;*use_ptr=='\t'||*use_ptr==' '||*use_ptr=='\n';use_ptr++) {
        head_ptr=use_ptr;
    }
    for (;*use_ptr!='\0';use_ptr++) {
        if (*use_ptr!='\t'&&*use_ptr!=' '&&*use_ptr!='\n') {
            tail_ptr=use_ptr;
        }
    }
    *(++tail_ptr)='\0';
    memmove(input,head_ptr,tail_ptr-head_ptr+1);
}
// the code above is copied from my 570_homework_2


char* get_balance(avl_tree node){
    if (node->balance==1) {
        return "L";
    }
    else if (node->balance==0) {
        return "E";
    }
    else if (node->balance==-1) {
        return "R";
    }
    else
        fprintf(stderr,"impossible check your code\n");
    return NULL;//impossible
}



void print_a_bst_line(My_tree_node* print_node, int depth, char* old_is_right,int is_right){
    int i=0;
    //char balance[3];//=get_balance(print_node);
    for (i=0;i<depth;i++) {
        if (old_is_right[i]=='0') {
            printf(" |   ");
        }
        else
            printf("     ");
    }
    if (is_right==0) {
        if (print_node==NULL) {
            printf(" +-- NULL\n");
        }
        else
            printf(" +-- %s\n",print_node->key);
    }
    else if(is_right==1){
        if (print_node==NULL) {
            printf(" \\-- NULL\n");
        }
        else
            printf(" \\-- %s\n",print_node->key);
    }
}

void print_bst_tree(My_search_tree my_tree, int depth, char* old_is_right){
    //int temp_depth=depth+1;
    //char is_right_array[100];
    int is_right;
    is_right=0;
    //temp_tree->root_node=my_tree->root_node->left_child;
    print_a_bst_line(my_tree->left_child,depth,old_is_right,is_right);
    if (my_tree->left_child!=NULL) {
        int temp_depth=depth+1;
        char is_right_array[100];
        strcpy(is_right_array,old_is_right);
        strcat(is_right_array,"0");
        //strcpy(is_right_array,old_is_right);
        //printf("%s\n",is_right_array);
        print_bst_tree(my_tree->left_child,temp_depth,is_right_array);
    }
    is_right=1;
    print_a_bst_line(my_tree->right_child,depth,old_is_right,is_right);
    if (my_tree->right_child!=NULL) {
        int temp_depth=depth+1;
        char is_right_array[100];
        strcpy(is_right_array,old_is_right);
        strcat(is_right_array,"1");
        //printf("%s\n",is_right_array);
        print_bst_tree(my_tree->right_child,temp_depth,is_right_array);
    }
}

void print_a_avl_line(avl_tree print_node, int depth, char* old_is_right,int is_right){
    int i=0;
    char balance[3];//=get_balance(print_node);
    if (print_node!=NULL)
        strcpy(balance, get_balance(print_node));
    for (i=0;i<depth;i++) {
        if (old_is_right[i]=='0') {
            printf(" |   ");
        }
        else
            printf("     ");
    }
    if (is_right==0) {
        if (print_node==NULL) {
            printf(" +-- NULL\n");
        }
        else
            printf(" +-- %s (%s)\n",print_node->key,balance);
    }
    else if(is_right==1){
        if (print_node==NULL) {
            printf(" \\-- NULL\n");
        }
        else
            printf(" \\-- %s (%s)\n",print_node->key,balance);
    }
}

void print_avl_tree(avl_tree my_tree, int depth, char* old_is_right){
    //int temp_depth=depth+1;
    //char is_right_array[100];
    int is_right;
    //strcpy(is_right_array,old_is_right);
    is_right=0;
    print_a_avl_line(my_tree->left_child,depth,old_is_right,is_right);
    if (my_tree->left_child!=NULL) {
        int temp_depth=depth+1;
        char is_right_array[100];
        strcpy(is_right_array,old_is_right);
        strcat(is_right_array,"0");
        //strcpy(is_right_array,old_is_right);
        //printf("%s\n",is_right_array);
        print_avl_tree(my_tree->left_child,temp_depth,is_right_array);
    }
    is_right=1;
    print_a_avl_line(my_tree->right_child,depth,old_is_right,is_right);
    if (my_tree->right_child!=NULL) {
        int temp_depth=depth+1;
        char is_right_array[100];
        strcpy(is_right_array,old_is_right);
        strcat(is_right_array,"1");
        //printf("%s\n",is_right_array);
        print_avl_tree(my_tree->right_child,temp_depth,is_right_array);
    }
}





