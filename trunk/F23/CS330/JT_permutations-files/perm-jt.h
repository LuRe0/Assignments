#ifndef PERM_JOHNSON_TROTTER_H
#define PERM_JOHNSON_TROTTER_H
#include <vector>

class PermJohnsonTrotter {


public:
	PermJohnsonTrotter(int size);
	bool Next();
	std::vector<int> const& Get() const;

private:
	std::vector<int> m_Data;

	std::vector<int> m_Direction;
};
#endif
