#ifndef UTENTE_H_
#define UTENTE_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "aula.h"
using namespace std;


class Aula;

class Utente
{
	unsigned int Id;
	string nome;
	vector<Aula *> aulas;
	int entradas;



public:
	/**
	* @brief construtor da classe utente
	*
	*/
	Utente();
	/**
	* @brief destrutor da classe utente
	*/
	~Utente();
	/**
	* @return retorna o Nome do Utente
	*
	*/
	string getNome();
	/**
	* @return retorna o Id do Utente
	*/
	unsigned int getId();
	/**
	* @brief para mostrar um utente
	*
	* @param of ostream para mostrar o utente
	* @param Utente Utente para mostrar
	*/
	friend ostream & operator <<(std::ostream &of, const Utente &u1);
	/**
	* @return retorna o numero total de aulas em que o utente participou
	*/
	unsigned int getTotalAulas();
	/**
	* @return retorna o numero de aulas livres em que o utente participou
	*/
	unsigned int getAulasLivres();
	/**
	* @return retorna o numero de treinos em que o utente participou
	*/
	unsigned int getAulasPro();
	/**
	* @brief calcula o valor de todas as aulas não pagas pelo utente
	*
	* @return retorna o valor total a pagar pelo utente
	*/
	float totalPrice();
	/**
	* @brief calcula o valor das aulas de um mes que devem ser pagas
	*
	* @param mes Mes que o utente deve pagar
	*
	* @return retorna o valor de um determinado mes a pagar pelo utente
	*/
	float totalPriceMes(int & mes);
	/**
	* @brief Define um id para o utente
	*
	* @param id O Id que se pretende atribuir ao utente
	*/
	void setId(int id);
	/**
	* @brief Define um nome para o nome
	*
	* @param nome O nome que se pretende atribuir ao utente
	*/
	void setNome(string &nome);
	/**
	* @brief Define as aulas do utente
	*
	* @aulas Vetor com as aulas de um utente
	*/
	void setAulas(vector<Aula *> &aulas);
	/**
	* @return retorna o vetor de aulas de um utente
	*/
	vector<Aula *> getaulas();
	/**
	* @return retorna o numero de vezes que um utente teve aulas na piscina
	*/
	int getEntradas();
	/**
	* @brief Define o numero de vezes que um utente teve aulas na piscina
	*
	* @param n Numero de vezes que o utente teve aulas na piscina
	*/
	void setEntradas(int n);
	/**
	* @brief Adiciona uma aula ao vetor de aulas do cliente
	*
	* @aula A aula que se pretende adicionar
	*/
	void adicionaAula(Aula *aula);
	/**
	* @brief Mostra as aulas de um mes do utente
	*
	* @param mes Mes do qual se pretende mostrar as aulas
	*/
	void getAulasMes(int &mes);

	ostream & operator <<(ostream &of);

	void incEntradas();

	void limpaAulaMes(int &mes);

	void ApagaAula(Aula * aula);


};

#endif /* UTENTE_H_ */

