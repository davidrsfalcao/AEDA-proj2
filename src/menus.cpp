#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <queue>
#include <cmath>

#include "professor.h"
#include "uteis.h"
#include "aula.h"
#include "piscina.h"
#include "utente.h"
#include "data.h"


using namespace std;

// @@@ funções atualização
void atualizar_aulas_piscina(Piscina &p1)
{
	string dia_S;
	int dia = dia_do_sistema();
	int mes = mes_do_sistema();
	int ano = ano_do_sistema();
	dia_S = calculo_dia_da_semana(dia, mes, ano);
	vector<string> mod = p1.getModalidades();
	unsigned int n_mod = mod.size();

	for (size_t i{}; i < 7; i++) {
		dia_S = calculo_dia_da_semana(dia, mes, ano);

		map<string, string>::iterator it = p1.horariomap.find(dia_S);
		if (it != p1.horariomap.end())
		{
			string temp = it->second;
			int hora_i = stoi(temp.substr(0, 2));
			int min_i = stoi(temp.substr(3, 2));
			int hora_f = stoi(temp.substr(8, 2));
			int min_f = stoi(temp.substr(11, 2));
			int hora{ hora_i };
			int minutos{ min_i };


			do {
				// inicio aula

				Aula *a1;

				int i = rand() % n_mod;

				if (mod[i] == "polo")
					a1 = new Polo();
				else if (mod[i] == "sincronizada")
					a1 = new Sincronizada();
				else if (mod[i] == "mergulho")
					a1 = new Mergulho();
				else if (mod[i] == "hidroginastica")
					a1 = new Hidroginastica();
				else if (mod[i] == "competicao")
					a1 = new Competicao();
				else return;

				Data d_ini{};
				d_ini.setAno(ano);
				d_ini.setMes(mes);
				d_ini.setDia(dia);
				d_ini.setDiaSemana(dia_S);
				d_ini.setHoras(hora);
				d_ini.setMinutos(minutos);
				a1->setInicio(d_ini);

				//fim aula
				hora++;
				Data d_fim{};
				d_fim.setAno(ano);
				d_fim.setMes(mes);
				d_fim.setDia(dia);
				d_fim.setDiaSemana(dia_S);
				d_fim.setHoras(hora);
				d_fim.setMinutos(minutos);

				a1->setFim(d_fim);
				a1->setId();
				a1->setDuracao(60);


				a1->setNumMaximo(p1.getLotacao());

				if (!p1.aulaSobreposta(a1)) {
					p1.adicionaAula(a1);
					p1.atribui_profaula(a1);
				}

			} while ((hora < (hora_f - 1)) || ((hora == (hora_f - 1) && (minutos <= min_f)))); // fim while

		}

		dia++;
		if (!dia_existe(dia, mes, ano)) {
			dia = 1;
			mes++;
		}
		if (!dia_existe(dia, mes, ano)) {
			dia = 1;
			mes = 1;
			ano++;
		}

	} // fim ciclo for

	p1.ordena_por_data();
}

void apagar_aulas_old(Piscina &p1)
{
	string dia_S;
	int dia = dia_do_sistema();
	int mes = mes_do_sistema();
	int ano = ano_do_sistema();
	dia_S = calculo_dia_da_semana(dia, mes, ano);
	int horas = horas_do_sistema();
	int min = minutos_do_sistema();

	Data atual(dia, mes, ano, horas, min);
	atual.setDiaSemana(dia_S);

	for (size_t k = 0; k< p1.getHorario().size(); k++)
	{
		if (p1.getHorario()[k]->getFim() < atual)
		{
			p1.apaga_aula(p1.getHorario()[k]);
			k--;
		}
	}


}

void atualizar_utentes_piscina(Piscina &p1)
{
	vector<Utente *> temp;

	Data atual{};
	int dia = dia_do_sistema();
	int mes = mes_do_sistema();
	int ano = ano_do_sistema();
	string dia_S = calculo_dia_da_semana(dia, mes, ano);
	int horas = horas_do_sistema();
	int minutos = minutos_do_sistema();

	atual.setAno(ano);
	atual.setMes(mes);
	atual.setDia(dia);
	atual.setHoras(horas);
	atual.setMinutos(minutos);
	atual.setDiaSemana(dia_S);

	while (p1.getutentes_piscina().size() != 0)
	{
		p1.remove_utente_napiscina(p1.getutentes_piscina()[0]);
	}

	for (size_t i{}; i < p1.getHorario().size(); i++) {
		if ((p1.getHorario()[i]->getInicio() < atual) && (atual < p1.getHorario()[i]->getFim())) {
			for (size_t in = 0; in < p1.getHorario()[i]->getUtentes().size(); in++)
			{
				temp.push_back(p1.getHorario()[i]->getUtentes()[in]);
			}

		}
	}

	for (size_t i = 0; i < temp.size(); i++)
	{
		p1.add_utente_napiscina(temp[i]);

	}

}

void set_prioridades(vector<Piscina> &piscinas, Piscina &piscina_criada) {
	vector<Piscina > temp = piscinas;
	float distmin = 100000000;
	float dist = 0;
	unsigned int id = 0;
	unsigned int c = 0;
	for (size_t i = 0; i < temp.size(); i++) {


		for (size_t j = 0; j < temp.size(); i++) {
			dist = sqrt(pow(piscina_criada.getX() - temp[j].getX(), 2) + pow(piscina_criada.getY() - temp[j].getY(), 2));
			if (dist < distmin) {
				dist = distmin;
				id = j;
			}
		}
		piscinas[id].setProximidade(c++);
		temp.erase(temp.begin() + id);

	}

}

vector<Piscina> carregar_piscinas() {
	vector<Piscina> v;
	return v;
}


// 7.2 Increver aulas
void entrar_piscina_livre(Piscina &p1, Utente *ut1)
{
	limparEcra();
	cabecalho();
	cout << endl << endl;

	Data atual{};
	Data fim{};
	int dia = dia_do_sistema();
	int mes = mes_do_sistema();
	int ano = ano_do_sistema();
	string dia_S = calculo_dia_da_semana(dia, mes, ano);
	int horas = horas_do_sistema();
	int minutos = minutos_do_sistema();

	atual.setAno(ano);
	atual.setMes(mes);
	atual.setDia(dia);
	atual.setHoras(horas);
	atual.setMinutos(minutos);
	atual.setDiaSemana(dia_S);

	bool existe{ false };

	for (size_t i{}; i < p1.getHorario().size(); i++) {
		if ((p1.getHorario()[i]->getInicio() < atual)
			&& (atual < p1.getHorario()[i]->getFim())) {
			existe = true;
			break;

		}

	} // fim ciclo for

	if (!existe) {
		textcolor(RED);
		cout << "\n\t\t Atualmente a piscina encontra-se fechada! 'Enter' para continuar ";
		cout << endl;
		textcolor(WHITE);
		cin.ignore(256, '\n');
		return;
		

	}
	else {

		Aula *nova = new AulaLivre();

		nova->addUtente(ut1);
		nova->setId();
		nova->setInicio(atual);

		string hora_f;
		char car;
		bool avancar;

		int horas1, min1;

		do
		{
			textcolor(LIGHT_GRAY);
			cout << "\t\t Hora de saida: (hh:mm) ";
			textcolor(WHITE);
			getline(cin, hora_f);
			stringstream ss1(hora_f);
			ss1 >> horas1 >> car >> min1;

			if (hora_f.size() == 4)
				hora_f = "0" + hora_f;

			if ((horas1 < horas) || (horas1 > 24) || ((horas1 == 24) && (min1 > 0)) || (min1 < 0) || (min1 >= 60) || (car != ':')) {
				avancar = false;
				textcolor(RED);
				cout << "\t\t* hora invalida";
				textcolor(WHITE);
			}
			else
			{
				if ((horas1 > (horas + 2)) || ((horas1 == (horas + 2)) && (min1 > minutos)))
				{
					textcolor(RED);
					cout << "\t\t* a duracao maxima e de 120 minutos \n\n";
					textcolor(WHITE);
				}
				else {
					avancar = true;
				}
			}
		} while (!avancar);

		int duracao;
		duracao = (horas1 - horas) * 60 + (min1 - minutos);

		fim.setAno(ano);
		fim.setMes(mes);
		fim.setDiaSemana(dia_S);
		fim.setDia(dia);
		fim.setHoras(horas1);
		fim.setMinutos(min1);
		nova->setFim(fim);

		p1.adicionaAula(nova);
		p1.retira_inativo(*ut1);
		(*ut1).adicionaAula(nova);
		p1.add_utente_napiscina(ut1);
	}

	textcolor(CYAN);
	cout << "\n\n\t\t Sucesso! Prima 'ENTER' para voltar \n\n ";
	textcolor(WHITE);
	cin.ignore(256, '\n');
}

void escolher_modalidade_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

	int y = 4 + opcao_b;
	int y1 = 4 + opcao;

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

string escolher_modalidade()
{
	limparEcra();
	cabecalho();
	cout << endl << endl;

	int opcao_a = 1, opcao_b = 1, tecla;
	bool imprimir = true;

	do
	{
		if (imprimir)
		{
			limparEcra();
			cabecalho();

			cout << endl << endl;
			cout << "\t\t\t\t    Polo" << endl;
			cout << "\t\t\t\t    Natacao Sincronizada" << endl;
			cout << "\t\t\t\t    Mergulho" << endl;
			cout << "\t\t\t\t    Hidroginastica" << endl;
			cout << "\t\t\t\t    Competicao" << endl;
			cout << "\t\t\t\t    Aula livre" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl;

		}

		imprimir = false;

		escolher_modalidade_ops(opcao_a, opcao_b);
		opcao_b = opcao_a;
		tecla = opcao_valida(opcao_a, 1, 7);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao_a)
			{
			case 1:
				return "polo";
				break;

			case 2:
				return "sincronizada";
				break;

			case 3:
				return "mergulho";
				break;

			case 4:
				return "hidroginastica";
				break;

			case 5:
				return "competicao";
				break;

			case 6:
				return "livre";
				break;

			case 7:
				return "exit";
				break;

			}

	} while (tecla != ENTER);


}

