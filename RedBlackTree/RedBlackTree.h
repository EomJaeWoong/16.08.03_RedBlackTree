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
	// 새로운 데이터를 추가한다
	//------------------------------------------------------
	bool		InsertNode(int iData);

	//------------------------------------------------------
	// 새로운 데이터를 추가한다
	//------------------------------------------------------
	void		DeleteNode(int iData);

	//------------------------------------------------------
	// 트리 전체 삭제
	//------------------------------------------------------
	bool		ReleaseTree(void);

	void		PrintNode(HDC hdc, RECT rWinSize);
	//------------------------------------------------------
	// 전위순회 방식 출력
	//------------------------------------------------------
	void		PreorderPrint(HDC hdc, RECT rWinSize, stNODE *pNode = NULL, int iDepth = 0, int iLR = 0);

	//------------------------------------------------------
	// 중위순회 방식 출력
	//------------------------------------------------------
	void		InorderPrint(stNODE *pNode = NULL, int iDepth = 0, int iLR = 0);

	//------------------------------------------------------
	// 후위순회 방식 출력
	//------------------------------------------------------
	void		PostorderPrint(stNODE *pNode = NULL, int iDepth = 0, int iLR = 0);

	void		PrintCount(HDC hdc);
protected :
	//------------------------------------------------------
	// 노드 생성
	//------------------------------------------------------
	void		CreateNode(stNODE **pNode, int iData);

	//------------------------------------------------------
	// 트리의 균형을 맞춘다
	//------------------------------------------------------
	void		BalanceTree(stNODE *pNode);

	//------------------------------------------------------
	// InsertNode 내부에서 호출되는 위치 찾아 추가 재귀 함수
	//------------------------------------------------------
	bool		linkNode(stNODE *pParent, stNODE *pChild);

	//------------------------------------------------------
	// deleteNode 내부에서 호출되는 위치 찾아 삭제 재귀 함수
	//------------------------------------------------------
	stNODE		*unlinkNode(stNODE *pNode, stNODE *pParent);

	//------------------------------------------------------
	// 노드 회전 함수
	//------------------------------------------------------
	void		LeftRotation(stNODE *pNode);
	void		RightRotation(stNODE *pNode);

	//------------------------------------------------------
	// releaseNode 내부에서 호출되는 노드삭제용 재귀함수
	//------------------------------------------------------
	void		releaseNode(stNODE *pNode);

private :
	stNODE		Nil;	// 끝 리프노드. 무조건 블랙 / 데이터 무 / NULL 의 같은 용도.
	stNODE		*m_pRoot;
	int			m_iNodeCount;
};

#endif