#include <iostream>

using namespace std;

class Game{

	private:
		// zmienne
			int x;
			int y;
			int menu_x;
			int menu_y;
			int console_x;
			int console_y;
			int width = 81;
			int height = 35;
			// int width = 3;
			// int height = 3;
			//colors
			int font_color = 0;
			int border_color = 35;
			int block_color = 45;
			int focus_color = 33;
			// int bg_color = 43;
			int fields[3][3] = { // 0 = null; 1 = o; 2 = x
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0}
			};
			int chars_x[3];
			int chars_y[3];
			bool in_game = false;
		// metody
			void draw_board();
			void draw_x(int x, int y);
			void draw_o(int x, int y);
			void menu();
			void clear_menu();
			void clear_input();
			int get_usr_inp(int max = 3, int min = 0, string title = "Menu", string opc = "Opcja", string error = "");
			int get_usr_field(string title = "Gracz _", string opc = "Pole", string error="");
			int get_ai_field();
			void draw_console(string title = "Menu", string opc = "Opcja", string error = "");
			void game_setup(int typ); // 0 - gracz vs gracz; 1 - gracz vs pc
			void game_start(int typ, int first = 0); // 0 - losowo; 1 - o; 2 - x;
			void show_stat();
			int end_game(); // 0 - false; 1 - o wins; 2 - x wins; 3 - draw
	public:
		Game(int x = 1, int y = 1);
		~Game();

};
Game::Game(int x, int y){
	this->x = x;
	this->y = y;
	this->menu_x = x + 9;
	this->menu_y = y + 27;
	this->console_x = x + 17;
	this->console_y = y + 27;

	this->chars_x[0] = x + 11;
	this->chars_x[1] = x + 19;
	this->chars_x[2] = x + 27;

	this->chars_y[0] = y + 3;
	this->chars_y[1] = y + 11;
	this->chars_y[2] = y + 19;

	this->draw_board();
	this->menu();
}
Game::~Game(){
	// system("clear");
	// cout << "\033[1;1H\033[0m";
}
void Game::draw_board(){
	//czysci plansze
		system("clear");
		cout << "\033[1;1H\033[0m";

	//rysuje obramowke / wewnetrzne sciany
		cout << "\033[0m\033[" << this->border_color << "m";
		//poziome
		for(int i = 0; i < this->width; i++){
			cout << "\033[" << this->x << ";" << this->y + i << "H\u2550";
			cout << "\033[" << this->x + this->height - 1 << ";" << this->y + i << "H\u2550";

			cout << "\033[" << this->x + 8 << ";" << this->y + i << "H\u2550";

			if(i > 25){
				cout << "\033[" << this->x + 16 << ";" << this->y + i << "H\u2550";
				cout << "\033[" << this->x + 22 << ";" << this->y + i << "H\u2550";
				//rysuje separatory inputa
				cout << "\033[" << this->x + 18 << ";" << this->y + i << "H\u254C";
				cout << "\033[" << this->x + 20 << ";" << this->y + i << "H\u254C";
			}
		}
		//pionowe
		for(int i = 0; i < this->height; i++){
			cout << "\033[" << this->x + i << ";" << this->y << "H\u2551";
			cout << "\033[" << this->x + i << ";" << this->y + this->width - 1 << "H\u2551";
			if(i > 7){
				cout << "\033[" << this->x + i << ";" << this->y + 26 << "H\u2551";
			}
		}

	//rysuje rogi obramowki / skrzyzowania
		cout << "\033[" << this->x << ";" << this->y << "H\u2554";											//tl
		cout << "\033[" << this->x << ";" << this->y + this->width - 1 << "H\u2557";						//tr
		cout << "\033[" << this->x + this->height - 1 << ";" << this->y << "H\u255A";						//bl
		cout << "\033[" << this->x + this->height - 1 << ";" << this->y + this->width - 1 << "H\u255D";		//br
		cout << "\033[" << this->x + 8 << ";" << this->y << "H\u2560";										//pod title l
		cout << "\033[" << this->x + 8 << ";" << this->y + this->width-1 << "H\u2563";						//pod title r
		cout << "\033[" << this->x + 16 << ";" << this->y + 26 << "H\u2560";								//pod menu l
		cout << "\033[" << this->x + 16 << ";" << this->y + this->width-1 << "H\u2563";						//pod menu r
		cout << "\033[" << this->x + 22 << ";" << this->y + 26 << "H\u2560";								//nad stopka l
		cout << "\033[" << this->x + 22 << ";" << this->y + this->width-1 << "H\u2563";						//nad stopka r
		cout << "\033[" << this->x + 8 << ";" << this->y + 26 << "H\u2566";									//prawa od o:x t
		cout << "\033[" << this->x + this->height - 1 << ";" << this->y + 26 << "H\u2569";					//prawa od o:x b


	//rysuje sciany glownej planszy
		for(int i = 0; i < 23; i++){
			//pionowe
				cout << "\033[" << this->x + 10 + i << ";" << this->y + 9 << "H\u2502";
				cout << "\033[" << this->x + 10 + i << ";" << this->y + 17 << "H\u2502";
			//poziome
				cout << "\033[" << this->x + 17 << ";" << this->y + 2 + i << "H\u2500";
				cout << "\033[" << this->x + 25 << ";" << this->y + 2 + i << "H\u2500";
		}
		//skrzyzowania
			cout << "\033[" << this->x + 17 << ";" << this->y + 9 << "H\u253c";		//tl
			cout << "\033[" << this->x + 17 << ";" << this->y + 17 << "H\u253c";	//tr
			cout << "\033[" << this->x + 25 << ";" << this->y + 9 << "H\u253c";		//bl
			cout << "\033[" << this->x + 25 << ";" << this->y + 17 << "H\u253c";	//br

	// 1 2 3 / a b c
		cout << "\033[0m\033[" << this->font_color << "m";

		cout << "\033[" << this->x + 9 << ";" << this->y + 5 << "HA";
		cout << "\033[" << this->x + 33 << ";" << this->y + 5 << "HA";
		cout << "\033[" << this->x + 9 << ";" << this->y + 13 << "HB";
		cout << "\033[" << this->x + 33 << ";" << this->y + 13 << "HB";
		cout << "\033[" << this->x + 9 << ";" << this->y + 21 << "HC";
		cout << "\033[" << this->x + 33 << ";" << this->y + 21 << "HC";

		cout << "\033[" << this->x + 13 << ";" << this->y + 1 << "H1";
		cout << "\033[" << this->x + 13 << ";" << this->y + 25 << "H1";
		cout << "\033[" << this->x + 21 << ";" << this->y + 1 << "H2";
		cout << "\033[" << this->x + 21 << ";" << this->y + 25 << "H2";
		cout << "\033[" << this->x + 29 << ";" << this->y + 1 << "H3";
		cout << "\033[" << this->x + 29 << ";" << this->y + 25 << "H3";

	//title
		cout << "\033[0m\033[" << this->block_color << "m";
		this->draw_o(this->x + 2, this->y + 1 + 17);
		this->draw_x(this->x + 2, this->y + 1 + 3*17 + 5 + 1);
		// i
		cout << "\033[" << this->x + 2 << ";" << this->y + 1 + 2*17 + 5 << "H ";
		cout << "\033[" << this->x + 4 << ";" << this->y + 1 + 2*17 + 5 << "H ";
		cout << "\033[" << this->x + 5 << ";" << this->y + 1 + 2*17 + 5 << "H ";
		cout << "\033[" << this->x + 6 << ";" << this->y + 1 + 2*17 + 5 << "H ";

	//footer
		cout << "\033[0m\033[" << this->block_color - 10 << "m";
		for(int i = 0; i < 11; i++){
			for(int j = 0; j < 53; j++){
				cout << "\033[" << this->x + 23 + i << ";" << this->y + 27 + j << "H\u2571";
			}
		}
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 23; j++){
				cout << "\033[" << this->x + 27 + i << ";" << this->y + 42 + j << "H ";
			}
		}
		cout << "\033[" << this->x + 28 << ";" << this->y + 43 << "HKrzysztof Kukiz \u00A92018";

}
void Game::draw_x(int x, int y){

	cout << "\033[0m\033[" << this->block_color << "m";

	cout << "\033[" << x+0 << ";" << y+0 << "H ";
	cout << "\033[" << x+0 << ";" << y+4 << "H ";

	cout << "\033[" << x+1 << ";" << y+1 << "H ";
	cout << "\033[" << x+1 << ";" << y+3 << "H ";

	cout << "\033[" << x+2 << ";" << y+2 << "H ";

	cout << "\033[" << x+3 << ";" << y+1 << "H ";
	cout << "\033[" << x+3 << ";" << y+3 << "H ";

	cout << "\033[" << x+4 << ";" << y+0 << "H ";
	cout << "\033[" << x+4 << ";" << y+4 << "H ";
}
void Game::draw_o(int x, int y){

	cout << "\033[0m\033[" << this->block_color << "m";

	cout << "\033[" << x+0 << ";" << y+1 << "H ";
	cout << "\033[" << x+0 << ";" << y+2 << "H ";
	cout << "\033[" << x+0 << ";" << y+3 << "H ";

	cout << "\033[" << x+1 << ";" << y+0 << "H ";
	cout << "\033[" << x+1 << ";" << y+4 << "H ";

	cout << "\033[" << x+2 << ";" << y+0 << "H ";
	cout << "\033[" << x+2 << ";" << y+4 << "H ";

	cout << "\033[" << x+3 << ";" << y+0 << "H ";
	cout << "\033[" << x+3 << ";" << y+4 << "H ";

	cout << "\033[" << x+4 << ";" << y+1 << "H ";
	cout << "\033[" << x+4 << ";" << y+2 << "H ";
	cout << "\033[" << x+4 << ";" << y+3 << "H ";
}
void Game::menu(){

	//czysci menu
		this->clear_menu();

	//wypisuje menu
		cout << "\033[" << this->font_color << "m\033[" << this->menu_x + 1 << ";" << this->menu_y + 1 << "H" << "(" << "\033[" << this->focus_color << ";1m" << "1" << "\033[0m\033[" << this->font_color << "m" << ") Gracz vs Gracz \t[wkrótce]";
		cout << "\033[" << this->font_color << "m\033[" << this->menu_x + 2 << ";" << this->menu_y + 1 << "H" << "(" << "\033[" << this->focus_color << ";1m" << "2" << "\033[0m\033[" << this->font_color << "m" << ") Gracz vs PC \t[wkrótce]";
		cout << "\033[" << this->font_color << "m\033[" << this->menu_x + 3 << ";" << this->menu_y + 1 << "H" << "(" << "\033[" << this->focus_color << ";1m" << "3" << "\033[0m\033[" << this->font_color << "m" << ") Statystyki \t[wkrótce]";

		cout << "\033[" << this->font_color << "m\033[" << this->menu_x + 5 << ";" << this->menu_y + 1 << "H" << "(" << "\033[" << this->focus_color << ";1m" << "0" << "\033[0m\033[" << this->font_color << "m" << ") Zakończ.";

	//pobiera wartosc
	int res = this->get_usr_inp(3, 0, "Menu", "Opcja", "To musi być liczba z zakresu 0-3");
	switch(res){
		case 1: this->game_setup(1); break;
		case 2: this->game_setup(2); break;
		case 3: this->show_stat(); break;
	}

}
void Game::clear_menu(){
	cout << "\033[0m";
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 53; j++){
			cout << "\033[" << this->menu_x + i << ";" << this->menu_y + j << "H ";
		}
	}
}
int Game::get_usr_inp(int max, int min, string title, string opc, string error){

	int inp;

	this->draw_console(title, opc);

	cin >> inp;
	while(!cin.good() || inp > max || inp < min){
		this->draw_console(title, opc, error);
		cin.clear();
		cin.ignore(1024, '\n');
		cin >> inp;
	}

	return inp;
}
void Game::draw_console(string title, string opc, string error){

	//clear
		for(int i = 0; i < 53; i++){
			cout << "\033[" << this->console_x + 0 << ";" << this->console_y + i << "H ";
			cout << "\033[" << this->console_x + 2 << ";" << this->console_y + i << "H ";
			cout << "\033[" << this->console_x + 4 << ";" << this->console_y + i << "H ";
		}

	cout << "\033[0m\033[" << this->font_color << "m";
	//title
		cout << "\033[" << this->console_x + 0 << ";" << this->console_y << "H " << title;

	//error
		if(error.length() > 0)
			cout << "\033[" << this->console_x + 4 << ";" << this->console_y << "H " << "\033[31;1mError: \033[" << this->font_color << "m" << error;

	//opc
		cout << "\033[" << this->console_x + 2 << ";" << this->console_y << "H " << opc << ": ";
		cout << "\033[" << this->focus_color << ";1m";

}
void Game::game_setup(int typ){

	//czysci menu
		this->clear_menu();

	//wypisuje menu
		cout << "\033[" << this->font_color << "m\033[" << this->menu_x + 1 << ";" << this->menu_y + 1 << "H" << "(" << "\033[" << this->focus_color << ";1m" << "1" << "\033[0m\033[" << this->font_color << "m" << ") Zaczyna O \t\t[wkrótce]";
		cout << "\033[" << this->font_color << "m\033[" << this->menu_x + 2 << ";" << this->menu_y + 1 << "H" << "(" << "\033[" << this->focus_color << ";1m" << "2" << "\033[0m\033[" << this->font_color << "m" << ") Zaczyna X \t\t[wkrótce]";
		cout << "\033[" << this->font_color << "m\033[" << this->menu_x + 3 << ";" << this->menu_y + 1 << "H" << "(" << "\033[" << this->focus_color << ";1m" << "3" << "\033[0m\033[" << this->font_color << "m" << ") Zaczyna losowy znak \t[wkrótce]";

		cout << "\033[" << this->font_color << "m\033[" << this->menu_x + 5 << ";" << this->menu_y + 1 << "H" << "(" << "\033[" << this->focus_color << ";1m" << "0" << "\033[0m\033[" << this->font_color << "m" << ") Zakończ.";

	//pobiera wartosc
	int res = this->get_usr_inp(3, 0, "Game setup", "Opcja", "To musi być liczba z zakresu 0-3");
	switch(res){
		case 1: this->game_start(typ, 1); break;
		case 2: this->game_start(typ, 2); break;
		case 3: this->game_start(typ, 0); break;
	}

}
void Game::game_start(int typ, int first){
	int cur_play; 	//1 = o; 2 = x
	int abc;
	int fst; //(1 2 3)
	int i_tmp;
	int i_end_game;
	string s_tmp;
	switch(first){
		case 0: cur_play = rand()%2 + 1; break;
		case 1: cur_play = 1; break;
		case 2: cur_play = 2; break;
		default: cur_play = rand()%2 + 1; break;
	}
	//zeruje pola
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			this->fields[i][j] = 0;

	this->in_game = true;
	while(this->in_game){
		//wydrukuj info kto jest aktualnym graczem
			this->clear_menu();

			cout << "\033[" << this->menu_x + 4 << ";" << this->menu_y + 1 << "H\033[0m" << "Wybierz Pole (np. \033[" << this->focus_color <<";1m1B\033[0m lub \033[" << this->focus_color <<";1mc3\033[0m)";
			// cout << "\033[" << this->menu_x + 5 << ";" << this->menu_y + 1 << "H\033[2m" << "Żeby anulować gre napisz \"exit\".";

			if(cur_play == 1){	//o
				i_tmp = this->get_usr_field("Gracz O", "Pole");
			}else{				//x
				if(typ == 1){	// gracz vs gracz
					i_tmp = this->get_usr_field("Gracz X", "Pole");
				}else{			//gracz vs pc
					// i_tmp = this->get_ai_field();
				}
			}
			abc = i_tmp / 10;
			fst = i_tmp % 10;
			this->fields[fst-1][abc-1] = cur_play;
			if(cur_play == 1){
				this->draw_o(this->chars_x[fst-1], this->chars_y[abc-1]);
			}else{
				this->draw_x(this->chars_x[fst-1], this->chars_y[abc-1]);
			}

		//czy koniec gry
			i_end_game = end_game();
			if( i_end_game ) this->in_game = false;

		//zmiana x -> o, lub o -> x
			cur_play = cur_play == 1 ? 2 : 1;
	}

	//wyswietla kto wygral
		string end_msg;
		switch(i_end_game){
			case 1: end_msg = "Wygrało: O"; break;
			case 2: end_msg = "Wygrało: X"; break;
			case 3: end_msg = "Remis"; 		break;
		}
		this->clear_menu();

		cout << "\033[" << this->menu_x + 3 << ";" << this->menu_y + 1 << "H\033[0m" << end_msg;
		cout << "\033[" << this->menu_x + 5 << ";" << this->menu_y + 1 << "H\033[2m" << "Naciśnij Enter by wrucić do menu.";

	//nacisnij enter by wrucic do menu


}
int Game::get_usr_field(string title, string opc, string error){

	string usr_inp;
	int abc;
	int fst;
	
	//konsola
		draw_console(title, opc, error);

	//pobiera od uzytkownika stringa
		cin >> usr_inp;

	//czy jest to exit
	// if( usr_inp == "exit" ){
	// 	this->in_game = false;
	// 	return 0;
	// }

	//czy sa tylko dwa znaki
	if(usr_inp.length() != 2)
		return this->get_usr_field(title, opc, "Nieprawidłowa liczba znaków!");
	

	//czy jest poprawny format: A1, 1A - C3, 3C.  NIE: AA, 11, CC, 33
		//czy sa tylko dozwolone znaki
			for(int i = 0; i < 2; i++){
				switch(usr_inp[i]){
					case '1': case '2': case '3':
					case 'a': case 'b': case 'c':
					case 'A': case 'B': case 'C':
					break;
					default: return this->get_usr_field(title, opc, "Niedozwolony znak! (tylko A,B,C,1,2,3)");
				}
			}
		//ile jest cyfr w opcji (ma byc tylko jedna)
			int ile_cyfr = 0;
			for(int i = 0; i < 2; i++){
				switch(usr_inp[i]){
					case '1': case '2': case '3':
					ile_cyfr++;
					break;
				}
			}
		//jesli inna cyfr niz 1 to od nowa pobiera wartosc
			if(ile_cyfr != 1)
				return this->get_usr_field(title, opc, "Musi być jedna cyfra, i jedna litera!");

	//przekstałcenie formatu na int (a-c = 10-30; 1-3 = 1-3)
		//gdzie jest liczba, gdie litera
			int miejsce_cyfry;
			int miejsce_litery;
			switch(usr_inp[0]){
				case '1': case '2': case '3':
					miejsce_cyfry = 0;
					miejsce_litery = 1;
					break;
				default:
					miejsce_cyfry = 1;
					miejsce_litery = 0;
			}
		//transformuje na wyjsciowy format

			switch(usr_inp[miejsce_litery]){
				case 'a':
				case 'A':
					abc = 1;
					break;
				case 'b':
				case 'B':
					abc = 2;
					break;
				case 'c':
				case 'C':
					abc = 3;
					break;
			}
			switch(usr_inp[miejsce_cyfry]){
				case '1':
					fst = 1;
					break;
				case '2':
					fst = 2;
					break;
				case '3':
					fst = 3;
					break;
			}
	//czy pole nie jest zajete
		if(this->fields[fst-1][abc-1] != 0) return this->get_usr_field(title, opc, "Pole już zajęte!");

	return abc*10 + fst;

}
int Game::get_ai_field(){

}
int Game::end_game(){ // 0 - false; 1 - o wins; 2 - x wins; 3 - draw
	//czy ktos ma 3 w lini
		for(int i = 0; i < 3; i++){
		//pionowe
			if( this->fields[0][i] == this->fields[1][i] && this->fields[1][i] == this->fields[2][i] && this->fields[1][i] != 0) 	return this->fields[0][i];
		//poziome
			if( this->fields[i][0] == this->fields[i][1] && this->fields[i][1] == this->fields[i][2] && this->fields[i][1] != 0) 	return this->fields[i][0];
		}
		//ukosy
			if( this->fields[0][0] == this->fields[1][1] && this->fields[1][1] == this->fields[2][2] && this->fields[1][1] != 0 ) 	return this->fields[1][1];
			if( this->fields[0][2] == this->fields[1][1] && this->fields[1][1] == this->fields[2][0] && this->fields[1][1] != 0 ) 	return this->fields[1][1];

	//czy sa wolne pola
		bool is_0 = false;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if( this->fields[i][j] == 0 ){
					is_0 = true;
					break;
				}
			}
		}
		if(!is_0) 	return 3;
		else		return 0;

}
void Game::show_stat(){

}

int main(){
	setlocale(LC_ALL, "");
	srand(time(NULL));

	Game game(8, 48);

	cout << "\033[50;1H";

	return 0;
}