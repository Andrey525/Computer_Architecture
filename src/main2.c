#include "mySimpleComputer.h"
int main()
{
    sc_memoryInit();
    printf("Только что инициализированная память:\n");
    for (int i = 0; i < SIZE_OF_MEMORY; i++) {
        printf("%d ", RAM[i]);
    }
    printf("\n\n");
    sc_memorySet(95, 1);
    sc_memorySet(24, 12);
    sc_memorySet(54, 17);
    printf("Задали значения с помощью memorySet:\n");
    for (int i = 0; i < SIZE_OF_MEMORY; i++) {
        printf("%d ", RAM[i]);
    }
    printf("\n\n");
    int value;
    sc_memoryGet(24, &value);
    printf("Работа функции memoryGet:");
    printf("value == %d\n", value);

    sc_memorySave("mem.bin");
    sc_memoryInit();
    printf("Заново инициализировали оперативную память и вызываем функцию memoryLoad\n");
    sc_memoryLoad("mem.bin");
    for (int i = 0; i < SIZE_OF_MEMORY; i++) {
        printf("%d ", RAM[i]);
    }
    printf("\n\n");
    // printf("registr_of_flags == %d\n", registr_of_flags);
    sc_regInit();
    printf("Попытка обратиться к несуществующему участку памяти. В регистр флагов устанавливается 1\n");
    sc_memorySet(514, 17);
    printf("registr_of_flags == %d\n", registr_of_flags);
    // sc_regSet(OVERFLOW, 1);
    // sc_regSet(ERROR_EXIT_RANGE_MEMORY, 1);
    // sc_regSet(INVALID_COMMAND_SPECIFIED, 1);
    printf("registr_of_flags == %d\n", registr_of_flags);
    printf("Получаем флаг регистра\n");
    sc_regGet(M, &value);
    printf("value == %d\n", value);
    printf("Кодируем команду\n");
    sc_commandEncode(0x32, 13, &value);
    printf("value == %d\n", value);
    int command = 0, operand = 0;
    // value = 16365;
    // printf("value == %d\n", value);
    printf("Декодируем команду\n");
    sc_commandDecode(value, &command, &operand);
    printf("command == %x operand == %d\n", command, operand);
    return 0;
}
