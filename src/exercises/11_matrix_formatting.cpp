#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <sstream>

// ============================================================
// EXERCISE 11: Matrix Operations and Terminal Formatting
// ============================================================

// Terminal color codes (ANSI escape sequences)
namespace TermColor {
    inline const char* RESET    = "\033[0m";
    inline const char* BOLD     = "\033[1m";
    inline const char* RED      = "\033[31m";
    inline const char* GREEN    = "\033[32m";
    inline const char* YELLOW   = "\033[33m";
    inline const char* BLUE     = "\033[34m";
    inline const char* MAGENTA  = "\033[35m";
    inline const char* CYAN     = "\033[36m";
    inline const char* WHITE    = "\033[37m";
    inline const char* BG_RED   = "\033[41m";
    inline const char* BG_GREEN = "\033[42m";
    inline const char* BG_BLUE  = "\033[44m";
}

class Matrix {
public:
    Matrix(size_t rows, size_t cols, double init = 0.0)
        : rows_(rows), cols_(cols), data_(rows * cols, init) {}

    double& at(size_t r, size_t c) {
        validate(r, c);
        return data_[r * cols_ + c];
    }

    double at(size_t r, size_t c) const {
        validate(r, c);
        return data_[r * cols_ + c];
    }

    size_t rowCount() const { return rows_; }
    size_t colCount() const { return cols_; }

    static Matrix identity(size_t n) {
        Matrix m(n, n);
        for (size_t i = 0; i < n; ++i) m.at(i, i) = 1.0;
        return m;
    }

    static Matrix zeros(size_t r, size_t c) { return Matrix(r, c, 0.0); }
    static Matrix ones(size_t r, size_t c) { return Matrix(r, c, 1.0); }

    Matrix operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::invalid_argument("Matrix dimensions must match for addition");
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < data_.size(); ++i)
            result.data_[i] = data_[i] + other.data_[i];
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::invalid_argument("Matrix dimensions must match for subtraction");
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < data_.size(); ++i)
            result.data_[i] = data_[i] - other.data_[i];
        return result;
    }

    Matrix operator*(double scalar) const {
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < data_.size(); ++i)
            result.data_[i] = data_[i] * scalar;
        return result;
    }

    Matrix multiply(const Matrix& other) const {
        if (cols_ != other.rows_)
            throw std::invalid_argument("Columns of A must equal rows of B");
        Matrix result(rows_, other.cols_);
        for (size_t i = 0; i < rows_; ++i)
            for (size_t j = 0; j < other.cols_; ++j)
                for (size_t k = 0; k < cols_; ++k)
                    result.at(i, j) += at(i, k) * other.at(k, j);
        return result;
    }

    Matrix transpose() const {
        Matrix t(cols_, rows_);
        for (size_t i = 0; i < rows_; ++i)
            for (size_t j = 0; j < cols_; ++j)
                t.at(j, i) = at(i, j);
        return t;
    }

    double trace() const {
        if (rows_ != cols_) throw std::runtime_error("Trace requires square matrix");
        double sum = 0;
        for (size_t i = 0; i < rows_; ++i) sum += at(i, i);
        return sum;
    }

    void print(const std::string& title = "", const char* color = "") const {
        if (!title.empty()) {
            std::cout << color << TermColor::BOLD << title << TermColor::RESET << "\n";
        }
        for (size_t i = 0; i < rows_; ++i) {
            std::cout << (i == 0 ? "[" : " ");
            for (size_t j = 0; j < cols_; ++j) {
                std::cout << std::setw(8) << std::fixed << std::setprecision(2) << at(i, j);
                std::cout << (j == cols_ - 1 ? "" : ",");
            }
            std::cout << (i == rows_ - 1 ? "]" : "") << "\n";
        }
    }

private:
    void validate(size_t r, size_t c) const {
        if (r >= rows_ || c >= cols_)
            throw std::out_of_range("Matrix index out of range");
    }
    size_t rows_, cols_;
    std::vector<double> data_;
};

// ============================================================
// CONCEPT: Matrix Basics
// - 2D data stored in flat vector (row-major order)
// - Index: data[row * cols + col]
// - Identity matrix has 1s on diagonal, 0s elsewhere

