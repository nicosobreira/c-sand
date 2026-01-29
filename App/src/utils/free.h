#pragma once

/** Free heap allocated memory and sets to NULL
 *
 */
void Pointer_Free(void **pp);

/**
 * @brief Frees a heap-allocated pointer and sets it to NULL.
 *
 * @param[in,out] ptr Address of a heap pointer to free.
 *
 * @warning
 * - `ptr` must not be NULL.
 */
#define FREE(ptr)                                                                                                      \
	do                                                                                                                 \
	{                                                                                                                  \
		Pointer_Free((void **)&ptr);                                                                                   \
	} while (0)
