
// GEO-DemoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GEO-Demo.h"
#include "GEO-DemoDlg.h"
#include "afxdialogex.h"

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


// CGEODemoDlg 对话框



CGEODemoDlg::CGEODemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GEODEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGEODemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, listctl);
}

BEGIN_MESSAGE_MAP(CGEODemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_COMMAND(ID_32776, &CGEODemoDlg::calc)
	ON_COMMAND(ID_32773, &CGEODemoDlg::exitfunc)
	ON_COMMAND(ID_32771, &CGEODemoDlg::openfile)
	ON_COMMAND(ID_32772, &CGEODemoDlg::savefunc)
	ON_COMMAND(ID_32777, &CGEODemoDlg::anglecalc)
	ON_COMMAND(ID_32779, &CGEODemoDlg::IDW)
	ON_COMMAND(ID_32778, &CGEODemoDlg::AreaCalc)
	ON_COMMAND(ID_32780, &CGEODemoDlg::CrossCalc)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CGEODemoDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CGEODemoDlg 消息处理程序

BOOL CGEODemoDlg::OnInitDialog()
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
	menu.LoadMenuW(IDR_MENU1);
	SetMenu(&menu);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGEODemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGEODemoDlg::OnPaint()
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
	CDC* pdc = GetDC();

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGEODemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGEODemoDlg::calc()
{
	// TODO: 在此添加命令处理程序代码
	
}



void CGEODemoDlg::exitfunc()
{
	// TODO: 在此添加命令处理程序代码
	OnCancel();
}


void CGEODemoDlg::openfile()
{
	// TODO: 在此添加命令处理程序代码
	/*CFileDialog fileDialog(TRUE, _T("txt"), NULL, 0, _T("文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*||"), this);
	fileDialog.DoModal();*/
	CString tmp_name;
	CFileDialog file(TRUE);
	file.DoModal();
	auto path = file.GetPathName();

	std::ifstream fin;
	int index = 0;
	fin.open(path);
	std::string line = "", word = "";
	if (fin.is_open())
	{
		std::getline(fin, line, '\n');
		std::stringstream ss(line);
		while (std::getline(ss, word, ','))
		{
			if (index == 0)
			{
				ref_height.name = word.c_str();
				index++;
				continue;
			}
			if (index == 1)
			{
				ref_height.x = atof(word.c_str());
				ref_height.y = ref_height.x;
				index = 0;
				break;
			}
		}
		ss.clear();
		std::getline(fin, line, '\n');
		ss.str(line);
		while (std::getline(ss, word, ','))
		{
			//tmp_name.Format(_T("%s"), word.c_str());
			middle_p[index].name = word.c_str();
			index++;
		}
		ss.clear();
		index = 0;
		for (auto i = 0; i < 2; i++)
		{
			while (std::getline(fin, line, '\n'))
			{
				ss.str(line);
				while (std::getline(ss, word, ','))
				{
					if (index == 0)
					{
						ap[i].name = word.c_str();
						index++; continue;
					}
					if (index == 1)
					{
						ap[i].x = atof(word.c_str());
						index++; continue;
					}
					if (index == 2)
					{
						ap[i].y = atof(word.c_str());
						index = 0; break;
					}
				}
				ss.clear();
				break;
			}
		}
		//MessageBox(ap[1].name);

		while (std::getline(fin, line, '\n'))
		{
			if (line.size() < 2)
			{
				continue;
			}
			ss.str(line);
			while (std::getline(ss, word, ','))
			{
				if (index == 0)
				{
					tmp_point.name = word.c_str();
					index++; continue;
				}
				if (index == 1)
				{
					tmp_point.x = atof(word.c_str());
					index++; continue;
				}
				if (index == 2)
				{
					tmp_point.y = atof(word.c_str());
					index++; continue;
				}
				if (index == 3)
				{
					tmp_point.h = atof(word.c_str());
					index = 0; break;
				}

			}
			ss.clear();
			point_vec.push_back(tmp_point);
		}
		tmp_point_vec = point_vec;
		CString header[4] = {
			TEXT("name"),TEXT("X"),TEXT("Y"),TEXT("Z")
		};
		CString txt1, txt2, txt3, txt4;
		for (auto i = 0; i < 4; i++)
		{
			listctl.InsertColumn(i, header[i], LVCFMT_CENTER, 70);
		}
		for (auto i = 0; i < point_vec.size(); i++)
		{
			txt1 = CString(point_vec[i].name.c_str());
			txt2.Format(_T("%.3f"), point_vec[i].x);
			txt3.Format(_T("%.3f"), point_vec[i].y);
			txt4.Format(_T("%.3f"), point_vec[i].h);
			listctl.InsertItem(i, txt1);
			listctl.SetItemText(i, 1, txt2);
			listctl.SetItemText(i, 2, txt3);
			listctl.SetItemText(i, 3, txt4);
		}
	}
	listctl.SetExtendedStyle(listctl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	fin.close();

	for (auto i = 0; i < sizeof(middle_p) / sizeof(middle_p[0]); i++)
	{
		for (auto j = 0; j < point_vec.size(); j++)
		{
			if (middle_p[i].name == point_vec[j].name)
			{
				middle_p[i].x = point_vec[j].x;
				middle_p[i].y = point_vec[j].y;
				middle_p[i].h = point_vec[j].h;
				break;
			}
			else
			{
				continue;
			}
		}
	}

}


void CGEODemoDlg::savefunc()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog file_w(FALSE);
	file_w.DoModal();
	auto locforw = file_w.GetPathName();
	std::ofstream of;
	of.open(locforw);
	if (of.is_open())
	{
		for (auto &it : point_vec)
		{
			of << it.name << '\t' << it.x << '\t' << it.y << '\t' << it.h << '\n';
		}
	}
	of.close();
}




void CGEODemoDlg::anglecalc()
{
	// TODO: 在此添加命令处理程序代码
	for (auto i = 0; i < sizeof(middle_p) / sizeof(middle_p[0]); i++)
	{
		for (auto j = 0; j < point_vec.size(); j++)
		{
			if (middle_p[i].name == point_vec[j].name)
			{
				middle_p[i].x = point_vec[j].x;
				middle_p[i].y = point_vec[j].y;
				middle_p[i].h = point_vec[j].h;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	double angle = 0;
	auto det_y = ap[0].y - ap[1].y;
	auto det_x = ap[0].x - ap[1].x;
	angle = atan2(det_y, det_x);
	start_angle = r2d(angle);
}

double CGEODemoDlg::r2d(double ang_rad)
{
	std::ofstream fout;
	fout.open("angle.txt", std::ios::out);
	fout << "coor_angle: \ndeg\tmin\tsec\n";
	auto deg = ang_rad * rad2deg + 180;
	double degree = static_cast<int>(deg);
	auto min = (deg - static_cast<int>(deg)) * 60;
	auto minute = static_cast<int>(min);
	auto second = (min - minute) * 60;
	//degree += (minute * 1.0 / 60) + (second / 3600);
	fout << degree << '\t' << minute << '\t' << second << '\n';
	fout.close();
	degree += minute * 1.0 / 100 + second / 10000;
	return degree;
}

double CGEODemoDlg::d2r(double ang_deg)
{
	auto deg = floor(ang_deg);
	auto min_sec = (ang_deg - deg) * 100;
	auto min = floor(min_sec);
	auto sec = (min_sec - min) * 100;
	deg += min / 60 + sec / 3600;
	return deg * PI / 180;
}

struct {
	std::string name;
	double dis = 0;
} sort_unit;

double dis_calc(double x0, double x1, double y0, double y1)
{
	auto dis = sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
	return dis;
}

bool comparebydis(decltype(sort_unit)& u1, decltype(sort_unit)& u2)
{
	return u1.dis < u2.dis;
}

void CGEODemoDlg::IDW()
{
	// TODO: 在此添加命令处理程序代码
	std::ofstream fout;
	fout.open("IDW_test.txt", std::ios::out);
	std::vector<decltype(sort_unit)> unit;
	insert_height(middle_p[0]);
	fout << middle_p[0].name << '\t' << middle_p[0].x << '\t' << middle_p[0].y << '\t' << middle_p[0].h << '\n';

	fout.close();
}

void CGEODemoDlg::insert_height(point& p)
{
	//std::ofstream fout;
	/*fout.open("IDW.txt", std::ios::app);
	fout << "used points\n";*/
	std::vector<decltype(sort_unit)> unit;
	for (auto i = 0; i < point_vec.size(); i++)
	{
		sort_unit.dis = dis_calc(p.x, point_vec[i].x, p.y, point_vec[i].y);
		sort_unit.name = point_vec[i].name;
		unit.push_back(sort_unit);
	}
	std::sort(unit.begin(), unit.end(), comparebydis);
	double dis_ = 0;
	double _dis_ = 0;
	for (auto i = 0; i < 5; i++)
	{
		for (auto j = 0; j < point_vec.size(); j++)
		{
			if (unit[i].name == point_vec[j].name)
			{
				dis_ += point_vec[j].h / unit[i].dis;
				_dis_ += 1.0 / unit[i].dis;
				//fout << point_vec[j].name << '\t' << point_vec[j].x << '\t' << point_vec[j].y << '\t' << point_vec[j].h << '\n';
				break;
			}
		}
	}
	p.h = dis_ / _dis_;
	//fout << '\n';
}


void CGEODemoDlg::AreaCalc()
{
	// TODO: 在此添加命令处理程序代码

	double D_[2]{
		0, 0
	};
	D_[0] = dis_calc(middle_p[0].x, middle_p[1].x, middle_p[0].y, middle_p[1].y);
	D_[1] = dis_calc(middle_p[1].x, middle_p[2].x, middle_p[1].y, middle_p[2].y);
	auto D = D_[0] + D_[1];
	double area = 0;
	auto num1 = static_cast<int>(D_[0] / 10);
	auto num = static_cast<int>(D / 10);
	point* insert_point = new point[num];
	std::vector<point> main_point;
	for (auto i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			int L = 0;
			auto angle = atan2(middle_p[1].y - middle_p[0].y, middle_p[1].x - middle_p[0].x);
			for (auto j = 0; j < num1; j++)
			{
				L = (j + 1) * 10;
				insert_point[j].x = middle_p[i].x + L * cos(angle);
				insert_point[j].y = middle_p[i].y + L * sin(angle);
				insert_point[j].name = "V-";
				insert_point[j].name += std::to_string(j + 1);
			}
		}
		if (i == 1)
		{
			int L = 0;
			auto angle = atan2(middle_p[2].y - middle_p[1].y, middle_p[2].x - middle_p[1].x);
			for (auto j = num1; j < num; j++)
			{
				L = (j + 1) * 10;
				insert_point[j].x = middle_p[i].x + (L - D_[0]) * cos(angle);
				insert_point[j].y = middle_p[i].y + (L - D_[0]) * sin(angle);
				insert_point[j].name = "V-";
				insert_point[j].name += std::to_string(j + 1);
			}
		}
	}
	std::ofstream fout;
	fout.setf(std::ios::fixed);
	fout.precision(3);
	fout.open("Area.txt", std::ios::out);
	fout << "Route Main Point: \n";
	for (auto i = 0; i < 3; i++)
	{
		main_point.push_back(middle_p[i]);
		fout << middle_p[i].name << '\t' << middle_p[i].x << '\t' << middle_p[i].y << '\t' << middle_p[i].h << '\n';
		if (i == 0)
		{
			for (auto j = 0; j < num1; j++)
			{
				insert_height(insert_point[j]);
				main_point.push_back(insert_point[j]);
				fout << insert_point[j].name << '\t' << insert_point[j].x << '\t' << insert_point[j].y << '\t' << insert_point[j].h << '\n';
			}
		}
		if (i == 1)
		{
			for (auto j = num1; j < num; j++)
			{
				insert_height(insert_point[j]);
				main_point.push_back(insert_point[j]);
				fout << insert_point[j].name << '\t' << insert_point[j].x << '\t' << insert_point[j].y << '\t' << insert_point[j].h << '\n';
			}
		}
	}
	for (auto i = 0; i < main_point.size() - 1; i++)
	{
		area += (main_point[i].h + main_point[i + 1].h - 2 * ref_height.x) * dis_calc(main_point[i].x, main_point[i + 1].x, main_point[i].y, main_point[i + 1].y) / 2;
		//fout << '\n' << dis_calc(main_point[i].x, main_point[i + 1].x, main_point[i].y, main_point[i + 1].y) << '\n';
	}
	fout << "Area: " << area << '\n';
	fout << "Distance: " << D << '\n';
	fout.close();
	delete[]insert_point;
	MessageBox(TEXT("Done!"));
}


void CGEODemoDlg::CrossCalc()
{
	// TODO: 在此添加命令处理程序代码
	point M_insert[10], N_insert[10];
	std::vector<point> tmp_Mvec, tmp_Nvec;
	point M_[2];
	M_[0].name = "M"; M_[1].name = "N";
	double area1 = 0, area2 = 0;
	std::ofstream fout;
	fout.setf(std::ios::fixed);
	fout.precision(3);
	fout.open("Cross.txt", std::ios::out);
	fout << "Cross Main Point: \n";
	for (auto i = 0; i < 2; i++)
	{
		M_[i].x = (middle_p[i].x + middle_p[i + 1].x) / 2;
		M_[i].y = (middle_p[i].y + middle_p[i + 1].y) / 2;
		insert_height(M_[i]);
		tmp_point_vec.push_back(M_[i]);
	}
	for (auto i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			auto angle = atan2(middle_p[1].y - middle_p[0].y, middle_p[1].x - middle_p[0].x) + PI / 2;
			for (auto j = 0; j < 5; j++)
			{
				M_insert[j].x = M_[i].x + (j + 1) * 5 * cos(angle);
				M_insert[j].y = M_[i].y + (j + 1) * 5 * sin(angle);
				M_insert[j].name = "MC-";
				M_insert[j].name += std::to_string(j + 1);
				insert_height(M_insert[j]);
			}
			for (auto j = 5; j < 10; j++)
			{
				M_insert[j].x = M_[i].x + (4 - j) * 5 * cos(angle);
				M_insert[j].y = M_[i].y + (4 - j) * 5 * sin(angle);
				M_insert[j].name = "MC-";
				M_insert[j].name += std::to_string(j + 1);
				insert_height(M_insert[j]);
			}
		}
		if (i == 1)
		{
			auto angle = atan2(middle_p[2].y - middle_p[1].y, middle_p[2].x - middle_p[1].x) + PI / 2;
			for (auto j = 0; j < 5; j++)
			{
				N_insert[j].x = M_[i].x + (j + 1) * 5 * cos(angle);
				N_insert[j].y = M_[i].y + (j + 1) * 5 * sin(angle);
				N_insert[j].name = "NC-";
				N_insert[j].name += std::to_string(j + 1);
				insert_height(N_insert[j]);
			}
			for (auto j = 5; j < 10; j++)
			{
				N_insert[j].x = M_[i].x + (4 - j) * 5 * cos(angle);
				N_insert[j].y = M_[i].y + (4 - j) * 5 * sin(angle);
				N_insert[j].name = "NC-";
				N_insert[j].name += std::to_string(j + 1);
				insert_height(N_insert[j]);
			}
		}
	}
	for (auto i = 4; i > -1; i--)
	{
		tmp_Mvec.push_back(M_insert[i]);
		tmp_Nvec.push_back(N_insert[i]);
	}
	tmp_Mvec.push_back(M_[0]); tmp_Nvec.push_back(M_[1]);
	for (auto i = 5; i < 10; i++)
	{
		tmp_Mvec.push_back(M_insert[i]);
		tmp_Nvec.push_back(N_insert[i]);
	}
	for (auto i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			for (auto j = 0; j < tmp_Mvec.size(); j++)
			{
				fout << tmp_Mvec[j].name << '\t' << tmp_Mvec[j].x << '\t' << tmp_Mvec[j].y << '\t' << tmp_Mvec[j].h << '\n';
			}
		}
		if (i == 1)
		{
			for (auto j = 0; j < tmp_Nvec.size(); j++)
			{
				fout << tmp_Nvec[j].name << '\t' << tmp_Nvec[j].x << '\t' << tmp_Nvec[j].y << '\t' << tmp_Nvec[j].h << '\n';
			}
		}
	}
	for (auto i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			for (auto j = 0; j < tmp_Mvec.size() - 1; j++)
			{
				area1 += (tmp_Mvec[j].h + tmp_Mvec[j + 1].h - 2 * ref_height.x) * dis_calc(tmp_Mvec[j].x, tmp_Mvec[j + 1].x, tmp_Mvec[j].y, tmp_Mvec[j + 1].y) / 2;
			}
		}
		if (i == 1)
		{
			for (auto j = 0; j < tmp_Nvec.size() - 1; j++)
			{
				area2 += (tmp_Nvec[j].h + tmp_Nvec[j + 1].h - 2 * ref_height.x) * dis_calc(tmp_Nvec[j].x, tmp_Nvec[j + 1].x, tmp_Nvec[j].y, tmp_Nvec[j + 1].y) / 2;
			}
		}
	}
	fout << "Area1: \n";
	fout << area1 << '\n';
	fout << "Area2: \n";
	fout << area2 << '\n';
	fout.close();
	MessageBox(TEXT("Done!"));
}


void CGEODemoDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
