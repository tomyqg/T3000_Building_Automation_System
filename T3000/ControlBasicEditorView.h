#pragma once
#include "CControlBasicEditorCOM.h"
// CNewT3000ProgramEditorDlg dialog

class ControlBasicEditorView : public CDialogEx
{
	DECLARE_DYNAMIC(ControlBasicEditorView)

public:
	ControlBasicEditorView(CWnd* pParent = NULL);   // standard constructor
	virtual ~ControlBasicEditorView();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_CONTROLBASIC_EDITOR_VIEW
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    void SetAllPoints_BACnetDevice();
	CProgramEditor1 m_programeditor;
	virtual BOOL OnInitDialog();
	
};
