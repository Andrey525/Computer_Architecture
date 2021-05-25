

int find_pref(char* ar, int arg)
{
    int i = 0;
    while (ar[i] != 0) {
        i++;
        if (ar[i] == '.' && ar[i + 1] == 's' && ar[i + 2] == 'a' && ar[i + 3] == 0 && arg == 1) {
            return 1;
        } else if (ar[i] == '.' && ar[i + 1] == 'o' && ar[i + 2] == 0 && arg == 2) {
            return 1;
        }
    }
    return 0;
}

int get_command(char* str)
{
    int command = -1;
    if (strcmp(str, "READ") == 0) {
        command = 0x10;
    } else if (strcmp(str, "WRITE") == 0) {
        command = 0x11;
    } else if (strcmp(str, "LOAD") == 0) {
        command = 0x20;
    } else if (strcmp(str, "STORE") == 0) {
        command = 0x21;
    } else if (strcmp(str, "ADD") == 0) {
        command = 0x30;
    } else if (strcmp(str, "SUB") == 0) {
        command = 0x31;
    } else if (strcmp(str, "DIVIDE") == 0) {
        command = 0x32;
    } else if (strcmp(str, "MUL") == 0) {
        command = 0x33;
    } else if (strcmp(str, "JUMP") == 0) {
        command = 0x40;
    } else if (strcmp(str, "JNEG") == 0) {
        command = 0x41;
    } else if (strcmp(str, "JZ") == 0) {
        command = 0x42;
    } else if (strcmp(str, "HALT") == 0) {
        command = 0x43;
    } else if (strcmp(str, "ADDC") == 0) {
        command = 0x65;
    } else if (strcmp(str, "=") == 0) {
        command = 0;
    }
    return command;
}

int write_into_memory(char* str)
{
    // получение адреса ячейки
    int address;
    char str_address[3];
    strncpy(str_address, str, 2);
    str_address[2] = '\0';
    printf("%s", str_address);
    address = atoi(str_address);
    printf(" address = %d", address);

    // получение команды
    int command;
    int i = 3;
    char str_cmd[10];
    while (str[i] != ' ') {
        int len = strlen(str_cmd);
        str_cmd[len] = str[i];
        str_cmd[len + 1] = '\0';
        i++;
    }
    printf(" %s\n", str_cmd);
    command = get_command(str_cmd);
    if (command == -1) {
        printf("В строке неверная команда\n");
        return 1;
    }

    // получение операнда
    while (str[i] < '0' || str[i] > '9') {
        i++;
    }
    int operand;
    char str_operand[5];
    for (int j = 0; j < 5; j++, i++) {
        str_operand[j] = str[i];
    }
    int len = strlen(str_operand);
    str_operand[len] = '\0';
    printf("str_operand = %s\n", str_operand);
    operand = atoi(str_operand);
    printf("%d - operand\n", operand);

    // заполняем ячейки памяти
    if (command == 0) { // явно задаем, если =
        sc_memorySet(address, operand);
    } else if (operand > 127) {
        return 1;
    } else {
        int value = 0;
        sc_commandEncode(command, operand, &value);
        sc_memorySet(address, value);
    }

    return 0;
}

int assembler_to_simple_computer(char* from, char* to)
{

    FILE* input;
    if ((input = fopen(from, "r")) == NULL) {
        printf("Не удалось открыть файл\n"); // открыть файл не удалось
        return 0;
    }
    printf("Файл открыт для чтения\n"); // требуемые действия над данными
    sc_init();
    char* estr;
    char str[50];
    int i = 0;
    while (1) {
        // Чтение одной строки  из файла
        estr = fgets(str, sizeof(str), input);

        //Проверка на конец файла или ошибку чтения
        if (estr == NULL) {
            // Проверяем, что именно произошло: кончился файл
            // или это ошибка чтения
            if (feof(input) != 0) {
                //Если файл закончился, выводим сообщение о завершении
                //чтения и выходим из бесконечного цикла
                printf("\nЧтение файла закончено\n");
                break;
            } else {
                //Если при чтении произошла ошибка, выводим сообщение
                //об ошибке и выходим из бесконечного цикла
                printf("\nОшибка чтения из файла\n");
                break;
            }
        }
        //Если файл не закончился, и не было ошибки чтения
        //выводим считанную строку  на экран
        if (write_into_memory(str)) {
            printf("Трансляция не выполнена, в Вашей программе ошибка\n");
            return 1;
        }
        printf("\tстрока %d\n", i);
        i++;
        // printf("%s", str);
    }
    fclose(input);

    sc_memorySave(to);
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 3 || !find_pref(argv[1], 1) || !find_pref(argv[2], 2)) {
        printf("Неверные аргументы\n");
        return 0;
    } else {
        printf("Все ок\n");
    }
    assembler_to_simple_computer(argv[1], argv[2]);
    return 0;
}
