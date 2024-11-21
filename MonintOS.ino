#include <EEPROM.h>

char command[20];
unsigned long systemStartTime = 0;

struct Command {
    const char* name;
    void (*function)();
};

void help();
void printHello();
void printLanguages();
void printYear();
void turnOnLED();
void turnOffLED();
void printInfo();
void printDeviceInfo();
void showCommandList();
void printUptime();
void checkMemory();

Command commands[] = {
    {"допомога", help},
    {"пс", printHello},
    {"умп", printLanguages},
    {"рік", printYear},
    {"світло", turnOnLED},
    {"-світло", turnOffLED},
    {"інфо", printInfo},
    {"про", printDeviceInfo},
    {"час", printUptime},
    {"пам'ять", checkMemory},
    {"команди", showCommandList}
};

void setup() {
    Serial.begin(9600);
    systemStartTime = millis();
    Serial.println(F("Вітаю! Я система MonintOS"));
    pinMode(13, OUTPUT);
}

void loop() {
    if (Serial.available()) {
        byte len = Serial.readBytesUntil('\n', command, sizeof(command) - 1);
        command[len] = '\0';

        bool commandFound = false;
        for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
            if (strncmp(command, commands[i].name, strlen(commands[i].name)) == 0) {
                commands[i].function();
                commandFound = true;
                break;
            }
        }
        if (!commandFound) {
            Serial.println(F("\nНевідома команда"));
        }
    }
}

void help() {
    Serial.println(F(
        "\nпс - привітання світу\n"
        "умп - українські мови програмування\n"
        "рік - показує який зараз рік\n"
        "інфо - вся інформація про систему та пристрій\n"
        "про - характеристика пристрою\n"
        "світло - вбудований світлодіод світиться\n"
        "-світло - вбудований світлодіод не світиться\n"
        "час - показує час роботи системи\n"
        "пам'ять - показує вільну пам'ять"
    ));
}

void printHello() {
    Serial.println(F("\nПривіт світе!"));
}

void printLanguages() {
    Serial.println(F("\nУкраїнські мови програмування - Мавка, Ціль"));
}

void printYear() {
    Serial.println(F("\nЗараз 2024 рік"));
}

void turnOnLED() {
    digitalWrite(13, HIGH);
    Serial.println(F("\nСвітлодіод вмикається"));
}

void turnOffLED() {
    digitalWrite(13, LOW);
    Serial.println(F("\nСвітлодіод вимикається"));
}

void printInfo() {
    Serial.println(F(
        "\nПро систему:\n"
        "Назва ОС: MonintOS\n"
        "Мова системи: українська\n"
        "Назва пристрою: Freenove V4\n"
        "Архітектура пристрою: 8-біт\n"
        "Мова програмування: C++\n"
        "Версія: 0.0.0.1\n"
        "Дата випуску: 25.11.2024\n"
        "Розробник: Яценко Ярослав"
    ));
}

void printDeviceInfo() {
    Serial.println(F(
        "\nВсе про пристрій:\n"
        "Пристрій: Freenove V4\n"
        "Процесор: Atmega328P 16 Мгц\n"
        "Флеш-пам'ять: 32 (31.5) Кб\n"
        "Оперативна пам'ять: 2 Кб\n"
        "Енергонезалежна пам'ять: 1 Кб\n"
        "Сумісний з Arduino UNO R3"
    ));
}

void showCommandList() {
    Serial.println(F("\nДоступні команди:"));
    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        Serial.print(F("- "));
        Serial.println(commands[i].name);
    }
}

void printUptime() {
    unsigned long uptime = millis() - systemStartTime;
    Serial.print(F("\nЧас роботи системи: "));
    Serial.print(uptime / 1000);
    Serial.println(F(" секунд"));
}

void checkMemory() {
    extern int __heap_start;
    extern int *__brkval;
    int free_memory;
    if ((int)__brkval == 0) {
        free_memory = (int)&free_memory - (int)&__heap_start;
    } else {
        free_memory = (int)&free_memory - (int)__brkval;
    }
    Serial.print(F("\nВільна пам'ять: "));
    Serial.println(free_memory);
}
