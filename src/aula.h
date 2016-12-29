#ifndef AULA_H_
#define AULA_H_

#include <vector>
#include <iostream>
#include <string>

#include "professor.h"
#include "data.h"
#include "utente.h"

class Data;
class Professor;
class Utente;

using namespace std;

class Aula {
protected:
	Data inicio;
	Data fim;
	vector<Utente *> utentes;
	Professor professor;
	unsigned int duracao;
	unsigned int NumMaximo;
	static unsigned int idloc;
	unsigned int id;

public:
	/**
	* @brief construtor da classe aula
	*/
	Aula();
	/**
	* @brief Construtor da classe aula com parametros
	*
	* @param inicio data do Inicio da aula
	* @param fim data do Fim da aula
	* @param duracao duracao da aula
	* @param NumMaximo numero maximo de utentes da aula
	*/
	Aula(Data &inicio, Data & fim, int & duracao, int & NumMaximo);
	/**
	* @brief Destrutor da classe aula
	*/
	~Aula();
	/**
	* @return Retorna a data do Incicio de uma aula
	*/
	Data getInicio() const;
	/**
	* @return Retorna a Duracao de uma aula
	*/
	int getDuracao();
	/**
	* @return Retorna a data do fim de uma aula
	*/
	Data getFim();
	/**
	* @return retorna o numero maximo de uma aula
	*/
	int getNumMaximo();
	/**
	* @return Retorna o numero de utentes numa aula
	*/
	unsigned int getnumaula();
	/**
	* @brief diz se uma aula é livre ou de treino
	*
	* @return True se for Treino,False se Aula Livre
	*/
	virtual bool pro() { return true; }
	/**
	* @return o preço a pagar por aula
	*/
	virtual float price();
	/**
	* @brief Define um professor para a aula de treino
	*
	* @param prof Professor que se pretende atribuir
	*/
	void setProfessor(Professor *prof);
	/**
	* @return retorna um vetor com os utentes da aula
	*/
	vector<Utente *> getUtentes();
	/**
	* @brief Adiciona um utente a aula
	*
	* @param ut Utente que vai ser adicionado
	*/
	void addUtente(Utente *ut);
	/**
	* @brief remove um utente da aula
	*
	* @param i id do utente que vai ser removido
	*/
	void removeUtente(int i);
	/**
	* @return Retorna o Id do utente
	*
	*/
	unsigned int getId();
	/**
	* @brief Define um Inicio para uma aula
	*
	* @param d1 a data que vai ser definida
	*/
	void setInicio(Data &d1);
	/**
	* @brief Define um Fim para uma aula
	*
	* @param d1 a data que vai ser definida
	*/
	void setFim(Data &d1);
	/**
	* @brief Define a duracao de uma aula
	*
	* @param d duracao que vai ser definida
	*/
	void setDuracao(unsigned int d);
	/**
	* @brief Define um Numero Maximo para uma aula
	*
	* @param max o numero maximo que vai ser definido
	*/
	void setNumMaximo(unsigned int max);
	/**
	* @brief Define um id para uma aula nova
	*/
	void setId();
	/**
	* @brief Define um id para uma aula
	*
	* @param id Id que vai ser atribuido
	*/
	void setId(unsigned int id);
	/**
	* @brief para mostrar uma aula
	*
	* @param of ostream para mostrar a aula
	* @param Aula aula que vai ser mostrada
	*/
	friend ostream & operator <<(std::ostream &of, const Aula &a1);


		/*@brief operador que compara as aulas consoante a sua data de in�cio
		*
		* @param aula 1 a comparar
		* @param aula 2 a comparar
		*/
	bool operator <(const Aula &a1);

		/**
		*  @brief fun��o que retorna o professor da aula
		*
		*  @return Professor
		*/
	Professor getProfessor();

	void setIdloc(unsigned int id) { this->idloc = id; };

	virtual unsigned int getInfo() { return 0; };

};

class AulaLivre :public Aula {
public:
	/**
	* @brief Construtor da Aula Livre
	*/
	AulaLivre() :Aula() {};
	/**
	* @brief diz se uma aula é livre ou de treino
	*
	* @return True se for Treino,False se Aula Livre
	*/
	bool pro();
	/**
	* @return o preço a pagar por aula
	*/
	float price();

	unsigned int getInfo() { return 999; }
};

class AulaPro :public Aula {
public:
	/**
	* @brief Construtor da Aula de treino
	*/
	AulaPro() :Aula() {};
	/**
	* @brief diz se uma aula é livre ou de treino
	*
	* @return True se for Treino,False se Aula Livre
	*/
	bool pro();
	/**
	* @return o preço a pagar por aula
	*/
	float price();

	virtual unsigned int getInfo() { return 0; };
};


class Polo :public AulaPro {
public:
	Polo() :AulaPro() {};
	unsigned int getInfo();
};

class Sincronizada :public AulaPro {
public:
	Sincronizada() :AulaPro() {};
	unsigned int getInfo();
};

class Mergulho :public AulaPro {
public:
	Mergulho() :AulaPro() {};
	unsigned int getInfo();
};

class Hidroginastica :public AulaPro {
public:
	Hidroginastica() :AulaPro() {};
	unsigned int getInfo();
};

class Competicao :public AulaPro {
public:
	Competicao() :AulaPro() {};
	unsigned int getInfo();
};


#endif /* AULA_H_ */