void example_matrix_basics() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== Matrix Basics ===" << TermColor::RESET << "\n";

    Matrix A(2, 3);
    A.at(0, 0) = 1; A.at(0, 1) = 2; A.at(0, 2) = 3;
    A.at(1, 0) = 4; A.at(1, 1) = 5; A.at(1, 2) = 6;
    A.print("Matrix A (2x3):", TermColor::CYAN);

    Matrix I = Matrix::identity(3);
    I.print("Identity (3x3):", TermColor::CYAN);

    Matrix Z = Matrix::zeros(2, 2);
    Z.print("Zeros (2x2):", TermColor::CYAN);

    std::cout << TermColor::YELLOW << "Trace of identity(4): "
              << Matrix::identity(4).trace() << TermColor::RESET << "\n";
}

// CHALLENGE 11.1: Create a 3x3 matrix filled with values 1-9 (row by row).
// Print it. Then compute and print its transpose.
void challenge_matrix_basics() {
    std::cout << "\n--- Challenge 11.1: Create and transpose ---\n";

    // TODO: Create a 3x3 Matrix

    // TODO: Fill with values 1,2,3 / 4,5,6 / 7,8,9

    // TODO: Print the matrix

    // TODO: Compute and print the transpose

    std::cout << "Challenge 11.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Matrix Operations (Add, Subtract, Multiply, Scale)
// - Addition/subtraction: element-wise, same dimensions required
// - Scalar multiplication: each element multiplied by scalar
// - Matrix multiplication: dot product of rows and columns (MxN * NxP = MxP)

void example_matrix_operations() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== Matrix Operations ===" << TermColor::RESET << "\n";

    Matrix A(2, 2);
    A.at(0,0)=1; A.at(0,1)=2; A.at(1,0)=3; A.at(1,1)=4;
    A.print("A:", TermColor::CYAN);

    Matrix B(2, 2);
    B.at(0,0)=5; B.at(0,1)=6; B.at(1,0)=7; B.at(1,1)=8;
    B.print("B:", TermColor::CYAN);

    (A + B).print("A + B:", TermColor::MAGENTA);
    (A - B).print("A - B:", TermColor::MAGENTA);
    (A * 3.0).print("A * 3:", TermColor::MAGENTA);
    A.multiply(B).print("A x B:", TermColor::MAGENTA);
}

// CHALLENGE 11.2: Create two 3x3 matrices:
//   X = [[1,0,0],[0,1,0],[0,0,1]] (identity)
//   Y = [[2,3,4],[5,6,7],[8,9,10]]
// Compute X * Y (matrix multiply) and Y * 2 (scalar).
// Verify X * Y equals Y (identity property).
void challenge_matrix_operations() {
    std::cout << "\n--- Challenge 11.2: Identity and scaling ---\n";

    // TODO: Create identity matrix X (3x3)

    // TODO: Create matrix Y with values 2-10

    // TODO: Compute X * Y (matrix multiply) and print

    // TODO: Compute Y * 2 (scalar multiply) and print

    // TODO: Verify that X * Y == Y (identity property)

    std::cout << "Challenge 11.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Terminal Color Output (ANSI Escape Codes)
// - \033[Nm sets a graphics mode (N = color code)
// - \033[0m resets to default
// - Foreground: 30-37 (black,red,green,yellow,blue,magenta,cyan,white)
// - Background: 40-47
// - Bold: \033[1m
// - Works on most Unix terminals and modern Windows

void example_terminal_colors() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== Terminal Color Output ===" << TermColor::RESET << "\n";

    std::cout << "Foreground colors:\n";
    std::cout << TermColor::RED    << "  Red"     << TermColor::RESET << "\n";
    std::cout << TermColor::GREEN  << "  Green"   << TermColor::RESET << "\n";
    std::cout << TermColor::YELLOW << "  Yellow"  << TermColor::RESET << "\n";
    std::cout << TermColor::BLUE   << "  Blue"    << TermColor::RESET << "\n";
    std::cout << TermColor::MAGENTA<< "  Magenta" << TermColor::RESET << "\n";
    std::cout << TermColor::CYAN   << "  Cyan"    << TermColor::RESET << "\n";

    std::cout << "Background colors:\n";
    std::cout << TermColor::BG_RED   << "  BG Red   " << TermColor::RESET << "\n";
    std::cout << TermColor::BG_GREEN << "  BG Green " << TermColor::RESET << "\n";
    std::cout << TermColor::BG_BLUE  << "  BG Blue  " << TermColor::RESET << "\n";

    std::cout << TermColor::BOLD << "  Bold text" << TermColor::RESET << "\n";
    std::cout << TermColor::BOLD << TermColor::RED << "  Bold Red"
              << TermColor::RESET << "\n";
}

