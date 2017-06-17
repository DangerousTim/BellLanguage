#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include "token.h"

/*Normal binary parser*/

struct treeNode {
	Token token;

	treeNode *left;
	treeNode *right;
};

treeNode *newTreeNode(Token);
treeNode *insertToken(treeNode*, Token);

void deleteTree(treeNode*);

#endif

