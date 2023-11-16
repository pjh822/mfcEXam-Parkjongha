// DlgImage.cpp

#include "stdafx.h"
#include "gPrj.h"
#include "DlgImage.h"
#include "afxdialogex.h"

// CDlgImage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_DLGIMAGE, pParent)
{
    m_pParent = pParent;
    m_nCircleSize = 0;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_UP_PARENT, &CDlgImage::OnBnClickedBtnUpParent)
    ON_WM_PAINT()
END_MESSAGE_MAP()

// CDlgImage 메시지 처리기입니다.

#include "gPrjDlg.h"

void CDlgImage::OnBnClickedBtnUpParent()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    static int n = 100;
    CgPrjDlg* pDlg = (CgPrjDlg*)m_pParent;
    pDlg->callFunc(n++);
}

BOOL CDlgImage::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.
    MoveWindow(0, 0, 640, 480);

    InitImage();
    return TRUE;  // return TRUE unless you set the focus to a control
    // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgImage::InitImage()
{
    int nWidth = 4096 * 5;
    int nHeight = 4096 * 5;
    int nBpp = 8;

    m_image.Create(nWidth, -nHeight, nBpp);
    if (nBpp == 8)
    {
        static RGBQUAD rgb[256];
        for (int i = 0; i < 256; i++)
            rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
        m_image.SetColorTable(0, 256, rgb);
    }

    int nPitch = m_image.GetPitch();
    unsigned char* fm = (unsigned char*)m_image.GetBits();

    memset(fm, 0xff, nWidth * nHeight);
}

void CDlgImage::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
    // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
    if (m_image)
        m_image.Draw(dc, 0, 0);

    drawData(&dc);
}

void CDlgImage::SetCircleSize(int nSize)
{
    // 여기서 크기를 설정하도록 구현
    m_nCircleSize = nSize;
}

void CDlgImage::DrawCircle()
{
    if (m_nCircleSize > 0) {
        CClientDC dc(this);  // CClientDC를 사용하여 화면 DC를 얻습니다.

        int centerX = rand() % (640 - m_nCircleSize * 2);
        int centerY = rand() % (480 - m_nCircleSize * 2);

        // 중심을 계산
        int circleCenterX = centerX + m_nCircleSize;
        int circleCenterY = centerY + m_nCircleSize;

        // 흰색 원으로 원의 중심을 표시
        CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255)); // 흰색 펜 생성
        CPen* pOldWhitePen = dc.SelectObject(&whitePen);

        dc.Ellipse(centerX, centerY, centerX + m_nCircleSize * 2, centerY + m_nCircleSize * 2);

        // 노란 외곽선 그리기
        CPen yellowPen(PS_SOLID, 2, RGB(255, 255, 0));  // 노란색 펜 생성
        CPen* pOldYellowPen = dc.SelectObject(&yellowPen);

        dc.Ellipse(centerX, centerY, centerX + m_nCircleSize * 2, centerY + m_nCircleSize * 2);  // 노란 외곽선 그리기

        // 원 안에 가운데 빨간 "+" 선 그리기
        CPen pen(PS_SOLID, 1, RGB(255, 0, 0));  // 빨간색 펜 생성
        CPen* pOldPen = dc.SelectObject(&pen);

        // 가로선
        dc.MoveTo(circleCenterX - m_nCircleSize, circleCenterY);
        dc.LineTo(circleCenterX + m_nCircleSize, circleCenterY);
        // 세로선
        dc.MoveTo(circleCenterX, circleCenterY - m_nCircleSize);
        dc.LineTo(circleCenterX, circleCenterY + m_nCircleSize);

        dc.SelectObject(pOldPen);
        dc.SelectObject(pOldYellowPen);
        dc.SelectObject(pOldWhitePen);
    }
}


void CDlgImage::drawData(CDC* pDC)
{
    CRect rect;
    CPen pen;
    pen.CreatePen(PS_SOLID, 5, COLOR_RED);

    CClientDC dc(this);
    CPen* pOldPen = dc.SelectObject(&pen); 

    for (int i = 0; i < m_nDataCount; i++)
    {
        rect.SetRect(m_ptData[i], m_ptData[i]);
        rect.InflateRect(2, 2);
        dc.Ellipse(rect);
    }

    dc.SelectObject(pOldPen);
}
