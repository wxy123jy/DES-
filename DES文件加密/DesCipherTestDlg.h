// NDesDlg.h : header file
//

#if !defined(AFX_NDESDLG_H__3595F8BA_03F5_4FBB_8A71_D3AE25584DB6__INCLUDED_)
#define AFX_NDESDLG_H__3595F8BA_03F5_4FBB_8A71_D3AE25584DB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDesCipherTestDlg dialog

class CDesCipherTestDlg : public CDialog
{
// Construction
public:
	CDesCipherTestDlg(CWnd* pParent = NULL);	// standard constructor
	CString Hex2Chr(CString );
	CString Chr2Hex(CString );
	char* UnicodeToASCII(unsigned char * buf);

// Dialog Data
	//{{AFX_DATA(CDesCipherTestDlg)
	enum { IDD = IDD_NDES_DIALOG };
	CString	m_ciphertext;
	CString	m_key;
	CString	m_decrypttext;
	CString	m_plaintext;
	BOOL	m_chkhex_src;
	BOOL	m_chkhex_des;
	BOOL	m_chkhex_key;
	BOOL	m_chkhex_dedes;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesCipherTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDesCipherTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnCheckSrc();
	afx_msg void OnCheckDes();
	afx_msg void OnCheckKey();
	afx_msg void OnEncryption();
	afx_msg void OnDescryption();
	afx_msg void OnCheck4();
	afx_msg void OnOk4();
	afx_msg void OnOk5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NDESDLG_H__3595F8BA_03F5_4FBB_8A71_D3AE25584DB6__INCLUDED_)
