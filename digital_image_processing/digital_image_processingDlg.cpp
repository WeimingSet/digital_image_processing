
// digital_image_processingDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "digital_image_processing.h"
#include "digital_image_processingDlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<opencv2/imgcodecs/imgcodecs.hpp>
#include <algorithm>
#include <fstream>
#include <conio.h>
#include "polyfit.h"
using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CdigitalimageprocessingDlg 对话框



CdigitalimageprocessingDlg::CdigitalimageprocessingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIGITAL_IMAGE_PROCESSING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdigitalimageprocessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_file_EDIT1, m_filepath);
}

BEGIN_MESSAGE_MAP(CdigitalimageprocessingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_EN_CHANGE(IDC_file_EDIT1, &CdigitalimageprocessingDlg::OnEnChangefileEdit1)
	
	ON_BN_CLICKED(IDC_gray_BUTTON1, &CdigitalimageprocessingDlg::OnBnClickedgrayButton1)
	ON_BN_CLICKED(IDC_histogram_BUTTON2, &CdigitalimageprocessingDlg::OnBnClickedhistogramButton2)

	ON_BN_CLICKED(IDC_equalize_BUTTON3, &CdigitalimageprocessingDlg::OnBnClickedequalizeButton3)
	ON_BN_CLICKED(IDC_grad_BUTTON4, &CdigitalimageprocessingDlg::OnBnClickedgradButton4)
	ON_BN_CLICKED(IDC_Lapalaceshape_BUTTON5, &CdigitalimageprocessingDlg::OnBnClickedLapalaceshapeButton5)
	ON_BN_CLICKED(IDC_Roberts_BUTTON6, &CdigitalimageprocessingDlg::OnBnClickedRobertsButton6)
	ON_BN_CLICKED(IDC_Sobel_BUTTON7, &CdigitalimageprocessingDlg::OnBnClickedSobelButton7)
	ON_BN_CLICKED(IDC_Lapalaceedg_BUTTON8, &CdigitalimageprocessingDlg::OnBnClickedLapalaceedgButton8)
	ON_BN_CLICKED(IDC_Canny_BUTTON9, &CdigitalimageprocessingDlg::OnBnClickedCannyButton9)
	ON_BN_CLICKED(IDC_Meanfilter_BUTTON10, &CdigitalimageprocessingDlg::OnBnClickedMeanfilterButton10)
	ON_BN_CLICKED(IDC_med_BUTTON11, &CdigitalimageprocessingDlg::OnBnClickedmedButton11)
	ON_BN_CLICKED(IDC_sidewindown_BUTTON12, &CdigitalimageprocessingDlg::OnBnClickedsidewindownButton12)
	ON_BN_CLICKED(IDC_gaussian_BUTTON13, &CdigitalimageprocessingDlg::OnBnClickedgaussianButton13)
	ON_BN_CLICKED(IDC_morphplpgy_BUTTON14, &CdigitalimageprocessingDlg::OnBnClickedmorphplpgyButton14)
	ON_BN_CLICKED(IDC_affine_BUTTON15, &CdigitalimageprocessingDlg::OnBnClickedaffineButton15)
	ON_BN_CLICKED(IDC_perspective_BUTTON16, &CdigitalimageprocessingDlg::OnBnClickedperspectiveButton16)
	ON_BN_CLICKED(IDC_onecameraBUTTON17, &CdigitalimageprocessingDlg::OnBnClickedonecamerabutton17)
	ON_BN_CLICKED(IDC_twocamera_BUTTON18, &CdigitalimageprocessingDlg::OnBnClickedtwocameraButton18)
	ON_BN_CLICKED(IDC_StereoSGBM_BUTTON19, &CdigitalimageprocessingDlg::OnBnClickedStereosgbmButton19)
	ON_BN_CLICKED(IDC_HLS_BUTTON20, &CdigitalimageprocessingDlg::OnBnClickedHlsButton20)
	ON_BN_CLICKED(IDC_roadlineperspectiveBUTTON21, &CdigitalimageprocessingDlg::OnBnClickedroadlineperspectivebutton21)
	ON_BN_CLICKED(IDC_houghroadline_BUTTON1, &CdigitalimageprocessingDlg::OnBnClickedhoughroadlineButton1)
	ON_BN_CLICKED(IDC_feaurematch_BUTTON2, &CdigitalimageprocessingDlg::OnBnClickedfeaurematchButton2)
END_MESSAGE_MAP()


// CdigitalimageprocessingDlg 消息处理程序

BOOL CdigitalimageprocessingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	// TODO: 在此添加额外的初始化代码
	DragAcceptFiles(TRUE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdigitalimageprocessingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CdigitalimageprocessingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CdigitalimageprocessingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CdigitalimageprocessingDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TCHAR szPath[MAX_PATH] = { 0 };
	DragQueryFile(hDropInfo, 0, szPath, MAX_PATH); //获取文件路径
	//显示到控件上
	m_filepath.SetWindowText(szPath);
	UpdateData(TRUE); //释放资源
	CDialogEx::OnDropFiles(hDropInfo);
}


void CdigitalimageprocessingDlg::OnEnChangefileEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}




void CdigitalimageprocessingDlg::OnBnClickedgrayButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	 // 获取编辑框中的文件路径
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);

	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) =grayValue;
		}
	}
	// 显示和保存结果
	imshow("灰度图", grayImage);
	imwrite("D:\\First-year graduate\\图像处理技术\\第二周课件与作业\\灰度图.jpg", grayImage);

	waitKey(0);
	
}


void CdigitalimageprocessingDlg::OnBnClickedhistogramButton2()
{
	// TODO: 在此添加控件通知处理程序代码
		 // 获取编辑框中的文件路径
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);

	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}

	// 初始化直方图数组为0
	int histogram[256] = { 0 };
	int sumpixel[256] = { 0 };
	// 遍历每个像素，统计灰度值
	for (int i = 0; i < grayImage.rows; i++) {
		for (int j = 0; j < grayImage.cols; j++) {
			uchar grayValue = grayImage.at<uchar>(i, j); // 获取灰度值
			histogram[grayValue]++; // 统计灰度值的出现频率
		}
	}
	// 计算直方图中的最大值
	int maxValue = *std::max_element(histogram, histogram + 256);

	// 创建一个黑色背景的图像用来绘制直方图
	int histHeight = 279;  // 直方图显示的高度
	int histWidth = 344;   // 直方图显示的宽度
	int binWidth = cvRound((double)histWidth / 256);  // 每个柱的宽度
	Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));

	// 归一化：将灰度值频率映射到直方图高度
	for (int i = 0; i < 256; i++) {
		histogram[i] = cvRound((double)histogram[i] / maxValue * histHeight);
	}

	// 绘制直方图柱形，使用矩形填充每个柱子
	for (int i = 0; i < 256; i++) {
		rectangle(histImage,
			Point(i * binWidth, histHeight - histogram[i]),  // 左上角
			Point((i + 1) * binWidth - 1, histHeight),      // 右下角
			Scalar(255, 255, 255),  // 白色
			-1); // 填充矩形
	}
	// 显示灰度图像和灰度直方图
	imshow("Gray Image", grayImage);   // 显示灰度图像
	imshow("灰度直方图", histImage);    // 显示灰度直方图

}



void CdigitalimageprocessingDlg::OnBnClickedequalizeButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat equalizedImage;
	equalizeHist(grayImage, equalizedImage);
	// 初始化直方图数组为0
	int histogram[256] = { 0 };
	int equalizehist[256] = { 0 };
	int sumpixel[256] = { 0 };
	// 遍历每个像素，统计灰度值
	for (int i = 0; i < grayImage.rows; i++) {
		for (int j = 0; j < grayImage.cols; j++) {
			uchar grayValue = grayImage.at<uchar>(i, j); // 获取灰度值
			histogram[grayValue]++; // 统计灰度值的出现频率
		}
	}
	for (int i = 0; i < equalizedImage.rows; i++) {
		for (int j = 0; j < equalizedImage.cols; j++) {
			uchar  equalizeValue = equalizedImage.at<uchar>(i, j); // 获取灰度值
			equalizehist[equalizeValue]++; // 统计灰度值的出现频率
		}
	}
	// 计算直方图中的最大值
	int maxValue = *std::max_element(histogram, histogram + 256);
	int maxequalizeValue = *std::max_element(equalizehist, equalizehist + 256);
	// 创建一个黑色背景的图像用来绘制直方图
	int histHeight = 279;  // 直方图显示的高度
	int histWidth = 344;   // 直方图显示的宽度
	int binWidth = cvRound((double)histWidth / 256);  // 每个柱的宽度
	Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));
	Mat equalizedhistImage(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));
	// 归一化：将灰度值频率映射到直方图高度
	for (int i = 0; i < 256; i++) {
		histogram[i] = cvRound((double)histogram[i] / maxValue * histHeight);
	}
	for (int i = 0; i < 256; i++) {
		equalizehist[i] = cvRound((double)equalizehist[i] / maxequalizeValue * histHeight);
	}
	// 绘制直方图柱形，使用矩形填充每个柱子
	for (int i = 0; i < 256; i++) {
		rectangle(histImage,
			Point(i * binWidth, histHeight - histogram[i]),  // 左上角
			Point((i + 1) * binWidth - 1, histHeight),      // 右下角
			Scalar(255, 255, 255),  // 白色
			-1); // 填充矩形
	}
	for (int i = 0; i < 256; i++) {
		rectangle(equalizedhistImage,
			Point(i * binWidth, histHeight - equalizehist[i]),  // 左上角
			Point((i + 1) * binWidth - 1, histHeight),      // 右下角
			Scalar(255, 255, 255),  // 白色
			-1); // 填充矩形
	}
	// 显示灰度图像和灰度直方图
	imshow("灰度图", grayImage);   // 显示灰度图像
	imshow("灰度直方图", histImage);    // 显示灰度直方图
	imshow("均衡化", equalizedImage);   // 显示图像
	imshow("灰度直方图均衡化", equalizedhistImage);    // 显示灰度直方图
	imwrite("D:\\First-year graduate\\图像处理技术\\第二周课件与作业\\图片\\灰度直方图.jpg", histImage);
	imwrite("D:\\First-year graduate\\图像处理技术\\第二周课件与作业\\图片\\均衡化.jpg", equalizedImage);
	imwrite("D:\\First-year graduate\\图像处理技术\\第二周课件与作业\\图片\\灰度直方图均衡化.jpg", equalizedhistImage);
	waitKey(0);
}


