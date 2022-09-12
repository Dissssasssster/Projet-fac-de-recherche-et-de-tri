/* Inclusion des bibliothèques */
#include "../includes/headers.h"
#include "../includes/tools.h"

/* Si un argument est transmis, ceci va être utilisé comme valeur de recherche */
int main(int args, char *argv[])
{
	/* Rech pour quel recherche il veut effectuer */
	unsigned int rech;

	/* Variables pour afficher ou non le tri séquentielle et Variables pour demander si l'utilisateur veut mélanger */
	bool re = false;
	unsigned int reshuffler = 0;

	/* Variables pour obtenir le temps */
	double getDataTime, sortTime;

	/* Variable pour mesurer le temps */
	clock_t timer;

	/* Chaine de caractères pour contenir la ligne */
	char tmpLine[2000];

	/* Allocation de la mémoire nécessaire au tableau de la structure */
	Data *dataArray = malloc(LINE_TO_READ_COUNT * sizeof(Data));

	/* Chaine de caractères qui va contenir le résultat de la fonction de recherche ou la valeur par défaut */
	Data *result;

	/* Variable pour stocker le résultat de la recherche par index */
	ArrayIndex results;

	/*
	création des variables de type FILE qui vont contenir le fichier, mode ouverture :
	(r = (lecture seul, doit exister))
	(a+ = ajout lecture/écriture, fin de fichier)
	*/
	FILE *registerFile = fopen("../resources/registerFile.csv", "r");
	FILE *getDataTranscriptFile = fopen("../resources/getDataTranscriptFile.csv", "a+");
	FILE *sortTranscriptFile = fopen("../resources/sortTranscriptFile.csv", "a+");

	/* Vérification que les fichiers ce sont ouvert correctement et que l'allocation de mémoire de dataArray c'est bien passé */
	if (!(registerFile && getDataTranscriptFile && sortTranscriptFile && dataArray))
	{
		fprintf(stderr, "Problème allocation dynamique");
		exit(EXIT_FAILURE);
	}

	/* récupération d'une ligne pour supprimer la ligne qui donne les colonnes */
	fgets(tmpLine, 2000, registerFile);

	timer = clock(); // Démarrage du Timer.

	/* Boucle pour récupérer le nombre lignes que l'on veut et appel de la fonction Get_data_in */
	for (size_t i = 0; i < LINE_TO_READ_COUNT; i++)
	{
		fgets(tmpLine, 2000, registerFile);
		Get_data_in(&dataArray[i], tmpLine);
	}

	/* Calcule pour avoir la durée en millisecondes, (double) est pour faire un cast en double */
	getDataTime = (double)((clock() - timer) * 1000) / CLOCKS_PER_SEC;

	/* Fonction permettant ecrire des temps */
	fprintf(getDataTranscriptFile, "%u,%lf\n", LINE_TO_READ_COUNT, getDataTime);

	do
	{
		/* Fonction qui demande le tri demandé */
		Call_tri(dataArray, timer);

		/* Calcule pour avoir la durée en millisecondes, (double) est pour faire un cast en double */
		sortTime = (double)((clock() - timer) * 1000) / CLOCKS_PER_SEC;

		/* Fonction permettant ecrire des temps. */
		fprintf(sortTranscriptFile, "%u,%lf\n", LINE_TO_READ_COUNT, sortTime);

		for (size_t i = 0; i < LINE_TO_READ_COUNT; i++)
		{
			printf("%d\n", dataArray[i].aged);
		}

		/*
		result prend la valeur de retour d'une fonction, (args > 1)? argv[1] : "valeur par défaut")
		est une condition ternaire ceci permet de dire si le nombre l'argument et au-dessus de 1,
		ceci recherchera l'argument placé, sinon on affectera une valeur par défaut.
		*/

		do
		{
			printf("Quel recherche vous voulez faire ? (séquentielle) --> 1 (Index) --> 2 (dichotomique) --> 3\n --> ");
			scanf("%d", &rech);

			/* appel des recherches */
			switch (rech)
			{
			case 1:
				result = Find_entity(dataArray, (args > 1) ? argv[1] : "valeur par defaut");
				;
				break;
			case 2:
				results = Find_entity_index(dataArray);
				Print_ArrayIndex(results);
				Free_ArrayIndex(results);
				;
				re = true;
				break;
			case 3:
				if (Find_entity_dicho(dataArray, (args > 1) ? argv[1] : "valeur par defaut"))
					printf("le caractere recherche a ete trouve.\n");
				else
					printf("le caractere recherche n a pas ete trouve.\n");
				re = true;
				;
				break;
			default:
				printf("Mauvaise saisie veuillez saisir une valeur, soit 1 ou 2 ou 3!\n");
				;
				break;
			}
		/* Boucle qui vérifie que l'utilisateur rentre bien un chiffre soit 1 ou 0 */
		} while (rech != 1 && rech != 2 && rech != 3);

		/*
		condition, si result n'a pas la valeur NULL afficher la recherche, car NULL est pointeur sur rien.
		-> est un raccourcie *(pointeur)
		*/
		if (result != NULL && re != true)
			printf("\nAged --> %d Surf --> %.2f Prof --> %s\n", result->aged, result->surf, result->prof);
		else if (result == NULL && re != true)
			printf("l information n a pas ete trouve !\n");

		re = false;

		do
		{
			printf("Voulez vous melanger pour refaire un tri (oui) --> 1 (Non) --> 0\n --> ");
			scanf("%u", &reshuffler);

			if (reshuffler > 1)
				printf("Mauvaise saisie veuillez saisir une valeur soit 1 ou 0 !\n");
		} while (reshuffler != 0 && reshuffler != 1);

		if (reshuffler)
			shuffler(dataArray); // Effectuer le tri.

	} while (reshuffler); // Boucle pour re effectuer le tri.

	/* libère la mémoire allouée dynamiquement */
	freeCloseFile(dataArray, registerFile, getDataTranscriptFile, sortTranscriptFile);

	return 0;
}