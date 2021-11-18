#include "bst.h"
#include <unistd.h>

BST*        makeBST(BSTNode rootNode)
{
    BST         *pBST;
    BSTNode*    currNode;

    if (!(pBST = malloc(sizeof(BST))))
        return (NULL);
    if (!(pBST->pRootNode = malloc(sizeof(BSTNode))))
    {
        free(pBST);
        return (NULL);
    }
    if (!(currNode = makeBSTNode(rootNode)))
    {
        free(pBST);
        free(pBST->pRootNode);
        return (NULL);
    }
    pBST->pRootNode->visited = -1;
    pBST->pRootNode->leftNode = currNode;
    pBST->pRootNode->rightNode = NULL;
    return (pBST);
}

BSTNode*    makeBSTNode(BSTNode element)
{
    BSTNode*    res;
    res = malloc(sizeof(BSTNode));
    if (!res)
        return (NULL);
    res->data = element.data;
    res->visited = 0;
    res->leftNode = NULL;
    res->rightNode = NULL;
    return (res);
}

BSTNode*    getRootNodeBST(BST* pBST)
{
    if (!pBST)
        return (NULL);
    return (pBST->pRootNode->leftNode);
}

BSTNode*    searchParentNodeBST(BST* pBST, BSTNode element)
{
    BSTNode *parentNode;
    BSTNode *currNode;

    currNode = pBST->pRootNode->leftNode;
    parentNode = pBST->pRootNode;
    while (currNode)
    {
        if (currNode->data == element.data)
            break ;
        parentNode = currNode;
        if (currNode->data > element.data)
            currNode = parentNode->leftNode;
        else if (currNode->data < element.data)
            currNode = parentNode->rightNode;
    }
    return (parentNode);
}

int    insertChildNodeBST(BST* pBST, BSTNode element)
{
    BSTNode *parentNode;
    BSTNode *newNode;

    if (!pBST)
        return (FALSE);
    if (searchkeyBST(pBST, element))
        return (FALSE);
    parentNode = searchParentNodeBST(pBST, element);
    if (!(newNode = makeBSTNode(element)))
        return (FALSE);
    if (parentNode->visited == -1)
    {
        parentNode->leftNode = newNode;
        parentNode->rightNode = NULL;
    }
    else if (parentNode->data > element.data)
        parentNode->leftNode = newNode;
    else
        parentNode->rightNode = newNode;
    return (TRUE);
}

BSTNode*    searchkeyBST(BST* pBST, BSTNode element)
{
    BSTNode *currNode;

    if (!pBST)
        return (NULL);
    currNode = pBST->pRootNode->leftNode;
    while (currNode)
    {
        if (currNode->data > element.data)
            currNode = currNode->leftNode;
        else if (currNode->data < element.data)
            currNode = currNode->rightNode;
        else
            return (currNode);
    }
    return (NULL);
}