void CdigitalimageprocessingDlg::OnBnClickedgradButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat gladimage = Mat::zeros(grayImage.size(), CV_8UC1); // 梯度图像
	Mat gladshape = Mat::zeros(grayImage.size(), CV_8UC1); // 梯度锐化图像

	for (int i = 0; i < grayImage.rows - 1; i++)
	{
		for (int j = 0; j < grayImage.cols - 1; j++)
		{
			gladimage.at<uchar>(i, j) = saturate_cast<uchar>(abs(grayImage.at<uchar>(i + 1, j)- grayImage.at<uchar>(i, j))
				+ abs(grayImage.at<uchar>(i, j + 1)- grayImage.at<uchar>(i, j)));
		}
	}
	for (int i = 0; i < gladimage.rows; i++)
	{
		for (int j = 0; j < gladimage.cols; j++)
		{
			gladshape.at<uchar>(i, j)= grayImage.at<uchar>(i, j)+ gladimage.at<uchar>(i, j);
		}
	}

	imshow("梯度算子", gladimage);
	imshow("梯度锐化", gladshape);
	imwrite("D:\\First-year graduate\\图像处理技术\\第二周课件与作业\\图片\\梯度算子.jpg", gladimage);
	imwrite("D:\\First-year graduate\\图像处理技术\\第二周课件与作业\\图片\\梯度锐化.jpg", gladshape);

}


void CdigitalimageprocessingDlg::OnBnClickedLapalaceshapeButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat Laplacegrayimg1 = Mat::zeros(grayImage.size(), CV_8UC1); // 梯度图像
	Mat Laplacegrayimg2 = Mat::zeros(grayImage.size(), CV_8UC1); // 梯度锐化图像


	for (int i = 1; i < grayImage.rows - 1; i++)
	{
		for (int j = 1; j < grayImage.cols - 1; j++)
		{
			int laplaceValue =
				-4 * grayImage.at<uchar>(i, j) +
				grayImage.at<uchar>(i + 1, j) +
				grayImage.at<uchar>(i - 1, j) +
				grayImage.at<uchar>(i, j + 1) +
				grayImage.at<uchar>(i, j - 1);

			// 限制范围在 [-128, 127]
			Laplacegrayimg1.at<char>(i, j) = saturate_cast<char>(laplaceValue);
		}
	}

	// ---- 计算锐化图像 ----
	for (int i = 0; i < grayImage.rows; i++)
	{
		for (int j = 0; j < grayImage.cols; j++)
		{
			int sharpenValue = grayImage.at<uchar>(i, j) + Laplacegrayimg1.at<char>(i, j);

			// 限制范围在 [0, 255]
			Laplacegrayimg2.at<uchar>(i, j) = saturate_cast<uchar>(sharpenValue);
		}
	}

	imshow("Laplace算子", Laplacegrayimg1);
	imshow("Laplace锐化", Laplacegrayimg2);
	imwrite("D:\\First-year graduate\\图像处理技术\\第二周课件与作业\\图片\\Laplace算子.jpg", Laplacegrayimg1);
	imwrite("D:\\First-year graduate\\图像处理技术\\第二周课件与作业\\图片\\Laplace锐化.jpg", Laplacegrayimg2);

}


void CdigitalimageprocessingDlg::OnBnClickedRobertsButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat robertsimg = Mat::zeros(grayImage.size(), CV_8UC1);



	for (int i = 0; i < grayImage.rows - 1; i++)
		for (int j = 0; j < grayImage.cols - 1; j++)
		{

			int t1 = (grayImage.at<uchar>(i, j) - grayImage.at<uchar>(i + 1, j + 1)) * (grayImage.at<uchar>(i, j) - grayImage.at<uchar>(i + 1, j + 1));
			int t2 = (grayImage.at<uchar>(i + 1, j) - grayImage.at<uchar>(i, j + 1)) * (grayImage.at<uchar>(i + 1, j) - grayImage.at<uchar>(i, j + 1));

			robertsimg.at<uchar>(i, j) = (uchar)sqrt(t1 + t2);
		}

	imshow("roberts边缘检测", robertsimg);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\roberts边缘检测.jpg", robertsimg);
}


void CdigitalimageprocessingDlg::OnBnClickedSobelButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat sobelimg = Mat::zeros(grayImage.size(), CV_8UC1);
	for (int i = 1; i < grayImage.rows - 1; i++)
		for (int j = 1; j < grayImage.cols - 1; j++)
		{

			int t1 = (grayImage.at<uchar>(i + 1, j - 1) + 2 * grayImage.at<uchar>(i + 1, j) 
				+ grayImage.at<uchar>(i + 1, j + 1) - grayImage.at<uchar>(i - 1, j - 1) - 2 * grayImage.at<uchar>(i - 1, j) 
				- grayImage.at<uchar>(i - 1, j + 1)) * (grayImage.at<uchar>(i + 1, j - 1) + 2 * grayImage.at<uchar>(i + 1, j) 
					+ grayImage.at<uchar>(i + 1, j + 1) - grayImage.at<uchar>(i - 1, j - 1) - 2 * grayImage.at<uchar>(i - 1, j) 
					- grayImage.at<uchar>(i - 1, j + 1));


			int t2 = (grayImage.at<uchar>(i - 1, j + 1) + 2 * grayImage.at<uchar>(i, j + 1) 
				+ grayImage.at<uchar>(i + 1, j + 1) - grayImage.at<uchar>(i - 1, j - 1) 
				- 2 * grayImage.at<uchar>(i, j - 1) - grayImage.at<uchar>(i + 1, j - 1)) * (grayImage.at<uchar>(i - 1, j + 1) 
					+ 2 * grayImage.at<uchar>(i, j + 1) + grayImage.at<uchar>(i + 1, j + 1) - grayImage.at<uchar>(i - 1, j - 1) 
					- 2 * grayImage.at<uchar>(i, j - 1) - grayImage.at<uchar>(i + 1, j - 1));
			sobelimg.at<uchar>(i, j) = saturate_cast<uchar>(sqrt(t1 + t2));
		}
	imshow("sobel边缘检测", sobelimg);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\Sobel边缘检测.jpg", sobelimg);
}


void CdigitalimageprocessingDlg::OnBnClickedLapalaceedgButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat Laplaceimg = Mat::zeros(grayImage.size(), CV_8UC1);

	for (int i = 1; i < grayImage.rows - 1; i++)
		for (int j = 1; j < grayImage.cols - 1; j++)
		{

			int t1 = grayImage.at<uchar>(i, j - 1) + grayImage.at<uchar>(i + 1, j) 
				+ grayImage.at<uchar>(i - 1, j) + grayImage.at<uchar>(i, j + 1) 
				- 4 * grayImage.at<uchar>(i, j);



			Laplaceimg.at<uchar>(i, j) = saturate_cast<uchar>(t1);
		}

	imshow("Laplace边缘检测", Laplaceimg);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\Laplace边缘检测图.jpg", Laplaceimg);
}

void myCanny(const cv::Mat& src, cv::Mat& edges, int upperThresh, int lowerThresh);
void followEdges(int x, int y, const cv::Mat& magnitude, int tUpper, int tLower, cv::Mat& edges);
void MyedgeDetect(const cv::Mat& magnitude, int tUpper, int tLower, cv::Mat& edges);
void nonMaximumSuppression(cv::Mat& magnitudeImage, const cv::Mat& directionImage);
void myCanny(const cv::Mat& src, cv::Mat& edges, int upperThresh, int lowerThresh)
{

	//Step1. 高斯滤波 Remove noise (apply gaussian)
	cv::Mat image;
	cv::GaussianBlur(src, image, cv::Size(3, 3), 1.5);


	//Step2. 使用sobel计算相应的梯度幅值及方向. Calculate gradient (apply sobel operator)
	cv::Mat magX, magY;//X,Y方向的梯度
	cv::Sobel(image, magX, CV_32FC1, 1, 0, 3);
	cv::Sobel(image, magY, CV_32FC1, 0, 1, 3);
	cv::Mat Mag, Ori;//梯度幅值,幅角
	cv::cartToPolar(magX, magY, Mag, Ori, true);//幅角0~360


	//Step3.Non-maximum supression 非极大值抑制
												// For each pixel find two neighbors (in the positive and negative gradient directions,
												// supposing that each neighbor occupies the angle of π/4 , and 0i s the direction straight to the right).
												// If the magnitude of the current pixel is greater than the magnitudes of the neighbors, nothing changes,
												// otherwise, the magnitude of the current pixel is set to zero.
	nonMaximumSuppression(Mag, Ori);

	//Step4. 双阈值检测和边缘连接 Double thresholding
	MyedgeDetect(Mag, upperThresh, lowerThresh, edges);

	imshow("Canny边缘检测", edges);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\Canny边缘检测图.jpg", edges);
	waitKey(0);
}


void followEdges(int x, int y, const cv::Mat& magnitude, int tUpper, int tLower, cv::Mat& edges)
{

	edges.at<uchar>(y, x) = 255;//该点与强边缘点邻接,故确定其为边缘点
	for (int i = -1; i < 2; i++)//8邻域: (i,j) ∈ [-1 0 1].一共8个点,因此要去掉自身
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)//去除自身点
				continue;

			// 边界限制
			if ((x + i >= 0) && (y + j >= 0) &&
				(x + i < magnitude.cols) && (y + j < magnitude.rows))
			{
				// 梯度幅值边缘判断及连接
				if ((magnitude.at<float>(y + j, x + i) > tLower)
					&& (edges.at<uchar>(y + j, x + i) != 255))//大于低阈值,且该点尚未被确定为边缘点
				{
					followEdges(x + i, y + j, magnitude, tUpper, tLower, edges);
				}
			}
		}
	}
}

void MyedgeDetect(const cv::Mat& magnitude, int tUpper, int tLower, cv::Mat& edges)
{

	int rows = magnitude.rows;
	int cols = magnitude.cols;
	edges = cv::Mat(magnitude.size(), CV_8UC1, cv::Scalar(0));

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			// 梯度幅值判断.//大于高阈值，为确定边缘点
			if (magnitude.at<float>(y, x) >= tUpper)
			{
				followEdges(x, y, magnitude, tUpper, tLower, edges);
			}
		}
	}
}

