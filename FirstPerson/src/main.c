#include "raylib.h"
#include "rcamera.h"

const Color classic_red = {255, 0, 0, 255};
const Color classic_blue = {0, 0, 255, 255};
const Color classic_green = {0, 255, 0, 255};
const Color classic_magenta = {255, 0, 255, 255};
const Color classic_cyan = {0, 255, 255, 255};
const Color classic_yellow = {255, 255, 0, 255};

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	InitWindow(screenWidth, screenHeight, "First Person");

	Model monk = LoadModel("resources/suzanne.obj");

	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = {0};
	camera.position = (Vector3){0.0f, 2.0f, 4.0f}; // Camera position
	camera.target = (Vector3){0.0f, 2.0f, 0.0f};   // Camera looking at point
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};	   // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;						   // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;		   // Camera projection type

	int cameraMode = CAMERA_FIRST_PERSON;
	bool showPlayer = false;
	bool showCursor = false;
	DisableCursor();

	//--------------------------------------------------------------------------------------
	Texture2D texture = LoadTexture("resources/floor.png");
	Texture2D monster = LoadTexture("resources/boo.png");
	Texture2D spooky = LoadTexture("resources/spooky.png");

	// monk.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = monster;
	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// Switch camera mode

		if (IsKeyPressed(KEY_TWO))
		{
			showPlayer = false;
			cameraMode = CAMERA_FIRST_PERSON;
			camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // Reset roll
		}

		if (IsKeyPressed(KEY_P))
		{
			cameraMode = CAMERA_THIRD_PERSON;
			showPlayer = true;
		}

		if (IsKeyPressed(KEY_LEFT_ALT) && showCursor)
		{
			DisableCursor();
			showCursor = false;
		}
		if (IsKeyPressed(KEY_SPACE) && !showCursor)
		{
			EnableCursor();
			showCursor = true;
		}

		UpdateCamera(&camera, cameraMode);

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, classic_red);
		DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, classic_blue);
		DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, classic_green);
		DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, classic_magenta);
		DrawCube((Vector3){0.0f, 2.5f, -16.0f}, 32.0f, 5.0f, 1.0f, classic_cyan);
		DrawPlane((Vector3){0.0f, 5.0f, 0.0f}, (Vector2){32.0f, -32.0f}, classic_yellow);
		// DrawBillboard(camera, spooky, (Vector3){2.5f, 2.5f, 0}, 1.0f, WHITE);
		// DrawBillboard(camera, texture, (Vector3){0, 2.5f, 2.5f}, 1.0f, WHITE);

		// DrawBillboard(camera, monster, (Vector3){2.5f, 2.5f, 2.5f}, 3.0f, WHITE);
		DrawModel(monk, (Vector3){0.0f, 2.5f, 0.0f}, 2.0f, LIGHTGRAY);
		if (showPlayer == true)
		{
			DrawCube(camera.target, 2, 2, 2, BLUE);
		}
		DrawGrid(50, 1);

		EndMode3D();
		DrawFPS(10, 10);

		EndDrawing();
	}
	UnloadModel(monk);
	UnloadTexture(monster);
	UnloadTexture(spooky);
	UnloadTexture(texture);

	CloseWindow();
	return 0;
}