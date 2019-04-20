// NDesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DesCipherTest.h"
#include "DesCipherTestDlg.h"

#include "mydes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE

static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesCipherTestDlg dialog

CDesCipherTestDlg::CDesCipherTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDesCipherTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDesCipherTestDlg)
	m_ciphertext = _T("");
	m_key = _T("wwxxyy");
	m_decrypttext = _T("");
	m_plaintext = _T("wxytest");
	m_chkhex_src = FALSE;
	m_chkhex_des = FALSE;
	m_chkhex_key = FALSE;
	m_chkhex_dedes = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDesCipherTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDesCipherTestDlg)
	DDX_Text(pDX, IDC_EDIT_DES, m_ciphertext);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
	DDX_Text(pDX, IDC_EDIT_RECOVERY, m_decrypttext);
	DDX_Text(pDX, IDC_EDIT_SRC, m_plaintext);
	DDX_Check(pDX, IDC_CHECK1, m_chkhex_src);
	DDX_Check(pDX, IDC_CHECK2, m_chkhex_des);
	DDX_Check(pDX, IDC_CHECK3, m_chkhex_key);
	DDX_Check(pDX, IDC_CHECK4, m_chkhex_dedes);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDesCipherTestDlg, CDialog)
	//{{AFX_MSG_MAP(CDesCipherTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, OnCheckSrc)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckDes)
	ON_BN_CLICKED(IDC_CHECK3, OnCheckKey)
	ON_BN_CLICKED(IDOK2, OnEncryption)
	ON_BN_CLICKED(IDOK3, OnDescryption)

	ON_BN_CLICKED(IDOK4, OnOk4)
	ON_BN_CLICKED(IDOK5, OnOk5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesCipherTestDlg message handlers

BOOL CDesCipherTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDesCipherTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDesCipherTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDesCipherTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



//十六进制串转换为字符串
CString CDesCipherTestDlg::Hex2Chr(CString src)
{
	CString tmp = "";
	char *token = strtok(src.GetBuffer(0), " \n\r");
	while(token != NULL )
	{
		unsigned char ch = 0;
		sscanf(token, "%X", &ch);
		tmp += CString(ch);
		token = strtok( NULL, " \n\r");	
	}
	return tmp;
}

//字符串转换为十六进制串，补够8的整数倍
CString CDesCipherTestDlg::Chr2Hex(CString src)
{
	CString tmp = "";
	for (int i=0; i<src.GetLength(); i++)
	{
		char buffer[20];
		sprintf(buffer, "%02X ", (unsigned char)src.GetAt(i));
		if (i%16==0 && i!=0) tmp += "\r\n";
		else if (i%8==0 && i!=0) tmp += "  ";
		tmp += buffer;
	}
	int n = src.GetLength();
	char addtmp[] = "00 00 00 00 00 00 00 00";
	if (n==0) tmp = addtmp;
	else if (n%8!=0) tmp += addtmp+ n%8*3;
	return tmp;
}

//源数据十六进制检查
void CDesCipherTestDlg::OnCheckSrc() 
{
	UpdateData(TRUE);
	if (m_chkhex_src==TRUE)
		m_plaintext = Chr2Hex(m_plaintext);
	else
		m_plaintext = Hex2Chr(m_plaintext);
	UpdateData(FALSE);
}

//目标数据十六进制检查
void CDesCipherTestDlg::OnCheckDes() 
{
	UpdateData(TRUE);
	if (m_chkhex_des==TRUE)
		m_ciphertext = Chr2Hex(m_ciphertext);
	else
		m_ciphertext = Hex2Chr(m_ciphertext);
	UpdateData(FALSE);
}

//密钥数据十六进制检查
void CDesCipherTestDlg::OnCheckKey() 
{
	UpdateData(TRUE);
	if (m_chkhex_key==TRUE)
		m_key = Chr2Hex(m_key);
	else
		m_key = Hex2Chr(m_key);
	UpdateData(FALSE);
}


//加密-解密
void CDesCipherTestDlg::OnOK() 
{
	UpdateData(TRUE);	
	//m_plaintext是CString类型的明文串
	//m_key是CString类型的密钥串
	//m_ciphertext是CString类型的密文
	//m_decrypttext是CString类型的解密后密文

	//your code begin

	//your code end
	UpdateData(FALSE);	
}


//加密字符串
void CDesCipherTestDlg::OnEncryption() 
{
	UpdateData(TRUE);	

	//m_plaintext是CString类型的明文串
	//m_key是CString类型的密钥串
	//m_ciphertext是CString类型的密文
	//m_decrypttext是CString类型的解密后密文
	//your code begin
	char* str = m_plaintext.GetBuffer(0);
	
	char* key = m_key.GetBuffer(0);
	int len = m_plaintext.GetLength();
	CMyDes* des = new CMyDes(str, len, key, true);

    int l=(len+7)/8*8;

	unsigned char* buffout;
	buffout = (UCHAR* )malloc(l);

	des->DoDes(buffout);
	buffout[l] = '\0';
	m_ciphertext = buffout;

	UpdateData(FALSE);		
}

//解密字符串
void CDesCipherTestDlg::OnDescryption() 
{
	UpdateData(TRUE);	

	//m_plaintext是CString类型的明文串
	//m_key是CString类型的密钥串
	//m_ciphertext是CString类型的密文
	//m_decrypttext是CString类型的解密后密文
	//your code begin
	char* str=m_ciphertext.GetBuffer(0);
	int len =m_ciphertext.GetLength(); 
	char* key = m_key.GetBuffer(0);
	unsigned char* buffout;

	int x = 0;
	int l=(len+7)/8*8;//长度

	CMyDes* des = new CMyDes(str, len, key, false);
	//guanjian
	buffout = (UCHAR*)malloc(l);

	des->DoDes(buffout);
	buffout[l] = '\0';
	m_decrypttext = buffout;

	UpdateData(FALSE);		
}


void CDesCipherTestDlg::OnOk4() //加密文件
{

	CString Filename;//保存路径
	CString Filetitle;//保存文件名
	
	CFileDialog opendlg (TRUE,_T("*"),_T("*.txt"),OFN_OVERWRITEPROMPT, NULL);
	if (opendlg.DoModal()==IDOK)
	{
		Filename=opendlg.GetPathName();
		Filetitle=opendlg.GetFileTitle();
	}

	CString Desroute=Filetitle+".desenc";

	char *filename=(char*)(LPCTSTR)Filename;
	char *filetitle=(char*)(LPCTSTR)Filetitle;
	char *desroute=(char*)(LPCTSTR)Desroute;
	//文件的输入输出变量
	CString strl;
	CStdioFile file,filee;
	
	BOOL flag = file.Open(filename,CFile::modeRead);//文件路径，打开模式

	if(file.ReadString(strl) != FALSE)
	{
		m_plaintext=strl;
		char* str = m_plaintext.GetBuffer(0);
		int len = m_plaintext.GetLength();
		char* key = m_key.GetBuffer(0);

        int l=(len+7)/8*8;//长度

		CMyDes* des = new CMyDes(str, len, key, true);
		unsigned char* buffout;
		buffout = (UCHAR*)malloc(l);
		
		des->DoDes(buffout);
		buffout[l] = '\0';
		m_ciphertext = buffout;

		filee.Open(desroute,CFile::modeCreate|CFile::modeWrite);
		filee.WriteString(m_ciphertext);

		UpdateData(FALSE);
	}
	file.Close();
	filee.Close();//关闭文件
}

void CDesCipherTestDlg::OnOk5() //解密文件
{

	CString Filename;//保存路径
	CString Filetitle;//保存文件名
	
	CFileDialog opendlg (TRUE,_T("*"),_T("*.txt"),OFN_OVERWRITEPROMPT, NULL);

	if (opendlg.DoModal()==IDOK)
	{
		Filename=opendlg.GetPathName();
		Filetitle=opendlg.GetFileTitle();
	}

	CString Desroute=Filetitle+".desdec";
	char *filename=(char*)(LPCTSTR)Filename;
	char *filetitle=(char*)(LPCTSTR)Filetitle;
	char *desroute=(char*)(LPCTSTR)Desroute;
	//文件的输入输出变量
	CString strl;
	CStdioFile file, filee;
	BOOL flag = file.Open(filename,CFile::modeRead);//文件路径，打开模式

	if(file.ReadString(strl) != FALSE)
	{
		m_ciphertext=strl;
		char* str=m_ciphertext.GetBuffer(0);
		int len =m_ciphertext.GetLength(); 
		int l=(len+7)/8*8;
		//长度
		char* key = m_key.GetBuffer(0);
		unsigned char* buffout;

		CMyDes* des = new CMyDes(str, len, key, false);
		buffout = (UCHAR*)malloc(l);
	
		des->DoDes(buffout);
		buffout[l] = '\0';
		m_decrypttext = buffout;

		filee.Open(desroute,CFile::modeCreate|CFile::modeWrite);
		filee.WriteString(m_decrypttext);

		UpdateData(FALSE);
	}
	file.Close();	
	filee.Close();//关闭文件
}

