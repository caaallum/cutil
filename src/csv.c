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

#include <cutil/csv.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

static int 
csv_parser_is_deliter_accepted(const char *delimiter) {
    char d = *delimiter;
    switch (d) {
        case '\n':
        case '\r':
        case '\0':
        case '\"':
            return 0;
    }
    return 1;
}

vector_t*
csv_parser_get_row(FILE* file, char delimiter) {
    int accepted_chars = 64;
    int field_it = 0;
    char* current_field = NULL;
    int inside_complex = 0;
    int current_field_char_it = 0;
    int series_of_quote_len = 0;
    int last_char_is_quote = 0;
    int end_of_file = 0;

    vector_t* row = vector_new();

    current_field = malloc(accepted_chars);
    while (1) {
        char current_char = fgetc(file);

        if (feof(file)) {
            if (current_field_char_it == 0 && field_it == 0) {
                free(current_field);
                return NULL;
            }
            current_char = '\n';
            end_of_file = 1;
        }
        if (current_char == '\r') {
            continue;
        }
        if (current_field_char_it == 0 && !last_char_is_quote) {
            if (current_char == '\"') {
                inside_complex = 1;
                last_char_is_quote = 1;
                continue;
            }
        }
        else if (current_char == '\"') {
            series_of_quote_len++;
            inside_complex = (series_of_quote_len % 2 == 0);
            if (inside_complex) {
                current_field_char_it--;
            }
        }
        else {
            series_of_quote_len = 0;
        }

        if (end_of_file || ((current_char == delimiter || current_char == '\n') && !inside_complex)) {
            current_field[last_char_is_quote ? current_field_char_it - 1 : current_field_char_it] = '\0';
            vector_push_string(row, current_field);

            free(current_field);
            if (current_char == '\n') {
                return row;
            }

            accepted_chars = 64;
            current_field = malloc(accepted_chars);
            current_field_char_it = 0;
            field_it++;
            inside_complex = 0;
        }
        else {
            current_field[current_field_char_it] = current_char;
            current_field_char_it++;
            if (current_field_char_it == accepted_chars - 1) {
                accepted_chars *= 2;
                current_field = realloc(current_field, accepted_chars);
            }
        }
        last_char_is_quote = current_char == '\"';
    }
}

int
csv_parser_parse(csv_parser_t* parser, const char* file, char delimeter, int has_header) {
    if (!csv_parser_is_deliter_accepted) {
        return CSV_INVALID_DELIMITER;
    }

    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        return CSV_FILE_NOT_FOUND;
    }

    *parser = malloc(sizeof(struct _csv_parser_t));
    assert(parser);

    (*parser)->rows = vector_new();
    vector_t* row;

    if (has_header) {
        (*parser)->header = csv_parser_get_row(fp, delimeter);
    }

    while ((row = csv_parser_get_row(fp, delimeter))) {
        vector_add((*parser)->rows, row);
    }

    return CSV_SUCCESS;
}

void
csv_parser_destroy(csv_parser_t parser) {
    assert(parser);

    free(parser);
}
