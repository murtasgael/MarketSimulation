StocReturn::StocReturn(const double & S, const double & R, const double & V, const double & Ka, const double & Xi, const double & KaE, const double & XiE, const TimeFrame & tf, size_t & n): 
    s(S), r(R), vol(V), kapa(Ka), xi(Xi), kapaE(KaE), xiE(XiE), Simulation::Simulation(tf,n){
        minVol = V/10;
        generate();
}


void StocReturn::generate(){
    //Création des 2 processus aléatoire
    TabExt<double> St(size);
    TabExt<double> Vt(size);
    TabExt<double> Et(size);
    TabExt<double> dS = Random::normalT(size-1);
    TabExt<double> dV = Random::normalT(size-1);
    TabExt<double> dE = Random::normalT(size-1);
    St.get(1) = s;
    Vt.get(1) = vol;
    Et.get(1) = r;
    for(size_t i=1; i <size; i++){
        //calcul de processus Vt
        if (Vt.get(i) < minVol){
            Vt.get(i) = minVol;
        }
        Vt.get(i+1) = Vt.get(i) + kapa*(vol-Vt.get(i))*dt + xi*dV.get(i);
        //calcul pros Et
        Et.get(i+1) = Et.get(i) + kapaE*(r-Et.get(i))*dt + xiE*dE.get(i);
        //calcul de process St
        St.get(i+1) = St.get(i)*(1+Et.get(i)*dt+Vt.get(i)*dS.get(i));
        //std::cout << St.get(i) << " " << Et.get(i) << " " << Vt.get(i) << " " << dt << std::endl;
    }
    //génération du Chart
   toChart(St);
}
