
// GEO-DemoDlg.h: 头文件
//
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <afxdlgs.h>

#define PI 3.1415926
#define rad2deg 180 / PI

#pragma once


// CGEODemoDlg 对话框
class CGEODemoDlg : public CDialogEx
{
	// 构造
public:
	CGEODemoDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CMenu menu;
	CStatusBar status;

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GEODEMO_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	double r2d(double ang_rad);
	double d2r(double ang_deg);



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
	afx_msg void calc();
private:
	CListCtrl listctl;
	struct angle_point
	{
		std::string name;
		double x = 0, y = 0;
	};
	struct point
	{
		std::string name;
		double x = 0, y = 0, h = 0;
	} tmp_point;
	angle_point ref_height;
	angle_point ap[2];
	point middle_p[3];
	std::vector<point> point_vec, tmp_point_vec;
	double start_angle = 0;

	void insert_height(point& p);
public:
	afx_msg void exitfunc();
	afx_msg void openfile();
	afx_msg void savefunc();
	afx_msg void anglecalc();
	afx_msg void IDW();
	afx_msg void AreaCalc();
	afx_msg void CrossCalc();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
};
