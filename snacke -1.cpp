#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>
using namespace std;
//-----------properties--------------//
enum Direction { Top = 1, Down, Right, Left };
struct map { int len, width, fruit_len , fruit_width; };
struct snak {
	int tail_len, head_width, head_len
		, Tail_y[50], Tail_x [50] ; Direction dir;
};
struct player { bool lose = true; int score; };
map map1; snak snak1; player player1;
//----------------------------//
void Fruit_options();
void Fruit_options();
void Setup();
void Tail_shift(int [], int);
void draw();
void input();
void moving();
int main() {
	
	Setup();
	while (player1.lose) {

 	draw();
	input();
	moving();
	Sleep(70);
	
	}
	//ssystem("pause");

	return 0;

}

void Fruit_options() {
	srand(time(NULL));
	map1.fruit_len = rand() % (map1.len - 2) + 1;
	map1.fruit_width = rand() % (map1.width - 2) + 1;
}

void Setup() {
	map1.len = 20;
	map1.width = 40;
	snak1.head_len = map1.len / 2;
	snak1.head_width = map1.width / 2;
	Fruit_options();
	snak1.tail_len = 0;
	player1.score = 0;

}

void Tail_shift (int arr[] ,int size) {
	for (int i = size - 2; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
}

void draw() {
	system("cls");

	for (int i = 0; i <= map1.len; i++) {
		for (int j = 0; j <= map1.width; j++) {
			if (i == 0  || i == map1.len  ) {
				cout << "-";
			}
			else if (j == 0 || j == map1.width) {
				cout << "|";
			}
			else if (snak1.head_width == j &&	
				snak1.head_len == i) 
			{
				cout << "O";
			}
			else if (map1.fruit_len == i &&
				map1.fruit_width == j) {
				cout << "+";
			}
			else {
				bool X = false;int xx = 0;
				for (int G = 0; G < snak1.tail_len; G++) {
					if (snak1.Tail_y[G] == i && snak1.Tail_x[G] == j) {
						cout << "*";
						X = true;
						break;
					}
				}
				if (!X) cout << " ";

			}
			
		}
		cout << endl;
	}
		cout <<"Your score is : " << player1.score<<endl;
		cout << "Press 'z' to end  ";
}

void input() {
	if (_kbhit()) {
		char c = _getch();
		switch (c)
		{
		case 'w': snak1.dir = Top; break;
	    case's': snak1.dir = Down; break;
		case 'd': snak1.dir = Right; break;
		case 'a': snak1.dir = Left; break;
		case 'z': exit(0);
		}
		

	}
}

void moving() {

	Tail_shift(snak1.Tail_y, 50);
	Tail_shift(snak1.Tail_x, 50);
	snak1.Tail_y[0] = snak1.head_len;
	snak1.Tail_x[0] = snak1.head_width;

	switch (snak1.dir) {

	case Top: snak1.head_len--; break; 
	case Down: snak1.head_len++; break;
	case Right:snak1.head_width++; break;
	case Left: snak1.head_width--; break;

	}
	
	if (snak1.head_len >= map1.len || snak1.head_len ==0||
		snak1.head_width == 0 || snak1.head_width >= map1.width
		) {
		player1.lose = false;
	}
	else if (snak1.head_len == map1.fruit_len &&
		snak1.head_width == map1.fruit_width) {
		Fruit_options ();
		player1.score++;
		snak1.tail_len++;
	}
}
