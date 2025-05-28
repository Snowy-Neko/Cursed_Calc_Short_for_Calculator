#include <iostream>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

using namespace std;

void haunted()
{
    std::string messages[] =
        {
        "Meoooooooowwwww...",
        "Something's terribly wrong...",
        "Did you hear it?",
        "This is not normal for a program :<",
        "RUN. NOW."
        };

    for (const auto& msg : messages)
        {
            cout << msg << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
}

void chaos()
{
#ifdef _WIN32
    MessageBox(NULL, "The windows void stares back.", "???", MB_OK|MB_ICONWARNING);
    MessageBox(NULL, "You shouldn't have ran this program!", "ERROR", MB_OK|MB_ICONERROR);
#endif
}
