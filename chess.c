#include <stdio.h>
#include <stdlib.h> 

int lastX = 3; 
int lastY = 3; 
int stone = 1; 
int e = 0;

const char* stoneNames[] = {"", "King", "Queen", "Rook", "Bishop", "Knight"};

int match(const char* s1, const char* s2) {
    for (int i = 0; s1[i] != '\0' || s2[i] != '\0'; i++) {
        if (s1[i] != s2[i]) return 0;
    }
    return 1;
}

int getCounts(int x, int y) {
    int dx = x - lastX;
    int dy = y - lastY;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;

    if (dx == 0 && dy == 0) return 0; 

    switch(stone) {
        case 1: return (dx <= 1 && dy <= 1);
        case 2: return (dx == dy || dx == 0 || dy == 0);
        case 3: return (dx == 0 || dy == 0);
        case 4: return (dx == dy);
        case 5: return ((dx == 2 && dy == 1) || (dx == 1 && dy == 2));
        default: return 0;
    }
}

void printBoard() {
    printf("\n    ");
    for (int i = 0; i < 8; i++) printf(" %d  ", i); 
    
    printf("\n   +");
    for (int i = 0; i < 8; i++) printf("---+"); 
    printf("\n");

    for (int i = 0; i < 8; i++) {
        printf(" %d |", i);
        
        for (int j = 0; j < 8; j++) {
            if (j == lastX && i == lastY) { 
                printf(" O |"); 
            } else if (getCounts(j, i)) { 
                printf(" X |"); 
            } else {
                printf("   |"); 
            }
        }
        
        printf("\n   +");
        for (int j = 0; j < 8; j++) printf("---+");
        printf("\n");
    }
}

void chooseStone() {
    printf("\n체스 말을 선택하세요\n");
    printf("(1:King, 2:Queen, 3:Rook, 4:Bishop, 5:Knight): ");
    if (scanf("%d", &stone) != 1 || stone < 1 || stone > 5) {
        stone = 1; 
        while (getchar() != '\n'); 
    }
}

int stoneLocation() {
    if (e == 1) {
        printf("정확한 좌표를 입력해주세요.\n");
        e = 0;
    } else if (e == 2) {
        printf("범위를 벗어났습니다.\n");
        e = 0;
    } else if (e == 3) {
        printf("이동 규칙에 어긋납니다.\n");
        e = 0;
    }

    printf("%s입니다.\n", stoneNames[stone]);
    printf("좌표 입력(교체, 종료) :");

    char input[20];
    scanf("%s", input); 

    if (match(input, "종료")) return -1;
    if (match(input, "교체")) return 2;

    if (input[0] < '0' || input[0] > '9') {
        e = 1;
        while (getchar() != '\n'); 
        return 0;
    }

    int x = atoi(input); 
    int y;
    
    if (scanf("%d", &y) != 1) {
        e = 1;
        while (getchar() != '\n'); 
        return 0;
    }
    while (getchar() != '\n');

    if (x < 0 || x > 7 || y < 0 || y > 7) {
        e = 2;
        return 0;
    }

    if (getCounts(x, y)) {
        lastX = x;
        lastY = y;
        return 1;
    } else {
        e = 3;
        return 0;
    }
}

int main() {
    chooseStone(); 
    printf("\n게임 시작 (X는 이동 가능한 경로입니다)\n");

    while (1) {
        printBoard();
        int status = stoneLocation();       
        
        if (status == -1) {
            printf("\n종료\n");
            break;
        } 
        else if (status == 2) {
            chooseStone();
            printf("%s로 교체\n", stoneNames[stone]);
        }
    }
    return 0;
}