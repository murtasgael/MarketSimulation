HestonProcess::HestonProcess(const double & S, const double & R, const double & V, const double & Rh, const double & Ka, const double & Xi, const TimeFrame & tf,size_t & n): 
    s(S), r(R), vol(V), rho(Rh), kapa(Ka), xi(Xi),  Simulation::Simulation(tf,n){
        generate();
}


//Il faut prendre en compte la condition de Feller, 2*kapa*vol^2 > xi^2, pour s'assurer que la variance sera positive
bool HestonProcess::fellerCondition(){
   return((2*kapa*vol)>(xi*xi));
   }

void HestonProcess::generate(){
    //Création de deux mouvement brownien corréllé en eux, calcul du prcessus final
    TabExt<double> St(size);
    TabExt<double> Vt(size);
    TabExt<double> dV(size-1);
    TabExt<double> dW = Random::normalT(size-1);
    TabExt<double> tmp = Random::normalT(size-1);
    St.get(1) = s;
    Vt.get(1) = vol;
    for(size_t i=1; i <size; i++){
        //calcul de processus Vt corélé avec St
        dV.get(i) = rho*dW.get(i)+sqrt(1-rho*rho)*tmp.get(i);//À faire: remplacer sqrt par un fonction optimisé perso
        Vt.get(i+1) = Vt.get(i) + kapa*(vol-Vt.get(i))*dt + xi*dV.get(i);//note: cette équation est une vertion simplifier de l'équation original
        //calcul de process St
        St.get(i+1) = St.get(i)*(1+r*dt+Vt.get(i)*dW.get(i));
    }
    //génération du Chart
   toChart(St);
}