void nonMaximumSuppression(cv::Mat& magnitudeImage, const cv::Mat& directionImage)
{

	cv::Mat edgeMag_noMaxsup = cv::Mat::zeros(magnitudeImage.size(), CV_32FC1);


	//根据输入的角度,判断该点梯度方向位于哪个区间
	//[0,45,90,135]
	auto _judgeDir = [](float angle)->int {

		if ((0 <= angle && angle < 22.5) || (157.5 <= angle && angle < 202.5) || (337.5 <= angle && angle < 360))//梯度方向为水平方向
			return 0;
		else if ((22.5 <= angle && angle < 67.5) || (202.5 <= angle && angle < 247.5))//45°方向
			return 45;
		else if ((67.5 <= angle && angle < 112.5) || ((247.5 <= angle && angle < 292.5)))
			return 90;
		else /*if( (112.5<=angle&&angle<157.5) || ((292.5<=angle&&angle<337.5)) )*/
			return 135;
		};

	for (int r = 1; r < magnitudeImage.rows - 1; ++r)
	{
		for (int c = 1; c < magnitudeImage.cols - 1; ++c)
		{
			const float mag = magnitudeImage.at<float>(r, c);//当前位置梯度幅值

			//将其量化到4个方向中进行计算
			const float angle = directionImage.at<float>(r, c);
			const int nDir = _judgeDir(angle);


			//非极大值抑制,8邻域的点进行比较,但只比较梯度方向
			//或者采用线性插值的方式,在亚像素层面进行比较
			//由于图像的y轴向下,x轴向右,因此注意这里的45°和135°
			switch (nDir)
			{
			case 0://梯度方向为水平方向-邻域内左右比较
			{
				float left = magnitudeImage.at<float>(r, c - 1);
				float right = magnitudeImage.at<float>(r, c + 1);
				if (mag > left && mag >= right)
					edgeMag_noMaxsup.at<float>(r, c) = mag;

				break;
			}
			case 135://即我们平常认为的45°.邻域内右上 左下比较.
			{
				float right_top = magnitudeImage.at<float>(r - 1, c + 1);
				float left_down = magnitudeImage.at<float>(r + 1, c - 1);
				if (mag > right_top && mag >= left_down)
					edgeMag_noMaxsup.at<float>(r, c) = mag;

				break;
			}
			case 90://梯度方向为垂直方向-邻域内上下比较
			{
				float top = magnitudeImage.at<float>(r - 1, c);
				float down = magnitudeImage.at<float>(r + 1, c);
				if (mag > top && mag >= down)
					edgeMag_noMaxsup.at<float>(r, c) = mag;

				break;
			}
			case 45://邻域内右下 左上比较
			{
				float left_top = magnitudeImage.at<float>(r - 1, c - 1);
				float right_down = magnitudeImage.at<float>(r + 1, c + 1);
				if (mag > left_top && mag >= right_down)
					edgeMag_noMaxsup.at<float>(r, c) = mag;

				break;
			}
			default:
				break;
			}//switch
		}//for col
	}//for row

	edgeMag_noMaxsup.copyTo(magnitudeImage);
}

void CdigitalimageprocessingDlg::OnBnClickedCannyButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);
	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat  edges = Mat::zeros(grayImage.size(), CV_8UC1);
	
	myCanny(grayImage, edges, 60, 30);
}

double generateGaussianNoise(double mu, double sigma);
Mat addGaussianNoise(Mat& srcImag);
Mat addSaltNoise(const Mat srcImage, int n);
//生成高斯噪声
double generateGaussianNoise(double mu, double sigma)
{
	//定义小值
	const double epsilon = numeric_limits<double>::min();
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flag为假构造高斯随机变量X
	if (!flag)
		return z1 * sigma + mu;
	double u1, u2;
	//构造随机变量
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flag为真构造高斯随机变量
	z0 = sqrt(-2.0 * log(u1)) * cos(2 * CV_PI * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(2 * CV_PI * u2);
	return z0 * sigma + mu;
}

//为图像添加高斯噪声
Mat addGaussianNoise(Mat& srcImag)
{
	Mat dstImage = srcImag.clone();
	for (int i = 0; i < dstImage.rows; i++)
	{
		for (int j = 0; j < dstImage.cols; j++)
		{
			//添加高斯噪声
			dstImage.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(dstImage.at<Vec3b>(i, j)[0] + generateGaussianNoise(2, 0.8) * 32);
			dstImage.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(dstImage.at<Vec3b>(i, j)[1] + generateGaussianNoise(2, 0.8) * 32);
			dstImage.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(dstImage.at<Vec3b>(i, j)[2] + generateGaussianNoise(2, 0.8) * 32);
		}
	}
	return dstImage;
}



Mat addSaltNoise(const Mat srcImage, int n)
{
	Mat dstImage = srcImage.clone();
	for (int k = 0; k < n; k++)
	{
		//随机取值行列
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 255;		//盐噪声
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 255;
			dstImage.at<Vec3b>(i, j)[1] = 255;
			dstImage.at<Vec3b>(i, j)[2] = 255;
		}
	}
	for (int k = 0; k < n; k++)
	{
		//随机取值行列
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 0;		//椒噪声
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 0;
			dstImage.at<Vec3b>(i, j)[1] = 0;
			dstImage.at<Vec3b>(i, j)[2] = 0;
		}
	}
	return dstImage;
}
void CdigitalimageprocessingDlg::OnBnClickedMeanfilterButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);
	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat  GaussianNoise = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat SaltNoise = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat blurimg = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat blurimg1 = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat blurimg2 = Mat::zeros(colorImage.size(), CV_8UC3);
	generateGaussianNoise(0.1, 0.1);
	GaussianNoise = addGaussianNoise(colorImage);
	imshow("原图加高斯噪声", GaussianNoise);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图加高斯噪声.jpg", GaussianNoise);

	SaltNoise = addSaltNoise(colorImage, 1000);
	imshow("原图加椒盐噪声", SaltNoise);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图加椒盐噪声.jpg", SaltNoise);

	blur(colorImage, blurimg, Size(5, 5));
	imshow("原图进行均值滤波", blurimg);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图进行均值滤波.jpg", blurimg);

	blur(GaussianNoise, blurimg1, Size(5, 5));
	imshow("高斯噪声图进行均值滤波", blurimg1);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\高斯噪声图进行均值滤波.jpg", blurimg1);

	blur(SaltNoise, blurimg2, Size(5, 5));
	imshow("椒盐噪声图进行均值滤波", blurimg2);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\椒盐噪声图进行均值滤波.jpg", blurimg2);
}


void CdigitalimageprocessingDlg::OnBnClickedmedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);
	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat  GaussianNoise = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat SaltNoise = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat blurimg = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat blurimg1 = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat blurimg2 = Mat::zeros(colorImage.size(), CV_8UC3);
	generateGaussianNoise(0.1, 0.1);
	GaussianNoise = addGaussianNoise(colorImage);
	imshow("原图加高斯噪声", GaussianNoise);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图加高斯噪声.jpg", GaussianNoise);

	SaltNoise = addSaltNoise(colorImage, 1000);
	imshow("原图加椒盐噪声", SaltNoise);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图加椒盐噪声.jpg", SaltNoise);

	medianBlur(colorImage, blurimg, 5);
	imshow("原图进行中值滤波", blurimg);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图进行中值滤波.jpg", blurimg);

	medianBlur(GaussianNoise, blurimg1,  5);
	imshow("高斯噪声图进行中值滤波", blurimg1);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\高斯噪声图进行中值滤波.jpg", blurimg1);

	medianBlur(SaltNoise, blurimg2, 5);
	imshow("椒盐噪声图进行中值滤波", blurimg2);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\椒盐噪声图进行中值滤波.jpg", blurimg2);
}

void slidewindow(Mat src, Mat& dst, int winsize);

