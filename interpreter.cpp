#include "interpreter.h"

using std::cout;

/*Virtual memory functions*/

int Memory::readVal(int steps){
	//default steps is 0, can be used to read offset from cur index
	return tape[index+steps];
}
void Memory::writeVal(int data){
	tape[index] = data;
}
void Memory::movePointer(int steps){
	index += steps;
	index %= TAPE_SIZE;
}
inline int Memory::currentIndex(){
	return index;
}
inline void Memory::writeAtLocation(int idx, int data){
	tape[idx] = data;
}

int Memory::tape[TAPE_SIZE] = {0};
Memory memory;	

/*Solving parse tree*/

extern Token tokNull;
extern Token tokErr;

/*Assume parse tree is syntactically sound*/
//make a syntax analyser!

Token solve(treeNode *leaf){
	if (leaf == NULL)
		return tokNull;

	switch (leaf->token.name) {
	
	case tn_print:
		return funcPrint(leaf);
	case tn_assign:
		return funcAssign(leaf);
	case tn_minus:
		return funcSub(leaf);
	case tn_plus:
		return funcAdd(leaf);
	case tn_mult:
		return funcMult(leaf);
	case tn_div:
		return funcDiv(leaf);

	case tn_lpoint:
		return funcPoint(leaf, left);
	case tn_rpoint:
		return funcPoint(leaf, right);
	case tn_lshift:
		return funcShift(leaf, left);
	case tn_rshift:
		return funcShift(leaf, right);
	case tn_lvalue:
		return funcThis();
	case tn_rvalue:
		return leaf->token;

	case tn_error:
		return tokErr;

	}
}
/* Input output*/
Token funcPrint(treeNode *leaf){
	Token trhs = solve(leaf->right);
	cout<<(char)trhs.val;
	return tokNull;		//hmmmmm
}

/*Operators related to this (pointer)*/
Token funcAssign(treeNode *leaf){
	Token tlhs = solve(leaf->left);
	int tempIndex = memory.currentIndex();
	Token trhs = solve(leaf->right);

	memory.writeAtLocation(tempIndex, trhs.val);

	Token result;
	result.setConstVal(trhs.val);
	return result;	//HAS to return const value
}	

Token funcThis(){
	Token result;
	result.setThisVal(memory.readVal());
	return result;
}

Token funcShift(treeNode *leaf, Side side){
	Token tlhs = solve(leaf->left);
	Token trhs = solve(leaf->right);

	if (side == right)
		memory.movePointer(trhs.val);
	else if (side == left)
		memory.movePointer(-tlhs.val);

	Token result;
	result.setThisVal(memory.readVal());
	return result;
}

Token funcPoint(treeNode *leaf, Side side){
	Token tlhs = solve(leaf->left);
	Token trhs = solve(leaf->right);

	if (side == left)
		trhs.val *= -1;	//okay to modify?

	Token result;
	result.setConstVal(memory.readVal(trhs.val));
	return result;
}

/*Arithmetic operations*/	

Token funcDiv(treeNode *leaf){
	Token tlhs = solve(leaf->left);
	Token trhs = solve(leaf->right);

	if (trhs.val == 0){
		execError("Division by zero");
		return tokErr;
	}

	Token result;
	result.setConstVal(tlhs.val / trhs.val);
	return result;
}

Token funcMult(treeNode *leaf){
	Token tlhs = solve(leaf->left);
	Token trhs = solve(leaf->right);

	Token result;
	result.setConstVal(tlhs.val * trhs.val);
	return result;
}

Token funcAdd(treeNode *leaf){
	Token tlhs = solve(leaf->left);
	Token trhs = solve(leaf->right);

	Token result;
	result.setConstVal(tlhs.val + trhs.val);
	return result;
}

Token funcSub(treeNode *leaf){
	Token tlhs = solve(leaf->left);
	Token trhs = solve(leaf->right);

	Token result;
	result.setConstVal(tlhs.val - trhs.val);
	return result;
}
