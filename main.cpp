#include<iostream>
#include<cstring>

using namespace std;

// вашиот код
class Avtomobil{
private:
    char boja[20];
    char brend[20];
    char model[20];

    public:
    Avtomobil(){}
    Avtomobil(char *boja, char *brend, char *model)
    {
      strcpy(this->boja,boja);
      strcpy(this->brend,brend);
      strcpy(this->model,model);
    }
    Avtomobil(const Avtomobil &a)
    {
       strcpy(this->boja,a.boja);
      strcpy(this->brend,a.brend);
      strcpy(this->model,a.model);
    }
    Avtomobil & operator = (const Avtomobil &a)
    {
        if(this != &a)
        {
        strcpy(this->boja,a.boja);
        strcpy(this->brend,a.brend);
        strcpy(this->model,a.model);
        }
        return *this;
    }
    void pecati()
    {
    cout<<boja<<" "<<brend<<" "<<model<<endl;
    }
};
class ParkingPlac{
private:
    char adresa[20];
    char *id;
    int cena;
    int zarabotka;
    Avtomobil *avtomobili;
    int parkirani;
public:
    ParkingPlac()
    {
        id = new char [0];
        cena=0;
        zarabotka=0;
        avtomobili = new Avtomobil [0];
        parkirani=0;
    }
    ParkingPlac (char *adresa,char *id,int cena)
    {
        strcpy(this->adresa,adresa);
        this->cena=cena;
        this->id = new char [strlen(id)+1];
        strcpy(this->id,id);
    }
    ~ParkingPlac()
    {
        delete [] id;
        delete [] avtomobili;
    }
    ParkingPlac(const ParkingPlac & PP){
        strcpy(this->adresa, PP.adresa);
        this->id=new char [strlen(PP.id)+1];
        strcpy(this->id, PP.id);
        this->cena=PP.cena;
        this->zarabotka=PP.zarabotka;
        this->avtomobili=new Avtomobil [PP.parkirani];
        for (int i=0; i<PP.parkirani; i++)
            avtomobili[i]=PP.avtomobili[i];
        this->parkirani=PP.parkirani;
    }
    ParkingPlac & operator =(const ParkingPlac &p)
    {
        if(this != &p)
        {
            delete [] avtomobili;
            delete [] id;
            strcpy(this->adresa,p.adresa);
        this->cena=p.cena;
        this->id = new char [strlen(p.id)+1];
        strcpy(this->id,p.id);
        this->zarabotka=p.zarabotka;
        this->avtomobili= new Avtomobil [p.parkirani];
        for (int i=0; i<p.parkirani; i++)
            avtomobili[i]=p.avtomobili[i];
        this->parkirani=p.parkirani;
        }
        return *this;
    }
    void pecati()
    {
        if(zarabotka!=0)
        {
            cout<<id<<" "<<adresa<<" "<<zarabotka<<" denari"<<endl;
        }
        else
            cout<<id<<" "<<adresa<<" ";
    }
    void platiCasovi(int casovi)
    {
        zarabotka+=cena*casovi;
    }
    bool daliIstaAdresa(ParkingPlac p)
    {
        return strcmp(this->adresa,p.adresa)==0;
    }
    void parkirajVozilo(Avtomobil &novoVozilo)
    {
        Avtomobil *tmp = new Avtomobil [parkirani+1];
        for(int i=0;i<parkirani;i++)
            tmp[i]=avtomobili[i];
        tmp[parkirani++]=novoVozilo;
        delete [] avtomobili;
        avtomobili=tmp;
    }
    void pecatiParkiraniVozila()
    {
        cout<<"Vo parkingot se parkirani slednite vozila:"<<endl;
        for(int i=0;i<parkirani;i++)
        {cout<<i+1<<".";
        avtomobili[i].pecati();
        }

    }
    char *getId()
    {
        return id;
    }
};
int main(){

	ParkingPlac p[100];
	int n,m;
	char adresa[50],id[50];
	int brojcasovi,cenacas;
	cin>>n;
	if(n > 0){


		for (int i=0;i<n;i++){
	        cin.get();
			cin.getline(adresa,50);
			cin>>id>>cenacas;

			ParkingPlac edna(adresa,id,cenacas);

	        p[i]=edna;
		}

		//plakjanje
		cin>>m;
		for (int i=0;i<m;i++){

			cin>>id>>brojcasovi;

	        int findId=false;
	        for (int j=0;j<m;j++){
	            if (strcmp(p[j].getId(),id)==0){
	                p[j].platiCasovi(brojcasovi);
	                findId=true;
	            }
	        }
			if (!findId)
	        cout<<"Ne e platen parking. Greshen ID."<<endl;
		}

	    cout<<"========="<<endl;
	    ParkingPlac pCentar("Cvetan Dimov","C10",80);
		for (int i=0;i<n;i++)
	        if (p[i].daliIstaAdresa(pCentar))
	            p[i].pecati();
	} else {

		ParkingPlac najdobarPlac("Mars", "1337", 1);
	    int brVozila;
	    cin >> brVozila;
	    for(int i = 0; i < brVozila; ++i){

	    	char boja[20];
	    	char brend[20];
	    	char model[20];

	    	cin >> boja >> brend >> model;
	    	Avtomobil novAvtomobil(boja, brend, model);
	    	najdobarPlac.parkirajVozilo(novAvtomobil);
	    }
	    if(brVozila != 0)
	    najdobarPlac.pecatiParkiraniVozila();

	}
}
