#include "utente.h"


using namespace std;


Utente::Utente()
{
	entradas=0;
}

Utente::~Utente()
{
	for (size_t i=0; i <aulas.size();i++){
				delete(aulas[i]);
			}
}


string Utente::getNome()
{
	return nome;

}

unsigned int Utente::getId()
{
	return Id;

}

unsigned int Utente::getTotalAulas()
{

	return aulas.size();

}


unsigned int Utente::getAulasLivres()
{
	unsigned int n { 0 };

	for(size_t i= 0; i< aulas.size(); i++)
	{
		if(!(aulas[i]->pro()))
			n++;

	}

	return n;
}


unsigned int Utente::getAulasPro()
{
	unsigned int n { 0 };

	for(size_t i= 0; i< aulas.size(); i++)
	{
		if(aulas[i]->pro())
			n++;

	}

	return n;

}

float Utente::totalPrice()
{
	float total { };
	total=0;
	for (size_t i=0;i < aulas.size();i++)
	{
		total=total + aulas[i]->price();
	}

	return total;
}

float Utente::totalPriceMes(int & mes)
{
	float total;
	total=0;
	for(size_t n=0; n<aulas.size();n++)
	{
		if(aulas[n]->getInicio().getMes() == mes)
		{
			total=total+aulas[n]->price();

		}
	}


	return total;
}

void Utente::setId(int id)
{
	this->Id=id;
}

void Utente::setNome(string &nome)
{
	this->nome=nome;
}

void Utente::setAulas(vector<Aula *> &aulas)
{
	this->aulas=aulas;
}

vector<Aula *> Utente::getaulas(){
	return aulas;
}
int Utente::getEntradas()
{
	return entradas;
}

void Utente::setEntradas(int n)
{
	entradas=n;
}

void Utente::adicionaAula(Aula *aula)
{
	aulas.push_back(aula);
	entradas++;
}

void Utente::getAulasMes(int &mes)
{
	bool existe = false;
	cout << "Aulas Frequentadas pelo Utente: ";
	for(size_t n=0; n<aulas.size();n++)
		{
			if(aulas[n]->getInicio().getMes() == mes)
			{
				existe = true;
				if(aulas[n]->pro())
				{
					cout << aulas[n]->getInicio() <<"- Treino"<< endl;
				}
				if(!(aulas[n]->pro()))
					cout << aulas[n]->getInicio() <<"- Aula Livre" << endl;

			}
		}

	if (! existe)
		cout << "Nao ha aulas a pagar neste mes"<<endl;
}

void Utente::limpaAulaMes(int &mes)
{
	for(vector<Aula *>::iterator i = aulas.begin();i != aulas.end();i++)
	{

		if((*i)->getInicio().getMes() == mes)
		{
			i = aulas.erase(i);
			i--;

		}
	}


}





ostream & Utente::operator <<(ostream &of){
of << Id << " - " << nome << endl;
return of;
}

void Utente::ApagaAula(Aula * aula)
{
	for(size_t i=0;i<aulas.size();i++)
	{
		if(aulas[i]->getId() == aula->getId())
		{
			aulas.erase(aulas.begin()+i);
			break;
		}


	}
}