void slidewindow(Mat src, Mat& dst, int winsize)
{

	Mat src_board; double I_up = 1, I_down = 1, I_L = 1, I_R = 1, I_LU = 1, I_LD = 1, I_RU = 1, I_RD = 1;
	int dst_tmp_up = 1;
	int dst_tmp_down = 1;
	int dst_tmp_L = 1;
	int dst_tmp_R = 1;
	int dst_tmp_LU = 1;
	int dst_tmp_LD = 1;
	int dst_tmp_RU = 1;
	int dst_tmp_RD = 1;

	//调用Opencv的copyMakeBorder函数扩充边界
	copyMakeBorder(src, src_board, 1, 1, 1, 1, BORDER_REFLECT);

	const int row = src_board.rows;   //行
	const int col = src_board.cols;
	Mat dst_tmp_img(src.size(), CV_8UC1);   //列
	for (int i = 1; i < row - 1; i++)  //行循环，只计算图像的原有行
	{
		for (int j = 1; j < col - 1; j++)  //列循环，只计算图像的原有列
		{

			//计算每一个像素点周围矩形区域内所有像素点的累加和

			int sum1 = src_board.ptr<uchar>(i - 1)[j - 1] + src_board.ptr<uchar>(i - 1)[j] + src_board.ptr<uchar>(i - 1)[j + 1] + src_board.ptr<uchar>(i)[j - 1] + src_board.ptr<uchar>(i)[j] + src_board.ptr<uchar>(i)[j + 1];


			//求得累加和之后再求窗口像素的平均值。作为当前像素点的滤波值
			dst_tmp_up = (uchar)(sum1 / 6);
			I_up = (src.ptr<uchar>(i - 1)[j - 1] - dst_tmp_up) ^ 2;


			int sum2 = src_board.ptr<uchar>(i)[j - 1] + src_board.ptr<uchar>(i)[j] + src_board.ptr<uchar>(i)[j + 1] + src_board.ptr<uchar>(i + 1)[j - 1] + src_board.ptr<uchar>(i + 1)[j] + src_board.ptr<uchar>(i + 1)[j + 1];


			//求得累加和之后再求窗口像素的平均值。作为当前像素点的滤波值
			dst_tmp_down = (uchar)(sum2 / 6);
			I_down = (src.ptr<uchar>(i - 1)[j - 1] - dst_tmp_down) ^ 2;


			int sum3 = src_board.ptr<uchar>(i - 1)[j] + src_board.ptr<uchar>(i)[j] + src_board.ptr<uchar>(i + 1)[j] + src_board.ptr<uchar>(i)[j - 1] + src_board.ptr<uchar>(i + 1)[j - 1] + src_board.ptr<uchar>(i - 1)[j - 1];


			//求得累加和之后再求窗口像素的平均值。作为当前像素点的滤波值
			dst_tmp_L = (uchar)(sum3 / 6);
			I_L = (src.ptr<uchar>(i - 1)[j - 1] - dst_tmp_L) ^ 2;


			int sum4 = src_board.ptr<uchar>(i - 1)[j] + src_board.ptr<uchar>(i)[j] + src_board.ptr<uchar>(i + 1)[j] + src_board.ptr<uchar>(i - 1)[j + 1] + src_board.ptr<uchar>(i)[j + 1] + src_board.ptr<uchar>(i + 1)[j + 1];


			//求得累加和之后再求窗口像素的平均值。作为当前像素点的滤波值
			dst_tmp_R = (uchar)(sum4 / 6);
			I_R = (src.ptr<uchar>(i - 1)[j - 1] - dst_tmp_R) ^ 2;


			int sum5 = src_board.ptr<uchar>(i - 1)[j - 1] + src_board.ptr<uchar>(i - 1)[j] + src_board.ptr<uchar>(i)[j - 1] + src_board.ptr<uchar>(i)[j];


			//求得累加和之后再求窗口像素的平均值。作为当前像素点的滤波值
			dst_tmp_LU = (uchar)(sum5 / 4);
			I_LU = (src.ptr<uchar>(i - 1)[j - 1] - dst_tmp_LU) ^ 2;


			int sum6 = src_board.ptr<uchar>(i - 1)[j + 1] + src_board.ptr<uchar>(i - 1)[j] + src_board.ptr<uchar>(i)[j] + src_board.ptr<uchar>(i)[j + 1];


			//求得累加和之后再求窗口像素的平均值。作为当前像素点的滤波值
			dst_tmp_RU = (uchar)(sum6 / 4);
			I_RU = (src.ptr<uchar>(i - 1)[j - 1] - dst_tmp_RU) ^ 2;


			int sum7 = src_board.ptr<uchar>(i + 1)[j - 1] + src_board.ptr<uchar>(i + 1)[j] + src_board.ptr<uchar>(i)[j] + src_board.ptr<uchar>(i)[j - 1];


			//求得累加和之后再求窗口像素的平均值。作为当前像素点的滤波值
			dst_tmp_LD = (uchar)(sum7 / 4);
			I_LD = (src.ptr<uchar>(i - 1)[j - 1] - dst_tmp_LD) ^ 2;

			int sum8 = src_board.ptr<uchar>(i + 1)[j + 1] + src_board.ptr<uchar>(i + 1)[j] + src_board.ptr<uchar>(i)[j] + src_board.ptr<uchar>(i)[j + 1];


			//求得累加和之后再求窗口像素的平均值。作为当前像素点的滤波值
			dst_tmp_RD = (uchar)(sum8 / 4);
			I_RD = (src.ptr<uchar>(i - 1)[j - 1] - dst_tmp_RD) ^ 2;

			double I[8] = { I_up, I_down, I_L, I_R, I_LU, I_LD, I_RU, I_RD };
			int dst_tmp[8] = { dst_tmp_up, dst_tmp_down, dst_tmp_L, dst_tmp_R, dst_tmp_LU, dst_tmp_LD, dst_tmp_RU, dst_tmp_RD };
			double I_min = *min_element(I, I + 8);
			int dst_tmp_min = dst_tmp[0];
			for (int a = 0; a < 8; a++)
			{

				if (I[a] <= I_min)
				{
					dst_tmp_min = dst_tmp[a];
				}


			}
			dst_tmp_img.ptr<uchar>(i - 1)[j - 1] = dst_tmp_min;
		}
	}

	dst_tmp_img.copyTo(dst);

}
void CdigitalimageprocessingDlg::OnBnClickedsidewindownButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat slidewindowdst = Mat::zeros(grayImage.size(), CV_8UC1);
	vector<Mat> channels(3), filteredChannels(3);
	split(colorImage, channels);
	for (int i = 0; i < 3; ++i) {
		slidewindow(channels[i], filteredChannels[i], 3);
	}
	merge(filteredChannels, slidewindowdst);
	imshow("边窗滤波", slidewindowdst);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\均值边窗滤波.jpg", slidewindowdst);
	Mat  GaussianNoise = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat SaltNoise = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat slidewindowdst1 = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat slidewindowdst2 = Mat::zeros(colorImage.size(), CV_8UC3);
	generateGaussianNoise(0.1, 0.1);
	GaussianNoise = addGaussianNoise(colorImage);
	imshow("原图加高斯噪声", GaussianNoise);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图加高斯噪声.jpg", GaussianNoise);

	SaltNoise = addSaltNoise(colorImage, 1000);
	imshow("原图加椒盐噪声", SaltNoise);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图加椒盐噪声.jpg", SaltNoise);

	vector<Mat> channels1(3), filteredChannels1(3);
	split(GaussianNoise, channels1);
	for (int i = 0; i < 3; ++i) {
		slidewindow(channels1[i], filteredChannels1[i], 3);
	}
	merge(filteredChannels1, slidewindowdst1);
	imshow("高斯噪声图进行中值滤波", slidewindowdst1);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\高斯噪声图进行边窗滤波.jpg", slidewindowdst1);

	vector<Mat> channels2(3), filteredChannels2(3);
	split(SaltNoise, channels2);
	for (int i = 0; i < 3; ++i) {
		slidewindow(channels2[i], filteredChannels2[i], 3);
	}
	merge(filteredChannels2, slidewindowdst2);
	medianBlur(SaltNoise, slidewindowdst2, 5);
	imshow("椒盐噪声图进行中值滤波", slidewindowdst2);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\椒盐噪声图进行边窗滤波.jpg", slidewindowdst2);
}


void CdigitalimageprocessingDlg::OnBnClickedgaussianButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat gaussianblur = Mat::zeros(grayImage.size(), CV_8UC3);
	Mat gaussianblur1 = Mat::zeros(grayImage.size(), CV_8UC3);
	Mat gaussianblur2 = Mat::zeros(grayImage.size(), CV_8UC3);
	Mat  GaussianNoise = Mat::zeros(colorImage.size(), CV_8UC3);
	Mat SaltNoise = Mat::zeros(colorImage.size(), CV_8UC3);

	generateGaussianNoise(0.1, 0.1);
	GaussianNoise = addGaussianNoise(colorImage);
	imshow("原图加高斯噪声", GaussianNoise);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图加高斯噪声.jpg", GaussianNoise);

	SaltNoise = addSaltNoise(colorImage, 1000);
	imshow("原图加椒盐噪声", SaltNoise);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图加椒盐噪声.jpg", SaltNoise);
	GaussianBlur(colorImage, gaussianblur, Size(3, 3), 0.8, 0);
	imshow("原图进行高斯模板滤波", gaussianblur);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\原图进行高斯模板滤波.jpg", gaussianblur);

	GaussianBlur(GaussianNoise, gaussianblur1, Size(3, 3), 0.8, 0);
	imshow("高斯噪声图进行高斯模板滤波", gaussianblur1);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\高斯噪声图进行高斯模板滤波.jpg", gaussianblur1);

	GaussianBlur(SaltNoise, gaussianblur2, Size(3, 3), 0.8, 0);
	imshow("椒盐噪声图进行高斯模板滤波", gaussianblur2);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\椒盐噪声图进行高斯模板滤波.jpg", gaussianblur2);

}


void CdigitalimageprocessingDlg::OnBnClickedmorphplpgyButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Mat dst, corro, expand;
	Mat kernel;
	kernel = getStructuringElement(MORPH_RECT, Size(13, 13), Point(-1, -1));
	erode(colorImage, corro, kernel, Point(-1, -1));
	dilate(corro, expand, kernel, Point(-1, -1));
	imshow("形态学滤波", expand);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\形态学滤波像素方块检测.jpg", expand);
}


void CdigitalimageprocessingDlg::OnBnClickedaffineButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	// TODO: 在此添加控件通知处理程序代码
	Mat src, dst;
	Point2f srcTri[3], dstTri[3]; //二维坐标下的点，类型为浮点
	Mat rot_mat(2, 3, CV_32FC1); //单通道矩阵
	Mat warp_mat(2, 3, CV_32FC1);

	src = colorImage;
	dst = Mat::zeros(src.rows, src.cols, src.type());
	//计算矩阵仿射变换
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0); //缩小一个像素
	srcTri[2] = Point2f(0, src.rows - 1);
	//改变目标图像大小
	dstTri[0] = Point2f(src.cols * 0.0, src.rows * 0.33);
	dstTri[1] = Point2f(src.cols * 0.85, src.rows * 0.25);
	dstTri[2] = Point2f(src.cols * 0.15, src.rows * 0.7);
	//由三对点计算仿射变换
	warp_mat = getAffineTransform(srcTri, dstTri);
	//对图像做仿射变换
	warpAffine(src, dst, warp_mat, src.size());
	//计算旋转仿射变换
	Mat dst_dst;
	Point2f center = Point2f(dst.cols / 2, dst.rows / 2);
	double angle = -50.0; //旋转角度，负值表示顺时针
	double scale = 0.6; //各项同性的尺度因子
	rot_mat = getRotationMatrix2D(center, angle, scale);
	warpAffine(dst, dst_dst, rot_mat, dst.size());//将src仿射变换存入dst
	imshow("仿射变换", dst_dst);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\仿射变换.jpg", dst_dst);

}


void CdigitalimageprocessingDlg::OnBnClickedperspectiveButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);
	// 创建灰度图像的 Mat 对象
	Mat grayImage = Mat::zeros(colorImage.size(), CV_8UC1);


	// 遍历每个像素，按公式计算灰度值
	for (int i = 0; i < colorImage.rows; i++) {
		for (int j = 0; j < colorImage.cols; j++) {
			Vec3b color = colorImage.at<Vec3b>(i, j);
			uchar grayValue = static_cast<uchar>(0.3 * color[2] + 0.59 * color[1] + 0.11 * color[0]); // BGR 顺序
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}
	Point2f srcQuad[4], dstQuad[4];
	Mat warp_matrix(3, 3, CV_32FC1);
	Mat src, dst;
	src = colorImage;
	dst = Mat::zeros(src.rows, src.cols, src.type());
	srcQuad[0] = Point2f(0, 0); //src top left
	srcQuad[1] = Point2f(src.cols - 1, 0); //src top right
	srcQuad[2] = Point2f(0, src.rows - 1); //src bottom left
	srcQuad[3] = Point2f(src.cols - 1, src.rows - 1); //src bot right
	dstQuad[0] = Point2f(src.cols * 0.05, src.rows * 0.33); //dst top left
	dstQuad[1] = Point2f(src.cols * 0.9, src.rows * 0.25); //dst top right
	dstQuad[2] = Point2f(src.cols * 0.2, src.rows * 0.7); //dst bottom left
	dstQuad[3] = Point2f(src.cols * 0.8, src.rows * 0.9); //dst bot right
	warp_matrix = getPerspectiveTransform(srcQuad, dstQuad);
	warpPerspective(src, dst, warp_matrix, src.size());
	imshow("dst", dst);
	imwrite("D:\\First-year graduate\\图像处理技术\\第三章课程\\图片\\透视变换.jpg", dst);
}


