#include "manager.h"

#include <stdlib.h>
#include <string.h>

#include "raylib.h"

SManager g_SceneManager = {0};

void SceneManager_Init(void)
{
	g_SceneManager.count = 0;
	g_SceneManager.pCurrent = NULL;
}

void SceneManager_Free(void)
{
	for (int i = 0; i < g_SceneManager.count; ++i)
	{
		void *pData = g_SceneManager.scenes[i].pData;
		g_SceneManager.scenes[i].Free(pData);
	}
}

void SceneManager_Switch(const char *name)
{
	for (int i = 0; i < g_SceneManager.count; i++)
	{
		if (strcmp(name, g_SceneManager.scenes[i].name) == 0)
		{
			g_SceneManager.pCurrent = &g_SceneManager.scenes[i];
			return;
		}
	}

	TraceLog(LOG_ERROR, "Unknow scene \"%s\"", name);
	exit(4);
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

void SceneManager_Register(Scene (*SceneConstructor)(void))
{
	if (g_SceneManager.count + 1 > SCENES_MAX)
	{
		TraceLog(LOG_ERROR, "SceneManager overflow");
		exit(2);
	}

	g_SceneManager.scenes[g_SceneManager.count] = SceneConstructor();

	void *pData = g_SceneManager.scenes[g_SceneManager.count].pData;
	g_SceneManager.scenes[g_SceneManager.count].Init(pData);

	g_SceneManager.count++;
}

void Scene_Free(void)
{
	void *pData = g_SceneManager.pCurrent->pData;
	g_SceneManager.pCurrent->Free(pData);
}

void Scene_Update(void)
{
	void *pData = g_SceneManager.pCurrent->pData;
	g_SceneManager.pCurrent->Update(pData);
}

void Scene_Draw(void)
{
	void *pData = g_SceneManager.pCurrent->pData;
	g_SceneManager.pCurrent->Draw(pData);
}
