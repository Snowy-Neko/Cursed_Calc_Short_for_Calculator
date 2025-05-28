#include "state.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

void ai_open_message()
{
    vector<string> greetings =
    {
        "[AI]:",
        "[AI]:",
        "[AI]:",
        "[AI]:",
        "[AI]:",
        "[AI]:",
        "[AI]:",
        "[AI]:",
        "[AI]:",
        "[AI]:",
    };

    int capped = min(open_attempt, (int)greetings.size() -1);
    cout << greetings[capped] << endl;

}

void psuedo_ai_response()
{
    vector<string> aiLevels[] =
    {
        {"Just another Calc", "another"},
        {"Just another Calc", "another"},
        {"Just another Calc", "another"},
        {"Just another Calc", "another"},
        {"Just another Calc", "another"},
    };
    int level = min(ai_state / 2, 4);
    const auto& responses = aiLevels[level];
    string msg = responses[rand()% responses.size()];
    cout << "[AI v" << level << "]" << msg << endl;
};

