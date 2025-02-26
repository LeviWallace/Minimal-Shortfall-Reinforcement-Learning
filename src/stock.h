
#include <vector>
#include <string>

class Stock {
public:
	Stock(const std::string& ticker);
	

	~Stock();

	inline std::string GetTicker() const { return ticker; };

private:
	std::string ticker;
	std::vector<float> prices; // S
	std::vector<float> price_changes; // Change in S
	float price_mean; // mean
	float price_covariances;  // cov
};
