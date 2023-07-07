// MovingAverageFilter.cpp

#include "MovingAverageFilter.h"

MovingAverageFilter::MovingAverageFilter(size_t window_size): window_size_(window_size) {
    if (window_size == 0) 
        throw std::invalid_argument("Window size must be > 0");
}

void MovingAverageFilter::addData(int data) {
    if(dataQueue.size() == window_size) {
        sum -= dataQueue.front();
        dataQueue.pop_front();
    }

    dataQueue.push_back(data);
    sum += data;
}

double MovingAverageFilter::getAverage() const {
    if (dataQueue.empty()) 
        throw std::domain_error("No data available");
    return static_cast<double>(sum) / dataQueue.size();
}