#include "piscina.h"

using namespace std;

Piscina::Piscina() {
}

Piscina::Piscina(string nome, unsigned int NumMaximoUtentes) {
	this->nomePiscina = nome;
	this->NumMaximoUtentes = NumMaximoUtentes;
}

Piscina::~Piscina(){

	for (size_t i=0; i <horario.size();i++){
		delete(horario[i]);
	}

	for (size_t i=0; i <utentes.size();i++){
			delete(utentes[i]);
		}
	for (size_t i=0; i <professores.size();i++){
				delete(professores[i]);
			}

	for (size_t i=0; i <utentesNaPisicina.size();i++){
				delete(utentesNaPisicina[i]);
			}
}

void Piscina::setNome(string nome) {

	this->nomePiscina = nome;

}

void Piscina::setLotacao(unsigned int lotacao) {

	this->NumMaximoUtentes = lotacao;

}

string Piscina::getNome() {
	return nomePiscina;
}

unsigned int Piscina::getLotacao() {
	return NumMaximoUtentes;
}

vector<Utente *> Piscina::getUtentes() {
	return utentes;

}

vector<Utente *> Piscina::getUtentesNaPisicina() {
	return utentesNaPisicina;
}

vector<Professor *> Piscina::getProfessores() {
	return professores;
}

unsigned int Piscina::getNumMaximoUtententes() {
	return NumMaximoUtentes;

}

void Piscina::addUtente(Utente * utente) {
	utentes.push_back(utente);
}

void Piscina::addProfessor(Professor *professor) {

	professores.push_back(professor);

}

void Piscina::atribuiprofs() {
	for (size_t i = 0; i < horario.size(); i++) {
		if (horario[i]->pro()&& horario[i]->getProfessor().getNome()=="")
			horario[i]->setProfessor(professores[i % professores.size()]);

	}

}



void Piscina::ler_FichAulas(string &fichAulas) {
	ifstream fich;
	fich.open(fichAulas);
	int pro;
	string linha, pr;
	getline(fich, linha, ';');
	getline(fich, linha, ';');
	int i = stoi(linha);
	unsigned int id, dia, mes, ano, horas, minutos, horasf, minutosf;
	for (; i > 0; i--) {
		getline(fich, pr, ';');
		getline(fich, linha, ';');
		id = stoi(linha);
		Data data1, data2;
		getline(fich, linha, '/');
		dia = stoi(linha);
		data1.setDia(dia);
		data2.setDia(dia);
		getline(fich, linha, '/');
		mes = stoi(linha);
		data1.setMes(mes);
		data2.setMes(mes);
		getline(fich, linha, ';');
		ano = stoi(linha);
		data1.setAno(ano);
		data2.setAno(ano);
		getline(fich, linha, ':');
		horas = stoi(linha);
		data1.setHoras(horas);
		getline(fich, linha, '-');
		minutos = stoi(linha);
		data1.setMinutos(minutos);
		getline(fich, linha, ':');
		horasf = stoi(linha);
		data2.setHoras(horasf);
		getline(fich, linha, ';');
		minutosf = stoi(linha);
		data2.setMinutos(minutosf);
		cout<<pr<<endl;
		pr=delete_space(pr);
		pro=stoi(pr);
		if (pro == 1) {
			Aula *a1=new AulaPro();
			data1.setDiaSemana();
			data2.setDiaSemana();
			a1->setDuracao(data1-data2);
			a1->setInicio(data1);
			a1->setFim(data2);
			a1->setId(id);

			horario.push_back(a1);

		}

//		if (pr == "L")
		else{
			Aula *a1=new AulaLivre();

			data1.setDiaSemana();
			data2.setDiaSemana();
			a1->setInicio(data1);
			a1->setFim(data2);
			a1->setId(id);
			a1->setDuracao(data1-data2);
			horario.push_back(a1);

		}
	}
fich.close();
horario[horario.size()-1]->setIdloc(horario[horario.size()-1]->getId());
}

void Piscina::utentes_aulas() {

for(size_t i=0;i <utentes.size();i++)
{
	vector <Aula *>aulas_cli;
	aulas_cli=utentes[i]->getaulas();

	for (size_t j=0; j <aulas_cli.size();j++)
	{

		for(size_t k=0; k <horario.size();k++)
		{

			if(aulas_cli[j]->getId()==horario[k]->getId())
			{
				horario[k]->addUtente(utentes[i]);
				break;
			}



		}
	}
}
}

