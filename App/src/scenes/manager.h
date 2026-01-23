#pragma once

#include <stddef.h>

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

void SceneManager_Init(SManager *pMan, int capacity);

void SceneManager_Free(SManager *pMan);

void SceneManager_Switch(SManager *pMan, int currentIndex);

/// Add a Scene to `scenes`.
void SceneManager_Add(SManager *pMan, Scene scene, int index);

void Scene_Init(SManager *pMan);

void Scene_Free(SManager *pMan);

void Scene_Update(SManager *pMan);

void Scene_Draw(SManager *pMan);
