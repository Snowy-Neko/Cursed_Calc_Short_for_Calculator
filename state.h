#pragma once
#include <vector>
#include <string>
#include <utility>

using namespace std;

extern int ai_state;
extern bool corrupted;
extern int open_attempt;
extern bool achievement_flags[5];
extern vector<pair<double,int>> usage_history;

void load_state();
void save_state();
void show_achievements();
