// DlgImage.h

#pragma once

#define MAX_POINT 100000
// CDlgImage 대화 상자입니다.

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CImage m_image;
	CWnd* m_pParent;
	int m_nDataCount = 0;
	CPoint m_ptData[MAX_POINT];

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGIMAGE };
#endif

	// DrawCircle 함수를 외부에 선언합니다.
	void DrawCircle();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
	int m_nCircleSize;  // 추가된 부분

private:
	CPoint m_Center;
};

