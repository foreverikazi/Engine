// ContentBrowser.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "ContentBrowser.h"
#include <filesystem>
#include <string>
#include <atlstr.h>
#include <stack>

// ContentBrowser
using namespace std;
namespace fs = std::experimental::filesystem::v1;
IMPLEMENT_DYNCREATE(ContentBrowser, CFormView)

ContentBrowser::ContentBrowser()
	: CFormView(IDD_CONTENTBROWSER)
{

}

ContentBrowser::~ContentBrowser()
{
}

void ContentBrowser::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mListCtrl);
	DDX_Control(pDX, IDC_TAB1, mTabCtrl);
	DDX_Control(pDX, IDC_TREE2, mTreeCtrl);
}

BEGIN_MESSAGE_MAP(ContentBrowser, CFormView)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE2, &ContentBrowser::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// ContentBrowser 진단

#ifdef _DEBUG
void ContentBrowser::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ContentBrowser::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

void ContentBrowser::OnDraw(CDC* pDC)
{
	
}

#endif
#endif //_DEBUG


void ContentBrowser::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	InitTabControl();
	InitTreeControl();
	//InitListControl();
}

void ContentBrowser::InitTabControl()
{
	mTabCtrl.InsertItem(0, L"컨텐츠 브라우저");
}

void ContentBrowser::InitTreeControl()
{
	HTREEITEM parentDir;
	stack<HTREEITEM> parentDirStack;
	fs::path contentPolderPath = fs::current_path() /= "Content";
	int depth = 0;

	for (auto&& file = fs::recursive_directory_iterator(contentPolderPath); file != fs::recursive_directory_iterator(); file++)
	{
		if (depth > file.depth())
		{
			for (int i = 0; i < depth - file.depth(); i++)
				parentDirStack.pop();
		}
		depth = file.depth();

		if (fs::is_directory(*file))
		{
			if (!fs::is_empty(*file))
			{
				if (file.depth() == 0)
				{
					parentDir = mTreeCtrl.InsertItem(CA2T(file->path().filename().string().c_str()), 0, 0, TVI_ROOT, TVI_LAST);
				}
				else
				{
					parentDir = mTreeCtrl.InsertItem(CA2T(file->path().filename().string().c_str()), 0, 0, parentDirStack.top(), TVI_LAST);
				}
				parentDirStack.push(parentDir);
			}
			else
			{
				if (!parentDirStack.empty())
				{
					mTreeCtrl.InsertItem(CA2T(file->path().filename().string().c_str()), 0, 0, parentDirStack.top(), TVI_LAST);
				}
				else
				{
					mTreeCtrl.InsertItem(CA2T(file->path().filename().string().c_str()), 0, 0, TVI_ROOT, TVI_LAST);
				}
			}
		}
	}
}

void ContentBrowser::UpdateListControlItem()
{
	stack<CString> strFilename;
	fs::path contentPolderPath = fs::current_path() /= "Content";

	HTREEITEM selectedItem = mTreeCtrl.GetSelectedItem();
	HTREEITEM parentItem;
	int iCount = 0;

	strFilename.push(mTreeCtrl.GetItemText(selectedItem));
	while (parentItem = mTreeCtrl.GetParentItem(selectedItem))
	{
		strFilename.push(mTreeCtrl.GetItemText(parentItem));
		selectedItem = parentItem;
	}
	while (!strFilename.empty())
	{
		contentPolderPath /= strFilename.top().GetString();
		strFilename.pop();
	}

	for (auto&& file : fs::directory_iterator(contentPolderPath))
	{
		mListCtrl.InsertItem(iCount++, CA2T(file.path().filename().string().c_str()));
	}
}



void ContentBrowser::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//UpdateData(TRUE);
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mListCtrl.DeleteAllItems();
	UpdateListControlItem();

	*pResult = 0;
	//UpdateData(FALSE);
}
