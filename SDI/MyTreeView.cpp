// MyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "SDI.h"
#include "MyTreeView.h"


// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG

void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();
	m_hLines = tree.InsertItem(L"Толщина", -1, -1, NULL, TVI_FIRST);

	m_hLine3 = tree.InsertItem(L"Толщина 3", -1, -1, m_hLines, TVI_FIRST);
	m_hLine2 = tree.InsertItem(L"Толщина 2", -1, -1, m_hLines, TVI_FIRST);
	m_hLine1 = tree.InsertItem(L"Толщина 1", -1, -1, m_hLines, TVI_FIRST);
	
	m_hColor = tree.InsertItem(L"Цвет", -1, -1, NULL, TVI_FIRST);

	m_hColor3 = tree.InsertItem(L"Цвет 3", -1, -1, m_hColor, TVI_FIRST);
	m_hColor2 = tree.InsertItem(L"Цвет 2", -1, -1, m_hColor, TVI_FIRST);
	m_hColor1 = tree.InsertItem(L"Цвет 1", -1, -1, m_hColor, TVI_FIRST);
	
	tree.Expand(m_hLines, TVE_EXPAND);
	tree.Expand(m_hColor, TVE_EXPAND);
}

// Обработчики сообщений CMyTreeView


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;

}
