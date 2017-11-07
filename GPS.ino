/*
   FILE          : GPS.ino
   PROJECT       : PROG8125
   PROGRAMMER    : Rohit Bhardwaj
   FIRST VERSION : 2016-07-21
   DESCRIPTION   : This program reads the GPS string from serial port, parse the string and also
                   decode longitude,latitude,and time data
   Example of GPS String: $GPGGA,014729.10,4303.5753,N,08019.0810,W,1,6,1.761,214.682,M,0,M,0,*5D 
   This code is tested on Teensy 3.1 board
*/

void setup()
{
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  Serial.println("starting");
}

//protoype declaration
void checkForRecvdChar();
void parsethestring(char* recBuffer);
void displayAndCalculateTime(float utcTime);
void displayAndCalculateLatitudeAndLongitude( char *recValue);

void loop()
{
  checkForRecvdChar ();
}


// FUNCTION      : checkForRecvdChar()
// DESCRIPTION   : Checks the serial port to see if any chars
//                 are available. If so, reads the chars using
//                 the serial.read method
//                 is read.
// PARAMETERS    : none
// RETURNS       : nothing
void checkForRecvdChar()
{
  static int recByteCtr = 0;    //declare and initialize the rec'd byte counter variable
  static char recBuffer [255];
  char byteRead;

  while (Serial.available())   //then let's read the byte
  {
    if (recByteCtr == 0)       //then check to see if it's the start of a message
    {
      byteRead = Serial.read(); //read the byte
      if (byteRead == '$')
      {
        recBuffer[recByteCtr] = byteRead; //copy the byte read into the rec buffer
        recByteCtr++;
      }
    }
    if (recByteCtr != 0) //then we're reading bytes after receiving an STX in the message stream
    {
      byteRead = Serial.read(); //read the byte
      if (byteRead != 13) //13 = CR
      {
        recBuffer[recByteCtr] = byteRead; //copy the byte read into the rec buffer
        recByteCtr++;
      }
      else //recbyte == 13
      {
        recBuffer[recByteCtr] = '\0'; //null terminate the rec'd string in rec buffer
        recByteCtr = 0;
        Serial.printf("%s\n", recBuffer);
        parsethestring (recBuffer);
      }
    }
  }
}

