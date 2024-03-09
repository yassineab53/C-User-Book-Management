
enum Identifiant
{
    CIN,
    CNE,
    APOGEE
};
enum Type_Utilisateur
{
    ETUDIANT,
    ADMINISTRATEUR
};
union Nom_Utilisateur
{
    char CIN[8];
    char CNE[10];
    int APOGEE;
};
struct User
{
    enum Identifiant id;
    union Nom_Utilisateur login;
    char password[20];
    enum Type_Utilisateur type;
    char nom[20];
    char prenom[20];
    char date_N[10];
    struct User *suivant;
};
typedef struct User User;
struct Livre
{
    char ISBN[13];
    char titre[50];
    char auteur[50];
    struct Livre *suivant;
};
typedef struct Livre Livre;
User *ajouterUtilisateur(User **, User *);
void saisir_utilisateur(User **);
void deconnexion();
Livre *ajouterLivre(Livre **, Livre *);
void afficherLivre(Livre *);
void afficherUtilisateur(User *);
void saisir_livre(Livre **);
User *authentification(User *, char *, char *);
// User *authentificationApogee(User *, int , char *)
void crypt(char *, int);
void masskPassword(char *);
void enregistrerUser(User *);
User *chargementUser();
void enregistrerLivre(Livre *);

void crypt(char *message, int key)
{
    int i;
    char str;

    for (i = 0; message[i] != '\0'; i++)
    {
        str = message[i];
        if (str >= 'a' && str <= 'z')
        {
            str = str + key;
            if (str > 'z')
                str = str - 26;
            message[i] = str;
        }
        else if (str >= 'A' && str <= 'Z')
        {
            str = str + key;
            if (str > 'Z')
                str = str - 26;
            message[i] = str;
        }
    }
}
void saisir_utilisateur(User **list_utilisateur)
{
    int i, nbUtilisateur;
    printf("\n\n\tVeuillez saisir le nombre d'etulisateur que vous voullez ajouter : ");
    scanf("%d", &nbUtilisateur);
    for (i = 0; i < nbUtilisateur; i++)
    {
        User *u;
        u = (User *)malloc(sizeof(User));
        printf("\n\n\tEntrer les info pour l'etulisateur numero %d : \n\n", i + 1);
        printf("\n\tVotre identifient  CIN(0),CNE(1),APOGEE(2) :  ");
        scanf("%d", &u->id);
        if (u->id == 0)
        {
            printf("\n\tEntrer le CIN : ");
            scanf("%s", u->login.CIN);
        }
        else if (u->id == 1)
        {
            printf("\n\tEntrer le CNE : ");
            scanf("%s", u->login.CNE);
        }
        else if (u->id == 2)
        {
            printf("\n\tEntrer le numero  APOGEE : ");
            scanf("%d", &u->login.APOGEE);
        }
        printf("\n\tEntrer le mot de passe : ");
        fflush(stdin);
        masskPassword(u->password);
        crypt(u->password, 5);
        printf("\n\n\tType  ETUDIANT(0), ADMINISTRATEUR(1) : ");
        scanf("%d", &u->type);
        fflush(stdin);
        printf("\n\tNom : ");
        fflush(stdin);
        gets(u->nom);
        printf("\n\tPrenom : ");
        fflush(stdin);
        gets(u->prenom);
        printf("\n\tDate de naissance : ");
        fflush(stdin);
        gets(u->date_N);
        ajouterUtilisateur(list_utilisateur, u);
        // ins_end(list_utilisateur, u);
        printf("\n\n\n\tUtilisateur bien ajoute !\n\n");
    }
}

void masskPassword(char pass[])
{
    char ch;
    int i = 0;
    while (1)
    {
        ch = getch();
        if (ch != ENTER && ch != BACKSPC && ch != TAB)
        {
            pass[i] = ch;
            i++;
            printf("*");
        }
        else if (ch == ENTER)
        {
            pass[i] = '\0';
            break;
        }
        else if (ch == BACKSPC)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            continue;
        }
    }
}

