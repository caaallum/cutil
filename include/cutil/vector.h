/**********************************************************
 * This file is part of cutil.
 *
 * cutil is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License 
 * as published by the Free SoftwareFoundation, either version 3 
 * of the License, or (at your option) any later version.
 * 
 * cutil is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with cutil. If not, see <https://www.gnu.org/licenses/>.
 **********************************************************/

#ifndef __VECTOR_H
#define __VECTOR_H

/**********************************************************
 * Macros
 **********************************************************/
#define V_NARGS_IMPL_(x1, x2, x3, x4, x5, x6, x7, x8, x9, x11, x12, x13, \
        x14, x16, N, ...) N
#define V_EXPAND_(x) x
#define V_PP_NARGS_(...) \
    V_EXPAND_(V_NARGS_IMPL_(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, \
                5, 4, 3, 2, 1, 0))
#define V_FOREACH(v, t, n) \
    t *n = (t *)vector_get(v, 0); \
    for (unsigned int i = 0; i < vector_size(v); n = (t *)vector_get(v, ++i))

typedef struct vector_t vector_t;

/**********************************************************
 * \brief Init new vector
 *
 * \returns newly created vector
 **********************************************************/
vector_t *vector_new(void);

/**********************************************************
 * \brief Free vector memory
 *
 * \param vector    this
 **********************************************************/
void vector_destroy(vector_t *vector);

/**********************************************************
 * \brief Get size of vector
 *
 * \param vector   this
 *
 * \returns size
 **********************************************************/
int vector_size(vector_t *vector);

/**********************************************************
 * \brief Add item to vector
 *
 * \param vector   this
 * \param item     item to add to vector
 **********************************************************/
void vector_add(vector_t *vector, void *item);

/**********************************************************
 * \brief Add multiple items to vector
 *
 * \param vector   this
 * \param ...      items to add
 **********************************************************/
#define vector_addv(vector, ...) \
    vector_addv_(vector, V_PP_NARGS_(__VA_ARGS__), __VA_ARGS__)
void vector_addv_(vector_t *vector, int count, ...);

/**********************************************************
 * \brief Add item to vector and copy data
 *
 * \param vector   this
 * \param item     item to add to vector
 **********************************************************/
void vector_pushback(vector_t *vector, void *item, int size);

/**********************************************************
 * \brief Add multiple items to vector and copy data
 *
 * \param vector   this
 * \param ...      items to add
 **********************************************************/
#define vector_pushbackv(vector, ...) \
    vector_pushbackv_(vector, V_PP_NARGS_(__VA_ARGS__), __VA_ARGS__)
void vector_pushbackv_(vector_t *vector, int count, ...);

/**********************************************************
 * \brief Delete item from vector at givem index
 *
 * \param vector   this
 * \param index    item index to delete
 **********************************************************/
void vector_delete(vector_t *vector, int index);

/**********************************************************
 * \brief Get item from vector at given index
 *
 * \param vector   this
 * \param index    item to add to vector
 *
 * \returns item if found NULL if not
 **********************************************************/
void *vector_get(vector_t *vector, int index);

#endif /* __VECTOR_H */
