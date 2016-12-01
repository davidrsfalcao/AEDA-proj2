#include <iostream>

#include "uteis.h"

using namespace std;

void menu_inicial_ops(int opcao)
{
	if (opcao == 1)
	{
		textcolor(LIGHT_RED);
		cout << "\t\t\t\t\  => ";
		textcolor(WHITE);
		cout << "Criar Piscina" << endl;
	}
	else cout << "\t\t\t\t     Criar Piscina" << endl;

	if (opcao == 2)
	{
		textcolor(LIGHT_RED);
		cout << "\t\t\t\t  => ";
		textcolor(WHITE);
		cout << "Carregar Piscina" << endl;
	}
	else cout << "\t\t\t\t     Carregar Piscina" << endl;

	if (opcao == 3)
	{
		textcolor(LIGHT_RED);
		cout << "\t\t\t\t  => ";
		textcolor(WHITE);
		cout << "Sobre" << endl;
	}
	else cout << "\t\t\t\t     Sobre" << endl;

	if (opcao == 4)
	{
		textcolor(LIGHT_RED);
		cout << "\t\t\t\t  => ";
		textcolor(WHITE);
		cout << "Sair" << endl;
	}
	else cout << "\t\t\t\t     Sair" << endl;


}

void menu_inicial()
{
	int opcao = 1, tecla;

	do
	{
		system("cls");
		titulo();
		cout << endl << endl;
		menu_inicial_ops(opcao);

		cout << endl << endl;
		cout << "\t\t\t\t\t\t\t" << mostrar_mes(mes_do_sistema()) << " " << ano_do_sistema();
		cout << endl << endl;


		tecla = opcao_valida(opcao, 1, 4);
		Sleep(100);


		if (tecla == ENTER)
		switch (opcao)
		{
		case 1:
			cout << "\n\n EM CONSTRUCAO" << endl;
			Sleep(3000);
			break;

		case 2:
			cout << "\n\n EM CONSTRUCAO" << endl;
			Sleep(3000);
			break;

		case 3:
			cout << "\n\n EM CONSTRUCAO" << endl;
			Sleep(3000);
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