User *authentification(User *liste, char *login, char *password)
{
    User *ptr = liste;
    while (ptr != NULL)
    {
        if (strcmp(ptr->login.CIN, login) == 0 && strcmp(ptr->password, password) == 0)
        {
            return ptr;
        }
        ptr = ptr->suivant;
    }

    return NULL;
}

User *authentificationApogee(User *liste, int login, char *password)
{
    User *ptr = liste;
    while (ptr != NULL)
    {
        if (ptr->login.APOGEE == login && strcmp(ptr->password, password) == 0)
        {
            return ptr;
        }
        ptr = ptr->suivant;
    }

    return NULL;
}
void deconnexion()
{
    system("cls");
    char r;
    printf("\n\n\n\t\t\tETES-VOUS SURE DE LA DECONNEXION ? [ Y / N ]  \n\n\n\t\t");
    scanf(" %c", &r);
    if (r == 'Y')
    {
        system("cls");
        printf("\n\n\n\t\t\tVous Etes Deconnectes !\n\n\n\n");
        getch();
        exit(1);
    }
    else if (r == 'N')
    {
        system("cls");
        printf("\n\n\n\t\t\tVous Etes Encore Connectes !\n\n\n\n");
    }
}
Livre *ajouterLivre(Livre **ListLivre, Livre *nvLivre)
{
    Livre *tmp = (Livre *)malloc(sizeof(Livre));
    strcpy(tmp->auteur, nvLivre->auteur);
    strcpy(tmp->ISBN, nvLivre->ISBN);
    strcpy(tmp->titre, nvLivre->titre);
    tmp->suivant = NULL;
    tmp->suivant = *ListLivre;
    *ListLivre = tmp;
    return *ListLivre;
}
void afficherLivre(Livre *head)
{
    if (head == NULL)
        printf("\n\tLa liste des livres est vide !! \n");
    else
    {
        printf("\n\n\t\t\t**********AFFICHAGE DES LIVRES********** \n");
        Livre *tmp = head;
        int i = 1;
        while (tmp != NULL)
        {
            printf("\n\t\tLes info pour le livre numero %d : \n", i);
            printf("\n\tISBN : %s\n\tTitre : %s\n\tAuteur : %s\n", tmp->ISBN, tmp->titre, tmp->auteur);
            tmp = tmp->suivant;
            i++;
        }
    }
}

User *ajouterUtilisateur(User **head, User *nvUtilisateur)
{
    User *tmp = (User *)malloc(sizeof(User));
    tmp->id = nvUtilisateur->id;
    tmp->login = nvUtilisateur->login;
    strcpy(tmp->password, nvUtilisateur->password);
    tmp->type = nvUtilisateur->type;
    strcpy(tmp->nom, nvUtilisateur->nom);
    strcpy(tmp->prenom, nvUtilisateur->prenom);
    strcpy(tmp->date_N, nvUtilisateur->date_N);
    tmp->suivant = NULL;
    tmp->suivant = *head;
    *head = tmp;
    return *head;
}

