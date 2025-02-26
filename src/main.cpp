#include <iostream>
#include <tensorflow/c/c_api.h>

int main() {
	std::cout << "Tensor Flow C Library\nVersion:\t" << TF_Version() << '\n';
	return 0;
}
