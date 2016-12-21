#include <iostream>
#include <string>
#include "BST.h"


class Loja{
	BST<Produto> produtos;
public:
	BST<Produto> getProdutos();



};

class Produto{
	string nome;
	string tamanho;
	unsigned int stock;
public:
	Produto(string &nome, string &tamanho, unsigned int &stock);
	string getNome();
	string getTamanho();
	unsigned int getStock();
	void setNome(string &nome);
	void setTamanho(string &tamanho);
	void setStock(unsigned int &stock);




};