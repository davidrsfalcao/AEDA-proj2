#include "professor.h"

using namespace std;

Professor::Professor(string nome)
{
	this->nome=nome;

}

Professor::Professor()
{

}

Professor::~Professor(){
	for (size_t i=0; i <aulas.size();i++){
					delete(aulas[i]);
				}
}

Professor::Professor(string nome, vector<Aula *> aulas)
{
	this->nome=nome;
	this->aulas=aulas;

}

vector<Aula *> Professor::getaulas()
{
	return aulas;
}

string Professor::getNome()
{
	return nome;

}

void Professor::addaula(Aula *aula)
{
aulas.push_back(aula);
}

void Professor::operator = (const Professor &prof)
{
	this->nome=prof.nome;
	this->aulas=prof.aulas;

}

ostream & operator <<(ostream &of, const Professor &p1){
	of<< p1.nome;
	return of;
}
