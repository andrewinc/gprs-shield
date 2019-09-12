keyestudio gsm gprs shield
===========
Статья https://habr.com/ru/post/403843/

Библиотека для Arduino, позволяющая управлять [GSM/GPRS Shield’ом keyestudio] (PDF download: http://www.keyestudio.com/files/index/download/id/1479110960/)
от [keyestudio] (http://www.keyestudio.com/keyestudio-sim900-gsm-gprs-module-shield.html).

datasheet чипа sim900 https://www.elecfreaks.com/estore/download/EF03072-SIM900_Hardware%20Design_V2.00.pdf

Установка
=========
Скопировать папку распакованного архива в arduino/libraries
Узнать расположение папки arduino можно в Arduino IDE → пункт меню «Файл» → «Настройки». Перезапустите  Arduino IDE. Установка завершена.

Пример использования
====================

```cpp
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

  Serial.print("Send SMS: ");
  // отправляем сообщение по указанному номеру с заданным текстом
  if (gprs.sendSMS("+79007654321", "Hello from Keyestudio GSM/GPRS Shield!"))
    Serial.println("Ok");
  else
    Serial.println("Error");  
}

void loop()
{
}
/*
В результате, помимо SMS по укзанному номеру, в монитор порта попадут такие строки:
Serial init OK
GPRS init success
Send SMS: Ok
*/
