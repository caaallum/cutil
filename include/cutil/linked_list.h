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

#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

typedef struct node_t node_t;

struct node_t {
    void *val;
    node_t *next;
};

node_t *linkedlist_new(void *val);

void linkedlist_push(node_t *head, void *val);

#endif /* __LINKED_LIST_H */
