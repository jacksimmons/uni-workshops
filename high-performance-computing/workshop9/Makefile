# Makefile for workshop 9 programs
# Load the intel/2017b module before running make


CC=icc

matmul: matmul.c 
	$(CC) -o matmul matmul.c

matmul_big: matmul_big.c
	$(CC) -fopenmp -o matmul_big matmul_big.c

dgemm: dgemm.c
	$(CC) -mkl -o dgemm dgemm.c 

dgemm_big: dgemm_big.c
	$(CC) -mkl -o dgemm_big dgemm_big.c 
