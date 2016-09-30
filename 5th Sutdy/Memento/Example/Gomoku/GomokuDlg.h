
// GomokuDlg.h : ��� ����
//

#pragma once

#include "GomokuBoard.h"
#include <string>

//��ĭ�� ���� �� ���� : �ʳ��� ����, ������, ��
enum SITE { NONE, BLACK, WHITE };

// CGomokuDlg ��ȭ ����
class CGomokuDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CGomokuDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GOMOKU_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()


public:
	GomokuBoard m_GoBoard;
	BOOL m_WhTurn; //���� �� ����
	SITE m_Board[19][19]; //�ٵ��ǿ� ���� ���� ���¸� �����Ѵ�.
	void DrawBoard(CDC *pDC, int x, int y, SITE dol);
	void DrawBoard_(CDC *pDC, int x, int y, int dol);


	afx_msg void OnBnClickedOk();
};
