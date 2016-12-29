#ifndef DATA_H_
#define DATA_H_

#include <iostream>
#include "uteis.h"
#include <ctime>

using namespace std;

class Data {
protected:
	unsigned int dia;
	unsigned int mes;
	unsigned int ano;
	unsigned int horas;
	unsigned int minutos;
	string dia_semana;

public:
	/**
	 * @brief Construtor da classe data
	 */
	Data();
	/**
	 * @brief Construtor da classe Data com parametros
	 *
	 * @param dia Dia da data
	 * @param mes Mes da data
	 * @param ano Ano da data
	 * @param horas Horas da data
	 * @param minutos Minutos da data
	 */
	Data(unsigned int dia, unsigned int mes, unsigned int ano, unsigned int horas, unsigned int minutos);
	/**
	 * @return Retorna o dia da semana de uma determinada data
	 */
	string getDiaSemana();
	/**
	 * @return Retorna o dia de uma data
	 */
	unsigned int getDia();
	/**
	 * @return Retorna o mes de uma data
	 */
	unsigned int getMes();
	/**
	 * @return Retorna o ano de uma data
	 */
	unsigned int getAno();
	/**
	 * @return Retorna as horas de uma data
	 */
	unsigned int getHoras();
	/**
	 * @return Retorna os minutos de uma data
	 */
	unsigned int getMinutos();
	/**
	 * @brief  Define o dia de uma data
	 *
	 * @param dia Dia que se pretende definir
	 */
	void setDia(unsigned int dia);
	/**
	 * @brief Define o mes de uma data
	 * @param mes O mes que se pretende definir
	 */
	void setMes(unsigned int mes);
	/**
	 * @brief Define o ano de uma data
	 *
	 * @param ano Ano que se pretende definir
	 */
	void setAno(unsigned int ano);
	/**
	 * @brief Define as horas de uma data
	 *
	 * @param horas Horas que se pretende definir
	 */
	void setHoras(unsigned int horas);
	/**
	* @brief Define os minutos de uma data
	*
	* @param minutos Minutos que se pretende definir
	*/
	void setMinutos(unsigned int minutos);
	/**
	 * @brief Define o dia da semana de uma data
	 *
	 * @param dia_semana O Dia da semana que se pretende definir
	 */
	void setDiaSemana(string dia_semana);
	void setDiaSemana();
	/**
	 * @brief Overload do operador << para mostrar a data
	 *
	 * @param of ostream para mostrar
	 *
	 * @para a1 Data que se pretende mostrar
	 */
	friend ostream & operator <<(ostream &of, const Data &a1);

	/**
	 * @brief para comparar datas
	 *
	 * @param data1  data para ser comparada
	 */
	bool operator<(Data data1);

	int operator-(Data data1);

	bool operator==(Data &data1);

	unsigned int days_passed();
};

#endif /* DATA_H_ */

