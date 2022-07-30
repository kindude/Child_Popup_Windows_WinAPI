#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>
#include <stdlib.h>

using namespace std;




//#define WM_LBUTTONDBLCLK                0x0203

// --- Прототип оконной функции главного окна
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



// --- Объявление глобальных переменных
HINSTANCE hInst; // Дескриптор экземпляра приложения

TCHAR ClassName1[] = "Windows Class"; // Название класса окна
TCHAR AppTitle1[] = "Главное окно группа АСУ-19 \n Сыгинь Л.Я."; // Заголовок главн. окна

TCHAR ClassName2[] = "PopupWindow Class";
TCHAR AppTitle2[] = " Временное окно";


TCHAR ClassName3[] = "ChildWindow Class";
TCHAR AppTitle3[] = "Дочернее окно";

FLASHWINFO fi;

RECT rect;
HWND hMainWnd, hWndPopup, hWndChild;
// --- Главная функция приложения WinMain
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));
	HBRUSH FIRST_BRUSH, SECOND_BRUSH, THIRD_BRUSH;
	FIRST_BRUSH = CreateSolidBrush(RGB((int)rand() % 255, (int)rand() % 255, (int)rand() % 255));
	SECOND_BRUSH = CreateSolidBrush(RGB((int)rand() % 255, (int)rand() % 255, (int)rand() % 255));
	THIRD_BRUSH = CreateSolidBrush(RGB((int)rand() % 255, (int)rand() % 255, (int)rand() % 255));

	



	WNDCLASS wc_main, wc_popup, wc_child; // Структура для класса окна
	 // Дескриптор главного окна прилож.
	MSG msg; // Структура для хранения сообщения
	// --- Проверка, было ли приложение запущено ранее

	int cx, cy;
	cx = GetSystemMetrics(SM_CXFULLSCREEN);
	cy = GetSystemMetrics(SM_CXFULLSCREEN);




	// Главное окно

	if ((hMainWnd = FindWindow(ClassName1, NULL)) != NULL)
	{

		// Если прилож. было запущено ранее, активизировать
		// и выдвинуть на передний план его главное окно
		if (IsIconic(hMainWnd))
			ShowWindow(hMainWnd, SW_RESTORE);
		SetForegroundWindow(hMainWnd);
		// Работа новой копии прекращается
		return FALSE;
	}



	hInst = hInstance; // Сохран. дескриптора экз. прилож.
	ZeroMemory(&wc_main, sizeof(wc_main)); // Очистка полей структуры
	// Заполнение полей стр-ры WNDCLASS
	wc_main.lpszClassName = ClassName1; // Имя класса окон
	//Адрес оконной ф-ции
	wc_main.lpfnWndProc = (WNDPROC)MainWndProc;
	wc_main.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // Стиль класса окон
	wc_main.hInstance = hInstance; // Экземпляр приложения
	// Пиктограмма для окон
	wc_main.hIcon = LoadIcon(NULL, IDI_SHIELD);
	// Курсор мыши для окон
	wc_main.hCursor = LoadCursor(NULL, IDC_ARROW);
	// Кисть для окон
	wc_main.hbrBackground = FIRST_BRUSH;
	wc_main.lpszMenuName = NULL; // Ресурс меню окон
	wc_main.cbClsExtra = 0; // Дополнительная память класса
	wc_main.cbWndExtra = 0; // Дополнительная память окна
	// Pегистрация класса окна.
	RegisterClass(&wc_main);
	// Создание главного окна приложения.
	hMainWnd = CreateWindow(
		ClassName1, // Имя класса окон
		AppTitle1, // Заголовок окна
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, // Стиль окна
		0, // X-координата
		0, // Y-координата
		cx, // Ширина окна
		cy, // Высота окна
		NULL, // Дескриптор окна-родителя
		NULL, // Дескриптор меню окна
		hInst, // Дескриптор экз. приложения
		NULL); // Дополнительная информация




	if (!hMainWnd)
	{
		// Окно не создано, выдается сообщение.
		MessageBox(NULL, "Window create error", AppTitle1, MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	// Отображение окна и обновление его
	ShowWindow(hMainWnd, SW_NORMAL);
	UpdateWindow(hMainWnd);






	

	GetWindowRect(hMainWnd, &rect);
	int x, y,cx1,cy1;

	cx1 = GetSystemMetrics(SM_CXMINIMIZED);
	cy1 = GetSystemMetrics(SM_CYMINIMIZED);

	x = rect.right-cx1;
	y = rect.top+20;
	
	





	hInst = hInstance; // Сохран. дескриптора экз. прилож.
	ZeroMemory(&wc_popup, sizeof(wc_popup)); // Очистка полей структуры
	// Заполнение полей стр-ры WNDCLASS
	wc_popup.lpszClassName = ClassName2; // Имя класса окон
	//Адрес оконной ф-ции
	wc_popup.lpfnWndProc = (WNDPROC)PopupWndProc;
	wc_popup.style = CS_HREDRAW | CS_VREDRAW; // Стиль класса окон
	wc_popup.hInstance = hInstance; // Экземпляр приложения
	// Пиктограмма для окон
	wc_popup.hIcon = LoadIcon(NULL, IDI_INFORMATION);
	// Курсор мыши для окон
	wc_popup.hCursor = LoadCursor(NULL, IDC_ARROW);
	// Кисть для окон
	wc_popup.hbrBackground = SECOND_BRUSH;
	wc_popup.lpszMenuName = NULL; // Ресурс меню окон
	wc_popup.cbClsExtra = 0; // Дополнительная память класса
	wc_popup.cbWndExtra = 0; // Дополнительная память окна
	// Pегистрация класса окна.
	RegisterClass(&wc_popup);




	hWndPopup = CreateWindow(ClassName2,
		AppTitle2, WS_POPUPWINDOW |
		WS_CAPTION | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | WS_BORDER,x,y,cx1,cy1,
		hMainWnd, NULL, hInstance, NULL);

	if (hWndPopup == NULL)
	{ // Уничтожение главного окна при неудаче
		DestroyWindow(hMainWnd);
		return FALSE;
	}

	ShowWindow(hWndPopup, SW_RESTORE);

	UpdateWindow(hWndPopup);













	int cx2, cy2,x1, y1;
	cx2 = cx / 25;
	cy2 = cy / 25;
	
	x1 = cx / 2;
	y1 = cy / 4;



	hInst = hInstance; // Сохран. дескриптора экз. прилож.
	ZeroMemory(&wc_child, sizeof(wc_child)); // Очистка полей структуры
	// Заполнение полей стр-ры WNDCLASS
	wc_child.lpszClassName = ClassName3; // Имя класса окон
	//Адрес оконной ф-ции
	wc_child.lpfnWndProc = (WNDPROC)ChildWndProc;
	wc_child.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // Стиль класса окон
	wc_child.hInstance = hInstance; // Экземпляр приложения
	// Пиктограмма для окон
	wc_child.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
	// Курсор мыши для окон
	wc_child.hCursor = LoadCursor(NULL,IDC_APPSTARTING);
	// Кисть для окон
	wc_child.hbrBackground = THIRD_BRUSH;
	wc_child.lpszMenuName = NULL; // Ресурс меню окон
	wc_child.cbClsExtra = 0; // Дополнительная память класса
	wc_child.cbWndExtra = 0; // Дополнительная память окна
	// Pегистрация класса окна.
	RegisterClass(&wc_child);



	hWndChild = CreateWindow(ClassName3,
		AppTitle3, WS_CHILDWINDOW |
		WS_CAPTION | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | WS_EX_MDICHILD | WS_CLIPSIBLINGS, x1, y1, cx2, cy2,
		hMainWnd, NULL, hInstance, NULL);

	if (hWndChild == NULL)
	{ // Уничтожение главного окна при неудаче
		DestroyWindow(hMainWnd);

		DestroyWindow(hWndPopup);
		return FALSE;
	}
	ShowWindow(hWndChild, SW_SHOW);
	UpdateWindow(hWndChild);





	// Запуск цикла обработки очереди сообщений.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Преобразов. сообщений клавиатуры в символьные
		TranslateMessage(&msg);
	
		DispatchMessage(&msg);
	}
	return msg.wParam; // Завершение работы приложения





}


