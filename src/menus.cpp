#include <iostream>

#include "uteis.h"

using namespace std;

void creditos()
{
	system("cls");
	titulo();
	cout << endl;
	cout << endl << "\t    Projeto final da cadeira 'Algoritmos e Estruturas de Dados' - AEDA " << endl << endl;
	cout << "\t    Desenvolvido por:" << endl << endl;

	cout << "\t\t\t David Falcao    -  up201506571";
	textcolor(YELLOW);
	cout << " @ ";
	textcolor(WHITE);
	cout <<"fe.up.pt" << endl;

	cout << "\t\t\t Pedro Miranda   -  up201506574";
	textcolor(YELLOW);
	cout << " @ ";
	textcolor(WHITE);
	cout << "fe.up.pt" << endl;

	cout << "\t\t\t Jose Machado    -  up201504779";
	textcolor(YELLOW);
	cout << " @ ";
	textcolor(WHITE);
	cout << "fe.up.pt" << endl;

	textcolor(RED);
	cout << endl << endl << "\t    Prima ENTER para voltar" << endl;
	textcolor(WHITE);
	
	cin.ignore();
}

void menu_inicial_ops(int opcao)
{
	int a = 254;
	char square = a; // obter 
	if (opcao == 1)
	{
		textcolor(LIGHT_RED);
		cout << "\t\t\t\t  " <<  square;
		textcolor(WHITE);
		cout << " Criar Piscina" << endl;
	}
	else cout << "\t\t\t\t    Criar Piscina" << endl;

	if (opcao == 2)
	{
		textcolor(LIGHT_RED);
		cout << "\t\t\t\t  " << square;
		textcolor(WHITE);
		cout << " Carregar Piscina" << endl;
	}
	else cout << "\t\t\t\t    Carregar Piscina" << endl;

	if (opcao == 3)
	{
		textcolor(LIGHT_RED);
		cout << "\t\t\t\t  " << square;
		textcolor(WHITE);
		cout << " Sobre" << endl;
	}
	else cout << "\t\t\t\t    Sobre" << endl;

	if (opcao == 4)
	{
		textcolor(LIGHT_RED);
		cout << "\t\t\t\t  " << square;
		textcolor(WHITE);
		cout << " Sair" << endl;
	}
	else cout << "\t\t\t\t    Sair" << endl;


}

void menu_inicial()
{
	int opcao = 1, tecla;

	do
	{
		system("cls");
		titulo();
		cout << endl  << endl;
		menu_inicial_ops(opcao);

		cout << endl << endl << endl << endl;
		cout << "\t\t\t\t\t\t\t\t" << mostrar_mes(mes_do_sistema()) << " " << ano_do_sistema();
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
			creditos();
			break;

		case 4:
			break;

		}
	
	} while ((opcao != 4) || (tecla != 13));

	cout << endl << endl;
}

int main()
{
	configurar_terminal();
	menu_inicial();

	return 0;
}
