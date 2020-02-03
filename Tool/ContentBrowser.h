#pragma once



// ContentBrowser 폼 보기

class ContentBrowser : public CFormView
{
	DECLARE_DYNCREATE(ContentBrowser)

protected:
	ContentBrowser();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ContentBrowser();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTENTBROWSER };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	virtual void OnDraw(CDC* pDC);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	void InitTabControl();
	void InitTreeControl();
	void UpdateListControlItem();
	DECLARE_MESSAGE_MAP()

public :
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);

public:
	CListCtrl mListCtrl;
	CTabCtrl mTabCtrl;
	CTreeCtrl mTreeCtrl;
	
};


