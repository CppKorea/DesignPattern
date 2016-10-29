
// GomokuDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Gomoku.h"
#include "GomokuDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGomokuDlg 대화 상자



CGomokuDlg::CGomokuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GOMOKU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGomokuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGomokuDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(ID_UNDO, &CGomokuDlg::OnBnClickedUndo)
	ON_BN_CLICKED(ID_REDO, &CGomokuDlg::OnBnClickedRedo)
END_MESSAGE_MAP()


// CGomokuDlg 메시지 처리기

BOOL CGomokuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGomokuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGomokuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CWnd* pWnd = NULL;
		pWnd = GetDlgItem(IDC_STATIC_BOARD);
		CDC *pDC = pWnd->GetDC();

		//바둑판
		int x, y;
		for (x = 0;x<GO_BOARD_SIZE;x++)
		{
			pDC->MoveTo(10, 10 + x * 20);
			pDC->LineTo(370, 10 + x * 20);
		}
		for (x = 0;x<GO_BOARD_SIZE;x++)
		{
			pDC->MoveTo(10 + x * 20, 10);
			pDC->LineTo(10 + x * 20, 370);
		}

		//돌 그림
		for (x = 0;x<GO_BOARD_SIZE;x++)
		{
			for (y = 0;y<GO_BOARD_SIZE;y++)
			{	
				DrawBoard_(pDC, x, y, m_GoBoard.GetStone(x, y)); 
			}
		}

		ReleaseDC(pDC); 
		
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGomokuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// x,y 좌표의 돌을 그린다.
void CGomokuDlg::DrawBoard_(CDC *pDC, int x, int y, int dol)
{
	if (dol > 0) // 검정색 돌은 검정색 브러시
	{
		pDC->SelectObject(GetStockObject(BLACK_BRUSH));
		pDC->SetTextColor(RGB(255, 255, 255)); // 텍스트 흰색으로 설정

	}
	if (dol < 0)
	{
		pDC->SelectObject(GetStockObject(WHITE_BRUSH));
		pDC->SetTextColor(RGB(0,0,0)); // 텍스트 검은색으로 설정
	}

	if (dol != 0) //돌이 없으면 그리지 않는다.
	{
		pDC->Ellipse(x * 20 + 2, y * 20 + 2, x * 20 + 18, y * 20 + 18);
		wstring strDol = std::to_wstring(abs(dol));
		pDC->SetBkMode(TRANSPARENT);

		pDC->TextOut(x * 20 + 4, y * 20 + 1 , strDol.c_str(), strDol.length());
	}
}


void CGomokuDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int ax, ay;
	
	ax = point.x / 20; //화면 좌표를 배열 좌표로 변환한다.
	ay = point.y / 20;

	//바둑판 안이어야 하고 돌이 놓이지 않는 자리여야 한다.
	if ((ax<0) || (ax >= GO_BOARD_SIZE) || (ay<0) || (ay >= GO_BOARD_SIZE)) return;

	m_GoBoard.PutStone(ax, ay);

	Invalidate(FALSE);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGomokuDlg::OnBnClickedUndo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_GoBoard.RetractStone(3);

	Invalidate();
	UpdateWindow();
	Invalidate(FALSE);
}


void CGomokuDlg::OnBnClickedRedo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_GoBoard.AfterActStone();
	Invalidate();
	UpdateWindow();
	Invalidate(FALSE);
}
