
// digital_image_processingDlg.h: 头文件
//

#pragma once


// CdigitalimageprocessingDlg 对话框
class CdigitalimageprocessingDlg : public CDialogEx
{
// 构造
public:
	CdigitalimageprocessingDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIGITAL_IMAGE_PROCESSING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CEdit m_filepath;
	afx_msg void OnEnChangefileEdit1();
	afx_msg void OnBnClickedgrayButton1();
	afx_msg void OnBnClickedhistogramButton2();
	afx_msg void OnBnClickedequalizeButton3();
	afx_msg void OnBnClickedgradButton4();
	afx_msg void OnBnClickedLapalaceshapeButton5();
	afx_msg void OnBnClickedRobertsButton6();
	afx_msg void OnBnClickedSobelButton7();
	afx_msg void OnBnClickedLapalaceedgButton8();
	afx_msg void OnBnClickedCannyButton9();
	afx_msg void OnBnClickedMeanfilterButton10();
	afx_msg void OnBnClickedmedButton11();
	afx_msg void OnBnClickedsidewindownButton12();
	afx_msg void OnBnClickedgaussianButton13();
	afx_msg void OnBnClickedmorphplpgyButton14();
	afx_msg void OnBnClickedaffineButton15();
	afx_msg void OnBnClickedperspectiveButton16();
	afx_msg void OnBnClickedonecamerabutton17();
	afx_msg void OnBnClickedtwocameraButton18();
	afx_msg void OnBnClickedStereosgbmButton19();
	afx_msg void OnBnClickedHlsButton20();
	afx_msg void OnBnClickedroadlineperspectivebutton21();
	afx_msg void OnBnClickedhoughroadlineButton1();
	afx_msg void OnBnClickedfeaurematchButton2();
};
