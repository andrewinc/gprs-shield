// библиотека для работы с GPRS устройством
#include <GPRSk_Shield_Arduino.h>

// библиотека для эмуляции Serial порта
// она нужна для работы библиотеки GPRSk_Shield_Arduino
#include <SoftwareSerial.h>

// создаём объект mySerial и передаём номера управляющих пинов RX и TX
SoftwareSerial mySerial(6, 7);

// номер на который будем отправлять сообщение
#define PHONE_NUMBER  "+79007654321"
// текст сообщения, которое будем отправлять
#define MESSAGE  "Hello from Keyestudio GSM/GPRS Shield!"

// создаём объект класса GPRS и передаём в него объект Serial1
GPRSk gprs(mySerial);


void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  Serial.begin(9600);

  // открываем Serial-соединение с GPRS Shield
  mySerial.begin(9600);

  // ждём пока не откроется монитор последовательного порта
  // для того, чтобы отследить все события в программе
  while (!Serial) {
  }
  Serial.print("Serial init OK\r\n");

  // включаем GPRS-шилд
  gprs.powerOn();
  // проверяем, есть ли связь с GPRS-устройством
  while (!gprs.init()) {
    // если связи нет, ждём 1 секунду
    // и выводим сообщение об ошибке;
    // процесс повторяется в цикле,
    // пока не появится ответ от GPRS-устройства
    delay(1000);
    Serial.print("GPRS Init error\r\n");
  }
  // вывод об удачной инициализации GPRS Shield
  Serial.println("GPRS init success");
  // сообщаем о написании и отправке СМС по указанному номеру
  Serial.println("Start to send message ...");
  // отправляем сообщение по указанному номеру с заданным текстом
  if (gprs.sendSMS(PHONE_NUMBER, MESSAGE))
    Serial.println("Success");
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
Start to send message ...
Success
*/
