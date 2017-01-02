#ifndef PISCINA_H_
#define PISCINA_H_

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <unordered_set>
#include <queue>


#include "aula.h"
#include"utente.h"
#include "loja.h"

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
	priority_queue<Piscina> piscinas_prox;
	Loja loja_pis;


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
	void ler_FichPiscina(string &fichPiscina, const vector<Piscina> & piscinas);
	/**
	* @brief Grava as informacoes no ficheiro da piscina
	*
	* @param fichPiscina nome do ficheiro onde se pretende guardar
	* @param piscinas vector com as varias piscinas 
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
	/**
	* @brief mostra os detelhes da aula
	*/
	void detalhes_aula();
	/**
	* @brief mostra a frequencia do utente
	*/
	void freq_Utente();
	/**
	*   @brief atribui um professor a uma aula
	*	@param a aula a ser atribuida
	*/
	void atribui_profaula(Aula *a);
	/**
	* @return retorna os utentes na piscina
	*/
	vector<Utente *> getutentes_piscina() { return utentesNaPisicina; };
	/**
	* @brief adiciona um utente a piscina
	* @param u1 utente a ser adicionado
	*/
	void add_utente_napiscina(Utente* u1) { utentesNaPisicina.push_back(u1); };
	/**
	* @brief remove um utente a piscina
	* @param u1 utente a ser removido
	*/
	void remove_utente_napiscina(Utente* u1);
	/**
	* @brief apaga uma aula
	*/
	void apaga_aulas();
	/**
	*   @brief paga a mensalidade de um utente
	*   @param u1 utente que vai pagar a sua mensalidade
	*/
	void paga_mensalidade(Utente * u1);
	/**
	*	@brief adiciona um utente a uma aula
	*	@param a aula a que vai ser adicionado o utente
	*	@param u utente a ser adicionado
	*/
	void adiciona_utente_aula(Aula *a, Utente *u);
	/**
	*   @brief ordena os professores
	*/
	void ordena_professores();
	/**
	*   @brief mostra os detalhes do professore
	*/
	void detalhes_professor();
	/**
	*   @brief ordena os utentes
	*/
	void ordena_utentes();
	/**
	*   @brief compara a proximidade de duas piscinas
	*	@param p1 piscina a ser comparada
	*	@return True se a proximidade for menos,False se não for
	*/
	bool operator <(const Piscina &p1)const;
	/**
	*	@return retorna a posicao x da piscina
	*/
	unsigned int getX() const { return x; };
	/**
	*	@return retorna a posicao y da piscina
	*/
	unsigned int getY() const { return y; };
	/**
	* @return retorna a proximidade de uma piscina
	*/
	unsigned int getProximidade()const { return proximidade; };
	/**
	*	@brief define a proximidade de uma piscina
	*   @param p proximidade a ser definida
	*/
	void setProximidade(unsigned int p) { this->proximidade = p; };
	/**
	*   @brief retira um utente dos inativos
	*   @param u1 utente a ser retirado
	*	@return retorn True se removido,False se não
	*/
	bool retira_inativo(const Utente &u1);
	/**
	*	@brief coloca utentes nos inativos
	*   @return o numero de clientes colocados
	*/
	unsigned int coloca_inativos();
	/**
	*	@return retorna as modalidades disponiveis na piscina
	*/
	vector<string> getModalidades()const;
	/**
	*	@brief define as modalidades disponiveis na piscina
	*	@param mod modalidades a ser definidas
	*/
	void setModalidades(vector<string> mod);
	/**
	*   @brief atualiza as informacoes de um cliente inativo
	*/
	void campanha_promocional();
	/**
	*	@brief define a posicao x da piscina
	*	@param x1 x a ser definido
	*/
	void setX(unsigned int x1);
	/**
	*	@brief define a posicao y da piscina
	*	@param y1 y a ser definido
	*/
	void setY(unsigned int y1);
	/**
	*	@return retorna as piscinas mais proximas
	*/
	priority_queue<Piscina> getPiscinas_prox()const { return piscinas_prox; };
	/**
	*	@brief define as piscinas mais proximas
	*	@param piscinas piscinas que vao ser definidas
	*/
	void setPiscinas_prox(const vector<Piscina> & piscinas);
	/**
	*	@param modalidade modalidade desejada pelo utente
	*	@return retorna a piscina mais proxima com a modalidade pretendida
	*/
	Piscina getMaisperto(string modalidade);
	/**
	*	@brief imprime as piscinas mais proximas
	*/
	void imprime_piscinas_prox();
	/**
	*	@return retorna os utentes inativos
	*/
	tabHU getInativos() const { return utentes_inativos; };
	/**
	*	@return retorna a loja da piscina
	*/
	Loja getLoja() const { return loja_pis; };
	/**
	*	@brief define  a loja da piscina
	*	@param lj1 loja que vai ser definida
	*/
	void setLoja(Loja lj1) { loja_pis = lj1; };

	/**
	*	@brief Define os utentes que estão na piscina
	*	@param utes vetor de utentes que está na piscina
	*/
	void setUtentesNaPiscina(vector<Utente *> utes);

};


#endif /* PISCINA_H_ */
