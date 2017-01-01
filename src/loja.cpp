#include "loja.h"


using namespace std;

//Loja
BST<Produto> Loja::getProdutos()
{
	return produtos;
}

int Loja::vende(Produto &prod)
{
	BSTItrIn<Produto> it(produtos);
	bool existe = false;
	while (!it.isAtEnd())
	{

		if (prod == it.retrieve())
		{
			if (prod.getStock() > it.retrieve().getStock())
			{
				textcolor(RED);
				cout << "\t\tNao ha itens suficientes em stock para concluir a sua compra" << endl;
				textcolor(WHITE);
				existe = true;
				return 0;
			}
			else
			{
				unsigned int st = it.retrieve().getStock();
				st = st - prod.getStock();
				string name = it.retrieve().getNome();
				string tm = it.retrieve().getTamanho();
				Produto px(name, tm, st);
				produtos.remove(it.retrieve());
				produtos.insert(px);
				existe = true;
				return 0;

			}

		}

		it.advance();


	}

	if (!existe)
	{
		textcolor(RED);
		cout << "\t\tO produto nao existe" << endl;
		textcolor(WHITE);
		return 1;

	}


}

//Produto

Produto::Produto(string &nome, string &tamanho, unsigned int &stock)
{
	this->nome = nome;
	this->tamanho = tamanho;
	this->stock = stock;
}

Produto::Produto() {
	this->nome = "";
	this->tamanho = "";
	this->stock = 0;
}

string Produto::getNome()const
{
	return nome;
}

string Produto::getTamanho() const
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

bool Produto::operator==(const Produto &p) const
{
	if (p.getNome() == nome && p.getTamanho() == tamanho)
		return true;
	else
		return false;


}

bool Produto::operator<(const Produto & p) const
{
	if (nome == p.getNome()) {
		return tamanho < p.getTamanho();
	}

	else
		return nome < p.getNome();
}

void Loja::repor_stock(Produto &prod)
{
	bool existe = false;
	BSTItrIn<Produto> it(produtos);

	while(! (it.isAtEnd()))
	{
		if (prod == it.retrieve())
		{
			unsigned int st = it.retrieve().getStock();
			st = st + prod.getStock();
			string name = it.retrieve().getNome();
			string tm = it.retrieve().getTamanho();
			Produto px(name, tm, st);
			produtos.remove(it.retrieve());
			produtos.insert(px);
			existe = true;
		
		}
		it.advance();
	
	}

	if (!existe) 
	{
		produtos.insert(prod);
	}
	

}

void Loja::ler_FichLoja(string &fichLoja)
{
	ifstream in;
	int n = 0;
	in.open(fichLoja);
	string line, titulo;
	getline(in, titulo);
	getline(in, line);
	n = stoi(line);
	line = "";
	if (n != 0)
	{
		for (int i = 0; i < n; i++)
		{
			string nome, tamanho;
			unsigned int stock;
			getline(in, nome);
			getline(in, tamanho);
			getline(in, line);
			stock = stoi(line);
			Produto p(nome, tamanho, stock);
			produtos.insert(p);
			line = "";

		}

	}

	in.close();

}

void Loja::escrever_FichLoja(string &fichLoja)
{
	BSTItrIn<Produto> it(produtos);
	BSTItrIn<Produto> i(produtos);
	ofstream ofile(fichLoja);
	ofile << "Loja;" << endl;
	int c = 0;
	while (!it.isAtEnd()) 
	{
		c++;
		it.advance();
	}
	ofile << c << endl;
	while (!i.isAtEnd()) 
	{
		ofile << i.retrieve().getNome() << endl;
		ofile << i.retrieve().getTamanho() << endl;
		ofile << i.retrieve().getStock() << endl;
		i.advance();
	}


	ofile.close();


}

void Loja::adiciona_produto(Produto &prod)
{
	produtos.insert(prod);
}
