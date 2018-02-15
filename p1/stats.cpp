#include <cassert> /* This library allows us to use the
					  assert() function */
#include "stats.h"
// This is the implementation file for stats.h.
// It has the definitions of the methods defined 
// in stats.h
namespace main_savitch_2C {
	statistician::statistician() {
		// We don't really need to store anything in
		// a vector or something similar, since ever-
		// ything we need from it is calculatable
		// without using vectors.
		reset();
	} // Completed the constructor definition. 

	void statistician::next(double r) {
		// This function appends a number to the
		// statistician class.
		count++;
		total += r;
		if(count == 1) {
			largest = r;
			tinyest = r;
		} else if(count > 1){
			if(r < tinyest) tinyest = r;
			if(r >= largest) largest = r;
		} else {}
	} // The next function changes each property

	void statistician::reset() {
		// Resets every value to 0. We can use this
		// function in the constructor as it is 
		// intended to do the same thing.
		count = 0;
		total = 0.0;
		tinyest = 0.0;
		largest = 0.0;
	} // Completed the reset() function.

	double statistician::mean() const {
		// Couldn't be an inline because we also
		// have to use assert to make sure the pre-
		// condition is met.
		assert(count > 0);
		double mean_val = (total / (double)count);
		return mean_val;
	} // Returns the arithmetic mean.

	double statistician::minimum() const {
		// Couldn't be an inline because we also
		// have to use assert to make sure the pre-
		// condition is met.
		assert(count > 0);
		return tinyest;
	} // Returns the smallest value in statistician.

	double statistician::maximum() const {
		// Couldn't be an inline because we also
		// have to use assert to make sure the pre-
		// condition is met.
		assert(count > 0);
		return largest;
	} // Returns the largest value in statistician.

	statistician operator +(const statistician& s1, 
			const statistician& s2) {
		// According the postcondition this appends
		// the data in s2 and s1.
		statistician return_s;
		return_s.count = s1.count + s2.count;
		return_s.total = s1.total + s2.total;
		// Determine the maximum of the new statistician
		if(s1.count != 0 && s2.count != 0) {
			if(s1.largest >= s2.largest) return_s.largest = s1.largest;
			else if(s1.largest < s2.largest) return_s.largest = s2.largest;
			// Determine the minimum of the new statistician
			if(s1.tinyest <= s2.tinyest) return_s.tinyest = s1.tinyest;
			else if(s1.tinyest > s2.tinyest) return_s.tinyest = s2.tinyest;
			// Return the statistician object
		} else if(s1.count == 0 && s2.count != 0) {
			return_s.tinyest = s2.tinyest;
			return_s.largest = s2.largest;
		} else if(s1.count != 0 && s2.count == 0) {
			return_s.tinyest = s1.tinyest;
			return_s.largest = s1.largest;
		} else {}
		return return_s;
	} // Completed definition for + operator. This
	// function does not need to be within the scope
	// of the class since it is a friend function
	
	statistician operator *(double scale, 
			const statistician& s) {
		// Simple scales each data point in the
		// statistician object. Nothing else is 
		// useful. 
		statistician return_s;
		return_s.count = s.count;
		return_s.total = (double)s.total * scale;
		if(scale >= 0) {
			return_s.tinyest = (double)s.tinyest * scale;
			return_s.largest = (double)s.largest * scale;
		} else if(scale < 0) {
			return_s.tinyest = (double)s.largest * scale;
			return_s.largest = (double)s.tinyest * scale;
		} else {}

		return return_s;
	}
	
	bool operator ==(const statistician& s1, 
			const statistician& s2) {
		// Return true if mean, min, max, total and count
		// are equal. Since this is neither a member 
		// function nor a friend function, we have to 
		// use the public methods to obtain certain private
		// values.
		bool same_mean, same_min, same_max, same_total;
		if(s1.length() == 0 && s2.length() == 0) {
			return 1;
		} else if(s1.length() != 0 || s2.length() != 0) {
			if(s1.length() == s2.length()) {
				same_mean = (s1.mean() == s2.mean());
				same_min = (s1.minimum() == s2.minimum());
				same_max = (s1.maximum() == s2.maximum());
				same_total = (s1.sum() == s2.sum());
			} else if(s1.length() != s2.length()) {
				return 0;
			} else {}
		} else {}
		return same_mean && same_min && same_max &&
			same_total;
	} // Completed definition for == operator
}