// FUNCTION      : parsethestring()
// DESCRIPTION   : It parse the recevied string with the help of
//                 delimiter(,) and also prints them on the serial
//                 port
// PARAMETERS    : Char* - recBuffer (Pointer Variable)
// RETURNS       : nothing
void parsethestring(char* recBuffer)
{
  const char *delim  = ",";   //a comma is the delimiter

  //Now initialize all the pointer variables as NULL pointer
  // As subsquent calls to strtok are done using the Null pointer
  char *firstItem = NULL;
  char *secondItem = NULL;
  char *thirdItem = NULL;
  char *fourthItem = NULL;
  char *fifthItem = NULL;
  char *sixthItem = NULL;
  char *seventhItem = NULL;
  char *eighthItem = NULL;
  char *ninthItem = NULL;
  char *tenthItem = NULL;
  char *eleventhItem = NULL;
  char *twelvethItem = NULL;
  char *thirteenthItem = NULL;
  char *fourteenthItem = NULL;
  char *fifteenthItem = NULL;

  firstItem = strtok(recBuffer, delim);  // it will parse the first
  if (firstItem != NULL)
  {
    secondItem = strtok(NULL, delim);
    if (secondItem != NULL)
    {
      thirdItem = strtok(NULL, delim);
      if (thirdItem != NULL)
      {
        fourthItem = strtok(NULL, delim);
        if (fourthItem != NULL)
        {
          fifthItem = strtok(NULL, delim);
          if (fifthItem != NULL)
          {
            sixthItem = strtok(NULL, delim);
            if (sixthItem != NULL)
            {
              seventhItem = strtok(NULL, delim);
              if (seventhItem != NULL)
              {
                eighthItem = strtok(NULL, delim);
                if (eighthItem != NULL)
                {
                  ninthItem = strtok(NULL, delim);
                  if (ninthItem != NULL)
                  {
                    tenthItem = strtok(NULL, delim);
                    if (tenthItem != NULL)
                    {
                      eleventhItem = strtok(NULL, delim);
                      if (eleventhItem != NULL)
                      {
                        twelvethItem = strtok(NULL, delim);
                        if (twelvethItem != NULL)
                        {
                          thirteenthItem = strtok(NULL, delim);
                          if (thirteenthItem != NULL)
                          {
                            fourteenthItem = strtok(NULL, delim);
                            if (fourteenthItem != NULL)
                            {
                              fifteenthItem = strtok(NULL, delim);
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  if (firstItem != NULL)
  {
    Serial.printf("Sentence ID: ");
    Serial.println(firstItem);
  }
  if (secondItem != NULL)
  {
    Serial.print("UTC time: ");
    Serial.println(secondItem);
    float utcTime = atof(secondItem);  //convert the secondItem into a floating point value
    displayAndCalculateTime (utcTime);  //Calling the displayAndCalculateTime()
  }
  if (thirdItem != NULL)
  {
    Serial.print("Latitude: ");
    Serial.println(thirdItem);
    displayAndCalculateLatitudeAndLongitude(thirdItem);
  }
  if (fourthItem != NULL)
  {
    Serial.print("Measured is North of the equator: ");
    Serial.println(fourthItem);
  }
  if (fifthItem != NULL)
  {
    Serial.print("Longitude: ");
    Serial.println(fifthItem);
    displayAndCalculateLatitudeAndLongitude(fifthItem);
  }
  if (sixthItem != NULL)
  {
    Serial.print("Measured is West of Greenwich England :");
    Serial.println(sixthItem);
  }
  if (seventhItem != NULL)
  {
    Serial.print("Position Fix ");
    Serial.println(seventhItem);
  }
  if (eighthItem != NULL)
  {
    Serial.print("Satellites Used: ");
    Serial.println(eighthItem);
  }
  if (ninthItem != NULL)
  {
    Serial.print("HDOP 38466 Horizontal dilution of precision: ");
    Serial.println(ninthItem);
  }
  if (tenthItem != NULL)
  {
    Serial.print("Altitude: ");
    Serial.println(tenthItem);
    float altiInMeters = atof(tenthItem);
    Serial.printf("Altitude in meters according to WGS-84 elliposoid %0.3f\n", altiInMeters);
  }
  if (eleventhItem != NULL)
  {
    Serial.print("Altitude Units: ");
    Serial.println(eleventhItem);
  }
  if (twelvethItem != NULL)
  {
    Serial.print("Geoid Separation: ");
    Serial.println(twelvethItem);
  }
  if (thirteenthItem != NULL)
  {
    Serial.print("In Meters: ");
    Serial.println(thirteenthItem);
  }
  if (fourteenthItem != NULL)
  {
    Serial.print("DGPS Age: ");
    Serial.println(fourteenthItem);
  }
  if (fifteenthItem != NULL)
  {
    Serial.print("Checksum: ");
    int32_t checksum = strtoul(fifteenthItem + 1, NULL, 16);
    Serial.printf("%X \n", checksum);
  }
}

// FUNCTION      : displayAndCalculateTime()
// DESCRIPTION   : It uses math to separate the string into hours
//                 ,Minutes and Seconds. It also print these on
//                 the serial port.
//                 is read.
// PARAMETERS    : Float - utcTime
// RETURNS       : nothing
void displayAndCalculateTime(float utcTime)
{
  int hours = utcTime / 10000;                                 // divide the utcTime by 10000 to get the first two digits(i.e Hours)
  int minuteCal = utcTime / 100;                               // divide the utcTime by 100 to get the first four digits(i.e Hours+minutes)
  int minutes = minuteCal % 100;                               // Now take modulus of minuteCal(i.e first four digits)as it will give us Minutes
  int a = hours * 100;                                         // here we take a variable'a' to calculate Seconds
  int mint = minuteCal - a;                                    // and subtract that from minuteCal
  float seconds = utcTime - (hours * 10000) - (mint * 100);    // here we get Seconds
  Serial.printf("%i hh\n", hours);
  Serial.printf("%i mm\n", minutes);
  Serial.printf("%2.2f ss \n", seconds);
}

// FUNCTION      : displayAndCalculateLatitudeAndLongitude
// DESCRIPTION   : It uses strtok and match to separate the string into
//                 degrees, minutes  and decimal degree. It also print these
//                 on the serial port.
//                 is read.
// PARAMETERS    : Char* recValue(pointer variable)
// RETURNS       : nothing
void displayAndCalculateLatitudeAndLongitude( char *recValue)
{
  const char *delimi = ".";              //a dot is the delimiter

  //Now initialize the pointer variables as NULL pointer
  // As subsquent calls to strtok are done using the Null pointer
  char *integer = NULL;
  char *fraction = NULL;

  integer = strtok(recValue, delimi);                  // prase the string and store the integeral part
  if (integer != NULL)
    fraction = strtok(NULL, delimi);                     // parese the string and store the fractional part
  int fract = atoi(fraction);                          // convert it into integer
  int integ = atoi(integer);                           // convert it into integer
  int minutes = integ % 100;                           // take modulus to get the minutes
  int degree = integ / 100;                            //  divide integ by 100 to get the degree
  Serial.printf("%i degree\n", degree);
  Serial.printf("%i minutes\n", minutes);
  Serial.printf("%i decimal degree \n", fract);

}


