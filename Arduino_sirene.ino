int sireneStatus = 0;
int actionStatus = 0;
int pinSirene = 13;// HIGH for turnoff sirene , LOW for turn on sirene
unsigned long currentTime[3], previousTime[3];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinSirene,OUTPUT);
  digitalWrite(pinSirene,HIGH); 
  Serial.println("Sirene Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  readSerial();
}


void readSerial()
{
    if(Serial.available()>1)
  {
    String serialread = Serial.readString();
    char baca[100];
    serialread.toCharArray(baca,64,0);
    if(baca[10] == '1' || baca[11] == '1')
    {
      actionStatus = 1;
    }
    else if(baca[10] == '0' || baca[11] == '0')
    {
      actionStatus = 0;
    }
    //Serial.println(baca[10]);
  }  
  actionStatus?turnOn():turnOff();  
}

void turnOn()
{
  if(timer(0,2000))sireneStatus=!sireneStatus; // on off every 1s
  sireneStatus?digitalWrite(pinSirene,LOW):digitalWrite(pinSirene,HIGH);
}

void turnOff()
{
  digitalWrite(pinSirene,HIGH);
}

bool timer(unsigned int id,unsigned long minidetik)
{
  currentTime[id] = millis();
  if(currentTime[id]-previousTime[id]>=minidetik)
  {
    previousTime[id] = millis();
    return true;
  }
  else 
    return false;
}
