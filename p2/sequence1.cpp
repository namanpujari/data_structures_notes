#include <cassert> /* This library allows us to use the
					  assert() function */
#include "sequence1.h"
// This is the implementation file for sequence1.h.
// It has the definitions of the methods defined 
// in sequence1.h

namespace main_savitch_3 {
	sequence::sequence() {
		// Initialize all the private members to their 
		// default values. data has already been initialized
		// with CAPACITY has its total memory cap.
		total_used = 0; // Nothing has been used in the sequence
		current_index = CAPACITY; // Make this something impossible. 
	}

	void sequence::start() {
		// Move the cursor current_index to the beginning 
		// of the sequence
		if(total_used != 0) {
			current_index = 0;
		} else {} // current_index is already invalid if this is true.
	}

	void sequence::advance() {
		assert(is_item());
		if(current_index == total_used - 1) {
			current_index = CAPACITY; // Some nonsense current index
			// indicating that there is no more valid current 
			// item
		} else current_index++; // Move to the next item in
		// the sequence
		
		// We are not caring about the case where sequence is empty
		// because assert(is_item()) takes care of that
	}

	void sequence::insert(const value_type& entry) {
		assert(size() < CAPACITY);
		if(!is_item()) { // If index is invalid insert at beginning
			current_index = 0;
		} else {} // We can use the same for loop for both cases: 
		// valid or invalid current index
		for(size_type i = total_used; i > current_index; i--) {
			// This is very similar to the code for attach, which I did first.
			// If you think about it, insert is simply attach for 
			// current_index - 1.
			data[i] = data[i - 1];
		} data[current_index] = entry;
		// We do not have to change the current_index
		total_used++;
	}

	void sequence::attach(const value_type& entry) {
		assert(size() < CAPACITY);
		if(!is_item()) { // There is no valid current item
			data[total_used] = entry;
			current_index = total_used;
			// If the item is attached at the end, then there is no need
			// to shift anything at the end.
		} else if(current_index >= 0) {
			for(size_type i = total_used; i > current_index + 1; i--) {
				// Condsider * to be the point of attachment
				// In the sequence 2 3 6 8* 9 10, attaching 3
				// We end up with 2 3 6 8 3 9 10
				data[i] = data[i - 1];
			} data[current_index+1] = entry;
			current_index++;
		} else {}
		total_used++;
	}

	void sequence::remove_current() {
		assert(is_item());
		// If we remove an item, every single item after it is moved to the
		// left. Also, total_used value reduces by exactly 1.
		for(size_type i = current_index; i < total_used - 1; i++) {
			data[i] = data[i + 1];
		} total_used --;
	}

	// CONSTANT MEMBER FUNCTIONS
	// Inline functions are in the header file. These are the 
	// non-inline functions.
	sequence::value_type sequence::current() const {
		assert(is_item());
		return data[current_index];
	}
}
