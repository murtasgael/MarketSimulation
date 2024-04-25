#include "Exception/exception.h"
#include "Trading/trading.h"
#include "Utils/utils.h"
#include "Simulation/simulation.h"

using namespace std;

int main(){
    //Situation à réglé plus tard :
    /*string s = "3.543521";
	Bougie B("2.5","t;!1",s,"1");
	B.affiche();*/
    
    //Exception::THROW = true;
    TabExt<string> tab(0);
    tab.get(1)="z";
    cout << endl << "Result : " << tab.getConst(2) << endl;
    //Exception::BYPASS = true;
    tab.get(2)="2";
    cout << endl << "Result : " << tab.getCopie(2) << endl;

	/*Bougie B1(2,2,2,1);
    tab.get(1)=B1;
	Bougie B2(1,2,3,1);
    tab.get(2)=B2;
	Bougie B3(3,2,4,1);
    tab.get(3)=B3;
	Bougie B4(2,2,5,1);
    tab.get(4)=B4;
    tab+B4+B2;
    for(int i=1; i<=tab.Taille(); i++){
        tab.get(i).affiche();}*/
    //TabExt2<int> tab(0,2);
    //tab.get(4,2);

    //Table T("test2");
    //T.affiche();
    //T.CSV("test.txt");
    //cout << readFile("Donnée/test");
    
    /*TimeFrame tf(1,TimeUnit::d);
    TimeFrame tf2;
    tf.affiche();
    cout << tf.duree() << endl;
    cout << tf.duree(tf2) << endl;*/

    /*TimeFrame tf(1,TimeUnit::m);
    Chart C("Donnée/test2", tf);
    C.toFile("Donnée/result");*/

    //cout<< Random::normalT(3000000000).get(1) << endl;
    

    //TimeFrame tf(1,TimeUnit::h);
    //BrownianProcess P(100,0.000001,0.001,tf,100000000);
    //StocReturn P(10000, 0.0001, 0.001, 0.3, 0.0002, 0.4, 0.00001, tf, 10000);
    //P.chart.toFile("Donnée/testStocReturn");
    
    cout << "SUCCES \n";
    return 0;
}