// --- Оконная функция главного окна



LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC dc;
	dc = GetDC(hWnd);
	int cycaption,cymenu;
	FLASHWINFO fi;

	char buffer0[50] ="Высота заголовка = ";
	char  buffer2[50] = " \nВысота меню = ";
	char buffer[_MAX_U64TOSTR_BASE2_COUNT] ;
	char buffer1[_MAX_U64TOSTR_BASE2_COUNT];
	cycaption = GetSystemMetrics(SM_CYCAPTION);
	cymenu = GetSystemMetrics(SM_CYMENU);

	
	_itoa_s(cycaption, buffer, _countof(buffer), 10);

	strcat_s(buffer0, sizeof(buffer0), buffer);

	
	_itoa_s(cymenu, buffer1, _countof(buffer1), 10);

	strcat_s(buffer2, sizeof(buffer2), buffer1);


	strcat_s(buffer0, sizeof(buffer0), buffer2);

	fi.cbSize = sizeof(fi);
	fi.hwnd = hWnd; // здесь подставляешь HWND нужного окна
	fi.dwFlags = FLASHW_ALL;
	fi.uCount = 4; // мигнуть 4 раза
	fi.dwTimeout = 0; // мигать с частотой курсора


	switch (uMsg)
	{

	case WM_LBUTTONDBLCLK:
	
		MessageBox(hWnd,buffer0, "Информационное сообщение", MB_OK);
		break;

	case WM_RBUTTONDBLCLK:
		FlashWindowEx(&fi);
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;




	default:

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}



