/*
 * Project: Rayka
 * Copyright (c) 2026, Tyler Renaud
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <Rayka/CUDA/CUDATest.h>

#include <cuda_runtime.h>
#include <iostream>

// Simple CUDA kernel
__global__ void addKernel(int a, int b, int* result)
{
    *result = a + b;
}

void CUDATest()
{
    int hostResult = 0;
    int* deviceResult = nullptr;

    // Allocate device memory
    cudaError_t err = cudaMalloc(&deviceResult, sizeof(int));
    if (err != cudaSuccess) {
        std::cerr << "cudaMalloc failed: "
                  << cudaGetErrorString(err) << std::endl;
        return;
    }

    // Launch kernel (1 block, 1 thread)
    addKernel<<<1, 1>>>(2, 3, deviceResult);

    // Check kernel launch
    err = cudaGetLastError();
    if (err != cudaSuccess) {
        std::cerr << "Kernel launch failed: "
                  << cudaGetErrorString(err) << std::endl;
        cudaFree(deviceResult);
        return;
    }

    // Copy result back to host
    err = cudaMemcpy(&hostResult, deviceResult, sizeof(int), cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) {
        std::cerr << "cudaMemcpy failed: "
                  << cudaGetErrorString(err) << std::endl;
        cudaFree(deviceResult);
        return;
    }

    // Clean up
    cudaFree(deviceResult);

    std::cout << "CUDA test passed: 2 + 3 = " << hostResult << std::endl;
}
