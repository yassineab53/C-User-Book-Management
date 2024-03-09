#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define ENTER 13
#define BACKSPC 8
#define TAB 9
#include "yassine.h"
// ! ABBOU YASSINE :  COMPUTER SCIENCE STUDENT AT FSO
int main()
{
    system("cls");
    system("color 0e");
    User *maListe = (User *)malloc(sizeof(User));
    maListe = NULL;
    /*User u1, u2, u3;
    strcpy(u1.nom, "ABBOU");
    strcpy(u1.prenom, "Yassine");
    strcpy(u1.login.CIN, "N123456789");
    // u1.login.APOGEE = 1230;
    strcpy(u1.password, "ys123");
    u1.type = 1;
    u1.suivant = &u2;
    ajouterUtilisateur(&maListe, &u1);
    strcpy(u2.nom, "ABBOU");
    strcpy(u2.prenom, "Oussama");
    strcpy(u2.login.CIN, "1234");
    strcpy(u2.password, "oussama123");
    u2.type = 1;
    u2.suivant = &u3;
    ajouterUtilisateur(&maListe, &u2);
    strcpy(u3.nom, "etudiant");
    strcpy(u3.prenom, "etudiant");
    strcpy(u3.login.CIN, "etudiant");
    strcpy(u3.password, "etudiant");
    u3.type = 0;
    u3.suivant = NULL;
    ajouterUtilisateur(&maListe, &u3);*/

    // enregistrerUser(maListe);
    maListe = chargementUser();

    Livre *list_livre = (Livre *)malloc(sizeof(Livre));
    list_livre = NULL;
    Livre l1, l2;
    strcpy(l1.titre, "La Boite A Merveille");
    strcpy(l1.auteur, "Ahmed Safrioui");
    strcpy(l1.ISBN, "123456");
    l1.suivant = &l2;
    ajouterLivre(&list_livre, &l1);
    strcpy(l2.titre, "Le Dernier Jour D'un Condamne");
    strcpy(l2.auteur, "Victor Hugo");
    strcpy(l2.ISBN, "173150");
    l2.suivant = NULL;
    ajouterLivre(&list_livre, &l2);
    int choix;
    User *u = (User *)malloc(sizeof(User));
    int choixLogin;
    printf("\n\tVoullez-vous s'authentifier en utilisant quoi ?\n\n");
    printf("\t0. CIN\n");
    printf("\t1. CNE\n");
    printf("\t2. APOGEE\n\n");
    printf("\t\tChoix : ");
    scanf("%d", &choixLogin);
    switch (choixLogin)
    {
    case 0:
        system("cls");
        printf("\n\n\n\n\n\n\n\t\t\t\t\tLogin : ");
        scanf(" %[^\n]s", u->login.CIN);
        break;
    case 1:
        system("cls");
        printf("\n\n\n\n\n\n\n\t\t\t\t\tLogin : ");
        scanf(" %[^\n]s", u->login.CNE);
        break;
    case 2:
        system("cls");
        printf("\n\n\n\n\n\n\n\t\t\t\t\tLogin : ");
        scanf("%d", &u->login.APOGEE);
        break;
    }

    printf("\n\n\t\t\t\t\tMot De Passe : ");
    masskPassword(u->password);
    User *uzr = (User *)malloc(sizeof(User));

    if (choixLogin == 0)
    {
        uzr = authentification(maListe, u->login.CIN, u->password);
    }
    else if (choixLogin == 1) // !!!!!!!!!!!!!!
    {
        uzr = authentification(maListe, u->login.CNE, u->password);
    }
    else if (choixLogin == 2)
    {
        uzr = authentificationApogee(maListe, u->login.APOGEE, u->password);
    }
    if (uzr == NULL)
    {
        system("cls");
        system("color 0c");
        printf("\tEchec d'authentification \n");
    }
    else
    {
        system("cls");
        system("color 0a");
        printf("\n\tAuthentification reussi\n\n");
        printf("\tBienvenue Mr %s %s : %s\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t", uzr->nom, uzr->prenom, (uzr->type == 1) ? "ADMINISTRATEUR" : "ETUDIANT");
        system("pause");
        if (uzr->type == 0) // etudient
        {
            do
            {
                system("color 0b");
                system("cls");
                printf("\n\n\n\t\t\t\t========== Menu ==========\n\n\n\n\n");
                printf("\t1. Afficher la liste des livres\n\n");
                printf("\t2. Se deconnecter\n\n");
                printf("\t\t\tChoix : ");
                scanf("%d", &choix);

                switch (choix)
                {
                case 1:
                    system("cls");
                    system("color 0e");
                    afficherLivre(list_livre);
                    printf("\n\n\n\n\n\t");
                    system("pause");
                    break;

                case 2:
                    system("cls");
                    system("color 0c");
                    deconnexion();
                    break;
                }
            } while (choix == 1 || choix == 2);
        }
        else if (uzr->type == 1) // admin
        {
            do
            {
                system("color 0a");
                system("cls");
                printf("\n\n\n\t\t\t\t\t========== Menu ==========\n\n\n\n\n\n");
                printf("\t1. Afficher la liste d'utilisateurs\n\n");
                printf("\t2. Ajouter un utilisateur a la liste des utilisateurs\n\n");
                // printf("\t3. Enregister la liste des utilisateurs dans un fichier binaire\n\n");
                // printf("\t4. Chargement du fichier binaire dans une liste chainee et afficher cette liste\n\n");
                printf("\t3. Afficher la liste des livres\n\n");
                printf("\t4. Ajouter un livre a la liste des livres\n\n");
                // printf("\t7. Enregister la liste des livres dans un fichier texte\n\n");
                printf("\t5. Se deconnecter\n\n\n");
                printf("\t\t\tChoix : ");
                scanf("%d", &choix);

                switch (choix)
                {
                case 1:
                    system("cls");
                    system("color 0e");
                    afficherUtilisateur(maListe);
                    break;
                case 2:
                    system("cls");
                    saisir_utilisateur(&maListe);
                    enregistrerUser(maListe);
                    break;
                /*case 3:
                    system("cls");
                    system("color 0e");
                    enregistrerUser(maListe);
                    // system("pause");
                    break;
                case 4:
                    system("cls");
                    maListe = chargementUser();
                    if (maListe == NULL)
                    {
                        system("color 0c");
                        printf("\n\tChargement impossible\n");
                    }
                    else
                    {
                        system("color 0a");
                        printf("\n\tChargement reussi ! \n");
                        printf("\n\tVeuillez taper n'importe qu'elle boutton pour afficher la liste recupere du fichier  :\n\n\n");
                        getch();
                        system("cls");
                        afficherUtilisateur(maListe);
                    }
                    break;*/
                /*case 4:
                    system("cls");
                    User *listeChargee = chargementUser();
                    if (listeChargee == NULL)
                    {
                        system("color 0c");
                        printf("\n\tChargement impossible\n");
                    }
                    else
                    {
                        system("color 0a");
                        printf("\n\tChargement reussi ! \n");
                        printf("\n\tVeuillez taper n'importe qu'elle boutton pour afficher la liste recupere du fichier  :\n\n\n");
                        getch();
                        system("cls");
                        afficherUtilisateur(listeChargee);
                    }
                    break;*/
                case 3:
                    system("cls");
                    system("color 0e");
                    afficherLivre(list_livre);
                    break;
                case 4:
                    system("cls");
                    system("color 0e");
                    saisir_livre(&list_livre);
                    enregistrerLivre(list_livre);
                    break;
                /*case 7:
                    system("cls");
                    system("color 0a");
                    enregistrerLivre(list_livre);
                    break;*/
                /*case 8:
                    system("cls");
                    Livre *listChargee = chargementLivre();
                    if (listChargee == NULL)
                        printf("Chargement impossible\n");
                    else
                    {
                        printf("Chargement reussi ! \n");
                        printf("affichage de la liste recupere du fichier : \n");
                        afficherLivre(listChargee);
                    }
                    break;*/
                case 5:
                    system("color 0c");
                    deconnexion();
                    break;
                }
                getch();
            } while (choix);
        }
    }

    return 0;
}
