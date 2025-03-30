#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

class Record{
  public:
    std::chrono::system_clock::time_point time;
    int subscribers = 0;
    int dropouts = 0;
    int paymentAmount = 0;
    int amountUsed = 0;
    int salesAmount = 0;

    Record() = default;
    Record(std::chrono::system_clock::time_point time, int subscribers, int dropouts,
           int paymentAmount, int amountUsed, int salesAmount) 
          : time(time), subscribers(subscribers), dropouts(dropouts),
            paymentAmount(paymentAmount), amountUsed(amountUsed), salesAmount(salesAmount){}
    
    void init(){
      time = std::chrono::system_clock::now();
      subscribers = 0;
      dropouts = 0;
      paymentAmount = 0;
      amountUsed = 0;
      salesAmount = 0;
    }

    std::string toString() const {
      auto timeT = std::chrono::system_clock::to_time_t(time);
      std::ostringstream oss;
      oss << "Time: " << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S")
          << ", Subscribers: " << subscribers
          << ", Dropouts: " << dropouts
          << ", PaymentAmount: " << paymentAmount
          << ", amountUsed: " << amountUsed
          << ", salesAmount: " << salesAmount;
      return oss.str();
    }

    bool isEmpty() const {
      return subscribers == 0 && dropouts == 0 && paymentAmount == 0 &&
             amountUsed == 0 && salesAmount == 0;
    }
};

#endif // RECORD_H