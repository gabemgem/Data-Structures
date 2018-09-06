#include "Matrix.h"
#include <iostream>
#include <cstddef>



using namespace std;


Matrix::Matrix()//default constructor
{
	rows=0;
	cols=0;
}

Matrix::Matrix(const Matrix& m)//copy constructor
{
	rows=m.num_rows();
	cols=m.num_cols();
	
	mat = new double*[rows];
	
	for(unsigned int i=0; i<rows; i++)//creates 2d array
		mat[i]=new double[cols];
	
	for(unsigned int r=0; r<rows; r++) {//fills 2d array
		for(unsigned int c=0; c<cols; c++) {
			double val;
			m.get(r,c,val);
			mat[r][c]=val;
		}
	}
}

Matrix::Matrix(unsigned int r, unsigned int c, double f)//normal constructor
{
	if(r==0 || c==0)//sets size to 0 if r or c is 0
	{
		rows=0;
		cols=0;
		return;
	}
	
	rows=r;
	cols=c;
	
	mat = new double*[rows];
	
	for(unsigned int i=0; i<rows; i++)//creates 2d array
		mat[i]=new double[cols];
	
	for(unsigned int j=0; j<rows; j++)//fills array with fill double
		for(unsigned int k=0; k<cols; k++)
			mat[j][k]=f;
		
}

Matrix::~Matrix()//destructor
{
	clear();
}

Matrix& Matrix::operator=(const Matrix& m)//assignment operator
{
	if(*this==m)//don't do anything if this and other matrix are already the same
		return *this;
	
	/*for(unsigned int r=0; r<rows; r++)
		delete [] mat[r];
	//delete [] mat;*/
	clear();//clears out the matrix
	
	rows=m.num_rows();
	cols=m.num_cols();
	
	mat = new double*[rows];//makes new matrix
	
	for(unsigned int i=0; i<rows; i++)
		mat[i]=new double[cols];
	
	for(unsigned int r=0; r<rows; r++) {//fills 2d array
		for(unsigned int c=0; c<cols; c++) {
			double val=0;
			m.get(r,c,val);
			mat[r][c]=val;
		}
	}
	
	return *this;
}

bool Matrix::operator==(const Matrix& m) const //== operator
{
	if(rows!=m.num_rows() || cols!=m.num_cols())//check size
		return false;
	
	for(unsigned int i=0; i<rows; i++)//check values
	{
		for(unsigned int j=0; j<cols; j++)
		{
			double val;
			m.get(i,j,val);
			if(mat[i][j]!=val)
				return false;
		}
	}
	
	return true;
}

bool Matrix::operator!=(const Matrix& m) const//!= operator
{
	return !operator==(m);//is the opposite of == operator
}

unsigned int Matrix::num_rows() const//returns number of rows
{
	return rows;
}

unsigned int Matrix::num_cols() const//returns number of columns
{
	return cols;
}

void Matrix::clear()//clears matrix
{
	if(rows!=0 && cols!=0) {//makes sure matrix isn't already clear
	for(unsigned int i=0; i<rows; i++)
		delete [] mat[i];//deletes elements
	
	delete [] mat;//deletes rows
	}
	rows=0;
	cols=0;
}

bool Matrix::get(unsigned int r, unsigned int c, double& val) const
{//returns an element of the matrix in val
	
	if(r>=rows || c>=cols)//check that element is in the bounds of the matrix
		return false;
	
	val=mat[r][c];//gets the element
	return true;
}

bool Matrix::set(unsigned int r, unsigned int c, double val)
{//sets an element in the matrix to val
	if(r>=rows || c>=cols)//checks if in bounds
		return false;
	
	mat[r][c]=val;//sets element
	return true;
}

void Matrix::multiply_by_coefficient(double d)//multiplies matrix by a number
{
	for(unsigned int i=0; i<rows; i++)//loops through and multiplies each element
		for(unsigned int j=0; j<cols; j++)
			mat[i][j]*=d;
}

bool Matrix::swap_row(unsigned int r1, unsigned int r2)//swaps two rows
{
	if(r1>=rows || r2>=rows)//checks if in bounds
		return false;
	
	double *temp=new double[cols];//makes a temp array
	
	for(unsigned int i=0; i<cols; i++)//loops through the row
	{
		temp[i]=mat[r1][i];//copies first row to temp
		mat[r1][i]=mat[r2][i];//copies second row to first row
		mat[r2][i]=temp[i];//copies temp to second row
	}
	delete [] temp;//deletes temp
	return true;
}

