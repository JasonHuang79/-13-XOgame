#include<stdio.h>
#include<iostream>
#include<windows.h>

//输出菜单
void MENU() {
	printf("**************************\n");
	printf("******	井字棋游戏  ******\n");
	printf("**************************\n");
	printf("******	1:开始游戏  ******\n");
	printf("******	2:退出游戏  ******\n");
	printf("******	3:游戏规则  ******\n");
	printf("**************************\n");
	
	printf("\n");
}

//清空屏幕
void clear_screen() {
	printf("\033[2J\033[1;1H");
}

//加载进度
void prepare() {
	printf("游戏加载中.....\n");
	int cnt;
	for (cnt = 0; cnt < 110; cnt += 10) {
		printf("进度：%d/100......\n", cnt);
		Sleep(500);//延迟500ms输出；
	}
	printf("游戏开始！！");
	Sleep(1000);
	clear_screen();//调用清屏函数；
}

//输出棋盘
void game_pre(int NUM[3][3]/*棋盘大小3*3*/, int row, int col) {
	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			if (NUM[row][col] == 0)
				printf("口");/*数组初值为0，该位置输出口*/
			else if (NUM[row][col] == 1) {
				printf("O ");//数组被赋值为1，该位置输出O；
			}
			else if (NUM[row][col] == -1) {
				printf("X ");//数组被赋值为-1，该位置输出X；
			}
		}
		printf("\n");
	}
}

int game() {
	int NUM[3][3]= { {0,0,0},{0,0,0},{0,0,0} };//定义数组，并为数组赋初值为0；
	int row=3,col=3;//定义棋盘行列
	game_pre(NUM, row, col);//将棋盘大小、数组传给game_pre函数，生成棋盘
	
	int turn = 1;//定义回合数
	int i;
	for (turn = 1; turn < 10; turn++)/*遍历9次，输入1/-1*/ {
		
		while (turn % 2 != 0) {//奇数轮，p1下棋
			printf("请P1下棋\n");
			scanf_s("%d %d", &row, &col);
			if (row > 2 || col > 2) {//超出棋盘范围，重新输入
				printf("请重新输入\n");
				scanf_s("%d %d", &row, &col);
			}
			if (NUM[row][col]!=0) {//若该位置已经写入，重新输入
				printf("请重新输入\n");
				scanf_s("%d %d", &row, &col);
			}
			NUM[row][col] = 1;//对输入位置赋值为1
			
			clear_screen();//清屏
			game_pre(NUM, row, col);//刷新棋盘状态
			break;//结束p1下棋；
		}
		while (turn % 2 == 0) {//偶数轮，p2下棋
			printf("请P2下棋\n");
			scanf_s("%d%d", &row, &col);
			if (row > 2 || col > 2) {//超出棋盘范围，重新输入
				printf("请重新输入\n");
				scanf_s("%d %d", &row, &col);
			}
			if (NUM[row][col]!=0) {//若该位置已经写入，重新输入
				printf("请重新输入\n");
				scanf_s("%d %d", &row, &col);
			}
			NUM[row][col] = -1;//对输入位置赋值为1
			
			clear_screen();//清屏
			game_pre(NUM, row, col);//刷新棋盘状态
			break;
		}
		//判断是否胜利
		/*
		*100	100	*111	001
		 100	010	 000	010	---->共四种胜利条件，*号条件有三种情况（三行/三列）
		 100	001	 000	100
		*/
		for (i = 0; i < 3; i++) /*遍历三行/三列*/ {
			//判断p1四种情况是否成立
			if (NUM[i][0] + NUM[i][1] + NUM[i][2] == 3||NUM[0][0] + NUM[1][1] + NUM[2][2] == 3||NUM[0][i] + NUM[1][i] + NUM[2][i] == 3|| NUM[0][2] + NUM[1][1] + NUM[2][0] == 3) {
				printf("P1 WON!!\n本次游戏结束!\n\n");
				return 1;//返回1
				
			}
			//判断p2四种情况是否成立
			if (NUM[i][0] + NUM[i][1] + NUM[i][2] == -3|| NUM[0][0] + NUM[1][1] + NUM[2][2] == -3 || NUM[0][i] + NUM[1][i] + NUM[2][i] == -3 || NUM[0][2] + NUM[1][1] + NUM[2][0] == -3) {
				printf("P2 WON!!\n本次游戏结束!\n\n");
				return 1;//返回1
				
			}
		}
	}
	//若9次输入后，胜利情况不成立
	printf("平局\n\n");
	return 1;//返回1
}


int main() {
	int begin = 0;
	do 
	{
		begin++;
		MENU();//调用MENU函数，输出菜单
	} while (begin==0);
	int menu;//定义操作指令数字
	printf("请输入操作数字\n");
		scanf_s("%d", &menu);
	if(menu == 2) /*menu==2，退出游戏*/ {
		return 0;
		//exit(0);//可以使用exit函数退出
	}
	if(menu==3)/*menu==3，输出规则*/ {
		printf("规则：text\n");//输出游戏规则
		printf("请重新输入操作数字！\n");
		//menu = 0;
		scanf_s("%d", &menu);
	}
	if (menu != 1 && menu != 2 && menu != 3) /*menu不为123的情况*/ {
		menu = 0;
		printf("请重新输入操作数字！\n");
		scanf_s("%d", &menu);
	}
	if(menu == 1) /*menu==1，开始游戏*/ {
		prepare();//调用prepare函数，其实没什么用，显得高级一点
		game();//调用game函数，生成游戏
	}
	while (game) /*game函数结束返回值为1，重启main*/ {
			main();//调用main自身重启
	}
	
	return 0;
}