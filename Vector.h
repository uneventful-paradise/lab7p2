#pragma once
template <class T>
class Vector {
private:
	int allocated;
	int maxalloc;//de ce e nevoie ca astea sa fie private?
	T* elements;
public:
	Vector();//constructor pentru alocarea initiala a memoriei
	~Vector();//destructor de completat!!
	void push(T element);
	T pop();
	void remove(int index);
	void insert(T element, int index);
	void sort(T(*callback)(T,T));//de ce e nevoie ca tipul functiei callback sa fie T?
	const T& get(int index); //de ce nu const& T? o referinta constanta sau const &T  <- pt ca T e ca tipul| const int & n
	void set(T elem, int index);
	int count();
	int firstIndexOf(T element, bool (*callback)(T,T));//bool [pentru ca operatorul era ==?
	void Print();
};

template <class T>
Vector<T>::Vector()//de ce <T>?
{
	this->allocated = -1;
	this->maxalloc = 1;
	this->elements = (T*)malloc(maxalloc * sizeof(elements));//?? de ce maxalloc*sizeof(T)
	//sau
	//this->elements = new T[maxalloc]?
}

template <class T>
Vector<T>::~Vector()
{
	free(elements);//free pt malloc
	//sau
	//delete[] elements
}

template<class T>
void Vector<T>::push(T elem)
{
	if (this->allocated == this->maxalloc)
	{
		maxalloc *= 2;
		this->elements = (T*)realloc(this->elements, maxalloc * sizeof(elements));
	}
	this->allocated++;
	this->elements[allocated]= elem;
}

template<class T>
T Vector<T>::pop()
{
	this->allocated--;
	return this->elements[allocated+1];//nu e nevoie aici sa dau delete la acel spatiu de memorie?
}

template <class T>
void Vector<T> ::remove(int index)
{
	if (index > this->maxalloc or index < 0)//???problema?
		return -1;
	else
	{
		for (int i = index; i <= this->maxalloc-1; ++i)//nu invers
			this->elements[i] = this->elements[i+1];
	}
	this->allocated--;
}

template <class T>
void Vector<T>::insert(T element,int index)
{
	if (index >= 0 and index <= this->maxalloc)
	{
		if (this->allocated == this->maxalloc)
		{
		this->maxalloc*=2;
		this->elements = (T*)realloc(this->elements, maxalloc * sizeof(elements));
		}
		this->allocated++;//cresc indicele ultimului element adaugat pentru a putea muta toate elementele la dreapta cu un spatiu
		for (int i = this->allocated; i > index; --i)//e mai ok sa merg de la maxalloc la index?
			this->elements[i] = this->elements[i - 1];
		this->elements[index] = element;
	}
}

template <class T>
void Vector<T>::sort(T(*callback)(T, T))
{
	for(int i = 0; i < this->allocated; ++i)
		for(int j = i+1; j < this->allocated; ++j)
			if (callback == nullptr)
			{
				if (this->elements[i] > this->elements[j])
				{
					T aux;
					aux = elements[i];
					elements[i] = elements[j];
					elements[j] = aux;
				}
			}
			else
			{
				if (callback(this->elements[i], this->elements[j]))
				{
					T aux;
					aux = elements[i];
					elements[i] = elements[j];
					elements[j] = aux;
				}
			}
}

template<class T>
const T& Vector<T>::get(int index)
{
	if (index >= 0 and index <= this->allocated)//allocated pentru ca indexul trebuie sa fie folosit de alt obiect
		return this->elements[index]; //cum returnez aici referinta? vectorul nu e deja o adresa? daca da, care ar fi fost diferenta sa dau pointer la vector?
}

template <class T>
void Vector<T>::set(T element, int index)
{
	if (index >= 0 and index <= this->allocated)
		this->elements[index] = element;
}

template<class T>
int Vector<T>::count()
{
	return this->allocated + 1;
}

template<class T>
int Vector<T>::firstIndexOf(T element, bool(*callback)(T, T))
{
	//ar avea mai mult sens sa pun intai if-ul? sau nu are asta asa mare impact?
	for(int i = 0; i <= this->allocated; ++i)
		if (callback != nullptr)
		{
			if (callback(element, this->elements[i]))
				return i;
		}
		else
		{
			if (element == this->elements[i])
				return i;
		}
	//daca nu gasim
	return -1;
}

template<class T>
void Vector<T>::Print()
{
	for (int i = 0; i < this->allocated; ++i)
		std::cout << this->elements[i] << " ";
}
