#include <iostream>

#include "uteis.h"

using namespace std;

void menu_inicial()
{
	int opcao = 1, tecla;

	do
	{
		system("cls");
		titulo();
		cabecalho();
		cout << endl << endl;
		
		if (opcao == 1)
		{
			textcolor(LIGHT_RED);
			cout << "\t\t\t=> ";
			textcolor(WHITE);
			cout << "Escolher piscina" << endl;
		}
		else cout << "\t\t\tEscolher piscina" << endl;

		if (opcao == 2)
		{
			textcolor(LIGHT_RED);
			cout << "\t\t\t=> ";
			textcolor(WHITE);
			cout << "Lista piscinas" << endl;
		}
		else cout << "\t\t\tLista piscinas" << endl;

		if (opcao == 3)
		{
			textcolor(LIGHT_RED);
			cout << "\t\t\t=> ";
			textcolor(WHITE);
			cout << "Sobre" << endl;
		}
		else cout << "\t\t\tSobre" << endl;

		if (opcao == 4)
		{
			textcolor(LIGHT_RED);
			cout << "\t\t\t=> ";
			textcolor(WHITE);
			cout << "Sair" << endl;
		}
		else cout << "\t\t\tSair" << endl;

		tecla = opcao_valida(opcao, 1, 4);
		Sleep(100);


		if (tecla == ENTER)
		switch (opcao)
		{
		case 1:
			break;

		case 2:
			break;

		case 3:
			break;


		case 4:
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
