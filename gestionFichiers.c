#include "gestionFichiers.h"

void sauvegarderResultat(const char *nomFichier, joueur joueur1, joueur joueur2, clock_t tempsDebut)
{
    FILE *fichier = fopen(nomFichier, "a"); 

    if (fichier != NULL)
    {
        clock_t tempsFin = clock();
        double tempsEcoule = ((double)(tempsFin - tempsDebut)) / CLOCKS_PER_SEC;

        fprintf(fichier, "Resultat du jeu :\n");
        fprintf(fichier, "%s : %d\n", joueur1.nom, joueur1.score);
        fprintf(fichier, "%s : %d\n", joueur2.nom, joueur2.score);
        fprintf(fichier, "Temps ecoule : %.2f secondes\n", tempsEcoule);
        fprintf(fichier, "-----------------\n");
        fclose(fichier);
    }
    else
        fprintf(stderr, "Erreur type2 \n");
}
