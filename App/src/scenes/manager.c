#include "manager.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static inline bool isIndexValid(int capacity, int index)
{
	return (index >= 0 && index < capacity);
}

void SceneManager_Init(SManager *pMan, int capacity)
{
	pMan->capacity = capacity;
	pMan->scenes = malloc(capacity * sizeof(SManager));

	pMan->currentIndex = 0;
}

void SceneManager_Free(SManager *pMan)
{
	for (int i = 0; i < pMan->capacity; ++i)
	{
		void *pData = pMan->scenes[i].pData;
		pMan->scenes[i].Free(pData);
	}

	memset(pMan->scenes, 0, pMan->capacity * sizeof(Scene));

	free(pMan->scenes);
	memset(pMan, 0, sizeof(SManager));
}

void SceneManager_Switch(SManager *pMan, int currentIndex)
{
	if (isIndexValid(pMan->capacity, currentIndex))
	{
		exit(1);
	}

	pMan->currentIndex = currentIndex;
}

/// Add a Scene to `scenes`.
void SceneManager_Add(SManager *pMan, Scene scene, int index)
{
	if (isIndexValid(pMan->capacity, index))
	{
		exit(2);
	}

	// NOTE: Struct copy, not reference!
	pMan->scenes[index] = scene;
}

void Scene_Init(SManager *pMan)
{
	int i = pMan->currentIndex;
	void *pData = pMan->scenes[i].pData;

	pMan->scenes[i].Init(pData);
}

void Scene_Free(SManager *pMan)
{
	int i = pMan->currentIndex;
	void *pData = pMan->scenes[i].pData;

	pMan->scenes[i].Free(pData);
}

void Scene_Update(SManager *pMan)
{
	int i = pMan->currentIndex;
	void *pData = pMan->scenes[i].pData;

	pMan->scenes[i].Update(pData);
}

void Scene_Draw(SManager *pMan)
{
	int i = pMan->currentIndex;
	void *pData = pMan->scenes[i].pData;

	pMan->scenes[i].Draw(pData);
}
