#ifndef TRAVERSE_H
#define TRAVERSE_H

#include <stdlib.h>

#include "ch05_list.h"
#include "ch09_bitree.h"

int preorder(BiTreeNode* node, List* list);

int inorder(BiTreeNode* node, List* list);

int postorder(BiTreeNode* node, List* list);

#endif
