#pragma once

typedef struct Scene
{
	void (*Init)(void *pData);
	void (*Free)(void *pData);

	/// Also handles **Input**.
	void (*Update)(void *pData);
	void (*Draw)(void *pData);

	/// Heap allocated data pointer.
	/// This `Scene` manages the lifetime.
	void *pData;
} Scene;
