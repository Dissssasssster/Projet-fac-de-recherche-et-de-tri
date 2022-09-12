// Inclusion des bibliothèques.
#include "../includes/headers.h"
#include "../includes/tools.h"

// Création de la fonction qui va permettre de récupérer les données et les placer dans la structure.
void Get_data_in(Data *data, char *line)
{
	// i représente la colonne.
	unsigned int i = 1;

	// Separators est un point repère pour faire les découpes.
	char separators[] = ";";

	// TempValue va récupérer temporairement la donnée à placer dans la structure.
	char *tmpValue;

	// Affectation la chaine tempValue la fonction qui découpe la chaine et extraie le token.
	tmpValue = strtok(line, separators);

	/*
	Découpes de la chaine avec strtok (à partir de l'exemple de la documentation).
	Utilisation d'un switch sur i pour savoir si quelle colonne doit être récupérée,
	les informations et dans quelle valeur la structure la placé.
	*/
	while (tmpValue != NULL)
	{
		switch (i)
		{
		case 6:
			data->aged = atoi(tmpValue);
			;
			break;

		case 76:
			strcpy(data->prof, tmpValue);
			;
			break;

		case 85:
			data->surf = atof(tmpValue);
			;
			break;
		}

		tmpValue = strtok(NULL, separators);
		i++;
	}
}

// Fonction de tri à bulle.
void Sort_data_Bubble(Data *dataArray)
{
	Data temp; /* Variable qui va prendre une valeur temporaire */
	bool aucun_echange; /* Varible pour vérifier si le tri est déjà fini */
	for (int i = LINE_TO_READ_COUNT - 1; i >= 0; i--)
	{
		aucun_echange = true;
		for (int j = 0; j < i; j++)
			if (dataArray[j].aged >= dataArray[j + 1].aged) /* inverse les données comparées */
			{
				temp = dataArray[j + 1];
				dataArray[j + 1] = dataArray[j];
				dataArray[j] = temp;
				aucun_echange = false;
			}
		if (aucun_echange == true)
			break; /* Quitte la fonction*/ 
	}
}

// Fonction de tri à insersion.
void Sort_data_insertion(Data *dataArray)
{
	// Boucle pour recommencer la répétition de la boucle while.
	for (size_t i = 1; i < LINE_TO_READ_COUNT; i++)
	{
		// Variable qui conserve la structure en fonction de i pour pouvoir faire la permutation.
		Data val = dataArray[i];

		// Variable qui va permettre de parcourir le tableau en fonction de i.
		unsigned int j = i;
		// boucle pour comparer les données de aged, on utilise atoi() pour convertir en entier.
		while ((j > 0) && (dataArray[j - 1].aged > val.aged))
		{
			dataArray[j] = dataArray[j - 1];
			j = j - 1;
		}
		dataArray[j] = val;
	}
}

// Fonction tri rapide.
void Quick_sort(Data *dataArray, unsigned int size)
{
	// wall marque la séparation entre les éléments plus petits et ceux plus grands que pivot et current l'élément actuel.
	unsigned int wall, current;
	// tmp conserve la structure pour pouvoir faire la permutation.
	Data tmp;
	// Condition si la taille est plus petite que 2 on quitte la fonction.
	if (size < 2)
		return;
	// On prend comme pivot l'élément le plus à droite.
	Data pivot = dataArray[size - 1]; // Pivot est pour comparer aux autres.
	wall = current = 0;

	// Boucle tanque current et inférieur à size.
	while (current < size)
	{
		// Condition pour comparer tableau de la structure au pivot on convertit en entier avec atoi();
		if (dataArray[current].aged <= pivot.aged)
		{
			// Si wall est différent de current on intervertit les éléments.
			if (wall != current)
			{
				tmp = dataArray[current];
				dataArray[current] = dataArray[wall];
				dataArray[wall] = tmp;
			}
			wall++;
		}
		current++;
	}
	// Appel de la fonction tri rapide.
	Quick_sort(dataArray, wall - 1);
	// Appel de la fonction tri rapide.
	Quick_sort(dataArray + wall - 1, size - wall + 1);
}

// Fonction tri par selction.
void Sort_selection(Data *dataArray, unsigned int size)
{
	// Variable in_progress qui va être l'élément actuel et smaller le plus petit et j pour la boucle.
	unsigned int smaller;
	// Variable qui conserve la structure pour pouvoir faire la permutation.
	Data temp;
	// Boucle for partant de in_progress jusqu'à la size-1
	for (unsigned int in_progress = 0; in_progress <= size - 1; in_progress++)
	{
		smaller = in_progress;

		// Boucle pour répéter une comparaison et pour interchanger les éléments.
		for (unsigned int j = in_progress; j < size; j++)
			// Condition pour comparer les éléments du tableau de la structure et on utilise atoi() pour convertir en entier.
			if (dataArray[j].aged < dataArray[smaller].aged)
				smaller = j;
		// On place le plus petit à la position en_cours.
		temp = dataArray[in_progress];
		dataArray[in_progress] = dataArray[smaller];
		dataArray[smaller] = temp;
	}
}

