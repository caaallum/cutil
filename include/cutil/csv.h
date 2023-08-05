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

#ifndef __CSV_H
#define __CSV_H

#include <cutil/vector.h>

#define ERROR_COUNT 3

enum {
    CSV_SUCCESS = 0,
    CSV_FILE_NOT_FOUND = 1,
    CSV_INVALID_DELIMITER = 2,
};

static char* csv_errors[ERROR_COUNT] = {
    "Success"
    "File not found",
    "Invalid delimiter",
};

#define csv_parser_get_error(err) csv_errors[err]

 typedef struct _csv_parser_t {
    vector_t* header;
    vector_t* rows;
} *csv_parser_t;

/**********************************************************
 * \brief Init new parser
 *
 * \param parser     pointer to parser struct
 * \param file 		 path to csv file
 * \param deleimeter csv delimiter to use
 * \param has_header indicator if the file has a header
 *
 * \returns error code
 **********************************************************/
int csv_parser_parse(csv_parser_t *parser, const char *file, char delimiter, int has_header);

/**********************************************************
 * \brief Destroy parser
 *
 * \param parser 	csv parser
 **********************************************************/
void csv_parser_destroy(csv_parser_t parser);


#endif /* __CSV_H */