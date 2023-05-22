
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

struct wavfile //définit la structure de l entete d un wave
{
    char id[4]; // doit contenir "RIFF"
    int totallength; // taille totale du fichier moins 8 octets
    char wavefmt[8]; // doit etre "WAVEfmt "
    int format; // 16 pour le format PCM
    short pcm; // 1 for PCM format
    short channels; // nombre de channels
    int frequency; // frequence d echantillonage
    int bytes_per_second; // nombre de octets par secondes
    short bytes_by_capture; // nombre de bytes par echantillon
    short bits_per_sample; // nombre de bit par echantillon
    char data[4]; // doit contenir "data"
    int bytes_in_data; // nombre de bytes de la partie data
};

void analyse(char *fichieraudio)
{
    int i=0;
    int taille=1; //variable qui correspondra par la suite a la longueur du tableau(puissance de 2)
    int puissance=0;
    int nbech=0; //nombre d echantillons extraits du fichier audio

    FILE *wav = fopen(fichieraudio,"rb"); //ouverture du fichier wave
    struct wavfile header; //creation du header
    if ( wav == NULL )
    {
        printf("\nne peut pas ouvrir le fichier demande, verifier le nom\n");
        printf("ne pas oublier l'extention .wav\n");
        exit(1);
    }

    //initialise le header par l'entete du fichier wave
    //verifie que le fichier possÈde un entete compatible
    if ( fread(&header,sizeof(header),1,wav) < 1 )
    {
        printf("\nne peut pas lire le header\n");
        exit(1);
    }
    if ( header.id[0] != 'R' || header.id[1] != 'I' || header.id[2] != 'F'
    || header.id[3] != 'F' )
    {
        printf("\nerreur le fichier n'est pas un format wave valide\n");
        exit(1);
    }
    if (header.channels!=1)
    {
        printf("\nerreur : le fichier n'est pas mono\n");
        exit(1);
    }

    printf("%d\n",header.bytes_in_data);
    nbech=(header.bytes_in_data/header.bytes_by_capture);
    printf ("\nle fichier audio contient %d echantillons\n",nbech);
    while (nbech>taille)
    {
        taille=taille*2;
        puissance=puissance+1;
    }
    printf("%d\n",taille);
    
    double **tab=NULL; //tableau de l'onde temporelle
    tab=malloc( (taille) * sizeof(double));
    if (tab == NULL)
    {
        exit(0);
    }
    /*for(i=0;i<(taille);i++)
    {
        tab[i]=malloc( 2 * sizeof(double));
        if (tab[i] == NULL)
        {
            printf("sadge%d\n",i);
            exit(0);
        }
    }*/

    i=0;
    int lenght=0;
    printf("%d\n",i);
    short value=0;
    int next=0;
    int act=1;
    int cur=0;
    FILE *dat=fopen("data.dat","w"); //fichier data des echantillons
    FILE *test=fopen("test","w");
    while( fread(&value,(header.bits_per_sample)/8,1,wav) )
    { //lecture des echantillons et enregistrement dans le tableau
        tab[lenght]=malloc( 2 * sizeof(double));
        if (tab[lenght] == NULL)
        {
            printf("sadge%d\n",i);
            exit(0);
        }
        if(act==1 && value==0)
        {
            printf("%d\n",lenght);
            act=0;
            if (next==0)
            {
                if (cur>5000)
                {
                    fprintf(test,"-");
                }
                else if(cur>200)
                {
                    fprintf(test,".");
                }
            }
            next=0;
            cur=0;
        }
        else if (act==0 && value!=0)
        {
            act=1;
            if (cur>5000)
            {
                fprintf(test," ");
            }
            if (cur<200)
            {
                next=1;
                printf("ok\n");
            }
            cur=0;
        }
        else
        {
            cur+=1;
        }
        
        tab[lenght][0]=value;
        i++;
        lenght++;
    }

    printf("\nnombre d'echantillons lus : %d\n",lenght);
    printf("frequance : %d\n",header.frequency);
    printf("nombre de valeurs sauvegardees %d\n",lenght);
    for (int j=0;j<lenght;j++)
    {
        fprintf(dat,"%lf\n", tab[j][0]);
    }
    for(int j=0;j<lenght;j++)
    {
        free(tab[j]);
        tab[j] = NULL ;
    }
    fclose(wav);
    fclose(dat);
    fclose(test);
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Veuillez indiquer le fichier audio en argument.\n");
        return 1;
    }
    char *fichieraudio = argv[1];
    printf ("nom du fichier : %s\n", fichieraudio);
    analyse(fichieraudio);
    
    return 0;
}
