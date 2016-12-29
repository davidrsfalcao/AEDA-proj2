#include <iostream>
#include <string>
#include "BST.h"

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
	void vende(Produto &prod);
	void repor_stock(Produto &prod);


};