void inscrever_aula(Piscina &p1, Utente * ute)
{
	string escolha = escolher_modalidade();
	int ind;
	int existe;
	vector<Aula *> aulas;

	if (escolha != "livre")
		existe = encontra_string_vetor(escolha, p1.getModalidades());
	else existe = 1;

	if (existe != -1)
	{
		if (escolha == "exit")
			return;
		else if (escolha == "polo")
			ind = 0;
		else if (escolha == "sincronizada")
			ind = 1;
		else if (escolha == "mergulho")
			ind = 2;
		else if (escolha == "hidroginastica")
			ind = 3;
		else if (escolha == "competicao")
			ind = 4;
		else if (escolha == "livre")
		{
			entrar_piscina_livre(p1, ute);
			return;
		}
		else return;

		for (size_t i = 0; i < p1.getHorario().size(); i++)
		{
			if (p1.getHorario()[i]->getInfo() == ind)
				aulas.push_back(p1.getHorario()[i]);

		}

		int opcao = 1;
		int tecla = 0;
		int imax = aulas.size();
		int opcaomax = ((imax - 1) / 2) + 1;
		int cima = 0;
		int cima_b = 0;
		size_t i;


			while (1)
			{
				limparEcra();
				cabecalho();
				textcolor(LIGHT_GRAY);
				cout << "\t\tAulas disponiveis (" << imax << ")" << endl;
				textcolor(WHITE);
				cout << endl;

				for (i = (opcao - 1) * 2; ((i < opcao * 2) && (i < imax)); i++)
				{
					textcolor(LIGHT_GRAY);
					cout << "\t\tId aula: ";
					textcolor(WHITE);

					cout << aulas[i]->getId() << endl;

					textcolor(LIGHT_GRAY);
					cout << "\t\tData: ";
					textcolor(WHITE);

					cout << aulas[i]->getInicio().getDiaSemana() << ", ";

					cout << aulas[i]->getInicio().getDia() << " de ";
					cout << mostrar_mes(aulas[i]->getInicio().getMes()) << " de ";
					cout << aulas[i]->getInicio().getAno() << endl;

					textcolor(LIGHT_GRAY);
					cout << "\t\tHora: ";
					textcolor(WHITE);

					if (aulas[i]->getInicio().getHoras() < 10)
						cout << "0" << aulas[i]->getInicio().getHoras();
					else
						cout << aulas[i]->getInicio().getHoras();

					cout << ":";
					if (aulas[i]->getInicio().getMinutos() < 10)
						cout << "0" << aulas[i]->getInicio().getMinutos();
					else
						cout << aulas[i]->getInicio().getMinutos();


					cout << " - ";

					if (aulas[i]->getFim().getHoras() < 10)
						cout << "0" << aulas[i]->getFim().getHoras();
					else
						cout << aulas[i]->getFim().getHoras();

					cout << ":";
					if (aulas[i]->getFim().getMinutos() < 10)
						cout << "0" << aulas[i]->getFim().getMinutos() << endl;
					else
						cout << aulas[i]->getFim().getMinutos() << endl;

					textcolor(LIGHT_GRAY);
					cout << "\t\tTipo: ";
					textcolor(WHITE);

					if (aulas[i]->pro())
					{
						int modo = aulas[i]->getInfo();

						switch (modo)
						{
						case 0:
							cout << "Polo";
							break;

						case 1:
							cout << "Sincronizada";
							break;

						case 2:
							cout << "Mergulho";
							break;

						case 3:
							cout << "Hidroginastica";
							break;

						case 4:
							cout << "Competicao";
							break;

						}

					}

					cout << endl << endl;
					textcolor(WHITE);

				}

				cout << "\t\t\t\t";

				gotoxy(37, 15);
				textcolor(YELLOW);
				cout << "<<";
				textcolor(WHITE);


				cout << " Pagina " << opcao;

				textcolor(YELLOW);
				cout << " >>";
				textcolor(WHITE);

				cout << "\n\n\t\t Prime 'ENTER' para escolher " << endl;

				tecla = opcao_valida_listas(opcao, 1, opcaomax);


				if (tecla == ENTER)
					break;

			}

			unsigned int id;
			bool encontrou = false;

			while (1)
			{
				textcolor(LIGHT_GRAY);
				cout << "\t\tID: ";
				textcolor(WHITE);
				cin >> id;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(256, '\n');
					textcolor(RED);
					cout << "\t\t id invalido" << endl << endl;
					textcolor(WHITE);
				}
				else
				{
					for (size_t k = 0; k < p1.getHorario().size(); k++)
					{
						if (p1.getHorario()[k]->getId() == id)
						{
							p1.adiciona_utente_aula(p1.getHorario()[k], ute);
							ute->adicionaAula(p1.getHorario()[k]);
							p1.add_utente_napiscina(ute);
							p1.retira_inativo(*ute);
							encontrou = true;
							break;
						}

					}

					if (encontrou)
					{
						textcolor(CYAN);
						cout << "\n\t\tUtente inscrito com sucesso. 'ENTER' para continuar" << endl;
						textcolor(WHITE);

						break;

					}
					else {
						textcolor(RED);
						cout << "\t\t id nao existente" << endl << endl;
						textcolor(WHITE);
					}

				}

			}


	}
	else {
		limparEcra();
		cabecalho();

		cout << endl << endl;
		textcolor(RED);
		cout << "\t\t Modalidade inexistente nesta piscina." << endl << endl;
		textcolor(WHITE);

		cout << "\t\t Podera dirigir-se a " << p1.getMaisperto(escolha).getNome();

		cout << endl << endl;
		textcolor(CYAN);
		cout << "\t\t Prima 'ENTER' para sair" << endl << endl;
		textcolor(WHITE);

	}

}


// 7.1.2 Aulas frequentadas
void aulas_frequentadas(Utente &ute)
{

	int opcao = 1;
	int tecla = 0;
	int imax = ute.getaulas().size();
	int opcaomax = ((imax - 1) / 3) + 1;
	size_t i;

	while (1)
	{
		limparEcra();
		cabecalho();
		cout << endl << endl;

		for (i = (opcao - 1) * 3; ((i < opcao * 3) && (i < imax)); i++)
		{
			textcolor(LIGHT_GRAY);
			cout << "\t\tId aula: ";
			textcolor(WHITE);

			cout << ute.getaulas()[i]->getId() << endl;

			textcolor(LIGHT_GRAY);
			cout << "\t\tData: ";
			textcolor(WHITE);

			cout << ute.getaulas()[i]->getInicio().getDiaSemana() << ", ";

			cout << ute.getaulas()[i]->getInicio().getDia() << " de ";
			cout << mostrar_mes(ute.getaulas()[i]->getInicio().getMes()) << " de ";
			cout << ute.getaulas()[i]->getInicio().getAno() << endl;

			textcolor(LIGHT_GRAY);
			cout << "\t\tHora: ";
			textcolor(WHITE);

			if (ute.getaulas()[i]->getInicio().getHoras() < 10)
				cout << "0" << ute.getaulas()[i]->getInicio().getHoras();
			else
				cout << ute.getaulas()[i]->getInicio().getHoras();

			cout << ":";
			if (ute.getaulas()[i]->getInicio().getMinutos() < 10)
				cout << "0" << ute.getaulas()[i]->getInicio().getMinutos();
			else
				cout << ute.getaulas()[i]->getInicio().getMinutos();


			cout << " - ";

			if (ute.getaulas()[i]->getFim().getHoras() < 10)
				cout << "0" << ute.getaulas()[i]->getFim().getHoras();
			else
				cout << ute.getaulas()[i]->getFim().getHoras();

			cout << ":";
			if (ute.getaulas()[i]->getFim().getMinutos() < 10)
				cout << "0" << ute.getaulas()[i]->getFim().getMinutos() << endl;
			else
				cout << ute.getaulas()[i]->getFim().getMinutos() << endl;

			textcolor(LIGHT_GRAY);
			cout << "\t\tTipo: ";
			textcolor(WHITE);

			if (ute.getaulas()[i]->pro())
			{
				int modo = ute.getaulas()[i]->getInfo();

				switch (modo)
				{
				case 0:
					cout << "Polo";
					break;

				case 1:
					cout << "Sincronizada";
					break;

				case 2:
					cout << "Mergulho";
					break;

				case 3:
					cout << "Hidroginastica";
					break;

				case 4:
					cout << "Competicao";
					break;

				}

			}

			cout << endl << endl;
			textcolor(WHITE);

		}

		cout << "\t\t\t\t";

		gotoxy(37, 20);
		textcolor(YELLOW);
		cout << "<<";
		textcolor(WHITE);


		cout << " Pagina " << opcao;

		textcolor(YELLOW);
		cout << " >>";
		textcolor(WHITE);

		textcolor(CYAN);
		cout << "\n\n\n Prima 'ENTER' para sair \n";
		textcolor(WHITE);

		tecla = opcao_valida_listas(opcao, 1, opcaomax);
		if (tecla == ENTER)
			break;
	}


}


// 7.1.1 Detalhes cliente
void detalhes_cliente(Utente &ute)
{
	limparEcra();
	cabecalho();

	textcolor(LIGHT_GRAY);
	cout << "\t\t Nome: ";
	textcolor(WHITE);
	cout << ute.getNome() << endl;


	textcolor(LIGHT_GRAY);
	cout << "\t\t Morada: ";
	textcolor(WHITE);
	cout << ute.getMorada() << endl;

	textcolor(LIGHT_GRAY);
	cout << "\t\t Telemovel: ";
	textcolor(WHITE);
	cout << ute.getTelemovel() << endl;

	textcolor(LIGHT_GRAY);
	cout << "\t\t Ultima aula: ";
	textcolor(WHITE);

	Data d1 =ute.getLast_class();
	cout << d1.getDia() << "/" << d1.getMes() << "/" << d1.getAno() << endl;

	textcolor(LIGHT_GRAY);
	cout << "\t\t Total aulas: ";
	textcolor(WHITE);
	cout << ute.getEntradas() << endl;


	cout << endl << endl;

	textcolor(CYAN);
	cout << "\t\t Prima 'ENTER' para voltar";
	textcolor(WHITE);
	cin.ignore(256, '\n');

}


// 7.1 Gerir registros
void menu_registros_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

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

void menu_registros(Piscina &p1, Utente &ute)
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
			cout << "\t\t\t\t    Informacoes pessoais" << endl;
			cout << "\t\t\t\t    Aulas por pagar" << endl;
			cout << "\t\t\t\t    Pagar mensalidade" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl << endl << endl;
			cout << endl << endl;

		}

		imprimir = false;

		menu_registros_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 4);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				detalhes_cliente(ute);
				imprimir = true;
				break;

			case 2:
				aulas_frequentadas(ute);
				imprimir = true;
				break;

			case 3:
				p1.paga_mensalidade(&ute);
				imprimir = true;
				break;

			case 4:
				break;

			}

	} while ((opcao != 4) || (tecla != ENTER));

	cout << endl << endl;

	return;

}


// 7 MENU UTENTE
void menu_utente_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

	int y = 10+ opcao_b;
	int y1 = 10 + opcao;

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

void menu_utente(Piscina &p1, Utente* ute)
{
	int opcao = 1, opcao_b = 1, tecla;
	bool imprimir = true;

	do
	{
		if (imprimir)
		{
			limparEcra();
			titulo();
			cout << endl;
			cout << "\t\t\t Bem vindo, ";
			textcolor(CYAN);
			cout << ute->getNome();
			textcolor(WHITE);

			cout << endl << endl;
			cout << "\t\t\t\t    Ver registros" << endl;
			cout << "\t\t\t\t    Inscrever aulas" << endl;
			cout << "\t\t\t\t    Loja" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl;

		}

		imprimir = false;

		menu_utente_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 4);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				menu_registros(p1, *ute);
				imprimir = true;
				break;

			case 2:
				inscrever_aula(p1, ute);
				imprimir = true;
				break;

			case 3:
				imprimir = true;
				break;

			case 4:
				break;

			}

	} while ((opcao != 4) || (tecla != ENTER));

	cout << endl << endl;
	
	return;

}


// 6.5.2.2 Repor prods existentes

