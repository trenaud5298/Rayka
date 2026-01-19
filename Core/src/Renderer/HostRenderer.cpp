// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, Tyler Renaud

// Rayka Includes
#include <Rayka/Core/Renderer/HostRenderer.h>
#include <Rayka/Core/Scene/Scene.h>

// C++ Includes
#include <iostream>


namespace Rayka {

bool saveBMP(const char* filename, int width, int height, const uint8_t* rgbData)
{
	// BMP row padding: each row must be multiple of 4 bytes
	int rowSize = (width * 3 + 3) & ~3; // round up to nearest multiple of 4
	int dataSize = rowSize * height;

	// BMP file header
	uint8_t fileHeader[14] = {
		'B','M',                      // Signature
		0,0,0,0,                      // File size (filled later)
		0,0,                          // Reserved
		0,0,                          // Reserved
		54,0,0,0                      // Pixel data offset (14+40)
	};

	uint8_t infoHeader[40] = {0};
	infoHeader[0] = 40;               // Header size
	*(int32_t*)(infoHeader + 4) = width;
	*(int32_t*)(infoHeader + 8) = height;
	*(int16_t*)(infoHeader + 12) = 1;  // planes
	*(int16_t*)(infoHeader + 14) = 24; // bits per pixel
	// rest (compression, image size, etc.) left as 0

	int fileSize = 14 + 40 + dataSize;
	*(int32_t*)(fileHeader + 2) = fileSize;

	FILE* f = std::fopen(filename, "wb");
	if (!f) return false;

	std::fwrite(fileHeader, 1, 14, f);
	std::fwrite(infoHeader, 1, 40, f);

	// write pixel data bottom-up
	uint8_t padding[3] = {0,0,0};
	for (int y = height - 1; y >= 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			const uint8_t* pixel = rgbData + (y * width + x) * 3;
			uint8_t bgr[3] = { pixel[2], pixel[1], pixel[0] }; // BGR order
			std::fwrite(bgr, 1, 3, f);
		}
		std::fwrite(padding, 1, rowSize - width*3, f); // row padding
	}

	std::fclose(f);
	return true;
}

void HostRenderer::render(const Scene& scene) {
	std::cout << "Rendering" << std::endl;

	std::uint32_t resolution[2] = {800, 600};
	std::uint8_t* imageData = new std::uint8_t[resolution[0] * resolution[1] * 3];
	for (int y = 0; y < resolution[1]; ++y) {
		for (int x = 0; x < resolution[0]; ++x) {
			std::uint32_t pixelIndex = (y * resolution[0] + x) * 3;
			imageData[pixelIndex] = 255*x/resolution[0];
			imageData[pixelIndex + 1] = 255*y/resolution[0];
			imageData[pixelIndex + 2] = 255;
		}
	}
	saveBMP("test.bmp", resolution[0], resolution[1], imageData);
	delete[] imageData;
	std::cout << "done" << std::endl;
}

}