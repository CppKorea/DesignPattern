
// GomokuDlg.h : 헤더 파일
//

#pragma once

#include "GomokuBoard.h"
#include <string>

//한칸의 상태 세 가지 : 않놓은 상태, 검정돌, 희돌
enum SITE { NONE, BLACK, WHITE };

// CGomokuDlg 대화 상자
class CGomokuDlg : public CDialogEx
{
// 생성입니다.
public:
	CGomokuDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GOMOKU_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()


public:
	GomokuBoard m_GoBoard;
	BOOL m_WhTurn; //다음 둘 차례
	SITE m_Board[19][19]; //바둑판에 돌이 놓인 상태를 보관한다.
	void DrawBoard(CDC *pDC, int x, int y, SITE dol);
	void DrawBoard_(CDC *pDC, int x, int y, int dol);


	afx_msg void OnBnClickedOk();
};
