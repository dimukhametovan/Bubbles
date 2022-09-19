
// SDIDoc.h: интерфейс класса CSDIDoc 
//


#pragma once

class CMyCircle
{
public:
	CMyCircle();
	CMyCircle(int x, int y, int r);

	int m_iX, m_iY, m_iR;
	void Draw(CDC* pDC);
};

class CSDIDoc : public CDocument
{
protected: // создать только из сериализации
	CSDIDoc() noexcept;
	DECLARE_DYNCREATE(CSDIDoc)

// Атрибуты
public:

	int stepx, stepy;
	int m_iVerstion;
	CMyCircle m_circ;
	

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
