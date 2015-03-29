/*
 *  Autor: Andrei Macavei
 *  Grupa: 334 CB
*/

#include <string.h>

#include "hash.h"
#include "list.h"
#include "utils.h"

#define ADD "add"
#define REMOVE "remove"
#define FIND "find"
#define CLEAR "clear"
#define PRINT_BUCKET "print_bucket"
#define PRINT "print"
#define RESIZE "resize"
#define DOUBLE "double"
#define HALVE "halve"

#define LINE_SIZE 20000
#define OP_SIZE 16
#define FILE_SIZE 512

/*
 *  Function that detects the output file and returns
 *  the corresponding file descriptor
 */
FILE *detect_output_file(char *filename, int flag)
{   FILE *f;

    if (flag != 0) {
        f = fopen(filename, "a");
        DIE(f == NULL, "detect_output_file - open file");
    } else {
        f = stdout;
    }
    return f;
}

/*
 *  Function that reads the input from a file and updates
 *  the hash table
 */
void read_input(HashTable *t, FILE *fin)
{
    int res, index, line_atoms, isfile;
    char line[LINE_SIZE], operation[OP_SIZE], word[LINE_SIZE], fname[FILE_SIZE];
    FILE *fout = NULL;

    while (fgets(line, LINE_SIZE-1, fin) != NULL) {
        /* skip blank lines */
        if (!strcmp(line, "\n") || !strcmp(line, "\r\n"))
            continue;

        /* flush input */
        fname[0] = '\0';
        word[0] = '\0';
        isfile = 0;

        /* get command  + word + output_file */
        line_atoms = sscanf(line, "%s %s %s", operation, word, fname);

        if (strcmp(operation, ADD) == 0) {
            table_add(t, word);
            /* debug print */
            dprintf("%s %s\n", operation, word);

        } else if (strcmp(operation, REMOVE) == 0) {
            table_remove(t, word);
            /* debug print */
            dprintf("%s %s\n", operation, word);

        } else if (strcmp(operation, FIND) == 0) {
            isfile = (line_atoms == 3) ? 1 : 0;
            fout = detect_output_file(fname, isfile);

            res = table_find(t, word);
            if (res != 0)
                fprintf(fout, "True\n");
            else
                fprintf(fout, "False\n");

            /* debug print */
            dprintf("%s %s %s\n", operation, word, fname);

        } else if (strcmp(operation, CLEAR) == 0) {
            table_clear(t);
            /* debug print */
            dprintf("%s %s\n", operation, word);

        } else if (strcmp(operation, PRINT_BUCKET) == 0) {
            isfile = (line_atoms == 3) ? 1 : 0;
            fout = detect_output_file(fname, isfile);
            index = atoi(word);

            table_print_bucket(t, index, fout);
            /* debug print */
            dprintf("%s %s %s\n", operation, word, fname);

        } else if (strcmp(operation, PRINT) == 0) {
            isfile = (line_atoms == 2) ? 1 : 0;
            fout = detect_output_file(word, isfile);
            table_print(t, fout);
            /* debug print */
            dprintf("%s %s\n", operation, word);

        } else if (strcmp(operation, RESIZE) == 0) {
            if (strcmp(word, DOUBLE) == 0)
                *t = table_resize(t, t->size * 2);
            else
                *t = table_resize(t, t->size / 2);

            /* debug print */
            dprintf("%s %s\n", operation, word);
        }

        if (fout != stdout && fout != NULL) {
            res = fclose(fout);
            DIE(res != 0, "read_input - close file");
            fout = NULL;
        }
    }
    DIE(ferror(fin) != 0, "read_input - read from file");

}

int main(int argc, char *argv[])
{
    FILE *f = NULL;
    HashTable t;
    int size, rc, i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s size [file1 file2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    size = atoi(argv[1]);
    DIE(size <= 0, "main - arg1");

    table_init(&t, size);


    if (argc - 2 == 0) {
        /* read from stdin */
        f = stdin;
        read_input(&t, f);
    } else {
        /* set i to first optional input_file argument */
        i = 2;

        while (i < argc) {

            f = fopen(argv[i], "r");
            /* Ignore invalid files*/
            if (f < 0) {
                fprintf(stderr, "file <%s> invalid\n", argv[i]);
                continue;
            }

            read_input(&t, f);

            rc = fclose(f);
            DIE(rc != 0, "main - close file");

            i++;
        }
    }

    table_free(&t);
    return 0;
}
