
// SDIDoc.h: интерфейс класса CSDIDoc 
//



#pragma once
#include <vector>

class CMyTreeView;

using namespace std;

class CMyCircle
{
public:
	CMyCircle();
	CMyCircle(int x, int y, int r);

	int m_iX, m_iY, m_iR;
	int mx, my;
	void Draw(CDC* pDC);
	void Randomxy(CRect& rect);
	
};

class CSDIDoc : public CDocument
{
protected: // создать только из сериализации
	CSDIDoc() noexcept;
	DECLARE_DYNCREATE(CSDIDoc)

// Атрибуты
public:
	vector <CMyCircle> m_mycircle;
	int count;
	int m_iVerstion;
	CMyCircle m_circ;
	CMyTreeView *m_pTreeView;
	bool m_bLine1, m_bLine2, m_bLine3, m_bColor1, m_bColor2, m_bColor3;
	

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
