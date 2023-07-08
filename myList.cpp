#include<iostream>
using namespace std;

template<class T>
class myList;//ǰ������

template<class T>
class myListNode {
private:
	T val;
	myListNode* next;
public:
	friend class myList<T>;
	myListNode() :val(), next(nullptr) {}
	myListNode(T x) :val(x), next(nullptr) {}
	friend ostream& operator<< <T>(ostream&, myList<T>&);
};

template<class T>
class myList {
private:
	myListNode<T>* head;
public:
	myList() {
		head = new myListNode<T>;
	}
	myList(T* inputs, int size) {
		head = new myListNode<T>(inputs[0]);
		myListNode<T>* ptr = head;
		for (int i = 1; i < size; ++i) {
			ptr->next = new myListNode<T>(inputs[i]);
			ptr = ptr->next;
		}
	}
	~myList() {   
		myListNode<T>* now = head;
		myListNode<T>* far = now->next;
		while (far != nullptr) {
			delete now;
			now = far;
			far = far->next;
		}
		delete now;
	}
	myList(myList& input) {
		head = new myListNode<T>(input.head->val);
		myListNode<T>* ptr2 = input.head->next;
		myListNode<T>* ptr1 = head;
		while (ptr2 != nullptr) {
			ptr1->next = new myListNode<T>(ptr2->val);
			ptr2 = ptr2->next;
			ptr1 = ptr1->next;
		}
	}

	//=��ֵ
	myList& operator=(myList& input) {
		myList* tempList = new myList(input);
		this->head = tempList->head;
		return *this;
	}

	//[]��ȡ��������
	T operator[](int input) {
		myListNode<T>* ptr = head;
		for (int i = 0; i < input; ++i) {
			ptr = ptr->next;
		}
		return ptr->val;
	}

	//��ĩβ���Ԫ��
	myList& add(T input) {
		myListNode<T>* ptr = head;
		while (ptr->next != nullptr) {
			ptr = ptr->next;
		}
		ptr->next = new myListNode<T>(input);
		return *this;
	}

	//ĩβɾ��Ԫ��
	myList& pop() {
		myListNode<T>* ptr = head;
		while (ptr->next->next != nullptr) {
			ptr = ptr->next;
		}
		delete ptr->next;
		ptr->next = nullptr;
		return *this;
	}

	//cout���
	friend ostream& operator<< <T>(ostream& , myList& );
};

template<class T>
ostream& operator<<(ostream& out, myList<T>& input) {
	out << "{ " << input.head->val;
	myListNode<T>* ptr = input.head->next;
	while (ptr != nullptr) {
		out << "," << ptr->val;
		ptr = ptr->next;
	}
	out << " }";
	return out;
}


//����Ϊ���Դ���

//void memory_test() {
//	int test[] = { 1,2,3,4,5,6,7 };
//	myList<int>example(test, 7);
//}

int main() {
	int test[] = { 1,2,3,4,5,6,7 };
	myList<int>example1(test, 7);
	myList<int>example2;
	example2 = example1;
	example2.add(187);
	cout << example2[7] << endl;
	example2.pop();
	cout << example2[6] << endl;
	cout << example2;
	return 0;
}