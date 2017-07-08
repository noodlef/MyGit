#ifndef SORT_H
#define SORT_H
namespace templa{
	//***********************************************************
	template<typename T1>
	T1& operator+(T1 &lhs, size_t n) {
		for (int i = 0; i != n; ++i) 
			++lhs;
		return lhs;
	}
	//**********************************************************
	template<typename T1>
	T1& operator-(T1 &lhs, size_t n) {
		for (int i = 0; i != n; ++i)
			--lhs;
		return lhs;
	}
	//********************************************************** 
	template<typename T1, typename T2>
	void insertionSort(T1 lowerBound, T1 upperBound, T2 compare){
		if (upperBound == lowerBound )
			return;
		auto key = *lowerBound;
		T1 index, temp = lowerBound;
		bool Flag = false;
		for (T1 beg = ++temp; beg != upperBound; ++beg){
			key = *beg;
			index = beg;
			while (compare(key, *--index)){                                //while (*--index > key){
			    temp = index;
				*++temp = *index;
				if (index == lowerBound) {
					Flag = true;
					break;
				}
			}
			if (Flag) {
				*index = key;
				Flag = false;
			}
			else
				*(++index) = key;
		}
		return;
	}
	//*************************************************************
	/*template<typename T1>
	T1 partition(T1 lowerBound, T1 upperBound){
		if (lowerBound == upperBound)
			return lowerBound;
		T1 t = upperBound, index = lowerBound;
		auto pivot = *(--t), temp = pivot;
		for (T1 beg = lowerBound; beg != upperBound; ++beg){
			if (*beg <= pivot){
				temp = *index;
				*index++ = *beg;
				*beg = temp;
			}
		}
		return --index;
	}*/
	//*********************************************************
	template<typename T1, typename T2>
	struct Compare {
		T2 greater;
		bool operator()(const T1 &lhs, const T1 &rhs) const {
			return greater(lhs, rhs);
		}
		Compare(T2 c) : greater(c) {}
	};
	//********************************************************
	template<typename T1, typename T2>
	T1 partition(T1 lowerBound, T1 upperBound, T2 compare) {
		if (lowerBound == upperBound)
			return lowerBound;
		T1 index = lowerBound,beg = lowerBound, end = upperBound;
		auto pivot = *(--end), temp = pivot;
		for (; beg != end; ++beg) {
			if (compare(*beg , pivot)) {                                     //if (*beg < pivot) {
				temp = *index;
				*index++ = *beg;
				*beg = temp;
			}
		}
		temp = *index;
		*index= *beg;
		*beg = temp;
		return index;
	}
	//***********************************************************
	const size_t MINIMUM_ARRY_LENGTH = 2;
	template<typename T1, typename T2>
	void quickSort(T1 lowerBound, T1 upperBound, T2 compare){
		if (upperBound == lowerBound)
			return;
		T1 q;
		while (upperBound - lowerBound > MINIMUM_ARRY_LENGTH){
			q = partition(lowerBound, upperBound, compare);
			quickSort(lowerBound, q, compare);
			lowerBound = ++q;
		}
		insertionSort(lowerBound, upperBound, compare);
		return;
	}
	//********************************************************
	//快速排序---非递归（使用堆栈）
	template<typename T1, typename T2>
	void QuickSort(T1 lowerBound, T1 upperBound, T2 compare){
		if (upperBound == lowerBound)
			return;
		T1 q;
		templa::Stack<T1> myStack;
		myStack.push(lowerBound);
		myStack.push(upperBound);
		while (!myStack.stackEmpty()){
			upperBound = myStack.pop();
			lowerBound = myStack.pop();
			if (upperBound - lowerBound > MINIMUM_ARRY_LENGTH){
				q = partition(lowerBound, upperBound, compare);
				myStack.push(lowerBound);
				myStack.push(q);
				myStack.push(q);
				myStack.push(upperBound);
			}
			else
				insertionSort(lowerBound, upperBound, compare);
		}
	}
}
#endif