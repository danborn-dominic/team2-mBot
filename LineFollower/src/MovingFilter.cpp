#include "MovingFilter.h"

MovingAverageFilter::MovingAverageFilter(size_t window_size): window_size_(window_size) {
    if (window_size == 0) 
        throw std::invalid_argument("Window size must be > 0");
}

void MovingAverageFilter::addData(int data) {
    if(dataQueue_.size() == window_size_) {
        sum_ -= dataQueue_.front();
        dataQueue_.pop_front();
    }

    dataQueue_.push_back(data);
    sum_ += data;
}

double MovingAverageFilter::getAverage() const {
    if (dataQueue_.empty()) 
        throw std::domain_error("No data available");
    return static_cast<double>(sum_) / dataQueue_.size();
}