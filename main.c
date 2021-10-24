#include <stdio.h>
#include <stdlib.h>
#define ALLOW_DIF 2 // 평단가가 0.몇 달러까지 차이가 될때 까지 알아볼 것인지 정의

typedef struct st_v
{
    float mean_price;
    int volume;
    float current_price;
} st_t;

float   mk_second_decimal(float nb)
{
    int int_nb;
    float ret;
    
    int_nb = (int)(nb * 100);
    ret = (float)int_nb / 100;
    return ret;
}

void    st_float(st_t *p)
{
    p->mean_price = mk_second_decimal(p->mean_price);
    p->current_price = mk_second_decimal(p->current_price);
}

void    op(st_t *p)
{
    int ret;
    float cu_asset;
    float cu_mean;
    float ck_price;
    
    ret = 0;
    cu_mean = p->mean_price;
    cu_asset = p->volume * p->mean_price;
    ck_price = p->current_price;
    while ((int)(cu_mean * 10) > (int)(ck_price * 10) + ALLOW_DIF)
    {
        ret++;
        cu_asset += p->current_price;
        cu_mean = cu_asset / (p->volume + ret);
    }
    printf("\n--------------------------\n");
    printf("The number of purchases : %d times\n",ret);
    printf("past purchased amount %.2f\n", p->mean_price * p->volume);
    printf("current purchase amount %.2f\n", cu_asset);
    printf("----------------------------\n");
}

void start(void)
{
    st_t *my;
    
    my = (st_t *)malloc(sizeof(st_t));
    printf("mean price :");
    scanf("%f", &my->mean_price);
    //printf("%.2f\n",my->mean_price );
    printf("volume :");
    scanf("%d", &my->volume);
    printf("current price :");
    scanf("%f", &my->current_price);
    st_float(my);
    op(my);
    free(my);
}

int main()
{
    start();
    return 0;
}
