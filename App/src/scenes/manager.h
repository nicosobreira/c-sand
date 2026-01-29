#pragma once

#include <stdbool.h>

#include "scene.h"

#define SCENES_MAX 16

/** Array of Scenes
 * I recommend creating an enum of Scenes with the
 * final element holding the total capacity.
 */
typedef struct SceneManager
{
	/// Array of possible scenes.
	/// Has size of `capacity`.
	Scene scenes[SCENES_MAX];
	Scene *pCurrent;

	/// Total of possible scenes.
	int count;
} SManager;

/// Only the `SceneManager` functions should read/write this variable.
extern SManager g_SceneManager;

void SceneManager_Init(void);

void SceneManager_Free(void);

void SceneManager_Switch(const char *name);

void SceneManager_Loop(void);

/** Get `pData` from a scene
 * @return The `pData` void pointer (need to cast!)
 */
void *SceneManager_GetDataByIndex(int index);

/// Add a Scene to `scenes`.
/// Also call the `Init` function.
void SceneManager_Register(Scene (*SceneConstructor)(void));

void Scene_Free(void);

void Scene_Update(void);

void Scene_Draw(void);
