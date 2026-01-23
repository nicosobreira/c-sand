#include "manager.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

static inline bool isIndexValid(int capacity, int index)
{
	return (index >= 0 && index < capacity);
}

SManager g_SceneManager = {0};

void SceneManager_Init(int capacity)
{
	if (capacity <= 0)
		exit(1);

	g_SceneManager.capacity = capacity;
	g_SceneManager.scenes = malloc(g_SceneManager.capacity * sizeof(Scene));

	g_SceneManager.currentIndex = 0;
}

void SceneManager_Free(void)
{
	for (int i = 0; i < g_SceneManager.capacity; ++i)
	{
		void *pData = g_SceneManager.scenes[i].pData;
		g_SceneManager.scenes[i].Free(pData);
	}

	memset(g_SceneManager.scenes, 0, g_SceneManager.capacity * sizeof(Scene));
	free(g_SceneManager.scenes);

	memset(&g_SceneManager, 0, sizeof(SManager));
}

void SceneManager_Switch(int newIndex)
{
	if (!isIndexValid(g_SceneManager.capacity, newIndex))
	{
		exit(1);
	}

	g_SceneManager.currentIndex = newIndex;

	TraceLog(LOG_DEBUG, "Current Index: %d", g_SceneManager.currentIndex);
}

void SceneManager_Add(Scene (*SceneFunc)(void), int index)
{
	if (!isIndexValid(g_SceneManager.capacity, index))
	{
		exit(2);
	}

	// NOTE: Struct copy, not reference!
	g_SceneManager.scenes[index] = SceneFunc();
}

void SceneManager_Loop(void)
{
	while (!WindowShouldClose())
	{
		Scene_Update();

		BeginDrawing();
		Scene_Draw();
		EndDrawing();
	}
}

void SceneIndex_Init(int index)
{
	void *pData = g_SceneManager.scenes[index].pData;

	g_SceneManager.scenes[index].Init(pData);
}

void SceneIndex_Free(int index)
{
	void *pData = g_SceneManager.scenes[index].pData;

	g_SceneManager.scenes[index].Free(pData);
}

void SceneIndex_Update(int index)
{
	void *pData = g_SceneManager.scenes[index].pData;

	g_SceneManager.scenes[index].Update(pData);
}

void SceneIndex_Draw(int index)
{
	void *pData = g_SceneManager.scenes[index].pData;

	g_SceneManager.scenes[index].Draw(pData);
}

void Scene_Init(void)
{
	SceneIndex_Init(g_SceneManager.currentIndex);
}

void Scene_Free(void)
{
	SceneIndex_Free(g_SceneManager.currentIndex);
}

void Scene_Update(void)
{
	SceneIndex_Update(g_SceneManager.currentIndex);
}

void Scene_Draw(void)
{
	SceneIndex_Draw(g_SceneManager.currentIndex);
}
