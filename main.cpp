#include <iostream>
#include "StockData.h"
#include "SMA.h"

int main()
{
    std::string symbol = "META";

    // Replace with Alpha Vantage API key
    std::string api_key = "DXMJ7O7ITS7K3JFJ";

    StockData stock_data(symbol, api_key);
    stock_data.fetchData();

    int short_period = 10;
    int long_period = 30;
    SMA sma(stock_data, short_period, long_period);
    sma.calculateSMA();
    sma.generateSignals();

    // Print buy and sell signals
    sma.printSignals();

    return 0;
}
