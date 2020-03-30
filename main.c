#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RESET "\x1b[0m"

#define PIXEL '#'

int columns = 80;
int rows = 25;

void drawMandelbrot(int iterations, double offset[], double zoom);

int main()
{
    printf("Enter the size of your terminal:\n");
    printf("Columns:\n");
    scanf("%d", &columns);
    printf("Rows:\n");
    scanf("%d", &rows);
    while (getchar() != '\n');

    double offset[] = {0, 0};
    unsigned i = 100;
    unsigned zoom = 25;
    char loop = 1;
    while (loop)
    {
        drawMandelbrot(i, offset, zoom);
        printf("WASD keys: move around, +-: zoom in/out, eq: double/half iterations, r: reset, z: exit\n");
        char key = getchar();
        while (getchar() != '\n');
        switch (key | 32)
        {
            case 'w':
                offset[1] -= 100.0 / zoom;
                break;

            case 'a':
                offset[0] -= 100.0 / zoom;
                break;

            case 's':
                offset[1] += 100.0 / zoom;
                break;

            case 'd':
                offset[0] += 100.0 / zoom;
                break;

            case '+':
                zoom *= 2;
                break;

            case '-':
                zoom /= 2;
                if (zoom == 0)
                {
                    zoom = 1;
                }
                break;

            case 'e':
                i *= 2;
                break;

            case 'q':
                i /= 2;
                if (i == 0)
                {
                    i = 1;
                }
                break;

            case 'r':
                offset[0] = offset[1] = 0;
                i = 100;
                zoom = 25;
                break;

            case 'z':
                loop = 0;
                break;
        }
    }

    return 0;
}

void drawMandelbrot(int iterations, double offset[], double zoom)
{
    int x;
    int y;
    double z[] = {0, 0};
    double parameter[] = {0, 0};
    for (y = 0; y < rows; y++)
    {
        parameter[1] = ((rows / 2) - y) / zoom + offset[1];
        for (x = 0; x < columns; x++)
        {
            parameter[0] = (x - (columns / 2)) / zoom + offset[0];
            z[0] = 0;
            z[1] = 0;
            int i = 0;
            double realTemp;
            while ((i < iterations) && ((z[0] * z[0]) + (z[1] * z[1]) <= 4))
            {
                realTemp = (z[0] * z[0]) - (z[1] * z[1]) + parameter[0];
                z[1] = (2 * z[0] * z[1]) + parameter[1];
                z[0] = realTemp;
                i++;
            }
            if (i == iterations)
            {
                printf("\x1b[3%dm%c", 0, PIXEL);
            }
            else
            {
                printf("\x1b[3%dm%c", iterations / i, PIXEL);
            }
            printf(ANSI_COLOR_RESET);
        }
        printf("\n");
    }
}