// Fonction pour melanger.
void shuffler(Data *dataArray)
{
	Arrayshuffler shuf = {
		.line = LINE_TO_READ_COUNT, // nombre de ligne.
		.index = rand() % shuf.line // valeur aléatoire
	};

	// On commence par initialiser le générateur de nombres pseudo-aléatoires.
	srand(time(NULL));

	// Variable qui conserve la structure pour pouvoir faire la permutation.
	Data tmp;

	// Boucle for où i est = à 0 allant jusqu'au nombre de line voulu, pas de 1.
	for (unsigned int i = 0; i < LINE_TO_READ_COUNT; i++)
	{
		// Echange aléatoirement le tableau de la structure.
		tmp = dataArray[shuf.index];
		dataArray[shuf.index] = dataArray[shuf.line - 1];
		dataArray[LINE_TO_READ_COUNT - i - 1] = tmp;
		shuf.line--;
	}

	printf("Melange -->\n");
	for (size_t i = 0; i < LINE_TO_READ_COUNT; i++)
		printf("%d\n", dataArray[i].aged);
}

// Fonction de recherche.
Data *Find_entity(Data *dataArray, const char *toFind)
{
	// boucle qui permet de comparer deux chaines de caractères.
	for (size_t i = 0; i < LINE_TO_READ_COUNT; i++)
		if (atoi(toFind) == dataArray[i].aged)
			// Renvoie l'adresse du tableau de notre structure.
			return &dataArray[i];
	// Renvoie NULL si la recherche a échoué.
	return NULL;
}

// Fonction d'appel de tri.
void Call_tri(Data *dataArray, clock_t timer)
{
	unsigned int tri;

	printf("Veuillez choisir une methode pour le tri.\n");
	printf("Tri à bulle --> 1\t Tri selectif--> 2\t tri à insersion --> 3\t tri rapide --> 4\n --> ");
	scanf("%d", &tri);

	if (tri == 1)
	{
		timer = clock();
		Sort_data_Bubble(dataArray);
	}
	else if (tri == 2)
	{
		timer = clock();
		Sort_selection(dataArray, LINE_TO_READ_COUNT);
	}
	else if (tri == 3)
	{
		timer = clock();
		Sort_data_insertion(dataArray);
	}
	else if (tri == 4)
	{
		timer = clock();
		Quick_sort(dataArray, LINE_TO_READ_COUNT);
	}
	else
	{
		printf("Mauvaise saisi veuillez saisir une valeur entre 1 et 4\n");
		Call_tri(dataArray, timer);
	}
}

// Fonction recherche par index.
ArrayIndex Find_entity_index(Data *dataArray)
{
	ArrayIndex index = {
		/*Allocation de la mémoire nécessaire.*/
		.value = malloc((dataArray[LINE_TO_READ_COUNT - 1].aged + 1) * sizeof(unsigned int)),
		.index = malloc((dataArray[LINE_TO_READ_COUNT - 1].aged + 1) * sizeof(unsigned int)),
		.size = 1 // sera modifié plus tard.
	};
	// si l'allocation a échoué.
	if (!(index.value && index.index))
	{
		fprintf(stderr, "Problème allocation dynamique");
		exit(EXIT_FAILURE);
	}

	// initialise les premier chiffre.
	index.index[0] = 0;
	index.value[0] = dataArray[0].aged;
	int previousAge = dataArray[0].aged;

	// Fait la recherche.
	for (unsigned int line = 1; line < LINE_TO_READ_COUNT; line++)
	{
		if (dataArray[line].aged != previousAge)
		{
			index.index[index.size] = line;
			index.value[index.size] = dataArray[line].aged;
			index.size++;
			previousAge = dataArray[line].aged;
		}
	}

	// Optimisation de l'utilisation mémoire.
	index.index = realloc(index.index, index.size * sizeof(unsigned int));
	index.value = realloc(index.value, index.size * sizeof(unsigned int));

	return index;
}

// Fonction d'affichage de la recherche par index.
void Print_ArrayIndex(ArrayIndex data)
{
	for (unsigned int i = 0; i < data.size; ++i)
		printf("%u\t: %u\n", data.value[i], data.index[i]);

	return;
}

// fonction pour libérer la mémoire.
void Free_ArrayIndex(ArrayIndex data)
{
	/* Libère la mémoire */
	free(data.index);
	free(data.value);
	return;
}

