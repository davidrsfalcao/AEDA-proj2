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
	unsigned int telemovel;
	string morada;
	Data last_class;



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
	string getNome() const;
	/**
	* @return retorna o Id do Utente
	*/
	unsigned int getId() const;
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
	/**
	* @brief para mostrar informacao
	*
	* @param of ostream para mostrar a informacao
	* @ return a ostream que mostra a informacao
	*/
	ostream & operator <<(ostream &of);
	/**
	*	@brief limpas as aulas de um mes
	*	@param mes mes que via ser limpo
	*/
	void limpaAulaMes(int &mes);
	/**
	*	@brief apaga uma aula
	*	@param	aula que vai ser apagada
	*/
	void ApagaAula(Aula * aula);
	/**
	*	@return retorna o telemovel do utente
	*/
	unsigned int getTelemovel() const{ return telemovel; };
	/**
	*	@return retorna a morada do utente
	*/
	string getMorada()const { return morada; };
	/**
	*	@brief define o telemovel do utente
	*   @param nr_t numero de telemovel que vai ser definido
	*/
	void setTelemovel(unsigned int nr_t) { this->telemovel = nr_t; };
	/**
	*	@brief define a morada do utente
	*   @param morada morada que vai ser definida 
	*/
	void setMorada(string morada) { this->morada = morada; };
	/**
	*	@brief define a data da ultima aula do utente
	*   @param a1 data que vai ser definida 
	*/
	void setLast_class(const Data &a1) { this->last_class = a1; };
	/**
	*	@return retorna a data da ultima aula do cliente
	*/
	Data getLast_class() const { return last_class; };



};



class Funcionario
{
	unsigned int id;
	string password;


public:
	/**
	*	@return retorna o id do funcionario
	*/
	unsigned int getId() { return id; }
	/**
	*	@return retorna a password do funcionario
	*/
	string getPassword() { return password; }


};

#endif /* UTENTE_H_ */

