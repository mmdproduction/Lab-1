#include"Inputs.h"
#include"DynArr.h"
#include"Integer.h"
#include"Double.h"
#include"Outputs.h"
#include<locale.h>
#include<windows.h>

void* int_func(void* val){
        static int result;
        result = (*(int*)val) * 2;
        return &result;
    }

 void* double_func(void* val){
        static double result;
        result = (*(double*)val) * 2;
        return &result;
    }

static int booling(void* val){
    if(*(int*)val > 3) return 0;
    return 1;
}
static int is_double_positive(void* val) {
    return (*(double*)val) > 0.0;
}

typedef enum{
    EXIT,
    CREATE_DYN_ARRAY,
    CHOOSE_ARRAY, 
    NUM_CHHOSEN_ARRAY,
    MAP,
    CONCATENATION, 
    WHERE,
    SET
}ChooseMode;

int main(){
    setlocale(LC_ALL, "Russian");

    TypeInfo* int_info = GetIntTypeInfo();
    TypeInfo* double_info = GetDoubleTypeInfo();
    DynArrErrors array_errors = OPERATION_OK;
    u_int num_arrays = 0,  created_arrays = 0, choosen_array_num = 0;
    u_int type = 0, size = 0;
    puts("Введите количество массивов: ");
    scanf("%d", &num_arrays);
    DynArr** dyn_arrays = malloc(num_arrays*sizeof(DynArr*));
    for (u_int i = 0; i < num_arrays; i++) {
        dyn_arrays[i] = NULL;
    }
    ChooseMode choose = EXIT;
    do{
        puts("Выберите режим: \n 1 - Создать динамический массив\n 2 - Выбрать динамический массив\n 3 - Выбранный массива\n 4 - Функция map(для текущего массива)\n 5 - Конкатенация (для двух массивов)\n 6 - Функция where(для выбранного массива)\n 7 - Заполнение выбранного массива числами с консоли \n 0 - Выйти");
        scanf("%d", &choose);
        switch(choose)
        {
        case EXIT:
            break;
        
        case CREATE_DYN_ARRAY:
            puts("Выберите тип:\n 1 - Целочисленный \n 2 - С плавающей запятой");
            scanf("%d", &type);
            puts("Введите размер: ");
            scanf("%d", &size);
            if(created_arrays < num_arrays && (type == 1) && (size > 0)){
                dyn_arrays[created_arrays] = create_clear_array(size, int_info, &array_errors);
            }
            created_arrays++;
            choosen_array_num = created_arrays;
            break;

        case NUM_CHHOSEN_ARRAY:
            printf("Номер выбранного массива: %d\n", choosen_array_num);
            puts("Выбранный массив: ");
            output_dyn_arr(dyn_arrays[choosen_array_num - 1], &array_errors);
            break;

        case MAP:
            if(strcmp(dyn_arrays[choosen_array_num - 1]->type_info->format, "int") == 0){
                dyn_arrays[choosen_array_num - 1] = map(int_func, dyn_arrays[choosen_array_num - 1], &array_errors);
            }
            else{
                dyn_arrays[choosen_array_num - 1] = map(double_func, dyn_arrays[choosen_array_num - 1], &array_errors);
            }
            output_dyn_arr(dyn_arrays[choosen_array_num - 1], &array_errors);
            break;
        case WHERE:
            if(strcmp(dyn_arrays[choosen_array_num - 1]->type_info->format, "int") == 0){
                dyn_arrays[choosen_array_num - 1] = where(booling, dyn_arrays[choosen_array_num - 1], &array_errors);
            }
            else{
                dyn_arrays[choosen_array_num - 1] = where(is_double_positive, dyn_arrays[choosen_array_num - 1], &array_errors);
            }
            output_dyn_arr(dyn_arrays[choosen_array_num - 1], &array_errors);
            break;
        case CONCATENATION:
            if (choosen_array_num > 0 && choosen_array_num < created_arrays) {
                DynArr* arr1 = dyn_arrays[choosen_array_num - 1];
                DynArr* arr2 = dyn_arrays[choosen_array_num];
                DynArr* concat_arr = concatenation(arr1, arr2, &array_errors);
                dyn_arrays[choosen_array_num - 1] = concat_arr;
                printf("Конкатенация выполнена. Новый размер: %d\n", concat_arr->array_size);
                output_dyn_arr(concat_arr, &array_errors);
            }
            break;
        case SET:
            puts("Введите значения по элементно");
            dyn_arrays[choosen_array_num - 1] = input_dyn_arr(dyn_arrays[choosen_array_num - 1]->type_info, &array_errors, dyn_arrays[choosen_array_num - 1]->array_size);
            break;
        case CHOOSE_ARRAY:
            puts("Введите номер  массива: \n");
            scanf("%d", &choosen_array_num);
            break;
        }
    }while(choose != EXIT);
    
}