void CdigitalimageprocessingDlg::OnBnClickedonecamerabutton17()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	/*
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}*/
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	
	ifstream fin("D:\\First-year graduate\\camercab\\camercab\\imageDatalist_right.txt"); /* 标定所用图像文件的路径 */
	//ifstream fin(filepath);
	ofstream fout("D:\\First-year graduate\\camercab\\caliberation_result_right.txt");  /* 保存标定结果的文件 */
	//读取每一幅图像，从中提取出角点，然后对角点进行亚像素精确化	
	_cprintf("start to find corners………………\n");
	int image_count = 0;  /* 图像数量 */
	Size image_size;  /* 图像的尺寸 */
	Size board_size = Size(9, 6);    /* 标定板上每行、列的角点数 */
	vector<Point2f> image_points_buf;  /* 缓存每幅图像上检测到的角点 */
	vector<vector<Point2f>> image_points_seq; /* 保存检测到的所有角点 */
	string filename;
	int count = -1;//用于存储角点个数。
	while (getline(fin, filename))
	{
		image_count++;
		// 用于观察检验输出
		_cprintf("image_count = %d\n", image_count);

		Mat imageInput = imread(filename);
		if (image_count == 1)  //读入第一张图片时获取图像宽高信息
		{
			image_size.width = imageInput.cols;
			image_size.height = imageInput.rows;
			_cprintf("image_size.width = %d\n", image_size.width);
			_cprintf("image_size.height = %d\n", image_size.height);
		}

		/* 提取角点 */
		if (0 == findChessboardCorners(imageInput, board_size, image_points_buf))
		{
			_cprintf("can not find chessboard corners!\n"); //找不到角点
			waitKey(0);
			exit(1);
		}
		else
		{
			Mat view_gray;
			cvtColor(imageInput, view_gray, COLOR_RGB2GRAY);
			/* 亚像素精确化 */
			find4QuadCornerSubpix(view_gray, image_points_buf, Size(5, 5)); //对粗提取的角点进行精确化
			//cornerSubPix(view_gray,image_points_buf,Size(5,5),Size(-1,-1),TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1));
			image_points_seq.push_back(image_points_buf);  //保存亚像素角点
			/* 在图像上显示角点位置 */
			drawChessboardCorners(view_gray, board_size, image_points_buf, false); //用于在图片中标记角点
			imshow("Camera Calibration", view_gray);//显示图片
			waitKey(50);//暂停0.5S		
		}
	}
	int total = image_points_seq.size();
	_cprintf("total = %d\n", total);
	int CornerNum = board_size.width * board_size.height;  //每张图片上总的角点数
	for (int ii = 0; ii < total; ii++)
	{
		if (0 == ii % CornerNum)// 24 是每幅图片的角点个数。此判断语句是为了输出 图片号，便于控制台观看 
		{
			int i = -1;
			i = ii / CornerNum;
			int j = i + 1;
			_cprintf("--> the %d image's data --> :", j);
		}
		if (0 == ii % 3)	// 此判断语句，格式化输出，便于控制台查看
		{
			_cprintf("\n");
		}
		else
		{
			cout.width(10);
		}
		//输出所有的角点
		_cprintf(" -->%f", image_points_seq[ii][0].x);
		_cprintf(" -->%f", image_points_seq[ii][0].y);
	}
	_cprintf("find corner successfully！\n");

	//以下是摄像机标定
	_cprintf("start calibration………………");
	/*棋盘三维信息*/
	Size square_size = Size(10, 10);  /* 实际测量得到的标定板上每个棋盘格的大小 */
	vector<vector<Point3f>> object_points; /* 保存标定板上角点的三维坐标 */
	/*内外参数*/
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 摄像机内参数矩阵 */
	vector<int> point_counts;  // 每幅图像中角点的数量
	Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* 摄像机的5个畸变系数：k1,k2,p1,p2,k3 */
	vector<Mat> tvecsMat;  /* 每幅图像的旋转向量 */
	vector<Mat> rvecsMat; /* 每幅图像的平移向量 */
	/* 初始化标定板上角点的三维坐标 */
	int i, j, t;
	for (t = 0; t < image_count; t++)
	{
		vector<Point3f> tempPointSet;
		for (i = 0; i < board_size.height; i++)
		{
			for (j = 0; j < board_size.width; j++)
			{
				Point3f realPoint;
				/* 假设标定板放在世界坐标系中z=0的平面上 */
				realPoint.x = i * square_size.width;
				realPoint.y = j * square_size.height;
				realPoint.z = 0;
				tempPointSet.push_back(realPoint);
			}
		}
		object_points.push_back(tempPointSet);
	}
	/* 初始化每幅图像中的角点数量，假定每幅图像中都可以看到完整的标定板 */
	for (i = 0; i < image_count; i++)
	{
		point_counts.push_back(board_size.width * board_size.height);
	}
	/* 开始标定 */
	calibrateCamera(object_points, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, 0);
	_cprintf("calibrate successfully！\n");
	//对标定结果进行评价
	_cprintf("start evaluate the calibration results………………\n");
	double total_err = 0.0; /* 所有图像的平均误差的总和 */
	double err = 0.0; /* 每幅图像的平均误差 */
	vector<Point2f> image_points2; /* 保存重新计算得到的投影点 */
	_cprintf("\t each image's calibration error：\n");
	_cprintf("each image's calibration error：\n");
	for (i = 0; i < image_count; i++)
	{
		vector<Point3f> tempPointSet = object_points[i];
		/* 通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点 */
		projectPoints(tempPointSet, rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points2);
		/* 计算新的投影点和旧的投影点之间的误差*/
		vector<Point2f> tempImagePoint = image_points_seq[i];
		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);
		Mat image_points2Mat = Mat(1, image_points2.size(), CV_32FC2);
		for (int j = 0; j < tempImagePoint.size(); j++)
		{
			image_points2Mat.at<Vec2f>(0, j) = Vec2f(image_points2[j].x, image_points2[j].y);
			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
		}
		err = norm(image_points2Mat, tempImagePointMat, NORM_L2);
		total_err += err /= point_counts[i];
		_cprintf("the %d th image's average err: %f pixels\n", i + 1, err);
		fout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
	}
	_cprintf(" the total average err：%f \n", total_err / image_count);
	fout << "总体平均误差：" << total_err / image_count << "像素" << endl << endl;
	_cprintf("evaluate successfully！\n");
	//保存定标结果  	
	_cprintf("start save calibration results………………\n");
	Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 保存每幅图像的旋转矩阵 */
	fout << "相机内参数矩阵：" << endl;
	fout << cameraMatrix << endl << endl;
	fout << "畸变系数：\n";
	fout << distCoeffs << endl << endl << endl;
	for (int i = 0; i < image_count; i++)
	{
		fout << "第" << i + 1 << "幅图像的旋转向量：" << endl;
		fout << tvecsMat[i] << endl;
		/* 将旋转向量转换为相对应的旋转矩阵 */
		Rodrigues(tvecsMat[i], rotation_matrix);
		fout << "第" << i + 1 << "幅图像的旋转矩阵：" << endl;
		fout << rotation_matrix << endl;
		fout << "第" << i + 1 << "幅图像的平移向量：" << endl;
		fout << rvecsMat[i] << endl << endl;
	}
	_cprintf("save successfully\n");
	fout << endl;
	/************************************************************************
	显示定标结果
	*************************************************************************/
	Mat mapx = Mat(image_size, CV_32FC1);
	Mat mapy = Mat(image_size, CV_32FC1);
	Mat R = Mat::eye(3, 3, CV_32F);
	_cprintf("save rectified image\n");
	string imageFileName;
	std::stringstream StrStm;
	for (int i = 0; i != image_count; i++)
	{
		_cprintf("Frame # %d ...\n", i + 1);
		initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix, image_size, CV_32FC1, mapx, mapy);
		StrStm.clear();
		imageFileName.clear();
		string filePath = "D:\\First-year graduate\\camercab\\chess";
		StrStm << i + 1;
		StrStm >> imageFileName;
		filePath += imageFileName;
		filePath += ".jpg";
		Mat imageSource = imread("D:\\First-year graduate\\camercab\\camercab\\left01.jpg");
		Mat newimage = imageSource.clone();
		//另一种不需要转换矩阵的方式
		//undistort(imageSource,newimage,cameraMatrix,distCoeffs);
		remap(imageSource, newimage, mapx, mapy, INTER_LINEAR);
		StrStm.clear();
		filePath.clear();
		filePath = "D:\\First-year graduate\\camercab\\chess";
		StrStm << i + 1;
		StrStm >> imageFileName;
		filePath += imageFileName;
		filePath += "_d.jpg";
		imwrite(filePath, newimage);
	}
	_cprintf(" save successfully\n");
	waitKey(0);

}


void calRealPoint(vector<vector<Point3f>>& obj, int boardWidth, int boardHeight, int imgNumber, int squareSize);
void outputCameraParam(void);



/*计算标定板上模块的实际物理坐标*/
void calRealPoint(vector<vector<Point3f>>& obj, int boardWidth, int boardHeight, int imgNumber, int squareSize)
{
	vector<Point3f> imgpoint;
	for (int rowIndex = 0; rowIndex < boardHeight; rowIndex++)
	{
		for (int colIndex = 0; colIndex < boardWidth; colIndex++)
		{
			imgpoint.push_back(Point3f(rowIndex * squareSize, colIndex * squareSize, 0));
		}
	}
	for (int imgIndex = 0; imgIndex < imgNumber; imgIndex++)
	{
		obj.push_back(imgpoint);
	}
}
Mat R, T, E, F;
Mat Rl, Rr, Pl, Pr, Q;
//映射表
Mat mapLx, mapLy, mapRx, mapRy;

Mat cameraMatrixL = (Mat_<double>(3, 3) << 530.1397548683084, 0, 338.2680507680664,
	0, 530.2291152852337, 232.4902023212199,
	0, 0, 1);
//获得的畸变参数
Mat distCoeffL = (Mat_<double>(5, 1) << -0.266294943795012, -0.0450330886310585, 0.0003024821418382528, -0.001243865371699451, 0.2973605735168139);

Mat cameraMatrixR = (Mat_<double>(3, 3) << 530.1397548683084, 0, 338.2680507680664,
	0, 530.2291152852337, 232.4902023212199,
	0, 0, 1);
Mat distCoeffR = (Mat_<double>(5, 1) << -0.266294943795012, -0.0450330886310585, 0.0003024821418382528, -0.001243865371699451, 0.2973605735168139);

