#ifndef _BIN_TREE_
#define _BIN_TREE_

#include <stdlib.h>
#include <stdio.h>

typedef struct BinTreeNodeType
{
  char  data;
  int   visited;
  
  struct  BinTreeNodeType* pLeftChild;
  struct  BinTreeNodeType* pRightChild;
} BinTreeNode;

typedef struct  BINTREEType
{
  struct BinTreeNodeType* pRootNode;  
} BinTree;

BinTree*        makeBinTree(BinTreeNode rootNode);
BinTreeNode*    getRootNodeBT(BinTree* pBinTree);
BinTreeNode*    insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element);
BinTreeNode*    insertRightChildNodeBT(BinTreeNode* pRarentNode, BinTreeNode element);
BinTreeNode*    getLeftChildNodeBT(BinTreeNode* pNode);
BinTreeNode*    getRightChildNodeBT(BinTreeNode* pNode);
void            deleteBinTree(BinTree* pBinTree);
void            deleteBinTreeNode(BinTreeNode* pNode);
void            Preorder(BinTreeNode *pBinTreeNode, int i);
void		    Inorder(BinTreeNode *pBinTreeNode, int i);
void		    Postorder(BinTreeNode *pBinTreeNode, int i);


#endif

#define TRUE    1
#define FALSE   0