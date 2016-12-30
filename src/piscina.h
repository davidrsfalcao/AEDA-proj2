#ifndef PISCINA_H_
#define PISCINA_H_

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <unordered_set>


#include "aula.h"
#include"utente.h"

using namespace std;

class Utente;
class Aula;
class Professor;


struct UtentesEq {
	bool operator() (const Utente & u1, const Utente &u2)const {
		if (u1.getId() == u2.getId() && u1.getNome() == u2.getNome())
			return true;
		else
			return false;
	}
};

struct UtentesHash {
	//TODO:melhorar função de hash
	int operator() (const Utente &u1) const{
		return u1.getId();
	}
};


typedef unordered_set<Utente, UtentesHash, UtentesEq> tabHU;
typedef unordered_set<Utente, UtentesHash, UtentesEq >::iterator iteratorH;
class Piscina
{

	unsigned int NumMaximoUtentes;
	unsigned int x;
	unsigned int y;
	unsigned int proximidade;

	string nomePiscina;
	vector<Utente *> utentes;
	vector <Professor *> professores;
	vector <Aula *> horario;
	vector<Utente *> utentesNaPisicina;
	tabHU utentes_inativos;
	vector<string> modalidades;


public:
	map<string, string> horariomap;
	
	/**
	* @brief Construtor da classe piscina
	*/
	Piscina();
	/**
	* @brief Construtor da classe piscina com parametros
	*
	* @param nome Nome da piscina
	* @para NumMaximoUtentes Lotacao da piscina
	*/
	Piscina(string nome, unsigned int NumMaximoUtentes);
	/**
	* @brief Destrutor da Piscina
	*/
	~Piscina();
	/**
	* @return Retorna o vetor de utentes registados na piscina
	*/
	vector<Utente *> getUtentes();
	/**
	* @return Retorna o vetor de utentes atualmente na Piscina
	*/
	vector<Utente *> getUtentesNaPisicina();
	/**
	* @return Retorna o vetor com todas as aulas da piscina
	*/
	vector<Aula *> getHorario();
	/**
	* @return Retorna o vetor de Professores da Piscina
	*/
	vector <Professor *> getProfessores();
	/**
	* @return Retorna a lotacao da piscina
	*/
	unsigned int getNumMaximoUtententes();
	/**
	* @brief Adiciona um utente ao vetor de clientes da piscina
	*
	* @param utente Utente que se pretende adicionar
	*/
	void addUtente(Utente * utente);

	bool addAula(Aula * aula); //nao defenido
	 /**
	 * @brief Adicona um Professor ao vetor de professores da piscina
	 * @param professor Professor que se pretende adicionar
	 */
	void addProfessor(Professor *professor);
	/**
	* @brief Atribui os professores a aulas
	*/
	void atribuiprofs();
	/**
	* @brief Apaga um professor do vetor de professores
	*
	* @param professor Professor que se pretende adicionar
	*/
	bool apaga_prof(string &nome);
	/**
	* @brief apaga um utente do vetor de utentes e das aulas em que ele se encontrava inscrito
	*
	* @param utente Utente que se pretende apagar
	*/
	void apaga_Utente(string &nome);
	/**
	* @brief Define um nome para a Piscina
	*
	* @param nome O nome que se pretende atribuir
	*/
	void setNome(string nome);
	/**
	* @brief Define a lotacao da piscina
	*
	* @param lotacao Lotacao que se pretende atribuir
	*/
	void setLotacao(unsigned int lotacao);
	/**
	* @return Retorna o nome da piscina
	*/
	string getNome() const;
	/**
	* @return Retorna a lotacao da piscina
	*/
	unsigned int getLotacao();
	/**
	* @brief Carrega informacao do ficheiro para as diversas estruturas
	*
	* @param fichAulas Nome do ficheiro de aulas que se pretende ler
	*/
	void ler_FichAulas(string &fichAulas);
	/**
	* @brief atribui os clientes as suas aulas depois de ter carregado a informacao do
	* ficheiro utentes
	*
	*/
	void utentes_aulas();
	/**
	* @brief atribui os professores as suas aulas depois de ter carregado a informacao do
	* ficheiro Professor
	*/
	void professores_aulas();
	/**
	* @brief Grava no ficheiro a informacao sobre as aulas
	*
	* @param fichAulas nome de ficheiro onde se pretende guardar
	*/
	void escrever_FichAulas(string &fichAulas);
	/**
	* @brief adiciona uma aula ao horario da piscina
	*
	* @param aula Aula que se prentede adicionar
	*/
	void adicionaAula(Aula *aula);
	/**
	* @brief Carrega as informacoes do ficheiro de professores para as devidas estruturas
	*
	* @param fichProfessor Nome do ficheiro que se pretende ler
	*/
	void ler_FichProfessores(string &fichProfessor);
	/**
	* @brief Grava as informacoes no ficheiro de professores
	*
	* @param fichProfessor nome do ficheiro onde se pretende guardar
	*/
	void escrever_FichProfessores(string &fichProfessor);
	/**
	* @brief constroi o utente com base nas informacoes dadas pelo utilizador para depois
	* chamar a funcao addUtente que adiciona o utente construido
	*
	*/
	int adicionar_utente();
	/**
	* @brief Carrega as informacoes do ficheiro de utentes para as devidas estruturas
	*
	* @param fichUtente Nome do ficheiro que se pretende ler
	*/
	void ler_FichUtente(string &fichUtente);
	/**
	* @brief Grava as informacoes no ficheiro de utentes
	*
	* @param fichUtente nome do ficheiro onde se pretende guardar
	*/
	void escrever_FichUtente(string &fichUtente);
	/**
	* @brief Carrega as informacoes do ficheiro da piscina para as devidas estruturas
	*
	* @param fichPiscina Nome do ficheiro que se pretende ler
	*/
	void ler_FichPiscina(string &fichPiscina);
	/**
	* @brief Grava as informacoes no ficheiro da piscina
	*
	* @param fichPiscina nome do ficheiro onde se pretende guardar
	*/
	void escrever_FichPiscina(string &fichPiscina);
	/**
	* @brief atribui um id a um utente com base nos ids ja utilizados para outros utentes
	*/
	unsigned int atribuiID_utente();

