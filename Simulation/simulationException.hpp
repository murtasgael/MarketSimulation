#ifndef SIMEXC
#define SIMEXC

class RandomException
{
	private :
		const Random* obj;
		
		RandomException(const Random * instance){
			obj = instance;
		}
		
		void threadError(size_t & T,const size_t & N){
			if(T>N){
				std::cout <<"ERROR : Nombre de threads supérieur à la taille de la simulation \n" << " Nombre de threads : " << T << "\n Nombre de valeur à calculer : " << N << std::endl;
				throw this;}
			if(T<2){
				std::cout <<"ERROR : Nombre de threads Trop petit \n" << " Nombre de threads : " << T << "\n Veulliez utiliser la fonction \"normal\" au lieu de \"normalT\"." << std::endl;
				throw this;}
		}
		
		
		
	public :
		static void normalTCheck(const bool & threadWork,const size_t & N,size_t & T,const Random * instance){
			if (threadWork){
				std::cout << "Warning : tentative de nouvelle génération multithread mais travail déja en cour \n" << " Instance : " << instance << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}
			else if(T>200){
				std::cout << "WARNING : Nombre de thread trop grand \n" << " nombre de thread : " << T 
				<< "\n pour le calcul paralèle sur CPU l'utilisation de moins de 200 thread est recomendé. \n Nombre de threads par défault rétablie. ";
				T = 48;
			}
			else if((T<2)||(T>N)){
					RandomException e(instance);
					e.threadError(T,N);
				}
		}
};

class SimulationException
{
	private :
		const Simulation * obj;
		
		void ErrorConstructor(const size_t & i){
		
		}
		
		void ErrorToChart(const TabExt<double> & St){
		
		}
		
	public : 
		static void checkConstructor(const size_t & i){
		
		}
		
		static void checkToChart(const Simulation * sim, const TabExt<double> & St){
		
		}
};

#endif
