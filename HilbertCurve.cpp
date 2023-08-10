#include "framework.h"
#include "HilbertCurve.h"
#include "HilberLineABC.h"
#include "SetConfig.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HILBERTCURVE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    nCmdShow = SW_SHOWMAXIMIZED;
    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HILBERTCURVE));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//窗口类
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HILBERTCURVE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(ZjhColor::BackGroundColor().R, ZjhColor::BackGroundColor().G, ZjhColor::BackGroundColor().B));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HILBERTCURVE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//创建窗口实例,并显示和刷新窗口
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, SetConfig::zjhScreenWidth, SetConfig::zjhScreenHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SquareSide* squareSide = SquareSide::GetInstance();
    ZjhColor hilbertUC = ZjhColor(200, 150, 120);
    std::vector<HilberU> hilberUs_temp1;
    std::vector<HilberU> hilberUs_temp2;
    switch (message)
    {
    case WM_LBUTTONDOWN:
        squareSide->backgroundC.R = rand() % 255;
        squareSide->backgroundC.G = rand() % 255;
        squareSide->backgroundC.B = rand() % 255;
        squareSide->DrawSide(hWnd, squareSide->backgroundC);
        for (HilberU item : squareSide->hilberUs) {
            hilberUs_temp2 = item.Split(hWnd, hilbertUC);
            hilberUs_temp1.insert(hilberUs_temp1.end(), hilberUs_temp2.begin(), hilberUs_temp2.end());
        }
        squareSide->DrawU(hWnd, ZjhColor::BackGroundColor());
        squareSide->hilberUs = hilberUs_temp1;
        squareSide->DrawU(hWnd, hilbertUC);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT://绘制调用
        {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
            //首先绘制外框
            squareSide->DrawSide(hWnd, squareSide->backgroundC);
            //绘制一个希尔伯特U型折线
            HilberU hilberU = HilberU(ZjhPoint2D(512, 512), ZjhDirection::Down, 512);
            hilberU.Draw(hWnd, hilbertUC);
            squareSide->hilberUs.push_back(hilberU);
        EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
