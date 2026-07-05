#include "pch.h"
#include "Util.h"

constexpr float ASPECT_RATIO = 16.0f / 9.0f;
constexpr uint32_t IMAGE_WIDTH = 800;
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

static void Render(uint32_t* framebuffer, const uint32_t pitch);
static void WriteColor(uint32_t* pixel, const Color& color);
[[nodiscard]] static Color GetRayColor(const Ray& ray);

int main(int argc, char* argv[])
{
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);

	VERIFY(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL_Init failed [error:%s]", SDL_GetError());

	SDL_Window* window = SDL_CreateWindow("VoxelWithOpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, IMAGE_WIDTH, IMAGE_HEIGHT, SDL_WINDOW_OPENGL bitor SDL_WINDOW_SHOWN);
	MASSERT(window != nullptr, "SDL_CreateWindow failed [error:%s]", SDL_GetError());

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	MASSERT(renderer != nullptr, "SDL_CreateRenderer failed [error:%s]", SDL_GetError());

	SDL_Texture* frame = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, IMAGE_WIDTH, IMAGE_HEIGHT);
	MASSERT(frame != nullptr, "SDL_CreateTexture failed [error:%s]", SDL_GetError());

	void* framebuffer = nullptr;
	int pitch = 0;
	VERIFY(SDL_LockTexture(frame, nullptr, &framebuffer, &pitch) == 0, "SDL_LockTexture failed [error:%s]", SDL_GetError());

	Render(static_cast<uint32_t*>(framebuffer), pitch);

	SDL_UnlockTexture(frame);
	VERIFY(SDL_RenderCopy(renderer, frame, nullptr, nullptr) == 0, "SDL_RenderCopy failed [error:%s]", SDL_GetError());
	SDL_RenderPresent(renderer);

	while (true)
	{
		SDL_Event event{};
		VERIFY(SDL_WaitEvent(&event) > 0, "SDL_WaitEvent failed [error:%s]", SDL_GetError());

		switch (event.type)
		{
		case SDL_KEYDOWN:
		{
			uint32_t scancode = event.key.keysym.scancode;
			if (scancode == SDL_SCANCODE_ESCAPE)
			{
				goto QUIT_PROCESS;
			}

			break;
		}

		case SDL_QUIT:
			goto QUIT_PROCESS;
		}
	}

QUIT_PROCESS:
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void Render(uint32_t* framebuffer, const uint32_t pitch)
{
	ASSERT(framebuffer != nullptr);

	for (uint32_t i = 0; i < IMAGE_HEIGHT; ++i)
	{
		const uint32_t y = i * (pitch / 4);

		for (uint32_t j = 0; j < IMAGE_WIDTH; ++j)
		{
			uint32_t* pixel = &framebuffer[y + j];
			Vector3 pixelCenter = PIXEL00_LOCATION + (float(j) * PIXEL_DELTA_U) + (float(i) * PIXEL_DELTA_V);
			Vector3 rayDirection = Normalize(pixelCenter - CAMERA_CENTER);
			Ray ray{ .Origin = CAMERA_CENTER, .Direction = rayDirection };

			float r = GetLength(Vector3(pixelCenter.X, pixelCenter.Y, 0.0f) - Vector3(CAMERA_CENTER.X, CAMERA_CENTER.Y, 0.0f));
			if (r <= 0.5f)
			{
				Color color{ 0.5f, 0.5f, 0.0f };
				WriteColor(pixel, color);
			}
			else
			{
				Color color = GetRayColor(ray);
				WriteColor(pixel, color);
			}
		}
	}
}

void WriteColor(uint32_t* pixel, const Color& color)
{
	ASSERT(pixel != nullptr);

	uint32_t r = uint32_t(min(color.X * 255.0f, 255.0f));
	*pixel = r << 24;

	uint32_t g = uint32_t(min(color.Y * 255.0f, 255.0f));
	*pixel |= g << 16;

	uint32_t b = uint32_t(min(color.Z * 255.0f, 255.0f));
	*pixel |= b << 8;

	constexpr uint32_t ALPHA = 0xFF;
	*pixel |= ALPHA;
}

void WriteColor(std::string* buffer, const Color& color)
{
	ASSERT(buffer != nullptr);

	uint32_t r = uint32_t(color.X * 255.0f);
	uint32_t g = uint32_t(color.Y * 255.0f);
	uint32_t b = uint32_t(color.Z * 255.0f);

	*buffer += std::format("{} {} {}\n", r, g, b);
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