void Piscina::professores_aulas(){
	for(size_t i=0;i <professores.size();i++)
	{
		vector <Aula *>aulas_prof;
		aulas_prof=professores[i]->getaulas();

		for (size_t j=0; j <aulas_prof.size();j++)
		{

			for(size_t k=0; k <horario.size();k++)
			{

				if(aulas_prof[j]->getId()==horario[k]->getId()){
					horario[k]->setProfessor(professores[i]);
					break;}


}
}
}
}

void Piscina::escrever_FichAulas(string &fichAulas)
{
ofstream fich;
fich.open(fichAulas);
fich<< "Aula;"<<endl<< horario.size() << ";"<<endl;

for(size_t i=0; i<horario.size();i++)
{
	stringstream temp;
	fich<<horario[i]->pro()<<";"<<endl;
	fich<<horario[i]->getId()<<";"<<endl;
	Data data,dataf;
	data=horario[i]->getInicio();
	dataf=horario[i]->getFim();
	string datat;
	temp<< data.getDia() << "/" << data.getMes() << "/" << data.getAno()<<";";
	datat=temp.str();
	fich << datat<<endl;
	string hora;
	temp={};
	temp << data.getHoras()<<":"<<data.getMinutos()<<"-" <<dataf.getHoras() <<":"<<dataf.getMinutos() <<";";
	hora=temp.str();
	fich << hora<<endl;
temp.clear();

}

}

vector<Aula *> Piscina::getHorario(){
	return horario;
}

void Piscina::adicionaAula(Aula *aula)
{
	horario.push_back(aula);

}

void Piscina::ler_FichPiscina(string &fichPiscina)
{
	ifstream in;
	string titulo, nome, linha,dia,horas;
	int lotacao,dias;

	in.open(fichPiscina);
	getline(in,titulo);
	getline(in,nome);

	nomePiscina = delete_space(nome);

	getline(in,linha);
	lotacao = stoi(linha);
	linha ="";
	getline(in,linha);
	dias=stoi(linha);
	linha="";
	NumMaximoUtentes = lotacao;
	for(int i=0;i<dias;i++)
	{
		getline(in,linha,'-');
		dia=linha;
		linha="";
		getline(in,linha);
		horas=linha;
		linha="";
		horariomap.insert (pair<string,string>(dia,horas));
		dia="";
		horas="";
	}

	in.close();
}

void Piscina::escrever_FichPiscina(string &fichPiscina)
{
	ofstream ofile(fichPiscina);
	ofile << "Piscina;" <<endl;
	ofile << nomePiscina <<endl;
	ofile << NumMaximoUtentes <<endl;
	ofile << horariomap.size() <<endl;

	for (auto& x: horariomap) {
	    ofile << x.first << "-" << x.second << endl;
	  }

	ofile.close();
}

void Piscina::ler_FichProfessores(string &fichProfessor)
{
	    string contador;
		int i;
		ifstream in;
		string titulo;

		in.open(fichProfessor);

		getline(in,titulo);
		getline(in, contador);
		i=stoi(contador);

		if(i != 0)
		{
			for(int n=0;n < i;n++)
			{
				string nome;
				string line;
				int n_aulas;
				vector<Aula *>aulas;
				vector<int> id;


				getline(in,nome);
				getline(in,line);
				n_aulas=stoi(line);
				int ids;
				for(int k=0;k<n_aulas;k++)
				{
					getline(in,line);
					ids=stoi(line);
					id.emplace_back(ids);
				}
				for(int j = 0;j<id.size();j++)
				{
					for(int a = 0;a < horario.size();a++)
					{
						if(horario[a]->getId() == id[j])
						{
							aulas.push_back(horario[a]);
						}

					}
				}
				Professor *p=new Professor(nome,aulas);
				professores.push_back(p);

			}
		}
		in.close();

}

