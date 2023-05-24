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

#ifndef __STRING_H
#define __STRING_H

typedef struct {
    char *str;
    int length;
} string_t;

/**********************************************************
 * \brief Init new string
 *
 * \param str string to init from
 *
 * \returns newly created string
 **********************************************************/
string_t *string_new(const char *str);

/**********************************************************
 * \brief Append string to string struct
 *
 * \param s     string_t struct 
 * \param str   string to append
 **********************************************************/
void string_append(string_t *s, const char *str);

/**********************************************************
 * \brief Prepend string to string struct
 *
 * \param s     string_t struct
 * \param str   string to prepend
 **********************************************************/
void string_prepend(string_t *s, const char *str);

/**********************************************************
 * \brief Destroy string struct
 *
 * \param s     string_t to destroy
 **********************************************************/
void string_destroy(string_t *s);

#endif /* __STRING_H */
