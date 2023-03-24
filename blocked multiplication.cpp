#include <iostream>
#include<bits/stdc++.h>
#include <sys/time.h>
#include <chrono>

using namespace std;

const int n = 1024; // Size of the matrices
int block_size = 16; // Block size for blocking

int A[n][n];
int B[n][n];
int C[n][n];
int D[n][n];

void blocked_multiplication(){
    for (int i = 0; i < n; i += block_size) {
        for (int j = 0; j < n; j += block_size) {
            for (int k = 0; k < n; k += block_size) {
                for (int x = 0; x < block_size; x++) {
                    for (int y = 0 ; y < block_size; y++) {
                        for (int z = 0; z < block_size; z++) {
                            C[i+x][j+y] += A[i+x][k+z]*B[k+z][j+y];
                        }
                    }
                }
            }
        }
    }
}

void naive_multiplication(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                D[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void print_matrix(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << D[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void reset_matrix(){
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = 0;
        }
    }
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n; j++){
            D[i][j] = 0;
        }
    }
}

int main(){
    double elapsed = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = rand() % 10;
        }
    }

    reset_matrix();



    auto start_time = chrono::high_resolution_clock::now();
    blocked_multiplication();
    auto end_time = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " nanoseconds." << endl;

    auto start_time2 = chrono::high_resolution_clock::now();
    naive_multiplication();
    auto end_time2 = chrono::high_resolution_clock::now();

    auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end_time2 - start_time2);
    cout << "Time taken: " << duration2.count() << " nanoseconds." << endl;

    
}