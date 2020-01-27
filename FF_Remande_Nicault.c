#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Heros
int xp = 0;
int niveau = 1;
int lvl = 1;
int gold = 0;

float PV = 0;
int PV_min = 0;

int PM_max = 0;
int PM = 0;

int attk = 0;
int sort = 0;

//Effets
int poisonne_m = 0;
int poisonne_j = 0;
int brule = 0;

//Autre
int tour = 10000;
int aide = 0;
int choix_hero;

//Monstre
float vie_m = 12;
int pm_m = 30;
int choix_m = 0;


typedef struct Hero
{
    int classe;
    float PV;
    int PV_min;
    int PM;
    int PM_max;
    int attk;
    int sort;
} hero;

hero Barbare = {1,30,30,15,15,25,1};
hero Voleur = {2,30,30,25,25,15,2};
hero Mage = {3,20,20,40,40,10,3};
hero Paladin = {4,45,45,20,20,5,4};
hero Archer = {5,25,25,25,25,20,5};


int a = 1;
int b = 4;

int rand_a_b(int a, int b){
    srand (time( NULL ));
    return rand()%(b-a) +a;
}

base(){ 

    for (tour=10000 ; tour>=0 ; tour--){
        int choix_j;
        int choix_m = rand_a_b(1,4);
        int choix_p1 = rand_a_b(1,3);

        if(xp == 100){
            lvl += 1;
            printf("Vous avez passe un niveau\nVous etes niveau %d \n", lvl);
            PV = PV_min*lvl;
            PM += 2*lvl;
            PM_max += 2*lvl;
            xp = 0;
        }
    
        if(PM < PM_max){
            PM += 1;
        }

        if (brule == 1){
            vie_m -= 5;
        }
                
        if (poisonne_m == 1){
            vie_m -= 1;
        }

        if (poisonne_j == 1){
            PV -= 1;
        }           
                
        if (PV <= 0){
            printf("YOU DIED\n");
            break;
        }
                
        if (vie_m <= 0){
            printf("Le monstre est mort\n");
            xp += 25;
            niveau += 1;
            vie_m = 12*niveau;
            pm_m = 30;
            PV = PV_min*lvl;
            PM += 2*lvl;
            PM_max += 2*lvl;
            poisonne_j = 0;
            poisonne_m = 0;
            brule = 0;
            printf("Vous descendez plus bas\nVous entrez au niveau %d \n", niveau);
            printf("Un nouveau monstre apparait avec %f PV\n", vie_m);
    
        }
    
        scanf("%d", &choix_j);
                
        while (PM < 10){
            if (choix_j > 2){
                printf("Vous n'avez plus assez de mana, dans la confusion personne ne fait rien\n");
                printf("Attaquez ou defendez-vous\n");
                scanf("%d", &choix_j);
            }
            else{
                break;
            }
        }


    
        switch(choix_j) {
            case 1 :
                switch(choix_m) {
                    case 1 :
                        vie_m -= attk;
                        
                        printf("Vous attaquez, Monstre perd 1 PV ");
                            
                        if(vie_m>0){
                            printf("Monstre contre-attaque,");
                            
                            if(choix_p1 == 1){
                                printf(" Vous perdez 1 PV\nVous reste %f PV\nVotre allie attaque\n", PV);
                                vie_m -= 5;
                                printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                                PV -= 1;
                                printf("Vous reste %f PV\n", PV);
                            }
                        
                            else{
                                PV -= 0.5;
                                printf("Votre allie vous defends\nVous ne prenez que la moitie des degats\n");
                            }
                        }
                    break;
                        
                    case 2 :
                        vie_m -= (attk/4);
                        printf("Vous avez attaque, Monstre perd 1/4 PV, Il a encore %f PV\n", vie_m);
                    break;

                    case 3 : 
                        if (pm_m != 0){
                            printf("Vous avez attaque, Monstre a perdu un PV, Il n'a plus que %f PV\n", vie_m);
                            if(vie_m>0){
                                printf("Monstre lance Poison, Vous prenez 1 dgt/tour\nVous reste %f PV\n", PV);
                                poisonne_j = 1;
                                pm_m -= 10;
                                
                                if(choix_p1 == 1){
                                    vie_m -= 5;
                                    printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                                }
                        
                                else{
                                    printf("Votre allie vous defends\n");
                                }                            
                            }
                        }
                    break;
                }

                break;
                
            break;
                
            case 2 :
                switch(choix_m) {
                    case 1 :
                        printf("Vous vous defendez\n");
                        printf("Le Monstre attaque\n");
                        
                        if(choix_p1 == 1){
                            printf("Votre allie attaque\n");
                            vie_m -= 5;
                            printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                            PV -= 0.25;
                            printf("Vous reste %f PV\n", PV);
                        }
                        
                        else{
                            printf("Votre allie vous defends\nVous ne prenez pas de degats\n");

                        }

                    break;

                    case 2 :
                        printf("Vous n'avez pas attaque ");           
                        if(vie_m>0){
                            if(choix_p1 == 1){
                                printf("Votre allie attaque\n");
                                vie_m -= 2.5;
                                printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                                
                                if(poisonne_m==1){
                                    printf("Monstre a perdu des PV du au poison, Il a encore %f PV\n", vie_m);
                                }
                                        
                                else{
                                    printf("Monstre n'a perdu aucun PV, Il a encore %f PV\n", vie_m);
                                }
                            }
                        
                            else{
                                printf("Votre allie vous defends\n");
                                if(poisonne_m==1){
                                    printf("Monstre a perdu des PV du au poison, Il a encore %f PV\n", vie_m);
                                }
                                        
                                else{
                                    printf("Monstre n'a perdu aucun PV, Il a encore %f PV\n", vie_m);
                                }
                            }

            
                            printf("Monstre se protege, Vous ne perdez aucun PV\nVous reste %f PV\n", PV);
                        }
                    break;
        
                    case 3 : 
                        if(pm_m != 0){
                            printf("Monstre n'a perdu aucun PV, Il a encore %f PV\n", vie_m);
                            printf("Monstre lance Poison, Vous prend 1 dgt/tour\nVous reste %f PV\n", PV);
                            poisonne_j = 1;
                            pm_m -= 10;
                        }
                        if(choix_p1 == 1){
                            printf("Votre allie attaque\n");
                            vie_m -= 5;
                            printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                        }
                        
                        else{
                            printf("Votre allie vous defends\nVous ne prenez pas de degats\n");

                        }
                    break;
                }
                break;
                
            break;
    
            case 3 :
                PM -= 5;
                
                switch(choix_m) {   
                    case 1 :

                        printf("Vous lancez Poison, Monstre prend 1 dgt/tour, Il a encore %f PV\n", vie_m);

                        if(vie_m>0){

                            if(choix_p1 == 1){
                                printf("Votre allie attaque\n");
                                vie_m -= 5;
                                printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                                PV -= 1;
                                printf("Monstre attaque, Vous ne vous etes pas protege, vous perdez 1 PV\nVous reste %f PV\n", PV);
                                printf("Vous reste %f PV\n", PV);
                            }
                        
                            else{
                                PV -= 0.5;
                                printf("Votre allie vous defends\nVous ne prenez que la moitie des degats\n");

                            }
                        }
                        poisonne_m = 1;
                    
                    break;
                        
                    case 2 :
                        printf("Vous lancez Poison, Monstre prend 1 dgt/tour, Il a encore %f PV\n", vie_m);
                            
                        if(vie_m>0){
                            printf("Monstre se protege, Vous perd 0 PV\nVous reste %f PV\n", PV);
                            if(choix_p1 == 1){
                                printf("Votre allie attaque\n");
                                vie_m -= 2.5;
                                printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                            }
                        
                            else{
                                printf("Votre allie vous defends\n");

                            }
                        }
                        poisonne_m = 1;
                    break;
        
                    case 3 : 
                        if (pm_m != 0){
                            printf("Vous lancez Poison, Monstre prend 1 dgt/tour, Il a encore %f PV\n", vie_m);
                                
                            if(vie_m>0){
                                printf("Monstre lance Poison, Vous etes empoisonne \nVous reste %f PV\n", PV);
                                poisonne_j = 1;
                                pm_m -= 10;
                            }
                            
                            if(choix_p1 == 1){
                                printf("Votre allie attaque\n");
                                vie_m -= 5;
                                printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                            }
                        
                            else{
                                printf("Votre allie vous defends\n");

                            }    
                            poisonne_m = 1;
                        }
        
                        printf("Vous reste %d PM\n", PM);
                    break;
                }
                break;

            break;
    
            case 4 :
                PM -= 10;
                    
                switch (choix_m) {
                    case 1 :
                        PV -= 1;
                        printf("Vous lancez Antidote, Poison est retire\n");
                            
                        if(vie_m>0){
                            if(choix_p1 == 1){
                                printf("Votre allie attaque\n");
                                vie_m -= 5;
                                printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                                PV -= 1;
                                printf("Monstre attaque, Vous ne vous etes pas protege, vous perdez 1 PV\nVous reste %f PV\n", PV);
                                printf("Vous reste %f PV\n", PV);
                            }
                        
                            else{
                                PV -= 0.5;
                                printf("Votre allie vous defends\nVous ne prenez que la moitie des degats\n");

                            }
                        }

                        poisonne_j = 0;
                    break;
                
                    
                    case 2 :
                        printf("Vous lancez Antidote, Poison est retire\n");
                            
                         if(vie_m>0){
                            printf("Monstre se protege, Vous perd 0 PV\nVous reste %f PV\n", PV);
                            if(choix_p1 == 1){
                                printf("Votre allie attaque\n");
                                vie_m -= 2.5;
                                printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                            }
                        
                            else{
                                printf("Votre allie vous defends\n");

                            }

                        poisonne_j = 0;
                    break;
                
    
                    case 3 : 
                        if(pm_m != 0){
                            printf("Vous lancez Antidote, Poison est retire\n");
                                
                            if(vie_m>0){
                                printf("Monstre lance Poison, Vous etes empoisonne \nVous reste %f PV\n", PV);
                                poisonne_j = 1;
                                pm_m -= 10;
                            }
                            
                            if(choix_p1 == 1){
                                printf("Votre allie attaque\n");
                                vie_m -= 5;
                                printf("Monstre perd 5 PV\nIl a encore %f PV\n", vie_m);
                            }
                        
                            else{
                                printf("Votre allie vous defends\n");

                            } 
                            poisonne_j = 0;

                        }
                    break;
                }
                break;
    
                printf("Vous reste %d PM\n", PM);
                }
                
            break;

            case 5 :
                switch (sort) {
                    case 1 :
                        PM = 0;
                        vie_m -= 40;
                        printf("Vous entrez dans une rage folle, le monstre perds 40 PV\n");

                    break;

                    case 2 :
                        PM = 0;
                        gold += 75;
                        printf("Vous trouvez une cache avec 75 pieces d'or\n");
                    break;

                    case 3 :
                        PM = 0;
                        vie_m -= 40;
                        brule = 1;
                        printf("Vous lancez une boule de feu, le monstre perds 40 PV et brule\n");
                    break;

                    case 4 :
                        PM = 0;
                        PV += 40;
                        printf("Vous priez les dieux, vous regagnez 40 PV\n");
                    break;

                    case 5 :
                        PM = 0;
                        vie_m -= 40;
                        printf("Vous decochez une fleche vitale, le monstre perds 40 PV\n");
                    break;
                }
            break;

        }
    }
}

