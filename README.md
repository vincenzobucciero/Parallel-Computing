# Parallel-Computing - Laboratory Part

This repository has been created specifically to support the Parallel Computing - Laboratory Part course within the Computer Science exam at the University of Naples "Parthenope". The OpenMP library is used for implementing the parallel programs in the repository.

# Getting Started

Clone the repository to your local system using git clone:
```
git clone https://github.com/your-username/Calcolo-Parallelo.git
```

# Repository contents

The repository contains several computational kernels implemented using OpenMP. The included computational kernels are as follows:

  *  Sum of N numbers: Parallel implementation of the sum of N numbers.
  *  Sum of two N-length vectors: Parallel implementation of the sum of two N-length vectors.
  *  Scalar product of two vectors: Parallel implementation of the scalar product of two vectors.
  *  Matrix x vector: Parallel implementation of the product between a matrix and a vector using two data collection strategies: strategy 1 and strategy 2.
  *  Matrix block decomposition: Parallel implementation of the block decomposition of a matrix using three strategies: strategy 1 row blocks, strategy 2 column blocks, and strategy 3 row-column blocks.
  *  SAXPY: Parallel implementation of the "SAXPY" problem, a common mathematical problem that can be parallelized and is used in various fields.
  *  Exercises: Various exercises on parallel computing.

# Using OpenMP

All the programs in the repository make use of the capabilities offered by the OpenMP library for parallel programming. OpenMP provides high-level directives such as #pragma omp parallel for, #pragma omp parallel sections, etc., which simplify the implementation of parallelism. Additionally, in some cases, the #pragma omp parallel directive is exclusively used to manually manage the distribution of work to the threads generated after the fork-join.

# Contributing
If you wish to contribute to this project, you can clone the repository, make the desired modifications, and submit a pull request. It will be reviewed and integrated if deemed appropriate. This repository serves as a reference for students who wish to explore the world of parallel computing and discover the wonders of distributed computing.
