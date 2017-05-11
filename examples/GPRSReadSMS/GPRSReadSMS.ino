// библиотека для работы с GPRS устройством
#include <GPRSk_Shield_Arduino.h>

#include <SoftwareSerial.h>

// длина сообщения
#define MESSAGE_LENGTH 160

// создаём объект mySerial и передаём номера управляющих пинов RX и TX
SoftwareSerial mySerial(6, 7);

// номер сообщения в памяти сим-карты
int messageIndex = 0;

// текст сообщения
char message[MESSAGE_LENGTH];
// номер, с которого пришло сообщение
char phone[16];
// дата отправки сообщения
char datetime[24];

// создаём объект класса GPRS и передаём в него объект mySerial
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
  // выводим сообщение об удачной инициализации GPRS Shield
  Serial.println("GPRS init success");
  Serial.println("Please send SMS message to me!");
}

void loop()
{
  // если пришло новое сообщение
  if (gprs.ifSMSNow()) {
    // читаем его
    gprs.readSMS(message, phone, datetime);

    // выводим номер, с которого пришло смс
    Serial.print("From number: ");
    Serial.println(phone);

    // выводим дату, когда пришло смс
    Serial.print("Datetime: ");
    Serial.println(datetime);

    // выводим текст сообщения
    Serial.print("Recieved Message: ");
    Serial.println(message);
  }
}
/**
Вывод в монитор:
Serial init OK
GPRS init success
Please send SMS message to me!
From number: +79007654321
Datetime: 17/05/07,21:38:00+12
Recieved Message: Hello
*/
