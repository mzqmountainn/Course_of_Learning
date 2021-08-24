#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
int main(void) {
	int in;
	HWND hWnd;
	DWORD Pid;
	HANDLE HProcess = 0;
	while (1) {
		printf("1  C\n");
		scanf("%d", &in);
		//if (in == 1) {
			hWnd = FindWindow(NULL, "Plants vs.Zombies");
			if (hWnd != 0) {
				GetWindowThreadProcessId(hWnd, &Pid);
				HProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
				if (HProcess == 0) {
					printf("failed\n");
				}
				else { printf("succeed get process\n"); }
			}
		//}

	}
}