// CHALLENGE 11.3: Create a function that prints a colored status bar.
// Print "SUCCESS" in green, "WARNING" in yellow, "ERROR" in red.
// Each should be bold and on its own line with a [bracket] format.
void challenge_terminal_colors() {
    std::cout << "\n--- Challenge 11.3: Colored status messages ---\n";

    // TODO: Print "[SUCCESS]" in bold green

    // TODO: Print "[WARNING]" in bold yellow

    // TODO: Print "[ERROR]" in bold red

    // TODO: Print "[INFO]" in bold cyan

    std::cout << "Challenge 11.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Colored Matrix Display
// - Highlight specific values with colors
// - Negative values in red, positive in green
// - Diagonal elements in bold

void example_colored_matrix() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== Colored Matrix Display ===" << TermColor::RESET << "\n";

    Matrix M(3, 3);
    M.at(0,0)=-5;  M.at(0,1)=10;  M.at(0,2)=-3;
    M.at(1,0)=8;   M.at(1,1)=15;  M.at(1,2)=-7;
    M.at(2,0)=-2;  M.at(2,1)=4;   M.at(2,2)=20;

    std::cout << "Matrix with colored values (red=negative, green=positive, bold=diagonal):\n";
    for (size_t i = 0; i < M.rowCount(); ++i) {
        std::cout << (i == 0 ? "[" : " ");
        for (size_t j = 0; j < M.colCount(); ++j) {
            double val = M.at(i, j);
            bool isDiag = (i == j);
            if (isDiag) std::cout << TermColor::BOLD;
            if (val < 0) std::cout << TermColor::RED;
            else if (val > 0) std::cout << TermColor::GREEN;
            std::cout << std::setw(8) << std::fixed << std::setprecision(1) << val;
            std::cout << TermColor::RESET;
            std::cout << (j == M.colCount()-1 ? "" : ",");
        }
        std::cout << (i == M.rowCount()-1 ? "]" : "") << "\n";
    }
}

// CHALLENGE 11.4: Create a 4x4 matrix with random-ish values (use any numbers).
// Print it with: values > 10 in cyan, values < 0 in red, values 0-10 in yellow.
void challenge_colored_matrix() {
    std::cout << "\n--- Challenge 11.4: Custom colored matrix ---\n";

    // TODO: Create a 4x4 Matrix with varied values

    // TODO: Print with custom coloring: >10 cyan, <0 red, 0-10 yellow

    std::cout << "Challenge 11.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Matrix Utility Operations
// - Frobenius norm: sqrt(sum of all squared elements)
// - Element-wise operations
// - Submatrix extraction

void example_matrix_utilities() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== Matrix Utilities ===" << TermColor::RESET << "\n";

    Matrix A(3, 3);
    A.at(0,0)=3; A.at(0,1)=0; A.at(0,2)=2;
    A.at(1,0)=2; A.at(1,1)=0; A.at(1,2)=-1;
    A.at(2,0)=1; A.at(2,1)=4; A.at(2,2)=5;
    A.print("Matrix A:", TermColor::CYAN);

    double frobeniusNorm = 0;
    for (size_t i = 0; i < A.rowCount(); ++i)
        for (size_t j = 0; j < A.colCount(); ++j)
            frobeniusNorm += A.at(i,j) * A.at(i,j);
    frobeniusNorm = std::sqrt(frobeniusNorm);
    std::cout << TermColor::YELLOW << "Frobenius norm: " << std::setprecision(2)
              << frobeniusNorm << TermColor::RESET << "\n";

    std::cout << TermColor::YELLOW << "Max element: ";
    double maxVal = -1e18;
    for (size_t i = 0; i < A.rowCount(); ++i)
        for (size_t j = 0; j < A.colCount(); ++j)
            if (A.at(i,j) > maxVal) maxVal = A.at(i,j);
    std::cout << maxVal << TermColor::RESET << "\n";
}

