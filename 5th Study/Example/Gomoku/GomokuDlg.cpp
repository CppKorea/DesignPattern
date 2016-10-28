
// GomokuDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Gomoku.h"
#include "GomokuDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CGomokuDlg ��ȭ ����



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


// CGomokuDlg �޽��� ó����

BOOL CGomokuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CGomokuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CWnd* pWnd = NULL;
		pWnd = GetDlgItem(IDC_STATIC_BOARD);
		CDC *pDC = pWnd->GetDC();

		//�ٵ���
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

		//�� �׸�
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CGomokuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// x,y ��ǥ�� ���� �׸���.
void CGomokuDlg::DrawBoard_(CDC *pDC, int x, int y, int dol)
{
	if (dol > 0) // ������ ���� ������ �귯��
	{
		pDC->SelectObject(GetStockObject(BLACK_BRUSH));
		pDC->SetTextColor(RGB(255, 255, 255)); // �ؽ�Ʈ ������� ����

	}
	if (dol < 0)
	{
		pDC->SelectObject(GetStockObject(WHITE_BRUSH));
		pDC->SetTextColor(RGB(0,0,0)); // �ؽ�Ʈ ���������� ����
	}

	if (dol != 0) //���� ������ �׸��� �ʴ´�.
	{
		pDC->Ellipse(x * 20 + 2, y * 20 + 2, x * 20 + 18, y * 20 + 18);
		wstring strDol = std::to_wstring(abs(dol));
		pDC->SetBkMode(TRANSPARENT);

		pDC->TextOut(x * 20 + 4, y * 20 + 1 , strDol.c_str(), strDol.length());
	}
}


void CGomokuDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int ax, ay;
	
	ax = point.x / 20; //ȭ�� ��ǥ�� �迭 ��ǥ�� ��ȯ�Ѵ�.
	ay = point.y / 20;

	//�ٵ��� ���̾�� �ϰ� ���� ������ �ʴ� �ڸ����� �Ѵ�.
	if ((ax<0) || (ax >= GO_BOARD_SIZE) || (ay<0) || (ay >= GO_BOARD_SIZE)) return;

	m_GoBoard.PutStone(ax, ay);

	Invalidate(FALSE);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGomokuDlg::OnBnClickedUndo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_GoBoard.RetractStone(3);

	Invalidate();
	UpdateWindow();
	Invalidate(FALSE);
}


void CGomokuDlg::OnBnClickedRedo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_GoBoard.AfterActStone();
	Invalidate();
	UpdateWindow();
	Invalidate(FALSE);
}