// --- Оконная функция временное окно 
LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	


	GetWindowRect(hMainWnd, &rect);
	int x1, y1,x2,y2, cx1, cy1,cx2,cy2;

	cx1 = GetSystemMetrics(SM_CXMINIMIZED);
	cy1 = GetSystemMetrics(SM_CYMINIMIZED);

	x1 = rect.right - cx1;
	y1 = rect.top;

	cx2 = GetSystemMetrics(SM_CXFULLSCREEN);
	cy2 = GetSystemMetrics(SM_CYFULLSCREEN);
	cx2 = cx2 / 16;
	cy2 = cy2 / 16;

	x2 = rect.left+20;
	y2 = rect.bottom-120;

	switch (uMsg)
	{

	case WM_LBUTTONDOWN:
		MoveWindow(hWnd, x1, y1, cx1, cy1, false);

		break;
	case WM_RBUTTONDOWN:

		MoveWindow(hWnd, x2, y2, cx2, cy2, false);

		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}




// --- Оконная функция дочернего окна
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	int x1, y1,x2,y2, cx1, cy1,cx,cy;
	x1 = rect.right-200;
	y1 = rect.bottom-200;
	
	cx = GetSystemMetrics(SM_CXFULLSCREEN);
	cy = GetSystemMetrics(SM_CXFULLSCREEN);
	cx1 = cx / 25;
	cy1 = cy / 25;
	x2 = cx / 2;
	y2 = cy / 4;


	switch (uMsg)
	{
	
		
	case WM_LBUTTONDBLCLK:


		MoveWindow(hWnd, x1, y1, cx1, cy1, true);
		break;

	case WM_RBUTTONDBLCLK:
		MoveWindow(hWnd, x2, y2, cx1, cy1, true);
		break;
		
	default:

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}
