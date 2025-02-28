
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Stock
{
public:
	Stock(const std::string& ticker, const std::string& csv_location, const unsigned int csv_size);
	inline Stock(const Stock& other) = default;
	inline Stock(Stock&& other) noexcept = default;
	
	inline std::string GetTicker() const { return ticker; };
	inline const std::vector<float>* const GetPrices() const { return &prices; };
	inline const std::vector<float>* const GetPriceChanges() const {return &price_changes; };
	inline float GetPriceMean() const { return price_mean; };
	inline unsigned int GetSize() const { return csv_size; };

	double CalculateCovarience(const Stock& other);

	inline bool operator=(const Stock& other) const { return this->ticker == other.ticker; };
	~Stock();

private:
	std::string ticker;
	std::string csv_location;
	std::ifstream file;
	unsigned int csv_size;

	// PRICE VARIABLES
	std::vector<float> prices; // S
	std::vector<float> price_changes; // Change in S	
	float price_mean; // Mean

	// VOLUME VARIABLES
	std::vector<int> volume_changes; // Change in V

	// VWAP VARIABLES
	double market_vwap;
	double target_vwap;

	void CalculatePrices(); // Load prices and calculates S, dS, Mean, and dV
	void CalculateMarketVWAP(); 
	void CalculateTargetVWAP(const std::vector<int>& actions); 
};
