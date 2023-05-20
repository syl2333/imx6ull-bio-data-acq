#ifndef __CIRCULAR_BUFF_H__
#define __CIRCULAR_BUFF_H__

#include <vector>
#include <mutex>
#include <condition_variable>

#include "log.h"

class CircularBuffer {
public:
    CircularBuffer(size_t size) : buffer_(size), head_(0), tail_(0), max_size_(size) { }

    void put(int value) {
        std::lock_guard<std::mutex> lock(mutex_);
        buffer_[head_] = value;
        head_ = (head_ + 1) % max_size_;

        if(head_ == tail_) {
            is_full_ = true;
        }
    }

    int get() {
        std::lock_guard<std::mutex> lock(mutex_);
        if(empty()) {
            return -1; // or throw
        }

        int val = buffer_[tail_];
        tail_ = (tail_ + 1) % max_size_;
        is_full_ = false;
        return val;
    }

    std::vector<int> copy_all() {
        std::lock_guard<std::mutex> lock(mutex_);
        std::vector<int> all_data;
        std::copy(buffer_.begin() + head_,buffer_.end(),std::back_inserter(all_data));
        std::copy(buffer_.begin(),buffer_.begin() + head_ - 1,std::back_inserter(all_data));
        return all_data;
    }

    uint32_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        if(is_full_) {
            return max_size_;
        } else if(head_ >= tail_) {
            return head_ - tail_;
        } else {
            return max_size_ + head_ - tail_;
        }
    }


    bool empty() const {
        return !is_full_ && (head_ == tail_);
    }

    bool full() const {
        Logger::getInstance().infoStream() << "缓冲区实际大小：" << size();
        return size() == max_size_;
    }

private:
    std::vector<int> buffer_;
    bool is_full_ = false;
    size_t head_;
    size_t tail_;
    size_t max_size_;
    mutable std::mutex mutex_;
};


#endif //
