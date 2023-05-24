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

#include <cutil/string.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

string_t *
string_new(const char *str) {
    string_t *s = malloc(sizeof(string_t));
    assert(s);

    s->length = strlen(str) + 1;

    s->str = malloc(s->length);
    assert(s->str);

    strcpy(s->str, str);

    return s;
}

void
string_append(string_t *s, const char *str) {
    s->length += strlen(str);
    char *new_str = realloc(s->str, s->length);
    assert(new_str);

    strcat(s->str, str);

    s->str = new_str;
}

void
string_prepend(string_t *s, const char *str) {
    s->length += strlen(str);
    char *new_str = malloc(s->length);
    strcpy(new_str, str);
    strcat(new_str, s->str);

    free(s->str);
    s->str = new_str;
}


void string_destroy(string_t *s) {
    free(s->str);
    free(s);
}
