#pragma once

#include <stdbool.h>

#include "scene.h"

/** Array of Scenes
 * I recommend creating an enum of Scenes with the
 * final element holding the total capacity.
 */
typedef struct SceneManager
{
	/// Array of possible scenes.
	/// Has size of `capacity`.
	Scene *scenes;

	/// Total of possible scenes.
	int capacity;

	int currentIndex;
} SManager;

/// Only the functions above should change this variable.
extern SManager g_SceneManager;

void SceneManager_Init(int capacity);

void SceneManager_Free(void);

void SceneManager_Switch(int newIndex);

void SceneManager_Loop(void);

/// Add a Scene to `scenes`.
void SceneManager_Add(Scene (*SceneFunc)(void), int index);

void SceneIndex_Init(int index);

void SceneIndex_Free(int index);

void SceneIndex_Update(int index);

void SceneIndex_Draw(int index);

void Scene_Init(void);

void Scene_Free(void);

void Scene_Update(void);

void Scene_Draw(void);
