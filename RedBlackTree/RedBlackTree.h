#ifndef __REDBLACKTREE__H__
#define __REDBLACKTREE__H__

#define LEFT			    1
#define RIGHT		    	2

enum NODE_COLOR
{
	BLACK = 0,
	RED
};

struct stNODE
{
	struct stNODE *pParent;
	struct stNODE *pLeft;
	struct stNODE *pRight;


	NODE_COLOR Color;

	int iData;
};

class CRedBlackTree
{
	
public :
	CRedBlackTree();
	virtual		~CRedBlackTree();

	//------------------------------------------------------
	// ���ο� �����͸� �߰��Ѵ�
	//------------------------------------------------------
	bool		InsertNode(int iData);

	//------------------------------------------------------
	// ���ο� �����͸� �߰��Ѵ�
	//------------------------------------------------------
	void		DeleteNode(int iData);

	//------------------------------------------------------
	// Ʈ�� ��ü ����
	//------------------------------------------------------
	bool		ReleaseTree(void);

	void		PrintNode(HDC hdc, RECT rWinSize);
	//------------------------------------------------------
	// ������ȸ ��� ���
	//------------------------------------------------------
	void		PreorderPrint(HDC hdc, RECT rWinSize, stNODE *pNode = NULL, int iDepth = 0, int iLR = 0);

	//------------------------------------------------------
	// ������ȸ ��� ���
	//------------------------------------------------------
	void		InorderPrint(stNODE *pNode = NULL, int iDepth = 0, int iLR = 0);

	//------------------------------------------------------
	// ������ȸ ��� ���
	//------------------------------------------------------
	void		PostorderPrint(stNODE *pNode = NULL, int iDepth = 0, int iLR = 0);

	void		PrintCount(HDC hdc);
protected :
	//------------------------------------------------------
	// ��� ����
	//------------------------------------------------------
	void		CreateNode(stNODE **pNode, int iData);

	//------------------------------------------------------
	// Ʈ���� ������ �����
	//------------------------------------------------------
	void		BalanceTree(stNODE *pNode);

	//------------------------------------------------------
	// InsertNode ���ο��� ȣ��Ǵ� ��ġ ã�� �߰� ��� �Լ�
	//------------------------------------------------------
	bool		linkNode(stNODE *pParent, stNODE *pChild);

	//------------------------------------------------------
	// deleteNode ���ο��� ȣ��Ǵ� ��ġ ã�� ���� ��� �Լ�
	//------------------------------------------------------
	stNODE		*unlinkNode(stNODE *pNode, stNODE *pParent);

	//------------------------------------------------------
	// ��� ȸ�� �Լ�
	//------------------------------------------------------
	void		LeftRotation(stNODE *pNode);
	void		RightRotation(stNODE *pNode);

	//------------------------------------------------------
	// releaseNode ���ο��� ȣ��Ǵ� �������� ����Լ�
	//------------------------------------------------------
	void		releaseNode(stNODE *pNode);

private :
	stNODE		Nil;	// �� �������. ������ �� / ������ �� / NULL �� ���� �뵵.
	stNODE		*m_pRoot;
	int			m_iNodeCount;
};

#endif