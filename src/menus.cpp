
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

//3.3 Definir horario

unsigned int definir_horas(Piscina &p1, vector<string> &dias)
{
	string hora_i, hora_f;
	int horas{}, minutos{};
	char car{};
	bool avancar{ false };

	cin.ignore(256, '\n');

	for (size_t i{}; i < dias.size(); i++) {
		limparEcra();
		cabecalho();
		cout << endl << endl;
		for (size_t a{}; a < i; a++) {
			map<string, string>::iterator it = p1.horariomap.find(dias[a]);
			string horario_dia = it->second;
			cout << dias[a] << " : " << horario_dia << endl;

		}
		///hora de inicio
		do {
			cout << "\n\n " << dias[i] << ": " << endl;
			cout << "Hora de abertura (hh:mm): ";
			getline(cin, hora_i);
			stringstream ss1(hora_i);
			ss1 >> horas >> car >> minutos;

			if (hora_i.size() == 4)
				hora_i = "0" + hora_i;

			if ((horas < 0) || (horas > 24) || ((horas == 24) && (minutos > 0)) || (minutos < 0) || (minutos >= 60) || (car != ':'))
			{
				avancar = false;
				cout << "* hora invalida";
			}
			else {
				avancar = true;
			}


		} while (!avancar);

		avancar = false;
		horas = {};
		minutos = {};

		// hora de encerramento

		do {
			cout << "Hora de encerramento (hh:mm): ";
			getline(cin, hora_f);
			stringstream ss2(hora_f);
			ss2 >> horas >> car >> minutos;

			if (hora_f.size() == 4)
				hora_f = "0" + hora_f;

			if ((horas < 0) || (horas > 24) || ((horas == 24) && (minutos > 0)) || (minutos < 0) || (minutos >= 60) || (hora_f < hora_i) || (car != ':'))
			{
				avancar = false;
				cout << "* hora invalida\n";
			}
			else {
				avancar = true;
			}


		} while (!avancar);

		string h;
		h = hora_i + " - " + hora_f;
		p1.horariomap[dias[i]] = h;

	}

	return 1;
}

void editar_dias_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a; // obter  █

	int y = 0;
	int y1 = 0;

	if (opcao_b <= 7)
		y = 6 + opcao_b;
	else y = 7 + opcao_b;

	if (opcao <= 7)
		y1 = 6 + opcao;
	else y1 = 7 + opcao;

	gotoxy(9, y);
	textcolor(YELLOW);
	cout << " ";
	textcolor(WHITE);

	gotoxy(9, y1);
	textcolor(YELLOW);
	cout << square;
	textcolor(WHITE);

	gotoxy(0, 21);


}

void editar_dias(Piscina &p1, vector<string>&dias)
{
	int opcao = 1, opcao_b = 1, tecla;
	vector<string> temp = dias;
	bool imprimir = true;

	do {
		if (imprimir)
		{
		limparEcra();
		cabecalho();

		cout << "\n\n Atualmente: ";
		if (temp.size() == 0)
			cout << "sem dias de funcionamento ";
		else
		{
			temp = ordena_dias_semana(temp);
			cout << temp[0];
			for (size_t i{ 1 }; i < temp.size(); i++) {
				cout << ", " << temp[i];
			}
		}

		cout << "\n\n\t  ";
		if (encontra_string_vetor("segunda", temp) != -1)
			cout << " Retirar Segunda" << endl;
		else
			cout << " Adicionar Segunda" << endl;

		cout << "\t  ";
		if (encontra_string_vetor("terca", temp) != -1)
			cout << " Retirar Terca" << endl;
		else
			cout << " Adicionar Terca" << endl;

		cout << "\t  ";
		if (encontra_string_vetor("quarta", temp) != -1)
			cout << " Retirar Quarta" << endl;
		else
			cout << " Adicionar Quarta" << endl;

		cout << "\t  ";
		if (encontra_string_vetor("quinta", temp) != -1)
			cout << " Retirar Quinta" << endl;
		else
			cout << " Adicionar Quinta" << endl;

		cout << "\t  ";
		if (encontra_string_vetor("sexta", temp) != -1)
			cout << " Retirar Sexta" << endl;
		else
			cout << " Adicionar Sexta" << endl;

		cout << "\t  ";
		if (encontra_string_vetor("sabado", temp) != -1)
			cout << " Retirar Sabado" << endl;
		else
			cout << " Adicionar Sabado" << endl;

		cout << "\t  ";
		if (encontra_string_vetor("domingo", temp) != -1)
			cout << " Retirar Domingo" << endl << endl;
		else
			cout << " Adicionar Domingo" << endl << endl;

		cout << "\t   Concluir" << endl;
		cout << "\t   Cancelar" << endl;
	}
		imprimir = false;

		editar_dias_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 9);
		Sleep(100);

		if (tecla == ENTER)
		{
			switch (opcao) {

			case 1:
				if (encontra_string_vetor("segunda", temp) != -1)
					temp.erase(temp.begin() + encontra_string_vetor("segunda", temp));
				else
					temp.push_back("segunda");

				imprimir = true;
				break;

			case 2:
				if (encontra_string_vetor("terca", temp) != -1)
					temp.erase(temp.begin() + encontra_string_vetor("terca", temp));
				else
					temp.push_back("terca");
				imprimir = true;
				break;

			case 3:
				if (encontra_string_vetor("quarta", temp) != -1)
					temp.erase(temp.begin() + encontra_string_vetor("quarta", temp));
				else
					temp.push_back("quarta");
				imprimir = true;
				break;

			case 4:
				if (encontra_string_vetor("quinta", temp) != -1)
					temp.erase(temp.begin() + encontra_string_vetor("quinta", temp));
				else
					temp.push_back("quinta");
				imprimir = true;
				break;

			case 5:
				if (encontra_string_vetor("sexta", temp) != -1)
					temp.erase(temp.begin() + encontra_string_vetor("sexta", temp));
				else
					temp.push_back("sexta");
				imprimir = true;
				break;

			case 6:
				if (encontra_string_vetor("sabado", temp) != -1)
					temp.erase(temp.begin() + encontra_string_vetor("sabado", temp));
				else
					temp.push_back("sabado");
				imprimir = true;
				break;

			case 7:
				if (encontra_string_vetor("domingo", temp) != -1)
					temp.erase(temp.begin() + encontra_string_vetor("domingo", temp));
				else
					temp.push_back("domingo");
				imprimir = true;
				break;

			case 8:
				dias = temp; // altera os dias
				break;

			case 9:
				break;

			}
		}


	} while (((opcao != 8) && (opcao != 9)) || (tecla != ENTER));

}

