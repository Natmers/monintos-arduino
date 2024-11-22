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
void monthInYear();
void borsch();

Command commands[] = {
    {"help", help},
    {"hello", printHello},
    {"dish", borsch},
    {"langs", printLanguages},
    {"year", printYear},
    {"months", monthInYear},
    {"game", printUkrainianGameCompany},
    {"light", turnOnLED},
    {"-light", turnOffLED},
    {"info", printInfo},
    {"config", printDeviceInfo},
    {"uptime", printUptime},
    {"memory", checkMemory},
    {"S.T.A.L.K.E.R.", STALKER},
    {"commands", showCommandList}
};

void setup() {
    Serial.begin(9600);
    systemStartTime = millis();
    Serial.println(F("Welcome! I am the MonintOS system."));
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
            Serial.println(F("\nUnknown command"));
        }
    }
}

void help() {
    Serial.println(F(
        "\nhello - greets the world\n"
        "dish - national Ukrainian dish\n"
        "langs - Ukrainian programming languages\n"
        "year - shows the current year\n"
        "game - a small list of Ukrainian game dev companies\n"
        "months - list of months in a year\n"
        "info - all information about the system and device\n"
        "config - device specifications\n"
        "light - turns on the built-in LED\n"
        "-light - turns off the built-in LED\n"
        "uptime - shows system uptime\n"
        "memory - shows free memory\n"
        "S.T.A.L.K.E.R. - information about the S.T.A.L.K.E.R. game series"
    ));
}

void monthInYear() {
    Serial.print(F("\n12 months in a year:\nJanuary, February, March, April, May, June, July, August, September, October, November, December"));
}

void printHello() {
    Serial.println(F("\nHello, World!"));
}

void printLanguages() {
    Serial.println(F("\nUkrainian programming languages - Mavka, Ziel"));
}

void borsch() {
    Serial.print(F("\nThe national Ukrainian dish is borsch"));
}

void printYear() {
    Serial.println(F("\nIt is currently the year 2024"));
}

void turnOnLED() {
    digitalWrite(13, HIGH);
    Serial.println(F("\nLED is turned on"));
}

void turnOffLED() {
    digitalWrite(13, LOW);
    Serial.println(F("\nLED is turned off"));
}

void STALKER() {
    Serial.println(F(
        "\nS.T.A.L.K.E.R. game series:\n"
        "Developer: GSC Game World\n"
        "The first game in the series was created in 2007\n"
        "The series currently consists of four games: S.T.A.L.K.E.R.: Shadow of Chernobyl, S.T.A.L.K.E.R.: Clear Sky, S.T.A.L.K.E.R.: Call of Pripyat, and the much-anticipated S.T.A.L.K.E.R. 2: Heart of Chernobyl\n"
        "Games in the series are supported on Windows and Xbox\n"
        "Additionally, the first three games were bundled in S.T.A.L.K.E.R.: Legends of the Zone Trilogy and are supported on PlayStation, Nintendo Switch, Xbox, and Windows\n"
        "GSC Game World collaborated with NonStop to release energy drinks: orange S.T.A.L.K.E.R.: Limited Edition and purple S.T.A.L.K.E.R.: Limited Edition"
    ));
}

void printInfo() {
    Serial.println(F(
        "\nSystem information:\n"
        "OS Name: MonintOS\n"
        "System Language: Ukrainian\n"
        "Device Name: Freenove V4\n"
        "Device Architecture: 8-bit\n"
        "Programming Language: C++\n"
        "Version: 0.0.0.1\n"
        "Release Date: 25.11.2024\n"
        "Developer: Yaroslav Yatsenko"
    ));
}

void printDeviceInfo() {
    Serial.println(F(
        "\nDevice specifications:\n"
        "Device: Freenove V4\n"
        "Processor: Atmega328P 16 MHz\n"
        "Flash Memory: 32 (31.5) KB\n"
        "RAM: 2 KB\n"
        "Non-volatile Memory: 1 KB\n"
        "Compatible with Arduino UNO R3"
    ));
}

void printUkrainianGameCompany() {
    Serial.println(F(
        "\nSome Ukrainian game development companies (list is expandable):\n"
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
        "That's all for now, as memory constraints prevent further expansion."
    ));
}

void showCommandList() {
    Serial.println(F("\nAvailable commands:"));
    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        Serial.print(F("- "));
        Serial.println(commands[i].name);
    }
}

void printUptime() {
    unsigned long uptime = millis() - systemStartTime;
    Serial.print(F("\nSystem uptime: "));
    Serial.print(uptime / 1000);
    Serial.println(F(" seconds"));
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
    Serial.print(F("\nFree memory: "));
    Serial.println(free_memory);
}
