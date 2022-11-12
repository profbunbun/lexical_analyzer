#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// void printspace(int numtabs)
// {
//     for (int i = 0; i < numtabs; i++)
//         printf(" ");
// }

// typedef struct node
// {
//     char *typ;
//     char *pos;
//     char *val;
//     struct node *left;
//     struct node *right;
//     struct node *center;
// } node;

// node *createnode(char *t, char *p, char *v)
// {
//     struct node *result;
//     result = malloc(sizeof(*result) + 480);
//     result->typ = t;
//     result->pos = p;
//     result->val = v;
//     if (result != NULL)
//     {
//         printf("                                             tester");
//         // result->typ = t;
//         result->pos = p;
//         result->val = v;
//         result->left = NULL;
//         result->center = NULL;
//         result->right = NULL;
//     }
//     return result;
// }

// void printnode_rec(node *root, int level)
// {
//     if (root == NULL)
//     {
//         printspace(level);
//         printf("\n------EMPTY___________\n");
//         return;
//     }
//     printspace(level);
//     if (strcmp(root->typ, "NUM") == 0)
//     {
//         printf("(    %s)", root->val);
//     }
//     printnode_rec(root->left, level + 1);
//     printnode_rec(root->right, level + 1);
// }

// void printnode(node *root)
// {
//     printnode_rec(root, 0);
// }

char check_next(FILE *const fp)
{
    char innext;
    innext = getc(fp);
    fseek(fp, -1L, SEEK_CUR);
    return innext;
}

int getSize(char *s)
{
    char *t;
    for (t = s; *t != '\0'; t++)
        ;
    return t - s;
}

int isKeyword(char buffy[])
{
    int i;
    int f = 0;
    const char keywords[33][9] = {{"program"}, {"end"}, {"bool"}, {"int"}, {"if"}, {"then"}, {"else"}, {"fi"}, {"while"}, {"do"}, {"od"}, {"print"}, {"or"}, {"and"}, {"not"}, {"fasle"}, {"true"}};

    for (i = 0; i < 33; ++i)
    {
        if (strcmp(keywords[i], buffy) == 0)
        {
            f = 1;
        }
    }
    return f;
}

int isID(char buffy[])
{
    // printf("%d  \n ",getSize(buffy));
    int i;
    int f = 0;
    if (isalpha(buffy[0]))
    {

        for (i = 0; i < getSize(buffy); ++i)
        {
            if (isalnum(buffy[i]) || isdigit(buffy[i]))
            {
                f = 1;
            }
        }
    }
    return f;
}

int isNUM(char buffy[])
{
    int i;
    int f = 0;
    if (isdigit(buffy[0]))
    {

        for (i = 0; i < getSize(buffy); ++i)
        {
            if (isdigit(buffy[i]))
            {
                f = 1;
            }
        }
    }
    return f;
}

void iscommie(FILE *const fp, FILE *const outF, int cin, int *linenum, int pos)
{

    int f = 0;
    if (cin == '/' && check_next(fp) == '/')
    {
        while (cin != '\n')
        {

            cin = fgetc(fp);
        }
        (*linenum)++;
    }
    else if (cin == '/' && (check_next(fp) == '/') == 0)
    {

        f = 1;
        // printf("%d:%d: \'/\'\n", *linenum, pos);
        fprintf(outF, "%d:%d: \'/\'\n", *linenum, pos);
    }

    return;
}

void colspec(FILE *const fp, FILE *const outF, int cin, int linenum, int pos)
{

    if (cin == ':' && check_next(fp) == '=')
    {
        //  printf("%d:%d: \':=\'\n", linenum, pos);
        fprintf(outF, "%d:%d: \':=\'\n", linenum, pos);
        getc(fp);
    }
    else if (cin == ':' && check_next(fp) != '=')
    {
        //  printf("%d:%d: \':\'\n", linenum, pos);
        fprintf(outF, "%d:%d: \':\'\n", linenum, pos);
    }
    else
        return;
}

void ineq(FILE *const fp, FILE *const outF, int cin, int linenum, int pos)
{

    if (cin == '!' && check_next(fp) == '=')
    {
        // printf("%d:%d: \'!=\'\n", linenum, pos);
        fprintf(outF, "%d:%d: \'!=\'\n", linenum, pos);
        getc(fp);
    }
    else if (cin == '!' && (check_next(fp) == '=') == 1)
    {
        // printf("%d:%d:>>>>> Illegal cahracter \'!\'\n", linenum, pos);
        fprintf(outF, "%d:%d:>>>>> Illegal cahracter \'!\'\n", linenum, pos);
        exit(1);
    }
    else

        return;
}

