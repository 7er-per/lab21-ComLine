#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

HWND textfi,n1,n2,B,L,K,H;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

		case WM_CREATE:{
			textfi = CreateWindowA("STATIC","Please input two number",
									WS_VISIBLE | WS_CHILD | WS_BORDER ,
									25, // x
									20, // y
									170, //w
									20,  //h
									hwnd,NULL,NULL,NULL);

			n1 = CreateWindowA("EDIT","",
									WS_VISIBLE | WS_CHILD | WS_BORDER ,
									42, // x
									45, // y
									130, //w
									20,  //h
									hwnd,NULL,NULL,NULL);
			
			n2 = CreateWindowA("EDIT","",
									WS_VISIBLE | WS_CHILD | WS_BORDER ,
									42, // x
									70, // y
									130, //w
									20,  //h
									hwnd,NULL,NULL,NULL);
			B = CreateWindowA("BUTTON","+",
									WS_VISIBLE | WS_CHILD | WS_BORDER ,
									35, // x
									95, // y
									30, //w
									35,  //h
									hwnd,(HMENU) 1,NULL,NULL);
			L = CreateWindowA("BUTTON","-",
									WS_VISIBLE | WS_CHILD | WS_BORDER ,
									75, // x
									95, // y
									30, //w
									35,  //h
									hwnd,(HMENU) 2,NULL,NULL);
			K = CreateWindowA("BUTTON","*",
									WS_VISIBLE | WS_CHILD | WS_BORDER ,
									115, // x
									95, // y
									30, //w
									35,  //h
									hwnd,(HMENU) 3,NULL,NULL);
			H = CreateWindowA("BUTTON","/",
									WS_VISIBLE | WS_CHILD | WS_BORDER ,
									155, // x
									95, // y
									30, //w
									35,  //h
									hwnd,(HMENU) 4,NULL,NULL);

			break;
		}

		case WM_COMMAND:{
			char r1[30], r2[30] , resultText[50];
            float num1, num2, result;

			GetWindowTextA(n1, r1, sizeof(r1));
            GetWindowTextA(n2, r2, sizeof(r2));

			num1 = atof(r1);
            num2 = atof(r2);
			
			switch (LOWORD(wParam)) {
                case 1:  
                    result = num1 + num2;
                    sprintf(resultText, "%f", result);
                    MessageBoxA(hwnd, resultText, "Result", MB_OK);
                    break;

                case 2:  
                    result = num1 - num2;
                    sprintf(resultText, "%f", result);
                    MessageBoxA(hwnd, resultText, "Result", MB_OK);
                    break;

                case 3:  
                    result = num1 * num2;
                    sprintf(resultText, "%f", result);
                    MessageBoxA(hwnd, resultText, "Result", MB_OK);
                    break;

                case 4:  
                    if (num2 == 0) {
                        MessageBoxA(hwnd, "Unable to find value!", "Result", MB_OK);
                    } else {
                        result = num1 / num2;
                        sprintf(resultText, "%f", result);
                        MessageBoxA(hwnd, resultText, "Result", MB_OK);
                    }
                    break;
            }

			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(192, 229, 146));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",
		WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/

	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
