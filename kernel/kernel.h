// Screen

typedef struct {
    int x;
    int y;
} point_t;

void screen_clear();
void screen_print(point_t point, const char *str);