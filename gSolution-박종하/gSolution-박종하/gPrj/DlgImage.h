// DlgImage.h

#pragma once

#define MAX_POINT 100000
// CDlgImage ��ȭ �����Դϴ�.

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgImage();

	CImage m_image;
	CWnd* m_pParent;
	int m_nDataCount = 0;
	CPoint m_ptData[MAX_POINT];

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGIMAGE };
#endif

	// DrawCircle �Լ��� �ܺο� �����մϴ�.
	void DrawCircle();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnUpParent();
	virtual BOOL OnInitDialog();


private:
	void InitImage();
	void drawData(CDC* pDC);

public:
	afx_msg void OnPaint();

public:
	void SetCircleSize(int nSize);

private:
	int m_nCircleSize;  // �߰��� �κ�

private:
	CPoint m_Center;
};

