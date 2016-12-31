#include "data.h"

using namespace std;

Data::Data()
{

}

Data::Data(unsigned int dia, unsigned int mes, unsigned int ano, unsigned int horas, unsigned int minutos)
{
	this->dia = dia;
	this->mes = mes;
	this->ano = ano;
	this->horas = horas;
	this->minutos = minutos;

	dia_semana = calculo_dia_da_semana(dia, mes, ano);

}

string Data::getDiaSemana()
{
	return dia_semana;
}

unsigned int Data::getDia()
{
	return dia;
}

unsigned int Data::getMes()
{
	return mes;
}

unsigned int Data::getAno()
{
	return ano;
}

unsigned int Data::getHoras()
{
	return horas;
}

unsigned int Data::getMinutos()
{
	return minutos;
}

void Data::setDia(unsigned int dia)
{
	this->dia=dia;
}

void Data::setMes(unsigned int mes)
{
	this->mes=mes;
}

void Data::setAno(unsigned int ano)
{
	this->ano=ano;
}

void Data::setHoras(unsigned int horas)
{
	this->horas=horas;
}

void Data::setMinutos(unsigned int minutos)
{
	this->minutos=minutos;
}

void Data::setDiaSemana(string dia_semana)
{
	this->dia_semana=dia_semana;
}

void Data::setDiaSemana()
{
	dia_semana = calculo_dia_da_semana(dia, mes, ano);
}

bool Data::operator<(Data data1)
{
	if (ano < data1.getAno())
		return true;

	if (ano > data1.getAno())
		return false;

	if (mes < data1.getMes())
		return true;

	if (mes > data1.getMes())
		return false;

	if (dia < data1.getDia())
		return true;

	if (dia > data1.getDia())
		return false;

	if (horas < data1.getHoras())
		return true;

	if (horas > data1.getHoras())
		return false;

	if (minutos < data1.getMinutos())
		return true;
	else
		return false;

}

ostream & operator <<(ostream &of, const Data &a1){

	of<<a1.ano <<"/"<< a1.mes <<"/" <<a1.dia <<"  "<< a1.horas<< ":"<<a1.minutos;


return of;
}

int Data::operator-(Data data1)
{
	int h1 = data1.getHoras();
	int h2 = horas;
	int m1 = data1.getMinutos();
	int m2 = minutos;

	int d1= (h1 * 60) + m1;
	int d2 = (horas * 60) + m2;

	return d1-d2;


}

bool Data::operator==(Data &data1)
{
	if(ano == data1.getAno() && mes == data1.getMes() && dia == data1.getDia() && horas == data1.getHoras() && minutos == data1.getMinutos())
		return true;
	else
		return false;

}

unsigned int Data::days_passed() {
	unsigned int  a = dia+mes*30+365*ano;
	unsigned int b= dia_do_sistema()+mes_do_sistema()*30+ 365*ano_do_sistema();
	unsigned difference = b-a;
		return difference;

}
