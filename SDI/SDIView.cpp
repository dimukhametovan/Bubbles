
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

	mx = (2 + rand() % 5)*2; //передвижение по х
	my = (2 + rand() % 5)*2; //передвижение по у

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


	pDoc->m_circ.Draw(pDC);
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
	SetTimer(0, 10, NULL);
	// TODO: добавьте специализированный код или вызов базового класса
}


void CSDIView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CSDIDoc* pDoc = GetDocument();

	CRect rect;
	GetClientRect(&rect);

	pDoc->m_circ.m_iX += mx;
	pDoc->m_circ.m_iY += my;

	if (pDoc->m_circ.m_iY + pDoc->m_circ.m_iR >= rect.Height()) {
		my *= -1;
	}

	if (pDoc->m_circ.m_iY - pDoc->m_circ.m_iR <= 0) {
		my *= -1;
	}

	if (pDoc->m_circ.m_iX + pDoc->m_circ.m_iR >= rect.Width()) {
		mx *= -1;
	}

	if (pDoc->m_circ.m_iX - pDoc->m_circ.m_iR <= 0) {
		mx *= -1;
	}

	
	
	

	Invalidate();//перерисовка true - стирает прошлые данные

	CView::OnTimer(nIDEvent);
}
