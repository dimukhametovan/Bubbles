
// SDIView.cpp: реализация класса CSDIView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDI.h"
#endif

#include "SDIDoc.h"
#include "SDIView.h"
#include <math.h>
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIView

IMPLEMENT_DYNCREATE(CSDIView, CView)

BEGIN_MESSAGE_MAP(CSDIView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// Создание или уничтожение CSDIView

CSDIView::CSDIView() noexcept
{
	// TODO: добавьте код создания
	std::srand(time(NULL));

}

CSDIView::~CSDIView()
{
}

BOOL CSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	//SetTimer(0, 1000, NULL);
	return CView::PreCreateWindow(cs);
}

// Рисование CSDIView

void CSDIView::OnDraw(CDC* pDC)
{
	CSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	CRect rect;
	GetClientRect(&rect);

	CPen newPen;
	

	if (pDoc->m_bLine1) 
		newPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	else if (pDoc->m_bLine2)
		newPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	else if (pDoc->m_bLine3)
		newPen.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	else 
		newPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	if (pDoc->m_bColor1)
		newPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	else if (pDoc->m_bColor2)
		newPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	else if (pDoc->m_bColor3)
		newPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	

	CPen* oldPen = pDC->SelectObject(&newPen);
	for (int i = 0; i < pDoc->count; i++) {
		pDoc->m_mycircle[i].Draw(pDC);
	}

	
	/*pDC->MoveTo(0, rect.Height() / 2);
	pDC->LineTo(rect.Width(), rect.Height()/2);
	pDC->MoveTo(0, rect.Height() / 2);
	pDoc->stepx = rect.Width() / 1000;
	for (float a = 0; a <= rect.Width(); a += pDoc->stepx) {
		pDC->LineTo(a* rect.Width() /8, rect.Height() / 2 - sin(a) * rect.Height()/2 );
		pDC->MoveTo(a * rect.Width() /8, rect.Height() / 2 - sin(a)* rect.Height()/2 );
	}*/

	//Invalidate(); //перерисовка окна
}


// Печать CSDIView


void CSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CSDIView

#ifdef _DEBUG
void CSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIDoc* CSDIView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIDoc)));
	return (CSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSDIView


void CSDIView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	SetTimer(0, 100, NULL);
	// TODO: добавьте специализированный код или вызов базового класса
}


void CSDIView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CSDIDoc* pDoc = GetDocument();

	CRect rect;
	GetClientRect(&rect);

	

	for (int i = 0; i < pDoc->count; i++)
	{
		for (int k = i; k < pDoc->count; k++)
		{
			int firstx = pDoc->m_mycircle[i].m_iX;
			int secondx = pDoc->m_mycircle[k].m_iX;
			int firsty = pDoc->m_mycircle[i].m_iY;
			int secondy = pDoc->m_mycircle[k].m_iY;
			if (k != i)
			{
				if (sqrt(pow(abs(firstx - secondx), 2) + pow(abs(firsty - secondy), 2)) <= pDoc->m_mycircle[i].m_iR * 2)
				{
					pDoc->m_mycircle[i].mx *= -1;
					pDoc->m_mycircle[k].mx *= -1;
					pDoc->m_mycircle[i].my *= -1;
					pDoc->m_mycircle[k].my *= -1;
				}
			}

		}
		pDoc->m_mycircle[i].Randomxy(rect);
	}
	Invalidate();//перерисовка true - стирает прошлые данные

	CView::OnTimer(nIDEvent);
}
