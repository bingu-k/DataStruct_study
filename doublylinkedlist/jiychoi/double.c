#include "doublylist.h"
#include <stdio.h>
#include <stdlib.h>

DoublyList	*createDoublyList(void) //양방향 연결리스트 생성 및 초기화
{
	DoublyList	*dList; //반환해줄 DoublyList 선언

	dList = malloc(sizeof(DoublyList)); //리스트 메모리 할당
	if (!dList) //DoublyList 할당 실패 시 (malloc이 널포인터 반환했을 시)
		return (NULL); //바로 널포인터 반환 (Malloc Guard)
	dList->headerNode.pLLink = &dList->headerNode;
	dList->headerNode.pRLink = &dList->headerNode;
	//양방향 연결리스트는 마지막 노드가 맨 처음 노드를 가리키므로 (원형)
	//헤더 노드의 좌우 포인터가 자기 자신을 가리키도록 해줌
	dList->currentElementCount = 0; //DoublyList의 현재 원소 개수 0으로 초기화
	return (dList); //초기화된 리스트 반환
}

void	deleteDoublyList(DoublyList *pList) //DoublyList 삭제
{
	clearDoublyList(pList); //내부의 모든 노드를 Clear해주고 (하나하나 free)
	free(pList); //리스트 그 자체를 free
}

int	addDLElement(DoublyList *pList, int position, DoublyListNode element) //노드 추가
{
	int				i; //인덱스용 i 선언
	DoublyListNode	*to_add; //추가할 노드 생성
	DoublyListNode	*node; //목록을 순회하기 위한 노드 변수

	if (position > pList->currentElementCount + 1 || position < 0)
	//currentElementCount (최대 인덱스 + 1) 보다 크거나 음수일 경우 예외처리
		return (-1); //-1 반환 (에러)
	to_add = malloc(sizeof(DoublyListNode)); //추가할 노드에 메모리 할당
	if (!to_add) //할당 실패시
		return (-1); //-1 반환 (에러)
	to_add->data = element.data; //to_add 노드 (리스트에 추가할 노드) 의 data를
	//원래 넣고자 했던 Element의 data값을 넣어줌으로써 초기화
	i = -1; //인덱스 i는 -1부터 시작
	node = &pList->headerNode; //순회용 노드인 node 포인터는 header부터 시작
	while (++i < position) //전위연산을 통해 인덱스를 0부터 시작하게끔 함
		node = node->pRLink; //0번째 포지션부터 원하는 포지션 직전 노드까지 이동 (Position - 1)
	to_add->pLLink = node; //추가할 노드의 왼쪽에 node 배치 (인덱스가 Position - 1인 노드)
	to_add->pRLink = node->pRLink; //추가할 노드의 오른쪽에 node->pRLink 배치 (인덱스가 Position이었으나 Position + 1이 됨)
	node->pRLink = to_add; //node의 오른쪽에 추가할 노드 배치
	to_add->pRLink->pLLink = to_add; //node의 오른쪽에 있었던 노드의 왼쪽에 추가할 노드 배치
	pList->currentElementCount++; //원소 개수 1 증가
	return (0);
}

int	removeDLElement(DoublyList *pList, int position) //노드 제거
{
	int				i; //인덱스용 i
	DoublyListNode	*to_del; //삭제할 노드 포인터
	DoublyListNode	*node; //목록을 순회하기 위한 노드 변수

	if (pList->currentElementCount <= position || position < 0)
	//currentElementCount (최대 인덱스 + 1) 보다 크거나 같을때, 음수일 경우 예외처리
		return (-1); //-1 반환 (에러)
	i = -1; //인덱스 i는 -1부터 시작
	node = &pList->headerNode; //순회용 노드인 node 포인터는 header부터 시작
	while (++i < position) //전위연산을 통해 인덱스를 0부터 시작하게끔 함
		node = node->pRLink; //0번째 포지션부터 원하는 포지션 직전 노드까지 이동 (Position - 1)
	to_del = node->pRLink; //삭제할 노드는 방금 찾은 노드의 오른쪽
	//(인덱스가 Position - 1인 노드의 오른쪽이므로 인덱스가 Position인 노드)
	to_del->pLLink->pRLink = to_del->pRLink;
	//삭제할 노드의 왼쪽 노드의 오른쪽에 삭제할 노드의 오른쪽에 있던 노드 배치
	to_del->pRLink->pLLink = to_del->pLLink;
	//삭제할 노드의 오른쪽 노드의 왼쪽에 삭제할 노드의 왼쪽에 있던 노드 배치
	free(to_del); //노드 삭제
	pList->currentElementCount--; //원소 개수 1 감소
	return (0);
}

void clearDoublyList(DoublyList* pList) //리스트 비우기
{
	while (pList->currentElementCount > 0) //원소개수가 0이 될 때까지
		removeDLElement(pList, 0); //첫번째 노드 삭제 반복
}

int getDoublyListLength(DoublyList* pList) //리스트 길이 반환
{
	return (pList->currentElementCount); //원소개수 반환
}

DoublyListNode* getDLElement(DoublyList* pList, int position) //리스트 원소 받아오기
{
	int				i; //원소 접근용 인덱스
	DoublyListNode	*to_find; //찾아서 반환할 노드를 담은 포인터

	if (pList->currentElementCount <= position || position < 0)
	//currentElementCount (최대 인덱스 + 1) 보다 크거나 음수일 경우 예외처리
		return (NULL); //널포인터 반환 (에러)
	i = -1; //인덱스 i는 -1부터 시작
	to_find = &pList->headerNode; //순회용 노드인 node 포인터는 header부터 시작
	while (++i <= position) //전위연산을 통해 인덱스를 0부터 시작하게끔 함
		to_find = to_find->pRLink; //0번째 포지션부터 원하는 포지션 인덱스의 노드까지 이동
	return (to_find); //해당 노드 반환
}

void displayDoublyList(DoublyList* pList) //리스트 출력
{
	int				i; //원소 접근용 인덱스
	DoublyListNode	*node; //출력할 노드를 담은 임시포인터

	node = &pList->headerNode; //헤더노드부터 시작
	i = -1; //인덱스는 -1부터 시작
	while (++i < pList->currentElementCount) //전위연산을 통해 0부터 현재 원소개수 직전까지 순회
	{
		node = node->pRLink; //다음 노드로 이동
		printf("%d ", node->data); //노드 출력
	}
	printf("\n"); //개행 출력
}