// CHALLENGE 11.5: Create a 3x3 matrix and compute:
// - Sum of all elements
// - Average of all elements
// - Count of positive, negative, and zero elements
void challenge_matrix_utilities() {
    std::cout << "\n--- Challenge 11.5: Matrix statistics ---\n";

    // TODO: Create a 3x3 matrix with mixed positive/negative/zero values

    // TODO: Compute and print sum of all elements

    // TODO: Compute and print average

    // TODO: Count and print positive, negative, zero counts

    std::cout << "Challenge 11.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: 2D Transformation Matrices
// - 3x3 matrices used in computer graphics
// - Translation, rotation, scaling
// - Applied via matrix multiplication

void example_transformation_matrices() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== 2D Transformation Matrices ===" << TermColor::RESET << "\n";

    double angle = 45.0 * 3.14159265 / 180.0;
    Matrix rotation(3, 3);
    rotation.at(0,0) = std::cos(angle); rotation.at(0,1) = -std::sin(angle); rotation.at(0,2) = 0;
    rotation.at(1,0) = std::sin(angle); rotation.at(1,1) =  std::cos(angle); rotation.at(1,2) = 0;
    rotation.at(2,0) = 0;               rotation.at(2,1) = 0;               rotation.at(2,2) = 1;
    rotation.print("Rotation 45 degrees:", TermColor::CYAN);

    Matrix scale(3, 3);
    scale.at(0,0)=2; scale.at(0,1)=0; scale.at(0,2)=0;
    scale.at(1,0)=0; scale.at(1,1)=3; scale.at(1,2)=0;
    scale.at(2,0)=0; scale.at(2,1)=0; scale.at(2,2)=1;
    scale.print("Scale (2x, 3y):", TermColor::CYAN);

    Matrix translate(3, 3);
    translate.at(0,0)=1; translate.at(0,1)=0; translate.at(0,2)=5;
    translate.at(1,0)=0; translate.at(1,1)=1; translate.at(1,2)=10;
    translate.at(2,0)=0; translate.at(2,1)=0; translate.at(2,2)=1;
    translate.print("Translate (+5, +10):", TermColor::CYAN);

    Matrix point(3, 1);
    point.at(0,0)=1; point.at(1,0)=1; point.at(2,0)=1;
    point.print("Point (1, 1):", TermColor::CYAN);

    Matrix transformed = rotation.multiply(scale.multiply(translate.multiply(point)));
    transformed.print("Transformed point:", TermColor::MAGENTA);
}

// CHALLENGE 11.6: Create a point (3, 4) in homogeneous coordinates.
// Apply a scaling matrix (0.5x, 2y) then a translation (+10, -5).
// Print the final transformed point.
void challenge_transformation_matrices() {
    std::cout << "\n--- Challenge 11.6: Transform a point ---\n";

    // TODO: Create point (3, 4, 1) as 3x1 matrix

    // TODO: Create scale matrix (0.5x, 2y)

    // TODO: Create translation matrix (+10, -5)

    // TODO: Apply scale then translation to the point

    // TODO: Print the final transformed point

    std::cout << "Challenge 11.6 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_matrix_formatting() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 11: Matrix Operations and Terminal Formatting\n";
    std::cout << "========================================\n";

    example_matrix_basics();
    challenge_matrix_basics();

    example_matrix_operations();
    challenge_matrix_operations();

    example_terminal_colors();
    challenge_terminal_colors();

    example_colored_matrix();
    challenge_colored_matrix();

    example_matrix_utilities();
    challenge_matrix_utilities();

    example_transformation_matrices();
    challenge_transformation_matrices();

    std::cout << "\n========================================\n";
    std::cout << "Matrix and Formatting exercise complete!\n";
    std::cout << "========================================\n";
}