void outputCameraParam(void)
{
	/*保存数据*/
	/*输出数据*/
	FileStorage fs("D:\\First-year graduate\\camercab\\two_camera\\intrisics.yml", FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "cameraMatrixL" << cameraMatrixL << "cameraDistcoeffL" << distCoeffL << "cameraMatrixR" << cameraMatrixR << "cameraDistcoeffR" << distCoeffR;
		fs.release();
		cout << "cameraMatrixL=:" << cameraMatrixL << endl << "cameraDistcoeffL=:" << distCoeffL << endl << "cameraMatrixR=:" << cameraMatrixR << endl << "cameraDistcoeffR=:" << distCoeffR << endl;
	}
	else
	{
		cout << "Error: can not save the intrinsics!!!!" << endl;
	}

	fs.open("D:\\First-year graduate\\camercab\\two_camera\\extrinsics.yml", FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "R" << R << "T" << T << "Rl" << Rl << "Rr" << Rr << "Pl" << Pl << "Pr" << Pr << "Q" << Q;
		cout << "R=" << R << endl << "T=" << T << endl << "Rl=" << Rl << endl << "Rr" << Rr << endl << "Pl" << Pl << endl << "Pr" << Pr << endl << "Q" << Q << endl;
		fs.release();
	}
	else
	{
		cout << "Error: can not save the extrinsic parameters\n";
	}
}
//双目摄像机标定


void CdigitalimageprocessingDlg::OnBnClickedtwocameraButton18()
{
	// TODO: 在此添加控件通知处理程序代码
//摄像头的分辨率
	const int imageWidth = 640;
	const int imageHeight = 480;
	//横向的角点数目
	const int boardWidth = 9;
	//纵向的角点数目
	const int boardHeight = 6;
	//总的角点数目
	const int boardCorner = boardWidth * boardHeight;
	//相机标定时需要采用的图像帧数
	const int frameNumber = 14;
	//标定板黑白格子的大小 单位是mm
	const int squareSize = 10;
	//标定板的总内角点
	const Size boardSize = Size(boardWidth, boardHeight);
	Size imageSize = Size(imageWidth, imageHeight);


	//R旋转矢量 T平移矢量 E本征矩阵 F基础矩阵
	vector<Mat> rvecs; //R
	vector<Mat> tvecs; //T
	//左边摄像机所有照片角点的坐标集合
	vector<vector<Point2f>> imagePointL;
	//右边摄像机所有照片角点的坐标集合
	vector<vector<Point2f>> imagePointR;
	//各图像的角点的实际的物理坐标集合
	vector<vector<Point3f>> objRealPoint;
	//左边摄像机某一照片角点坐标集合
	vector<Point2f> cornerL;
	//右边摄像机某一照片角点坐标集合
	vector<Point2f> cornerR;

	Mat rgbImageL, grayImageL;
	Mat rgbImageR, grayImageR;
	Mat intrinsic;
	Mat distortion_coeff;
	//校正旋转矩阵R，投影矩阵P，重投影矩阵Q
	//映射表
	Mat mapLx, mapLy, mapRx, mapRy;
	Rect validROIL, validROIR;
	//图像校正之后，会对图像进行裁剪，其中，validROI裁剪之后的区域

	Mat img;
	int goodFrameCount = 1;
	while (goodFrameCount <= frameNumber)
	{
		ofstream fout("D:\\First-year graduate\\camercab\\two_camera\\Two_Camera_caliberation_result.txt");  /* 保存标定结果的文件 */
		char filename[100];
		/*读取左边的图像*/
		sprintf_s(filename, "D:\\First-year graduate\\camercab\\camercab\\left%02d.jpg", goodFrameCount);
		rgbImageL = imread(filename, 1);
		imshow("chessboardL", rgbImageL);
		cvtColor(rgbImageL, grayImageL, COLOR_BGR2GRAY);
		/*读取右边的图像*/
		sprintf_s(filename, "D:\\First-year graduate\\camercab\\camercab\\right%02d.jpg", goodFrameCount);
		rgbImageR = imread(filename, 1);
		cvtColor(rgbImageR, grayImageR, COLOR_BGR2GRAY);

		bool isFindL, isFindR;
		isFindL = findChessboardCorners(rgbImageL, boardSize, cornerL);
		isFindR = findChessboardCorners(rgbImageR, boardSize, cornerR);
		if (isFindL == true && isFindR == true)
		{
			cornerSubPix(grayImageL, cornerL, Size(5, 5), Size(-1, 1), TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 20, 0.1));
			drawChessboardCorners(rgbImageL, boardSize, cornerL, isFindL);
			imshow("chessboardL", rgbImageL);
			imagePointL.push_back(cornerL);

			cornerSubPix(grayImageR, cornerR, Size(5, 5), Size(-1, -1), TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 20, 0.1));
			drawChessboardCorners(rgbImageR, boardSize, cornerR, isFindR);
			imshow("chessboardR", rgbImageR);
			imagePointR.push_back(cornerR);

			_cprintf("the image %d is good\n", goodFrameCount);
			goodFrameCount++;
		}
		else
		{
			_cprintf("the image is bad please try again\n");
		}

		if (waitKey(10) == 'q')
		{
			break;
		}
	}

	//计算实际的校正点的三维坐标，根据实际标定格子的大小来设置

	calRealPoint(objRealPoint, boardWidth, boardHeight, frameNumber, squareSize);
	_cprintf("cal real successful\n");

	//标定摄像头
	double rms = stereoCalibrate(objRealPoint, imagePointL, imagePointR,
		cameraMatrixL, distCoeffL,
		cameraMatrixR, distCoeffR,
		Size(imageWidth, imageHeight), R, T, E, F, CALIB_USE_INTRINSIC_GUESS,
		TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 100, 1e-5));

	_cprintf("Stereo Calibration done with RMS error = %f\n", rms);

	stereoRectify(cameraMatrixL, distCoeffL, cameraMatrixR, distCoeffR, imageSize, R, T, Rl,
		Rr, Pl, Pr, Q, CALIB_ZERO_DISPARITY, -1, imageSize, &validROIL, &validROIR);

	//摄像机校正映射
	initUndistortRectifyMap(cameraMatrixL, distCoeffL, Rl, Pl, imageSize, CV_32FC1, mapLx, mapLy);
	initUndistortRectifyMap(cameraMatrixR, distCoeffR, Rr, Pr, imageSize, CV_32FC1, mapRx, mapRy);

	Mat rectifyImageL, rectifyImageR;
	cvtColor(grayImageL, rectifyImageL, COLOR_GRAY2BGR);
	cvtColor(grayImageR, rectifyImageR, COLOR_GRAY2BGR);

	imshow("RecitifyL Before", rectifyImageL);
	imshow("RecitifyR Before", rectifyImageR);

	//经过remap之后，左右相机的图像已经共面并且行对准了
	Mat rectifyImageL2, rectifyImageR2;
	remap(rectifyImageL, rectifyImageL2, mapLx, mapLy, INTER_LINEAR);
	remap(rectifyImageR, rectifyImageR2, mapRx, mapRy, INTER_LINEAR);


	imshow("rectifyImageL", rectifyImageL2);
	imshow("rectifyImageR", rectifyImageR2);

	outputCameraParam();
	//显示校正结果
	Mat canvas;
	double sf;
	int w, h;
	sf = 600. / MAX(imageSize.width, imageSize.height);
	w = cvRound(imageSize.width * sf);
	h = cvRound(imageSize.height * sf);
	canvas.create(h, w * 2, CV_8UC3);

	//左图像画到画布上
	Mat canvasPart = canvas(Rect(0, 0, w, h));
	resize(rectifyImageL2, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
	Rect vroiL(cvRound(validROIL.x * sf), cvRound(validROIL.y * sf),
		cvRound(validROIL.width * sf), cvRound(validROIL.height * sf));
	rectangle(canvasPart, vroiL, Scalar(0, 0, 255), 3, 8);

	_cprintf("Painted ImageL\n");

	//右图像画到画布上
	canvasPart = canvas(Rect(w, 0, w, h));
	resize(rectifyImageR2, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);
	Rect vroiR(cvRound(validROIR.x * sf), cvRound(validROIR.y * sf),
		cvRound(validROIR.width * sf), cvRound(validROIR.height * sf));
	rectangle(canvasPart, vroiR, Scalar(0, 255, 0), 3, 8);

	_cprintf("Painted ImageR\n");

	//画上对应的线条
	for (int i = 0; i < canvas.rows; i += 16)
		line(canvas, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);

	imshow("rectified", canvas);
	_cprintf("wait key\n");
	waitKey(0);
}


void CdigitalimageprocessingDlg::OnBnClickedStereosgbmButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	int mMaxDisp = 96;
	int mP1 = 8 * 9 * 9;
	int mP2 = 32 * 9 * 9;
	int mWinSize = 9;
	int mPreFilterCap = 63;
	Ptr<StereoSGBM> mSGBM = StereoSGBM::create(0, mMaxDisp, mWinSize, mP1, mP2, 1, mPreFilterCap, 10, 100, 32);
	//Ptr<cv::StereoSGBM> mSGBM = cv::StereoSGBM::create(0, 96, 9, 8 * 9 * 9, 32 * 9 * 9, 1, 63, 10, 100, 32);   

	// read image
	Mat left = imread("D:\\First-year graduate\\camercab\\camercab\\left01.jpg", 0);
	Mat right = imread("D:\\First-year graduate\\camercab\\camercab\\right01.jpg", 0);
	Mat disp16s, disp;

	//compute disparity
	mSGBM->compute(left, right, disp16s);

	//disp16s = disp16s / 16;
	//disp16s.convertTo(disp16s, CV_8UC1);
	disp16s.convertTo(disp, CV_8U, 255 / ((32) * 16.));

	//cv::Mat UdispMap = cv::Mat(mMaxDisp, disp.cols, CV_16UC1);
	//cv::Mat VdispMap = cv::Mat(disp.rows, mMaxDisp, CV_16UC1);
	imshow("left", left);
	imshow("right", right);

	imshow("disp", disp);
}


void CdigitalimageprocessingDlg::OnBnClickedHlsButton20()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);

	Mat hls, L, S, L_sobel, S_threshold, combined, src;
	src = colorImage;
	// 转为 HLS 空间
	cvtColor(src, hls, COLOR_BGR2HLS);
	vector<Mat> hls_channels;
	split(hls, hls_channels);

	L = hls_channels[1]; // L 通道
	S = hls_channels[2]; // S 通道

	// 对 L 通道进行 Sobel 边缘检测
	Mat grad_x;
	Sobel(L, grad_x, CV_64F, 1, 0, 3); // X 方向梯度
	convertScaleAbs(grad_x, L_sobel);  // 转换为 8 位

	// 对 S 通道进行阈值分割
	threshold(S, S_threshold, 170, 255, THRESH_BINARY);

	// 融合结果
	combined = L_sobel | S_threshold;
	imshow("hls", hls);
	imshow("L", L);
	imshow("S", S);
	imshow("L_sobel", L_sobel);
	imshow("S_threshold", S_threshold);
	imshow("combined", combined);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\HLS图像.jpg", hls);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\L通道.jpg", L);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\S通道.jpg", S);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\L通道边缘检测.jpg", L_sobel);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\S通道阈值分割.jpg",S_threshold);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\双通道融合.jpg",combined);
	waitKey(0);
}