void definir_dias_funcionamento_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a; // obter  █

	int y = 0;
	int y1 = 0;

	if (opcao_b <= 3)
		y = 8 + opcao_b;
	else y = 9 + opcao_b;

	if (opcao <= 3)
		y1 = 8 + opcao;
	else y1 = 9 + opcao;

	gotoxy(10, y);
	textcolor(YELLOW);
	cout << " ";
	textcolor(WHITE);

	gotoxy(10, y1);
	textcolor(YELLOW);
	cout << square;
	textcolor(WHITE);

	gotoxy(0, 21);


}

int definir_dias_funcionamento(Piscina &p1)
{
	unsigned int opcao1 = 0;
	int opcao = 1, opcao_b = 1, tecla;
	vector<string> dias;
	bool imprimir = true;
	
	do {
		tecla = 0;

		if (imprimir)
		{
			limparEcra();
			cabecalho();
			textcolor(LIGHT_GRAY);
			cout << "\n\n Atualmente: ";
			textcolor(WHITE);
			if (dias.size() == 0)
			{
				textcolor(RED);
				cout << "sem dias de funcionamento ";
				textcolor(WHITE);
			}
			else
			{
				dias = ordena_dias_semana(dias);
				cout << dias[0];
				for (size_t i{ 1 }; i < dias.size(); i++) {
					cout << ", " << dias[i];
				}
			}

			textcolor(LIGHT_GRAY);
			cout << "\n\n Dias de funcionamento:" << endl << endl;
			textcolor(WHITE);
			cout << "\t    Todos os dias" << endl;
			cout << "\t    Dias uteis" << endl;
			cout << "\t    Editar" << endl << endl;
			cout << "\t    Avancar" << endl;
			cout << "\t    Voltar atras" << endl << endl;
		}
		imprimir = false;

		definir_dias_funcionamento_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 5);

		if (tecla == ENTER)
		{
			switch (opcao) {

			case 1:
				dias = { "segunda", "terca", "quarta", "quinta", "sexta", "sabado", "domingo" };
				imprimir = true;
				break;

			case 2:
				dias = { "segunda", "terca", "quarta", "quinta", "sexta" };
				imprimir = true;
				break;

			case 3:
				editar_dias(p1, dias);
				imprimir = true;
				break;

			case 4:
				if (dias.size() == 0)
				{
					cout << "\n Defina os dias de funcionamento antes de avancar! 'Enter' para continuar";
					getchar();
					imprimir = true;
				}
				else {
					opcao1 = definir_horas(p1, dias);
					opcao = 5;

				}
				break;

			case 5:
				break;

			}
		}

	} while ((opcao != 5) || (tecla != ENTER));

	if (opcao1 == 0)
	{
		cout << "\nO horario continua por definir! 'Enter' para continuar" << endl;
		cin.ignore();
		getchar();
		return 0;
	}
	return 1;

}


//3.2 Definir lotacao
void lotacao_piscina(Piscina &p1)
{
	unsigned int lotacao;
	bool fim = false;
	int a = 254;
	char square = a; // obter  █

	if (p1.getLotacao() != NULL)
	{
		limparEcra();
		cabecalho();
		textcolor(LIGHT_GRAY);
		cout << " Lotacao atual: ";
		textcolor(WHITE);
		cout << p1.getLotacao() << endl << endl;
		
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

	do
	{
		limparEcra();
		cabecalho();
		cout << "\n Lotacao: ";
		cin >> lotacao;

		if (cin.fail())
		{
			cout << "\t *Numero invalido \n\n ";
			cin.clear();
			cin.ignore(256, '\n');
		}
		else fim = true;

	} while (!fim);

	textcolor(LIGHT_GREEN);
	cout << " " << square << " aceite"<< endl;
	textcolor(WHITE);
	Sleep(500);

	p1.setLotacao(lotacao);

}

//3.1 Definir nome
void nome_piscina(Piscina &p1)
{
	string nome;
	bool fim = false;
	int a = 254;
	char square = a; // obter  █

	if (p1.getNome() != "")
	{
		limparEcra();
		cabecalho();
		textcolor(LIGHT_GRAY);
		cout << " Nome atual: ";
		textcolor(WHITE);
		cout << p1.getNome() << endl << endl;
		string opcao;

		cin.ignore(256, '\n');
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
		cout << "\n Nome da piscina: ";
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
	
	textcolor(LIGHT_GREEN);
	cout << " " << square << " aceite" << endl;
	textcolor(WHITE);
	Sleep(500);

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
				lotacao_piscina(p1);
				imprimir = true;
				break;

			case 3:
				definir_dias_funcionamento(p1);
				imprimir = true;
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
