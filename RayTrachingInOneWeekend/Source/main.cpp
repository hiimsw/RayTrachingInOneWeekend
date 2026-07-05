#include "pch.h"
#include "Util.h"

[[nodiscard]] static Color GetRayColor(const Ray& ray);

int main()
{
	constexpr float ASPECT_RATIO = 16.0f / 9.0f;
	constexpr uint32_t IMAGE_WIDTH = 400;
	constexpr uint32_t IMAGE_HEIGHT = uint32_t(max(IMAGE_WIDTH / ASPECT_RATIO, 1.0f));

	constexpr float VIEWPORT_HEIGHT = 2.0f; // -1~1 범위를 갖도록 2.0을 설정한다.
	constexpr float VIEWPORT_WIDTH = float(IMAGE_WIDTH) / IMAGE_HEIGHT * VIEWPORT_HEIGHT;
	
	constexpr Vector3 VIEWPORT_U = Vector3(VIEWPORT_WIDTH, 0.0f, 0.0f);
	constexpr Vector3 VIEWPORT_V = Vector3(0.0f, -VIEWPORT_HEIGHT, 0.0f);

	constexpr Vector3 PIXEL_DELTA_U = VIEWPORT_U / float(IMAGE_WIDTH);
	constexpr Vector3 PIXEL_DELTA_V = VIEWPORT_V / float(IMAGE_HEIGHT);

	constexpr float FOCAL_LENGTH = 1.0f;
	constexpr Point3 CAMERA_CENTER{};
	constexpr Vector3 VIEWPORT_LEFT_TOP = CAMERA_CENTER - Vector3(0.0f, 0.0f, FOCAL_LENGTH) - (VIEWPORT_U * 0.5f) - (VIEWPORT_V * 0.5f);
	constexpr Vector3 PIXEL00_LOCATION = VIEWPORT_LEFT_TOP + 0.5f * (PIXEL_DELTA_U + PIXEL_DELTA_V);

	std::string imageBuffer;
	imageBuffer += std::format("P3\n{} {}\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

	for (uint32_t i = 0; i < IMAGE_HEIGHT; ++i)
	{
		printf("\rscanlines remaining: %d ", IMAGE_HEIGHT - i);
		fflush(stdout);

		for (uint32_t j = 0; j < IMAGE_WIDTH; ++j)
		{
			Vector3 pixelCenter = PIXEL00_LOCATION + (float(j) * PIXEL_DELTA_U) + (float(i) * PIXEL_DELTA_V);
			Vector3 rayDirection = Normalize(pixelCenter - CAMERA_CENTER);
			Ray ray{ .Origin = CAMERA_CENTER, .Direction = rayDirection };

			float r = GetLength(Vector3(pixelCenter.X, pixelCenter.Y, 0.0f) - Vector3(CAMERA_CENTER.X, CAMERA_CENTER.Y, 0.0f));
			if (r <= 0.5f)
			{
				Color color{ 0.5f, 0.5f, 0.0f };
				WriteColor(&imageBuffer, color);
			}
			else
			{
				Color color = GetRayColor(ray);
				WriteColor(&imageBuffer, color);
			}
		}
	}

	printf("\rdone.                 \n");
	fflush(stdout);

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

Color GetRayColor(const Ray& ray)
{
	constexpr Color TOP_COLOR{ 0.5f, 0.7f, 1.0f };
	constexpr Color BOTTOM_COLOR{ 1.0f, 1.0, 1.0 };

	const Vector3 rayDirection = Normalize(ray.Direction);
	const float a = 0.5f * (rayDirection.Y + 1.0f);
	const Color color = Lerp(BOTTOM_COLOR, TOP_COLOR, a);

	return color;
}