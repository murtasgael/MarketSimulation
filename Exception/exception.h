#include <source_location>
#include <iostream>

#ifndef _EXCEPTION
#define _EXCEPTION
class Exception {

    public:
		//addresse de l'object dans lequel l'exception est déclancher
		const void* obj;
        
        //localisation du déclanchement de l'exception
        std::source_location location;

		//passer a true pour ignorer complétement la gestion d'exception
		//À utiliser uniquement au cours du dévelloppement où dans certain cas précis pour accéléré un peu l'exécution
		static bool BYPASS;
		
		//passer a true pour renvoyer les exceptions au lieu de tenter de les gérées
		//cela donne la possibilité de façon indépendante du comportement prévu par leur classe lors de leur détections en cas de besoin
		static bool THROW;
		
		//chemin du fichier de LOG
		//static std::string path;


	protected :
		std::string message;

    enum class ExceptionType {
	    warning, //Préviens l'utilisateur d'un danger potentiel le programme tante de continuer sans changement
	    error, //on tente de continuer l'exécution mais après avoir géré l'exception en moditiant un variable par exemple
	    fatal_error //on arrête immédiatement l'exécution
    };
		ExceptionType type;
		
		//construction interdite le constructeur sera seulement appeller par les classes filles
		Exception(const void*, const std::source_location &, const ExceptionType &);
		Exception() = delete;
		
		//afficahge des information de l'erreur dans le terminal
		void affiche();
		
        //afficahge des information de l'erreur dans un fichier de LOG - À FAIRE -
		//void toLOG();
};

class TabExtException : public Exception{ 
    
    using Exception::Exception;

    private :
        size_t size; 
        size_t alloc;

        TabExtException(const void *, const std::source_location &, const ExceptionType &, const size_t &, const size_t &);
        
        void constructionFailed();

        void accessDenied(const size_t & s);

    public :
        //vérification des paramètres du constructeur
        static void constructorCheck(size_t &, const std::source_location & location);
        
        //vérification des paramètres des accesseurs
        static void accessCheck(const void*, const std::source_location &, const size_t &, const size_t &, const size_t &);
    };



#endif
