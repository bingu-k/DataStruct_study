#ifndef _BST_H_
# define _BST_H_

# include <stdio.h>
# include <stdlib.h>

typedef struct BSTNodeType
{
	int data;
	int visited;
	struct BSTNodeType* leftNode;
	struct BSTNodeType* rightNode;
} BSTNode;
typedef struct BSTType
{
	struct BSTNodeType* pRootNode;
} BST;

BST*        makeBST(BSTNode rootNode);
BSTNode*    makeBSTNode(BSTNode element);
BSTNode*    getRootNodeBST(BST* pBST);
int         insertChildNodeBST(BST* pBST, BSTNode element);
BSTNode*    searchParentNodeBST(BST* pBST, BSTNode element);
BSTNode*    searchkeyBST(BST* pBST, BSTNode element);
BSTNode*    searchCandidateNodeBST(BSTNode* pBSTNode);
void        deleteBST(BST** pBST);
void        deleteBSTNode(BST* pBST, BSTNode element);
void        Inorder(BSTNode* pBSTNode);
#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_
        
#define TRUE    1
#define FALSE   0
		
#endif