void repor_prods(Piscina &p1)
{
	limparEcra();
	cabecalho();
	cout << endl;

	BST<Produto> prods = p1.getLoja().getProdutos();
	BSTItrIn<Produto> it(prods);

	int y = 5;
	gotoxy(20, 4);
	textcolor(CYAN);
	cout << "Nome";
	textcolor(WHITE);

	gotoxy(40, 4);
	textcolor(CYAN);
	cout << "Tamanho";
	textcolor(WHITE);

	gotoxy(56, 4);
	textcolor(CYAN);
	cout << "Quantidade";
	textcolor(WHITE);


	while (!it.isAtEnd())
	{
		gotoxy(18, y);
		cout << it.retrieve().getNome();
		gotoxy(43, y);
		cout << it.retrieve().getTamanho();
		gotoxy(60, y);

		int i = it.retrieve().getStock();
		if (i > 10)
		{
			textcolor(LIGHT_GREEN);
			cout << i;
			textcolor(WHITE);
		}
		else if (i > 5)
		{
			textcolor(YELLOW);
			cout << i;
			textcolor(WHITE);
		}
		else {
			textcolor(LIGHT_RED);
			cout << i;
			textcolor(WHITE);
		}

		y++;

		it.advance();
	}

	Loja temp;
	string produto;
	Produto prod;

	while (1)
	{
		textcolor(LIGHT_GRAY);
		cout << endl << endl << "\t\tProduto: ";
		textcolor(WHITE);
		getline(cin, produto);

		bool existe = false;

		while (!it.isAtEnd())
		{
			if (it.retrieve().getNome() == produto)
			{
				existe = true;
				prod = it.retrieve();
				break;
			}
		}

		if (!existe)
		{
			textcolor(RED);
			cout << "\t\t* produto nao encontrado ";
			textcolor(WHITE);

		}
		else break;


		

	}

	bool stock_aceite = false;
	unsigned int stock_produto;

	while (!stock_aceite)
	{
		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Quantidade: ";
		textcolor(WHITE);
		cin >> stock_produto;

		if (cin.fail())
		{
			textcolor(RED);
			cout << "\t\t* stock invalido" << endl;
			textcolor(WHITE);
			cin.clear();
			cin.ignore(256, '\n');
		}
		else stock_aceite = true;

	}

	unsigned int stock = prod.getStock() + stock_produto;

	prod.setStock(stock);

	temp.repor_stock(prod);

	p1.setLoja(temp);




}


// 6.5.2.1 Adicionar produto
void loja_add_produto(Piscina &p1)
{
	limparEcra();
	cabecalho();
	cout << endl;

	bool nome_aceite = false;
	string nome_produto;

	while (!nome_aceite)
	{
		textcolor(LIGHT_GRAY);
		cout << "\n\t\tNome produto: ";
		textcolor(WHITE);
		getline(cin, nome_produto);

		if (nome_produto == "")
		{
			textcolor(RED);
			cout << "\t\t* nome invalido" << endl;
			textcolor(WHITE);
		}
		else {
			BSTItrIn<Produto> it(p1.getLoja().getProdutos());

			bool existe = false;

			while (!it.isAtEnd())
			{
				if (it.retrieve().getNome() == nome_produto)
				{
					existe = true;
					break;
				}
			}

			if (existe)
			{
				textcolor(RED);
				cout << "\t\t* produto ja existente" << endl;
				textcolor(WHITE);
			}
			else nome_aceite = true;

		}



	}

	bool tam_aceite = false;
	string tam_produto;

	while (!tam_aceite)
	{
		textcolor(LIGHT_GRAY);
		cout << "\n\t\tTamanho produto: ";
		textcolor(WHITE);
		getline(cin, tam_produto);

		if ((tam_produto == "xs") || (tam_produto == "XS") || (tam_produto == "Xs"))
			tam_aceite = true;
		else if ((tam_produto == "S") || (tam_produto == "s"))
			tam_aceite = true;
		else if ((tam_produto == "M") || (tam_produto == "m"))
			tam_aceite = true;
		else if ((tam_produto == "L") || (tam_produto == "l"))
			tam_aceite = true;
		else if ((tam_produto == "xl") || (tam_produto == "XL") || (tam_produto == "Xl"))
			tam_aceite = true;
		else if ((tam_produto == "xxl") || (tam_produto == "XXL") || (tam_produto == "Xxl"))
			tam_aceite = true;

		if (!tam_aceite)
		{
			textcolor(RED);
			cout << "\t\t* tamanho desconhecido" << endl;
			textcolor(WHITE);

		}
		else {
			if ((tam_produto == "xs") || (tam_produto == "Xs"))
				tam_produto = "XS";
			else if (tam_produto == "s")
				tam_produto = "S";
			else if (tam_produto == "m")
				tam_produto = "M";
			else if (tam_produto == "l")
				tam_produto = "L";
			else if ((tam_produto == "xl") || (tam_produto == "Xl"))
				tam_produto = "XL";
			else if ((tam_produto == "xxl") || (tam_produto == "Xxl"))
				tam_produto = "XXS";
		}


	}

	bool stock_aceite = false;
	unsigned int stock_produto;

	while (!stock_aceite)
	{
		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Stock: ";
		textcolor(WHITE);
		cin >> stock_produto;

		if (cin.fail())
		{
			textcolor(RED);
			cout << "\t\t* stock invalido" << endl;
			textcolor(WHITE);
			cin.clear();
			cin.ignore(256, '\n');
		}
		else stock_aceite = true;

	}

	Produto prod;

	prod.setNome(nome_produto);
	prod.setTamanho(tam_produto);
	prod.setStock(stock_produto);

	Loja loja1 = p1.getLoja();
	loja1.adiciona_produto(prod);
	p1.setLoja(loja1);

	cout << "\n\n\t\tProduto adicionado com sucesso. 'ENTER' para continuar" << endl;
	cin.ignore(256, '\n');

}


 // 6.5.2 Repor stock
void menu_repor_stock_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

	int y = 4 + opcao_b;
	int y1 = 4 + opcao;

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

void menu_repor_stock(Piscina &p1)
{
	int opcao = 1, opcao_b = 1, tecla;
	bool imprimir = true;

	do
	{
		if (imprimir)
		{
			limparEcra();
			cabecalho();
			cout << endl << endl;

			cout << "\t\t\t\t    Adicionar produto" << endl;
			cout << "\t\t\t\t    Repor stock produto" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl;

		}

		imprimir = false;

		menu_repor_stock_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 3);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				loja_add_produto(p1);
				imprimir = true;
				break;

			case 2:
				imprimir = true;
				break;

			case 3:
				break;

			}

	} while ((opcao != 3) || (tecla != ENTER));

	cout << endl << endl;

	return;

}


// 6.5.1 Ver stock
void ver_stock(Piscina &p1)
{
	limparEcra();
	cabecalho();
	cout << endl;

	BST<Produto> prods = p1.getLoja().getProdutos();
	BSTItrIn<Produto> it(prods);

	int y=5;
	gotoxy(20, 4);
	textcolor(CYAN);
	cout << "Nome";
	textcolor(WHITE);

	gotoxy(40, 4);
	textcolor(CYAN);
	cout << "Tamanho";
	textcolor(WHITE);

	gotoxy(56, 4);
	textcolor(CYAN);
	cout << "Quantidade";
	textcolor(WHITE);


	while (!it.isAtEnd())
	{
		gotoxy(18, y);
		cout << it.retrieve().getNome();
		gotoxy(43, y);
		cout << it.retrieve().getTamanho();
		gotoxy(60, y);
		
		int i = it.retrieve().getStock();
		if (i > 10)
		{
			textcolor(LIGHT_GREEN);
			cout << i;
			textcolor(WHITE);
		}
		else if (i > 5)
		{
			textcolor(YELLOW);
			cout << i;
			textcolor(WHITE);
		}
		else {
			textcolor(LIGHT_RED);
			cout << i;
			textcolor(WHITE);
		}
		
		y++;

		it.advance();
	}

	textcolor(CYAN);
	cout << "\n\n\n\t\t Prima 'ENTER' para sair" << endl;
	textcolor(WHITE);
	cin.ignore(256, '\n');


}


// 6.5 Menu gerir loja
void menu_loja_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

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

void menu_loja(Piscina &p1)
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

			cout << "\t\t\t\t    Ver stock" << endl;
			cout << "\t\t\t\t    Repor stock" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl;

		}

		imprimir = false;

		menu_loja_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 3);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				ver_stock(p1);
				imprimir = true;
				break;

			case 2:
				//menu_repor_stock(p1);
				imprimir = true;
				break;

			case 3:
				break;

			}

	} while ((opcao != 3) || (tecla != ENTER));

	cout << endl << endl;

	return;

}


// 6.4.1 Listar professores
void listar_professores(Piscina &p1)
{
	int opcao = 1;
	int tecla = 0;
	int imax = p1.getProfessores().size();
	int opcaomax = ((imax - 1) / 4) + 1;
	size_t i;

	while (1)
	{
		limparEcra();
		cabecalho();
		cout << endl << endl;

		for (i = (opcao - 1) * 4; ((i < opcao * 4) && (i < imax)); i++)
		{
			textcolor(LIGHT_GRAY);
			cout << "\t\tNome: ";
			textcolor(WHITE);
			cout << p1.getProfessores()[i]->getNome() << endl;

			textcolor(LIGHT_GRAY);
			cout << "\t\tNumero aulas: ";
			textcolor(WHITE);
			cout << p1.getProfessores()[i]->getaulas().size();

			cout << endl << endl;
			textcolor(WHITE);

		}

		cout << "\t\t\t\t";

		gotoxy(37, 20);
		textcolor(YELLOW);
		cout << "<<";
		textcolor(WHITE);


		cout << " Pagina " << opcao;

		textcolor(YELLOW);
		cout << " >>";
		textcolor(WHITE);

		textcolor(CYAN);
		cout << "\n\n\n Prima 'ENTER' para sair \n";
		textcolor(WHITE);

		tecla = opcao_valida_listas(opcao, 1, opcaomax);
		if (tecla == ENTER)
			break;
	}
}

// 6.4 Menu gerir professor
void menu_gerir_professores_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

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

void menu_gerir_professores(Piscina &p1)
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
			cout << "\t\t\t\t    Listar professores" << endl;
			cout << "\t\t\t\t    Adicionar professor" << endl;
			cout << "\t\t\t\t    Remover professor" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl << endl << endl;
			cout << endl << endl;

		}

		imprimir = false;

		menu_gerir_professores_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 4);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				listar_professores(p1);
				imprimir = true;
				break;

			case 2:
				p1.adicionarProfessor();
				imprimir = true;
				break;

			case 3:
				p1.apagarProfessor();
				imprimir = true;
				break;

			case 4:
				break;

			}

	} while ((opcao != 4) || (tecla != ENTER));

	cout << endl << endl;

	return;

}


// 6.3.2 Adicionar aula
void adicionar_aula_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

	int y = 4 + opcao_b;
	int y1 = 4 + opcao;

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