void colpow(FILE *const fp, FILE *const outF, int cin, int inlin, int inpos)
{
    int i;
    char cc = cin;
    char inl = inlin;
    char inp = inpos;

    if (cc == ';')

    {
        // printf("%d:%d: \'%c\'\n", inl, inp, cc);
        fprintf(outF, "%d:%d: \'%c\'\n", inl, inp, cc);
    }
}

void rels(FILE *const fp, FILE *const outF, int cin, int inlin, int inpos)
{
    int i;
    char cc = cin;
    char inl = inlin;
    char inp = inpos;

    if (cin == '<' && check_next(fp) == '=')
    {
        // printf("%d:%d: \'<=\'\n", inl, inpos);
        fprintf(outF, "%d:%d: \'<=\'\n", inl, inpos);
        getc(fp);
    }
    else if (cin == '>' && check_next(fp) == '=')
    {
        // printf("%d:%d: \'<=\'\n", inl, inpos);
        fprintf(outF, "%d:%d: \'<=\'\n", inl, inpos);
        getc(fp);
    }
    else if (cc == '>')
    {
        // printf("%d:%d: \'%c\'\n", inl, inp, cc);
        fprintf(outF, "%d:%d: \'%c\'\n", inl, inp, cc);
    }
    else if (cc == '<')
    {
        // printf("%d:%d: \'%c\'\n", inl, inp, cc);
        fprintf(outF, "%d:%d: \'%c\'\n", inl, inp, cc);
    }
    else if (cc == '=')
    {
        // printf("%d:%d: \'%c\'\n", inl, inp, cc);
        fprintf(outF, "%d:%d: \'%c\'\n", inl, inp, cc);
    }
}

void ads(int cin, FILE *const outF, int inlin, int inpos)

{
    int i;
    char cc = cin;
    char inl = inlin;
    char inp = inpos;

    if (cc == '+')
    {
        //  printf("%d:%d: \'%c\'\n", inl, inp, cc);
        fprintf(outF, "%d:%d: \'%c\'\n", inl, inp, cc);
    }
    else if (cc == '-')
    {
        //  printf("%d:%d: \'%c\'\n", inl, inp, cc);
        fprintf(outF, "%d:%d: \'%c\'\n", inl, inp, cc);
    }
}

void facs(int cin, FILE *const outF, int inlin, int inpos)

{
    int i;
    char cc = cin;
    char inl = inlin;
    char inp = inpos;
    if (cc == '(')
    {
        // printf("%d:%d: \'%c\'\n", inl, inp, cc);
        fprintf(outF, "%d:%d: \'%c\'\n", inl, inp, cc);
    }
    else if (cc == ')')
    {
        //  printf("%d:%d: \'%c\'\n", inl, inp, cc);
        fprintf(outF, "%d:%d: \'%c\'\n", inl, inp, cc);
    }
}

void mults(FILE *const fp, FILE *const outF, int cin, int inlin, int inpos)
{
    int i;
    char cc = cin;
    char inl = inlin;
    char inp = inpos;

    if (cc == '*')
    {
        // printf("%d:%d: \'%c\'\n", inl, inp, cc);
        fprintf(outF, "%d:%d: \'%c\'\n", inl, inp, cc);
    }
}

void illeagle(int cin, FILE *const outF, int inlin, int inpos)
{
    int i;
    char cc = cin;
    char inl = inlin;
    char inp = inpos;
    const char fac[20] = {"\"#$%%&\',.?@[\\]^`{|}~"};
    for (i = 0; i < 20; ++i)
    {
        if (cc == fac[i])
        {
            printf("%d:%d:>>>>> Illegal cahracter \'%c\'\n", inlin, inpos, cin);
            fprintf(outF, "%d:%d:>>>>> Illegal cahracter \'%c\'\n", inlin, inpos, cin);
            exit(0);
        }
    }
}