void Piscina::escrever_FichProfessores(string &fichProfessor)
{

	vector<Aula *>aulas;
	ofstream ofile(fichProfessor);
	ofile << "Professor;" <<endl;
	ofile << professores.size() << endl;
	int n = 0;
	do{
		ofile << professores[n]->getNome()<<endl;
		ofile << professores[n]->getaulas().size()<<endl;
		if (professores[n]->getaulas().size() != 0)
		{
			aulas= professores[n]->getaulas();
			for(int i=0;i<aulas.size();i++)
			{
				ofile << aulas[i]->getId() <<endl;
			}
		}
		n++;
	}while(n <= professores.size() - 1);

  ofile.close();

}

void Piscina::ler_FichUtente(string &fichUtente)
{
	ifstream in;
	int n=0;
	in.open(fichUtente);
	string line,titulo;
	getline(in,titulo);
	getline(in,line);
	n=stoi(line);
	line="";
	if(n != 0){
	for (int i=0;i < n;i++)
	{
		int id=0;
		int naulas=0;
		int entradas=0;
		vector<Aula *>aulas;
		vector<int> ids;
		int idaulas=0;
		string nome;
		getline(in,line);
		id=stoi(line);
		line="";
		getline(in,nome);
		getline(in,line);
		naulas=stoi(line);
		getline(in,line);
		entradas=stoi(line);
		line="";
		for (int k = 0; k < naulas; k++)
		{
			line="";
			getline(in, line);
			idaulas = stoi(line);
			ids.emplace_back(idaulas);
		}
		for (int j = 0; j < ids.size(); j++)
		{
			for (int a = 0; a < horario.size(); a++) {
				if (horario[a]->getId() == ids[j]) {
					aulas.push_back(horario[a]);
				}

			}
		}

		Utente *u=new Utente();
		u->setId(id);
		u->setNome(nome);
		u->setAulas(aulas);
		u->setEntradas(entradas);
		utentes.push_back(u);


	}

}
}

void Piscina::escrever_FichUtente(string &fichUtente)
{
	ofstream ofile(fichUtente);
	ofile << "Utente;" <<endl;
	ofile << utentes.size() << endl;
	for (int i=0;i < utentes.size();i++)
	{
		ofile << utentes[i]->getId() << endl;
		ofile << utentes[i]->getNome()<<endl;
		ofile << utentes[i]->getTotalAulas() <<endl;
		ofile << utentes[i]->getEntradas() << endl;
		for(int j=0;j < utentes[i]->getTotalAulas();j++)
		{

			ofile << utentes[i]->getaulas()[j]->getId() <<endl;
		}

	}

	ofile.close();
}

unsigned int Piscina::atribuiID_utente()
{
	unsigned int id;
	if (utentes.size()==0)
	return 1;
	id= utentes[0]->getId();
	for (size_t i=1; i< utentes.size();i++){
		if (utentes[i]->getId()>id)
			id=utentes[i]->getId();

	}
	id++;
	return id;
}

int Piscina::adicionar_utente(){
	cout <<"Introduza um nome para o novo utente: ";
	string nome;

try{
	getline(cin,nome);
	if(nome.size()<3)
		throw NomeInvalido(nome);

}
catch(Piscina::NomeInvalido(nome)){
	cout << "nome invalido!" << endl;
	return 1;

}


Utente *u1=new Utente();
u1->setNome(nome);
unsigned int id= atribuiID_utente();
u1->setId(id);
addUtente(u1);
return 0;
}

int Piscina::pesquisa_professor(string nome)
{
 int left = 0, right = professores.size() - 1;
 while (left <= right)
 {
 int middle = (left + right) / 2;
 if (professores[middle]->getNome() < nome)
 left = middle + 1;
else if (nome < professores[middle]->getNome())
 right= middle- 1;
else
 return middle; // encontrou
 }
 return -1; // nï¿½o encontrou
}

int Piscina::adicionarProfessor(){
	cout <<"Introduza um nome para o novo professor: ";
	string nome;

try{
	cin >>nome;
	if(nome.size()<3 && pesquisa_professor(nome)==-1)
		throw NomeInvalido(nome);


}
catch(Piscina::NomeInvalido(nome)){
	cout << "nome invalido!" << endl;
	return 1;

}

Professor *p1=new Professor(nome);
addProfessor(p1);
return 0;
}

