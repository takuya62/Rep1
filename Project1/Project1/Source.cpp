#include<Windows.h>
#include<gl/GL.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL(HWND hwnd, HDC *hdc, HGLRC *hrc);
void DisableOpenGL(HWND hwnd, HDC hdc, HGLRC hrc);
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int icmdshow) {
	WNDCLASS wc; HWND hwnd; HDC hdc; HGLRC hrc; MSG msg; bool bquit = false; float theta = 1.0f;
	wc.style = CS_OWNDC; wc.lpfnWndProc = WndProc; wc.cbClsExtra = 0; wc.cbWndExtra = 0; wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0; wc.lpszClassName = "a"; RegisterClass(&wc);
	hwnd = CreateWindow("a", "b", WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE, 0, 0, 256, 256, NULL, NULL, hinstance, NULL);
	EnableOpenGL(hwnd, &hdc, &hrc);
	while (!bquit) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)bquit = true; else { TranslateMessage(&msg); DispatchMessage(&msg); }
		}
		else {
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f); glClear(GL_COLOR_BUFFER_BIT);
			glPushMatrix(); glRotatef(theta, 0.0f, 0.0f, 1.0f); glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.87f, -0.5f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
			glEnd(); glPopMatrix(); SwapBuffers(hdc); theta += 1.0f; Sleep(1);
		}
	}
	DisableOpenGL(hwnd, hdc, hrc); DestroyWindow(hwnd); return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	switch (message) {
	case WM_CREATE:return 0; case WM_CLOSE:PostQuitMessage(0); return 0; case WM_DESTROY:return 0;
	case WM_KEYDOWN:switch (wparam) { case VK_ESCAPE: PostQuitMessage(0); return 0; }return 0;
	default:return DefWindowProc(hwnd, message, wparam, lparam);
	}
};
void EnableOpenGL(HWND hwnd, HDC *hdc, HGLRC *hrc) {
	PIXELFORMATDESCRIPTOR pfd; int iFormat; *hdc = GetDC(hwnd); ZeroMemory(&pfd, sizeof(pfd));
	pfd.nVersion = 1; pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA; pfd.cColorBits = 24; pfd.cDepthBits = 16; pfd.iLayerType = PFD_MAIN_PLANE;
	iFormat = ChoosePixelFormat(*hdc, &pfd); SetPixelFormat(*hdc, iFormat, &pfd);
	*hrc = wglCreateContext(*hdc); wglMakeCurrent(*hdc, *hrc);
};
void DisableOpenGL(HWND hwnd, HDC hdc, HGLRC hrc) {
	wglMakeCurrent(NULL, NULL); wglDeleteContext(hrc); ReleaseDC(hwnd, hdc);
};