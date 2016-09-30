
// GomokuDlg.h : ��� ����
//

#pragma once

#include "GomokuBoard.h"
#include <string>

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
	afx_msg void OnBnClickedUndo();
	DECLARE_MESSAGE_MAP()


public:
	GomokuBoard m_GoBoard;
	
	void DrawBoard_(CDC *pDC, int x, int y, int dol);
};