vector<Point> slidingWindowSearch(const Mat& binaryImage, int startX, int windowWidth, int windowHeight, int minPixels);
// 滑动窗口法：沿y轴（从下至上）滑动窗口，搜索车道线
vector<Point> slidingWindowSearch(const Mat& binaryImage, int startX, int windowWidth, int windowHeight, int minPixels) {
	vector<Point> lanePoints;  // 用于存储车道线的中心点

	int numWindows = binaryImage.rows / windowHeight;  // 计算窗口的数量

	int currentX = startX;  // 初始化当前窗口的x坐标

	// 遍历每个窗口，从底部到顶部滑动
	for (int window = 0; window < numWindows; ++window) {
		// 计算当前窗口的上下边界
		int winYLow = binaryImage.rows - (window + 1) * windowHeight;
		int winYHigh = binaryImage.rows - window * windowHeight;

		// 计算窗口的左右边界，确保不超出图像边界
		int winXLow = max(currentX - windowWidth / 2, 0);
		int winXHigh = min(currentX + windowWidth / 2, binaryImage.cols);

		// 统计窗口内像素值大于200的点（白色像素）
		vector<Point> nonZeroPoints;
		for (int y = winYLow; y < winYHigh; ++y) {
			for (int x = winXLow; x < winXHigh; ++x) {
				if (binaryImage.at<uchar>(y, x) > 200) {  // 统计白色像素点
					nonZeroPoints.push_back(Point(x, y));
				}
			}
		}

		// 如果窗口内白色像素点数量大于minPixels，则更新当前窗口的中心
		if (nonZeroPoints.size() > minPixels) {
			// 计算当前窗口内白色像素点的x坐标均值
			int meanX = 0;
			for (const auto& pt : nonZeroPoints) {
				meanX += pt.x;
			}
			meanX /= nonZeroPoints.size();  // 求均值
			currentX = meanX;  // 更新中心点为均值

			// 将当前窗口中心点加入车道线点
			lanePoints.push_back(Point(currentX, (winYLow + winYHigh) / 2));
		}
	}

	return lanePoints;
}
void CdigitalimageprocessingDlg::OnBnClickedroadlineperspectivebutton21()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 1. 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 2. 转换为 cv::String
	cv::String filepath = stdString;
	Mat colorImage = imread(filepath);

	Mat hls, L, S, L_sobel, S_threshold, combined, src, combined1;
	src = colorImage;
	// 转为 HLS 空间
	cvtColor(src, hls, COLOR_BGR2HLS);
	vector<Mat> hls_channels;
	split(hls, hls_channels);

	L = hls_channels[1]; // L 通道
	S = hls_channels[2]; // S 通道

	// 对 L 通道进行 Sobel 边缘检测
	Mat grad_x;
	Sobel(L, grad_x, CV_64F, 1, 0, 3); // X 方向梯度
	convertScaleAbs(grad_x, L_sobel);  // 转换为 8 位

	// 对 S 通道进行阈值分割
	threshold(S, S_threshold, 170, 255, THRESH_BINARY);

	// 融合结果
	combined = L_sobel | S_threshold;

	Mat warped, M, M_inv;
	// 定义透视变换的四点
	Point2f src_points[4] = { Point2f(combined.cols / 2 - 63, combined.rows / 2 + 100), Point2f(combined.cols / 6 - 20, combined.rows),
		Point2f(combined.cols * 5 / 6 + 60, combined.rows), Point2f(combined.cols / 2 + 65, combined.rows / 2 + 100) };
	Point2f dst_points[4] = { Point2f(combined.cols / 4, 0), Point2f(combined.cols / 4, combined.rows),
		Point2f(combined.cols * 3 / 4, combined.rows), Point2f(combined.cols * 3 / 4, 0) };

	M = getPerspectiveTransform(src_points, dst_points);       // 正变换矩阵
	M_inv = getPerspectiveTransform(dst_points, src_points);   // 逆变换矩阵
	// 转换到鸟瞰图
	warpPerspective(combined, warped, M, combined.size());
	imshow("车道线透视变换", warped);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\2\\车道线透视变换为鸟瞰图.jpg", warped);



	std::vector<int> histogram(warped.cols, 0);

	for (int col = 0; col < warped.cols; ++col) {
		for (int row = 0; row < warped.rows; ++row) {
			if (warped.at<uchar>(row, col) > 200) { // 近白色像素计数
				histogram[col]++;
			}
		}
	}
	// 计算直方图中的最大值
	int maxValue = *std::max_element(histogram.begin(), histogram.end());

	// 创建一个黑色背景的图像用来绘制直方图
	int histHeight = 720;  // 直方图显示的高度
	int histWidth = 1280;   // 直方图显示的宽度
	int binWidth = cvRound((double)histWidth / warped.cols);  // 每个柱的宽度
	Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));

	// 归一化：将灰度值频率映射到直方图高度
	for (int i = 0; i < warped.cols; i++) {
		histogram[i] = cvRound((double)histogram[i] / maxValue * histHeight);
	}
	// 绘制直方图柱形，使用矩形填充每个柱子
	for (int i = 0; i < warped.cols; i++) {
		rectangle(histImage,
			Point(i * binWidth, histHeight - histogram[i]),  // 左上角
			Point((i + 1) * binWidth - 1, histHeight),      // 右下角
			Scalar(255, 255, 255),  // 白色
			-1); // 填充矩形
	}
	imshow("灰度直方图", histImage);

	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\2\\车道线检测灰度直方图.jpg", histImage);

// 计算左右车道线的初始位置
// 车道线大致位于直方图的两个峰值
	int leftStartX = distance(histogram.begin(), max_element(histogram.begin(), histogram.begin() + histogram.size() / 2));
	int rightStartX = distance(histogram.begin(), max_element(histogram.begin() + histogram.size() / 2, histogram.end()));
	// 设置窗口参数
	int windowWidth = 200;  // 窗口宽度
	int windowHeight = 50;  // 窗口高度
	int minPixels = 50;     // 最小像素点数

	// 使用滑动窗口法搜索车道线点
	vector<Point> leftLanePoints = slidingWindowSearch(warped, leftStartX, windowWidth, windowHeight, minPixels);
	vector<Point> rightLanePoints = slidingWindowSearch(warped, rightStartX, windowWidth, windowHeight, minPixels);

	// 提取x和y坐标（分别为左右车道线的坐标）
	vector<double> leftX, leftY, rightX, rightY;
	for (const auto& pt : leftLanePoints) {
		leftX.push_back(pt.x);
		leftY.push_back(pt.y);

	}
	for (const auto& pt : rightLanePoints) {
		rightX.push_back(pt.x);
		rightY.push_back(pt.y);
	}


	// 定义多项式系数数组
	double leftCoeffs1[3], rightCoeffs1[3];
	double leftCoeffs[3], rightCoeffs[3];
	int poly_n = 2;  // 使用二次多项式拟合

	// 使用polyfit拟合左右车道线
	polyfit(leftX.size(), leftX, leftY, poly_n, leftCoeffs1);
	polyfit(rightX.size(), rightX, rightY, poly_n, rightCoeffs1);
	leftCoeffs[0] = leftCoeffs1[2]; rightCoeffs[0] = rightCoeffs1[2];
	leftCoeffs[1] = leftCoeffs1[1]; rightCoeffs[1] = rightCoeffs1[1];
	leftCoeffs[2] = leftCoeffs1[0]; rightCoeffs[2] = rightCoeffs1[0];





	// 创建一个用于绘制车道区域的图像
	Mat laneImage = Mat::zeros(warped.size(), warped.type());

	// 绘制左右车道线
	std::vector<cv::Point> leftLanePoints1, rightLanePoints1;

	// 计算对称轴的位置
	double leftaxis = -leftCoeffs[1] / (2 * leftCoeffs[0]);
	double rightaxis = -rightCoeffs[1] / (2 * rightCoeffs[0]);

	for (int x = 0; x < warped.cols; ++x) {
		// 只取右半部分，即x > 对称轴
		if (x > leftaxis) {
			// 计算二次曲线上的y值
			int yLeft = leftCoeffs[0] * x * x +
				leftCoeffs[1] * x +
				leftCoeffs[2];

			// 检查是否在图像范围内
			if (yLeft >= 0 && yLeft < warped.rows) {
				leftLanePoints1.emplace_back(x, yLeft);
			}
		}
		if (x > rightaxis) {
			// 计算二次曲线上的y值
			int yRight = rightCoeffs[0] * x * x +
				rightCoeffs[1] * x +
				rightCoeffs[2];

			// 检查是否在图像范围内
			if (yRight >= 0 && yRight < warped.rows) {
				rightLanePoints1.emplace_back(x, yRight);
			}
		}

	}
	
	// 绘制左右车道线
	for (const auto& point : leftLanePoints1) {
		circle(laneImage, point, 3, Scalar(255, 255, 255), -1); // 红色点表示左车道线
	}
	for (const auto& point : rightLanePoints1) {
		circle(laneImage, point, 3, Scalar(255, 255, 255), -1); // 绿色点表示右车道线
	}

	// 生成车道区域多边形点集合
	vector<Point> lanePolygon;
	lanePolygon.insert(lanePolygon.end(), leftLanePoints1.begin(), leftLanePoints1.end());   // 左车道线点
	lanePolygon.insert(lanePolygon.end(), rightLanePoints1.rbegin(), rightLanePoints1.rend()); // 右车道线点（反向）


	// 绘制填充的多边形（车道区域）
	vector<vector<Point>> polygons = { lanePolygon };
	cvtColor(laneImage, laneImage, COLOR_GRAY2BGR);
	fillPoly(laneImage, polygons, Scalar(0, 255, 0));  // 绿色填充
	imshow("车道线区域绿色填充", laneImage);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\2\\车道线区域绿色填充.jpg", laneImage);
	// 将车道区域绘制到图上
	cvtColor(warped, warped, COLOR_GRAY2BGR);
	addWeighted(warped, 0.7, laneImage, 0.3, 0, warped);
	imshow("车道线区域绘制到俯瞰图上", warped);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\2\\车道线区域绘制到俯瞰图上.jpg", warped);
	// 逆投影
	cvtColor(combined, combined, COLOR_GRAY2BGR);
	warpPerspective(warped, combined, M_inv, combined.size());
	imshow("车道线区域在俯瞰图逆投影", combined);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\2\\车道线区域在俯瞰图逆投影.jpg", combined);
	Mat laneImage_color, lanImge_RGB;
	warpPerspective(laneImage, laneImage_color, M_inv, combined.size());
	imshow("车道线区域绿色填充逆投影", laneImage_color);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\2\\车道线区域绿色填充逆投影.jpg", laneImage_color);
	addWeighted(colorImage, 0.7, laneImage_color, 0.3, 0, colorImage);

	imshow("最终车道线结果", colorImage);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\2\\最终车道线结果.jpg", colorImage);
	waitKey(0);

}


