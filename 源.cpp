//蛇的初始长度为3
#include<iostream>
#include<stdio.h>
#include<time.h>
#include<windows.h>
using namespace std;
int num;
int *zhizhen = &num;
class snake{
public:
	int x, y;
	int direct;//1上，2下，3左，4右
	snake *next;
	snake *before;
};
class game{
public:
	int **gg;//0表示无点，1表示有点
	int mapx, mapy;//地图参数
	int itemx, itemy;//物品坐标
	snake *currentsnake = new snake;
	int fenshu=0;
	int snakelong;//蛇的长度	
	snake *snakehead = new snake;
	int gamecondition = 1;//控制游戏结束
	void map(int x, int y){//初始化地图
		mapx = x;
		mapy = y;
		gg = new int*[x];
		for (int i = 0; i < x; i++){
			gg[i] = new int[y];
		}
		for (int i = 0; i < x; i++){
			for (int j = 0; j < y; j++){
				gg[i][j] = 0;
			}
		}
	}
	void beginsnake(){//初始化蛇头
		snakelong = 1;
		snakehead->x = mapx / 2;
		snakehead->y = mapy / 2;
		snakehead->direct = 2;
	}
	void longersnake(){//蛇的增长方法
		snake *asnake = new snake; 
		currentsnake = snakehead;
		for (int i = 0; i < snakelong - 1; i++){
			currentsnake = currentsnake->next;
		}
		currentsnake->next = asnake;
		asnake->before = currentsnake;
		asnake->direct = currentsnake->direct;
		if (asnake->direct == 3){
			asnake->x = (currentsnake->x);
			asnake->y = (currentsnake->y + 1) % mapy;
		}
		else if (asnake->direct == 4){
			asnake->x = (currentsnake->x);
			if (currentsnake->y - 1 >= 0){
				asnake->y = (currentsnake->y - 1);
			}
			else{
				asnake->y = mapy - 1;
			}
		}
		else if (asnake->direct == 1){
			asnake->x = (currentsnake->x + 1) % mapx;
			asnake->y = (currentsnake->y);
		}
		else if (asnake->direct == 2){
			if (currentsnake->x - 1 >= 0){
				asnake->x = (currentsnake->x - 1);
			}
			else{ asnake->x = mapx - 1; }
			asnake->y = (currentsnake->y);
		}
		snakelong += 1;
	}
	void snakepoint(){//把蛇的点赋值到地图数组上
		map(mapx, mapy);
		gg[itemx][itemy] = 1;
		currentsnake = snakehead;
		for (int i = 0; i < snakelong; i++){
			gg[currentsnake->x][currentsnake->y] = 1;
			currentsnake = currentsnake->next;
		}
	}
	void item(){//物品出现位置
		int x, y;
		srand((unsigned)time(NULL));
		do{
			x = rand() % mapx;
			y = rand() % mapy;
		} while (gg[x][y] == 1);
		itemx = x;
		itemy = y;
		gg[itemx][itemy] = 1;
	}
	void touch(){//蛇头接触物品时
		if (snakehead->x == itemx && snakehead->y == itemy){
			item();
			longersnake();
			fenshu += 1;
		}
	}
	void play(int a){//玩家操控蛇的方法
		if (a == 5){ if (snakehead->direct!=2){ snakehead->direct = 1; } }
		if (a == 2){ if (snakehead->direct != 1){ snakehead->direct = 2; } }
		if (a == 1){ if (snakehead->direct != 4){ snakehead->direct = 3; } }
		if (a == 3){ if (snakehead->direct != 3){ snakehead->direct = 4; } }
	}
	void move(){//蛇移动的方法//1上，2下，3左，4右
		currentsnake = snakehead;
		for (int i = 0; i < snakelong - 1; i++){//循环到蛇尾
			currentsnake = currentsnake->next;
		}
		for (int i = snakelong - 1; i>0; i--){
			currentsnake->x = currentsnake->before->x;
			currentsnake->y = currentsnake->before->y;
			currentsnake = currentsnake->before;
		}
		if (snakehead->direct == 3){
			snakehead->x = (snakehead->x);
			if (snakehead->y - 1 >= 0){
				snakehead->y = (snakehead->y - 1);
			}
			else{
				snakehead->y = mapy - 1;
			}
		}
		else if (snakehead->direct == 4){
			snakehead->x = (snakehead->x);
			snakehead->y = (snakehead->y + 1) % mapy;
		}
		else if (snakehead->direct == 1){
			snakehead->y = (snakehead->y);
			if (snakehead->x - 1 >= 0){
				snakehead->x = (snakehead->x - 1);
			}
			else{
				snakehead->x = mapx - 1;
			}
		}
		else if (snakehead->direct == 2){
			snakehead->x = (snakehead->x + 1) % mapx;
			snakehead->y = (snakehead->y);
		}
		//update();
	}
	void update(){//更新蛇的状态（每一次蛇移动后）
		currentsnake = snakehead;
		for (int i = 0; i < snakelong - 1; i++){//循环到蛇尾
			currentsnake = currentsnake->next;
		}
		for (int i = snakelong - 1; i>0; i--){
			currentsnake->direct = currentsnake->before->direct;
			currentsnake = currentsnake->before;
		}
	}
	void ending(){//死亡的方法(每一次移动玩才判定)
		currentsnake = snakehead->next;
		for (int i = 0; i < snakelong - 1; i++){
			if (currentsnake->x == snakehead->x&&currentsnake->y == snakehead->y){
				gamecondition = 0;
				cout << "game over"<<endl;
				cout << "你的得分为：" << fenshu;
			}
			currentsnake = currentsnake->next;
		}
	}
	void print(){//显示当前屏幕的方法
		system("cls");
		for (int i = 0; i < mapy+1; i++){
			cout << "—";
		}
		cout << endl;
		for (int i = 0; i < mapx; i++){
			cout << "|";
			for (int j = 0; j < mapy; j++){
				
				if (gg[i][j] == 0){
					cout << "  ";
				}
				if (gg[i][j] == 1){
					cout << "■";
				}
			}cout << "|" << endl;
		}
		for (int i = 0; i < mapy+1; i++){
			cout << "—";
		}
		cout << endl << "得分分数："<<fenshu;
	}
};
DWORD WINAPI Fun(LPVOID lpParamter)
{
	while (1){
	cin >> *zhizhen;}
	return 0;	
}
int main(){
	game agame;
	agame.map(15, 30);
	agame.beginsnake();
	agame.longersnake();
	agame.longersnake();
	agame.snakepoint();
	agame.item();
	cout << "贪吃蛇 version:2.0"<<endl;
	cout << "1.闲庭信步" << endl;
	cout << "2.正常步速" << endl;
	cout << "3.凌波微步" << endl;
	int a;
	do{ cin >> a; } while (a != 1 && a != 2 && a != 3);
	HANDLE hThread = CreateThread(NULL, 0, Fun, zhizhen, 0, NULL);
	CloseHandle(hThread);
	agame.print();
	while (agame.gamecondition > 0){
		agame.move();
		agame.update();
		agame.touch();
		agame.snakepoint();
		agame.print();
		agame.ending();
		Sleep(500 - 120 * a);
		agame.play(*zhizhen);
	}
	system("pause");
	return 0;
}