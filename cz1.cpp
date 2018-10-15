#include <iostream>

class Game{
	private:
	//zmienne
		int x = 1;
		int y = 1;
		int char_max_height_width = 5;
		int padding = 1;
		int width = 50;
		int border_color = 35;
		int block_color = 45;
	//funkcje
		void menu();
		void game_setup();
		void game_paly();
		void game_end();
		void draw_title();
		void draw_o(int x, int y);
		void draw_x(int x, int y);
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
	std::cout << "\033[2J\033";

	this->draw_title();

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


int main(){
	setlocale(LC_ALL, "");

	Game game(4, 2);

	std::cout << "\033[" << 50 << ";" << 50 << "H ";

	return 0;
}
