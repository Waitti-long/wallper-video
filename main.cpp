#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

char *cmd = nullptr;

void startVideo();
HWND get_wallpaper_window();

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "This Program Receive a Filename(Video) as Param." << endl;
        return -1;
    }
    cmd = new char[1024];
    sprintf(cmd, "ffplay %s -loop 0 -loglevel quiet", argv[1]);
    thread t(startVideo);
    ::Sleep(1000);
    HWND ffplay = nullptr;
    ffplay = ::FindWindow("SDL_app", nullptr);
    auto wallpaper = get_wallpaper_window();
    ::SetParent(ffplay, wallpaper);
    LONG_PTR Style = ::GetWindowLongPtr(ffplay, GWL_STYLE);
    Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
    ::SetWindowLongPtr(ffplay, GWL_STYLE, Style);
    ::MoveWindow(ffplay, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), false);
    cout << "Program Running~ Press Any Key To Exit." << endl;
    getchar();
    ::SendMessage(ffplay, WM_CLOSE, 0, 0);
    ::TerminateThread((HANDLE)t.native_handle(), 0);
}

void startVideo()
{
    system(cmd);
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    HWND p = FindWindowEx(hwnd, NULL, "SHELLDLL_DefView", NULL);
    HWND *ret = (HWND *)lParam;
    if (p)
    {
        // Gets the WorkerW Window after the current one.
        *ret = FindWindowEx(NULL, hwnd, "WorkerW", NULL);
    }
    return true;
}

HWND get_wallpaper_window()
{
    // Fetch the Progman window
    HWND progman = FindWindow("ProgMan", NULL);
    // Send 0x052C to Progman. This message directs Progman to spawn a
    // WorkerW behind the desktop icons. If it is already there, nothing
    // happens.
    SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
    // We enumerate all Windows, until we find one, that has the SHELLDLL_DefView
    // as a child.
    // If we found that window, we take its next sibling and assign it to workerw.
    HWND wallpaper_hwnd = nullptr;
    EnumWindows(EnumWindowsProc, (LPARAM)&wallpaper_hwnd);
    // Return the handle you're looking for.
    return wallpaper_hwnd;
}