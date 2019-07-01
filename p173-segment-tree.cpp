#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

using namespace std;

//https://github.com/jakobkogler/Algorithm-DataStructures/blob/master/RangeQuery/SegmentTree.cpp
class SegmentTree {
public:
	SegmentTree(int count) {
		n = count;
		data = vector<int>(2 * n, 0); //init with size 2N (still can change), value = 0
	}

  // Construct
	SegmentTree(vector<int> const &v) {
		n = v.size();
		data = vector<int>(2 * n, 0);
		copy(v.begin(), v.end(), &data[0] + n);
		
    for (int idx = n - 1; idx >= 1; idx--)
			data[idx] = min(data[idx * 2], data[idx * 2 + 1]);
	}

	void update(int idx, int value) {
		idx += n;
		data[idx] = value;

		while (idx > 1) {
			idx /= 2;
			data[idx] = min(data[2 * idx], data[2 * idx + 1]);
		}
	}

	int minimum(int left, int right) { // interval [left, right)
		int ret = std::numeric_limits<int>::max(); // = 2147483647, INF
		left += n;
		right += n;

		while (left < right) {
			if (left & 1) // is odd
        ret = min(ret, data[left++]);
			if (right & 1) // is odd
        ret = min(ret, data[--right]);
			left >>= 1;
			right >>= 1;
		}
		return ret;
	}

private:
	int n;
	vector<int> data; // main storage data structure
};

int main() {
	SegmentTree st(5);
	st.update(0, 5);
	st.update(1, 2);
	st.update(2, 3);
	st.update(3, 1);
	st.update(4, 4);
	for (int i = 0; i < 5; i++) {
		std::cout << i << ": " << st.minimum(i, i+1) << std::endl;
	}

	std::cout << st.minimum(1, 4) << std::endl;
	st.update(3, 10);
	std::cout << st.minimum(1, 4) << std::endl;
	std::cout << st.minimum(0, 5) << std::endl;
	st.update(4, 0);
	std::cout << st.minimum(1, 4) << std::endl;
	std::cout << st.minimum(0, 5) << std::endl;

}

