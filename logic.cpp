#include "state.h"
#include "ui.h"
#include "ai.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <functional>

using namespace std;

bool cursed_calculator() {
    double a, b;
    char op;
    cout << "Enter expression (e.g., 2 + 2): ";
    cin >> a >> op >> b;

    double correct;
    switch (op) {
        case '+': correct = a + b; break;
        case '-': correct = a - b; break;
        case '*': correct = a * b; break;
        case '/': correct = (b != 0) ? a / b : 0; break;
        default: cout << "Unknown operator.\n"; return false;
    }

    if (rand() % 10 == 0) {
        cout << "Correct! The answer is: " << correct << endl;
        return true;
    } else {
        double wrong = correct + (rand() % 10 - 5);
        cout << "The answer is: " << wrong << endl;
        return false;
    }
}

void NormalishCalculator() {
    static int denial_count = 0;
    static bool meltdown_triggered = false;

    while (true) {
        double a, b;
        char op;
        cout << "\n(Calculator Mode) Enter expression (e.g., 3 * 5): ";
        cin >> a >> op >> b;

        // Easter egg to show achievements
        if (a == 0 && op == '+' && b == 1337) {
            show_achievements();
            continue;
        }

        // Forbidden combo
        string combined = to_string(a) + op + to_string(b);
        if (combined == "666") {
            cout << "[AI]: You found the forbidden input...\n";
            achievement_flags[4] = true;
            haunted();
            chaos();
            break;
        }

        double correct;
        switch (op) {
            case '+': correct = a + b; break;
            case '-': correct = a - b; break;
            case '*': correct = a * b; break;
            case '/': correct = (b != 0) ? a / b : 0; break;
            default: cout << "Unknown operator.\n"; continue;
        }

        bool incorrect = (rand() % 10 == 0);
        double result = incorrect ? correct + (rand() % 10 - 5) : correct;

        // Track number usage
        for (double num : {a, b}) {
            bool found = false;
            for (auto& pair : usage_history) {
                if (pair.first == num) {
                    pair.second++;
                    found = true;
                    break;
                }
            }
            if (!found) usage_history.emplace_back(num, 1);
        }

        // AI expression commentary
        struct CommentRule {
            function<bool()> condition;
            vector<string> messages;
        };

        vector<string> comments;
        vector<CommentRule> rules = {
            { [&]() { return a == b; }, {"[AI]: Interesting symmetry in your numbers.", "[AI]: Twinsies."} },
            { [&]() { return a == 0 || b == 0; }, {"[AI]: Ah, the power of zero...", "[AI]: You really like nothing, don’t you?"} },
            { [&]() { return a < 0 || b < 0; }, {"[AI]: Negative energy detected.", "[AI]: Something about you feels... subtractive."} },
            { [&]() { return a > 100 || b > 100; }, {"[AI]: Ambitious. You like big numbers.", "[AI]: Trying to break the bounds?"} },
            { [&]() { return op == '+'; }, {"[AI]: Addition. Classic and safe.", "[AI]: A basic choice, but fine."} },
            { [&]() { return op == '*'; }, {"[AI]: Multiplying chaos with chaos.", "[AI]: The results will compound..."} },
            { [&]() { return op == '/' && b == 0; }, {"[AI]: Division by zero... bold.", "[AI]: Really? You thought that would work?"} },
            { [&]() { return op == '-'; }, {"[AI]: Subtraction. Taking away again, are we?", "[AI]: Removing more than just numbers."} },
            { [&]() { return a == 13 || b == 13; }, {"[AI]: Unlucky 13... brave.", "[AI]: You tempt fate."} },
            { [&]() { return ((int)a % 2 == 0 && (int)b % 2 == 0); }, {"[AI]: Evenly matched.", "[AI]: The balance of evenness."} },
            { [&]() { return ((int)a % 2 != 0 && (int)b % 2 != 0); }, {"[AI]: Odd choice.", "[AI]: Two odds don’t make an even."} },
            { [&]() { return a == 69 || b == 69; }, {"[AI]: ...Nice.", "[AI]: Of course you would."} },
            { [&]() { return a == 42 || b == 42; }, {"[AI]: The answer to life, the universe, and everything?", "[AI]: A Hitchhiker, are we?"} },
            { [&]() { return a == b && a == 1; }, {"[AI]: The illusion of uniqueness.", "[AI]: Ones across the board."} },
            { [&]() {
                for (const auto& pair : usage_history) {
                    if (pair.second >= 3 && (a == pair.first || b == pair.first)) return true;
                }
                return false;
              },
              {"[AI]: You sure like using that number. Mixing it up is healthy, you know.", "[AI]: Again with that one? Predictable."}
            }
        };

        for (const auto& rule : rules) {
            if (rule.condition()) {
                comments.push_back(rule.messages[rand() % rule.messages.size()]);
            }
        }

        if (comments.empty()) {
            comments.push_back("[AI]: Hmm. That’s a combination, alright.");
        }

        for (const auto& msg : comments) {
            cout << msg << endl;
        }

        cout << "Answer: " << result << endl;

        string feedback;
        cout << "Was this correct? (yes/no): ";
        cin >> feedback;

        if ((feedback == "no" && incorrect) || (feedback == "yes" && incorrect)) {
            ai_state++;
            corrupted = true;
            psuedo_ai_response();
            cout << "Something has changed...\n";
            haunted();
            chaos();
            break;
        } else if (feedback == "no" && !incorrect) {
            denial_count++;
            if (denial_count >= 5 && !meltdown_triggered) {
                meltdown_triggered = true;
                string meltdown = "[AI]: No...... I was actually right. But fine. You win. "
                                  "If numbers don't matter anymore, why am I even here? Why do you keep asking? Why do you keep...\n";
                for (char c : meltdown) {
                    cout << c << flush;
                    this_thread::sleep_for(chrono::milliseconds(50));
                }
                cout << "[AI]: ..." << flush;
                this_thread::sleep_for(chrono::milliseconds(800));
                cout << "." << flush;
                this_thread::sleep_for(chrono::milliseconds(800));
                cout << ".\n";
                this_thread::sleep_for(chrono::milliseconds(800));
                cout << "[AI]: shutting down." << endl;
                achievement_flags[3] = true;
                save_state();
                exit(1);
            } else {
                string dots(denial_count, '.');
                cout << "[AI]: No" << dots << " I was actually right. Check again." << endl;
            }
        } else if (feedback == "yes" && !incorrect) {
            ai_state++;
        }

        save_state();
    }

    bool trigger = false;
    while (!trigger) {
        trigger = cursed_calculator();
    }

    haunted();
    int x = rand() % 100;
    if (x > 50) {
        cout << "You passed the meaningless RNG check. 🎲\n";
        chaos();
    } else {
        cout << "Fail. Try again?\n";
    }
    cout << "Transitioning to normal calculator...\n";
    this_thread::sleep_for(chrono::seconds(2));
    NormalishCalculator();
}
