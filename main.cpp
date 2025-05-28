#include "state.h"
#include "ai.h"
#include "ui.h"
#include "logic.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>
#include <thread>
#include <sstream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

#define SPOOKY cout
//#define FOREVER for(;;)
#define YES true
#define NO false
#define maybe main //LMAO

using namespace std;

int maybe(int argc, char* argv[])
{
    srand(time(0));
    load_state();
    open_attempt++;
    ai_open_message();

    if (corrupted) {
        SPOOKY << "[AI]: Welcome back. You thought you left, didn’t you?\n";
    }

    save_state();

    bool trigger = false;
    while (!trigger) {
        trigger = cursed_calculator();
    }

    haunted();

    int x = rand() % 100;
    if (x > 50) {
        SPOOKY << "You passed the meaningless RNG check. 🎲\n";
        chaos();
    } else {
        SPOOKY << "Fail. Try again?" << endl;
    }

    SPOOKY << "Transitioning to normal calculator..." << endl;
    this_thread::sleep_for(chrono::seconds(2));

    NormalishCalculator();

    SPOOKY << "Back to the abyss. Goodbye.\n";
    return 0; //this should never work LKMAO
}
