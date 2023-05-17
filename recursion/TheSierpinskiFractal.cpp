#include <iostream>

void drawNthLine(int i, int n) {
    if (n == 1) {
        if (i == 1) {
            printf(" /\\");
        } else {
            printf("/__\\");
        }
    }
    else if (i <= (1 << (n-1))) {
        for (int j = 0; j < (1 << (n-1)); ++j)
            putchar(' ');
        drawNthLine(i, n-1);
    }
    else {
        drawNthLine(i - (1 << (n-1)), n-1);
        for (int j = 0; j < (1 << n) - i; ++j)
            putchar(' ');
        drawNthLine(i - (1 << (n-1)), n-1);
    }
}

void drawFractal(int n) {
    for (int i = 1; i <= (1 << n); ++i) {
        drawNthLine(i, n);
        putchar('\n');
    }
}

int main() {
    int n;
    while (std::cin >> n && n != 0) {
        drawFractal(n);
        putchar('\n');
    }
    return 0;
}