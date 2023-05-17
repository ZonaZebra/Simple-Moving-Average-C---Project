#ifndef STOCKDATA_H
#define STOCKDATA_H

#include <vector>
#include <string>
#include <curl/curl.h>
#include "json.hpp"

class StockData
{
public:
    struct DataPoint
    {
        std::string date;
        double close;
    };

    StockData(const std::string &symbol, const std::string &api_key);
    void fetchData();
    const std::vector<DataPoint> &getStockData() const;

private:
    std::string symbol;
    std::string api_key;
    std::vector<DataPoint> stock_data;
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif // STOCKDATA_H