void adicionar_aula(Piscina &p1)
{
	string dia, mes, ano, horas;
	unsigned int dia1, mes1, ano1, horas1, minutos1;
	char lixo;
	bool avancar;
	bool avancar2 = false ;
	Data d_ini{};
	string opcao;
	Aula *a1 = new AulaPro();
	

	do {
		limparEcra();
		cabecalho();
		cout << endl << endl;

		int opcao_a = 1, opcao_b = 1, tecla;
		bool imprimir = true;

		do
		{
			if (imprimir)
			{
				limparEcra();
				cabecalho();

				cout << endl << endl;
				cout << "\t\t\t\t    Polo" << endl;
				cout << "\t\t\t\t    Natacao Sincronizada" << endl;
				cout << "\t\t\t\t    Mergulho" << endl;
				cout << "\t\t\t\t    Hidroginastica" << endl;
				cout << "\t\t\t\t    Competicao" << endl;
				cout << "\t\t\t\t    Sair" << endl;
				cout << endl << endl << endl << endl;
				cout << endl << endl;

			}

			imprimir = false;

			adicionar_aula_ops(opcao_a, opcao_b);
			opcao_b = opcao_a;
			tecla = opcao_valida(opcao_a, 1, 6);
			Sleep(100);


			if (tecla == ENTER)
				switch (opcao_a)
				{
				case 1:
					a1 = new Polo();
					break;

				case 2:
					a1 = new Sincronizada();
					break;

				case 3:
					a1 = new Mergulho();
					break;

				case 4:
					a1 = new Hidroginastica();
					break;

				case 5:
					a1 = new Competicao();
					break;

				case 6:
					return;
					break;

				}

		} while (tecla != ENTER);

		limparEcra();
		cabecalho();
		cout << endl << endl;

		do {
			textcolor(LIGHT_GRAY);
			cout << "\t\tDia: ";
			textcolor(WHITE);
			getline(cin, dia);
			stringstream ss1;
			ss1 << delete_space(dia);
			ss1 >> dia1;

			textcolor(LIGHT_GRAY);
			cout << "\n\t\tMes: ";
			textcolor(WHITE);
			getline(cin, mes);
			stringstream ss2;
			ss2 << delete_space(mes);
			ss2 >> mes1;

			textcolor(LIGHT_GRAY);
			cout << "\n\t\tAno: ";
			textcolor(WHITE);
			getline(cin, ano);
			stringstream ss3;
			ss3 << delete_space(ano);
			ss3 >> ano1;

			if (!dia_existe(dia1, mes1, ano1)) {
				textcolor(RED);
				cout << "\n\t\t  *dia inexistente" << endl << endl;
				textcolor(WHITE);
			}

		} while (!dia_existe(dia1, mes1, ano1));

		do {
			textcolor(LIGHT_GRAY);
			cout << "\n\t\tHora de incio (hh:mm): ";
			textcolor(WHITE);
			getline(cin, horas);
			stringstream ss4;
			ss4 << delete_space(horas);
			ss4 >> horas1 >> lixo >> minutos1;

			if ((horas1 > 23) || ((horas1 == 23) && (minutos1 > 0)) || (minutos1 >= 60) || (lixo != ':')) {
				avancar = false;
				textcolor(RED);
				cout << "\t\t  *hora invalida";
				textcolor(WHITE);
			}
			else {
				avancar = true;
			}

		} while (!avancar);


		bool existe{ false };
		d_ini.setAno(ano1);
		d_ini.setMes(mes1);
		d_ini.setDia(dia1);
		string dia_S = calculo_dia_da_semana(dia1, mes1, ano1);
		d_ini.setDiaSemana(dia_S);
		d_ini.setHoras(horas1);
		d_ini.setMinutos(minutos1);

		a1->setInicio(d_ini);

		if (p1.aulaSobreposta(a1))
			existe = true;
		else existe = false;

		if (existe)
		{
			textcolor(RED);
			cout << "\n\n\t\t   *nao e possivel sobrepor aulas";
			textcolor(WHITE);

			do {
				textcolor(LIGHT_GRAY);
				cout << "\n\n\t\tDeseja tentar outra data? ";
				textcolor(WHITE);
				getline(cin, opcao);

			} while ((opcao != "nao") && (opcao != "n") && (opcao != "sim") && (opcao != "s"));

		}
		else avancar2 = true;



	} while (!avancar2 && (opcao != "nao") && (opcao != "n"));


	if (avancar)
	{
		string dia_S = calculo_dia_da_semana(dia1, mes1, ano1);
		horas1++;
		//fim aula
		Data d_fim{};
		d_fim.setAno(ano1);
		d_fim.setMes(mes1);
		d_fim.setDia(dia1);
		d_fim.setDiaSemana(dia_S);
		d_fim.setHoras(horas1);
		d_fim.setMinutos(minutos1);

		a1->setFim(d_fim);
		a1->setId();
		a1->setNumMaximo(60);

		p1.adicionaAula(a1);
		//p1.atribui_profaula(a1);
		p1.ordena_por_data();

		textcolor(CYAN);
		cout << "\n\n\t\t Aula adicionada com sucesso! 'Enter' para continuar" << endl << endl;
		textcolor(WHITE);
		cin.ignore(256,'\n');

	}

}


// 6.3.1 Listar aulas
void listar_aulas(Piscina &p1)
{
	int opcao = 1;
	int tecla = 0;
	int imax = p1.getHorario().size();
	int opcaomax = ((imax-1) / 3) + 1;
	size_t i;

	while (1)
	{
		limparEcra();
		cabecalho();
		cout << endl << endl;

		for (i = (opcao - 1) * 3; ((i < opcao * 3) && (i < imax)); i++)
		{
			textcolor(LIGHT_GRAY);
			cout << "\t\tId aula: ";
			textcolor(WHITE);

			cout << p1.getHorario()[i]->getId() << endl;

			textcolor(LIGHT_GRAY);
			cout << "\t\tData: ";
			textcolor(WHITE);

			cout << p1.getHorario()[i]->getInicio().getDiaSemana() << ", ";

			cout << p1.getHorario()[i]->getInicio().getDia() << " de ";
			cout << mostrar_mes(p1.getHorario()[i]->getInicio().getMes()) << " de ";
			cout << p1.getHorario()[i]->getInicio().getAno() << endl;

			textcolor(LIGHT_GRAY);
			cout << "\t\tHora: ";
			textcolor(WHITE);

			if (p1.getHorario()[i]->getInicio().getHoras() < 10)
				cout << "0" << p1.getHorario()[i]->getInicio().getHoras();
			else
				cout << p1.getHorario()[i]->getInicio().getHoras();

			cout << ":";
			if (p1.getHorario()[i]->getInicio().getMinutos() < 10)
				cout << "0" << p1.getHorario()[i]->getInicio().getMinutos();
			else
				cout << p1.getHorario()[i]->getInicio().getMinutos();


			cout << " - ";

			if (p1.getHorario()[i]->getFim().getHoras() < 10)
				cout << "0" << p1.getHorario()[i]->getFim().getHoras();
			else
				cout << p1.getHorario()[i]->getFim().getHoras();

			cout << ":";
			if (p1.getHorario()[i]->getFim().getMinutos() < 10)
				cout << "0" << p1.getHorario()[i]->getFim().getMinutos() << endl;
			else
				cout << p1.getHorario()[i]->getFim().getMinutos() << endl;
			
			textcolor(LIGHT_GRAY);
			cout << "\t\tTipo: ";
			textcolor(WHITE);

			if (p1.getHorario()[i]->pro())
			{
				int modo = p1.getHorario()[i]->getInfo();

				switch (modo)
				{
				case 0:
					cout << "Polo";
					break;

				case 1:
					cout << "Sincronizada";
					break;

				case 2:
					cout << "Mergulho";
					break;

				case 3:
					cout << "Hidroginastica";
					break;

				case 4:
					cout << "Competicao";
					break;

				}
				
			}
				
			cout << endl << endl;
			textcolor(WHITE);

		}

		cout << "\t\t\t\t";
		
		gotoxy(37, 20);
		textcolor(YELLOW);
		cout << "<<";
		textcolor(WHITE);


		cout << " Pagina " << opcao;

		textcolor(YELLOW);
		cout << " >>";
		textcolor(WHITE);

		textcolor(CYAN);
		cout << "\n\n\n Prima 'ENTER' para sair \n";
		textcolor(WHITE);

		tecla = opcao_valida_listas(opcao, 1, opcaomax);
		if (tecla == ENTER)
			break;
	}
}


// 6.3 Menu gerir aulas
void menu_gerir_aulas_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

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

void menu_gerir_aulas(Piscina &p1)
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
			cout << "\t\t\t\t    Listar aulas" << endl;
			cout << "\t\t\t\t    Adicionar aula" << endl;
			cout << "\t\t\t\t    Remover aula" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl << endl << endl;
			cout << endl << endl;

		}

		imprimir = false;

		menu_gerir_aulas_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 4);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				listar_aulas(p1);
				imprimir = true;
				break;

			case 2:
				adicionar_aula(p1);
				imprimir = true;
				break;

			case 3:
				p1.apaga_aulas();
				imprimir = true;
				break;

			case 4:
				break;

			}

	} while ((opcao != 4) || (tecla != ENTER));

	cout << endl << endl;

	return;

}


// 6.2.4 Utentes inativos
void mostra_clientes_inativos(Piscina &p1)
{
	limparEcra();
	cabecalho();
	cout << endl << endl;

	tabHU inativos = p1.getInativos();

	iteratorH it = inativos.begin();

	while (it != inativos.end())
	{
		textcolor(LIGHT_GRAY);
		cout << "\t\t Nome: ";
		textcolor(WHITE);
		cout << (*it).getNome() << endl;
		
		textcolor(LIGHT_GRAY);
		cout << "\t\t Morada: ";
		textcolor(WHITE);
		cout << (*it).getMorada() << endl;

		textcolor(LIGHT_GRAY);
		cout << "\t\t Telemovel: ";
		textcolor(WHITE);
		cout << (*it).getTelemovel() << endl;

		textcolor(LIGHT_GRAY);
		cout << "\t\t Ultima aula: ";
		textcolor(WHITE);
		Data ultima_aula = (*it).getLast_class();
		cout << ultima_aula.getDia() << "/" << ultima_aula.getMes() << "/" << ultima_aula.getAno() << endl << endl;

	}

}

// 6.2.1 Listar utentes
void listar_utentes(Piscina &p1)
{
	int opcao = 1;
	int tecla = 0;
	int imax = p1.getUtentes().size();
	int opcaomax = ((imax - 1) / 3) + 1;
	size_t i;

	while (1)
	{
		limparEcra();
		cabecalho();
		cout << endl << endl;

		for (i = (opcao - 1) * 3; ((i < opcao * 3) && (i < imax)); i++)
		{
			textcolor(LIGHT_GRAY);
			cout << "\t\tNome: ";
			textcolor(WHITE);
			cout << p1.getUtentes()[i]->getNome() << endl;

			textcolor(LIGHT_GRAY);
			cout << "\t\tID: ";
			textcolor(WHITE);
			cout << p1.getUtentes()[i]->getId() << endl;

			textcolor(LIGHT_GRAY);
			cout << "\t\tUltima aula: ";
			textcolor(WHITE);

			Data d1 = p1.getUtentes()[i]->getLast_class();
			cout << d1.getDia() << "/" << d1.getMes() << "/" << d1.getAno();


			cout << endl << endl;
			textcolor(WHITE);

		}

		cout << "\t\t\t\t";

		gotoxy(37, 20);
		textcolor(YELLOW);
		cout << "<<";
		textcolor(WHITE);


		cout << " Pagina " << opcao;

		textcolor(YELLOW);
		cout << " >>";
		textcolor(WHITE);

		textcolor(CYAN);
		cout << "\n\n\n Prima 'ENTER' para sair \n";
		textcolor(WHITE);

		tecla = opcao_valida_listas(opcao, 1, opcaomax);
		if (tecla == ENTER)
			break;
	}
}


// 6.2 Menu gerir utentes
void menu_gerir_utentes_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

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

