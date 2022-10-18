// MyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "SDI.h"
#include "MyTreeView.h"
#include "SDIDoc.h"


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
	ON_WM_LBUTTONDOWN()
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
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_CHECKBOXES;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;

}


void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CTreeCtrl& tree = GetTreeCtrl();
	CTreeView::OnLButtonDown(nFlags, point);
	CRect rc;
	{
		tree.GetItemRect(m_hLines, &rc, false);
		if (rc.PtInRect(point))
			tree.SelectItem(m_hLines);

		tree.GetItemRect(m_hLine1, &rc, false);
		if (rc.PtInRect(point))
			tree.SelectItem(m_hLine1);

		tree.GetItemRect(m_hLine2, &rc, false);
		if (rc.PtInRect(point))
			tree.SelectItem(m_hLine2);

		tree.GetItemRect(m_hLine3, &rc, false);
		if (rc.PtInRect(point))
			tree.SelectItem(m_hLine3);
	}

	{
		tree.GetItemRect(m_hColor, &rc, false);
		if (rc.PtInRect(point))
			tree.SelectItem(m_hColor);

		tree.GetItemRect(m_hColor1, &rc, false);
		if (rc.PtInRect(point))
			tree.SelectItem(m_hColor1);

		tree.GetItemRect(m_hColor2, &rc, false);
		if (rc.PtInRect(point))
			tree.SelectItem(m_hColor2);

		tree.GetItemRect(m_hColor3, &rc, false);
		if (rc.PtInRect(point))
			tree.SelectItem(m_hColor3);
	}

	

	if (tree.GetSelectedItem() == m_hLines)
	{
		bool check = tree.GetCheck(m_hLines);
		tree.SetCheck(m_hLine1, check);
		tree.SetCheck(m_hLine2, check);
		tree.SetCheck(m_hLine3, check);

	}
	else
		tree.SetCheck(m_hLines, false);

	if (tree.GetSelectedItem() == m_hColor)
	{
		bool check = tree.GetCheck(m_hColor);
		tree.SetCheck(m_hColor1, check);
		tree.SetCheck(m_hColor2, check);
		tree.SetCheck(m_hColor3, check);

	}
	else
		tree.SetCheck(m_hColor, false);

	m_pDoc->m_bLine1 = tree.GetCheck(m_hLine1);
	m_pDoc->m_bLine2 = tree.GetCheck(m_hLine2);
	m_pDoc->m_bLine3 = tree.GetCheck(m_hLine3);

	m_pDoc->m_bColor1 = tree.GetCheck(m_hColor1);

	m_pDoc->m_pTreeView->Invalidate();


}
