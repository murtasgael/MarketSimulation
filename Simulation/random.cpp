using namespace std;

//initialisation des membres statiques
Random* Random::instance = NULL;
bool Random::isInstantiate = false;
bool Random::threadWork = false;

Random::Random(){
    isInstantiate = true;
    instance = this;
}

Random & Random::getI(){
    if(!isInstantiate){
    static Random* tmp = new Random;
    }
    return *instance;
}

double Random::normal(){
    return getI().std_normal(0,1);
}

TabExt<double> Random::normal(const size_t & n){
    TabExt<double> T(n);
    for (size_t i = 1; i <= n; i++){
        T.get(i) = normal();
    }
    return T;
}

void Random::normalThread(const size_t & n, TabExt<double> & res, const size_t & i){
    for (size_t j = i; j < i+n; j++){
        res.get(j) = normal();
    }
}

TabExt<double> Random::normalT(const size_t & N){
	//par défault on choisit un nombre de thread assez grand pour être relativement efficace sur différents processeurs
	return normalT(N,48);
}

//N est le nombre de variables voulu et nbT le nombre de threads
TabExt<double> Random::normalT(const size_t & N, size_t nbT){
    //Check de la validité des enter via la classe de gestion d'exception
    RandomException::normalTCheck(threadWork,N,nbT,instance);
    TabExt<double> T(N);
    size_t n = N/nbT+1;//nombre d'opération par threads, +1 pour être sur de tout avoir fait (la dernière thread sera un peu plus courte
    std::vector<jthread> threads;
    for (size_t i = 1; i <= N; i=i+n){
        if(i+n-1 > N){n = N-i+1;} //cout << n << " " << i << endl;
        threads.push_back(jthread(normalThread, (n), ref(T), (i)));
    }
    return T;
}

double Random::std_normal(const double & esp, const double & et){
    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    std::normal_distribution<double> dist (esp, et);
    return dist(generator);
}