void menu_gerir_utentes(Piscina &p1)
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
			cout << "\t\t\t\t    Listar utentes" << endl;
			cout << "\t\t\t\t    Adicionar utente" << endl;
			cout << "\t\t\t\t    Remover utente" << endl;
			cout << "\t\t\t\t    Utentes inativos" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl << endl << endl;
			cout << endl << endl;

		}

		imprimir = false;

		menu_gerir_utentes_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 5);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				listar_utentes(p1);
				imprimir = true;
				break;

			case 2:
				p1.adicionar_utente();
				imprimir = true;
				break;

			case 3:
				p1.apagarUtente();
				imprimir = true;
				break;

			case 4:
				mostra_clientes_inativos(p1);
				imprimir = true;
				break;

			case 5:
				break;

			}

	} while ((opcao != 5) || (tecla != ENTER));

	cout << endl << endl;

	return;

}


// 6.1.2 Mostrar horario
void mostrar_horario(Piscina &p1)
{
	int tecla;
	{
		limparEcra();
		cabecalho();

		int a = 186;
		char char1 = a;  // obter -> ║

		int b = 201;
		char char2 = b; // obter -> ╔

		int c = 205;
		char char3 = c; // obter -> ═

		int d = 187;
		char char4 = d; // obter -> ╗

		int e = 200;
		char char5 = e; // obter -> ╚

		int f = 188;
		char char6 = f; // obter -> ╝

		int g = 204;
		char char7 = g; // obter -> ╠

		int h = 185;
		char char8 = h; // obter -> ╣

		int i = 203;
		char char9 = i; // obter -> ╦

		int j = 206;
		char char10 = j; // obter -> ╬

		int k = 202;
		char char11 = k; // obter -> ╩

		cout << "\t      " << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char9 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char4 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char11 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6 << endl;

		textcolor(CYAN);
		gotoxy(22, 4);
		cout << "Dias";

		gotoxy(53, 4);
		cout << "Horario";
		textcolor(WHITE);



		for (size_t i = 1; i <= 7; i++)
		{
			map<string, string>::iterator it{};
			switch (i)
			{
			case 1:
				it = p1.horariomap.find("segunda");
				gotoxy(21, 6);
				cout << "Segunda";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 6);
					cout << it->second;
				}
				else {
					gotoxy(53, 6);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 2:
				it = p1.horariomap.find("terca");
				gotoxy(21, 8);
				cout << "Terca";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 8);
					cout << it->second;
				}
				else {
					gotoxy(53, 8);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 3:
				it = p1.horariomap.find("quarta");
				gotoxy(21, 10);
				cout << "Quarta";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 10);
					cout << it->second;
				}
				else {
					gotoxy(53, 10);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 4:
				it = p1.horariomap.find("quinta");
				gotoxy(21, 12);
				cout << "Quinta";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 12);
					cout << it->second;
				}
				else {
					gotoxy(53, 12);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 5:
				it = p1.horariomap.find("sexta");
				gotoxy(21, 14);
				cout << "Sexta";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 14);
					cout << it->second;
				}
				else {
					gotoxy(53, 14);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 6:
				it = p1.horariomap.find("sabado");
				gotoxy(21, 16);
				cout << "Sabado";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 16);
					cout << it->second;
				}
				else {
					gotoxy(53, 16);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 7:
				it = p1.horariomap.find("domingo");
				gotoxy(21, 18);
				cout << "Domingo";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 18);
					cout << it->second;
				}
				else {
					gotoxy(53, 18);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			}

		}

		textcolor(CYAN);
		cout << "\n\n\t Prima ENTER para continuar" << endl;
		textcolor(WHITE);
		int opcao;
		tecla = opcao_valida(opcao, 1, 1);
	} while (tecla != ENTER);
}


// 6.1.1 Estado atual
void estado_atual(Piscina &p1)
{
	limparEcra();
	cabecalho();

	cout << endl << endl;

	Data atual{};
	int dia = dia_do_sistema();
	int mes = mes_do_sistema();
	int ano = ano_do_sistema();
	string dia_S = calculo_dia_da_semana(dia, mes, ano);
	int horas = horas_do_sistema();
	int minutos = minutos_do_sistema();

	atual.setAno(ano);
	atual.setMes(mes);
	atual.setDia(dia);
	atual.setHoras(horas);
	atual.setMinutos(minutos);
	atual.setDiaSemana(dia_S);

	unsigned int utentes_a{};
	bool existe{ false };
	unsigned int id{};

	for (size_t i{}; i < p1.getHorario().size(); i++) {
		if ((p1.getHorario()[i]->getInicio() < atual)
			&& (atual < p1.getHorario()[i]->getFim())) {
			existe = true;
			id = i;
			break;

		}

	}

	utentes_a = p1.getUtentesNaPisicina().size();

	if (!existe)
	{
		cout << "\n\t\t\t Atualmente a piscina encontra-se fechada!" << endl << endl;

	}
	else {
		cout << "\t\tId aula: " << p1.getHorario()[id]->getId() << endl;
		cout << "\t\tDuracao: " << p1.getHorario()[id]->getDuracao() << endl;
		cout << "\t\tHora inicio: ";

		if (p1.getHorario()[id]->getInicio().getHoras()<10)
			cout << "0" << p1.getHorario()[id]->getInicio().getHoras();
		else
			cout << p1.getHorario()[id]->getInicio().getHoras();

		cout << ":";
		if (p1.getHorario()[id]->getInicio().getMinutos()<10)
			cout << "0" << p1.getHorario()[id]->getInicio().getMinutos() << endl;
		else
			cout << p1.getHorario()[id]->getInicio().getMinutos() << endl;


		cout << "\t\tHora fim: ";

		if (p1.getHorario()[id]->getFim().getHoras() < 10)
			cout << "0" << p1.getHorario()[id]->getFim().getHoras();
		else
			cout << p1.getHorario()[id]->getFim().getHoras();

		cout << ":";
		if (p1.getHorario()[id]->getFim().getMinutos() < 10)
			cout << "0" << p1.getHorario()[id]->getFim().getMinutos() << endl;
		else
			cout << p1.getHorario()[id]->getFim().getMinutos() << endl;

		cout << "\t\tProfesor: " << p1.getHorario()[id]->getProfessor() << endl;

		cout << "\t\tCategoria: ";

		int categ = p1.getHorario()[id]->getInfo();

		switch (categ)
		{
		case 0:
			cout << "Polo aquatico";
			break;

		case 1:
			cout << "Natacao sincronizada";
			break;

		case 2:
			cout << "Mergulho";
			break;

		case 3:
			cout << "Hidroginastica";

		case 4:
			cout << "Competicao";
			break;

		default:
			break;
		}

		cout << endl << endl;

		faz_grafico(utentes_a, "pessoas na piscina", p1.getLotacao(), "vagas", "lugares na piscina");



	}

	textcolor(CYAN);
	cout << "\n\n\t\tPrima 'Enter' para continuar " << endl;
	textcolor(WHITE);
	cin.ignore(256, '\n');

	return;

}


// 6.1 Menu gerir piscina
void menu_gerir_piscina_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

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

void menu_gerir_piscina(Piscina &p1)
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
			cout << "\t\t\t\t    Estado atual" << endl;
			cout << "\t\t\t\t    Horario de funcionamento" << endl;
			cout << "\t\t\t\t    Piscinas nas proximidades" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl << endl << endl;
			cout << endl << endl;

		}

		imprimir = false;

		menu_gerir_piscina_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 4);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				estado_atual(p1);
				imprimir = true;
				break;

			case 2:
				mostrar_horario(p1);
				imprimir = true;
				break;

			case 3:
				p1.imprime_piscinas_prox();
				textcolor(CYAN);
				cout << endl << endl << "Prima 'ENTER' para sair" << endl;
				textcolor(WHITE);
				cin.ignore(256, '\n');
				imprimir = true;
				break;

			case 4:
				break;

			}

	} while ((opcao != 4) || (tecla != ENTER));

	cout << endl << endl;

	return;

}


// 6 MENU ADMIN
void menu_admin_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

	int y = 10 + opcao_b;
	int y1 = 10 + opcao;

	gotoxy(34, y);
	textcolor(YELLOW);
	cout << " ";
	textcolor(WHITE);

	gotoxy(34, y1);
	textcolor(YELLOW);
	cout << square;
	textcolor(WHITE);



	gotoxy(0, 21);

	return;
}

void menu_admin(Piscina &p1, string &fichPiscina, string &fichUtentes, string &fichAulas, string &fichProfessores)
{
	int opcao = 1, opcao_b = 1, tecla;
	bool imprimir = true;

	atualizar_aulas_piscina(p1);

	do
	{
		apagar_aulas_old(p1);
		atualizar_utentes_piscina(p1);

		if (imprimir)
		{
			limparEcra();
			titulo();
			cout << endl;
			cout << "\t\t\t Bem vindo, ";
			textcolor(CYAN);
			cout << "admin";
			textcolor(WHITE);

			cout << endl << endl;
			cout << "\t\t\t\t    Gerir Piscina" << endl;
			cout << "\t\t\t\t    Gerir Utentes" << endl;
			cout << "\t\t\t\t    Gerir Aulas" << endl;
			cout << "\t\t\t\t    Gerir Professores" << endl;
			cout << "\t\t\t\t    Gerir Loja" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl << endl << endl;
			cout << "\t\t\t\t\t\t\t\t" << mostrar_mes(mes_do_sistema()) << " " << ano_do_sistema();
			cout << endl << endl;

		}

		imprimir = false;

		menu_admin_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 6);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				menu_gerir_piscina(p1);
				imprimir = true;
				break;

			case 2:
				menu_gerir_utentes(p1);
				imprimir = true;
				break;

			case 3:
				menu_gerir_aulas(p1);
				imprimir = true;
				break;

			case 4:
				menu_gerir_professores(p1);
				imprimir = true;
				break;

			case 5:
				menu_loja(p1);
				imprimir = true;
				break;

			case 6:
				break;

			}

	} while ((opcao != 6) || (tecla != ENTER));

	cout << endl << endl;

	return;

}


// 5.1 Entrar como utente
void encontra_parecido(Piscina &p1, string nome, Utente &melhor)
{
	unsigned int melhor_count = 0;
	unsigned int atual=0;
	string nome_a;


	for (size_t i = 0; i < p1.getUtentes().size(); i++)
	{
		atual = 0;
		nome_a = p1.getUtentes()[i]->getNome();

		for (size_t j = 0; j < nome.size(); j++)
		{
			for (size_t k = 0; k <nome_a.size(); k++)
			{
				if (nome[j] == nome_a[k])
				{
					atual++;
					break;
				}
			}

		}

		if (atual > melhor_count)
		{
			melhor = *p1.getUtentes()[i];
			melhor_count = atual;
		}
		else if (atual == melhor_count)
		{
			int a1, a2;
			a1 = abs(nome[0] - melhor.getNome()[0]);
			a2 = abs(nome[0] - p1.getUtentes()[i]->getNome()[0]);

			if (a2 < a1)
			{
				melhor = *p1.getUtentes()[i];
				melhor_count = atual;
			}
		}
	}

	return;
}

void entrar_como_utente_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

	int y = 7 + opcao_b;
	int y1 = 7 + opcao;

	gotoxy(22, y);
	textcolor(YELLOW);
	cout << " ";
	textcolor(WHITE);

	gotoxy(22, y1);
	textcolor(YELLOW);
	cout << square;
	textcolor(WHITE);



	gotoxy(0, 21);
}

