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
void printUkrainianGameCompany();
void STALKER();
void monthinyear();
void borch();

Command commands[] = {
    {"допомога", help},
    {"пс", printHello},
    {"страва", borch},
    {"умп", printLanguages},
    {"рік", printYear},
    {"місяці", monthinyear},
    {"гейм", printUkrainianGameCompany},
    {"світло", turnOnLED},
    {"-світло", turnOffLED},
    {"про", printInfo},
    {"конфіг", printDeviceInfo},
    {"час", printUptime},
    {"пам'ять", checkMemory},
    {"S.T.A.L.K.E.R.", STALKER},
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
        "\nстрава - національна українська страва"
        "умп - українські мови програмування\n"
        "рік - показує який зараз рік\n"
        "гейм - невеличкий список українських гейм-дейв компаній\n"
        "місяці - список місяців у році\n"
        "про - вся інформація про систему та пристрій\n"
        "конфіг - характеристика пристрою\n"
        "світло - вбудований світлодіод світиться\n"
        "-світло - вбудований світлодіод не світиться\n"
        "час - показує час роботи системи\n"
        "пам'ять - показує вільну пам'ять\n"
        "S.T.A.L.K.E.R. - інформація про серії ігор S.T.A.L.K.E.R."
    ));
}

void monthinyear(){
  Serial.print(F("\n12 місяців у році:\nСічень, Лютий, Березень, Квітень, Травень, Червень, Липень, Серпень, Вересень, Жовтень, Листопад, Грудень"));
  }

void printHello() {
    Serial.println(F("\nПривіт світе!"));
}

void printLanguages() {
    Serial.println(F("\nУкраїнські мови програмування - Мавка, Ціль"));
}

void borch(){
  Serial.print(F("\nНаціональна українська страва - борщ"));
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

void STALKER(){
  Serial.println(F(
    "\nСерія ігор S.T.A.L.K.E.R.:\n"
    "Розробник: GSC Game World\n"
    "Першу гру з серії було створено 2007 року\n"
    "Серія на цей момент складається з чотирьох ігор: S.T.A.L.K.E.R.: Тінь Чорнобиля, S.T.A.L.K.E.R.: Чисте Небо, S.T.A.L.K.E.R.: Полкик Прип'яті і та частина яку найбільше чекали S.T.A.L.K.E.R. 2: Серце Чорнобиля\n"
    "Ігри серії підтримуються як і на Windows, так і на Xbox\n"
    "Також перші три гри з серії ,були об'єднані в S.T.A.L.K.E.R.: Legends of the Zone Trilogy та підтримуються на PlayStation, Nintendo Switch, Xbox, Windows\n"
    "GSC Game World проводили колаборацію з NonStope випустивши такі енергетики як: помаранчевий S.T.A.L.K.E.R.: Limited Edition та фіолетовий S.T.A.L.K.E.R.: Limited Edition"
    ));
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

void printUkrainianGameCompany(){
  Serial.println(F(
    "\nДеякі українські гейм-дейв компанії(список доповнюється)\nPS: в майбутньому можу видалити заради зменшення використання пам'яті пристрою, але список буде перенесений на інші варіанти системи...\n"
    "GSC Game World\n"
    "4A Games\n"
    "Best Way\n"
    "Action Forms\n"
    "N-Game Studios\n"
    "Frogwares\n"
    "PershaStudia\n"
    "Brenntkopf Development\n"
    "Muzt Die Studios\n"
    "Frag Lab LLC\n"
    "На цьому все, бо заради економії пам'яті не можу збільшити список..."
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