barbare(){

    //Hero
    xp = 0;
    niveau = 1;
    lvl = 1;
    gold = 0;

    PV = Barbare.PV;
    PV_min = Barbare.PV_min;

    PM_max = Barbare.PM_max;
    PM = Barbare.PM;

    attk = Barbare.attk;
    sort = Barbare.sort;

    base();
}

voleur(){

    //Hero
    xp = 0;
    niveau = 1;
    lvl = 1;
    gold = 0;

    PV = Voleur.PV;
    PV_min = Voleur.PV_min;

    PM_max = Voleur.PM_max;
    PM = Voleur.PM;

    attk = Voleur.attk;
    sort = Voleur.sort;

    base();
}

mage(){

    //Hero
    xp = 0;
    niveau = 1;
    lvl = 1;
    gold = 0;

    PV = Mage.PV;
    PV_min = Mage.PV_min;

    PM_max = Mage.PM_max;
    PM = Mage.PM;

    attk = Mage.attk;
    sort = Mage.sort;

    base();
}

paladin(){

    //Hero
    xp = 0;
    niveau = 1;
    lvl = 1;
    gold = 0;

    PV = Paladin.PV;
    PV_min = Paladin.PV_min;

    PM_max = Paladin.PM_max;
    PM = Paladin.PM;

    attk = Paladin.attk;
    sort = Paladin.sort;

    base();
}

