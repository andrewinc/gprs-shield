// библиотека для работы с GPRS устройством
#include <GPRSk_Shield_Arduino.h>

// библиотека для эмуляции Serial порта
// она нужна для работы библиотеки GPRSk_Shield_Arduino
#include <SoftwareSerial.h>

// создаём объект mySerial и передаём номера управляющих пинов RX и TX
SoftwareSerial mySerial(6, 7);

// создаём объект класса GPRS и передаём в него объект mySerial
GPRSk gprs(mySerial);


void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  Serial.begin(9600);

  // открываем Serial-соединение с GPRS Shield
  mySerial.begin(9600);// ждём, пока не откроется монитор последовательного порта

  // ждём, пока не откроется монитор последовательного порта
  // для того, чтобы отследить все события в программе
  while (!Serial) {
  }
  Serial.print("Serial init OK\r\n");

  // включаем GPRS шилд
  gprs.powerOn();
  // проверяем есть ли связь с GPRS устройством
  while (!gprs.init()) {
    // если связи нет, ждём 1 секунду
    // и выводим сообщение об ошибке
    // процесс повторяется в цикле
    // пока не появится ответ от GPRS устройства
    Serial.print("GPRS Init error\r\n");
    delay(3000);
  }
  // выводим сообщение об удачной инициализации GPRS Shield
  Serial.println("GPRS init success");
}

void loop()
{
  // считываем данные с компьютера и записываем их в GPRS Shield
  serialPCread();
  // считываем данные с GPRS Shield и выводим их в Serial-порт
  serialGPRSread();
}

void serialPCread()
{
  if (Serial.available() > 0) {
    // если приходят данные по USB
    while (Serial.available() > 0) {
      // записываем их в GPRS Shield
      mySerial.write(Serial.read());
    }
  }
}

void serialGPRSread()
{
    if (mySerial.available() > 0) {
      // если приходят данные с GPRS Shield
      while (mySerial.available() > 0) {
        // передаём их в USB
        Serial.write(mySerial.read());
    }
  }
}
/*
В монитор будет записано:
Serial init OK
GPRS init success

после чего следует вводить AT-команды.
Правда через стандартный монитор мне это не удалось, только через Putty на тот же COM (предварительно, естественно отключив монитор Arduino IDE)
Для примера запрос IMEI, об операторе и о качестве сигнала:
AT+GSN
861508036742104

OK
AT+CSPN?
+CSPN: "Tele2", 0

OK
AT+CSQ
+CSQ: 15,0

OK
*/