void lex_on_em2(char *fileName)
{

    const char ws[4] = {0x09, 0x0A, 0x0D, 0x20};
    int i, j = 0, line = 1, position = 1, *lineptr, *posptr, p = 0;
    int c;

    char *buffy;
    buffy = (char *)malloc(sizeof(char));

    char *in = fileName;
    // char *in = "euclid.txt";
    //   char *in = "test2.txt";

    FILE *fp;
    FILE *lexfile;
    lexfile = fopen("out.txt", "w+");
    fp = fopen(in, "r+");
    if (fp == NULL)
    {
        printf("error while opening the file\n");
        exit(0);
    }

    while ((c = fgetc(fp)) != EOF)
    {

        if (isdigit(c) && (j == 0))
        {

            buffy[j++] = c;

            while (isdigit(check_next(fp)))
            {
                c = getc(fp);

                buffy[j++] = c;
                position++;
            }
            buffy[j] = '\0';

            j = 0;

            // printf("%d:%d: \'NUM\' %s \n", line, position - getSize(buffy) + 1, buffy);
            fprintf(lexfile, "%d:%d: \'NUM\' %s \n", line, position - getSize(buffy) + 1, buffy);
            free(buffy);
        }

        if (isalpha(c))
        {
            buffy[j++] = c;

            while (isalpha(check_next(fp)) || check_next(fp) == '_' || isdigit(check_next(fp)))
            {

                c = getc(fp);
                buffy[j++] = c;
                position++;
            }
        }

        else if ((c == ' ' || c == '\n' || isalnum(c) == 0) && (j != 0))
        {
            buffy[j] = '\0';

            j = 0;

            if (isKeyword(buffy) == 1)
            {
                //  printf("%d:%d: \'%s\' \n", line, position - getSize(buffy), buffy);
                fprintf(lexfile, "%d:%d: \'%s\' \n", line, position - getSize(buffy), buffy);
                free(buffy);
            }
            else if (isID(buffy) == 1)
            {
                // printf("%d:%d: \'ID\' %s \n", line, position - getSize(buffy), buffy);
                fprintf(lexfile, "%d:%d: \'ID\' %s \n", line, position - getSize(buffy), buffy);
                free(buffy);
            }
        }

        iscommie(fp, lexfile, c, &line, position);
        colspec(fp, lexfile, c, line, position);
        colpow(fp, lexfile, c, line, position);
        ineq(fp, lexfile, c, line, position);
        ads(c, lexfile, line, position);
        mults(fp, lexfile, c, line, position);
        rels(fp, lexfile, c, line, position);
        facs(c, lexfile, line, position);
        illeagle(c, lexfile, line, position);

        if (c != ws[1] && c != ws[2])
        {
            position++;
        }
        if (c == ws[1] || c == ws[2])
        {
            line++;
            position = 1;
        }
    }

    free(buffy);
    // printf("end-of-file");
    fprintf(lexfile, "end-of-text");
    fclose(fp);
    fclose(lexfile);
    return;
}

char *next(FILE *in, char *lexline)
{

    int i;
    i = 0;

    char c = getc(in);

    while (c != '\n')
    {

        lexline[i++] = c;
        c = getc(in);
    }

    lexline[i++] = '\0';
    i = 0;
    return lexline;
}

char *kind(char *lexline, char *kinda)
{
    int i;
    i = 0;
    int j;
    j = 0;

    while (lexline[j] != '\'')
    {

        j++;
    }
    j++;

    while (lexline[j] != '\'')
    {

        kinda[i] = lexline[j];
        i++;
        j++;
    }
    kinda[i++] = '\0';
    i = 0;
    j = 0;

    return kinda;
}

char *value(char *lexline, char *val)
{
    int i, j;
    i = 0;
    j = 0;

    while (lexline[j] != '\'')
    {
        j++;
    }
    j++;
    while (lexline[j] != '\'')
    {

        j++;
    }
    j++;

    while (lexline[j] != '\0')
    {

        val[i] = lexline[j];

        i++;

        j++;
    }
    val[i++] = '\0';

    return val;
}

char *position(char *lexline, char *posi)
{
    int i;
    i = 0;

    while (lexline[i] != ' ')
    {
        posi[i] = lexline[i];
        i++;
    }
    posi[i++] = '\0';
    i = 0;
    return posi;
}

int match(FILE *in, char *term_t, char *lexline, char *kinda, char *posi)
{

    if (strncmp("end", term_t, sizeof(term_t)) == 0)
    { 
        return 0;
    }
    else if(strncmp(kind(lexline, kinda), term_t, sizeof(term_t)) == 0)
    {
printf(" BoutaMatch  %s ", lexline);
        next(in, lexline);
         printf("Match  %s ", lexline);
        return 0;
     }

    printf("Syntax error %s ", position(lexline, posi));
    printf("line  %s ", lexline);
    exit(0);

    return 1;
}

