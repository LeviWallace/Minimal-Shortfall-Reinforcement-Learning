#include "stock.h"

Stock::Stock(const std::string& ticker, const std::string& csv_location, const unsigned int csv_size)
{
	this->ticker = ticker;
	this->csv_location = csv_location;
	this->csv_size = csv_size;

	this->price_mean = 0;
	
	file.open(csv_location);

	// Check to see if valid file location	
	if (!file.is_open()) {
		throw std::runtime_error("(stock.c) Invalid File Location: " + csv_location + '\n');
	}

	LoadPrices();
}

void Stock::LoadPrices()
{
	std::cout << "Loading Prices..." << '\n';		
	std::string line;

	// Read header seperately
	std::getline(file, line);
	
	// Loop through each line in file
	float last_price = -1;
	while(std::getline(file, line))
	{
		// Initialize
		std::string s_trade_time, s_volume, s_price;
		std::stringstream stream(line);

		std::getline(stream, s_trade_time, ',');
		std::getline(stream, s_volume, ',');
		std::getline(stream, s_price, ',');

		// Set Variables
		// int volume = std::stoi(s_volume);
		float price = std::stof(s_price);
		
		
		// Add to prices
		prices.push_back(price);
		
		// Check if initialized
		if (last_price > 0) {
			// Add to price changes
			float difference = (price - last_price) / last_price;
			price_changes.push_back(difference); 

			// Add to price mean
			price_mean += difference;
		}
		last_price = price;
	}
	price_mean /= csv_size;
	return;
}

double Stock::CalculateCovarience(const Stock& other)
{
	double covarience = 0;
		
	// Get other variables
	const std::vector<float>* other_price_changes = other.GetPriceChanges();
	const float other_price_mean = other.GetPriceMean();

	// Get minimum size
	const int adjusted_size = csv_size > other.GetSize() ? other.GetSize() : csv_size;

	// Calculate covarience
	for (int idx = 0; idx < adjusted_size; idx++)
	{
		covarience += (price_changes[idx] - price_mean) * ((*other_price_changes)[idx] - other_price_mean);
	}

	return covarience /= adjusted_size;
}


Stock::~Stock()
{
	return;
}
