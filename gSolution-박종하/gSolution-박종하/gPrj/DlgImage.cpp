// DlgImage.cpp

#include "stdafx.h"
#include "gPrj.h"
#include "DlgImage.h"
#include "afxdialogex.h"

// CDlgImage ��ȭ �����Դϴ�.

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

// CDlgImage �޽��� ó�����Դϴ�.

#include "gPrjDlg.h"

void CDlgImage::OnBnClickedBtnUpParent()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    static int n = 100;
    CgPrjDlg* pDlg = (CgPrjDlg*)m_pParent;
    pDlg->callFunc(n++);
}

BOOL CDlgImage::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
    MoveWindow(0, 0, 640, 480);

    InitImage();
    return TRUE;  // return TRUE unless you set the focus to a control
    // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
    // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
    if (m_image)
        m_image.Draw(dc, 0, 0);

    drawData(&dc);
}

void CDlgImage::SetCircleSize(int nSize)
{
    // ���⼭ ũ�⸦ �����ϵ��� ����
    m_nCircleSize = nSize;
}

void CDlgImage::DrawCircle()
{
    if (m_nCircleSize > 0) {
        CClientDC dc(this);  // CClientDC�� ����Ͽ� ȭ�� DC�� ����ϴ�.

        int centerX = rand() % (640 - m_nCircleSize * 2);
        int centerY = rand() % (480 - m_nCircleSize * 2);

        // �߽��� ���
        int circleCenterX = centerX + m_nCircleSize;
        int circleCenterY = centerY + m_nCircleSize;

        // ��� ������ ���� �߽��� ǥ��
        CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255)); // ��� �� ����
        CPen* pOldWhitePen = dc.SelectObject(&whitePen);

        dc.Ellipse(centerX, centerY, centerX + m_nCircleSize * 2, centerY + m_nCircleSize * 2);

        // ��� �ܰ��� �׸���
        CPen yellowPen(PS_SOLID, 2, RGB(255, 255, 0));  // ����� �� ����
        CPen* pOldYellowPen = dc.SelectObject(&yellowPen);

        dc.Ellipse(centerX, centerY, centerX + m_nCircleSize * 2, centerY + m_nCircleSize * 2);  // ��� �ܰ��� �׸���

        // �� �ȿ� ��� ���� "+" �� �׸���
        CPen pen(PS_SOLID, 1, RGB(255, 0, 0));  // ������ �� ����
        CPen* pOldPen = dc.SelectObject(&pen);

        // ���μ�
        dc.MoveTo(circleCenterX - m_nCircleSize, circleCenterY);
        dc.LineTo(circleCenterX + m_nCircleSize, circleCenterY);
        // ���μ�
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