int factor(FILE *in, char *lexline, char *kinda, char *posi, char *val);
void body(FILE *in, char *lexline, char *kinda, char *posi, char *val);

int Identifier(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf(" in  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    if ((strcmp(kind(lexline, kinda), "ID") == 0))
    {
        next(in, lexline);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}
int IntLit(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{

    printf(" in  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    if ((strcmp(kind(lexline, kinda), "NUM") == 0))
    {
       // node *intlit = createnode(kinda, posi, val);
        //  node *intlit = {kinda,posi,val};

        //printnode(intlit);

        next(in, lexline);
        printf("out yup %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    printf("out  nope %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    return 1;
}
int BoolLit(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf(" in  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    if ((strcmp(kind(lexline, kinda), "false") == 0))
    {
        next(in, lexline);
        return 0;
    }
    if ((strcmp(kind(lexline, kinda), "true") == 0))
    {
        next(in, lexline);
        return 0;
    }
    printf(" out  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    return 1;
}

int Literal(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf(" in  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    if (IntLit(in, lexline, kinda, posi, val) == 0)
    {
        return 0;
    }
    if (BoolLit(in, lexline, kinda, posi, val) == 0)
    {
        return 0;
    }
    printf(" out  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    return 1;
}
int UnaryOperator(FILE *in, char *lexline, char *kinda)
{
    printf("in %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    if ((strcmp(kind(lexline, kinda), "-") == 0))
    {
        next(in, lexline);
        printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), "not") == 0))
    {
        next(in, lexline);
        printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    else
        printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    return 1;
}
int MultiplicativeOperator(FILE *in, char *lexline, char *kinda)
{

    if ((strcmp(kind(lexline, kinda), "*") == 0))
    {
        next(in, lexline);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), "/") == 0))
    {
        next(in, lexline);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), "and") == 0))
    {
        next(in, lexline);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    else
        return 1;
}
int additiveOperator(FILE *in, char *lexline, char *kinda)
{
    if ((strcmp(kind(lexline, kinda), "+") == 0))
    {
        next(in, lexline);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), "-") == 0))
    {
        next(in, lexline);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), "or") == 0))
    {
        next(in, lexline);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    else
        return 1;
}
int relationalOperator(FILE *in, char *lexline, char *kinda)
{
    if ((strcmp(kind(lexline, kinda), "<") == 0))
    {
        next(in, lexline);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), ">") == 0))
    {
        next(in, lexline);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), "=") == 0))
    {
        next(in, lexline);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), ">=") == 0))
    {
        next(in, lexline);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), "<=") == 0))
    {
        next(in, lexline);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), "!=") == 0))
    {
        next(in, lexline);
        return 0;
    }

    return 1;
}
void Declaration(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf(" in  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    if ((strcmp(kind(lexline, kinda), "int") == 0) || (strcmp(kind(lexline, kinda), "bool") == 0))
    {
        next(in, lexline);
        Identifier(in, lexline, kinda, posi, val);
        match(in, ";", lexline, kinda, posi);
        printf("out success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    printf("out option skipped %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    return;
}
int Declarations(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf(" in  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    Declaration(in, lexline, kinda, posi, val);
    printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    while ((strcmp(kind(lexline, kinda), "int") == 0) || (strcmp(kind(lexline, kinda), "bool") == 0))
    {

        Declaration(in, lexline, kinda, posi, val);
        printf("repitition success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    printf(" out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}
void term(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf("in %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    factor(in, lexline, kinda, posi, val);
    while (MultiplicativeOperator(in, lexline, kinda) == 0)
    {
        factor(in, lexline, kinda, posi, val);
        printf("repitition success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
}
void simpleExpression(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf("in %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    term(in, lexline, kinda, posi, val);
    while (additiveOperator(in, lexline, kinda) == 0)
    {
        term(in, lexline, kinda, posi, val);
        printf("repitition success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    printf(" out  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
}
void Expression(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf("in %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    simpleExpression(in, lexline, kinda, posi, val);
    if (relationalOperator(in, lexline, kinda) == 0)
    {
        simpleExpression(in, lexline, kinda, posi, val);
        printf("option success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    printf(" out  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
}
int factor(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf("in %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);

    if (UnaryOperator(in, lexline, kinda) == 0)
    {
    }

    if (Literal(in, lexline, kinda, posi, val) == 0)
    {
        printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    else if (Identifier(in, lexline, kinda, posi, val) == 0)
    {
        printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    else if ((strcmp(kind(lexline, kinda), "(") == 0))
    {
        printf("in parenthisis %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        next(in, lexline);
        Expression(in, lexline, kinda, posi, val);
        match(in, ")", lexline, kinda, posi);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    else

        return 0;
}
void PrintStatement(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf(" in  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);

    if ((strcmp(kind(lexline, kinda), "print") == 0))
    {
        next(in, lexline);

        Expression(in, lexline, kinda, posi, val);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    printf(" out  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
}
void IterativeStatement(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf(" in  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    if ((strcmp(kind(lexline, kinda), "while") == 0))
    {
        next(in, lexline);
        Expression(in, lexline, kinda, posi, val);
        match(in, "do", lexline, kinda, posi);
        body(in, lexline, kinda, posi, val);
        match(in, "od", lexline, kinda, posi);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    printf(" out  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
}
void ConditionalStatement(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf(" in  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    if ((strcmp(kind(lexline, kinda), "if") == 0))
    {
        next(in, lexline);
        Expression(in, lexline, kinda, posi, val);
        match(in, "then", lexline, kinda, posi);
        body(in, lexline, kinda, posi, val);
        if ((strcmp(kind(lexline, kinda), "else") == 0))
        {
            next(in, lexline);
            body(in, lexline, kinda, posi, val);
            printf("option success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        }
        match(in, "fi", lexline, kinda, posi);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    printf(" out  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
}
void AssignmentStatement(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf(" in  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    if ((strcmp(kind(lexline, kinda), "ID") == 0))
    {
        next(in, lexline);
        match(in, ":=", lexline, kinda, posi);
        Expression(in, lexline, kinda, posi, val);
        printf("success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }

    printf(" out  %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
}
void Statement(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf("in %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    AssignmentStatement(in, lexline, kinda, posi, val);
    ConditionalStatement(in, lexline, kinda, posi, val);
    IterativeStatement(in, lexline, kinda, posi, val);
    PrintStatement(in, lexline, kinda, posi, val);
    printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
}
void Statements(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf("in %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    Statement(in, lexline, kinda, posi, val);
    while ((strcmp(kind(lexline, kinda), ";") == 0))
    {
        next(in, lexline);
        Statement(in, lexline, kinda, posi, val);
    }
    printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
}

void body(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf("in %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    if (Declarations(in, lexline, kinda, posi, val) == 0)
    {
        printf(" in option %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
        Statements(in, lexline, kinda, posi, val);
        printf(" option success %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    else
    {
        printf(" skip option %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    }
    Statements(in, lexline, kinda, posi, val);

    printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
}

void program(FILE *in, char *lexline, char *kinda, char *posi, char *val)
{
    printf("in %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    next(in, lexline);
    match(in, "program", lexline, kinda, posi);
    Identifier(in, lexline, kinda, posi, val);
    match(in, ":", lexline, kinda, posi);
    body(in, lexline, kinda, posi, val);
     printf("%s",kinda);
    match(in, "end", lexline, kinda, posi);

    printf("out %s %s (%d)\n", __FILE__, __FUNCTION__, __LINE__);
    return ;
}

int main()
{

    char *lexLine, *kindo, *posi, *val;
    free(lexLine);
    free(kindo);
    free(posi);
    free(val);
    lexLine = malloc(sizeof(char) + 1);
    kindo = malloc(sizeof(char) + 1);
    posi = malloc(sizeof(char) + 1);
    val = malloc(sizeof(char) + 1);
    FILE *lextable;

   // lex_on_em2("euclid.txt");

    lextable = fopen("out.txt", "r+");

    if (lextable == NULL)
    {
        printf("error while opening the file\n");
        exit(0);
    }



   // program(lextable, lexLine, kindo, posi, val);

    //  next(lextable, lexLine);
    // while (kind(lexLine, kindo) != "end-of-text")
    // {
    //      printf("%s %s %s\n", position(lexLine, posi), kind(lexLine, kindo), value(lexLine, val));
    //     next(lextable, lexLine);
    // }


    printf("Success!!! 100");

    free(lexLine);
    free(kindo);
    free(posi);
    free(val);
    // free(intlit);
    fclose(lextable);
  
    return 0;
}