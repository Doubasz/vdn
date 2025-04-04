#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> last_time;
    double delay_seconds;
    

public:
    Timer(double delay);
    bool canProceed();
    void reset();
    char last_input;
};

#endif // TIMER_H
