#include "parser.h"

/*Normal binary parser*/

treeNode *newTreeNode(Token newtok){
	treeNode *newnode = new treeNode;
	newnode->token = newtok;
	newnode->left = newnode->right = NULL;

	return newnode;
}

treeNode *insertToken(treeNode *leaf, Token newtok){
	if (leaf == NULL)
		return newTreeNode(newtok);

	if (newtok.priority > leaf->token.priority)
		leaf->right = insertToken(leaf->right, newtok);
	else {
		treeNode *newnode = new treeNode;
		*newnode = *leaf;

		leaf->token = newtok;
		leaf->left = newnode;
		leaf->right = NULL;
	}

	return leaf;
}

void postOrder(treeNode *leaf){
	if (leaf != NULL){
		postOrder(leaf->left);
		postOrder(leaf->right);
		leaf->token.print();
	}
}

void deleteTree(treeNode *leaf){
	if (leaf != NULL){
		deleteTree(leaf->left);
		deleteTree(leaf->right);
		delete leaf;
	}
}
