// INVARIANT OF THE SEQUENCE CLASS
// 1. The sequence uses a dynamic array whose address is located in
// data_pointer. The same member variables allows for modification of all 
// sorts.
// 2. The total_used member variable keeps track of how much memory of the array
// has been used. This way, we are only concerned with the values between 0 and 
// total_used - 1. Values indexed outside of this range are insignificant for the
// purposes of the sequence
// 3. current_item_index is used as a cursor to the chosen value. Through this value,
// the positioning of incoming values (using the insert/attach) functions is determined.
// It is also useful in determining which specific value is to be deleted
// from the dynamic sequence. 
// 4. data_capacity is a member variable that stores information regarding the size 
// (which, of course, is not fixed) of the dynamic array. Its sole purpose is to 
// act as a determinant of when to call the resize function, during insert/attach 
// function calls.

#include <cassert> // Contains the assert function, handles
// exceptions and other precondition related errors
#include "sequence2.h" // Contains definition for the sequence2 class

namespace main_savitch_4 {
	// Constructors (default and copy)
	
	// Below is the default constructor. It is used to initial a dynamic sequence
	// with the default values. No precondition is required
	sequence::sequence(sequence::size_type initial_capacity) {
		// Turns out, providing the default parameter is not necessary in the function 
		// implementaton if it has already been introduced in the header file.
		data_pointer = new value_type[initial_capacity];
		total_used = 0;
		data_capacity = initial_capacity;
		current_item_index = data_capacity; // Something impossible at this stage
	} // End of default constructor definition
	
	// Below is the copy constructor. It is used to initialize a copy of an already
	// existing dynamic sequence. It copies all the necessary values, like the member
	// variables and data array to produce an identical sequence.
	sequence::sequence(const sequence& source) {
		// The copy constructor: copies necessary member variables such
		// as current_item_index, data_capacity and total used. Also, copies the
		// source's data, not by simply copying the pointer, but by creating 
		// another, identical, array of value_type and making data_pointer point 
		// to the identical array. Avoids the mistake of both source and 
		// constructed sequence pointing to the same thing. 
		data_pointer = new value_type[source.data_capacity];
		for(size_type i = 0; i < source.total_used; i++) {
			*(data_pointer + i) = *(source.data_pointer + i);
		} // The code above copies the source data into data_pointer of new sequence
		total_used = source.total_used;
		current_item_index = source.current_item_index;
		data_capacity = source.data_capacity;
	} // End of default constructor definition

	// The destructor releases all the data that had been allocated to the dynamic
	// sequence. In doing so it does not hog memory from the machine. It is part of the
	// big three: constructors, destructors and assignment overload.
	sequence::~sequence() {
		// Returns the data in data_pointer back to memory,
		// making it free to use. Destructors can be implicitly called
		// (by the compiler), or they can be called if a programmer calls
		// the delete function on a pointer pointing to a sequence ADT.
		delete [] data_pointer;
	} // End of destructor definition.

	// Below are modification functions. They simply modify certain member variables
	// in order to allow for the basic functionality of the sequence
	
	void sequence::start() { 
		// This function is similar to the one in static sequence. It moves the 
		// current_item_index to 0 if and only if total_used > 0.
		if(total_used > 0) {
			current_item_index = 0;
			// That it, we just want to point the first item, and do nothing else
		} else {} // If the else statement is true, then we know for a fact that
		// total amount of slots used in the sequence is 0, so no need to change
		// the current_item_index.
	} // End of start definition

	void sequence::advance() {
		// Advances the current_item. In computer science terms, increments the index
		// value by 1. If the current_item is at total_used - 1 (end of the sequence), it
		// pushes it to total_used, which is an invalid index and will make is_item() return
		// false.
		assert(is_item());
		current_item_index++;
	} // End of advance definition

	void sequence::insert(const value_type& entry) {
		// Unlike the previous sequence, we don't need to check any capacity related 
		// errors. They can be taken care of, since the array is dynamic. Essentially, 
		// there are no Preconditions.
		if(!is_item()) {
			current_item_index = 0; // Start of the sequence
		} else {}
		// Resizes the array if the next entry will go beyond capacity
		if(total_used == data_capacity) resize(data_capacity * 2);
		for(size_type i = total_used; i > current_item_index; i--) {
			*(data_pointer + i) = *(data_pointer + (i - 1));
		} *(data_pointer + current_item_index) = entry;
		// We don't have to change the current_item_index if we were previously on 
		// a valid item. We are simply moving everything else to the right
		total_used++;
	} // End of insert definition

	void sequence::attach(const value_type& entry) {
		// Again, no assert needed because of dynamic memory
		if(!is_item()) {
			current_item_index = total_used;
		} else current_item_index++;
		// Unlike in the insert function, we actually have to change the current_item_index in
		// BOTH cases.
		// Resize the data_pointer if needed.
		if(total_used == data_capacity) resize(data_capacity * 2);
		for(size_type i = total_used; i > current_item_index; i--) {
			*(data_pointer + i) = *(data_pointer + (i - 1));
		} *(data_pointer + current_item_index) = entry;
		total_used++;
	} // End of attach definition

	void sequence::remove_current() {
		// Since we aren't appending anything to the sequence, there is no resizing necessary
		// and this makes our lives much easier...
		assert(is_item());
		// If we remove an item, every single item after it is moved to the left. Also, total_used
		// value reduces by exactly 1.
		for(size_type i = current_item_index; i < total_used - 1; i++) {
			*(data_pointer + i) = *(data_pointer + (i + 1));
		} total_used--;
	} // End of remove_current definition

	// Below is perhaps the most important function for the dynamic sequence. The resize
	// function changes data_capacity and increases it to a capacity provided by the 
	// parameter. This can be done by initializing a temporary pointer (with a higher 
	// capacity).
	void sequence::resize(size_type new_capacity) {
		if(total_used < new_capacity) {
			value_type *temp;
			temp = new value_type[new_capacity]; // This a pointer to an increased array.
			// We have to fill in the memory slots using the previous data array.
			for(size_type i = 0; i < total_used; i++) {
				*(temp + i) = *(data_pointer + i);
			} // This copies original values into resized array
			delete [] data_pointer; // Release the memory it previously had
			data_pointer = temp; // Copies the resized array pointer to the member
			// variables.
			temp = NULL;
			data_capacity = new_capacity; // Change the capacity member variable.
			// Every other member variable should be the same.
		} else {} // No need to resize if new_capacity is less than data_capacity we have
		// currently
	} // End of resize definition

	// The assignment operator is very important, and is part of The Big Three
	void sequence::operator=(const sequence& source) {
		// This is pretty much the same as the code for the copy constructor
		if(data_pointer == source.data_pointer) return; // This is a self-assignment!
		delete [] data_pointer; // Free any memory allocated previously by the object
		data_pointer = new value_type[source.data_capacity];
		for(size_type i = 0; i < source.total_used; i++) {
			*(data_pointer + i) = *(source.data_pointer + i);
		} // The code above copies the source data into data_pointer of new sequence
		total_used = source.total_used;
		current_item_index = source.current_item_index;
		data_capacity = source.data_capacity;
	} // End of operator= definition

	// Below are constant member functions. They do not change any associated values of
	// the class

	bool sequence::is_item() const {
		// This can only return true if the current_item_index is within a valid
		// range. This range is defined by 0 and the total_used, not by 0 and the 
		// data_capacity.
		return (current_item_index >= 0 && current_item_index < total_used);
	} // End of is_item definition

	sequence::value_type sequence::current() const {
		assert(is_item());
		return *(data_pointer + current_item_index);
	} // End of current definition	
}

