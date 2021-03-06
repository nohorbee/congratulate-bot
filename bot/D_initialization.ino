
#define PREFIX ""
WebServer webserver(PREFIX, 80);

void registerHandlers() {

handlers[0].method = &celebrateHandler;

}

static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
static uint8_t ip[] = { 172,16,21,254 };

void setup()
{
 Serial.begin(9600);
 pinMode(servoPin, OUTPUT);
 myServo.attach(servoPin);
 myServo.write(10);
 
 ethStart();
 
 Serial.end();
 registerHandlers();
 webserver.setFailureCommand(&dispatch);
 webserver.begin();
}

void ethStart() {
//  Ethernet.begin(mac,ip);
  Serial.println(F("Initializing Eth"));
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Failed to configure Ethernet using DHCP"));
    for(;;)
      ;
  }
  // print your local IP address:
  Serial.print(F("My IP address: "));
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(F("."));
  }
  Serial.println();
}

void loop()
{
  char buff[64];
  int len = 64;
 /* process incoming connections one at a time forever */
  webserver.processConnection(buff, &len); 
}


