#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;


class OperatiuniBancare {
protected:
    double sumaop;
    int data;
public:
    OperatiuniBancare() {
        sumaop = 0;
        data = 0;
    }
    OperatiuniBancare(double suma, int dataop)
    {
        sumaop = suma;
        data = dataop;
    }
    virtual double retragerebani() = 0;
    virtual void sumanoua(double&) = 0;
};



class AlimentareCont :public OperatiuniBancare {
public:
    AlimentareCont(double sumacont, int data) :OperatiuniBancare(sumacont, data) {};
    double retragerebani()
    {
        return 0;
    }
    void sumanoua(double& x) {

        x += sumaop - max(5.0, sumaop * 0.1);
    }
};



class DepozitConstituire :public OperatiuniBancare {
public:
    DepozitConstituire(double sumacont, int data) :OperatiuniBancare(sumacont, data) {};
    double retragerebani()
    {
        return sumaop;
    }
    void sumanoua(double& x) {
        x += -sumaop;
    }
};



class DepozitScadenta :public OperatiuniBancare {
    double dobanda;
    int perioada;
public:
    DepozitScadenta(double sumacont, int data, double dobanda, int perioada) :OperatiuniBancare(sumacont, data)
    {
        this->dobanda = dobanda;
        this->perioada = perioada;
    }
    double retragerebani()
    {
        return 0;
    }
    void sumanoua(double& x) {
        double dobandax = (dobanda / 12) * perioada;
        double impozitx = dobandax * 0.1;
        x += sumaop + sumaop * dobandax - sumaop * impozitx;

    }
};



class PlataCredit :public OperatiuniBancare {
    int dataplata;
    double dobanda;
public:
    PlataCredit(double sumacont, int data, int dataplata, double dobanda) : OperatiuniBancare(sumacont, data)
    {
        this->dataplata = dataplata;
        this->dobanda = dobanda;
    }
    double retragerebani()
    {
        return sumaop;
    }
    void sumanoua(double& x) {
        double dobandax = dobanda / 12.0;
        double penalizare = 2.0 * (data - dataplata) / 100.0;
        x += -sumaop - dobandax * sumaop - penalizare * (sumaop + dobandax * sumaop);
    }
};



int main()
{
    int n; cin >> n;
    vector<OperatiuniBancare*> operatii;

    for (int i = 0; i < n; i++)
    {
        string nume;
        int data, dataplata, perioada;
        double suma, dobandas, dobandap;
        cin >> nume >> suma >> data;
        if (nume == "AC") {

            operatii.push_back(new AlimentareCont(suma, data));
        }
        else if (nume == "DC") {

            operatii.push_back(new DepozitConstituire(suma, data));
        }
        else if (nume == "DS") {
            cin >> dobandas >> perioada;

            operatii.push_back(new DepozitScadenta(suma, data, dobandas, perioada));
        }
        else if (nume == "PC") {
            cin >> dataplata >> dobandap;

            operatii.push_back(new PlataCredit(suma, data, dataplata, dobandap));
        }
    }
    //////////////////  SUBIECT1  ///////////////////
    int* v = new int[n];
    int max = 0;
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        v[i] = operatii[i]->retragerebani();
        if (v[i] > max)
        {
            max = v[i];
            x = i + 1;
        }
    }
    cout << "a)" << x << endl;
    /////////////////   SUBIECT2   ////////////////////
    double sumacurenta = 0;
    for (int i = 0; i < n; i++) {
        operatii[i]->sumanoua(sumacurenta);
    }
    cout << sumacurenta;

}