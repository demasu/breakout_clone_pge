// Tutorial program from https://github.com/OneLoneCoder/olcPixelGameEngine/wiki
// As such, variables are in hungarian notation, because even though I'm typing everything out myself
// I don't want to get confused if I start changing names of things. It's also why they style is not consistent

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
	olc::vf2d vBallVel = { 200.0f, -100.0f };
	float fBatSpeed = 250.0f;
	float fBallRadius = 5.0f;

	float fTargetFrameTime = 1.0f / 60.0f; // 60 FPS
	float fAccumulatedTime = 0.0f;

public:
	
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		srand(100);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Clamp physics to 60 fps
		fAccumulatedTime += fElapsedTime;
		if (fAccumulatedTime >= fTargetFrameTime) {
			fAccumulatedTime -= fTargetFrameTime;
			fElapsedTime = fTargetFrameTime;
		}
		else {
			return true;
		}

		// Handle user input
		if (GetKey(olc::Key::LEFT).bHeld) {
			fBatPos -= fBatSpeed * fElapsedTime;
		}
		if (GetKey(olc::Key::RIGHT).bHeld) {
			fBatPos += fBatSpeed * fElapsedTime;
		}

		if (fBatPos < 11.0f) {
			fBatPos = 11.0f; // Left boundary
		}
		if (fBatPos + fBatWidth > float(ScreenWidth()) - 10.0f) {
			fBatPos = float(ScreenWidth()) - 10.0f - fBatWidth;
		}

		// Update ball
		vBall += vBallVel * fElapsedTime;

		// Crude arena detection
		if (vBall.y <= 10.0f) {
			vBallVel.y *= -1.0f;
		}
		if (vBall.x <= 10.0f) {
			vBallVel.x *= -1.0f;
		}
		if (vBall.x >= float(ScreenWidth()) - 10.0f) {
			vBallVel.x *= -1.0f;
		}

		// Check for collision with bat
		if (vBall.y >= (float(ScreenHeight()) - 20.0f) && (vBall.x > fBatPos + fBatWidth)) {
			vBallVel.y *= -1.0f;
		}

		// Check if ball has gone off screen
		if (vBall.y > ScreenHeight()) {
			// Reset ball location
			vBall = { 200.0f, 200.0f };
			// Choose random direction
			float fAngle = (float(rand()) / float(RAND_MAX)) * 2.0f * 3.14159f;
			vBallVel = { 300.0f * cos(fAngle), 300.0f * sin(fAngle) };
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