void entrar_como_utente(Piscina &p1)
{
	limparEcra();
	cabecalho();
	bool encontrou = false;
	vector<Utente *> ut1 = p1.getUtentes();
	Utente *novo = new Utente();


	string nome;

	if (p1.getUtentes().size() >= 1)
	{
		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Nome utente: ";
		textcolor(WHITE);
		getline(cin, nome);
		nome = delete_space(nome);
		if (nome == "sair")
			return;

		for (size_t i = 0; i < ut1.size(); i++)
		{
			if (ut1[i]->getNome() == nome)
			{
				novo = ut1[i];
				encontrou = true;
				break;
			}
		}
		if (!encontrou)
		{
			encontra_parecido(p1, nome, (*novo));
			cout << endl;
			textcolor(RED);
			cout << "\t\t Cliente nao encontrado.";
			cout << " Sera que quis dizer " << novo->getNome() << "?" << endl << endl;
			textcolor(WHITE);

			cout << "\t\t\tSim" << endl;
			cout << "\t\t\tNao" << endl;

			int opcao = 1, opcao_b = 1, tecla;

			while (1)
			{
				entrar_como_utente_ops(opcao, opcao_b);
				opcao_b = opcao;
				tecla = opcao_valida(opcao, 1, 2);
				Sleep(100);

				if (tecla == ENTER)
				{
					switch (opcao)
					{
					case 1:
						menu_utente(p1, novo);
						break;
					case 2:
						break;
					}

					break;
				}


			}

		}
		else {
			for (size_t i = 0; i < p1.getUtentes().size(); i++)
			{
				if (novo->getId() == p1.getUtentes()[i]->getId())
				{
					menu_utente(p1, p1.getUtentes()[i]);
				}

			}

		} 

	}
	else {

		textcolor(RED);
		cout << "\n\n\t\t A lista de utentes encontra-se vazia " << endl;
		textcolor(WHITE);
		cout << endl << endl;
		cout << "\t\t Prima ENTER para voltar" << endl;
		cin.ignore(256, '\n');
	}

}


// 5 MENU GERAL
void menu_geral_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

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

void menu_geral(Piscina &p1, string &fichPiscina, string &fichUtentes, string &fichAulas, string &fichProfessores)
{

	////////////////////////////////////////////////////////////////////////// <- UTENTES PARA TESTE ---- APAGAR
 	Utente *novo = new Utente();
	string a = "David";
	novo->setNome(a);
	p1.addUtente(novo);
	
	Utente *novo1 = new Utente();
	string a1 = "Divad";
	novo1->setNome(a1);
	p1.addUtente(novo1);

	Loja nova;
	string fichLoja = "loja.txt";
	nova.ler_FichLoja(fichLoja);

	p1.setLoja(nova);
	////////////////////////////////////////////////////////////////////////////

	int opcao = 1, opcao_b = 1, tecla;
	bool imprimir = true;
	atualizar_aulas_piscina(p1);
	do
	{
		if (imprimir)
		{
			apagar_aulas_old(p1);
			atualizar_utentes_piscina(p1);
			limparEcra();
			titulo();
			cout << endl << endl;
			cout << "\t\t\t\t    Entrar como administrador" << endl;
			cout << "\t\t\t\t    Entrar como utente" << endl;
			cout << "\t\t\t\t    Voltar ao menu anterior" << endl;

			cout << endl << endl;

		}

		imprimir = false;

		menu_geral_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 3);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao)
			{
			case 1:
				menu_admin(p1, fichPiscina, fichUtentes, fichAulas, fichProfessores);
				imprimir = true;
				break;

			case 2:
				entrar_como_utente(p1);
				imprimir = true;
				break;


			case 3:
				return;
				break;

			}

	} while ((opcao != 3) || (tecla != 13));

	cout << endl << endl;



}


// 4.4 Testar ficheiro professores
string testar_fich_professores()
{
	string opcao;
	ifstream in;
	bool ok;

	do
	{
		cout << "\n\t\t Professores: ";
		getline(cin, opcao);
		if (opcao == "sair")
			return opcao;

		opcao = opcao + ".txt";

		in.open(opcao);

		if (!in.is_open())
		{
			textcolor(RED);
			cout << "\t\tO ficheiro " << opcao << " nao existe! \n";
			textcolor(WHITE);

		}
		else {
			string tipo;
			getline(in, tipo, ';');
			tipo = delete_space(tipo);

			if (tipo == "Professor") {
				ok = true;
			}
			else {
				textcolor(RED);
				cout << "\t\tO ficheiro " << opcao
					<< " nao contem informacoes sobre Professores! \n";
				textcolor(WHITE);
				ok = false;
				in.close();
			}
		}

	} while (!in.is_open() || !ok);

	in.close();


	return opcao;

}


// 4.3 Testar ficheiro aulas
string testar_fich_aulas()
{
	string opcao;
	ifstream in{};
	bool ok{};

	do
	{
		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Aulas: ";
		textcolor(WHITE);
		getline(cin, opcao);
		if (opcao == "sair")
			return opcao;

		opcao = opcao + ".txt";

		in.open(opcao);

		if (!in.is_open())
		{
			textcolor(RED);
			cout << "\t\tO ficheiro " << opcao << " nao existe! \n";
			textcolor(WHITE);
		}
		else {
			string tipo;
			getline(in, tipo, ';');
			tipo = delete_space(tipo);

			if (tipo == "Aula") {
				ok = true;
			}
			else {
				textcolor(RED);
				cout << "\t\tO ficheiro " << opcao << " nao contem informacoes sobre a Aulas! \n";
				textcolor(WHITE);
				ok = false;
				in.close();
			}
		}

	} while (!in.is_open() || !ok);

	in.close();

	return opcao;

}


// 4.2 Testar ficheiro utentes
string testar_fich_utentes()
{
	string opcao;
	ifstream in{};
	bool ok{};

	do
	{
		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Utentes: ";
		textcolor(WHITE);
		getline(cin, opcao);
		if (opcao == "sair")
			return opcao;

		opcao = opcao + ".txt";

		in.open(opcao);

		if (!in.is_open())
		{ 
			textcolor(RED);
			cout << "\t\tO ficheiro " << opcao << " nao existe! \n";
			textcolor(WHITE);
		}
		else {
			string tipo;
			getline(in, tipo, ';');
			tipo = delete_space(tipo);

			if (tipo == "Utente") {
				ok = true;
			}
			else {
				textcolor(RED);
				cout << "\t\tO ficheiro " << opcao << " nao contem informacoes sobre a Utentes! \n";
				textcolor(WHITE);
				ok = false;
				in.close();
			}
		}


	} while (!in.is_open() || !ok);

	in.close();

	return opcao;


}


// 4.1 Testar ficheiro piscina
string testar_fich_piscina() 
{
	string opcao;
	ifstream in{};

	bool ok{};

	do {
		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Piscina: ";
		textcolor(WHITE);
		getline(cin, opcao);

		if (opcao == "sair")
			return opcao;

		opcao = opcao + ".txt";

		in.open(opcao);

		if (!in.is_open())
		{ 
			textcolor(RED);
			cout << "\t\tO ficheiro " << opcao << " nao existe! \n";
			textcolor(WHITE);
		}
		else {
			string tipo;
			getline(in, tipo, ';');
			tipo = delete_space(tipo);

			if (tipo == "Piscina") {
				ok = true;
			}
			else {
				textcolor(RED);
				cout << "\t\tO ficheiro " << opcao << " nao contem informacoes sobre a Piscina! \n";
				textcolor(WHITE);
				ok = false;
				in.close();
			}
		}

	} while (!in.is_open() || !ok);

	in.close();

	return opcao;

}


// 4 CARREGAR PISCINA
void importar_ficheiros(string &fichPiscina, string &fichUtentes, string &fichAulas, string &fichProfessores) /// importar conteudo dos ficheiros
{
	Piscina p1;
	p1.ler_FichPiscina(fichPiscina);
	p1.ler_FichAulas(fichAulas);
	p1.ler_FichProfessores(fichProfessores);
	p1.ler_FichUtente(fichUtentes);
	p1.utentes_aulas();
	p1.professores_aulas();
	menu_geral(p1, fichPiscina, fichUtentes, fichAulas, fichProfessores);

	return;
}

void escolher_ficheiros() /// um para cada classe
{
	string fichPiscina, fichUtentes, fichAulas, fichProfessores;

	limparEcra();
	cabecalho();
	textcolor(LIGHT_GRAY);
	cout << "\n\n\t\t Defina os ficheiros que contem informacoes sobre: \n";
	textcolor(WHITE);
	fichPiscina = testar_fich_piscina();
	if (fichPiscina != "sair") {
		fichUtentes = testar_fich_utentes();
		if (fichUtentes != "sair") {
			fichAulas = testar_fich_aulas();
			if (fichAulas != "sair") {
				fichProfessores = testar_fich_professores();
				if (fichProfessores != "sair")
				{
					importar_ficheiros(fichPiscina, fichUtentes, fichAulas, fichProfessores);
					return;
				}
			}
		}
	}

	cout << " Importacao cancelada pelo utilizador! Redirecionando ...\n ";
	system("sleep 2");
}


// 3.6 Verificação antes de avançar
unsigned int check(Piscina &p1, string &fichPiscina, string &fichUtentes, int loc)
{
	limparEcra();
	cabecalho();

	bool falta = false;
	unsigned int nome = 0, lotacao = 0, horario = 0, base_dados = 0, modalidades = 0;
	unsigned int localizacao = 0;
	int a = 254;
	char square = a;

	if (p1.getNome() == "")
	{
		falta = true;
	}
	else nome = 1;

	if (p1.getLotacao() == NULL)
	{
		falta = true;
	}
	else lotacao = 1;

	map<string, string>::iterator it = p1.horariomap.begin();

	if (it == p1.horariomap.end())
	{
		falta = true;
	}
	else horario = 1;

	if (loc == 0)
	{
		falta = true;
	}
	else localizacao = 1;

	if (p1.getModalidades().size() == NULL)
	{
		falta = true;
	}
	else modalidades = 1;


	if ((fichUtentes == "") && (fichPiscina == ""))
	{
		falta = true;
	}
	else base_dados = 1;


	if (falta)
	{
		cout << "\t\t Informacoes em falta: " << endl;
		textcolor(RED);
		if (!nome)
		{
			cout << "\t\t " << square << " nome" << endl;
		}
		if (!lotacao)
		{
			cout << "\t\t " << square << " lotacao" << endl; 
		}
		if (!horario)
		{
			cout << "\t\t " << square << " horario" << endl;
		}

		if (!localizacao)
		{
			cout << "\t\t " << square << " localizacao" << endl;
		}
		
		if (!modalidades)
		{
			cout << "\t\t " << square << " modalidades" << endl;
		}


		if (!base_dados)
		{
			cout << "\t\t " << square << " base de dados" << endl;
		}
		textcolor(WHITE);

		cout << "\n\n\t\t Prima enter para voltar";
		gotoxy(0, 21);
		cin.ignore(256, '\n');

		return 0;
	}

	return 1;
}


