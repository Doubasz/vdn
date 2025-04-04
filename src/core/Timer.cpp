#include "Timer.h"

Timer::Timer(double delay) : delay_seconds(delay) {
    last_time = std::chrono::high_resolution_clock::now() - std::chrono::milliseconds(int(delay * 1000)); // Initialiser à une valeur passée
    last_input = '/';
}

bool Timer::canProceed() {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - last_time;
    return elapsed.count() >= delay_seconds;
}

void Timer::reset() {
    last_time = std::chrono::high_resolution_clock::now();
}
