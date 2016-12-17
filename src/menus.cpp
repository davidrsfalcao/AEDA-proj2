
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

#include "professor.h"
#include "uteis.h"
#include "aula.h"
#include "piscina.h"
#include "utente.h"
#include "data.h"


using namespace std;


//3.1 Definir nome
void nome_piscina(Piscina &p1)
{
	string nome;
	bool fim = false;
	limparEcra();
	cabecalho();

	if (p1.getNome() != "")
	{
		textcolor(LIGHT_GRAY);
		cout << " Nome atual: ";
		textcolor(WHITE);
		cout << p1.getNome() << endl << endl;
		string opcao;

		do {
			textcolor(LIGHT_GRAY);
			cout << "\n Deseja aterar? ";
			textcolor(WHITE);
			getline(cin, opcao);

		} while ((opcao != "nao") && (opcao != "n") && (opcao != "sim") && (opcao != "s"));


		if ((opcao == "nao") || (opcao == "n")) /// se nao deseja guardar
			return;
	}

	limparEcra();
	cabecalho();
	do {
		textcolor(LIGHT_GRAY);
		cout << "\n\n Nome da piscina: ";
		textcolor(WHITE);
		getline(cin, nome);

		if (nome != "")
			fim = true;
		else {
			textcolor(RED);
			cout << "\t *Campo obrigatorio!";
			textcolor(WHITE);
		}


	} while (!fim);
	

	p1.setNome(nome);



}


//3. Criar Piscina 
void menu_criar_piscina_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a; // obter  █

	int y = 0;
	int y1 = 0;

	if (opcao_b <= 5)
		 y = 9 + opcao_b;
	else y = 10 + opcao_b;
	
	if(opcao <=5)
		y1 = 9 + opcao;
	else y1 = 10 + opcao;

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

void menu_criar_piscina()
{

	int opcao = 1, opcao_b = 1, tecla;
	bool imprimir = true;
	Piscina p1;

	do
	{
		if (imprimir)
		{
			limparEcra();
			titulo();
			cout << endl << endl;
			cout << "\t\t\t\t    Definir nome" << endl;
			cout << "\t\t\t\t    Definir lotacao" << endl;
			cout << "\t\t\t\t    Definir horario" << endl;
			cout << "\t\t\t\t    Definir localizacao" << endl;
			cout << "\t\t\t\t    Definir base de dados" << endl << endl;
			cout << "\t\t\t\t    Concluir e avancar" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl << endl << endl;

		}

		imprimir = false;

		menu_criar_piscina_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 7);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				nome_piscina(p1);
				imprimir = true;
				break;

			case 2:
				break;

			case 3:
				break;

			case 4:
				break;

			case 5:
				break;

			case 6:
				break;

			case 7:
				break;
			}

	} while ((opcao != 7) || (tecla != 13));

	cout << endl << endl;


}

//2. CREDITOS
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

	cout << "\t\t\t Jose Machado    -  up201504779";
	textcolor(YELLOW);
	cout << " @ ";
	textcolor(WHITE);
	cout << "fe.up.pt" << endl;

	cout << "\t\t\t Pedro Miranda   -  up201506574";
	textcolor(YELLOW);
	cout << " @ ";
	textcolor(WHITE);
	cout << "fe.up.pt" << endl;


	textcolor(YELLOW);
	cout << endl << endl << "\t    Prima ENTER para voltar" << endl;
	textcolor(WHITE);
	
	cin.ignore();
}

// 1.MENU INICIAL
void menu_inicial_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a; // obter  █
	
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
	Piscina p1;

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
			menu_criar_piscina();
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
