#include <iostream>
#include <string>

using namespace std;

#ifndef RANDOMEVENT_H
#define RANDOMEVENT_H

class RandomEvent {
    protected:
        int success_rate;
        string description;
        bool chosen_option;
    public:
        RandomEvent();
        RandomEvent(int, string);
        int get_success_rate();
        string get_description();
        bool get_chosen_option();
        void set_success_rate(int);
        void set_description(string);
        void set_chosen_option(bool);
};

#endif