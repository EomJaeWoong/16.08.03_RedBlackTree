#include "stdafx.h"

CRedBlackTree::CRedBlackTree()
{
	m_pRoot = &Nil;

	Nil.Color = BLACK;
	Nil.pParent = NULL;
	Nil.pLeft = NULL;
	Nil.pRight = NULL;

	m_iNodeCount = 0;
}

CRedBlackTree::~CRedBlackTree()
{

}

//------------------------------------------------------
// 새로운 데이터를 추가한다
//------------------------------------------------------
bool CRedBlackTree::InsertNode(int iData)
{
	stNODE *pNode;
	CreateNode(&pNode, iData);

	if (m_pRoot == &Nil)
	{
		pNode->Color = BLACK;
		m_pRoot = pNode;
		m_iNodeCount++;
		return true;
	}

	linkNode(m_pRoot, pNode);
	m_iNodeCount++;

	if (pNode->pParent->Color == RED)
		BalanceTree(pNode);
}

//------------------------------------------------------
// 트리의 데이터를 삭제한다
//------------------------------------------------------
void CRedBlackTree::DeleteNode(int iData)
{
	stNODE *pNode = m_pRoot;
	stNODE *pParent = NULL, *pTargetNode = NULL;

	//------------------------------------------------------
	// 데이터 탐색
	//------------------------------------------------------
	while (pNode->iData != iData && pNode != &Nil)
	{
		pParent = pNode;

		if (pNode->iData > iData)		pNode = pNode->pLeft;
		else							pNode = pNode->pRight;
	}

	//------------------------------------------------------
	// 자식노드 없는 경우
	//------------------------------------------------------
	if (pNode->pLeft == &Nil && pNode->pRight == &Nil)
	{
		if (pNode == pParent->pLeft)
			pParent->pLeft = &Nil;
		else
			pParent->pRight = &Nil;

		delete pNode;
	}

	//------------------------------------------------------
	// 자식노드가 하나인 경우
	//------------------------------------------------------
	else if (pNode->pLeft != &Nil && pNode->pRight == &Nil)
	{
		if (pNode == pParent->pLeft)
			pParent->pLeft = pNode->pLeft;
		else
			pParent->pRight = pNode->pLeft;
		delete pNode;
	}

	else if (pNode->pLeft == &Nil && pNode->pRight != &Nil)
	{
		if (pNode == pParent->pLeft)
			pParent->pLeft = pNode->pRight;
		else
			pParent->pRight = pNode->pRight;
		delete pNode;
	}

	//------------------------------------------------------
	// 자식노드가 두개인 경우
	//------------------------------------------------------
	else
	{
		pTargetNode = unlinkNode(pNode->pLeft, pNode);
		pNode->iData = pTargetNode->iData;
		delete pTargetNode;
	}
}

//------------------------------------------------------
// 노드 생성
//------------------------------------------------------
void CRedBlackTree::CreateNode(stNODE **pNode, int iData)
{
	*pNode = new stNODE;
	(*pNode)->iData   = iData;
	(*pNode)->pLeft   = &Nil;
	(*pNode)->pRight  = &Nil;
	(*pNode)->pParent = &Nil;
	(*pNode)->Color   = RED;
}

//------------------------------------------------------
// 트리의 균형을 맞춘다
//------------------------------------------------------
void CRedBlackTree::BalanceTree(stNODE *pNode)
{
	stNODE *pGrandFa, *pUncle, *pParent;
	pParent  = pNode->pParent;
	pGrandFa = pParent->pParent;
	
	if (pParent == pGrandFa->pLeft)
	{
		pUncle = pGrandFa->pRight;

		if (pNode->Color == RED && pParent->Color == RED && pUncle->Color == RED)
		{
			pParent->Color = BLACK;
			pUncle->Color  = BLACK;

			pGrandFa->Color = RED;

			if (pGrandFa == m_pRoot)	pGrandFa->Color = BLACK;
			else						BalanceTree(pGrandFa);
		}

		else if (pUncle->Color == BLACK && pNode->Color == RED && pParent->Color == RED)
		{
			if (pNode == pParent->pLeft)
			{
				pParent->Color = BLACK;
				pGrandFa->Color = RED;

				RightRotation(pGrandFa);
			}

			else if (pNode == pParent->pRight)
			{
				LeftRotation(pParent);
				BalanceTree(pNode->pLeft);
			}
		}
	}

	else if (pParent == pGrandFa->pRight)
	{
		pUncle = pGrandFa->pLeft;

		if (pNode->Color == RED && pParent->Color == RED && pUncle->Color == RED)
		{
			pParent->Color = BLACK;
			pUncle->Color = BLACK;

			pGrandFa->Color = RED;

			if (pGrandFa == m_pRoot)	pGrandFa->Color = BLACK;
			else						BalanceTree(pGrandFa);
		}

		else if (pUncle->Color == BLACK && pNode->Color == RED && pParent->Color == RED)
		{
			if (pNode == pParent->pLeft)
			{
				RightRotation(pParent);
				BalanceTree(pNode->pRight);
			}

			else if (pNode == pParent->pRight)
			{
				pParent->Color = BLACK;
				pGrandFa->Color = RED;

				LeftRotation(pGrandFa);
			}
		}
	}
}

