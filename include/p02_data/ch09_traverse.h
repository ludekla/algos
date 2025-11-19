#ifndef TRAVERSE_H
#define TRAVERSE_H

#include <stdlib.h>

#include "ch05_list.h"
#include "ch09_bitree.h"

int preorder(TreeNode* node, List* list);

int inorder(TreeNode* node, List* list);

int postorder(TreeNode* node, List* list);

#endif
