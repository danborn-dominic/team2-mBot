#ifndef MOVING_AVERAGE_FILTER_H
#define MOVING_AVERAGE_FILTER_H

#include <deque>
#include <stdexcept>

class MovingAverageFilter
{
    public:
        MovingAverageFilter(size_t window_size);
        void addData(int data);
        double getAverage() const;

    private:
        std::deque<int> dataQueue_;
        size_t window_size_;
        int sum_ = 0;
};

#endif // MOVING_AVERAGE_FILTER_H