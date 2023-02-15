#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char alph[][7]={
    {'a','.','-'},
    {'b','-','.','.','.'},
    {'c','-','.','-','.'},
    {'d','-','.','.'},
    {'e','.'},
    {'f','.','.','-','.'},
    {'g','-','-','.'},
    {'h','.','.','.','.'},
    {'i','.','.'},
    {'j','.','-','-','-'},
    {'k','-','.','-'},
    {'l','.','-','.','.'},
    {'m','-','-'},
    {'n','-','.'},
    {'o','-','-','-'},
    {'p','.','-','-','.'},
    {'q','-','-','.','-'},
    {'r','.','-','.'},
    {'s','.','.','.'},
    {'t','-'},
    {'u','.','.','-'},
    {'v','.','.','.','-'},
    {'w','.','-','-'},
    {'x','-','.','.','-'},
    {'y','-','.','-','-'},
    {'z','-','-','.','.'},
    {'0','-','-','-','-','-'},
    {'1','.','-','-','-','-'},
    {'2','.','.','-','-','-'},
    {'3','.','.','.','-','-'},
    {'4','.','.','.','.','-'},
    {'5','.','.','.','.','.'},
    {'6','.','.','.','.','.'},
    {'7','-','-','.','.','.'},
    {'8','-','-','-','.','.'},
    {'9','-','-','-','-','.'}
};

void add(char *letter, int len, char str)
{
    int new=0;
    while (*(letter+new)!='\0')
    {
        new++;
    }
    *(letter+new)=str;
}

size_t length(int i)
{
    size_t j = 1;
    while (alph[i][j]!='\0')
    {
        j++;
    }
    return j-1;
}

char found(char *letter)
{
    char res;
    int cur=0;
    int ok=1;
    while(ok)
    {
        int taille=length(cur);
        if(strlen(letter)==taille)
        {
            int ok2=1;
            int now=0;
            while (ok2 && now<taille)
            {
                if(letter[now]!=alph[cur][now+1])
                {
                    ok2=0;
                }
                now++;
            }
            if(ok2 && now==taille)
            {
                ok=0;
                res=alph[cur][0];
            }
        }
        cur++;
    }
    return res;
}

void clear(char *letter)
{
    int i = 0;
    while(*(letter+i)!='\0')
    {
        *(letter+i)='\0';
        i++;
    }
}

int found2(char *letter, char chara)
{
    int len=0;
    int cur=0;
    int ok=1;
    while (ok)
    {
        if(alph[cur][0]==chara)
        {
            while(alph[cur][len+1]!='\0')
            {
                letter[len]=alph[cur][len+1];
                len++;
            }
            ok=0;
        }
        cur++;
    }
    return len;
}

int cmpr(char *test, char chara)
{
    if(*test==chara)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main (int argc, char *argv[])
{
    if(cmpr(argv[1], 'm'))
    {
        remove("resultat");
        FILE *text = fopen(argv[2],"r");
        FILE *res = fopen("resultat","a");
        char letter[] = {'\0','\0','\0','\0','\0'};
        char *caracter= malloc(sizeof(char));
        while(fread(caracter,sizeof(char),1,text))
        {
            if (*caracter==' ')
            {
                char next = found(letter);
                fwrite(&next,sizeof(char),1,res);
                clear(letter);
            }
            else if (*caracter=='\n')
            {
                char next = found(letter);
                fwrite(&next,sizeof(char),1,res);
                clear(letter);
                char space=' ';
                fwrite(&space,sizeof(char),1,res);
            }
            else
            {
                add(letter,5, *caracter);
            }
        }
        char next = found(letter);
        fwrite(&next,sizeof(char),1,res);
        fclose(text);
        fclose(res);
    }
    else if(cmpr(argv[1], 'f'))
    {
        remove("resultat2");
        FILE *text = fopen(argv[2],"r");
        FILE *res = fopen("resultat2","a");
        char letter[] = {'\0','\0','\0','\0','\0'};
        char *caracter= malloc(sizeof(char));
        while(fread(caracter,sizeof(char),1,text))
        {
            if (*caracter==' ')
            {
                char next = '\n';
                fwrite(&next,sizeof(char),1,res);
            }
            else if(*caracter=='\n')
            {
                continue;
            }
            else
            {
                int next = found2(letter ,*caracter);
                fwrite(letter,sizeof(char),next,res);
                clear(letter);
                char next2 = ' ';
                fwrite(&next2,sizeof(char),1,res);
            }
        }
    }
    return 1;
}