void CdigitalimageprocessingDlg::OnBnClickedhoughroadlineButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	m_filepath.GetWindowText(filePath);

	// 检查文件路径是否为空
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径为空，请先拖入文件！"));
		return;
	}
	// 转换为 std::string
	CT2CA pszConvertedAnsiString(filePath); // 将宽字符（Unicode）转换为多字节字符
	std::string stdString(pszConvertedAnsiString);

	// 转换为 cv::String
	cv::String filepath = stdString;
	Mat img = imread(filepath);

	// 转换为灰度图
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// 高斯模糊
	Mat blurred;
	GaussianBlur(gray, blurred, Size(5, 5), 0);

	// 使用Canny算法进行边缘检测
	Mat edges;
	Canny(blurred, edges, 50, 150);
	imshow("Canny算法进行边缘检测", edges);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\3\\Canny算法进行边缘检测.jpg", edges);
	// imshow("车道线", edges);
	 // 感兴趣区域(ROI)裁剪
	 // 可以选择感兴趣区域，避免影响车道线检测的背景干扰
	 // 创建一个掩模，定义车道区域
	Mat mask = Mat::zeros(edges.size(), edges.type());
	Point vertices[1][4] = {
		{Point(img.cols / 2 - 63, img.rows / 2 + 100), Point(img.cols / 6 - 20, img.rows - 60),
		Point(img.cols * 5 / 6 + 60, img.rows - 60), Point(img.cols / 2 + 65, img.rows / 2 + 100) } };
	const Point* ppt[1] = { vertices[0] };
	int npt[] = { 4 };
	fillPoly(mask, ppt, npt, 1, Scalar(255), 8);

	// 使用掩模与边缘图像相乘，只保留感兴趣区域
	Mat masked_edges;
	bitwise_and(edges, mask, masked_edges);
	imshow("感兴趣区域", masked_edges);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\3\\感兴趣区域.jpg", masked_edges);
	// 使用霍夫线变换检测小线段
	vector<Vec4i> lines;
	HoughLinesP(masked_edges, lines, 1, CV_PI / 18, 10, 10, 250); // 参数需调整

	// 拟合为曲线
	vector<Point> points;
	for (size_t i = 0; i < lines.size(); i++) {
		points.push_back(Point(lines[i][0], lines[i][1]));
		points.push_back(Point(lines[i][2], lines[i][3]));

	}
	// 绘制检测到的直线
	Mat result = img.clone();
	for (size_t i = 0; i < lines.size(); i++) {
		Point p1(lines[i][0], lines[i][1]);  // 线段起点
		Point p2(lines[i][2], lines[i][3]);  // 线段终点
		line(result, p1, p2, Scalar(0, 255, 0), 10);  // 绘制绿色线段
	}
	// 显示结果
	imshow("车道线结果", result);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\车道线\\3\\车道线结果.jpg",result);
	waitKey(0);

}


void CdigitalimageprocessingDlg::OnBnClickedfeaurematchButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat obj = imread("D:\\First-year graduate\\图像处理技术\\第五周课程\\2.jpeg");   //载入目标图像
	Mat scene = imread("D:\\First-year graduate\\图像处理技术\\第五周课程\\1.jpeg"); //载入场景图像
	/*if (obj.empty() || scene.empty())
	{
		cout << "Can't open the picture!\n";
		return;
	}*/
	vector<KeyPoint> obj_keypoints, scene_keypoints;
	Mat obj_descriptors, scene_descriptors;
	Ptr<ORB> detector = ORB::create();

	detector->detect(obj, obj_keypoints);
	detector->detect(scene, scene_keypoints);
	detector->compute(obj, obj_keypoints, obj_descriptors);
	detector->compute(scene, scene_keypoints, scene_descriptors);

	BFMatcher matcher(NORM_HAMMING, true); //汉明距离做为相似度度量
	vector<DMatch> matches;
	matcher.match(obj_descriptors, scene_descriptors, matches);
	Mat match_img;
	drawMatches(obj, obj_keypoints, scene, scene_keypoints, matches, match_img);
	imshow("滤除误匹配前", match_img);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\特征点匹配\\滤除误匹配前.jpg", match_img);
	//保存匹配对序号
	vector<int> queryIdxs(matches.size()), trainIdxs(matches.size());
	for (size_t i = 0; i < matches.size(); i++)
	{
		queryIdxs[i] = matches[i].queryIdx;
		trainIdxs[i] = matches[i].trainIdx;

	}

	Mat H12;   //变换矩阵

	vector<Point2f> points1;
	KeyPoint::convert(obj_keypoints, points1, queryIdxs);
	vector<Point2f> points2;
	KeyPoint::convert(scene_keypoints, points2, trainIdxs);
	int ransacReprojThreshold = 5;  //拒绝阈值


	H12 = findHomography(Mat(points1), Mat(points2), cv::RANSAC, ransacReprojThreshold);
	vector<char> matchesMask(matches.size(), 0);
	Mat points1t;
	perspectiveTransform(Mat(points1), points1t, H12);
	for (size_t i1 = 0; i1 < points1.size(); i1++)  //保存‘内点’
	{
		if (norm(points2[i1] - points1t.at<Point2f>((int)i1, 0)) <= ransacReprojThreshold) //给内点做标记
		{
			matchesMask[i1] = 1;

		}
	}
	Mat match_img2;   //滤除‘外点’后
	drawMatches(obj, obj_keypoints, scene, scene_keypoints, matches, match_img2, Scalar(0, 0, 255), Scalar::all(-1), matchesMask);

	//画出目标位置
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = Point(0, 0); obj_corners[1] = Point(obj.cols, 0);
	obj_corners[2] = Point(obj.cols, obj.rows); obj_corners[3] = Point(0, obj.rows);
	std::vector<Point2f> scene_corners(4);
	perspectiveTransform(obj_corners, scene_corners, H12);
	//line( match_img2, scene_corners[0] + Point2f(static_cast<float>(obj.cols), 0),scene_corners[1] + Point2f(static_cast<float>(obj.cols), 0),Scalar(0,0,255),2);
	//line( match_img2, scene_corners[1] + Point2f(static_cast<float>(obj.cols), 0),scene_corners[2] + Point2f(static_cast<float>(obj.cols), 0),Scalar(0,0,255),2);
	//line( match_img2, scene_corners[2] + Point2f(static_cast<float>(obj.cols), 0),scene_corners[3] + Point2f(static_cast<float>(obj.cols), 0),Scalar(0,0,255),2);
	//line( match_img2, scene_corners[3] + Point2f(static_cast<float>(obj.cols), 0),scene_corners[0] + Point2f(static_cast<float>(obj.cols), 0),Scalar(0,0,255),2);
	line(match_img2, Point2f((scene_corners[0].x + static_cast<float>(obj.cols)), (scene_corners[0].y)), Point2f((scene_corners[1].x + static_cast<float>(obj.cols)), (scene_corners[1].y)), Scalar(0, 0, 255), 2);
	line(match_img2, Point2f((scene_corners[1].x + static_cast<float>(obj.cols)), (scene_corners[1].y)), Point2f((scene_corners[2].x + static_cast<float>(obj.cols)), (scene_corners[2].y)), Scalar(0, 0, 255), 2);
	line(match_img2, Point2f((scene_corners[2].x + static_cast<float>(obj.cols)), (scene_corners[2].y)), Point2f((scene_corners[3].x + static_cast<float>(obj.cols)), (scene_corners[3].y)), Scalar(0, 0, 255), 2);
	line(match_img2, Point2f((scene_corners[3].x + static_cast<float>(obj.cols)), (scene_corners[3].y)), Point2f((scene_corners[0].x + static_cast<float>(obj.cols)), (scene_corners[0].y)), Scalar(0, 0, 255), 2);

	float A_th;
	A_th = atan(abs((scene_corners[3].y - scene_corners[0].y) / (scene_corners[3].x - scene_corners[0].x)));
	A_th = 90 - 180 * A_th / 3.14;
	//printf("angle=%f\n", A_th);

	imshow("滤除误匹配后", match_img2);
	imwrite("D:\\First-year graduate\\图像处理技术\\第五周课程\\特征点匹配\\滤除误匹配后.jpg", match_img2);
	//line( scene, scene_corners[0],scene_corners[1],Scalar(0,0,255),2);
	//line( scene, scene_corners[1],scene_corners[2],Scalar(0,0,255),2);
	//line( scene, scene_corners[2],scene_corners[3],Scalar(0,0,255),2);
	//line( scene, scene_corners[3],scene_corners[0],Scalar(0,0,255),2);

	//imshow("场景图像", scene);
	//imwrite("D:\\First - year graduate\\图像处理技术\\第五周课程\\特征点匹配\\场景图像.jpg", scene);
	Mat rotimage;
	Mat rotate = getRotationMatrix2D(Point(scene.cols / 2, scene.rows / 2), A_th, 1);
	warpAffine(scene, rotimage, rotate, scene.size());
	//imshow("rotimage", rotimage);
	imwrite("D:\\First - year graduate\\图像处理技术\\第五周课程\\特征点匹配\\rotimage.jpg", rotimage);

	//方法三 透视变换  
	Point2f src_point[4];
	Point2f dst_point[4];
	src_point[0].x = scene_corners[0].x;
	src_point[0].y = scene_corners[0].y;
	src_point[1].x = scene_corners[1].x;
	src_point[1].y = scene_corners[1].y;
	src_point[2].x = scene_corners[2].x;
	src_point[2].y = scene_corners[2].y;
	src_point[3].x = scene_corners[3].x;
	src_point[3].y = scene_corners[3].y;


	dst_point[0].x = 0;
	dst_point[0].y = 0;
	dst_point[1].x = obj.cols;
	dst_point[1].y = 0;
	dst_point[2].x = obj.cols;
	dst_point[2].y = obj.rows;
	dst_point[3].x = 0;
	dst_point[3].y = obj.rows;

	Mat newM(3, 3, CV_32FC1);
	newM = getPerspectiveTransform(src_point, dst_point);

	Mat dst = scene.clone();

	warpPerspective(scene, dst, newM, obj.size());

	//imshow("obj", obj);
	//imshow("dst", dst);

	Mat resultimg = dst.clone();

	absdiff(obj, dst, resultimg);//当前帧跟前面帧相减

	imshow("result", resultimg);

	//imshow("dst", dst);
	//imshow("src", obj);
}