//------------------------------------------------------
// InsertNode 내부에서 호출되는 위치 찾아 추가 재귀 함수
//------------------------------------------------------
bool CRedBlackTree::linkNode(stNODE *pParent, stNODE *pChild)
{
	if (pParent->iData > pChild->iData)
	{
		if (pParent->pLeft == &Nil)
		{
			pParent->pLeft = pChild;
			pChild->pParent = pParent;
			return true;
		}

		else
			linkNode(pParent->pLeft, pChild);
	}

	else if (pParent->iData < pChild->iData)
	{
		if (pParent->pRight == &Nil)
		{
			pParent->pRight = pChild;
			pChild->pParent = pParent;
			return true;
		}

		else
			linkNode(pParent->pRight, pChild);
	}

	return false;
}

//------------------------------------------------------
// deleteNode 내부에서 호출되는 위치 찾아 삭제 재귀 함수
//------------------------------------------------------
stNODE *CRedBlackTree::unlinkNode(stNODE *pNode, stNODE *pParent)
{
	if (pNode->pRight == &Nil)
	{
		pParent->pRight = &Nil;
		return pNode;
	}

	return unlinkNode(pNode->pRight, pNode);
}

//------------------------------------------------------
// 노드 회전 함수(좌)
// -Node N 을 기준으로 좌회전
//
//
//       N
//
//   A       D
//
// B   C   E   F
//
//
// < N 에서 좌회전 >
//
//        D
//
//     N    F
//
//   A   E
//
// B   C
//
// N 의 오른 자식(D) 이 N 의 위치로 오며 N 은 왼쪽자식(D) 의 왼편으로 붙음.
//
// 이때 N 의 오른자식(D) 의 왼편 자식(E) 은  N 의 오른편으로 붙음.
//------------------------------------------------------
void CRedBlackTree::LeftRotation(stNODE *pNode)
{
	stNODE *pRightChild = pNode->pRight;

	if (pNode == m_pRoot)						m_pRoot = pRightChild;
	else if (pNode->pParent->pLeft == pNode)	pNode->pParent->pLeft = pRightChild;
	else if (pNode->pParent->pRight == pNode)	pNode->pParent->pRight = pRightChild;
	pRightChild->pParent = pNode->pParent;

	if (pNode->pLeft == &Nil)
	{
		pRightChild->pLeft = pNode;
		pNode->pParent = pRightChild;
		pNode->pRight = &Nil;
	}

	else
	{
		pNode->pRight = pRightChild->pLeft;
		pRightChild->pLeft->pParent = pNode;

		pRightChild->pLeft = pNode;
		pNode->pParent = pRightChild;
	}
}

//------------------------------------------------------
// 노드 회전 함수(우)
// -Node N 을 기준으로 우회전
//
//       N
//
//   A       D
//
// B   C   E   F
//
//
// < N 에서 우회전 >
//
//          A
//
//      B       N
//
//           C     D
//
//               E    F
//
//
// N 의 왼쪽 자식(A) 이 N 의 위치로 오며 N 은 왼쪽자식(A) 의 오른편으로 붙음.
//
// 이때 N 의 왼쪽자식(A) 의 오른편 자식(C) 은  N 의 왼편으로 붙음.
//------------------------------------------------------
void CRedBlackTree::RightRotation(stNODE *pNode)
{
	stNODE *pLeftChild = pNode->pLeft;

	if(pNode == m_pRoot)							m_pRoot = pLeftChild;
	else if (pNode->pParent->pLeft == pNode)		pNode->pParent->pLeft  = pLeftChild;
	else if (pNode->pParent->pRight == pNode)		pNode->pParent->pRight = pLeftChild;
	pLeftChild->pParent = pNode->pParent;

	if (pNode->pLeft == &Nil)
	{
		pLeftChild->pLeft = pNode;
		pNode->pParent = pLeftChild;
		pNode->pRight = &Nil;
	}

	else
	{
		pNode->pLeft = pLeftChild->pRight;
		pLeftChild->pRight->pParent = pNode;

		pLeftChild->pRight = pNode;
		pNode->pParent = pLeftChild;
	}

	Nil.pParent = NULL;
}

