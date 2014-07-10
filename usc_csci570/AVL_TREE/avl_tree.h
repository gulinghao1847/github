//
//  avl_tree.h
//  570homework3
//
//  Created by linghao on 12-10-14.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _70homework3_avl_tree_h
#define _70homework3_avl_tree_h
typedef struct tag_avl_tree_node avl_tree_node;
typedef struct tag_avl_tree_node* avl_tree;
struct tag_avl_tree_node{
    int balance;//={left_higher,equal,right_higher};
    char key[200];
    avl_tree_node* left_child;
    avl_tree_node* right_child;
    avl_tree_node* parent;
    int height;
};

avl_tree insert_avl_tree(avl_tree my_tree,char* value,int* is_taller);
avl_tree delete_avl_tree(avl_tree my_tree, char* value, int* is_shorter);
avl_tree find_avl_node(avl_tree my_tree,char* value);
avl_tree find_in_order_successor(avl_tree my_tree);
avl_tree delete_option(avl_tree my_avl_tree,char* store_string,int is_shorter);
#endif
