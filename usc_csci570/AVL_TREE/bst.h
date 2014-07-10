//
//  binary search tree.h
//  570homework3
//
//  Created by linghao on 12-10-10.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _70homework3_binary_search_tree_h
#define _70homework3_binary_search_tree_h
typedef struct tree_node{
    char key[200];
    struct tree_node* left_child;
    struct tree_node* right_child;
    struct tree_node* parent;
}My_tree_node;
typedef struct tree_node* My_search_tree;

/*
 typedef struct binary_search_tree{
    My_tree_node* root_node;
}My_tree;
*/

My_search_tree delete_binary_search_tree(My_search_tree my_tree,char* value);
My_search_tree insert_binary_search_tree(My_search_tree my_tree,char* value);
My_tree_node* create_node(char* value);
#endif