archer (){

    //Hero
    xp = 0;
    niveau = 1;
    lvl = 1;
    gold = 0;

    PV = Archer.PV;
    PV_min = Archer.PV_min;

    PM_max = Archer.PM_max;
    PM = Archer.PM;

    attk = Archer.attk;
    sort = Archer.sort;

    base();
}

int main(){

    printf("Choisissez votre classe\n1 pour le Barbare\n2 pour le Voleur\n3 pour le Mage\n4 pour le Paladin\n5 pour le Archer\n");
    scanf("%d", &choix_hero);

    printf("Pour avoir une aide tapez 1, pour jouer directement tapez 2\n");
    scanf("%d", &aide);

    if (aide == 1){
        printf("Pour attaquer tapez '1'\nPour parer tapez '2'\nPour lancer un sort de Poison tapez '3'\nPour lancer un sort d'Antidote tapez '4'\n \n \n                           BONNE CHANCE\n");
        aide = 2;
    }
    
    if (aide == 2){
        printf("Vous entrez dans le donjon, un premier monstre apparait\n");
        printf("PV Gobelin: %f \n", vie_m);

        switch(choix_hero){
            case 1 :
                barbare();
                break;

            case 2 :
                voleur();
                break;

            case 3 :
                mage();
                break;

            case 4 :
                paladin();
                break;

            case 5 :
                archer();
                break;
        }
    }
    return 0;
}
