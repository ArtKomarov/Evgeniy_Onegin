/*
 * Main.c
 *
 *  Created on: Sep 21, 2019
 *      Author: Artem
 */
#include "OneginConsts.h"
#include "OneginFunc.h"

void PrintStrSep(FILE* stream); // Prints separator string and two ends of line to file stream

int main() {
    char s[inplen];
    printf("Enter file name:\n");
    scanf("%s", s);
    FILE* wf2 = fopen("Output.txt", "w");
    assert(wf2 != NULL);
    char *str = CreateBuffer(s);
    assert(str != NULL);
    ll length;
    line* lines = ParseBuffer(str, &length);
    assert(lines != NULL);

    quicksort(lines, 0, length - 1, CMP_DIRECT);
    for(int i = 0; lines[i].str != NULL; i++){
        if(IsLine(lines[i]) == 0) continue;
        fwrite(lines[i].str, sizeof(char), lines[i].length, wf2);
    }
    PrintStrSep(wf2);

    quicksort(lines, 0, length - 1, CMP_END);
    for(int i = 0; lines[i].str != NULL; i++){
        if(IsLine(lines[i]) == 0) continue;
        fwrite(lines[i].str, sizeof(char), lines[i].length, wf2);
    }
    PrintStrSep(wf2);

    PrintRaveToFile(lines, length, wf2);
    PrintStrSep(wf2);

    fprintf(wf2, "%s", str);

    fclose(wf2);
    free(lines);
    free(str);
    return 0;
}

// Prints separator string and two ends of line to file stream
void PrintStrSep(FILE* stream) {
    assert(stream != NULL);
    fprintf(stream, "-----------------------------\n");
    fprintf(stream, "\n");
}

