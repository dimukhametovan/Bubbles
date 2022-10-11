
// SDIDoc.cpp: реализация класса CSDIDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDI.h"
#include <stdlib.h> 
#include <time.h>
#endif

#include "MyTreeView.h"

#include "SDIDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSDIDoc

IMPLEMENT_DYNCREATE(CSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDIDoc, CDocument)
END_MESSAGE_MAP()

CMyCircle::CMyCircle()
{
	

	mx = (2 + rand() % 5) * 2; //передвижение по х
	my = (2 + rand() % 5) * 2; //передвижение по у
}

CMyCircle::CMyCircle(int x, int y, int r)
{
	m_iX = x;
	m_iY = y;
	m_iR = r;
	
	
}

void CMyCircle::Draw(CDC* pDc)
{
	
	pDc->MoveTo(m_iX + m_iR, m_iY);
	pDc->AngleArc(m_iX, m_iY, m_iR, 0, 360);
}

void CMyCircle::Randomxy(CRect& rect)
{
	m_iX += mx;
	m_iY += my;
	if (m_iY + m_iR >= rect.Height()) {
		my *= -1;
	}

	if (m_iY - m_iR <= 0) {
		my *= -1;
	}

	if (m_iX + m_iR >= rect.Width()) {
		mx *= -1;
	}

	if (m_iX - m_iR <= 0) {
		mx *= -1;
	}
	
}
// Создание или уничтожение CSDIDoc

CSDIDoc::CSDIDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CSDIDoc::~CSDIDoc()
{
}

BOOL CSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_pTreeView->FillTree();

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	/*m_circ.m_iX = 50 + rand() % 400;
	m_circ.m_iY = 50 + rand() % 400;
	m_circ.m_iR = 25;*/

	for (int i = 0; i < 2 + rand() % 5; i++) {
		CMyCircle tempCircle;
		tempCircle.m_iX = 50 + rand() % 400;
		tempCircle.m_iY = 50 + rand() % 400;
		tempCircle.m_iR = 25;
		m_mycircle.push_back(tempCircle);
		count = i+1;
	}
	


	return TRUE;
}




// Сериализация CSDIDoc

void CSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSDIDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CSDIDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CSDIDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CSDIDoc

#ifdef _DEBUG
void CSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CSDIDoc
