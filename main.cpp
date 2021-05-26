
#include <iostream>
#include <cstring>
using namespace std;
// vashiot kod ovde
class IceCream{
private:
    char *ime=0;
    char sostav[100]={0};
    float cena=0;
    int popust=0;
public:
    IceCream()
    {
    }
    IceCream(char *ime, char sostav[],float cena)
    {
        this->ime = new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        strcpy(this->sostav,sostav);
        this->cena=cena;
    }
    IceCream(const IceCream &ic)
    {
        this->ime = new char [strlen(ic.ime)+1];
        strcpy(this->ime,ic.ime);
        strcpy(this->sostav,ic.sostav);
        this->cena=ic.cena;
        this->popust=ic.popust;
    }
    IceCream & operator = (const IceCream &ic)
    {
        delete [] ime;
        this->ime = new char [strlen(ic.ime)+1];
        strcpy(this->ime,ic.ime);
        strcpy(this->sostav,ic.sostav);
        this->cena=ic.cena;
        this->popust=ic.popust;
    }
    friend ostream & operator <<(ostream &out , const IceCream &ic)
    {
        out<<ic.ime<<" "<<ic.sostav<<" "<<ic.cena;
        float cenasopopust;
        if(ic.popust != 0)
        {cenasopopust=ic.cena-(ic.cena*ic.popust)/100;
        out<<"("<<cenasopopust<<")";
        }
        return out;
    }
    IceCream & operator ++()
    {
        popust+=5;
        return *this;
    }
    IceCream operator + (const char *extra)
    {
        char *novoime = new char [strlen(ime) + strlen(extra) +4];
        strcat(novoime,ime);
        strcat(novoime," + ");
        strcat(novoime,extra);

        IceCream res(novoime,sostav,cena+10);
        res.setDiscount(popust);
        return res;
    }
    void setDiscount(int discount)
    {
        if(discount>=0 && discount <=100)
            popust+=discount;
    }
    void setName(char *name)
    {
        delete [] ime;
        ime = new char [strlen(name)+1];
        strcpy(ime,name);
    }
    ~IceCream()
    {
        delete [] ime;
    }


};
class IceCreamShop{
private:
    char ime[50]={0};
    IceCream *sladoledi=0;
    int brojsladoledi=0;
public:
    IceCreamShop()
    {
    }
    IceCreamShop(char *ime)
    {
        strcpy(this->ime,ime);
    }
    IceCreamShop(const IceCreamShop &s)
    {
        strcpy(ime,s.ime);
        sladoledi = new IceCream [s.brojsladoledi];
        brojsladoledi=s.brojsladoledi;
    }
    ~IceCreamShop()
    {
        delete [] sladoledi;
    }
    IceCreamShop & operator +=(IceCream &i)
    {
        IceCream *tmp = new IceCream[brojsladoledi+1];
        for(int i=0;i<brojsladoledi;i++)
        {
            tmp[i]=sladoledi[i];
        }
        tmp[brojsladoledi++]=i;
        delete [] sladoledi;
        sladoledi=tmp;
        return *this;
    }
    friend ostream & operator <<(ostream &out, const IceCreamShop &ic)
    {
        out<<ic.ime<<endl;
        for(int i=0;i<ic.brojsladoledi;i++)
        {
            out<<ic.sladoledi[i];
        }
        return out;
    }

};
// zabraneto e menuvanje na main funkcijata

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
	cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}
