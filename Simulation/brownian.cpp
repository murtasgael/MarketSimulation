Simulation::Simulation(const TimeFrame & tf, size_t & n){
	SimulationException::checkConstructor(n);
    Chart chart(tf,n);
    size = nbTicks*n;
    dt = (double)1/nbTicks;
}

void Simulation::toChart(const TabExt<double> & St){
    SimulationException::checkToChart(this,St);
    for(size_t i=1; i <= chart.taille(); i++){
        size_t tmp = (i-1)*nbTicks+1;
        double o = St.getCopie(tmp);
        double h = St.getCopie(tmp);
        for(size_t j = 1; j< nbTicks; j++){
            if(h < St.getCopie(tmp+j)){
                h = St.getCopie(tmp+j);}
        }
        double l = o;
        for(size_t j = 1; j< nbTicks; j++){
            if(l > St.getCopie(tmp+j)){
                l = St.getCopie(tmp+j);}
        }
        double c = St.getCopie(tmp+nbTicks-1);
        Bougie b(o,h,l,c);
        chart.get(i) = b;
    }
}

BrownianProcess::BrownianProcess(const double & S, const double & R, const double & V, const TimeFrame & tf,size_t & n): 
    s(S), r(R), vol(V), Simulation::Simulation(tf,n){
        generate();
}


void BrownianProcess::generate(){
    //Simulation de processus de Mouvement Brownien par schéma d'Euler
    TabExt<double> St(size);
    TabExt<double> dW = Random::normalT(size-1);
    St.get(1) = s;
    for(size_t i=1; i<size; i++){
      St.get(i+1)=St.get(i)*(1+r*dt+vol*dW.get(i));
    }
    //génération du Chart
    toChart(St);
    }
