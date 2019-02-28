 #include <Wire.h>// библиотека для работы I²C
#include <TroykaIMU.h>// библиотека для работы с модулями IMU
#include<Servo.h>//подключаем библиотеку для работы с сервоприводом
Servo servo1;// создаём объект для работы с сервоприводом
Servo servo2;// создаём объект для работы с сервоприводом
Barometer barometer;// создаём объект для работы с барометром
int LentaRele=4;//переменная для работы со светодиодной лентой
int Svet=A1;//переменная для работы с фоторезистором
int ColdRele=5;//переменная для работы с охлаждающим куллером
int HotRele=6;//переменная для работы с нагревающим куллером
int PleteRele=7;//переменная для работы с элементом Пельтье
void setup() 
  {
    servo1.attach(2);
    servo2.attach(3);
    servo1.write(0);
    servo2.write(0);
    pinMode(ColdRele, OUTPUT); 
    pinMode(HotRele, OUTPUT); 
    pinMode(PleteRele, OUTPUT);
    pinMode(LentaRele,OUTPUT);//выставляем пины для работы со всеми реле, заданными выше
    pinMode(Svet,INPUT);//выставляем пин для работы с фоторезистором как вход
    Serial.begin(115200);// открываем последовательный порт
    barometer.begin();// инициализация барометра
  }

void loop() 
  { 
    float pressure = barometer.readPressureMillibars(); // создаём переменную и присваиваем ей значения абсолютного давления
    float altitude = barometer.pressureToAltitudeMeters(pressure);// создаём переменную и присваиваем ей значения высоты над уровнем море
    float temperature = barometer.readTemperatureC();// создаём переменную и присваиваем ей температуру окружающей среды
    int osv=analogRead(Svet);//создаём переменную для работы с освещённостью, читаем данные
    Serial.print("pressure = ");
    Serial.print(pressure);
    Serial.println(" mBar");
    Serial.print("altitude = ");
    Serial.print(altitude);
    Serial.println(" m");
    Serial.print("temperature = ");
    Serial.print(temperature);
    Serial.println(" C°");
    Serial.print("illumination = ");
    Serial.println(osv);//пишем данные со всех датчиков в порт
    Serial.println(" ");
    delay(500); 
    if(osv>400)//если показания с фоторезистора больше 400
    {
        digitalWrite(LentaRele,HIGH);//выключаем ленту
    }
    else//иначе
    {
        digitalWrite(LentaRele,LOW);//включаем ленту
    }
    if(temperature<25.00)//если температура меньше 25 градусов
    {
        digitalWrite(PleteRele,LOW);//включаем пельтье 
        
        digitalWrite(HotRele,HIGH);//включаем куллер нагревания 
    }    
    else if(temperature>30.00)//иначе если температура больше 30 градусов
    {
         digitalWrite(PleteRele,LOW);//включаем пельтье
         
         digitalWrite(ColdRele,HIGH);//включаем куллер охлаждения
    }
    else//иначе
    {
         digitalWrite(PleteRele,HIGH);
         digitalWrite(HotRele,HIGH);
         digitalWrite(ColdRele,HIGH);//всё выключено
    }


     if(pressure>1110.00)//если давление больше 1110.0 мБар...
    {
        // устанавливаем сервопривод в серединное положение
        servo1.write(0);
        // устанавливаем сервопривод в крайнее левое положение тем самым открывая клапан
        servo1.write(30);
    }
    else if(pressure<1110.00)//если давление меньше 1110.0 мБар...
    {
        servo1.write(30);
        servo1.write(0);
        //возвращаем сервопривод в исходное положение
    }
    if(pressure<1010.00)//если давление меньше 1010.0 мБар...
    {
        servo2.write(0);//нажимаем на кнопку
        servo2.write(35);
    }
    else if(pressure>1010.00)//если давление меньше 1010.0 мБар...
    {
        servo2.write(35);//отжимаем кнопку
        servo2.write(0);
    }
}

  
