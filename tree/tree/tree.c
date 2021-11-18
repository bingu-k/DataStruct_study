#include "tree.h"

BinTree*        makeBinTree(BinTreeNode rootNode)
{
    BinTree *res;
	BinTreeNode *node;

    if (!(res = malloc(sizeof(BinTree))))
        return (NULL);
	if (!(node = malloc(sizeof(BinTreeNode))))
    {
        free(res);
		return (NULL);
    }
    node->data = rootNode.data;
	node->visited = rootNode.visited;
	node->pLeftChild = NULL;
    node->pRightChild = NULL;
    res->pRootNode = node;
    return (res);
}

BinTreeNode*    getRootNodeBT(BinTree* pBinTree)
{
    if (!pBinTree)
        return (NULL);
	return(pBinTree->pRootNode);
}

BinTreeNode*    insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *node;

    if (!pParentNode)
        return (NULL);
    else if (pParentNode->pLeftChild) // 이미 존재한다면 부모노드 반환
        return (pParentNode);
    if (!(node = malloc(sizeof(BinTreeNode))))
        return (NULL);
    node->data = element.data;
    node->visited = element.visited;
	node->pLeftChild = NULL;
    node->pRightChild = NULL;
    pParentNode->pLeftChild = node;
	return (pParentNode);
}

BinTreeNode*    insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *node;

    if (!pParentNode)
        return (NULL);
	else if (pParentNode->pRightChild) // 이미 존재한다면 부모노드 반환
        return (pParentNode);
    if (!(node = malloc(sizeof(BinTreeNode))))
        return (NULL);
    node->data = element.data;
    node->visited = element.visited;
	node->pLeftChild = NULL;
    node->pRightChild = NULL;
    pParentNode->pRightChild = node;
	return (pParentNode);
}

BinTreeNode*    getLeftChildNodeBT(BinTreeNode* pNode)
{
    if (!pNode)
        return (NULL);
    return (pNode->pLeftChild);
}

BinTreeNode*    getRightChildNodeBT(BinTreeNode* pNode)
{
	if (!pNode)
        return (NULL);
    return (pNode->pRightChild);
}

void            deleteBinTreeNode(BinTreeNode* pNode)
{
	if (!pNode)
		return ;
	deleteBinTreeNode(pNode->pLeftChild);
    deleteBinTreeNode(pNode->pRightChild);
    free(pNode);
}

void            deleteBinTree(BinTree* pBinTree)
{
    if (!pBinTree)
        return ;
    deleteBinTreeNode(pBinTree->pRootNode);
	free(pBinTree);
}

void		Preorder(BinTreeNode *pBinTreeNode, int i)
{
	if (!pBinTreeNode)
		return ;
	printf("Preorder height : %d | %c\n", i, pBinTreeNode->data);
	Preorder(pBinTreeNode->pLeftChild, i + 1);
	Preorder(pBinTreeNode->pRightChild, i + 1);
}

void		Inorder(BinTreeNode *pBinTreeNode, int i)
{
	if (!pBinTreeNode)
		return ;
	Inorder(pBinTreeNode->pLeftChild, i + 1);
	printf("Inorder height : %d | %c\n", i, pBinTreeNode->data);
	Inorder(pBinTreeNode->pRightChild, i + 1);
}

void		Postorder(BinTreeNode *pBinTreeNode, int i)
{
	if (!pBinTreeNode)
		return ;
	Postorder(pBinTreeNode->pLeftChild, i + 1);
	Postorder(pBinTreeNode->pRightChild, i + 1);
	printf("Postorder height : %d | %c\n", i, pBinTreeNode->data);
}

BinTreeNode *save_tree(BinTreeNode *node, int data, int max)
{
    BinTreeNode *Lnode;
    BinTreeNode *Rnode;
    BinTreeNode element;

    if (max <= data)
        return (NULL);
    element.data = node->data + data;
    element.visited = 0;
    Lnode = insertLeftChildNodeBT(node, element)->pLeftChild;
    element.data = node->data + data + 1;
    element.visited = 0;
    Rnode = insertRightChildNodeBT(node, element)->pRightChild;
    save_tree(Lnode, data * 2, max);
    save_tree(Rnode, data * 2 + 1, max);
    return (node);
}

int main(void)
{
    BinTree     *pBinTree;
    BinTreeNode rootNode;

	rootNode.data = 'a';
	rootNode.visited = 0;
	rootNode.pLeftChild = NULL;
	rootNode.pRightChild = NULL;
	pBinTree = makeBinTree(rootNode);
	save_tree(pBinTree->pRootNode, 1, 8);
    /*
            a
        b  	    c
      d   e    f   g
     h i j k  l m n o
    */
    printf("\nPreorder\n");
	Preorder(pBinTree->pRootNode, 0);
    printf("\nInorder\n");
	Inorder(pBinTree->pRootNode, 0);
    printf("\nPostorder\n");
	Postorder(pBinTree->pRootNode, 0);
    printf("\n");
	deleteBinTree(pBinTree);
    return(0);
}

/*

int main()
{
	makeBinTree
}
void	makeTree(BinTreeNode *node)
{
	if (node->data - 'a' > 4)
		return ;
	BinTreeNode element;
	
	element.data = 2 * node->data;
	element.visited = 0;
	element.pLeftChild = 0;
	element.pRightChild = 0;
	insertLeftChildNodeBT(node, element);
	element.data = 2 * node->data + 1;
	insertRightChildNodeBT(node, element);
	makeTree(node->pLeftChild);
	makeTree(node->pRightChild);
}

*/