#include <iostream>
#include <windows.h>

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

	textcolor(YELLOW);
	cout << endl << endl << "\t    Prima ENTER para voltar" << endl;
	textcolor(WHITE);
	
	cin.ignore();
}


// MENU INICIAL
void menu_inicial_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a; // obter 
	
	int y = 9 + opcao_b;
	int y1 = 9 + opcao;

	gotoxy(34, y);
	textcolor(YELLOW);
	cout << " ";
	textcolor(WHITE);

	gotoxy(34, y1);
	textcolor(YELLOW);
	cout << square;
	textcolor(WHITE);

	

	gotoxy(0, 21);
}

void menu_inicial()
{
	int opcao = 1, opcao_b = 1, tecla;
	bool imprimir = true;

	do
	{
		if (imprimir)
		{
			limparEcra();
			titulo();
			cout << endl << endl;
			cout << "\t\t\t\t    Criar Piscina" << endl;
			cout << "\t\t\t\t    Carregar Piscina" << endl;
			cout << "\t\t\t\t    Sobre" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl << endl << endl;
			cout << "\t\t\t\t\t\t\t\t" << mostrar_mes(mes_do_sistema()) << " " << ano_do_sistema();
			cout << endl << endl;
		
		}

		imprimir = false;

		menu_inicial_ops(opcao,opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 4);
		Sleep(100);


		if (tecla == ENTER)
		switch (opcao)
		{
		case 1:
			cout << "\n\n EM CONSTRUCAO" << endl;
			Sleep(3000);
			imprimir = true;
			break;

		case 2:
			cout << "\n\n EM CONSTRUCAO" << endl;
			Sleep(3000);
			imprimir = true;
			break;

		case 3:
			creditos();
			imprimir = true;
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
