#ifndef MATRIX_HH
#define MATRIX_HH

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <exception>

typedef std::vector<std::vector<double>> vector_matrix;

//		CUSTOM EXCEPTION CLASS

class matrix_exception: public std::exception {
  public:
   matrix_exception(const char* error) : exception(), message(error) {}
   const char* what() const throw() {return message;}; 
  private:
   const char* message;
};


//		CLASS MATRIX

class matrix {

	vector_matrix m;

	int cols, rows;

	void copy (const matrix& m);
	/*	pre: true.
		post: the matrix is equal to m. */

public:

	//	CONSTRUCTORS

	matrix (int rows, int cols, double val = 0.0, bool random = false);
	/*	pre: cols and rows are positive integers
		post: a matrix of shape rows*cols and filled with val (0 as a
				default) if random = false and with random values from 0 to 
				val (1 as a default) otherwise. */

	matrix (const matrix& m);
	/*	pre: true
		post: creates a matrix equal to m */



	//	MODIFIERS

	void change (int row, int col, double val);
	/*	pre: 0 <= col < cols and 0 <= row < rows
		post: cahnges the element in the position row col to val. */

	void read ();
	/*	pre: there is a series of row*cols doubles to read in the standard
				channel
		post: the matrix has been filled with the given values. The first
				row takes the first row values and so on */

	void T ();
	/*	pre: true
		post: the matrix has been trasposed. */

	matrix gT () const;
	/*	pre:true
		post: returns a trasposed matrix. */

	void multn (double n);
	/*	pre:true
		post: the matrix has been multiplied by n. */

	matrix gmultn (double n) const;
	/*	pre: true
		post: the returned value is the matrix multiplied by n.*/

	matrix operator+ (const matrix& m) const;
	/*	pre: both matrices have the same shape.
		post: the returned value is a matrix with the same shape and whose
				elements are the sum of both matrices. */

	matrix operator- (const matrix& m) const;
	/*	pre: both matrices have the same shape.
		post: the returned value is a matrix with the same shape and whose
				elements are the difference of both matrices. */

	matrix operator^ (const matrix& m) const;
	/*	pre: both matrices have the same shape.
		post: the returned value is a matrix with the same shape and whose
				elements are the elemtwise product of both matrices. */

	matrix operator* (const matrix& m) const;
	/*	pre: the number of cols of this is equal to the number of rows of m.
		post: the returned matrix is the result of the matrix product
				betweeen this and m. */

	bool operator== (const matrix& m) const;
	/*	pre: true.
		post: returns true if both matrices have the same shape and elements. */

	void operator= (const matrix& m);
	/*	pre: true.
		post: the left hand side matrix is equal to the one in the right. */

	void operator+=(const matrix& m);
	/*	pre: both matrices have the same shape.
		post: the returned value is a matrix with the same shape and whose
				elements are the sum both matrices. */

	void operator-= (const matrix& m);
	/*	pre: both matrices have the same shape.
		post: the returned value is a matrix with the same shape and whose
				elements are the difference of both matrices. */

	void operator^= (const matrix& m);
	/*	pre: both matrices have the same shape.
		post: the returned value is a matrix with the same shape and whose
				elements are the elementwise multiplication of both matrices. */

	void operator*= (const matrix& m);
	/*	pre: the number of cols of this is equal to the number of rows of m.
		post: this becomes the result of the matrix product betweeen this
				and m. */

	std::vector <double> operator[] (int row) const;
	/*	pre: 0 <= row < rows and 0 <= col < cols
		post: returns the rowth row. NOT SUITABLE FOR CHANGING ITEMS IN THE
				MATRIX, for that purpose use change */



	//	CONSULTORS

	void shape (int& row, int& col) const;
	/*	pre: true
		post: changes the value of row to the number of rows and col to the
		number of columns. */

	int nrows () const;
	/*	pre: true
		post: returns number of rows. */

	int ncols () const;
	/*	pre: true
		post: returns the number of columns. */

	double elm (int row, int col) const;
	/*	pre: 0 <= col < cols and 0 <= row < rows
		post: returns the element in the row col position. */

	long double mod () const;
	/*	pre: true
		post: the value returned is square of the sum of the squares for
				each value of the matrix */

	void draw (int margin = 3, int p = 3) const;
	/*	pre: margin and p are a positive integers
		post: draws the matrix with margin number of spaces to the left and 
		precission p. If an item does not have a decimal part, the .000... 
		wont be drown, but if it does but is too small to fit in p precission
		a n.0000... will be shown. */

	matrix gcopy () const;
	/*	pre:true
		post: returns a copy of the matrix */


};

#endif