BSTNode*    searchCandidateNodeBST(BSTNode* pBSTNode)
{
    BSTNode*    left_canNode;
    BSTNode*    right_canNode;

    if (pBSTNode->leftNode)
    {
        left_canNode = pBSTNode->leftNode;
        while (left_canNode->rightNode)
            left_canNode = left_canNode->rightNode;
        return (left_canNode);
    }
    else if (pBSTNode->rightNode)
    {
        right_canNode = pBSTNode->rightNode;
        while (right_canNode->leftNode)
            right_canNode = right_canNode->leftNode;
        return (right_canNode);
    }
    else
        return (pBSTNode);
}
int			isChildLeft(BSTNode *parentNode, BSTNode *childNode)
{
	if (parentNode->leftNode == childNode)
		return (1);
	else 
		return (0);
}
void           deleteBSTNode(BST *pBST, BSTNode element)
{
    BSTNode*	delNode;
    BSTNode*	del_parentNode;
    BSTNode*	canNode;
    BSTNode*	can_parentNode;
    BSTNode*	newNode;


	if (!pBST)
		return ;
	if (!(delNode = searchkeyBST(pBST, element)))
		return ;
	del_parentNode = searchParentNodeBST(pBST, element);
	if (isChildLeft(del_parentNode, delNode))
	{
		if (!delNode->leftNode && !delNode->rightNode)
		{
			del_parentNode->leftNode = NULL;
			free(delNode);
			return ;
		}
		canNode = searchCandidateNodeBST(delNode);
		if (delNode->leftNode == canNode)
		{
			del_parentNode->leftNode = canNode;
			canNode->rightNode = delNode->rightNode;
			free(delNode);
			return ;
		}
		can_parentNode = searchParentNodeBST(pBST, *canNode);
		if (delNode->leftNode)
		{
			can_parentNode->rightNode = canNode->leftNode;
			del_parentNode->leftNode = canNode;
		}
		else
		{
			can_parentNode->leftNode = canNode->leftNode;
			del_parentNode->leftNode = canNode;
		}
		canNode->leftNode = delNode->leftNode;
		canNode->rightNode = delNode->rightNode;
		free(delNode);
	}
	else if (!isChildLeft(del_parentNode, delNode))
	{
		if (!delNode->leftNode && !delNode->rightNode)
		{
			del_parentNode->rightNode = NULL;
			free(delNode);
			return ;
		}
		canNode = searchCandidateNodeBST(delNode);
		if (delNode->rightNode == canNode)
		{
			del_parentNode->rightNode = canNode;
			canNode->leftNode = delNode->leftNode;
			free(delNode);
			return ;
		}
        can_parentNode = searchParentNodeBST(pBST, *canNode);
		if (delNode->leftNode)
		{
            can_parentNode->leftNode = canNode->rightNode;
			del_parentNode->rightNode = canNode;
		}
		else
		{
			can_parentNode->leftNode = canNode->rightNode;
			del_parentNode->leftNode = canNode;
		}
        canNode->leftNode = delNode->leftNode;
		canNode->rightNode = delNode->rightNode;
		free(delNode);
	}
	return ;
}

void        clearBST(BST* pBST, BSTNode* pBSTNode)
{
    if (!pBSTNode)
        return ;
    clearBST(pBST, pBSTNode->leftNode);
    clearBST(pBST, pBSTNode->rightNode);
    deleteBSTNode(pBST, *pBSTNode);
}

void        deleteBST(BST** pBST)
{
    if (!(*pBST))
        return ;
    clearBST((*pBST), (*pBST)->pRootNode->leftNode);
    free((*pBST)->pRootNode);
    free(*pBST);
	(*pBST) = NULL;
}

void        Inorder(BSTNode* pBSTNode)
{
    if (!pBSTNode)
        return ;
    Inorder(pBSTNode->leftNode);
    printf("|%d|", pBSTNode->data);
    Inorder(pBSTNode->rightNode);
}

int main(void)
{
    BST     *pBST;
    BSTNode BSTNode;
	int     lst[10] = {30, 20, 14, 16, 24, 22, 10, 40, 34, 15};
    int     lst2[12] = {30, 46, 14, 10, 24, 22, 11, 40, 34, 20, 15, 16};
    int     idx = -1;

    printf("========= MAKE BST TEST =========\n");
    BSTNode.data = lst[0];
	BSTNode.leftNode = 0;
	BSTNode.rightNode = 0;
	pBST = makeBST(BSTNode);
	Inorder(pBST->pRootNode->leftNode);

    printf("\n------ DEL TEST ------\n");
    deleteBSTNode(pBST, BSTNode);

    printf("\n========= INSERT TEST =========\n");
    while (++idx < 10 && lst[idx])
    {
        BSTNode.data = lst[idx];
        insertChildNodeBST(pBST, BSTNode);
    }
	Inorder(pBST->pRootNode->leftNode);
    printf("\n========= DEL TEST =========\n");
	idx = -1;
	while (++idx < 12)
    {
        BSTNode.data = lst2[idx];
		printf("del %d\n", BSTNode.data);
		printf("bf : ");
		Inorder(pBST->pRootNode->leftNode);
	    deleteBSTNode(pBST, BSTNode);
		printf("\naf : ");
		Inorder(pBST->pRootNode->leftNode);
		printf("\n\n");
    }
	deleteBST(&pBST);
    deleteBSTNode(pBST, BSTNode);
    return(0);
}


/*
	deleteBST // double point ??
*/