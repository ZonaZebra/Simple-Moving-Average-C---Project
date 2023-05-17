#include "StockData.h"
#include <iostream>
#include "json.hpp" // Include the nlohmann/json library

using json = nlohmann::json;

StockData::StockData(const std::string &symbol, const std::string &api_key) : symbol(symbol), api_key(api_key) {}

size_t StockData::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

void StockData::fetchData()
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol=" + symbol + "&apikey=" + api_key + "&datatype=json";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "Error: curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            json jsonData = json::parse(readBuffer);
            auto time_series = jsonData["Time Series (Daily)"];

            for (auto it = time_series.begin(); it != time_series.end(); ++it)
            {
                DataPoint data_point;
                data_point.date = it.key();
                data_point.close = std::stod(static_cast<std::string>(it.value()["4. close"]));
                stock_data.push_back(data_point);
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

const std::vector<StockData::DataPoint> &StockData::getStockData() const
{
    return stock_data;
}
