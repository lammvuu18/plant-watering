
#include <RtcDS1302.h>
#include <ThreeWire.h>


int Relay = 6;

const int giomo = 12;
const int phutmo = 19;
const int giotat = 12;
const int phuttat = 25;

ThreeWire myWire(4, 5, 3); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() 
{
  Serial.begin(57600);
  Rtc.Begin();
  
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);

// Kiểm tra nếu thời gian không hợp lệ, thiết lập lại thời gian
  if (!Rtc.IsDateTimeValid()) 
  {
    // Common Causes:
    //    1) First time you ran and the device wasn't running yet
    //    2) The battery on the device is low or even missing

    Serial.println("RTC lost confidence in the DateTime!");
    // Thiết lập lại thời gian
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Rtc.SetDateTime(compiled);
  }
}

void loop() 
{
  RtcDateTime now = Rtc.GetDateTime();

  Serial.print(now.Hour());
  Serial.print(" Giờ, ");
  Serial.print(now.Minute());
  Serial.print(" Phút, ");
  Serial.print(now.Second());
  Serial.print(" Giây ");
  Serial.println(" ");
  delay(1000);
  
  if(now.Hour() == giomo && now.Minute() == phutmo)
  {
    digitalWrite(Relay, HIGH);
    Serial.println("Relay ON, Bơm nước");
  }
  else if(now.Hour() == giotat && now.Minute() == phuttat)
  {
    digitalWrite(Relay, LOW);
    Serial.println("Relay OFF, Không bơm");
  }
}