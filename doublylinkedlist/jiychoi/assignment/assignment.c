#include "linkedlist.h"
#include <stdio.h>

void	printLinkedList(LinkedList *pList)
{
	int			i;
	ListNode	*node;

	i = -1;
	node = &pList->headerNode;
	while (++i < pList->currentElementCount)
	{
		node = node->pLink;
		printf("%d ", node->coef);
	}
	printf("\n");
}

void	printAlgebra(LinkedList *pList)
{
	int			i;
	ListNode	*node;

	i = -1;
	node = &pList->headerNode;
	while (++i + 1 < pList->currentElementCount)
	{
		node = node->pLink;
		printf("%dx^%d + ", node->coef, i);
	}
	node = node->pLink;
	printf("%dx^%d", node->coef, i);
	printf("\n");
}

void reverseLinkedList(LinkedList *pList)
{
	ListNode	*node_tmp;
	ListNode	*node_prev;
	ListNode	*node_now;

	if (!pList)
		return ;
	node_prev = pList->headerNode.pLink;
	node_now = pList->headerNode.pLink->pLink;
	node_prev->pLink = NULL;
	while (node_now)
	{
		node_tmp = node_prev;
		node_prev = node_now;
		node_now = node_prev->pLink;
		node_prev->pLink = node_tmp;
	}
	pList->headerNode.pLink = node_prev;
}

LinkedList	*alge_plus(LinkedList *pListA, LinkedList *pListB) //두 다항식을 더하는 함수
{
	LinkedList	*pList; //더한 결과가 들어가는 새로운 연결 리스트
	ListNode	*nodeA; //리스트 A를 순회하는 데에 사용할 노드 포인터
	ListNode	*nodeB; //리스트 B를 순회하는 데에 사용할 노드 포인터
	ListNode	node_temp; //노드 추가 시에 값을 임시로 넣어줄 스택 노드
	int			i; //인덱스용 i

	if (!pListA || !pListB) //둘 중 하나라도 널 포인터라면 덧셈이 성립하지 않으므로
		return (NULL); //널 포인터 반환
	pList = createLinkedList(); //새로운 연결 리스트 생성및 초기화
	if (!pList) //생성 실패시
		return (NULL); //널 포인터 반환
	nodeA = pListA->headerNode.pLink; //리스트 A에서 순회할 노드 지정 (헤더 다음의 0번째 노드)
	nodeB = pListB->headerNode.pLink; //리스트 B에서 순회할 노드 지정 (헤더 다음의 0번째 노드)
	i = 0; //인덱스 0부터 시작 (position = degree가 0부터 시작할 예정)
	while (nodeA || nodeB) //노드 A와 노드 B 중 하나라도 널포인터가 아닐 동안 순회
	{
		if (!nodeA) //만약 노드 A가 널 포인터고, 노드 B의 값만 남았을 경우
		{
			addLLElement(pList, i, *nodeB); //노드 B의 값을 그대로 pList에 새로운 노드로 추가
			nodeB = nodeB->pLink; //노드 B 한 칸 이동
		}
		else if (!nodeB) //만약 노드 B가 널 포인터고, 노드 A의 값만 남았을 경우
		{
			addLLElement(pList, i, *nodeA); //노드 A의 값을 그대로 pList에 새로운 노드로 추가
			nodeA = nodeA->pLink; //노드 A 한 칸 이동
		}
		else //둘 다 널 포인터가 아닐 경우
		{
			node_temp.coef = nodeA->coef + nodeB->coef; //두 노드의 값 (coef) 을 더한 새로운 값을 node_temp에 저장
			addLLElement(pList, i, node_temp); //node_temp 노드의 값을 pList에 추가
			nodeA = nodeA->pLink; //노드 A 한 칸 이동 (다음 차수)
			nodeB = nodeB->pLink; //노드 B 한 칸 이동 (다음 차수)
		}
		i++; //인덱스 (차수, position으로 이용되는 값) 증가
	}
	return (pList); //완성된 덧셈 결과 리스트 반환
}

int	main(void)
{
	LinkedList	*pListA;
	LinkedList	*pListB;
	LinkedList	*pListC;
	ListNode	elem;

	pListA = createLinkedList();
	pListB = createLinkedList();

	elem.coef = 0;
	addLLElement(pListA, 0, elem);
	elem.coef = 0;
	addLLElement(pListA, 1, elem);
	elem.coef = 2;
	addLLElement(pListA, 2, elem);
	elem.coef = 0;
	addLLElement(pListA, 3, elem);
	elem.coef = 0;
	addLLElement(pListA, 4, elem);
	elem.coef = 4;
	addLLElement(pListA, 5, elem);
	elem.coef = 6;
	addLLElement(pListA, 6, elem);
	printAlgebra(pListA);

	elem.coef = 4;
	addLLElement(pListB, 0, elem);
	elem.coef = 0;
	addLLElement(pListB, 1, elem);
	elem.coef = 3;
	addLLElement(pListB, 2, elem);
	elem.coef = 0;
	addLLElement(pListB, 3, elem);
	elem.coef = 2;
	addLLElement(pListB, 4, elem);
	elem.coef = 1;
	addLLElement(pListB, 5, elem);
	printAlgebra(pListB);

	pListC = alge_plus(pListA, pListB);
	printAlgebra(pListC);

	reverseLinkedList(pListC);
	printLinkedList(pListC);
}
