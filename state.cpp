#include "state.h"
#include <fstream>
#include <iostream>

using namespace std;

int ai_state = 0;
bool corrupted = false;
int open_attempt = 0;
bool achievement_flags[5] = {false};
vector<pair<double,int>> usage_history;

void load_state()
{
    usage_history.clear();
    ifstream file("state.txt");
    if (file.is_open())
    {
        file >> ai_state >> corrupted >> open_attempt;
        for (int i = 0; i < 5; i++) file >> achievement_flags[i]; //line 19 and 20 combined so I dont have to type more
        double num; int count;
        while (file >> num >> count)
            usage_history.emplace_back(num, count);
        file.close();
    }
}

void save_state()
{
    ofstream file("state.txt");
    if (file.is_open())
    {
        file << ai_state << "\n" << corrupted << "\n" << open_attempt;
        for (bool flag : achievement_flags) file << ' ' << flag;
        for (const auto& pair : usage_history)
            file << '\n' << pair.first << ' ' << pair.second;
        file.close();

    }
}

void show_achievements()
{
    vector<string> names =
    {
        "Used the number 420... NICE",
        "Used the number 69",
        "Used the funny number 25",
        "Melted the ai",
        "Found the forbidden input (666)"
    };
    cout << "\n ===Achievement Log=== \n";
    for (int i = 0; i < 5; ++i)
        cout << "[" << (achievement_flags[i] ? "\/" : " ") << "]" << names[i] << "\n";
    cout << "=================\n" << endl;

}
