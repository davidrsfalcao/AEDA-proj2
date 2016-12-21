#include "loja.h"

using namespace std;

//Loja
BST<Produto> Loja::getProdutos()
{
	return produtos;
}

//Produto

Produto::Produto(string &nome,string &tamanho,unsigned int &stock)
{
	this->nome = nome;
	this->tamanho = tamanho;
	this->stock = stock;
}

string Produto::getNome()
{
	return nome;
}
string Produto::getTamanho()
{
	return tamanho;
}
unsigned int Produto::getStock()
{
	return stock;
}
void Produto::setNome(string &nome)
{
	this->nome = nome;
}
void Produto::setTamanho(string &tamanho)
{
	this->tamanho = tamanho;
}
void Produto::setStock(unsigned int &stock)
{
	this->stock = stock;
}

