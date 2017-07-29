class Heap {
public:
	Heap();
	~Heap();
	typedef int KeyType;
	typedef size_t SatalliteData;
	struct ElementType {
		KeyType key;
		SatalliteData element;
	};
	void malloc();
	void shiftUp(int index);
	void shiftDown(int index);
	void insert(const ElementType *e);
	bool bigger(const ElementType *lhs, const ElementType *rhs) const;
	void swap(ElementType *lhs, ElementType *rhs);
private:
	size_t size;                                                                             
	size_t elementCnt;                                                                      
	ElementType *ptr;
};
//**************************************************************************
Heap::Heap()
	:size(0), elementCnt(0), ptr(nullptr) {
}
Heap::~Heap() {
	delete [] ptr;
}
//**************************************************************************
void Heap::
insert(const ElementType *e) {
	if (elementCnt == size)
		malloc();
	*(ptr + elementCnt) = *e;
	++elementCnt;
	shiftUp(elementCnt);
}
//**************************************************************************
void Heap::
malloc() {
	int newSize;
	if (size == 0)
		newSize = 1;
	else
		newSize = size * 2;
	//int increment = 2;
	//int newSize = size + increment;
	ElementType *newPtr = new ElementType[newSize];
	ElementType *temp1 = newPtr, *temp2 = ptr;
	for (int i = 0; i != elementCnt; ++i)
		*temp1++ = *temp2++;
	delete[] ptr;
	ptr = newPtr;
	size = newSize;
}
//**************************************************************************
void Heap::
shiftUp(int index) {
	int parent = index / 2, child = index;
	while (child > 1) {
		if (bigger(ptr + child - 1, ptr + parent - 1)) {
			swap(ptr + child - 1, ptr + parent - 1);
			child = parent;
			parent = child / 2;
		}
		else
			return ;
	}
}
//**************************************************************************
void Heap::
shiftDown(int index) {
	int parent = index, heapSize = elementCnt;
	int lchild = 2 * parent, rchild = lchild + 1, mark;
	while (parent <= heapSize / 2) {
		if (bigger(ptr + lchild - 1, ptr + parent - 1))
			mark = lchild;
		else
			mark = parent;
		if (rchild <= heapSize && bigger(ptr + rchild - 1, ptr + mark - 1))
			mark = rchild;
		if (mark != parent) {
			swap(ptr + mark - 1, ptr + parent - 1);
			parent = mark;
			lchild = parent * 2;
			rchild = lchild + 1;
		}
		else
			return ;
	}
}
//**************************************************************************
bool Heap::
bigger(const ElementType *lhs, const ElementType *rhs) const {
	return lhs->key < rhs->key;//lhs->key > rhs->key ´ó¶¥¶Ñ
}
//**************************************************************************
void Heap::
swap(ElementType *lhs, ElementType *rhs) {
	ElementType temp;
	temp = *lhs;
	*lhs = *rhs;
	*rhs = temp;
}