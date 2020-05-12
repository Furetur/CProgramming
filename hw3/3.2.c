#include <stdio.h>
#include <stdbool.h>

struct LineReadingStatus
{
    bool lineEmpty;
    bool endOfFile;
};

struct LineReadingStatus checkNextLine(FILE* file)
{
    bool curLineEmpty = true;
    int curChar = fgetc(file);
    while (curChar != '\n' && curChar != EOF)
    {
        if (curChar != '\t' && curChar != ' ')
        {
            curLineEmpty = false;
        }
        curChar = fgetc(file);
    }

    return (struct LineReadingStatus){ curLineEmpty, curChar == EOF };
}

int main()
{
    FILE *file = fopen("file.txt", "r");

    if (file == NULL)
    {
        printf("Error reading file");
        return 1;
    }

    int lineCounter = 0;
    int emptyLineCounter = 0;
    bool endOfFile = false;

    while(!endOfFile)
    {
        lineCounter++;
        struct LineReadingStatus status = checkNextLine(file);
        endOfFile = status.endOfFile;
        if (status.lineEmpty)
        {
            emptyLineCounter++;
        }
    }

    printf("Your file contains %d non-empty lines", lineCounter - emptyLineCounter);

    fclose(file);
    return 0;
}
