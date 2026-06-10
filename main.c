typedef enum {
    LINE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE
} ShapeType;

typedef struct {
    ShapeType type;
    int id;

    union {
        struct { int x1, y1, x2, y2; } line;

        struct { int x, y, width, height; } rect;

        struct { int xc, yc, radius; } circle;

        struct {
            int x1, y1;
            int x2, y2;
            int x3, y3;
        } triangle;
    };
} Shape;


#define ROWS 40
#define COLS 80

char canvas[ROWS][COLS];


void clearCanvas()
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            canvas[i][j] = '_';
}



void setPixel(int x, int y)
{
    if(x >= 0 && x < COLS &&
       y >= 0 && y < ROWS)
    {
        canvas[y][x] = '*';
    }
}


void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        setPixel(x1, y1);

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}