#include <iostream>
#include <tensorflow/c/c_api.h>
#include "stock.h"
#include <map>

#define STOCKS 6

int main() {
	std::cout << "Tensor Flow C Library\nVersion:\t" << TF_Version() << '\n' << '\n';
	
	std::map<std::string, int> stocks_mapping;
	
	stocks_mapping["AAPL"] = 1668;
	stocks_mapping["GOOG"] = 1560;
	stocks_mapping["IBM"] = 1549;
	stocks_mapping["TI"] = 1581;
	stocks_mapping["VZ"] = 1559;
	stocks_mapping["XOM"] = 1556;

	// Building stock profile
	std::vector<Stock> stocks;
	stocks.reserve(STOCKS);
	
	int index = 0;
	for (const auto& pair : stocks_mapping) {
		std::string ticker = pair.first;
		const unsigned int data_size = pair.second;
		try {
			stocks.emplace_back(ticker, "src/data/5-1-2017/" + ticker + ".csv", data_size);
		} catch (const std::runtime_error& e) {
			std::cerr << "Error: " << e.what() << '\n';
		}
		index++;
	}
	
	// Calculating covarience between pairs of stocks	
	float covarience[STOCKS][STOCKS];
	for (unsigned int i = 0; i < STOCKS; i++) {
		for (unsigned int j = 0; j <= i; j++) {
			float cov = stocks[i].CalculateCovarience(stocks[j]);
			covarience[i][j] = cov;
			covarience[j][i] = cov;
		}
	}

	// Printing out mean
	std::cout << "\nEXCEPTED MEAN RETURNS: \n";
	for (unsigned int i = 0; i < STOCKS; i++) {
		std::cout << stocks[i].GetTicker() << "\t" <<  stocks[i].GetPriceMean() << '\n';
	}
	

	// Printing out covarience matrix
	std::cout << "\nCOVARIENCE MATRIX: \n";
	for (unsigned int i = 0; i < STOCKS; i++) {
		for (unsigned int j = 0; j < STOCKS; j++) {
			std::cout << covarience[i][j] << "\t";
		}
		std::cout << '\n';
	}
		
	return 0;

}