void Matrix::transpose()//transposes matrix
{
	Matrix temp = Matrix(cols, rows, 0);
	
	for(unsigned int r=0; r<rows; r++) {
		for(unsigned int c=0; c<cols; c++) {
			temp.set(c,r, mat[r][c]);
		}
	}
		
	
	*this=temp;//sets matrix = to temp matrix
	
	temp.clear();//deletes temporary new matrix
}

bool Matrix::add(const Matrix& m)//adds a matrix to this matrix
{
	if(rows!=m.num_rows() || cols!=m.num_cols())//checks size
		return false;
	
	for(unsigned int r=0; r<rows; r++) {//loops through and adds elements
		for(unsigned int c=0; c<cols; c++) {
			double val=0;
			m.get(r, c, val);
			mat[r][c]+=val;
		}
	}
	return true;
}

bool Matrix::subtract(const Matrix& m)//subtracts a matrix from this matrix
{
	if(rows!=m.num_rows() || cols!=m.num_cols())//checks size
		return false;
	
	for(unsigned int r=0; r<rows; r++) {//loops through and subtracts elements
		for(unsigned int c=0; c<cols; c++) {
			double val=0;
			m.get(r, c, val);
			mat[r][c]-=val;
		}
	}
	return true;
}

double* Matrix::get_row(unsigned int r)//returns a row of the matrix
{
	double* row = NULL;//makes new row that's null
	
	if(r<rows)//check if requested row is in bounds
	{
		row = new double[cols];
		for(unsigned int c=0; c<cols; c++)//fills the row to return
			row[c]=mat[r][c];
	}
	
	return row;//returns the row
}

double* Matrix::get_col(unsigned int c)//returns a column of the matrix
{
	double* col = NULL;//makes new column that's null
	
	if(c<cols)//check if requested column is in bounds
	{
		col = new double[rows];
		for(unsigned int r=0; r<rows; r++)//fills the column to return
			col[r]=mat[r][c];
	}
	
	return col;//returns the column
}

Matrix* Matrix::quarter() const//returns an array of matricies that
{							   //that is this matrix quartered
	
	unsigned int r=(double(rows)/2)+0.5, c=(double(cols)/2)+0.5;
	//sets size of the quartered matricies rounded correctly
	
	Matrix* quart = new Matrix[4];//makes array of matricies
	
	Matrix ul = Matrix(r,c,0.0), ur = Matrix(r,c,0.0);//makes temp matricies
	Matrix ll = Matrix(r,c,0.0), lr = Matrix(r,c,0.0);
	
	for(unsigned int i=0; i<r; i++)//fills UL matrix
		for(unsigned int j=0; j<c; j++)
			ul.set(i,j,mat[i][j]);
		
	for(unsigned int i=0; i<r; i++)//fills UR matrix
		for(unsigned int j=0; j<c; j++)
			ur.set(i,j,mat[i][j+c]);
		
	for(unsigned int i=0; i<r; i++)//fills LL matrix
		for(unsigned int j=0; j<c; j++)
			ll.set(i,j,mat[i+r-1][j]);
		
	for(unsigned int i=0; i<r; i++)//fills LR matrix
		for(unsigned int j=0; j<c; j++)
			lr.set(i,j,mat[i+r-1][j+c]);
		
	quart[0]=ul; quart[1]=ur; quart[2]=ll; quart[3]=lr;//puts temp matricies into array
	
	return quart;//returns array
}


ostream& operator<< (ostream& out, const Matrix& m)//output operator
{
	out<<m.num_rows()<<" x "<<m.num_cols()<<" matrix:\n[";
	//outputs size and opening bracket
	
	for(unsigned int i=0; i<m.num_rows(); i++) {//outputs elements
		for(unsigned int j=0; j<m.num_cols(); j++) {
			double val=0;
			m.get(i,j,val);
			out<<" "<<val;
		}
		if(i!=m.num_rows()-1)
			out<<endl<<" ";
	}
	out<<" ]"<<endl<<endl;//outputs closing bracket
	
	return out;
}
	
	


