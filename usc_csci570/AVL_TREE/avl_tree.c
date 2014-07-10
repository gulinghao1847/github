//
//  avl_tree.c
//  570homework3
//
//  Created by linghao on 12-10-14.
//  Copyright (c) 2012年 linghao. All rights reserved.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl_tree.h"
//#include "binary_search_tree.h"

int get_max_height(avl_tree my_tree){
    int height;
    int height_left;
    int height_right;
    height_left=(my_tree->left_child==NULL?-1:my_tree->left_child->height);
    height_right=(my_tree->right_child==NULL?-1:my_tree->right_child->height);
    height=(height_left>height_right?height_left+1:height_right+1);
    return height;
}

int get_height(avl_tree my_tree){
    return my_tree==NULL?-1:my_tree->height;
}

void initial_avl_node(avl_tree_node* node){
    node->left_child=NULL;
    node->right_child=NULL;
    node->balance=0;
    node->height=0;
    //node->parent=NULL;
}

avl_tree_node* create_avl_node(char* value){
    avl_tree_node* new_node=(avl_tree_node*)malloc(sizeof(avl_tree_node));
    strcpy(new_node->key,value);
    initial_avl_node(new_node);
    return new_node;
}

avl_tree right_rotation(avl_tree my_tree){
    avl_tree_node* right_node=my_tree->right_child;
    my_tree->right_child=right_node->left_child;
    right_node->left_child=my_tree;
    return right_node;
}

avl_tree left_rotation(avl_tree my_tree){
    avl_tree_node* left_node=my_tree->left_child;
    my_tree->left_child=left_node->right_child;
    left_node->right_child=my_tree;
    return left_node;
}

avl_tree right_balance(avl_tree my_tree){
    //avl_tree_node* left_node=my_tree->left_child;
    avl_tree_node* right_node=my_tree->right_child;
    //my_tree->right_child
    if (right_node->balance==1) {
        switch (right_node->left_child->balance) {
            case -1:
                my_tree->balance=1;
                right_node->balance=0;
                break;
            case 1:
                my_tree->balance=0;
                right_node->balance=-1;
                break;
            case 0:
                my_tree->balance=0;
                right_node->balance=0;
                break;
            default:
                break;
        }
        right_node->left_child->balance=0;
        my_tree->right_child=left_rotation(my_tree->right_child);
        my_tree=right_rotation(my_tree);
    }else if(right_node->balance==-1){
        my_tree->balance=0;
        right_node->balance=0;
        my_tree=right_rotation(my_tree);
    }
    return my_tree;
}

avl_tree left_balance(avl_tree my_tree){
    avl_tree_node* left_node=my_tree->left_child;
    if (left_node->balance==1) {
        left_node->balance=0;
        my_tree->balance=0;
        my_tree=left_rotation(my_tree);
    }
    else if (left_node->balance==-1){
        switch (left_node->right_child->balance) {
            case 0:
                my_tree->balance=0;
                left_node->balance=0;
                break;
            case 1:
                //printf("get here %s\n",my_tree->key);
                my_tree->balance=-1;   //59 right
                left_node->balance=0;  //1a    right
                break;
            case -1:
                left_node->balance=1;
                my_tree->balance=0;
                break;
            default:
                break;
        }
        left_node->right_child->balance=0;
        my_tree->left_child=right_rotation(my_tree->left_child);
        my_tree=left_rotation(my_tree);
    }
    return my_tree;
}

