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
// ���ο� �����͸� �߰��Ѵ�
//------------------------------------------------------
bool CRedBlackTree::InsertNode(int iData)
{
	stNODE *pNode;
	CreateNode(&pNode, iData);

	if (m_pRoot == &Nil)
	{
		pNode->Color = BLACK;
		m_pRoot = pNode;
		return true;
	}

	return linkNode(m_pRoot, pNode);

	if (pNode->pParent->Color == RED)
		BalanceTree(pNode);
}

//------------------------------------------------------
// Ʈ���� �����͸� �����Ѵ�
//------------------------------------------------------
void CRedBlackTree::DeleteNode(int iData)
{
	stNODE *pNode = m_pRoot;
	stNODE *pParent = NULL, *pTargetNode = NULL;

	//------------------------------------------------------
	// ������ Ž��
	//------------------------------------------------------
	while (pNode->iData != iData && pNode != &Nil)
	{
		pParent = pNode;

		if (pNode->iData > iData)		pNode = pNode->pLeft;
		else							pNode = pNode->pRight;
	}

	//------------------------------------------------------
	// �ڽĳ�� ���� ���
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
	// �ڽĳ�尡 �ϳ��� ���
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
	// �ڽĳ�尡 �ΰ��� ���
	//------------------------------------------------------
	else
	{
		pTargetNode = unlinkNode(pNode->pLeft, pNode);
		pNode->iData = pTargetNode->iData;
		delete pTargetNode;
	}
}

//------------------------------------------------------
// ��� ����
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
// Ʈ���� ������ �����
//------------------------------------------------------
void CRedBlackTree::BalanceTree(stNODE *pNode)
{
	stNODE *pGrandFa, *pUncle, *pParent;
	pParent  = pNode->pParent;
	pGrandFa = pParent->pParent;
	
	if (pParent == pGrandFa->pLeft)
	{
		if (pNode->Color == RED && pParent->Color == RED && pUncle->Color == RED)
		{
			pParent->Color = BLACK;
			pUncle->Color  = BLACK;

			pGrandFa->Color = RED;

			BalanceTree(pGrandFa);
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
			}
		}
	}

	else if (pParent == pGrandFa->pRight)
	{
		if (pNode->Color == RED && pParent->Color == RED && pUncle->Color == RED)
		{
			pParent->Color = BLACK;
			pUncle->Color = BLACK;

			pGrandFa->Color = RED;

			BalanceTree(pGrandFa);
		}

		else if (pUncle->Color == BLACK && pNode->Color == RED && pParent->Color == RED)
		{
			if (pNode == pParent->pLeft)
			{
				RightRotation(pGrandFa);
			}

			else if (pNode == pParent->pRight)
			{
				pParent->Color = BLACK;
				pGrandFa->Color = RED;

				LeftRotation(pParent);
			}
		}
	}
}

//------------------------------------------------------
// InsertNode ���ο��� ȣ��Ǵ� ��ġ ã�� �߰� ��� �Լ�
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
// deleteNode ���ο��� ȣ��Ǵ� ��ġ ã�� ���� ��� �Լ�
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
// ��� ȸ�� �Լ�(��)
// -Node N �� �������� ��ȸ��
//
//
//       N
//
//   A       D
//
// B   C   E   F
//
//
// < N ���� ��ȸ�� >
//
//        D
//
//     N    F
//
//   A   E
//
// B   C
//
// N �� ���� �ڽ�(D) �� N �� ��ġ�� ���� N �� �����ڽ�(D) �� �������� ����.
//
// �̶� N �� �����ڽ�(D) �� ���� �ڽ�(E) ��  N �� ���������� ����.
//------------------------------------------------------
void CRedBlackTree::LeftRotation(stNODE *pNode)
{
	stNODE *pRightChild = pNode->pRight;

	if (pNode->pParent->pLeft == pNode)			pNode->pParent->pLeft = pRightChild;
	else if (pNode->pParent->pLeft == pNode)	pNode->pParent->pRight = pRightChild;
	pRightChild->pParent = pNode->pParent;

	pNode->pRight = pRightChild->pLeft;
	pRightChild->pLeft->pParent = pNode;

	pRightChild->pLeft = pNode;
	pNode->pParent = pRightChild;
}

//------------------------------------------------------
// ��� ȸ�� �Լ�(��)
// -Node N �� �������� ��ȸ��
//
//       N
//
//   A       D
//
// B   C   E   F
//
//
// < N ���� ��ȸ�� >
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
// N �� ���� �ڽ�(A) �� N �� ��ġ�� ���� N �� �����ڽ�(A) �� ���������� ����.
//
// �̶� N �� �����ڽ�(A) �� ������ �ڽ�(C) ��  N �� �������� ����.
//------------------------------------------------------
void CRedBlackTree::RightRotation(stNODE *pNode)
{
	stNODE *pLeftChild = pNode->pLeft;

	if (pNode->pParent->pLeft == pNode)			pNode->pParent->pLeft  = pLeftChild;
	else if (pNode->pParent->pLeft == pNode)	pNode->pParent->pRight = pLeftChild;
	pLeftChild->pParent = pNode->pParent;

	pNode->pLeft = pLeftChild->pRight;
	pLeftChild->pRight->pParent = pNode;

	pLeftChild->pRight = pNode;
	pNode->pParent = pLeftChild;
}

//------------------------------------------------------
// Ʈ�� ��ü ����
//------------------------------------------------------
bool CRedBlackTree::ReleaseTree(void)
{
	releaseNode(m_pRoot);

	return true;
}

//------------------------------------------------------
// releaseNode ���ο��� ȣ��Ǵ� �������� ����Լ�
//------------------------------------------------------
void CRedBlackTree::releaseNode(stNODE *pNode)
{
	if (pNode == NULL)	return;

	releaseNode(pNode->pLeft);
	releaseNode(pNode->pRight);

	delete pNode;
	pNode = NULL;
}

/*
//------------------------------------------------------
// ������ȸ ��� ���
//------------------------------------------------------
void CRedBlackTree::PreorderPrint(stNODE *pNode, int iDepth, int iLR)
{
	if (iDepth == 0)	pNode = m_pRoot;
	if (pNode == NULL)	return;

	for (int iCnt = 0; iCnt < iDepth; iCnt++)
		printf(" ");

	if (iLR == 0)			printf("[ROOT] ");
	if (iLR == LEFT)		printf("[LEFT %d] ", iDepth);
	if (iLR == RIGHT)		printf("[RIGHT %d] ", iDepth);

	printf("%d", pNode->iData);
	printf("\n");

	PreorderPrint(pNode->pLeft, iDepth + 1, LEFT);
	PreorderPrint(pNode->pRight, iDepth + 1, RIGHT);
}

//------------------------------------------------------
// ������ȸ ��� ���
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
// ������ȸ ��� ���
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