	class NomeInvalido {
	public:string nome;
		   NomeInvalido(string n) { nome = n; };
	};
	/**
	* @brief constroi o professor com base nas informacoes dadas pelo utilizador para depois
	* chamar a funcao addProfessor que adiciona o professor construido
	*
	*/
	int adicionarProfessor();
	/**
	* @brief pergunta qual o professor que o utilizador pretende apagar para depois
	* chamar a funcao apaga_prof que apaga o professor
	*
	*/
	int apagarProfessor();
	/**
	* @brief pergunta qual o utente que o utilizador pretende apagar para depois
	* chamar a funcao apaga_Utente que apaga o utente
	*
	*/
	int apagarUtente();
	/**
	* @brief Apresenta o numero de vezes que um determinado utente teve aulas na piscina
	*/

	/**
	* @brief Pesquisa no vetor de professores se existe um dado professor
	*
	* @param nome do professor a pesquisar no vetor
	*/
	int pesquisa_professor(string nome);
	/**
	* @brief apaga a aula do vetor horário
	*
	* @param aula a apagar do vetor de aulas
	*/
	void apaga_aula(Aula *a);
	/**
	*  @brief ordena o vetor de aulas
	*
	*	@param vetor de aulas a ordenar
	*/

	void ordena_por_data();

	/**
	* @brief verfica se a aula a1 se sobrepõe a alguma outra
	*
	* @param Aula a verificar
	*
	*/
	bool aulaSobreposta(Aula *a1);

	void detalhes_aula();

	void freq_Utente();

	void atribui_profaula(Aula *a);

	vector<Utente *> getutentes_piscina() { return utentesNaPisicina; };

	void add_utente_napiscina(Utente* u1) { utentesNaPisicina.push_back(u1); };

	void remove_utente_napiscina(Utente* u1);

	void apaga_aulas();

	void paga_mensalidade(Utente * u1);

	void adiciona_utente_aula(Aula *a, Utente *u);

	void ordena_professores();

	void detalhes_professor();

	void ordena_utentes();

	bool operator <(const Piscina &p1)const;

	unsigned int getX() const { return x; };

	unsigned int getY() const { return y; };

	unsigned int getProximidade()const { return proximidade; };

	void setProximidade(unsigned int p) { this->proximidade = p; };

	bool retira_inativo(const Utente &u1);

	unsigned int coloca_inativos();

	vector<string> getModalidades()const;

	void setModalidades(vector<string> mod);
	
	void campanha_promocional();

	void setX(unsigned int x1);

	void setY(unsigned int y1);

};


#endif /* PISCINA_H_ */
