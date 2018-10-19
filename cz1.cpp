#include <iostream>

class Game{
	private:
	//zmienne
		int x = 1;
		int y = 1;
		int char_max_height_width = 5;
		int padding = 1;
		int width = 80;
		int border_color = 35;
		int block_color = 45;
		int font_color = 35;
	//funkcje
		void menu();
		void game_setup();
		void game_paly();
		void game_end();
		void draw_title();
		void draw_o(int x, int y);
		void draw_x(int x, int y);
		void draw_console(int x, int y, std::string title = "Untitled", std::string opc = "Opcja: ", std::string error = "xd");
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
	int opc_height = opc_inner_height+(2*this->padding);
	int menu_top = this->char_max_height_width + (this->padding*2) + 2;
	std::cout << "\033[2J\033[" << menu_top << ";" << this->y << "H";
	int usr_response;

	//tytul
		this->draw_title();

	//menu
		//color
			std::cout << "\033[0m";
			std::cout << "\033[1;" << this->font_color << "m";
		//opcje
			std::cout << "\033[" << x + menu_top + this->padding + 0 /*pozycja od góry*/ << ";" << y + 1 + this->padding << "H" << "(1) - Gracz vs Gracz \t[Wkrótce]";
			std::cout << "\033[" << x + menu_top + this->padding + 1 /*pozycja od góry*/ << ";" << y + 1 + this->padding << "H" << "(2) - Gracz vs PC \t\t[Wkrótce]";
			std::cout << "\033[" << x + menu_top + this->padding + 2 /*pozycja od góry*/ << ";" << y + 1 + this->padding << "H" << "(3) - Statystyki \t\t[Wkrótce]";
			std::cout << "\033[" << x + menu_top + this->padding + 4 /*pozycja od góry*/ << ";" << y + 1 + this->padding << "H" << "(0) - Wyjdź \t\t\t[Wkrótce]";
		//lewa i prawa scianka
			for(int i = 0; i < opc_height; i++){
				std::cout << "\033[" << (this->x + menu_top + i) << ";" << (this->y) << "H" << "\u2551";
				std::cout << "\033[" << (this->x + menu_top + i) << ";" << (this->y + this->width) << "H" << "\u2551";
			}

	//konsola
		this->draw_console(menu_top + this->x + opc_height, this->y);

	//pobirz odpowiedz
	std::cin >> usr_response;
	while( !std::cin.good() || usr_response  > 3 || usr_response < 0){

	}
	
}
void Game::draw_title(){

	int innerHeight = char_max_height_width + padding*2;
	int i_y_posytion = this->y + (this->width / 2);
	int char_between_space = (this->width - (2 * this->padding) - (2 * this->char_max_height_width))/4;

	//ustawnienie koloru obramowania
		std::cout << "\033[" << this->border_color << ";1m";

	//narysowanie gurnej i dolnej lini
		for(int i = 0; i < width; i++){
			std::cout << "\033[" << (this->x) << ";" << (this->y + i) << "H" << "\u2550";
			std::cout << "\033[" << (this->x + innerHeight + 1) << ";" << (this->y + i) << "H" << "\u2550";
		}

	//narysowanie lewo i prawo
		for(int i = 0; i < innerHeight+2; i++){
			std::cout << "\033[" << (this->x + i) << ";" << (this->y) << "H" << "\u2551";
			std::cout << "\033[" << (this->x + i) << ";" << (this->y + this->width) << "H" << "\u2551";
		}

	//narysowanie naroznikow
		// top left
		std::cout << "\033[" << this->x << ";" << this->y << "H\u2554";
		// top right
		std::cout << "\033[" << this->x << ";" << this->y + this->width << "H\u2557";
		// bot left
		std::cout << "\033[" << this->x + innerHeight + 1 << ";" << this->y << "H\u2560";
		// bot right
		std::cout << "\033[" << this->x + innerHeight + 1 << ";" << this->y + this->width << "H\u2563";

	//narysowanie "o i x"
		std::cout << "\033[" << this->block_color << "m";
		// i
			std::cout << "\033[" << this->x + 1 + this->padding << ";" << i_y_posytion << "H ";
			std::cout << "\033[" << this->x + 3 + this->padding << ";" << i_y_posytion << "H ";
			std::cout << "\033[" << this->x + 4 + this->padding << ";" << i_y_posytion << "H ";
			std::cout << "\033[" << this->x + 5 + this->padding << ";" << i_y_posytion << "H ";
		// o
			this->draw_o( (this->x + 1 + this->padding), (i_y_posytion - char_between_space - this->char_max_height_width) );
		// x
			this->draw_x( (this->x + 1 + this->padding), (i_y_posytion + char_between_space) );
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
		std::cout << "\033[1;" << this->font_color << "m";
	//rysuje gore i dol
		for(int i = 1; i < this->width; i++){
			std::cout << "\033[" << x << ";" << y+i << "H\u2550"; 
			std::cout << "\033[" << x+height+1 << ";" << y+i << "H\u2550"; 
		}
	//rysuje lewo i prawo
		for(int i = 1; i < height+1; i++){
			std::cout << "\033[" << x+i << ";" << y << "H\u2551";
			std::cout << "\033[" << x+i << ";" << y+width << "H\u2551";
		}
	//rysuje rogi
		//top left
			std::cout << "\033[" << x << ";" << y << "H\u2560";
		//top right
			std::cout << "\033[" << x << ";" << y+this->width << "H\u2563";
		//bot left
			std::cout << "\033[" << x+height+1 << ";" << y << "H\u255A";
		//bot right
			std::cout << "\033[" << x+height+1 << ";" << y+this->width << "H\u255D";
	//czysci srodek
	for(int i = 1; i < this->width; i++){
		std::cout << "\033[" << x+1 << ";" << y+i << "H ";
		std::cout << "\033[" << x+3 << ";" << y+i << "H ";
		std::cout << "\033[" << x+5 << ";" << y+i << "H ";
	}
	std::cout << "\033[1;" << this->font_color << "m";
	//rysuje separatory
		for(int i = 1; i < this->width; i++){
			std::cout << "\033[" << x+2 << ";" << y+i << "H\u2508";	
			std::cout << "\033[" << x+4 << ";" << y+i << "H\u2508";	
		}
	//Wypisuje nazwy i zostawia kursor w miejsce na wpisanie
		std::cout << "\033[1;" << this->font_color << "m\033[" << x+1 << ";" << y+this->padding+1 << "H" << title;
		std::cout << "\033[1;" << this->font_color << "m\033[" << x+5 << ";" << y+this->padding+1 << "H" << error;
		std::cout << "\033[1;" << this->font_color << "m\033[" << x+3 << ";" << y+this->padding+1 << "H" << opc;
}


int main(){
	setlocale(LC_ALL, "");

	Game game(4, 2);

	std::cout << "\033[60;1H\n";

	return 0;
}