void Piscina::apaga_prof(string &nome) {
	vector<Aula *> aulas_prof;
	for (size_t i = 0; i < professores.size(); i++)
	{
		if (professores[i]->getNome() == nome)
		{
			aulas_prof = professores[i]->getaulas();
			professores.erase(professores.begin() + i);
		}
	}

	for (size_t i = 0; i < aulas_prof.size(); i++)
	{
		for (size_t j = 0; j < horario.size(); j++)
		{
			if (aulas_prof[i]->getId() == horario[j]->getId())
				horario[j]->setProfessor(professores[i % professores.size()]);
		}
	}
}

int Piscina::apagarProfessor()
{
	cout <<"Introduza o nome do professor que pretende eliminar: ";
		bool ex=true;
		string nome;
	while(ex){
	try{
		cin >>nome;
		if(nome.size()<3)
			throw NomeInvalido(nome);

	}
	catch(Piscina::NomeInvalido(nome)){
		cout << "nome invalido!" << endl;

	}
	}

	apaga_prof(nome);
	return 0;
}

void Piscina::apaga_Utente(string &nome)
{
		int id;
		for (size_t i = 0; i < utentes.size(); i++)
		{
			if (utentes[i]->getNome() == nome)
			{
				id=utentes[i]->getId();
				utentes.erase(utentes.begin() + i);
			}
		}
		for (size_t j=0;j<horario.size();j++)
		{
			for (size_t k=0;k<horario[j]->getUtentes().size();k++)
			{
				if(horario[j]->getUtentes()[k]->getNome() == nome)
				{
					horario[j]->removeUtente(id);
				}

			}

		}

}

int Piscina::apagarUtente()
{
	cout <<"Introduza o nome do Utente que pretende eliminar: ";
			bool ex=true;
			string nome;
		while(ex){
		try{
			cin >>nome;
			if(nome.size()<3)
				throw NomeInvalido(nome);

		}
		catch(Piscina::NomeInvalido(nome)){
			cout << "nome invalido!" << endl;

		}
		}
		cout << "Aulas nao pagas: " << endl;
		for (size_t k=0;k<utentes.size();k++)
		{
			if(utentes[k]->getNome() == nome)
			{
				for (size_t i=0;i < utentes[k]->getaulas().size();i++ )
				{
					cout << utentes[k]->getaulas()[i]->getInicio() <<endl;
					if (utentes[k]->getaulas()[i]->pro())
							{
								cout << utentes[k]->getaulas()[i]->getInicio() << "- Treino" <<endl;
							}
							if (! (utentes[k]->getaulas()[i]->pro()))
							{
								cout << utentes[k]->getaulas()[i]->getInicio() <<"- Aula Livre" <<endl;
							}
				}
				cout << "Valor a pagar: ";
				cout << utentes[k]->totalPrice() << "euros" <<endl;
			}
		}
		apaga_Utente(nome);
		return 0;
}

void Piscina::freq_Utente(Utente *ut)
{
	cout << "Numero de Entradas: " << ut->getEntradas()<<endl;
}

void Piscina::apaga_aula(Aula *a){


	for(size_t i=0; i<horario.size();i++){
		if(horario[i]->getId()==a->getId()){
			horario.erase(horario.begin()+i);
			break;

	}
	}
}

//void ordena_por_data(vector<Aula *> &v)
//{
// for (unsigned int p = 1; p < v.size(); p++)
// {
//	 Aula  *tmp = new Aula();
//  tmp = v[p];
//int j;
//for (j = p; j > 0 && (*tmp) < *(v[j-1]); j--)
// v[j] = v[j-1];
//v[j] = tmp;
// }
//}

bool Piscina::aulaSobreposta(Aula *a1)
{
	for(size_t i=0; i<horario.size();i++)
	{
		if ((horario[i]->getInicio() < a1->getInicio()) && (a1->getInicio() < horario[i]->getFim()))
			return true;

		if ((a1->getInicio() < horario[i]->getInicio()) && (horario[i]->getInicio() < a1->getFim()))
			return true;
	}

	return false;
}




