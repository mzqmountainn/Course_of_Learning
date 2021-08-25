#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
int main(void) {
	int in;
	HWND hWnd;
	DWORD Pid;
	HANDLE HProcess = 0;
	while (1) {
		printf("1.初始化  2.修改太阳\n");
		scanf("%d", &in);
		if (in == 1) {
			hWnd = FindWindow(NULL, "Plants vs. Zombies");
			if (hWnd != 0) {
				GetWindowThreadProcessId(hWnd, &Pid);
				HProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
				if (HProcess == 0) {
					printf("failed\n");
				}
				else { printf("succeed get process\n"); }
			}
		}
		if (in == 2) {
			if (HProcess == 0) {
				printf("请先初始化\n");
			}
			else
			{
				DWORD sun;
				DWORD sunadd = 0x248B2BE8;
				printf("你想要多少太阳？\n");
				scanf("%d", &sun);
				DWORD res = WriteProcessMemory(HProcess, (LPVOID)sunadd, &sun, 4, 0);
				if (res)
				{
					printf("succeed\n");

				}
				else
				{
					printf("failed\n");
				}

			}
		}

	}
}