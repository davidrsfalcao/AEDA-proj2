#include "aula.h"

using namespace std;
unsigned int Aula::idloc = 0;

// AULA

Aula::Aula()
{

}

Aula::~Aula()
{
	for (size_t i = 0; i <utentes.size(); i++) {
		delete(utentes[i]);
	}
}

Aula::Aula(Data &inicio, Data & fim, int & duracao, int & NumMaximo)
{
	this->inicio = inicio;
	this->fim = fim;
	this->duracao = duracao;
	this->NumMaximo = NumMaximo;
	idloc++;
	id = idloc;

}

vector<Utente *> Aula::getUtentes()
{
	return utentes;
}

void Aula::addUtente(Utente *ut)
{
	utentes.push_back(ut);
}

void Aula::removeUtente(int i)
{
	utentes.erase(utentes.begin() + i);
}

void Aula::setProfessor(Professor *prof)
{
	this->professor = (*prof);
}

unsigned int Aula::getnumaula()
{
	return utentes.size();
}

int Aula::getDuracao()
{
	return duracao;
}

Data Aula::getFim()
{
	return fim;
}

Data Aula::getInicio()const
{
	return inicio;
}

int Aula::getNumMaximo()
{
	return NumMaximo;
}

bool Aula::operator <(const Aula &a1) {
	return inicio < a1.getInicio();
}

Professor Aula::getProfessor() {
	return professor;
}

ostream & operator <<(ostream &of, const Aula &a1) {
	of << "ID:" << a1.id << endl << a1.inicio << endl << a1.fim << endl << "Professor:" << a1.professor << endl << "Incritos na aula:" << endl;
	for (size_t i = 0; i<a1.utentes.size(); i++) {
		of << a1.utentes[i]->getNome() << endl;
	}
	return of;
}

float Aula::price() {

	return 0;
}

unsigned int Aula::getId()
{
	return id;
}

void Aula::setInicio(Data &d1)
{
	inicio = d1;
}

void Aula::setFim(Data &d1)
{
	fim = d1;
}

void Aula::setDuracao(unsigned int d)
{
	duracao = d;
}

void Aula::setNumMaximo(unsigned int max)
{
	NumMaximo = max;
}

void Aula::setId()
{
	idloc++;
	id = idloc;
}

void Aula::setId(unsigned int id) {
	this->id = id;
}


// AULA LIVRE
float AulaLivre::price()
{
	float preco = 0;
	float precofinal = 0;

	if ((inicio.getHoras() >= 17) && (inicio.getHoras() <= 21))
	{
		preco = 4;
		precofinal = (duracao / 30)*preco;
		return precofinal;

	}
	else
	{
		preco = 3.5;
		precofinal = (duracao / 30)*preco;
		return precofinal;
	}
}

bool AulaLivre::pro()
{
	return false;
}


// AULA PRO

bool AulaPro::pro()
{
	return true;
}

float AulaPro::price()
{
	float preco = 5.5;
	return preco;
}

//// POLO
unsigned int Polo::getInfo()
{
	return 0;
}

//// SINCRONIZADA
unsigned int Sincronizada::getInfo()
{
	return 1;
}

//// Mergulho
unsigned int Mergulho::getInfo()
{
	return 2;
}

//// Hidroginastica
unsigned int Hidroginastica::getInfo()
{
	return 3;
}

unsigned int Competicao::getInfo()
{
	return 4;
}