//------------------------------------------------------
// 트리 전체 삭제
//------------------------------------------------------
bool CRedBlackTree::ReleaseTree(void)
{
	releaseNode(m_pRoot);

	return true;
}

//------------------------------------------------------
// releaseNode 내부에서 호출되는 노드삭제용 재귀함수
//------------------------------------------------------
void CRedBlackTree::releaseNode(stNODE *pNode)
{
	if (pNode == NULL)	return;

	releaseNode(pNode->pLeft);
	releaseNode(pNode->pRight);

	delete pNode;
	pNode = NULL;
}

void CRedBlackTree::PrintNode(HDC hdc, RECT rWinSize)
{
	PreorderPrint(hdc, rWinSize);
}

//------------------------------------------------------
// 전위순회 방식 출력
//------------------------------------------------------
void CRedBlackTree::PreorderPrint(HDC hdc, RECT rWinSize, stNODE *pNode, int iDepth, int iLR)
{
	if (iDepth == 0)	pNode = m_pRoot;
	if (pNode == &Nil)	return;

	HFONT hFont, hFontOld;
	TCHAR tData[5];
	int iTextLocation;

	hFont = CreateFont(15, 0, 0, 0, 800, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, NULL);
	hFontOld = (HFONT)SelectObject(hdc, hFont);
	if (pNode->Color == BLACK)			SetTextColor(hdc, RGB(0, 0, 0));
	else if (pNode->Color == RED)		SetTextColor(hdc, RGB(255, 0, 0));

	SetTextAlign(hdc, TA_CENTER);
	SetBkMode(hdc, TRANSPARENT);

	MoveToEx(hdc, rWinSize.left, (iDepth - 1) * 80 + 20, NULL);

	if (pNode == m_pRoot)			iTextLocation = rWinSize.right / 2;
	else if (iLR == LEFT)	iTextLocation = rWinSize.left - rWinSize.right / pow(2.0, (iDepth + 1));
	else if (iLR == RIGHT)	iTextLocation = rWinSize.left + rWinSize.right / pow(2.0, (iDepth + 1));
	LineTo(hdc, iTextLocation, iDepth * 80 - 10);

	wsprintf(tData, TEXT("%d"), pNode->iData);
	TextOut(hdc, iTextLocation, iDepth * 80, tData, wcslen(tData));

	rWinSize.left = iTextLocation;
	PreorderPrint(hdc, rWinSize, pNode->pLeft, iDepth + 1, LEFT);
	PreorderPrint(hdc, rWinSize, pNode->pRight, iDepth + 1, RIGHT);

	SelectObject(hdc, hFontOld);
}

void CRedBlackTree::PrintCount(HDC hdc)
{
	TCHAR tCount[20];

	SetTextAlign(hdc, TA_LEFT);
	SetTextColor(hdc, RGB(0, 0, 0));

	wsprintf(tCount, TEXT("NodeCount : %d"), m_iNodeCount);
	TextOut(hdc, 0, 0, tCount, wcslen(tCount));
}

/*
//------------------------------------------------------
// 중위순회 방식 출력
//------------------------------------------------------
void CRedBlackTree::InorderPrint(st_TNODE *pNode, int iDepth, int iLR)
{
	if (iDepth == 0)	pNode = m_m_pRoot;
	if (pNode == NULL)	return;

	InorderPrint(pNode->pLeft, iDepth + 1, LEFT);

	for (int iCnt = 0; iCnt < iDepth; iCnt++)
		printf(" ");

	if (iLR == 0)			printf("[ROOT] ");
	if (iLR == LEFT)		printf("[LEFT %d] ", iDepth);
	if (iLR == RIGHT)		printf("[RIGHT %d] ", iDepth);

	printf("%d", pNode->iData);
	printf("\n");

	InorderPrint(pNode->pRight, iDepth + 1, RIGHT);
}

//------------------------------------------------------
// 후위순회 방식 출력
//------------------------------------------------------
void CRedBlackTree::PostorderPrint(st_TNODE *pNode, int iDepth, int iLR)
{
	if (iDepth == 0)	pNode = m_m_pRoot;
	if (pNode == NULL)	return;

	PostorderPrint(pNode->pLeft, iDepth + 1, LEFT);
	PostorderPrint(pNode->pRight, iDepth + 1, RIGHT);

	for (int iCnt = 0; iCnt < iDepth; iCnt++)
		printf(" ");

	if (iLR == 0)			printf("[ROOT] ");
	if (iLR == LEFT)		printf("[LEFT %d] ", iDepth);
	if (iLR == RIGHT)		printf("[RIGHT %d] ", iDepth);

	printf("%d", pNode->iData);
	printf("\n");
}
*/