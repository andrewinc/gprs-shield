// библиотека для работы с GPRS устройством
#include <GPRSk_Shield_Arduino.h>

// библиотека для эмуляции Serial порта
// она нужна для работы библиотеки GPRSk_Shield_Arduino
#include <SoftwareSerial.h>

// создаём объект mySerial и передаём номера управляющих пинов RX и TX
SoftwareSerial mySerial(6, 7);

// номер на который будем звонить
#define PHONE_NUMBER  "+79007654321"

// создаём объект класса GPRS и передаём в него объект mySerial
GPRSk gprs(mySerial);


void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  Serial.begin(9600);

  // открываем Serial-соединение с GPRS Shield
  mySerial.begin(9600);

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
    delay(1000);
    Serial.print("GPRS Init error\r\n");
  }
  // вывод об удачной инициализации GPRS Shield
  Serial.println("GPRS init success");
  // сообщаем о наборе номера
  Serial.print("Start to call ");
  Serial.print(PHONE_NUMBER);
  // звоним по указанному номеру
  gprs.callUp(PHONE_NUMBER);
}

void loop()
{
}
/*
Вывод в монитор:
Serial init OK
GPRS init success
Start to call +79007654321
*/
