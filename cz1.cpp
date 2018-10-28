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
		// metody
			void draw_board();
			void draw_x(int x, int y);
			void draw_o(int x, int y);
			void menu();
			void clear_menu();
			void clear_input();
			int get_usr_inp(int max = 3, int min = 0, string title = "Menu", string opc = "Opcja", string error = "");
			void dewa_console(string title = "Menu", string opc = "Opcja", string error = "");
			void game_setup(int typ); // 0 - gracz vs gracz; 1 - gracz vs pc
			void game_start(int typ, int first = 0); // 0 - losowo; 1 - o; 2 - x;
			void show_stat();
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

	std::cout << "\033[" << x+0 << ";" << y+0 << "H ";
	std::cout << "\033[" << x+0 << ";" << y+4 << "H ";

	std::cout << "\033[" << x+1 << ";" << y+1 << "H ";
	std::cout << "\033[" << x+1 << ";" << y+3 << "H ";

	std::cout << "\033[" << x+2 << ";" << y+2 << "H ";

	std::cout << "\033[" << x+3 << ";" << y+1 << "H ";
	std::cout << "\033[" << x+3 << ";" << y+3 << "H ";

	std::cout << "\033[" << x+4 << ";" << y+0 << "H ";
	std::cout << "\033[" << x+4 << ";" << y+4 << "H ";
}
void Game::draw_o(int x, int y){

	std::cout << "\033[" << x+0 << ";" << y+1 << "H ";
	std::cout << "\033[" << x+0 << ";" << y+2 << "H ";
	std::cout << "\033[" << x+0 << ";" << y+3 << "H ";

	std::cout << "\033[" << x+1 << ";" << y+0 << "H ";
	std::cout << "\033[" << x+1 << ";" << y+4 << "H ";

	std::cout << "\033[" << x+2 << ";" << y+0 << "H ";
	std::cout << "\033[" << x+2 << ";" << y+4 << "H ";

	std::cout << "\033[" << x+3 << ";" << y+0 << "H ";
	std::cout << "\033[" << x+3 << ";" << y+4 << "H ";

	std::cout << "\033[" << x+4 << ";" << y+1 << "H ";
	std::cout << "\033[" << x+4 << ";" << y+2 << "H ";
	std::cout << "\033[" << x+4 << ";" << y+3 << "H ";
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
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 53; j++){
			cout << "\033[" << this->menu_x + i << ";" << this->menu_y + j << "H ";
		}
	}
}
int Game::get_usr_inp(int max, int min, string title, string opc, string error){

	int inp;

	this->dewa_console(title, opc);

	cin >> inp;
	while(!cin.good() || inp > max || inp < min){
		this->dewa_console(title, opc, error);
		cin.clear();
		cin.ignore(1024, '\n');
		cin >> inp;
	}

	return 1;
}
void Game::dewa_console(string title, string opc, string error){

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
		cout << "\033[" << this->font_color << "m\033[" << this->menu_x + 1 << ";" << this->menu_y + 1 << "H" << "(" << "\033[" << this->focus_color << ";1m" << "1" << "\033[0m\033[" << this->font_color << "m" << ") Zaczyna O \t\t\t[wkrótce]";
		cout << "\033[" << this->font_color << "m\033[" << this->menu_x + 2 << ";" << this->menu_y + 1 << "H" << "(" << "\033[" << this->focus_color << ";1m" << "2" << "\033[0m\033[" << this->font_color << "m" << ") Zaczyna X \t\t\t[wkrótce]";
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
	bool cur_play; // 0 = o; 1 = x
	bool finished = false;
	switch(first){
		case 0: cur_play = rand()%2; break;
		case 1: cur_play = 0; break;
		case 2: cur_play = 1; break;
	}

	while(!finished){

	}

}
void Game::show_stat(){

}

int main(){
	setlocale(LC_ALL, "");
	srand(time(NULL));

	Game game(2, 6);

	cout << "\033[50;1H";

	return 0;
}