avl_tree insert_avl_tree(avl_tree my_tree,char* value,int* is_taller){
    if (my_tree==NULL) {
        my_tree=create_avl_node(value);
        *is_taller=1;
    }
    else if(strcmp(value, my_tree->key)==0){
        fprintf(stderr,"this node '%s' has already exists\n",value);
        exit(1);
    }
    else if(strcmp(value,my_tree->key)>0){
        my_tree->right_child=insert_avl_tree(my_tree->right_child,value,is_taller);
        if (*is_taller==1) {
            if (my_tree->balance==1) {
                my_tree->balance=my_tree->balance-1;
                *is_taller=0;
            }
            else if(my_tree->balance==0){
                my_tree->balance=my_tree->balance-1;
            }
            else if(my_tree->balance==-1){
                //my_tree->balance=my_tree->balance-1;
                my_tree=right_balance(my_tree);
                *is_taller=0;
            }
            else
                fprintf(stderr,"impossible 4,check your code\n");
        }
    }
    else if(strcmp(value,my_tree->key)<0){
        my_tree->left_child=insert_avl_tree(my_tree->left_child,value,is_taller);
        if (*is_taller==1) {
            if (my_tree->balance==-1) {
                my_tree->balance=my_tree->balance+1;
                *is_taller=0;
            }
            else if(my_tree->balance==0){
                my_tree->balance=my_tree->balance+1;
            }
            else if(my_tree->balance==1){
                //my_tree->balance=my_tree->balance+1;
                //printf("%s  (%d)",my_tree->key,my_tree->balance);
                my_tree=left_balance(my_tree);
                *is_taller=0;
            }
            else
                fprintf(stderr,"impossible 3,check your code\n");
        }
    }
    return my_tree;
}


avl_tree find_in_order_successor(avl_tree my_tree){
    avl_tree_node* right_node=my_tree->right_child;
    avl_tree_node* result=right_node->left_child;
    avl_tree_node* result_parent=right_node;
    while (result!=NULL) {
        result_parent=result;
        result=result->left_child;
    }
    return result_parent;
}

avl_tree delete_right_balance(avl_tree my_tree,int* is_shorter){
    avl_tree_node* left_node=my_tree->left_child;
    if (left_node->balance==0) {
        my_tree->balance=1;
        left_node->balance=-1;
        my_tree=left_rotation(my_tree);
        *is_shorter=0;
    }
    else if(left_node->balance==1){
        my_tree->balance=0;
        left_node->balance=0;
        my_tree=left_rotation(my_tree);
        *is_shorter=1;
    }
    else if(left_node->balance==-1){
        switch (left_node->right_child->balance) {
            case 0:
                left_node->balance=0;
                my_tree->balance=0;
                break;
            case 1:
                left_node->balance=0;
                my_tree->balance=-1;
                break;
            case -1:
                my_tree->balance=0;
                left_node->balance=1;
                break;
            default:
                break;
        }
        left_node->right_child->balance=0;
        my_tree->left_child=right_rotation(left_node);
        my_tree=left_rotation(my_tree);
        *is_shorter=1;
    }
    return my_tree;
}

avl_tree delete_left_balance(avl_tree my_tree,int* is_shorter){    //called by reducing left_child
    avl_tree_node* right_node=my_tree->right_child;
    if (right_node->balance==0) {
        my_tree->balance=-1;
        right_node->balance=1;
        my_tree=right_rotation(my_tree);
        *is_shorter=0;
    }
    else if(right_node->balance==-1){
        my_tree->balance=0;
        right_node->balance=0;
        my_tree=right_rotation(my_tree);
        *is_shorter=1;
    }
    else if(right_node->balance==1){
        switch (right_node->left_child->balance) {
            case 0:
                right_node->balance=0;
                my_tree->balance=0;
                break;
            case 1:
                right_node->balance=-1;
                my_tree->balance=0;
                break;
            case -1:
                my_tree->balance=1;
                right_node->balance=0;
                break;
            default:
                break;
        }
        right_node->left_child->balance=0;
        my_tree->right_child=left_rotation(right_node);
        my_tree=right_rotation(my_tree);
        *is_shorter=1;
    }
    return my_tree;
}

