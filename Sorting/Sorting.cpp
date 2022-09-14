#define OLC_PGE_APPLICATION


#include "olcPixelGameEngine.h"
#include <wtypes.h>

int LENGTH = 0;

bool arrEqual(int* a, int* b) {
	for (int i = 0; i < LENGTH; i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}


class Sorting : public olc::PixelGameEngine
{
private:
	int* data;
	int* last_iter;
	int w;
	int index = 0;
	int stop = LENGTH;
	int swaps = 0;
	int comparisons = 0;
	bool sorting = true;
	bool finished = false;
	float t = 0;
public:
	Sorting()
	{
		sAppName = "Sorting";
	}
	~Sorting() {
		delete data;
		delete last_iter;
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		data = new int[LENGTH];
		last_iter = new int[LENGTH];
		memset(data, 0, sizeof(int));
		memset(last_iter, 0, sizeof(int));
		for (int i = 0; i < LENGTH; i++) {
			data[i] = (rand() % LENGTH) + 1;
		}
		w = ScreenWidth() / LENGTH;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::BACK).bPressed) olc_Terminate();
		if (t > 0) {
			if (finished) return true;
			if (!sorting) {
				if (t > 0) {
					if (index >= LENGTH - 1) finished = true;
					int h = data[index] * (ScreenHeight() / LENGTH) - 20;
					FillRect(index * w, ScreenHeight() - h, w, 300, olc::GREEN);
					index++;
					t = 0;
				}
				else t += fElapsedTime;
				return true;
			}
			Clear(olc::BLACK);
			if (index < LENGTH - 1) index++;
			else {
				index = 0;
				for (int i = 0; i < LENGTH; i++)
					last_iter[i] = data[i];
			};
			int temp = data[index];
			if (index + 1 != LENGTH && data[index] > data[index + 1]) {
				comparisons++;
				swaps++;
				data[index] = data[index + 1];
				data[index + 1] = temp;
			}
			else comparisons++;

			for (int i = 0; i < LENGTH; i++) {
				olc::Pixel c = i % 2 == 0 ? olc::VERY_DARK_BLUE : olc::DARK_BLUE;
				index == i ? c = olc::GREEN : c = c;
				olc::Pixel lc = i % 2 == 0 ? olc::DARK_YELLOW : olc::YELLOW;
				int h = data[i] * (ScreenHeight() / LENGTH) - 20;
				FillRect(i * w, ScreenHeight() - h, w, 300, c);
				//DrawString(i * w + w / (data[i] >= 10 ? 8 : 4), (ScreenHeight() - h) - 10, std::to_string(h), lc);
			}
			DrawString(0, 0, "Comparisons: " + std::to_string(comparisons) + "; Swaps: " + std::to_string(swaps));
			if (arrEqual(data, last_iter) && index == LENGTH - 1) {
				std::cout << "Sorted!\n";
				index = 0;
				sorting = false;
			}
				t = 0;
		}
		else t += fElapsedTime;
		return true;
	}
};


int main()
{
	while (true) {
		std::cout << "Choose the length of the data: ";
		std::cin >> LENGTH;
		Sorting* demo = new Sorting();
		if (demo->Construct(500, 300, 2, 2))

			demo->Start();
		delete demo;
	}

	return 0;
}