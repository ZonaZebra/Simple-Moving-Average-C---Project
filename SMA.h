#ifndef SMA_H
#define SMA_H

#include "StockData.h"
#include <vector>

class SMA
{
public:
    SMA(const StockData &stock_data, int short_period, int long_period);
    void calculateSMA();
    void generateSignals();
    void printSignals() const;
    const std::vector<double> &getShortSMA() const;
    const std::vector<double> &getLongSMA() const;

private:
    int short_period;
    int long_period;
    const StockData &stock_data;
    std::vector<double> short_sma;
    std::vector<double> long_sma;
    std::vector<std::string> signals;
};

#endif // SMA_H
