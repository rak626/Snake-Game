#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<unistd.h>
using namespace std;

bool gameover;
const int width = 50;
const int height = 20;
int x,y,fruitx,fruity,score;
int tailx[100],taily[100];
int ntail = 0;

enum edirection { STOP = 0 , LEFT , RIGHT , UP , DOWN};
edirection dir;
void setup(){
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitx = rand() % width;
	fruity = rand() % height;
	score = 0;
}

void draw(){
	system("cls");
	for(int i = 0 ; i < width ; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++){
		for(int j = 0; j < width + 2 ; j++){
			if(j == 0 || j == width - 1)
				cout << "#";
			else if( i == y && j == x)
				cout << "0";
			else if( i == fruity && j == fruitx)
				cout << "F";
			else{
				for(int k = 0 ;k < ntail ; k++){
					 if(tailx[k] == j && taily[k] == i){
						cout << "o";
					}
				}
				cout << " ";
			}
		}
		cout << endl;
	}
	
	for(int i = 0 ; i < width ; i++)
		cout << "#";
	cout << endl;
	cout << endl;
	cout <<"Score : " << score << endl;
}

void input(){
	if(_kbhit()){
		cout << "here";
		switch(_getch()){
			case 'a' : dir = LEFT;break;
			case 'd' : dir = RIGHT;break;
			case 'w' : dir = UP;break;
			case 's' : dir = DOWN;break;
			case 'q' : gameover = true;break;
		}
	}
}
void logic(){
	if(ntail > 0){
		int prevx = tailx[0];
		int prevy = taily[0];
		tailx[0] = x;
		taily[0] = y;
		for(int i = 1; i < ntail ; i++){
			int prev2x = tailx[i];
			int prev2y = taily[i];
			tailx[i] = prevx;
			taily[i] = prevy;
			prevx = prev2x;
			prevy = prev2y;
		}
	} 
	switch(dir){
		case LEFT : x--;break;
		case RIGHT : x++;break;
		case UP : y--;break;
		case DOWN : y++;break;
		default : break;
	}
	if(x >= width || x < 1 || y < -1 || y >= height){
		gameover = true;
	}
	for(int i = 0 ; i < ntail ; i++){
		if(tailx[i] == x && taily[i] == y){
			gameover = true;
		}
	} 
	if(x == fruitx && y == fruity){
		score++;
		fruitx = rand() % width;
		fruity = rand() % height;
		ntail++;
	}
	
		
}
int main(){
	setup();
	while(!gameover){
		draw();
		input();
		logic();
		sleep(0.80);
	}
	return 0;
}
