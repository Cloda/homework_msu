
/*
Объяснение алгоритма
Введем цикл по элементам. Будем проверять текущий и последующий. Так же введем переменные максимума 
длины возрастающей последовательности, макс числа с той последовательности, текущей длины последовательности
и соответственно ее максимальный элемент. С помощью условий будем проверять максимальную и текущую длину
последовательности и взависимости менять их местами, и обнулять текущую длину. Если длина больше максимальной 
то меняем с максимумом длину и число, а текущее обнуляем.
*/

#include "stdio.h"

int func(const char *entry, const char *exit); 
int func(const char *entry, const char *exit){
    // файлы
    FILE *fp_entry;
    FILE *fp_exit;
    fp_entry = fopen(entry, "r");
    fp_exit = fopen(exit, "w");
    // проверки 
    if(fp_entry == NULL){
        fclose(fp_entry);
        fclose(fp_exit);
        return -1;
    }
    if(fp_exit == NULL){
        fclose(fp_entry);
        fclose(fp_exit);
        return -2;
    }
    // алгоритм
    int prev, next, cur, flag;
    flag = fscanf(fp_entry, "%d", &cur);
    fscanf(fp_entry, "%d", &next);
    int count_len = 1, count_max = 0, num = 0, num_max = 0, count_low = 0;
    if (flag == -1){
        return -3;
    }
    while(flag == 1) {
        // проверка на убывание 
        if (cur > next){
            // проверка на максимум элемента перед первым элементом убывающей последовательности
            if((cur > prev) || (cur > num)){
                count_low += 1; // добавление к количеству убывющих
                num = cur;
            }
            if (count_len == 1){
                prev = cur;
                cur = next;
                flag = fscanf(fp_entry, "%d", &next);
                continue;
            }
            // если возрастающей длина больше макс
            if(count_len > count_max){
                count_max = count_len;
                num_max = num;
                num = 0;
                count_len = 1;
                prev = cur;
                cur = next;
                flag = fscanf(fp_entry, "%d", &next);
                continue;
            }
            // при одинаковых возрастающих длинах
            if (count_len == count_max){
                if (num_max < num){
                    num_max = num;
                }
                num = 0;
                count_len = 1;
            }
            count_len = 1;
            num = 0;
        }
        if (cur > num){
            num = cur;
        }
        count_len += 1;
        prev = cur;
        cur = next;
        flag = fscanf(fp_entry, "%d", &next);
    }   
    // в последовательности нет двух участков убывания
    if (count_low < 2){
        fclose(fp_entry);
        fclose(fp_exit);
        return 1;
    }
    // проверка на между любыми соседними участками убывания нет элементов
    if (count_max == 0){
        fclose(fp_entry);
        fclose(fp_exit);
        return 2;
    }
    fprintf(fp_exit, "%d", num_max);
    fclose(fp_entry);
    fclose(fp_exit);
    return 0;
}


int main(void){
    char entry[80];
    char exit[80];
    int k;
    scanf("%s", entry);
    scanf("%s", exit);
    k = func(entry, exit);
    switch (k)
    {
    case -1:
        printf("-1");
        break;
    case -2:
        printf("-2");
        break;
    case -3:
        printf("-3");
        break;
    case 1:
        printf("1");
        break;
    case 2:
        printf("2");
        break;
    case 0:
        printf("0");
        break;
    }
    return 0;
}