// 3.5 Definir base de dados
void definir_base_de_dados(string &fichPiscina, string &fichUtentes, string &fichAulas, string &fichProfessores)
{
	limparEcra();
	cabecalho();
	int a = 254;
	char square = a;


	if (fichPiscina != "")
	{
		textcolor(RED);
		cout << "\n\n\t\tPiscina: ";
		textcolor(WHITE);
		cout << fichPiscina << endl;
		textcolor(RED);
		cout << "\t\tUtentes: ";
		textcolor(WHITE);
		cout << fichUtentes << endl;
		textcolor(RED);
		cout << "\t\tAulas: ";
		textcolor(WHITE);
		cout << fichAulas << endl;
		textcolor(RED);
		cout << "\t\tProfessores: ";
		textcolor(WHITE);
		cout << fichProfessores << endl;

		string opcao;

		do {
			textcolor(LIGHT_GRAY);
			cout << "\n\t\t Deseja aterar? ";
			textcolor(WHITE);
			getline(cin, opcao);

		} while ((opcao != "nao") && (opcao != "n") && (opcao != "sim") && (opcao != "s"));


		if ((opcao == "nao") || (opcao == "n")) /// se nao deseja guardar
			return;


	}
	
		limparEcra();
		cabecalho();
		textcolor(LIGHT_GRAY);
		cout << "\n\n\t\t Escolha o ficheiro para guardar informacoes sobre: \n\n"; 
		textcolor(WHITE);


	ifstream in{};
	ofstream out{};

	 // escolher nome do ficheiro para guardar Piscina

	string piscina_temp;
	cin.ignore(256, '\n');

	do {
		in.close();
		out.close();

		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Piscina: ";
		textcolor(WHITE);
		cin.clear();
		getline(cin, piscina_temp);
		if (piscina_temp == "sair")
			return; //sair sem modificacoes

		piscina_temp += ".txt";
		in.open(piscina_temp);

		if (!in.fail()) {
			textcolor(RED);
			cout << "\t\t" << square << piscina_temp << " ja existente!" << endl;
			textcolor(WHITE);
		}
		else {

			out.open(piscina_temp);
			if (out.fail()) {
				textcolor(RED);
				cout << piscina_temp << " : nome do ficheiro invalido" << endl;
				textcolor(WHITE);
			}
		}

	} while (!in.fail() || out.fail());

	in.close();
	out.close();

	// escolher nome do ficheiro para guardar Utentes

	string utentes_temp;

	do {
		in.close();
		out.close();

		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Utentes: ";
		textcolor(WHITE);
		cin.clear();
		getline(cin, utentes_temp);

		if (utentes_temp == "sair")
			{
			const char *lixop = piscina_temp.c_str();  // apagar ficheiro temporario piscina
			remove(lixop);
			return; //sair sem modificacoes
		}
			

		utentes_temp += ".txt";
		in.open(utentes_temp);

		if (!in.fail()) {
			textcolor(RED);
			cout << "\t\t"<< square << utentes_temp << " ja existente!" << endl;
			textcolor(WHITE);
		}
		else {

			out.open(utentes_temp);
			if (out.fail()) {
				textcolor(RED);
				cout << utentes_temp << " : nome do ficheiro invalido" << endl;
				textcolor(WHITE);
			}
		}

	} while (!in.fail() || out.fail());

	in.close();
	out.close();


	// escolher nome do ficheiro para guardar Aulas

	string aulas_temp;

	do {
		in.close();
		out.close();

		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Aulas: ";
		textcolor(WHITE);
		cin.clear();
		getline(cin, aulas_temp);

		if (aulas_temp == "sair")
		{
			const char *lixop = piscina_temp.c_str();  // apagar ficheiro temporario piscina
			remove(lixop);
			const char *lixou = utentes_temp.c_str();  // apagar ficheiro temporario utentes
			remove(lixou);
			return; //sair sem modificacoes
		}

		aulas_temp += ".txt";
		in.open(aulas_temp);

		if (!in.fail()) {
			textcolor(RED);
			cout << "\t\t " << square <<aulas_temp << " ja existente!" << endl;
			textcolor(WHITE);
		}
		else {

			out.open(aulas_temp);
			if (out.fail()) {
				textcolor(RED);
				cout << aulas_temp << " : nome do ficheiro invalido" << endl;
				textcolor(WHITE);
			}
		}

	} while (!in.fail() || out.fail());

	in.close();
	out.close();


	// escolher nome do ficheiro para guardar Professores

	string profs_temp;

	do {
		in.close();
		out.close();

		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Professores: ";
		textcolor(WHITE);
		cin.clear();
		getline(cin, profs_temp);

		if (profs_temp == "sair")
		{
			const char *lixop = piscina_temp.c_str();  // apagar ficheiro temporario piscina
			remove(lixop);
			const char *lixou = utentes_temp.c_str();  // apagar ficheiro temporario utentes
			remove(lixou);
			const char *lixoa = aulas_temp.c_str();  // apagar ficheiro temporario aulas
			remove(lixoa);
			return; //sair sem modificacoes
		}

		profs_temp += ".txt";
		in.open(profs_temp);

		if (!in.fail()) {
			textcolor(RED);
			cout << "\t\t" << square <<profs_temp << " ja existente!" << endl;
			textcolor(WHITE);
		}
		else {

			out.open(profs_temp);
			if (out.fail()) {
				textcolor(RED);
				cout << profs_temp << " : nome do ficheiro invalido" << endl;
				textcolor(WHITE);
			}
		}

	} while (!in.fail() || out.fail());

	in.close();
	out.close();

	const char *lixo = piscina_temp.c_str();  // apagar ficheiro temporario piscina
	remove(lixo);
	const char *lixo1 = utentes_temp.c_str();  // apagar ficheiro temporario utentes
	remove(lixo1);
	const char *lixo2 = aulas_temp.c_str();  // apagar ficheiro temporario aulas
	remove(lixo2);
	const char *lixo3 = profs_temp.c_str();  // apagar ficheiro temporario lixo
	remove(lixo3);

	/// Guardar ou não

	string opcao{};

	do {
		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Deseja guardar? ";
		textcolor(WHITE);
		getline(cin, opcao);

	} while ((opcao != "nao") && (opcao != "n") && (opcao != "sim")
		&& (opcao != "s"));

	if ((opcao == "nao") || (opcao == "n")) /// se nao deseja guardar
		return; /// retorna sem modificacoes

				  /// guardar nomes dos ficheiros

	fichPiscina = piscina_temp;
	fichUtentes = utentes_temp;
	fichAulas = aulas_temp;
	fichProfessores = profs_temp;

}


// 3.6 Definir modalidades

void definir_modalidade_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a;

	int y, y1;

	if (opcao_b > 5)
		y = 7 + opcao_b;
	else y = 6 + opcao_b;

	if (opcao > 5)
		y1 = 7 + opcao;
	else y1 = 6 + opcao;

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

void definir_modalidades(Piscina &p1)
{

	int opcao_a = 1, opcao_b = 1, tecla;
	bool imprimir = true;
	vector<string> mod;

	do
	{
			if (imprimir)
			{
				limparEcra();
				cabecalho();
				textcolor(LIGHT_GRAY);
				cout << "\n\n\t\t Atualmente: ";
				textcolor(WHITE);
				if (mod.size() == 0)
				{
					textcolor(RED);
					cout << "sem modalidades ";
					textcolor(WHITE);
				}
				else
				{
					cout << mod[0];
					for (size_t i = 1; i < mod.size(); i++) {
						cout << ", " << mod[i];
					}
				}

			cout << endl << endl;
			cout << "\t\t\t\t    Polo" << endl;
			cout << "\t\t\t\t    Natacao Sincronizada" << endl;
			cout << "\t\t\t\t    Mergulho" << endl;
			cout << "\t\t\t\t    Hidroginastica" << endl;
			cout << "\t\t\t\t    Competicao" << endl << endl;
			cout << "\t\t\t\t    Voltar" << endl;
			cout << endl << endl << endl << endl;
			cout << endl << endl;

		}

		imprimir = false;

		definir_modalidade_ops(opcao_a, opcao_b);
		opcao_b = opcao_a;
		tecla = opcao_valida(opcao_a, 1, 6);
		Sleep(100);


		if (tecla == ENTER)
			switch (opcao_a)
			{
			case 1:
				if (encontra_string_vetor("polo", mod) == -1)
					mod.push_back("polo");
				else {
					mod.erase(mod.begin() + (encontra_string_vetor("polo", mod)));
				}
				imprimir = true;
				break;

			case 2:
				if (encontra_string_vetor("sincronizada", mod) == -1)
					mod.push_back("sincronizada");
				else {
					mod.erase(mod.begin() + (encontra_string_vetor("sincronizada", mod)));
				}
				imprimir = true;
				break;

			case 3:
				if (encontra_string_vetor("mergulho", mod) == -1)
					mod.push_back("mergulho");
				else {
					mod.erase(mod.begin() + (encontra_string_vetor("mergulho", mod)));
				}
				imprimir = true;
				break;

			case 4:
				if (encontra_string_vetor("hidroginastica", mod) == -1)
					mod.push_back("hidroginastica");
				else {
					mod.erase(mod.begin() + (encontra_string_vetor("hidroginastica", mod)));
				}
				imprimir = true;
				break;

			case 5:
				if (encontra_string_vetor("competicao", mod) == -1)
					mod.push_back("competicao");
				else {
					mod.erase(mod.begin() + (encontra_string_vetor("competicao", mod)));
				}
				imprimir = true;
				break;

			case 6:
				p1.setModalidades(mod);
				return;
				break;

			}

	} while ((tecla != ENTER)|| (opcao_a != 6));


}


//3.4 Definir localizacao
void definir_localizacao(Piscina &p1)
{
	limparEcra();
	cabecalho();

	unsigned int x,y;
	bool fim = false;
	int a = 254;
	char square = a; // obter  █

	do
	{
		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Coordenada x: ";
		textcolor(WHITE);
		cin >> x;

		if (cin.fail())
		{
			textcolor(RED);
			cout << "\t\t " << square << " Numero invalido \n\n ";
			textcolor(WHITE);
			cin.clear();
			cin.ignore(256, '\n');
		}
		else fim = true;

	} while (!fim);

	textcolor(LIGHT_GREEN);
	cout << "\t\t " << square << " aceite" << endl;
	textcolor(WHITE);
	
	fim = false;

	do
	{
		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Coordenada y: ";
		textcolor(WHITE);
		cin >> y;

		if (cin.fail())
		{
			textcolor(RED);
			cout << "\t\t " << square << " Numero invalido \n\n ";
			textcolor(WHITE);
			cin.clear();
			cin.ignore(256, '\n');
		}
		else fim = true;

	} while (!fim);

	textcolor(LIGHT_GREEN);
	cout << "\t\t " << square << " aceite" << endl;
	textcolor(WHITE);

	
	p1.setX(x);
	p1.setY(y);
	
}


