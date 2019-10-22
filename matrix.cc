# include "matrix.hh"
using namespace std;

// error messages for throw
const char* error_bounds	= "item out of bounds";
const char* error_sum		= "bad shape for sum";
const char* error_sub		= "bad shape for substraction";
const char* error_mult		= "bad shape for elementwise multiplication";
const char* bad_shape		= "not suitable shape for matrix";

//		METHODS OF MATRIX

matrix::matrix (int rows, int cols, double val, bool random)
{
	if (rows < 0 or cols < 0)
		throw matrix_exception(bad_shape);

	this->rows = rows;
	this->cols = cols;

	m = vector_matrix(rows, vector <double>(cols, val));

	if (random) {

		srand (time(NULL) * rand()/RAND_MAX);

		// calculate the maximum random value generated
		if (val == 0)
			val = 1;
		double max_rand = double(val)/RAND_MAX;

		// generate a matrix and fill it with random values
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				this->m[i][j] = rand()*max_rand;
			}
		}
			

	}
}


matrix::matrix (const matrix& m)
{
	copy(m);
}


void matrix::copy (const matrix& m)
{
	this->rows = m.rows;
	this->cols = m.cols;
	this->m = vector_matrix(rows, vector <double>(cols));

	// generate a matrix and fill it with random values
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			this->m[i][j] = m.m[i][j];
		}
	}
}


void matrix::change (int row, int col, double val)
{
	if (row >= rows or col >= cols)
		throw matrix_exception(error_bounds);
	m[row][col] = val;
}


void matrix::shape (int& row, int& col) const
{
	row = this->rows;
	col = this->cols;
}


int matrix::nrows () const
{
	return rows;
}


int matrix::ncols () const
{
	return cols;
}


double matrix::elm (int row, int col) const
{
	if (row >= rows or col >= cols)
		throw matrix_exception(error_bounds);
	return this->m[row][col];
}

int number_of_digits(double n)
// returns the quantity of digits of a number
{
	int counter = 0, number = int(n);
	if (number == 0) {
		if(n < 0) return 2;
		return 1;
	}

	if (n < 0) counter++;

	while (number != 0) {
		number /= 10;
		counter++;
	}

	return counter;
}

void matrix::draw (int margin, int p) const
{
	cout.setf(ios::fixed);
	cout.precision(p);

	int maximum_numb_of_digits = 0, digits;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			digits = number_of_digits(m[i][j]);
			if (maximum_numb_of_digits < digits)
				maximum_numb_of_digits = digits;
		}
	}

	for (int i = 0; i < rows; i++) {
		// draw the margin first
		for (int n = 0; n < margin; n++) cout << ' ';
		for (int j = 0; j < cols; j++) {

			// fill with spaces the numbers with less digits
			digits = number_of_digits(m[i][j]);
			for (int k = 0; k < maximum_numb_of_digits-digits; k++)
				cout << ' ';

			if (m[i][j] == int(m[i][j])) {
				cout << int(m[i][j]);
				for (int k = 0; k < p+1; k++)
					cout << " ";
			}	else cout << m[i][j];

			cout << "  ";

		}
		cout << endl;
	}

	cout << defaultfloat;
}


matrix matrix::operator+ (const matrix& m) const
{
	// if both don't have the same shape, throw an exception
	if (cols != m.cols or rows != m.rows)
		throw matrix_exception(error_sum);

	matrix result (rows, cols);

	// calculate the sum for each value
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.change(i, j, this->m[i][j] + m.elm(i, j));
		}
	}

	return result;
}


matrix matrix::operator- (const matrix& m) const
{
	// if both don't have the same shape, throw an exception
	if (cols != m.cols or rows != m.rows)
		throw matrix_exception(error_sub);

	matrix result (rows, cols);

	// calculate the difference for each value
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.change(i, j, this->m[i][j] - m.elm(i, j));
		}
	}

	return result;
}


matrix matrix::operator^ (const matrix& m) const
{
	// if both don't have the same shape, throw an exception
	if (cols != m.cols or rows != m.rows)
		throw matrix_exception(error_mult);

	matrix result (rows, cols);

	// calculate the difference for each value
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.change(i, j, this->m[i][j] * m.elm(i, j));
		}
	}

	return result;
}


bool matrix::operator== (const matrix& m) const
{
	// if both don't have the same shape, they are not equal
	if (cols != m.cols or rows != m.rows)
		return false;

	// if some value is different, return false
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			if (this->m[i][j] != m.elm(i,j))
				return false;
		}
	}

	return true;
}


void matrix::operator= (const matrix& m)
{
	copy(m);
}


void matrix::operator+= (const matrix& m)
{
	// if both don't have the same shape, throw an exception
	if (cols != m.cols or rows != m.rows)
		throw matrix_exception(error_sum);

	// calculate the sum for each value
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			this->m[i][j] = this->m[i][j] + m.elm(i, j);
		}
	}
}


void matrix::operator-= (const matrix& m)
{
	// if both don't have the same shape, throw an exception
	if (cols != m.cols or rows != m.rows)
		throw matrix_exception(error_sub);

	// calculate the difference for each value
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			this->m[i][j] = this->m[i][j] - m.elm(i, j);
		}
	}
}


void matrix::operator^= (const matrix& m)
{
	// if both don't have the same shape, throw an exception
	if (cols != m.cols or rows != m.rows)
		throw matrix_exception(error_mult);

	// calculate the multiplication for each value
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			this->m[i][j] = this->m[i][j] * m.elm(i, j);
		}
	}
}


vector<double> matrix::operator[] (int row) const
{
	if (row >= rows)
		throw matrix_exception(error_bounds);
	return m[row];
}


matrix matrix::gT () const
{
	matrix result(cols, rows);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			result.change(j, i, m[i][j]);
		}
	}

	return result;
}


void matrix::T ()
{
	matrix result(cols, rows);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			result.change(j, i, m[i][j]);
		}
	}

	copy(result);
}


void matrix::multn (double n)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			m[i][j] = n * m[i][j];
		}
	}
}


matrix matrix::gmultn (double n) const
{
	matrix result(*this);

	result.multn(n);

	return result;
}


long double matrix::mod () const
{
	long double sum = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sum += pow(m[i][j], 2);
		}
	}

	return sqrt(sum);
}


matrix matrix::operator* (const matrix& m) const
{
	matrix result(rows, m.cols);
	double sum;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			sum = 0;
			for (int k = 0; k < cols; k++)
				sum += this->m[i][k] * m.m[k][j];
			result.m[i][j] = sum;
		}
	}

	return result;
}


void matrix::operator*= (const matrix& m)
{
	matrix result(rows, m.cols);
	double sum;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			sum = 0;
			for (int k = 0; k < cols; k++)
				sum += this->m[i][k] * m.m[k][j];
			result.m[i][j] = sum;
		}
	}

	copy(result);
}


void matrix::read()
{
	double n;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> n;
			change(i, j, n);
		}
	}
}


matrix matrix::gcopy () const
{
	matrix copy(*this);
	return copy;
}