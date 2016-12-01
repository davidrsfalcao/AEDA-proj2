#include <iostream>

#include "uteis.h"

using namespace std;

void menu_inicial()
{
	int opcao = 1, tecla;

	do
	{
		switch (opcao)
		{
		case 1:
			system("cls");
			titulo();
			cabecalho();
			cout << endl << endl;
			textcolor(LIGHT_RED);
			cout << "\t=> ";
			textcolor(WHITE);
			cout << "Escolher piscina" << endl;
			cout << "\tSobre" << endl;
			cout << "\tSair" << endl;
			tecla = opcao_valida(opcao, 1, 3);
			break;

		case 2:
			system("cls");
			titulo();
			cabecalho();
			cout << endl << endl;

			cout << "\tEscolher piscina" << endl;
			textcolor(LIGHT_RED);
			cout << "\t=> ";
			textcolor(WHITE);
			cout << "Sobre" << endl;
			cout << "\tSair" << endl;
			tecla = opcao_valida(opcao, 1, 3);
			break;

		case 3:
			system("cls");
			titulo();
			cabecalho();
			cout << endl << endl;

			cout << "\tEscolher piscina" << endl;
			cout << "\tSobre" << endl;
			textcolor(LIGHT_RED);
			cout << "\t=> ";
			textcolor(WHITE);
			cout << "Sair" << endl;
			tecla = opcao_valida(opcao, 1, 3);
			break;



		}
	
	} while ((opcao != 3) || (tecla != 13));

	cout << endl << endl;
}

int main()
{
	system("TITLE PISCINA");
	menu_inicial();

	return 0;
}