//3.3 Definir horario
void mostrar_calendario(Piscina p1)
{
	int tecla;
	{
		limparEcra();
		cabecalho();

		int a = 186;
		char char1 = a;  // obter -> ║

		int b = 201;
		char char2 = b; // obter -> ╔

		int c = 205;
		char char3 = c; // obter -> ═

		int d = 187;
		char char4 = d; // obter -> ╗

		int e = 200;
		char char5 = e; // obter -> ╚

		int f = 188;
		char char6 = f; // obter -> ╝

		int g = 204;
		char char7 = g; // obter -> ╠

		int h = 185;
		char char8 = h; // obter -> ╣

		int i = 203;
		char char9 = i; // obter -> ╦

		int j = 206;
		char char10 = j; // obter -> ╬

		int k = 202;
		char char11 = k; // obter -> ╩

		cout << "\t      " << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char9 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char4 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char7 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char10 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char8 << endl;
		cout << "\t      " << char1 << "                    " << char1 << "                                       " << char1 << endl;
		cout << "\t      " << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char11 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6 << endl;

		textcolor(CYAN);
		gotoxy(22, 4);
		cout << "Dias";

		gotoxy(53, 4);
		cout << "Horario";
		textcolor(WHITE);



		for (size_t i = 1; i <= 7; i++)
		{
			map<string, string>::iterator it;
			switch (i)
			{
			case 1:
				it = p1.horariomap.find("segunda");
				gotoxy(21, 6);
				cout << "Segunda";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 6);
					cout << it->second;
				}
				else {
					gotoxy(53, 6);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 2:
				it = p1.horariomap.find("terca");
				gotoxy(21, 8);
				cout << "Terca";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 8);
					cout << it->second;
				}
				else {
					gotoxy(53, 8);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 3:
				it = p1.horariomap.find("quarta");
				gotoxy(21, 10);
				cout << "Quarta";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 10);
					cout << it->second;
				}
				else {
					gotoxy(53, 10);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 4:
				it = p1.horariomap.find("quinta");
				gotoxy(21, 12);
				cout << "Quinta";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 12);
					cout << it->second;
				}
				else {
					gotoxy(53, 12);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 5:
				it = p1.horariomap.find("sexta");
				gotoxy(21, 14);
				cout << "Sexta";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 14);
					cout << it->second;
				}
				else {
					gotoxy(53, 14);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 6:
				it = p1.horariomap.find("sabado");
				gotoxy(21, 16);
				cout << "Sabado";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 16);
					cout << it->second;
				}
				else {
					gotoxy(53, 16);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			case 7:
				it = p1.horariomap.find("domingo");
				gotoxy(21, 18);
				cout << "Domingo";
				if (it != p1.horariomap.end())
				{
					gotoxy(50, 18);
					cout << it->second;
				}
				else {
					gotoxy(53, 18);
					textcolor(RED);
					cout << "FECHADO";
					textcolor(WHITE);

				}
				break;

			}

		}

		textcolor(CYAN);
		cout << "\n\n\t Prima ENTER para continuar" << endl;
		textcolor(WHITE);
		int opcao;
		tecla = opcao_valida(opcao, 1, 1);
	} while (tecla != ENTER);
}

unsigned int definir_horas(Piscina &p1, vector<string> &dias)
{
	string hora_i, hora_f;
	int horas{}, minutos{};
	char car{};
	bool avancar{ false };
	int a = 254;
	char square = a; // obter  █

	cin.ignore(256, '\n');

	for (size_t i{}; i < dias.size(); i++) {
		limparEcra();
		cabecalho();
		cout << endl << endl;

		///hora de inicio
		do {
			textcolor(RED);
			cout << "\n\n\t\t " << dias[i] << ": " << endl;
			textcolor(LIGHT_GRAY);
			cout << "\t\tHora de abertura (hh:mm): ";
			textcolor(WHITE);
			getline(cin, hora_i);
			stringstream ss1(hora_i);
			ss1 >> horas >> car >> minutos;

			if (hora_i.size() == 4)
				hora_i = "0" + hora_i;

			if ((horas < 0) || (horas > 24) || ((horas == 24) && (minutos > 0)) || (minutos < 0) || (minutos >= 60) || (car != ':'))
			{
				avancar = false;
				textcolor(RED);
				cout << "\t\t"<< square <<"hora invalida";
				textcolor(WHITE);
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
			textcolor(LIGHT_GRAY);
			cout << "\t\tHora de encerramento (hh:mm): ";
			textcolor(WHITE);
			getline(cin, hora_f);
			stringstream ss2(hora_f);
			ss2 >> horas >> car >> minutos;

			if (hora_f.size() == 4)
				hora_f = "0" + hora_f;

			if ((horas < 0) || (horas > 24) || ((horas == 24) && (minutos > 0)) || (minutos < 0) || (minutos >= 60) || (hora_f < hora_i) || (car != ':'))
			{
				avancar = false;
				textcolor(RED);
				cout << "\t\t" << square << "hora invalida";
				textcolor(WHITE);
			}
			else {
				avancar = true;
			}


		} while (!avancar);

		string h;
		h = hora_i + " - " + hora_f;
		p1.horariomap[dias[i]] = h;

	}
	mostrar_calendario(p1);

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

	gotoxy(25, y);
	textcolor(YELLOW);
	cout << " ";
	textcolor(WHITE);

	gotoxy(25, y1);
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

		textcolor(LIGHT_GRAY);
		cout << "\n\n\t\t Atualmente: ";
		textcolor(WHITE);
		if (temp.size() == 0)
		{
			textcolor(RED);
			cout << "sem dias de funcionamento ";
			textcolor(WHITE);

		}
		else
		{
			temp = ordena_dias_semana(temp);
			cout << temp[0];
			for (size_t i{ 1 }; i < temp.size(); i++) {
				cout << ", " << temp[i];
			}
		}

		cout << "\n\n\t\t\t  ";
		if (encontra_string_vetor("segunda", temp) != -1)
			cout << " Retirar Segunda" << endl;
		else
			cout << " Adicionar Segunda" << endl;

		cout << "\t\t\t  ";
		if (encontra_string_vetor("terca", temp) != -1)
			cout << " Retirar Terca" << endl;
		else
			cout << " Adicionar Terca" << endl;

		cout << "\t\t\t  ";
		if (encontra_string_vetor("quarta", temp) != -1)
			cout << " Retirar Quarta" << endl;
		else
			cout << " Adicionar Quarta" << endl;

		cout << "\t\t\t  ";
		if (encontra_string_vetor("quinta", temp) != -1)
			cout << " Retirar Quinta" << endl;
		else
			cout << " Adicionar Quinta" << endl;

		cout << "\t\t\t  ";
		if (encontra_string_vetor("sexta", temp) != -1)
			cout << " Retirar Sexta" << endl;
		else
			cout << " Adicionar Sexta" << endl;

		cout << "\t\t\t  ";
		if (encontra_string_vetor("sabado", temp) != -1)
			cout << " Retirar Sabado" << endl;
		else
			cout << " Adicionar Sabado" << endl;

		cout << "\t\t\t  ";
		if (encontra_string_vetor("domingo", temp) != -1)
			cout << " Retirar Domingo" << endl << endl;
		else
			cout << " Adicionar Domingo" << endl << endl;

		cout << "\t\t\t   Concluir" << endl;
		cout << "\t\t\t   Cancelar" << endl;
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

	gotoxy(34, y);
	textcolor(YELLOW);
	cout << " ";
	textcolor(WHITE);

	gotoxy(34, y1);
	textcolor(YELLOW);
	cout << square;
	textcolor(WHITE);

	gotoxy(0, 21);

	return;

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
			cout << "\n\n\t\t Atualmente: ";
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
			cout << "\n\n\t\t Dias de funcionamento:" << endl << endl;
			textcolor(WHITE);
			cout << "\t\t\t\t    Todos os dias" << endl;
			cout << "\t\t\t\t    Dias uteis" << endl;
			cout << "\t\t\t\t    Editar" << endl << endl;
			cout << "\t\t\t\t    Avancar" << endl;
			cout << "\t\t\t\t    Voltar atras" << endl << endl;
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
					textcolor(CYAN);
					cout << "\n Defina os dias de funcionamento antes de avancar! 'Enter' para continuar";
					textcolor(WHITE);
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
		cout << endl;
		textcolor(LIGHT_GRAY);
		cout << "\t\t Lotacao atual: ";
		textcolor(WHITE);
		cout << p1.getLotacao() << endl << endl;
		
		cin.ignore();
		string opcao;
		do {
			textcolor(LIGHT_GRAY);
			cout << "\n\t\t Deseja aterar? ";
			textcolor(WHITE);
			getline(cin, opcao);

		} while ((opcao != "nao") && (opcao != "n") && (opcao != "sim") && (opcao != "s"));


		if ((opcao == "nao") || (opcao == "n")) /// se nao deseja guardar
			return;
	}

	limparEcra();
	cabecalho();

	do
	{
		textcolor(LIGHT_GRAY);
		cout << "\n\t\t Lotacao: ";
		textcolor(WHITE);
		cin >> lotacao;

		if (cin.fail())
		{
			textcolor(RED);
			cout << "\t\t " << square << " Numero invalido \n\n ";
			textcolor(WHITE);
			cin.clear();
			cin.ignore(256, '\n');
		}
		else fim = true;

	} while (!fim);

	textcolor(LIGHT_GREEN);
	cout << "\t\t " << square << " aceite"<< endl;
	textcolor(WHITE);
	Sleep(500);

	p1.setLotacao(lotacao);

	return;

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
		cout << "\t\t Nome atual: ";
		textcolor(WHITE);
		cout << p1.getNome() << endl << endl;
		string opcao;

		//cin.ignore(256, '\n');
		do {
			textcolor(LIGHT_GRAY);
			cout << "\n\t\t Deseja aterar? ";
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
		cout << "\n\t\t Nome da piscina: ";
		textcolor(WHITE);
		getline(cin, nome);

		if (nome != "")
			fim = true;
		else {
			textcolor(RED);
			cout << "\t\t " << square << " Campo obrigatorio!" << endl;
			textcolor(WHITE);
		}


	} while (!fim);
	
	textcolor(LIGHT_GREEN);
	cout << "\t\t " << square << " aceite" << endl;
	textcolor(WHITE);
	Sleep(500);

	p1.setNome(nome);

	return;


}


//3. CRIAR PISCINA
void menu_criar_piscina_ops(int opcao, int opcao_b)
{
	int a = 254;
	char square = a; // obter  █

	int y = 0;
	int y1 = 0;

	if (opcao_b <= 6)
		 y = 9 + opcao_b;
	else y = 10 + opcao_b;
	
	if(opcao <=6)
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
	unsigned int result = 0;
	int opcao = 1, opcao_b = 1, tecla;
	bool imprimir = true;
	string fichPiscina, fichUtentes, fichAulas, fichProfessores;
	Piscina p1;
	vector<Piscina>piscinas = carregar_piscinas();
	int localizacao = 0;

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
			cout << "\t\t\t\t    Definir modalidades" << endl;
			cout << "\t\t\t\t    Definir base de dados" << endl << endl;
			cout << "\t\t\t\t    Concluir e avancar" << endl;
			cout << "\t\t\t\t    Sair" << endl;
			cout << endl << endl << endl << endl;

		}

		imprimir = false;

		menu_criar_piscina_ops(opcao, opcao_b);
		opcao_b = opcao;
		tecla = opcao_valida(opcao, 1, 8);
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
				if (result == 0)
					result  = definir_dias_funcionamento(p1);
				else mostrar_calendario(p1);
				imprimir = true;
				break;

			case 4:
				definir_localizacao(p1);
				localizacao++;
				imprimir = true;
				break;

			case 5:
				definir_modalidades(p1);
				imprimir = true;
				break;
			
			case 6:
				definir_base_de_dados(fichPiscina, fichUtentes, fichAulas, fichProfessores);
				imprimir = true;
				break;

			case 7:
				if (check(p1, fichPiscina, fichProfessores,localizacao))
					menu_geral(p1, fichPiscina, fichUtentes, fichAulas, fichProfessores);
				imprimir = true;
				break;

			case 8:
				return;
				break;
			}

	} while ((opcao != 8) || (tecla != 13));

	cout << endl << endl;
	
	set_prioridades(piscinas, p1);
	p1.setPiscinas_prox(piscinas);

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
	char square = a;
	
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
			menu_criar_piscina();
			imprimir = true;
			break;

		case 2:
			escolher_ficheiros();
			imprimir = true;
			break;

		case 3:
			creditos();
			imprimir = true;
			break;

		case 4:
			return;
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