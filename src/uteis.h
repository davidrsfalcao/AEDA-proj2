#ifndef UTEIS_H_
#define UTEIS_H_

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <windows.h>

/**
 * @brief verifica se uma data existe
 *
 * @param dia Dia da Data
 * @param mes Mes da Data
 * @param ano Ano da Data
 *
 * @return True se o dia existe,False se não existir
 */
bool dia_existe(int dia, int mes, int ano);
/**
 * @return Retorna as horas do sistema
 */
int horas_do_sistema();
/**
 * @return Retorna os minutos do sistema
 */
int minutos_do_sistema();
/**
 * @return Retorna o dia do sistema
 */
int dia_do_sistema();
/**
 * @return Retorna o mes do sistema
 *
 */
int mes_do_sistema();
/**
 * @brief Passa um mes de numerico a escrito,como 1->janeiro
 *
 * @param mes Mes que se quer transformar
 * @return O mes transformado
 */
std::string mostrar_mes(unsigned int mes);
/**
 * @return retorna o Ano do Sistema
 */
int ano_do_sistema();
/**
 * @brief Limpa a tela onde se está a aparesentar o programa
 */
void limparEcra();
/**
 *
 * @brief le se a opcao esta entre os valores possiveis
 *
 * @param min Opcao minima
 * @param max Opcao maxima
 *
 * @return a opcao depois de analisada
 */
unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max);
/**
 * @brief Elimina os espaços antes e depois numa string
 *
 * @param str String que se pretende formatar
 *
 * @return Retorna a string ja sem os espaços
 */
std::string delete_space(std::string str);
/**
 * @brief Cria grafico para ilustrar melhor algumas situacoes
 *
 * @param n1 numero da primeira variavel
 * @param nome1 nome da primeira variavel
 * @param n2 numero da primeira variavel
 * @param nome2 nome da primeira variavel
 * @param variavel tipo de variavel
 */
void faz_grafico(double n1, std::string nome1, double n2, std::string nome2,
		std::string variavel);
/**
 * @brief Calcula que dia da semana corresponde a uma data
 *
 * @param dia Dia da Data
 * @param mes Mes da Data
 * @param ano Ano da Data
 *
 * @return Retorna o dia da semana
 */
std::string calculo_dia_da_semana(int dia, int mes, int ano);
/**
 * @brief Mostra a data atual
 */
void cabecalho();
/**
 * @brief Algoritmo de pesquisa de uma palavra num vetor
 *
 * @param palavra A palavra que se pretende encontrar
 * @param v1 Vetor onde se vai procurar
 *
 * @return Retorn a posicao da palavra no vetor se encontrar ou -1 se nao encontrar
 */
unsigned int encontra_string_vetor(std::string palavra,
		std::vector<std::string> v1);
/**
 * @brief Ordena os dias duma semana contidos num vetor
 *
 * @param v1 Vetor com os dias para ordenar
 *
 * @return Retorna o vetor ja ordenado
 */
std::vector<std::string> ordena_dias_semana(std::vector<std::string> v1);

/**
 * @brief Algoritmo de Ordenacao de um vetor
 *
 * @param v Vetor que se vai ordenar
 *
 */

int opcao_valida(int &opcao, int min, int max);

enum DOS_COLORS
{
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
	LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
	LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE
};

void textcolor(DOS_COLORS iColor);


#endif /* UTEIS_H_ */
