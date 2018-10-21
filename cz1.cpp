#include <iostream>

class Game{
	private:
	//zmienne
		int x = 1;
		int y = 1;
		int char_max_height_width = 5;
		int width = 80;
		int border_color = 35;
		int block_color = 45;
		// int font_color = 35;
		int font_color = 0;
		int board_width_heigth = 26;
	//funkcje
		void menu();
		void game_setup();
		void game_start(int game_start = 1); // 1 - gracz vs graczl; 2 - gracz vs komputer
		void game_end();
		void draw_title();
		void draw_o(int x, int y);
		void draw_x(int x, int y);
		void draw_console(int x, int y, std::string title = "Untitled", std::string opc = "Opcja: ", std::string error = "");
		void draw_board();
		void draw_footer(int x, int y, int inner_width, int inner_height);
		void gmae_pvp();
	public:
		Game();
		Game(int x, int y);

};
Game::Game(){
	this->menu();
}
Game::Game(int x, int y){
	this->x = x;
	this->y = y;
	this->menu();	
}
void Game::menu(){
	system("clear");
	int opc_inner_height = 5;
	int opc_height = opc_inner_height+2;
	int menu_top = this->char_max_height_width + 4;
	std::cout << "\033[2J\033[" << menu_top << ";" << this->y << "H";
	int usr_response;

	//tytul
		this->draw_title();

	//menu
		//color
			std::cout << "\033[0m";
			std::cout << "\033[1;" << this->font_color << "m";
		//opcje
			std::cout << "\033[" << this->x + menu_top + 1 /*pozycja od góry*/ << ";" << y + 2 + this->board_width_heigth << "H" << "(1) - Gracz vs Gracz \t\t[Wkrótce]";
			std::cout << "\033[" << this->x + menu_top + 2 /*pozycja od góry*/ << ";" << y + 2 + this->board_width_heigth << "H" << "(2) - Gracz vs PC \t\t\t[Wkrótce]";
			std::cout << "\033[" << this->x + menu_top + 3 /*pozycja od góry*/ << ";" << y + 2 + this->board_width_heigth << "H" << "(3) - Statystyki (Gracz vs PC) \t[Wkrótce]";
			std::cout << "\033[" << this->x + menu_top + 5 /*pozycja od góry*/ << ";" << y + 2 + this->board_width_heigth << "H" << "(0) - Wyjdź \t\t\t[Wkrótce]";
		//lewa i prawa scianka
			std::cout << "\033[1;" << this->border_color << "m";
			for(int i = 0; i < opc_height; i++){
				std::cout << "\033[" << (this->x + menu_top + i) << ";" << (this->y) << "H" << "\u2551";
				std::cout << "\033[" << (this->x + menu_top + i) << ";" << (this->y + this->width) << "H" << "\u2551";
			}
	
	//plansza
		this->draw_board();

	//konsola
		this->draw_console(menu_top + this->x + opc_height, this->y + this->board_width_heigth, "Menu", "Opcja: ");

	//footer
		this->draw_footer(this->x + menu_top + 8 + 6, 3*this->char_max_height_width + 14, 53, 11);

	//pobirz odpowiedz
		std::cin >> usr_response;
		while( !std::cin.good() || usr_response  > 3 || usr_response < 0){
			this->draw_console(menu_top + this->x + opc_height, this->y + this->board_width_heigth, "Menu", "Opcja: " ,"\033[1;31mError: \033[" + std::to_string(this->font_color) + "mTo musi być liczba z zakresu 0-3!");
			std::cin.clear();
			std::cin.ignore(1024,'\n');
			std::cin >> usr_response;
		}
		switch(usr_response){
			case 1: this->game_start(1);
		}
	
}
void Game::draw_title(){

	int innerHeight = char_max_height_width + 4;
	int i_y_posytion = this->y + (this->width / 2);
	int char_between_space = (this->width - 2 - (2 * this->char_max_height_width))/4;

	//ustawnienie koloru obramowania
		std::cout << "\033[" << this->border_color << ";1m";

	//narysowanie gurnej i dolnej lini
		for(int i = 0; i < width; i++){
			std::cout << "\033[" << (this->x) << ";" << (this->y + i) << "H" << "\u2550";
			std::cout << "\033[" << (this->x + innerHeight -1) << ";" << (this->y + i) << "H" << "\u2550";
		}

	//narysowanie lewo i prawo
		for(int i = 0; i < innerHeight; i++){
			std::cout << "\033[" << (this->x + i) << ";" << (this->y) << "H" << "\u2551";
			std::cout << "\033[" << (this->x + i) << ";" << (this->y + this->width) << "H" << "\u2551";
		}

	//narysowanie naroznikow
		// top left
		std::cout << "\033[" << this->x << ";" << this->y << "H\u2554";
		// top right
		std::cout << "\033[" << this->x << ";" << this->y + this->width << "H\u2557";
		// bot left
		std::cout << "\033[" << this->x + innerHeight - 1 << ";" << this->y << "H\u2560";
		// bot right
		std::cout << "\033[" << this->x + innerHeight - 1 << ";" << this->y + this->width << "H\u2563";

	//narysowanie "o i x"
		std::cout << "\033[" << this->block_color << "m";
		// i
			std::cout << "\033[" << this->x + 2 << ";" << i_y_posytion << "H ";
			std::cout << "\033[" << this->x + 4 << ";" << i_y_posytion << "H ";
			std::cout << "\033[" << this->x + 5 << ";" << i_y_posytion << "H ";
			std::cout << "\033[" << this->x + 6 << ";" << i_y_posytion << "H ";
		// o
			this->draw_o( (this->x + 2), (i_y_posytion - char_between_space - this->char_max_height_width) );
		// x
			this->draw_x( (this->x + 2), (i_y_posytion + char_between_space) );
}
void Game::draw_o(int x, int y){
	// color
		std::cout << "\033[" << this->block_color << "m";

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
void Game::draw_x(int x, int y){
	// color
		std::cout << "\033[" << this->block_color << "m";

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
void Game::draw_console(int x, int y, std::string title, std::string opc, std::string error){

	int height = 5;
	//color
		std::cout << "\033[1;" << this->border_color << "m";
	//rysuje gore i dol
		for(int i = 1; i < this->width - this->board_width_heigth; i++){
			std::cout << "\033[" << x << ";" << y+i << "H\u2550"; 
			std::cout << "\033[" << x+height+1 << ";" << y+i << "H\u2550"; 
		}
	//rysuje lewo i prawo
		for(int i = 1; i < height+1; i++){
			// std::cout << "\033[" << x+i << ";" << y << "H\u2551";
			std::cout << "\033[" << x+i << ";" << y+this->width - this->board_width_heigth << "H\u2551";
		}
	//rysuje rogi
		//top left
			std::cout << "\033[" << x << ";" << y << "H\u2560";
		//top right
			std::cout << "\033[" << x << ";" << y+this->width-y+2 << "H\u2563";
		//bot left
			std::cout << "\033[" << x+height+1 << ";" << y << "H\u2560";
		//bot right
			std::cout << "\033[" << x+height+1 << ";" << y+this->width-y+2 << "H\u2563";
	//czysci srodek
	for(int i = 1; i < this->width - y+2; i++){
		std::cout << "\033[" << x+1 << ";" << y+i << "H ";
		std::cout << "\033[" << x+3 << ";" << y+i << "H ";
		std::cout << "\033[" << x+5 << ";" << y+i << "H ";
	}
	std::cout << "\033[1;" << this->border_color << "m";
	//rysuje separatory
		for(int i = 1; i < this->width - y+2; i++){
			std::cout << "\033[" << x+2 << ";" << y+i << "H\u2508";	
			std::cout << "\033[" << x+4 << ";" << y+i << "H\u2508";	
		}
	//Wypisuje nazwy i zostawia kursor w miejsce na wpisanie
		std::cout << "\033[1;" << this->font_color << "m\033[" << x+1 << ";" << y+2 << "H" << title;
		std::cout << "\033[1;" << this->font_color << "m\033[" << x+5 << ";" << y+2 << "H" << error;
		std::cout << "\033[1;" << this->font_color << "m\033[" << x+3 << ";" << y+2 << "H" << opc;
}
void Game::draw_board(){
	int menu_top = this->char_max_height_width + 4 + this->x;
	int board_inner_width_heigth = 24;

	//color
		std::cout << "\033[0m";
		std::cout << "\033[1;" << this->border_color << "m";
	//rysuje obramowke
		//lewo prawo
			for(int i = 0; i < this->board_width_heigth; i++){
				std::cout << "\033[" << menu_top + i << ";" << this->y << "H\u2551";
				std::cout << "\033[" << menu_top + i << ";" << this->y + this->board_width_heigth	 << "H\u2551";
			}
		//gora dol
			for(int i = 0; i < this->board_width_heigth; i++){
				//std::cout << "\033[" << menu_top - 1<< ";" << this->y + i<< "H\u2550";
				std::cout << "\033[" << menu_top - 1 + this->board_width_heigth << ";" << this->y + i	 << "H\u2550";
			}
		//narozniki + skrzyrzowania
			std::cout << "\033[" << menu_top + this->board_width_heigth - 1 << ";" << this->y << "H\u255A";
			std::cout << "\033[" << menu_top + this->board_width_heigth - 1 << ";" << this->y + this->board_width_heigth << "H\u2569";
			std::cout << "\033[" << menu_top - 1 << ";" << this->y + this->board_width_heigth << "H\u2566";
	//rysuje separatory
		//linie
			for(int i = 0; i < board_inner_width_heigth-1; i++){
				//poziome
					std::cout << "\033[" << menu_top + this->char_max_height_width + 3 << ";" << this->y + 2+ i << "H\u2500";
					std::cout << "\033[" << menu_top + 2*this->char_max_height_width + 6 << ";" << this->y + 2 + i << "H\u2500";
				//pionowe
					std::cout << "\033[" << menu_top + 1 + i << ";" << this->y + this->char_max_height_width + 4 << "H\u2502";
					std::cout << "\033[" << menu_top + 1 + i << ";" << this->y + 2*this->char_max_height_width + 7 << "H\u2502";
			}
		//skrzyrzowania
			std::cout << "\033[" << menu_top + this->char_max_height_width + 3 << ";" << this->y + this->char_max_height_width + 4 << "H\u253C";
			std::cout << "\033[" << menu_top + 2*this->char_max_height_width +6 << ";" << this->y + this->char_max_height_width + 4 << "H\u253C";
			std::cout << "\033[" << menu_top + this->char_max_height_width + 3 << ";" << this->y + 2*this->char_max_height_width + 7 << "H\u253C";
			std::cout << "\033[" << menu_top + 2*this->char_max_height_width +6 << ";" << this->y + 2*this->char_max_height_width + 7 << "H\u253C";
	
	//rysuje numeracje (a b c / 1 2 3)
		std::cout << "\033[" << this->font_color << "m";
		//a b c
			std::cout << "\033[" << menu_top << ";" << this->y + this->char_max_height_width << "HA";
			std::cout << "\033[" << menu_top << ";" << this->y + 2*this->char_max_height_width + 3 << "HB";
			std::cout << "\033[" << menu_top << ";" << this->y + 3*this->char_max_height_width + 6 << "HC";
			std::cout << "\033[" << menu_top + 3 * this->char_max_height_width + 9 << ";" << this->y + this->char_max_height_width << "HA";
			std::cout << "\033[" << menu_top + 3 * this->char_max_height_width + 9 << ";" << this->y + 2*this->char_max_height_width + 3 << "HB";
			std::cout << "\033[" << menu_top + 3 * this->char_max_height_width + 9 << ";" << this->y + 3*this->char_max_height_width + 6 << "HC";
		//1 2 3
			std::cout << "\033[" << menu_top + 4 << ";" << this->y + 1 << "H1";
			std::cout << "\033[" << menu_top + 7 + this->char_max_height_width << ";" << this->y + 1 << "H2";
			std::cout << "\033[" << menu_top + 10 + 2*this->char_max_height_width << ";" << this->y + 1 << "H3";
			std::cout << "\033[" << menu_top + 4 << ";" << this->y + 10 + 3*this->char_max_height_width << "H1";
			std::cout << "\033[" << menu_top + 7 + this->char_max_height_width << ";" << this->y + 10 + 3*this->char_max_height_width << "H2";
			std::cout << "\033[" << menu_top + 10 + 2*this->char_max_height_width << ";" << this->y + 10 + 3*this->char_max_height_width << "H3";
}
void Game::draw_footer(int x, int y, int inner_width, int inner_height){

	//color
		std::cout << "\033[0m";
		std::cout << "\033[1;" << this->border_color << "m";

	//prawa sciana
		for(int i = 0; i < inner_height; i++){
			std::cout << "\033[" << x + i << ";" << y + inner_width << "H\u2551";
		}
	//dolna sciana
		for(int i = 0; i < inner_width; i++){
			std::cout << "\033[" << x + inner_height << ";" << y + i << "H\u2550";
		}
	//naroznik
		std::cout << "\033[" << x + inner_height << ";" << y + inner_width << "H\u255D";
	//wypelnienie
		for(int i = 0; i < inner_height; i++){
			for(int j = 0; j < inner_width; j++){
				std::cout << "\033[" << x + i << ";" << y+j << "H\u2571";
			}
		}
}
void Game::game_start(int opc){

	//czysci poprzednia plansze
		system("clear");
		std::cout << "\033[2J\033[" << this->x << ";" << this->y << "H";

	//tytul
		this->draw_title();

	//plansza
		this->draw_board();

}


int main(){
	setlocale(LC_ALL, "");

	Game game(4, 2);

	std::cout << "\033[60;1H\n";

	return 0;
}