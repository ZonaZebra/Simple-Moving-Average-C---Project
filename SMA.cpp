#include "SMA.h"
#include <iostream>

SMA::SMA(const StockData &stock_data, int short_period, int long_period)
    : stock_data(stock_data), short_period(short_period), long_period(long_period) {}

void SMA::calculateSMA()
{
    const auto &stock_data_points = stock_data.getStockData();

    for (size_t i = 0; i < stock_data_points.size(); ++i)
    {
        if (i >= short_period - 1)
        {
            double short_sum = 0.0;
            for (int j = 0; j < short_period; ++j)
            {
                short_sum += stock_data_points[i - j].close;
            }
            short_sma.push_back(short_sum / short_period);
        }
        else
        {
            short_sma.push_back(0.0);
        }

        if (i >= long_period - 1)
        {
            double long_sum = 0.0;
            for (int j = 0; j < long_period; ++j)
            {
                long_sum += stock_data_points[i - j].close;
            }
            long_sma.push_back(long_sum / long_period);
        }
        else
        {
            long_sma.push_back(0.0);
        }
    }
}

void SMA::generateSignals()
{
    for (size_t i = 1; i < short_sma.size(); ++i)
    {
        if (short_sma[i] > long_sma[i] && short_sma[i - 1] <= long_sma[i - 1])
        {
            signals.push_back("Buy");
        }
        else if (short_sma[i] < long_sma[i] && short_sma[i - 1] >= long_sma[i - 1])
        {
            signals.push_back("Sell");
        }
        else
        {
            signals.push_back("-");
        }
    }
}

void SMA::printSignals() const
{
    for (size_t i = 0; i < signals.size(); ++i)
    {
        std::cout << stock_data.getStockData()[i].date << " - " << signals[i] << std::endl;
    }
}

const std::vector<double> &SMA::getShortSMA() const
{
    return short_sma;
}

const std::vector<double> &SMA::getLongSMA() const
{
    return long_sma;
}
