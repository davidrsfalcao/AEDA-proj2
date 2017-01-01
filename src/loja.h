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
	Produto();
	Produto(string &nome, string &tamanho, unsigned int &stock);
	string getNome() const;
	string getTamanho()const;
	unsigned int getStock();
	void setNome(string &nome);
	void setTamanho(string &tamanho);
	void setStock(unsigned int &stock);
	bool operator == (const Produto &p) const;
	bool operator<(const Produto &p)const;





};
class Loja {
	BST<Produto> produtos;
public:
	Loja() :produtos(Produto()) {};
	BST<Produto> getProdutos();
	int vende(Produto &prod);
	void repor_stock(Produto &prod);
	void ler_FichLoja(string &fichLoja);
	void escrever_FichLoja(string &fichLoja);
	void adiciona_produto(Produto &prod);


};