// Fonction de recherche par dichotomie.
bool Find_entity_dicho(Data *dataArray, const char *toFind)
{
	ArrayDicho index = {
		.find = false,				 // vaut faux tant que la valeur "val" n'aura pas été trouvée
		.id = 0,					 // indice de début
		.idEnd = LINE_TO_READ_COUNT, // indice de fin
		.idMid = 0					 // indice de "milieu"
	};

	/* boucle de recherche */
	while (!index.find && ((index.idEnd - index.id) > 1))
	{

		index.idMid = (index.id + index.idEnd) / 2; // on détermine l'indice de milieu

		index.find = (dataArray[index.idMid].aged == atoi(toFind)); // on regarde si la valeur recherchée est à cet indice

		if (dataArray[index.idMid].aged > atoi(toFind))
			index.idEnd = index.idMid; // si la valeur qui est à la case "idMid" est supérieure à la valeur recherchée, l'indice de fin "ifin" << devient >> l'indice de milieu, ainsi l'intervalle de recherche est restreint lors du prochain tour de boucle
		else
			index.id = index.idMid; // sinon l'indice de début << devient >> l'indice de milieu et l'intervalle est de la même façon restreint
	}

	/* test conditionnant la valeur que la fonction va renvoyer */
	if (dataArray[index.id].aged == atoi(toFind))
		return (true); // si on a trouvé la bonne valeur, on retourne true
	else
		return (false); // sinon on retourne false
}

void freeCloseFile(Data *dataArray, FILE *registerFile, FILE *getDataTranscriptFile, FILE *sortTranscriptFile)
{
	/* Libère la mémoire */
	free(dataArray);

	// Fermeture des fichiers.
	fclose(registerFile);
	fclose(getDataTranscriptFile);
	fclose(sortTranscriptFile);
	return;
}

// Fonction de test.

/*
bool Find_entity_dicho(Data *dataArray, const char *toFind)
{
	unsigned int First = 0;					// Indice du premier élément du sous-tableau analysé.
	unsigned int Last = LINE_TO_READ_COUNT; // Indice du dernier élément du sous-tableau analysé.
	unsigned int Mid;						// Indice de l'élément du milieu du sous-tableau analysé.
	bool Find = false;						// Booléen indiquant si l'élément est trouvé.

	// Tant qu'on a pas trouve l'élément recherché ou que le sous-tableau.
	// contient plus de 1 élément.
	while ((First <= Last) && (Find == 0))
	{
		// Calcul de la position de l'élément du milieu.
		Mid = (First + Last) / 2;
		// Si l'élément du milieu est l'élément recherché.
		if (toFind == dataArray[Mid].prof)
			Find = true;
		else
		{
			// Si la valeur recherchée est plus petite.
			// que la valeur du l'élément du milieu.
			// Alors on regarde le sous-tableau de gauche.
			if (toFind == dataArray[Mid].prof)
				Last = Mid - 1;
			// sinon on regarde le sous-tableau de droit.
			else
				First = Mid + 1;
		}
		return Find;
	} // Fin du while
	return false;
}

float Interpole(Data *dataArray, unsigned int i, unsigned int j, const char *toFind)
{
	float a, b, r, result;

	if (i == j)
		result = i;
	else
	{
		a = ((dataArray[j].aged - dataArray[i].aged) / (j - i));
		b = dataArray[i].aged - a * i;
		if (a == 0)
			result = (i + j) / 2;
		else
		{
			r = (atof(toFind) - b) / a;
			if (r >= i && r <= j)
				result = r;
			else
				result = (i + j) / 2;
		}
	}
	return result;
}

bool Find_entity_dicho(Data *dataArray, const char *toFind)
{
	unsigned int i = 0, j = LINE_TO_READ_COUNT - 1, k;
	bool result = false;

	while (result == false && i <= j)
	{
		k = Interpole(dataArray, i, j, toFind);
		if (dataArray[k].aged == atoi(toFind))
			result = true;
		else
		{
			if (dataArray[k].aged > atoi(toFind))
				j = k--;
			else
				i = k++;
		}
	}
	return result;
}

// Fonction de tri à bulle.
void Sort_data_Bubble(Data *dataArray)
{
	// Variable qui va permettre de parcourir le tableau en fonction de i.
	unsigned int tmp;

	// Variable qui va stopper le programme si tout est déjà triée.
	unsigned int stop;

	// Variable qui conserve la structure pour pouvoir faire la permutation.
	Data tmpVal;

	stop = 0;

	for (int i = 0; i < LINE_TO_READ_COUNT; i++)
	{
		tmp = i;

		// boucle pour comparer les données de aged.
		for (int i2 = i; i2 < LINE_TO_READ_COUNT; i2++)
			if (dataArray[tmp].aged > dataArray[i2].aged)
				tmp = i2;

		// Inverse les données comparées.
		tmpVal = dataArray[tmp];
		dataArray[tmp] = dataArray[i];
		dataArray[i] = tmpVal;

		// Boucle pour vérifier si le tri est déjà fini.
		for (int i2 = (LINE_TO_READ_COUNT - 1); i2 > i + 1; i2--)
		{
			if (dataArray[i2].aged >= dataArray[i2 - 1].aged)
			{
				stop = 1;
				// Break pour sortir de la fonction.
				break;
			}
		}
		// Condition si elle est différente de stop on sort de la fonction.
		if (!stop)
			break;
		else
			stop = 0;
	}
}

*/