avl_tree delete_avl_node(avl_tree my_tree,int *is_shorter){
    //int is_shorter=0;
    //*is_shorter=0;
    avl_tree_node* in_order_successor_node;
    //char temp_char[20];
    avl_tree_node* temp_change_node=(avl_tree_node*)malloc(sizeof(avl_tree_node));
    if (my_tree->left_child==NULL&&my_tree->right_child==NULL) {
        *is_shorter=1;
        my_tree=NULL;
    }
    else if(my_tree->left_child!=NULL&&my_tree->right_child==NULL){
        *is_shorter=1;
        my_tree=my_tree->left_child;
    }
    else if(my_tree->right_child!=NULL&&my_tree->left_child==NULL){
        *is_shorter=1;
        my_tree=my_tree->right_child;
    }
    else{
        in_order_successor_node=find_in_order_successor(my_tree);
        //printf("in_order:%s\n",in_order_successor_node->key);
        avl_tree_node* new_node=(avl_tree_node*)malloc(sizeof(avl_tree_node));
        strcpy(new_node->key,in_order_successor_node->key);
        avl_tree temp_tree=my_tree;
        my_tree=delete_avl_tree(my_tree,in_order_successor_node->key,is_shorter);
        //问题在于如何找到这个东西
        if (strcmp(my_tree->key,temp_tree->key)!=0) {    //判断这个子树是否变得更短, 如果根节点不换, 就绝对不会短
            *is_shorter=0;
        }
        else
            *is_shorter=1;
        strcpy(temp_tree->key,new_node->key);
    }
    //free(is_shorter);
    free(temp_change_node);
    return my_tree;
}


avl_tree delete_avl_tree(avl_tree my_tree, char* value, int* is_shorter){
    if (my_tree==NULL) {
        fprintf(stderr,"this node '%s' doesn't exist\n",value);
        exit(1);
    }
    else if(strcmp(my_tree->key,value)==0){
        my_tree=delete_avl_node(my_tree,is_shorter);
        return my_tree;
    }
    else if(strcmp(my_tree->key,value)>0){              // value<key   left side
        my_tree->left_child=delete_avl_tree(my_tree->left_child,value,is_shorter);
        if (*is_shorter==1) {
            if (my_tree->balance==1) {           //balanced factor need to be reduced by 1, since the left side has lose a node
                my_tree->balance=my_tree->balance-1;
            }
            else if(my_tree->balance==0){        //balanced factor need to be reduced by 1, since the left side has lose a node
                my_tree->balance=my_tree->balance-1;
                //printf("here\n");
                *is_shorter=0;
            }
            else if(my_tree->balance==-1){       //balanced factor need to be reduced by 1, since the left side has lose a node
                //my_tree->balance=my_tree->balance-1;
                my_tree=delete_left_balance(my_tree,is_shorter); //the balacne will be 2, so we need to call balance function
                //*is_shorter=0;
            }
            else
                fprintf(stderr,"impossible  2, check your code\n");
        }
    }
    else if(strcmp(my_tree->key, value)<0){
        my_tree->right_child=delete_avl_tree(my_tree->right_child,value,is_shorter);
        if (*is_shorter==1) {
            if (my_tree->balance==-1) {
                my_tree->balance=my_tree->balance+1;
            }
            else if(my_tree->balance==0){
                my_tree->balance=my_tree->balance+1;
                *is_shorter=0;
            }
            else if(my_tree->balance==1){          //the balacne will be 2, so we need to call balance function.
                //my_tree->balance=my_tree->balance+1;
                my_tree=delete_right_balance(my_tree,is_shorter);
            }
            else
                fprintf(stderr,"impossible  1, check your code\n");
        }
    }
    return my_tree;
}


avl_tree delete_option(avl_tree my_avl_tree,char* store_string,int is_shorter){
    avl_tree_node* temp_node=find_avl_node(my_avl_tree,store_string);
    if (temp_node->left_child!=NULL&&temp_node->right_child!=NULL) {
        avl_tree_node* in_order_successor=find_in_order_successor(temp_node);
        char temp_char[1000];
        strcpy(temp_char,in_order_successor->key);
        my_avl_tree=delete_avl_tree(my_avl_tree,in_order_successor->key,&is_shorter);
        strcpy(temp_node->key,temp_char);
    }
    else
        my_avl_tree=delete_avl_tree(my_avl_tree,store_string,&is_shorter);
    return my_avl_tree;
}

avl_tree find_avl_node(avl_tree my_tree,char* value){
    if (my_tree==NULL) {
        fprintf(stderr,"this node '%s'doesn't exist\n",value);
        exit(1);
    }
    else if(strcmp(my_tree->key,value)==0){
        return my_tree;
    }
    else if(strcmp(my_tree->key,value)>0){
        return find_avl_node(my_tree->left_child,value);
    }
    else if(strcmp(my_tree->key,value)<0){
        return find_avl_node(my_tree->right_child,value);
    }
    return NULL;//impossible
}





