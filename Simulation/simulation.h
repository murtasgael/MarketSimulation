#ifndef SIMULATION
#define SIMULATION

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <utility>
#include <chrono>
#include "../Utils/utils.h"
#include "../Trading/trading.h"

//Génerateur de nombre aléatoire utilisant les patterns de "sigleton" et "factory".
class Random{
    public:
        //Création et accès de l'instance de notre objet
        static Random & getI();

        //Génération d'un nombre suivant la loi normale centrée réduite
        static double normal();
        //Tableau de nombre suivant la loie normale
        static TabExt<double> normal(const size_t &);
        // Équivalent multi-thread !
        // Par défautl 48 threads utilisé
        static TabExt<double> normalT(const size_t &);
        //On peut aussi choisir le nombre de thread
        static TabExt<double> normalT(const size_t &,size_t);

    private:
        //moteurs de gérération aléatoire
        //nombre suivant une loie normale dépendand de son espérence et son écrat-type
        ////solution proposé par la bibliothèque standard
        double std_normal(const double &, const double &);
        
        //fonction appeler pour chaque thread dans la génération multi-thread
        static void normalThread(const size_t &, TabExt<double> &, const size_t &);

        //Génération de l'entier aléatoire qui servira pour généré les autres loi
        //double rand();

        //Stockage de l'instance de notre object
        static Random* instance;
        //true si l'object à déjà été créé initialiser a false dans le cpp
        static bool isInstantiate;
        //true si un travail en multi-thread est en cours;
        //on veut éviter que puisieur travail en multi-thread soit lancé indépendament
        static bool threadWork;

        Random();
        Random(const Random &) = delete;
        
        friend class RandomException;

};

class Simulation
{
    /*
     * MODIFICATION IPORTANTE A FAIRE:
     * Prendre en compte une seconde time frame, 
     * on veut pouvoir calculer les processus aléatoire dans une time frame mais afficher les processus dans une autre
     * exemple : on aimerais pouvoir calculer le process a partir de la volatilité par an mais sortir une Chart par minute
    */
    public:
        //le chart qui contiendra les données générés
        Chart chart;


    protected :
        //construction interdite -abstract class- constructeur seulement utilisable par les classes filles
        Simulation(const TimeFrame &, size_t &);//nombre de bougie et la time frame
        //nombre de Tic par bougie
        static const size_t nbTicks = 100;
        //nombre de ticks au total
        size_t size;
        //granularité
        double dt;
        //méthode indispensable a toute simulation génération de la chart a partir de variable aléatoire
        virtual void generate() = 0;
        //Transformation d'un TabExt en Chart
        void toChart (const TabExt<double> &);
};

class BrownianProcess : public Simulation
{
    using Simulation::Simulation;

    public:
        //Construction à partir de la valeur initiale, l'espérence de rentabilité, la volatilité, la TimeFrame des bougies, le nombre de bougies
        //pour l'instant l'espérence de rentabilité et la volatilité sont dans la time frame des bougie
        BrownianProcess(const double &, const double &, const double &, const TimeFrame &,size_t &);

    protected :
    const double s; //Valeur initiale
    const double r; //taux d'actualisation
    const double vol; //volatilité du sous-jacent en % (sur une unité de période)

    private:
        virtual void generate();
};


/*
 * TOUJOURS EN CHANTIER NE PAS UTILISER
 * Processus d'Heston légérement simplifier, 
 * prendre le temps plus tard de bien vérifier les équations et de les modifier pour prendre en compte toutes les subtilitées du modèle
 */
class HestonProcess : public Simulation
{
    public:
        //en plus des paramètres utiliser pour la construction du mouvement Brownien nous allons inclure les paramètres rho kapa et xi
        HestonProcess(const double &, const double &, const double &, const double &, const double &, const double &, const TimeFrame &,size_t &);
        
    protected:
        //paramètres basiques
        const double s; //Valeur initiale
        const double r; //taux d'actualisation
        const double vol; //volatilité du sous-jacent en % (sur une unité de période)
        //paramètres spécifique au modèle d'eston
        const double rho; //correllation entre le processus de prix et le processus de la volatilité
        const double kapa; //vitesse de retour à la volatilité espère du processus de volatilité
        const double xi; //écart-type de la volatilité
        
    private:
        bool fellerCondition(); //vérifi que la condition de feller soit bien vérifié
        virtual void generate();
};

/* STOCHASTIC RETURN
 * Modèle de simulation perso pour l'entrainement des algo basé sur le MACD
 * Idée : Variance et espérence des rendemnts suiventes leur propre procesus stochastique
 * A faire : Dans cettes première version les 3 process var, esp et prix ne sont pas corrélé entre eux, cette corrélation est nécessaire dans la version finale.
 */
class StocReturn : public Simulation
{
    public :
        // constructeur avec paramètre du Bronien plus paramètre spé
        StocReturn(const double &, const double &, const double &, const double &, const double &, const double &, const double &, const TimeFrame &,size_t &);

    protected:
        //paramètre basiques
        double s; //Valeur initiale
        double r; //rendement espéré
        double vol; //volatilité du sous-jacent en % (sur une unité de période)
        //paramètres spécifique au modèle d'eston
        double kapa; //vitesse de retour à la volatilité espère du processus de volatilité
        double xi; //écart-type de la volatilité
        double kapaE; //vitesse de retour à la volatilité espère du processus de volatilité
        double xiE; //écart-type de la volatilité
        double minVol; //volatilité minimale sert à éviter une vol négative
        
    private:
        virtual void generate();

};
#endif