void Piscina::detalhes_aula()
{

	string dia, mes, ano, horas;
	unsigned int dia1, mes1, ano1, horas1, minutos1;
	char lixo;
	bool avancar;
	bool existe = false;
	Data d1;
	string opcao;

	cin.ignore(256, '\n');

	do{
	limparEcra();
	cabecalho();
	cout << endl << endl;



	for(size_t i=0;i < horario.size();i++){
			cout << horario[i]->getInicio()<<endl;
		}
		cout <<endl;
	do {
		cout << "Dia: ";
		getline(cin, dia);
		stringstream ss1;
		ss1 << delete_space(dia);
		ss1 >> dia1;

		cout << "\nMes: ";
		getline(cin, mes);
		stringstream ss2;
		ss2 << delete_space(mes);
		ss2 >> mes1;

		cout << "\nAno: ";
		getline(cin, ano);
		stringstream ss3;
		ss3 << delete_space(ano);
		ss3 >> ano1;

		if (!dia_existe(dia1, mes1, ano1)) {
			cout << "\n\t *dia inexistente" << endl << endl;
		}

	} while (!dia_existe(dia1, mes1, ano1));

	do {
		cout << "\nHora de incio (hh:mm): ";
		getline(cin, horas);
		stringstream ss4;
		ss4 << delete_space(horas);
		ss4 >> horas1 >> lixo >> minutos1;

		if ((horas1 > 23) || ((horas1 == 23) && (minutos1 > 0)) || (minutos1 >= 60) || (lixo != ':')) {
			avancar = false;
			cout << "* hora invalida";
		} else {
			avancar = true;
		}

	} while (!avancar);

	d1.setDia(dia1);
	d1.setMes(mes1);
	d1.setAno(ano1);
	d1.setHoras(horas1);
	d1.setMinutos(minutos1);


	for(size_t i=0;i < horario.size();i++)
	{
		if(horario[i]->getInicio() == d1)
		{
			cout << (*horario[i]) << endl;
			existe =true;

		}
	}

	if(! existe)
	{
		cout <<endl << "Aula inexistente!" << endl;
		system("sleep 3");

	}


}while(! existe);

	cout<< "Prima uma tecla para voltar ao menu anterior: "<<endl;
	cin.ignore();
	getchar();

}


void Piscina::freq_Utente()
{
	bool existe=false;
	do{
		limparEcra();
		cabecalho();
		cout << endl << endl;
		string nome;
		for(size_t i=0;i < utentes.size();i++)
		{
			cout << utentes[i]<<endl;
		}
		cout <<endl << "Nome do cliente pretendido: ";
		getline(cin,nome);
		for (size_t p=0;p<utentes.size();p++)
		{
			if (utentes[p]->getNome() == nome)
			{
				cout << "Numero de aulas atendidas pelo Utente: " << utentes[p]->getEntradas()<<endl;
				existe=true;
				system("sleep 3");
			}

		}
		if(! existe)
			cout << "Utente não encontrado!"<<endl;
	}while(! existe);

}



void Piscina::atribui_profaula(Aula *a){

	unsigned int min=professores[0]->getaulas().size();
	unsigned int min_id=0;
	for(size_t i=1; i<professores.size();i++){
		if(professores[i]->getaulas().size()<min){
			min=professores[i]->getaulas().size();
			min_id=i;
		}

	}
	a->setProfessor(professores[min_id]);

}



void Piscina::remove_utente_napiscina(Utente* u1){

	for(vector<Utente *>::iterator it=utentesNaPisicina.begin();it!=utentes.end();it++){
		if((*it)->getId()==u1->getId()){
			utentesNaPisicina.erase(it);
			break;
		}
	}
}


void Piscina::apaga_aulas(){

	unsigned int id;
	bool existe=false;
	Aula *a1;
	cout << "Insira o id da aula a apagar: ";
	cin >>id;
	cout <<endl;
	while(cin.fail()){
		cerr << " Opcao invalida. Tente de novo.\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >>id;
	}

	for(size_t i=0; i<horario.size();i++){
		if(id==horario[i]->getId()){
			existe=true;
			id=i;
		}
	}
	if(existe){
		a1=horario[id];
		apaga_aula(horario[id]);
		Data d1(dia_do_sistema(),mes_do_sistema(),ano_do_sistema(),horas_do_sistema(),minutos_do_sistema());
		if(d1<a1->getInicio()){
			vector <Utente *> v1=a1->getUtentes();

			for(size_t i=0; i<v1.size();i++){
				v1[i]->ApagaAula(a1);
		}
		}
		cout << "Aula apagada com sucesso!!"<<endl;
		cin.ignore();
			getchar();
			return;
	}
	cout << "Aula não existe!"<<endl;
			cin.ignore();
				getchar();

}

