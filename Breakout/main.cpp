// O------------------------------------------------------------------------------O
// | Example "Hello World" Program (main.cpp)                                     |
// O------------------------------------------------------------------------------O

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class BreakOut : public olc::PixelGameEngine
{

public:

	BreakOut()
	{
		// Name your application
		sAppName = "BreakOut";
	}

private:
	float fBatPos = 20.0f;
	float fBatWidth = 40.0f;

	olc::vf2d vBall = { 200.0f, 200.0f };
	float fBatSpeed = 0.1f;
	float fBallRadius = 5.0f;

public:
	
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Handle user input
		if (GetKey(olc::Key::LEFT).bHeld) {
			fBatPos -= fBatSpeed;
		}
		if (GetKey(olc::Key::RIGHT).bHeld) {
			fBatPos += fBatSpeed;
		}

		if (fBatPos < 11.0f) {
			fBatPos = 11.0f; // Left boundary
		}
		if (fBatPos + fBatWidth > float(ScreenWidth()) - 10.0f) {
			fBatPos = float(ScreenWidth()) - 10.0f - fBatWidth;
		}

		// Cheating! Moving the ball with the mouse
		if (GetMouse(0).bHeld) {
			vBall = { float(GetMouseX()), float(GetMouseY()) };
		}
		if (GetMouseWheel() > 0) {
			fBallRadius += 1.0f;
		}
		if (GetMouseWheel() < 0) {
			fBallRadius -= 1.0f;
		}
		if (fBallRadius < 5.0f) {
			fBallRadius = 5.0f;
		}

		// Erase previous frame
		Clear(olc::DARK_BLUE);

		// Draw boundary
		DrawLine(10, 10, 502, 10, olc::YELLOW);
		DrawLine(10, 10, 10, 470, olc::YELLOW);
		DrawLine(502, 10, 502, 470, olc::YELLOW);

		// Draw bat
		FillRect(int(fBatPos), ScreenHeight() - 20, int(fBatWidth), 10, olc::GREEN);

		// Draw ball
		FillCircle(vBall, 5, olc::CYAN);
		return true;
	}
};

int main()
{
	BreakOut demo;
	if (demo.Construct(512, 480, 2, 2))
		demo.Start();
	return 0;
}