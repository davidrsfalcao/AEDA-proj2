#include <iostream>
#include <string>
#include <fstream>
#include "BST.h"
#include "uteis.h"

using namespace std;
class Produto {
	string nome;
	string tamanho;
	unsigned int stock;
public:
	/**
	* @brief construtor da classe Produto
	*/
	Produto();
	/**
	* @brief construtor da classe Produto com parametros
	* @param nome nome do produto
	* @param tamanho tamanho do produto
	* @param stock numero pecas de um produto
	*/
	Produto(string &nome, string &tamanho, unsigned int &stock);
	/**
	*	@return retorn o nome do produto
	*/
	string getNome() const;
	/**
	*	@return retorn o tamanho do produto
	*/
	string getTamanho()const;
	/**
	*	@return retorn o stock do produto
	*/
	unsigned int getStock();
	/**
	*	@brief define um nome para o produto
	*	@param nome nome do produto
	*/
	void setNome(string &nome);
	/**
	*	@brief define o tamanho do produto
	*   @param tamanho tamanho do produto
	*/
	void setTamanho(string &tamanho);
	/**
	*	@brief define o stock do produto
	*   @param stock do produto
	*/
	void setStock(unsigned int &stock);
	/**
	*	@brief compara se dois produtos são iguais analisando o seu nome e tamanho
	*	@param p produto a ser comparado
	*	@return True se forem iguais,False se nao forem
	*/
	bool operator == (const Produto &p) const;
	/**
	*	@brief funcao utilizada pela BST para comparar produtos e organiza-los
	*	@param p produto a ser comparado
	*	@return retorna True se um produto for menor que outro,False se não 
	*/
	bool operator<(const Produto &p)const;





};
class Loja {
	BST<Produto> produtos;
public:
	/**
	* @brief construtor da classe Loja
	*/
	Loja() :produtos(Produto()) {};
	/**
	* @return retorn a BST com os produtos
	*/
	BST<Produto> getProdutos();
	/**
	* @brief funcao que vende um produto da loja
	* @param prod produto que vai ser vendido ao cliente
	* @return 0 se a venda for bem sucedida,1 se nao
	*/
	int vende(Produto &prod);
	/**
	*	@brief funcao que compra ao fornecedor um produto 
	*	@param prod produto a ser comprado ao fornecedor
	*/
	void repor_stock(Produto &prod);
	/**
	*	@brief funcao que le o ficheiro e passa a informacao para a BST
	*	@param fichLoja ficheiro a ser lido
	*/
	void ler_FichLoja(string &fichLoja);
	/**
	*	@brief funcao que escreve no ficheiro a informacao da BST
	*	@param fichLoja ficheiro onde vai ser escrita a informacao
	*/
	void escrever_FichLoja(string &fichLoja);
	/**
	*	@brief adiciona um novo produto a loja
	*	@param prod produto a ser adicionado
	*/
	void adiciona_produto(Produto &prod);


};

