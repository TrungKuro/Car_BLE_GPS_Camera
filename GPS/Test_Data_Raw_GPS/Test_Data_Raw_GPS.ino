/* Cung cấp các ký tự cho đối tượng TinyGPSPlus
** Từ một thiết bị GPS NMEA "nối tiếp"
** Nhưng ví dụ này sử dụng các CHUỖI TĨNH để cho đơn giản
*/
#include <TinyGPSPlus.h>

// A sample NMEA stream.
const char *gpsStream =
    "$GNGGA,125711.000,,,,,0,00,25.5,,,,,,*7B\r\n"
    "$GNRMC,125711.000,V,,,,,,,110123,,,N*52\r\n"
    "$GNGLL,,,,,025048.000,V,M*6C\r\n"

    "$GNGGA,125712.000,,,,,0,00,25.5,,,,,,*78\r\n"
    "$GNRMC,125712.000,V,,,,,,,110123,,,N*51\r\n"
    "$GNGLL,,,,,025049.000,V,M*6D\r\n"

    "$GNGGA,125713.000,,,,,0,00,25.5,,,,,,*79\r\n"
    "$GNRMC,125713.000,V,,,,,,,110123,,,N*50\r\n"
    "$GNGLL,,,,,025050.000,V,M*65\r\n"

    "$GNGGA,085106.000,1046.39984,N,10639.40257,E,1,15,0.8,13.2,M,0.0,M,,*41\r\n"
    "$GNRMC,085105.000,A,1046.39983,N,10639.40257,E,0.00,36.89,110123,,,A*4F\r\n"
    "$GNGLL,1046.39984,N,10639.40257,E,085106.000,A,A*48\r\n"

    "$GNGGA,085107.000,1046.39984,N,10639.40257,E,1,15,0.8,13.2,M,0.0,M,,*40\r\n"
    "$GNRMC,085106.000,A,1046.39984,N,10639.40257,E,0.00,36.89,110123,,,A*4B\r\n"
    "$GNGLL,1046.39984,N,10639.40257,E,085108.000,A,A*46\r\n"

    "$GNGGA,085108.000,1046.39984,N,10639.40257,E,1,15,0.8,13.3,M,0.0,M,,*4E\r\n"
    "$GNRMC,085107.000,A,1046.39984,N,10639.40257,E,0.00,36.89,110123,,,A*4A\r\n"
    "$GNGLL,1046.39984,N,10639.40257,E,085109.000,A,A*47\r\n";

// The TinyGPSPlus object
TinyGPSPlus gps;

void setup()
{
  Serial.begin(115200);

  Serial.println(F("Test data raw of ATGM336H"));
  Serial.println();

  while (*gpsStream)
    if (gps.encode(*gpsStream++))
      displayInfo();

  Serial.println();
  Serial.println(F("Done."));
}

void loop()
{
}

void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}