#include "raylib.h"
#include "rcamera.h"

#define MAX_COLUMNS 20

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "First Person");

	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = {0};
	camera.position = (Vector3){0.0f, 2.0f, 4.0f}; // Camera position
	camera.target = (Vector3){0.0f, 2.0f, 0.0f};   // Camera looking at point
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};	   // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;						   // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;		   // Camera projection type

	int cameraMode = CAMERA_FIRST_PERSON;

	DisableCursor(); // Limit cursor to relative movement inside the window

	SetTargetFPS(60); // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// Switch camera mode

		if (IsKeyPressed(KEY_TWO))
		{
			cameraMode = CAMERA_FIRST_PERSON;
			camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // Reset roll
		}

		UpdateCamera(&camera, cameraMode);

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, LIGHTGRAY);
		DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, LIGHTGRAY);
		DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, LIGHTGRAY);
		DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, LIGHTGRAY);

		EndMode3D();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}