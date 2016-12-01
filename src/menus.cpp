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
			cout << "\t\t\t=> ";
			textcolor(WHITE);
			cout << "Escolher piscina" << endl;
			cout << "\t\t\tLista Piscinas" << endl;
			cout << "\t\t\tSobre" << endl;
			cout << "\t\t\tSair" << endl;
			tecla = opcao_valida(opcao, 1, 4);
			Sleep(100);
			break;

		case 2:
			system("cls");
			titulo();
			cabecalho();
			cout << endl << endl;

			cout << "\t\t\tEscolher piscina" << endl;
			textcolor(LIGHT_RED);
			cout << "\t\t\t=> ";
			textcolor(WHITE);
			cout << "Lista Piscinas" << endl;
			cout << "\t\t\tSobre" << endl;
			cout << "\t\t\tSair" << endl;
			tecla = opcao_valida(opcao, 1, 4);
			Sleep(100);
			break;

		case 3:
			system("cls");
			titulo();
			cabecalho();
			cout << endl << endl;

			cout << "\t\t\tEscolher piscina" << endl;
			cout << "\t\t\tLista Piscinas" << endl;
			textcolor(LIGHT_RED);
			cout << "\t\t\t=> ";
			textcolor(WHITE);
			cout << "Sobre" << endl;
			cout << "\t\t\tSair" << endl;
			tecla = opcao_valida(opcao, 1, 4);
			Sleep(300);
			break;



		case 4:
			system("cls");
			titulo();
			cabecalho();
			cout << endl << endl;

			cout << "\t\t\tEscolher piscina" << endl;
			cout << "\t\t\tLista Piscinas" << endl;
			cout << "\t\t\tSobre" << endl;
			textcolor(LIGHT_RED);
			cout << "\t\t\t=> ";
			textcolor(WHITE);
			cout << "Sair" << endl;
			tecla = opcao_valida(opcao, 1, 4);
			Sleep(300);
			break;



		}
	
	} while ((opcao != 4) || (tecla != 13));

	cout << endl << endl;
}

int main()
{
	system("TITLE PISCINA");
	menu_inicial();

	return 0;
}
