
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Matrix {
public:
    int matrix_size;
    double** matrix_data;

    Matrix(int size = 0) : matrix_size(size) { // Constructor, and matrix_size set = to size
        matrix_data = new double*[matrix_size]; // Creates an array of matrix_size elements, where each element is a pointer to a double -- rows of matrix. Each element points to an array representing a row in the matrix
        for (int i = 0; i < matrix_size; ++i) { // Iterate over each row
            matrix_data[i] = new double[matrix_size]; // Initialize row in matrix
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;

        matrix_size = other.matrix_size;

        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }

        return *this;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix added_matrix(matrix_size);
        int sum;
        for (int i=0; i < matrix_size; i++) {
            for (int j=0; j < matrix_size; j++) {
                sum = matrix_data[i][j] + other.matrix_data[i][j];
                added_matrix.matrix_data[i][j] = sum;
            }
        }
        return added_matrix;
    }

    Matrix operator*(const Matrix& other) const {
        int size = matrix_size;
        Matrix product_matrix(size);
        for (int i=0; i < size; i++) {
            for (int j=0; j < size; j++) {
                for (int k=0; k < size; k++) {
                    // Add dot product of each row/column pair to corresponding product_matrix entry
                    product_matrix.matrix_data[i][j] += matrix_data[i][k]*other.matrix_data[k][j];
                }
            }
        }
        return product_matrix;
    }

    ~Matrix() {
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }
};


void read_matrix_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
    // TODO: Read matrix data from the file
    // Make sure to handle potential errors and invalid input
    // Create an input file stream object named 'file' and
    // open the file
    ifstream file(file_name);

    // String to store each line of the file.
    // string line;
    int size;
    file >> size;
    matrix_1 = Matrix(size);
    matrix_2 = Matrix(size);

    if (file.is_open()) {
        // Read each line from the file and store it in the
        // 'line' variable.
        for (int i=0; i < size; i++) {
            for (int j=0; j < size; j++){
                file >> matrix_1.matrix_data[i][j];
            }
        }

        for (int i=0; i < size; i++) {
            for (int j=0; j < size; j++){
                file >> matrix_2.matrix_data[i][j];
            }
        }

        // Close the file stream once all lines have been
        // read.
        file.close();
    }
    
    else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        cerr << "Unable to open file!" << endl;
    }
}

void print_matrix(const Matrix& matrix) {
    for (int i=0; i < matrix.matrix_size; i++) {
        for (int j=0; j < matrix.matrix_size; j++) {
            cout << matrix.matrix_data[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) {
    print_matrix(matrix_1);
    print_matrix(matrix_2);
}

Matrix add_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    int size = matrix_1.matrix_size;
    Matrix added_matrix(matrix_1.matrix_size); // Create matrix to store sum of matrices
    
    // Iterate through matrix and sum matrices for each element
    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            int sum = matrix_1.matrix_data[i][j] + matrix_2.matrix_data[i][j];
            added_matrix.matrix_data[i][j] = sum;
        }
    }
    return added_matrix;
}

Matrix multiply_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    // TODO: Implement matrix multiplication
    int size = matrix_1.matrix_size;
    Matrix product_matrix(size);
    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            for (int k=0; k < size; k++) {
                // Add dot product of each row/column pair to corresponding product_matrix entry
                product_matrix.matrix_data[i][j] += matrix_1.matrix_data[i][k]*matrix_2.matrix_data[k][j];
            }
        }
    }
    return product_matrix;
}

// Overloaded + operator for matrix addition
// Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2);

// Overloaded * operator for matrix multiplication
// Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2);

void get_diagonal_sum(const Matrix& matrix) {
    int sum = 0;
    int center;
    int isOdd = matrix.matrix_size % 2 == 1;
    if (isOdd) {
        center = matrix.matrix_size / 2 + 1;
    }
    // Iterate through main diagonal and sum each diagonal
    for (int i=0; i < matrix.matrix_size; i++) {
        // Don't sum center, as it will be summed in secondary diagonal loop
        if (isOdd && i == center) {
            continue;
        }
        sum += matrix.matrix_data[i][i];
    }

    // Iterate through and sum secondary diagonals
    for (int i=0; i < matrix.matrix_size; i++) {
        sum += matrix.matrix_data[i][matrix.matrix_size - i];
    }
    cout << "Sum of diagonals: " << sum << endl;
}

void swap_matrix_row(Matrix& matrix, int row1, int row2) {
    // TODO: Swap the rows 'row1' and 'row2' in the matrix
    //    Handle invalid row indices
}

int main(int argc, char* argv[]) {
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);

    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);

    cout << "add_matrices result:" << endl;
    Matrix add_result_1 = add_matrices(matrix_1, matrix_2);
    Matrix add_result_2 = matrix_1 + matrix_2;
    print_matrix(add_result_1);
    print_matrix(add_result_2);

    cout << "multiply_matrices result:" << endl;
    Matrix multiply_result_1 = multiply_matrices(matrix_1, matrix_2);
    Matrix multiply_result_2 = matrix_1 * matrix_2;
    print_matrix(multiply_result_1);
    print_matrix(multiply_result_2);

    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);

    // cout << "swap matrix rows" << endl;
    // swap_matrix_row(matrix_1, 0, 1);

    return 0;
}