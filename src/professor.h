#ifndef PROFESSOR_H_
#define PROFESSOR_H_

#include <vector>
#include <string>

using namespace std;

class Aula;

class Professor
{
protected:
string nome;
vector<Aula *> aulas;


public:
/**
 * @brief Construtor da classe professor com o nome do professor
 *
 * @param nome Nome do professor que se vai criar
 */
Professor(string nome);
/**
 * @brief Construtor da classe professor
 */
Professor();
/**
 * @brief Destrutor da classe professor
 */
~Professor();
/**
 * @brief Construtor da classe professor com o nome e as aulas dele
 *
 * @param nome Nome do Profesor que se vai criar
 * @param aulas Vetor com as aulas lecionadas pelo professor
 */
Professor(string nome, vector<Aula *> aulas);
/**
 * @return Retorna o nome do professor
 */
string getNome();
/**
 * @return Retorna o vetor com as aulas do professor
 */
vector<Aula *> getaulas();
/**
 * @brief Adiciona uma aula ao vetor de aulas do professor
 * @param aula Aula que vai ser adicionada,ou seja,que vai passar
 * a ser lecionada pelo profesor
 */
void addaula(Aula *aula);
/**
 * @brief Overload do Operador = para copiar um professor
 *
 * @param prof Professor que vai ser copiado
 */
void operator = (const Professor &prof);
/**
 * @brief Overload do Operador << para mostrar o professor
 *
 * @param of Ostream para mostrar o professor
 * @param p1 Professor que vai ser mostrado
 */
friend ostream & operator <<(ostream &of, const Professor &p1);

};

#endif /* PROFESSOR_H_ */
