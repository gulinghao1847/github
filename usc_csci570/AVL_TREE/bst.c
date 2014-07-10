//
//  BST.c
//  570homework3
//
//  Created by linghao on 12-10-10.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"

void initial_node(My_tree_node* node){
    node->left_child=NULL;
    node->right_child=NULL;
    //node->parent=NULL;
}

My_tree_node* create_node(char* value){
    My_tree_node* new_node=(My_tree_node*)malloc(sizeof(My_tree_node));
    strcpy(new_node->key,value);
    initial_node(new_node);
    return new_node;
}

My_search_tree insert_binary_search_tree(My_search_tree my_tree,char* value){
    if (my_tree==NULL) {
        my_tree=create_node(value);
    }
    else if(strcmp(my_tree->key,value)>0){       //left child
        my_tree->left_child=insert_binary_search_tree(my_tree->left_child,value);
    }
    else if(strcmp(my_tree->key,value)<0){        //right child
        my_tree->right_child=insert_binary_search_tree(my_tree->right_child,value);
    }
    else if(strcmp(my_tree->key,value)==0){
        fprintf(stderr,"this node '%s' has already exists\n",value);
        exit(1);
    }
    return my_tree;
}

My_tree_node* find_in_order__bst_successor(My_search_tree my_tree){
    My_tree_node* right_node=my_tree->right_child;
    My_tree_node* result=right_node->left_child;
    My_tree_node* result_parent=right_node;
    while (result!=NULL) {
        result_parent=result;
        result=result->left_child;
    }
    return result_parent;
}


My_search_tree delete_binary_search_tree(My_search_tree my_tree,char* value){
    if (my_tree==NULL) {
        fprintf(stderr,"the value '%s' doesn't exists in this tree\n",value);
        exit(1);
    }
    else if (strcmp(my_tree->key,value)==0) {
        if (my_tree->left_child==NULL&&my_tree->right_child==NULL) {     //no child node
            free(my_tree);
             my_tree=NULL;
        }
        else if (my_tree->left_child==NULL) {                     //left_child is empty right_child is not empty
            My_search_tree return_tree=my_tree->right_child;
            free(my_tree);
            my_tree=return_tree;
        }
        else if(my_tree->right_child==NULL){                      //left_child is not empty
            My_search_tree return_tree=my_tree->left_child;
            free(my_tree);
            my_tree=return_tree;
        }
        else{                                                    //both are not empty
            My_tree_node* in_order_successor;
            char temp_char[1000];
            in_order_successor=find_in_order__bst_successor(my_tree);
            strcpy(temp_char,in_order_successor->key);
            delete_binary_search_tree(my_tree,in_order_successor->key);
            strcpy(my_tree->key,in_order_successor->key);
        }
    }
    else if(strcmp(my_tree->key,value)>0){                     //left child
        my_tree->left_child=delete_binary_search_tree(my_tree->left_child,value);
    }
    else if(strcmp(my_tree->key,value)<0){                     //right child
        my_tree->right_child=delete_binary_search_tree(my_tree->right_child,value);
    }
    return my_tree;
}




























