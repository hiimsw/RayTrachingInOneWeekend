#include "pch.h"

int main()
{
	constexpr uint32_t IMAGE_WIDTH = 256;
	constexpr uint32_t IMAGE_HEIGHT = 256;

	std::string imageBuffer;
	imageBuffer += std::format("P3\n{} {}\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

	for (uint32_t i = 0; i < IMAGE_HEIGHT; ++i)
	{
		for (uint32_t j = 0; j < IMAGE_WIDTH; ++j)
		{
			uint32_t r = uint32_t(double(j) / (IMAGE_WIDTH - 1) * 255.0f);
			uint32_t g = uint32_t(double(i) / (IMAGE_HEIGHT - 1) * 255.0f);
			uint32_t b = uint32_t(0.0 * 255.0f);

			imageBuffer += std::format("{} {} {}\n", r, g, b);
		}
	}
	
	// Write a file to disk.
	{
		FILE* file = nullptr;
		fopen_s(&file, "image.ppm", "w");
		ASSERT(file != nullptr);

		fwrite(imageBuffer.c_str(), 1, imageBuffer.length(), file);
		fclose(file);
	}

	return 0;
}