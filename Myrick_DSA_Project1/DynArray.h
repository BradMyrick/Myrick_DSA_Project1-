template <typename Type>
class DynArray
{
private:

	Type* array = nullptr;
	unsigned int Size = 0, Capacity = 0;
	unsigned int Minimum = 1;
	unsigned int MultiP = 2;

public:

	/////////////////////////////////////////////////////////////////////////////
// Function :	Default Constructor
// Notes : Doesn't do anything since data members were initialized above.
//		Still needs to exist due to copy constructor.
/////////////////////////////////////////////////////////////////////////////
	DynArray()
	{
		Capacity = Minimum;
		Size = 0;
		array = new Type[Capacity];
	};

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Destructor
	// Notes : cleans up any dynamic memory (can call clear())
	/////////////////////////////////////////////////////////////////////////////
	~DynArray()
	{
		clear();
	}
	void DeepCopy(const DynArray<Type>& that)
	{
		delete[] array; //ensure clean start
		Capacity = that.Capacity;
		Size = that.Size;
		if (that.array)
		{
			array = new Type[Capacity];
			for (int i{ 0 }; i < Capacity; ++i)
				array[i] = that.array[i];
		}
		else
			array = nullptr;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function :	Copy Constructor
	// Notes : Call the assignment operator
	/////////////////////////////////////////////////////////////////////////////
	DynArray(const DynArray<Type>& that):
	array{ nullptr }
	{
		DeepCopy(that);
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Assignment Operator
	// Notes : Perform deep copy of 'that' internal array
	/////////////////////////////////////////////////////////////////////////////
	DynArray<Type>& operator=(const DynArray<Type>& that)
	{
		if (this == &that)
			return *this;
		DeepCopy(that);
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : operator[]
	// Parameters : index - the index to access
	// Return : Type & - returns the array element at [index]
	// Notes : performs no error checking
	/////////////////////////////////////////////////////////////////////////////
	Type& operator[](const unsigned int index)
	{
		return array[index];
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : operator[] const version
	// Notes : Same as above but works for const DynArray objects
	/////////////////////////////////////////////////////////////////////////////
	const Type& operator[](const unsigned int index) const
	{
		return array[index];
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function :	size
	// Returns : int - returns the Size data member
	/////////////////////////////////////////////////////////////////////////////
	unsigned int size() const
	{
		return Size;
	}
	////////////////////////////////////////////////////////////////////////////
	// Function : capacity
	// Returns : int - returns the Capacity data member
	/////////////////////////////////////////////////////////////////////////////
	unsigned int capacity() const
	{
		return Capacity;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function :	clear
	// Notes : deletes any dynamic memory and resets size and capacity to 0
	//	and array to nullptr
	//////////////////////////////////////s///////////////////////////////////////
	void clear()
	{
		delete[] array;
		array = nullptr;
		Size = 0, Capacity = 0;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : append
	// Parameters : item - the item to be appended to the next open spot
	// Notes : this function will append the item to the next open spot. if 
	//		the array is full first, call reserve() to double the array, then
	//		append the item.
	/////////////////////////////////////////////////////////////////////////////
	void append(const Type& item)
	{
		
		if (Size >= Capacity)
		{
			reserve();
		}
		array[Size] = item;
		Size++;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : reserve
	// Parameters : newCap - the new capacity
	// Notes : 	A) Default parameter of 0 should double the array capacity. In
	//	this double case, check for existing capacity of 0 or non-0.
	//	B) Parameter of lesser (non-0) or equal value to current capacity
	//	should do NOTHING.
	//	C) Parameter of higher value should be the newvalue for current
	//	capacity.
	//	Reallocates the array based on the new capacity amount (and copies over
	//	the existing data)
	/////////////////////////////////////////////////////////////////////////////
	void reserve(const unsigned int& newCap = 0)
	{
		//if (!array) // without this it breaks but I don't believe I am supposed to have it.
		//{
		//	array = new Type[newCap];
		//}
		if (newCap == 0)
		{
			Capacity = Capacity * MultiP;
			if (Capacity == 0)
			{
				Capacity = Minimum;
			}
			
		}
		if (newCap > Capacity)
		{
			Capacity = newCap;
		}
		
		Type* temp = nullptr;
		temp = new Type[Capacity];
		for (size_t i = 0; i < Size; i++)
		{
			temp[i] = array[i];
		}
		delete[] array;
		array = temp;
	}
};

