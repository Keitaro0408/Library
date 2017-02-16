#include <crtdbg.h>
#include <Library\Window.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	Lib::Window::GetInstance()->InitWindow(hInst,WINDOW_WIDTH,WINDOW_HEIGHT,"test");

	MSG Msg;
	ZeroMemory(&Msg, sizeof(Msg));
	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			//if (pSceneManager->Run())
			//{
			//	break;
			//}
		}
	}

	//delete pSceneManager;

	return (INT)Msg.wParam;
}
