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

#ifndef __STACK_H
#define __STACK_H

typedef struct _stack_t stack_t;

/**********************************************************
 * \brief Init new stack 
 *
 * \returns newly created stack
 **********************************************************/
stack_t *stack_new(void);

/**********************************************************
 * \brief Get size of stack
 *
 * \param s     stack struct
 *
 * \returns size of stack
 **********************************************************/
int stack_size(stack_t *s);

/**********************************************************
 * \brief Push item to stack
 *
 * \param s     stack struct
 * \param p     data to push
 * \param l     size of data to push
 **********************************************************/
void stack_push(stack_t *s, void *p, int l);

/**********************************************************
 * \brief Delete and return top most element
 *
 * \param s     stack struct 
 *
 * \returns element
 **********************************************************/
void *stack_pop(stack_t *s);

/**********************************************************
 * \brief Return top most element without deleting
 *
 * \param s     stack struct
 *
 * \return element
 **********************************************************/
void *stack_peek(stack_t *s);

/**********************************************************
 * \brief Destroy stack and data
 *
 * \param s     stack struct
 **********************************************************/
void stack_destroy(stack_t *s);

#endif /* __STACK_H */
