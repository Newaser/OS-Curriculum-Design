#define True 1
#define False 0
#define Null -1
typedef int bool;
typedef char* path;

typedef enum orient_c{  //car's oriention type: North, South, Eest, West
    North, South, Eest, West
} orient_c;

typedef enum orient_l{  //light's oriention type: North-South, Eest-West
    North_South,
    Eest_West
} orient_l;

typedef struct car{
    orient_c from;
    float across_time;
} car;

typedef struct light
{
    orient_l orientation;
    double time;
} light;

typedef struct traffic{
    car* cars;
    int car_num;
    light green_light;
} traffic;


