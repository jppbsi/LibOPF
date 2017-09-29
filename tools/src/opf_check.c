#include "OPF.h"

#define HEADERSIZE 100
#define LINESIZE 1000000

int isInteger(char *str, int strsize)
{
    int i;

    for (i = 0; i < strsize; i++)
    {
        if (!isdigit(str[i]))
            return 0;
    }

    return 1;
}

int isFLoat(char *str, int strsize)
{
    int i, ctr1 = 0, ctr2 = 0, ctr3 = 0;

    for (i = 0; i < strsize; i++)
    {
        if (!isdigit(str[i]) && (str[i] != '.') && (str[i] != '+') && (str[i] != '-') && ((int)str[i] != 13))
            return 0;
        if (str[i] == '.')
            ctr1++;
        else if (str[i] == '+')
            ctr2++;
        else if (str[i] == '-')
            ctr3++;
    }

    if (ctr1 > 1 || ctr2 > 1 || ctr3 > 1)
        return 0;
    if (ctr1 + ctr2 > 1)
        return 0; /* it checks if we have both '-' and '+' in the same float number */
    return 1;
}

int CheckHeader(char *line, int *nsamples, int *nlabels, int *nfeats)
{
    char *token = NULL;
    int ctr = 0;

    token = strtok(line, " \n\t");
    while (token)
    {
        ctr++;
        if (!isInteger(token, strlen(token)))
            return 0;
        switch (ctr)
        {
        case 1:
            *nsamples = atoi(token);
            break;
        case 2:
            *nlabels = atoi(token);
            break;
        case 3:
            *nfeats = atoi(token);
            break;
        default:
            return 0;
        }
        token = strtok(NULL, " \n\t");
    }

    if (ctr != 3)
        return 0;
    if ((*nsamples <= 0) || (*nlabels <= 0) || (*nfeats <= 0))
        return 0;

    return 1;
}

int CheckLine(char *line, int nlabels, int nfeats, int lineid)
{
    char *token = NULL;
    int ctr = 0;

    /* it checks the position of each sample (first column) */
    token = strtok(line, " \n\t");
    if (!isInteger(token, strlen(token)))
        return 0;

    /* it checks the label of each sample (second column) */
    token = strtok(NULL, " \n\t");
    if (!isInteger(token, strlen(token)) || atoi(token) <= 0)
        return 0;

    /* it checks the features */
    token = strtok(NULL, " \n\t");
    while (token)
    {
        if (!isFLoat(token, strlen(token)))
            return 0;
        ctr++;
        token = strtok(NULL, " \n\t");
    }

    if (ctr != nfeats)
        return 0;

    return 1;
}

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "\nusage opf_check <input ASCII file in the LibOPF format>\nNote that the input file for opf_check must be a text file.\nUse opf2txt to convert your OPF binary file into a text file.\n");
        exit(-1);
    }
    FILE *fp = NULL;
    char header[HEADERSIZE], line[LINESIZE], OK = 1;
    int nsamples, nlabels, nfeats, i;
    char *result = NULL;

    fp = fopen(argv[1], "r");
    if (!fp)
    {
        fprintf(stderr, "\nunable to open file %s\n", argv[1]);
        exit(-1);
    }

    /* it checks the header */
    result = fgets(header, HEADERSIZE, fp);
    if (!CheckHeader(header, &nsamples, &nlabels, &nfeats))
    {
        fprintf(stderr, "\nAn error has been found at line 1 (HEADER).");
        fprintf(stderr, "\nThe header should contain only three integers:");
        fprintf(stderr, "\n<#samples> <#labels> <#features>\n");
        OK = 0;
    }

    /* it checks the remaining file */
    for (i = 1; i <= nsamples; i++)
    {
        result = fgets(line, LINESIZE, fp);
        if (!CheckLine(line, nlabels, nfeats, i))
        {
            fprintf(stderr, "\nAn error has been found at line %d\n", i + 1);
            OK = 0;
            break;
        }
    }
    fclose(fp);
    if (result)
        result++;

    if (OK)
        fprintf(stderr, "\nThis file is in the proper format. Enjoy.\n");

    return 1;
}