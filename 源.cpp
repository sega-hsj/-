//�ߵĳ�ʼ����Ϊ3
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
	int direct;//1�ϣ�2�£�3��4��
	snake *next;
	snake *before;
};
class game{
public:
	int **gg;//0��ʾ�޵㣬1��ʾ�е�
	int mapx, mapy;//��ͼ����
	int itemx, itemy;//��Ʒ����
	snake *currentsnake = new snake;
	int fenshu=0;
	int snakelong;//�ߵĳ���	
	snake *snakehead = new snake;
	int gamecondition = 1;//������Ϸ����
	void map(int x, int y){//��ʼ����ͼ
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
	void beginsnake(){//��ʼ����ͷ
		snakelong = 1;
		snakehead->x = mapx / 2;
		snakehead->y = mapy / 2;
		snakehead->direct = 2;
	}
	void longersnake(){//�ߵ���������
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
	void snakepoint(){//���ߵĵ㸳ֵ����ͼ������
		map(mapx, mapy);
		gg[itemx][itemy] = 1;
		currentsnake = snakehead;
		for (int i = 0; i < snakelong; i++){
			gg[currentsnake->x][currentsnake->y] = 1;
			currentsnake = currentsnake->next;
		}
	}
	void item(){//��Ʒ����λ��
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
	void touch(){//��ͷ�Ӵ���Ʒʱ
		if (snakehead->x == itemx && snakehead->y == itemy){
			item();
			longersnake();
			fenshu += 1;
		}
	}
	void play(int a){//��Ҳٿ��ߵķ���
		if (a == 5){ if (snakehead->direct!=2){ snakehead->direct = 1; } }
		if (a == 2){ if (snakehead->direct != 1){ snakehead->direct = 2; } }
		if (a == 1){ if (snakehead->direct != 4){ snakehead->direct = 3; } }
		if (a == 3){ if (snakehead->direct != 3){ snakehead->direct = 4; } }
	}
	void move(){//���ƶ��ķ���//1�ϣ�2�£�3��4��
		currentsnake = snakehead;
		for (int i = 0; i < snakelong - 1; i++){//ѭ������β
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
	void update(){//�����ߵ�״̬��ÿһ�����ƶ���
		currentsnake = snakehead;
		for (int i = 0; i < snakelong - 1; i++){//ѭ������β
			currentsnake = currentsnake->next;
		}
		for (int i = snakelong - 1; i>0; i--){
			currentsnake->direct = currentsnake->before->direct;
			currentsnake = currentsnake->before;
		}
	}
	void ending(){//�����ķ���(ÿһ���ƶ�����ж�)
		currentsnake = snakehead->next;
		for (int i = 0; i < snakelong - 1; i++){
			if (currentsnake->x == snakehead->x&&currentsnake->y == snakehead->y){
				gamecondition = 0;
				cout << "game over"<<endl;
				cout << "��ĵ÷�Ϊ��" << fenshu;
			}
			currentsnake = currentsnake->next;
		}
	}
	void print(){//��ʾ��ǰ��Ļ�ķ���
		system("cls");
		for (int i = 0; i < mapy+1; i++){
			cout << "��";
		}
		cout << endl;
		for (int i = 0; i < mapx; i++){
			cout << "|";
			for (int j = 0; j < mapy; j++){
				
				if (gg[i][j] == 0){
					cout << "  ";
				}
				if (gg[i][j] == 1){
					cout << "��";
				}
			}cout << "|" << endl;
		}
		for (int i = 0; i < mapy+1; i++){
			cout << "��";
		}
		cout << endl << "�÷ַ�����"<<fenshu;
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
	cout << "̰���� version:2.0"<<endl;
	cout << "1.��ͥ�Ų�" << endl;
	cout << "2.��������" << endl;
	cout << "3.�貨΢��" << endl;
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