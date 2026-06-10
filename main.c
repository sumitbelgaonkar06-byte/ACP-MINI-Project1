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


int main()
{
    Shape r, c;

    r.type = RECTANGLE;
    r.id = 1;
    r.rect.x = 5;
    r.rect.y = 5;
    r.rect.width = 20;
    r.rect.height = 10;

    c.type = CIRCLE;
    c.id = 2;
    c.circle.xc = 40;
    c.circle.yc = 15;
    c.circle.radius = 8;

    addObject(r);
    addObject(c);

    printf("Original Picture:\n");
    redraw();
    displayCanvas();

    printf("\n\nAfter Modifying Rectangle:\n");
    modifyRectangle(1, 10, 10, 15, 8);
    redraw();
    displayCanvas();

    printf("\n\nAfter Deleting Circle:\n");
    deleteObject(2);
    redraw();
    displayCanvas();

    return 0;
}


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

void drawRectangle(int x, int y, int width, int height)
{
    drawLine(x, y, x + width, y);

    drawLine(x, y,
             x, y + height);

    drawLine(x + width, y,
             x + width, y + height);

    drawLine(x, y + height,
             x + width, y + height);
}


void drawCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = 1 - r;

    while(x <= y)
    {
        setPixel(xc + x, yc + y);
        setPixel(xc - x, yc + y);
        setPixel(xc + x, yc - y);
        setPixel(xc - x, yc - y);

        setPixel(xc + y, yc + x);
        setPixel(xc - y, yc + x);
        setPixel(xc + y, yc - x);
        setPixel(xc - y, yc - x);

        if(d < 0)
            d += 2*x + 3;
        else
        {
            d += 2*(x-y) + 5;
            y--;
        }
        x++;
    }
}


void drawTriangle(
    int x1, int y1,
    int x2, int y2,
    int x3, int y3)
{
    drawLine(x1,y1,x2,y2);
    drawLine(x2,y2,x3,y3);
    drawLine(x3,y3,x1,y1);
}


void displayCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);

        printf("\n");
    }
}

#define MAX_OBJECTS 100

Shape objects[MAX_OBJECTS];
int count = 0;

void addObject(Shape s)
{
    if(count < MAX_OBJECTS)
        objects[count++] = s;
}

void deleteObject(int id)
{
    for(int i = 0; i < count; i++)
    {
        if(objects[i].id == id)
        {
            for(int j = i; j < count-1; j++)
                objects[j] = objects[j+1];

            count--;
            break;
        }
    }
}



void modifyRectangle(
    int id,
    int x,
    int y,
    int w,
    int h)
{
    for(int i = 0; i < count; i++)
    {
        if(objects[i].id == id &&
           objects[i].type == RECTANGLE)
        {
            objects[i].rect.x = x;
            objects[i].rect.y = y;
            objects[i].rect.width = w;
            objects[i].rect.height = h;
        }
    }
}


void redraw()
{
    clearCanvas();

    for(int i = 0; i < count; i++)
    {
        Shape *s = &objects[i];

        switch(s->type)
        {
            case LINE:
                drawLine(
                    s->line.x1,
                    s->line.y1,
                    s->line.x2,
                    s->line.y2);
                break;

            case RECTANGLE:
                drawRectangle(
                    s->rect.x,
                    s->rect.y,
                    s->rect.width,
                    s->rect.height);
                break;

            case CIRCLE:
                drawCircle(
                    s->circle.xc,
                    s->circle.yc,
                    s->circle.radius);
                break;

            case TRIANGLE:
                drawTriangle(
                    s->triangle.x1,
                    s->triangle.y1,
                    s->triangle.x2,
                    s->triangle.y2,
                    s->triangle.x3,
                    s->triangle.y3);
                break;
        }
    }
}

