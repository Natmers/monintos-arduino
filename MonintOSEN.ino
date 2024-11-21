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
    {"help", help},
    {"hello", printHello},
    {"languages", printLanguages},
    {"year", printYear},
    {"led_on", turnOnLED},
    {"led_off", turnOffLED},
    {"info", printInfo},
    {"device", printDeviceInfo},
    {"uptime", printUptime},
    {"memory", checkMemory},
    {"commands", showCommandList}
};

void setup() {
    Serial.begin(9600);
    systemStartTime = millis();
    Serial.println(F("Welcome! I am the MonintOS system"));
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
        "\nhello - greet the world\n"
        "languages - Ukrainian programming languages: Mavka, Tziel\n"
        "year - shows the current year\n"
        "info - all information about the system and device\n"
        "device - device specifications\n"
        "led_on - turn on the built-in LED\n"
        "led_off - turn off the built-in LED\n"
        "uptime - shows system uptime\n"
        "memory - shows free memory"
    ));
}

void printHello() {
    Serial.println(F("\nHello, world!"));
}

void printLanguages() {
    Serial.println(F("\nUkrainian programming languages: Mavka, Tziel"));
}

void printYear() {
    Serial.println(F("\nThe current year is 2024"));
}

void turnOnLED() {
    digitalWrite(13, HIGH);
    Serial.println(F("\nLED is on"));
}

void turnOffLED() {
    digitalWrite(13, LOW);
    Serial.println(F("\nLED is off"));
}

void printInfo() {
    Serial.println(F(
        "\nSystem Info:\n"
        "OS Name: MonintOS\n"
        "System Language: Ukrainian\n"
        "Device Name: Freenove V4\n"
        "Device Architecture: 8-bit\n"
        "Programming Language: C++\n"
        "Version: 0.0.0.1\n"
        "Release Date: 25.11.2024\n"
        "Developer: Yatsenko Yaroslav"
    ));
}

void printDeviceInfo() {
    Serial.println(F(
        "\nDevice Info:\n"
        "Device: Freenove V4\n"
        "Processor: Atmega328P 16 MHz\n"
        "Flash Memory: 32 (31.5) KB\n"
        "RAM: 2 KB\n"
        "EEPROM: 1 KB\n"
        "Compatible with Arduino UNO R3"
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
