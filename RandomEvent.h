#include <iostream>
#include <string>

using namespace std;

#ifndef RANDOMEVENT_H
#define RANDOMEVENT_H

class RandomEvent {
    protected:
        double success_rate;
        string description;
        string success_description;
        string failure_description;
        bool chosen_option;
    public:
        RandomEvent();
        RandomEvent(double, string, string, string);
        double get_success_rate();
        string get_description();
        string get_success_description();
        string get_failure_description();
        bool get_chosen_option();
        void set_success_rate(double);
        void set_description(string);
        void set_success_description(string);
        void set_failure_description(string);

        void set_chosen_option(bool);
};

#endif