/*void ins_end(User **head, User *nvUtilisateur)
{
    User *ptr = head;
    User *tmp = (User *)malloc(sizeof(User));
    tmp->id = nvUtilisateur->id;
    tmp->login = nvUtilisateur->login;
    strcpy(tmp->password, nvUtilisateur->password);
    tmp->type = nvUtilisateur->type;
    strcpy(tmp->nom, nvUtilisateur->nom);
    strcpy(tmp->prenom, nvUtilisateur->prenom);
    strcpy(tmp->date_N, nvUtilisateur->date_N);

    tmp->suivant = NULL;
    while (ptr->suivant != NULL)
        ptr = ptr->suivant;
    ptr->suivant = tmp;
}*/
void afficherUtilisateur(User *head)
{
    if (head == NULL)
        printf("\tLa liste d'etulisateurs est vide !! \n ");
    else
    {
        printf("\t\t\t*** AFFICHAGE DES INFORMATIONS DES UTILISATEURS ***\n\n\n\n");
        User *tmp = head;
        int i = 1;
        while (tmp != NULL)
        {
            printf("\t\t-- Infos pour l'etulisateur numero %d --\n\n", i);
            printf("\tNom : %s\n\tPrenom : %s\n", tmp->nom, tmp->prenom);
            printf("\tType : %s\n", (tmp->type == 1) ? "Admin" : "Etudiant");
            printf("\tMot de passe : %s\n\n\n", tmp->password);
            tmp = tmp->suivant;
            i++;
        }
    }
}
void saisir_livre(Livre **liste)
{
    int i, nbLivre;
    printf("\n\tentrer le nombre de livre que vous voullez ajouter : ");
    scanf("%d", &nbLivre);
    for (i = 0; i < nbLivre; i++)
    {
        Livre *l = (Livre *)malloc(sizeof(Livre));
        printf("\n\tEntrer les info pour le livre numero %d : \n", i + 1);
        printf("\tTitre : ");
        scanf(" %[^\n]s", l->titre);
        printf("\tAuteur : ");
        scanf(" %[^\n]s", l->auteur);
        printf("\tISBN  :");
        scanf(" %[^\n]s", l->ISBN);
        ajouterLivre(liste, l);
        printf("\n\tLivre bien ajoute \n\n");
    }
}
void enregistrerUser(User *liste)
{
    FILE *fp;
    if ((fp = fopen("fichierUtilisateurs.bin", "ab")) == NULL)
    {
        fprintf(stderr, "\n\tErreur : impossible d'ouvrir le fichier \"fichierUtilisateurs.bin\"\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        User *ptr = liste;
        while (ptr != NULL)
        {
            fwrite(ptr, sizeof(User), 1, fp);
            ptr = ptr->suivant;
        }
        // printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tEnregistrement avec succes\n");
    }
    fclose(fp);
}
User *chargementUser()
{
    FILE *fp;
    if ((fp = fopen("fichierUtilisateurs.bin", "rb")) == NULL)
    {
        fprintf(stderr, "\n\tErreur : impossible d'ouvrir le fichier \"fichierUtilisateurs.bin\"\n");
        return NULL;
    }

    User *list = NULL;
    User *tmp = NULL;
    while ((tmp = (User *)malloc(sizeof(User))) && fread(tmp, sizeof(User), 1, fp) == 1)
    {
        ajouterUtilisateur(&list, tmp);
        // tmp->suivant = list;
        // list = tmp;
    }
    fclose(fp);
    return list;
}
void enregistrerLivre(Livre *list_livre)
{
    FILE *fp;
    if ((fp = fopen("fichierLivre.txt", "a")) == NULL)
    {
        fprintf(stderr, "\n\tErreur : Impossible d'ouvrir le fichier \"fichierLivre.txt\"\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        Livre *ptr = list_livre;
        while (ptr)
        {
            fprintf(fp, "%s\n%s\n%s\n", ptr->titre, ptr->auteur, ptr->ISBN);
            ptr = ptr->suivant;
        }
        printf("\n\tEnregistrement reussi \n");
    }
    fclose(fp);
}

Livre *chargementLivre()
{
    FILE *fp;
    if ((fp = fopen("fichierLivre.txt", "r")) == NULL)
    {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier \"fichierLivre.txt\"\n");
        return NULL;
    }
    Livre *list = NULL;
    Livre *ptr = NULL;
    while ((ptr = (Livre *)malloc(sizeof(Livre))) && fscanf(fp, "%s\n%s\n%s\n", ptr->titre, ptr->auteur, ptr->ISBN) == 3)
    {
        ajouterLivre(&list, ptr);
    }
    fclose(fp);
    return list;
}
