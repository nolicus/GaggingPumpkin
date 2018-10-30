#include "Comet.h"
//#include "Eeprom.h"
#include "Timer.h"
#include "Spi.h"
#include "Gpio.h"
#include "Comet_Sensor.cpp"
#include "MP3_Player.cpp"
#include "Cirque_Pumpkin.h"

measResult_t results;
Sensor green_wires;
Sensor blue_wires;
Sensor orange_wires;
mp3_player myMP3;

uint16_t hysteresis = 10;

void setup() {

  Comet_Init(&spiHandle, &gpioHandle);  
  Comet_WriteRegisters(PWCAddr, PWCRegs, 3);
  Comet_WriteRegisters(ELD_SELAddr, ELD_SEL, 16);
  Comet_WriteRegisters(BCX_LPFAddr, BCX_LPFRegs, 8);
  Comet_WriteRegisters(GAIN_ADJAddr, GAIN_ADJRegs, 8);

 // Go through autocal twice because of cross-talk between channels
//  BCXRegs[1] = autocalbcx(1);
//  BCXRegs[5] = autocalbcx(5);
  BCXRegs[9] = autocalbcx(9);
  Comet_WriteRegisters(BCXAddr, BCXRegs, 16);
//  BCXRegs[1] = autocalbcx(1);
//  BCXRegs[5] = autocalbcx(5);
  BCXRegs[9] = autocalbcx(9);
  Comet_WriteRegisters(BCXAddr, BCXRegs, 16);

  green_wires.begin((uint8_t)9, hysteresis);
  orange_wires.begin((uint8_t)5, hysteresis);
  blue_wires.begin((uint8_t)1, hysteresis);
 
  Serial.begin(115200);
//  while(!Serial); // needed for USB

  Serial.print("Read Firmware ID, version and device status ");
  Serial.print(Comet_ReadRegister(SYS__TR_BG));
  Serial.print(" ");
  Serial.println(Comet_ReadRegister(SYS__TR_BI));
  
  Serial.print("Register test ");
  for (int i = 0; i < 15; i++)
  {
    Serial.print(Comet_ReadRegister(i));
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("BCX test ");
  for (int i = 0; i < 15; i++)
  {
    Serial.print(Comet_ReadRegister(BCXAddr+i));
    Serial.print(" ");
  }    
  Serial1.begin(9600); // mp3 player
  myMP3.Begin(2);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
  myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);


  Control_Update();   // state starts out as reset, so do a reset
  Comet_StartMeasurement();
  delay(100);
  if (Comet_DataIsReady() )
  {
    Comet_ReadMeasResults(&results);
    Serial.print("\nInitial values, green: ");
    Serial.print(results.Array[9]);
    Serial.print(" orange: ");
    Serial.print(results.Array[5]);
    Serial.print(" blue: ");
    Serial.println(results.Array[1]);
  }
  else
    Serial.println("No data from Comet");
   myMP3.PlayTrack(MP3T0_JACK);
   delay(3000);
//   myMP3.PlayTrack(MP3T1_WATCHIT);
//   delay(3000);
}

void loop() {
if ( Comet_DataIsReady() )
{
  Comet_ReadMeasResults(&results);
  green_wires.update(results.Array);
  blue_wires.update(results.Array);
  orange_wires.update(results.Array);

  Control_Update();
  Comet_StartMeasurement();
}
if (Serial.available())
{
  Comet_StopMeasurement();
  /*if (Serial.read() == '+')
  {
    // BCX1_VAL++;
    green_wires.set_hysteresis(++hysteresis);
  }
  if (Serial.read() == '-')
  {
    //    BCX1_VAL--;
    green_wires.set_hysteresis(--hysteresis);
  }
*/
//  Comet_WriteRegister( (BCXAddr+1), BCX1_VAL);
  if (Serial.read() == 'c')
  {  
    Serial.println("Doing a Compensation");
    delay(1000);
    green_wires.recomp();
//    delay(20);
//    green_wires.begin((uint8_t)1, hysteresis);
  }
  Comet_StartMeasurement();
}

  if (Serial.available())
  {
    uint8_t ch = Serial.read();
/*
    if (ch == 'p')
        myMP3.Send_Packet(CMD_PLAY, 0x00, 0x00);
    if (ch == 's')
        myMP3.Send_Packet(CMD_PAUSE, 0x00, 0x00);
    if (ch == 'n')
        myMP3.Send_Packet(CMD_NEXT, 0x00, 0x00);
    if (ch == 'r')
        myMP3.Send_Packet(CMD_PREV, 0x00, 0x00);
*/
    if (ch == '+')
        myMP3.Send_Packet(CMD_INCVOL, 0x00, 0x00);
    if (ch == '-')
        myMP3.Send_Packet(CMD_DECVOL, 0x00, 0x00);
    delay(500);
  }  
}

uint16_t busy_count = 0;

void Control_Update()
{
  uint8_t next_state = control_state;
    if (myMP3.IsBusy())
    {
      if (busy_count == 0)
      {
        Serial.print("Busy ");
      }
      else
        Serial.print(".");

      busy_count++;
      if (busy_count > 64)
      {
        Serial.print("\r\n");
        busy_count = 1;
      }
      delay(200);
      return;
    }
    else
      busy_count = 0;
  
  switch (control_state)  
  {
    case CTRL_RESET:
      sound_file = -1;  // no file
      sound3_played = false;
      if ( (green_wires.state == SENSE_APPRCH) && (green_wires.avg_data > APPRCH_LVL1) )
        {
          switch (green_wires.avg_data % 3)
          {
            case 1: sound_file = MP3T1_GETHAND1;
            break;
            case 2: sound_file = MP3T1_GETHAND2;
            break;
            default: sound_file = MP3T1_WATCHIT;
            break;
          }
          
          myMP3.PlayTrack(sound_file);
          next_state = CTRL_SOUND1;
          Serial.println("Playing SOUND1");
          Serial.print("green: ");
          Serial.println(green_wires.avg_data);
          delay(250);
        }
   break;
   case CTRL_SOUND1:
      if (~myMP3.IsBusy())
      {
        if (green_wires.avg_data < RETRCT_LVL0)
        {
          next_state = CTRL_RESET;
          Serial.print("Resetting: green = ");
          Serial.println(green_wires.avg_data);
  //        myMP3.PlayTrack(MP3T4_AHHH_THANKYOU); //MP3T4_AHHH_THANKYOU ABTTIME
          delay(500);
        }
        else if ( (green_wires.state == SENSE_APPRCH) && (green_wires.avg_data > APPRCH_LVL2) )
        {
          myMP3.PlayTrack(MP3T2_GAG_GAG);
          Serial.println("Playing MP3_TRACK_GAGS");
          delay(250);
          next_state = CTRL_SOUND2;
        }
      }
    break;
    case CTRL_SOUND2:
        if (green_wires.avg_data < RETRCT_LVL1)
        {
          delay(50);
          myMP3.PlayTrack(MP3T5_BRAIN); //MP3T4_AHHH_ABTTIME); //MP3T4_AHHH_THANKYOU 
          next_state = CTRL_RETRACT;
        }
        else if ( (green_wires.avg_data > APPRCH_LVL3)  ) //&& ~sound3_played
        {
          delay(250);
          myMP3.PlayTrack(MP3T3_TONSILS);
          Serial.println("Playing MP3_TRACK_TONSILS");
          sound3_played = true;
        }
        else if ( (green_wires.avg_data > APPRCH_LVL2) )
        {
          delay(250);
          myMP3.PlayTrack(MP3_TRACK_WATCH);
          Serial.println("Playing MP3_TRACK_WATCHIT");
        }
    break;
    
    case CTRL_RETRACT:
        if (green_wires.avg_data < RETRCT_LVL0)
          next_state = CTRL_RESET;
    break;
    
    default:
        next_state = CTRL_RESET;
  }
  control_state = next_state;
}

void Debug()
{
  /****************************************
 * Debug code starts here
 ****************************************/
  switch (green_wires.state) {
    case SENSE_APPRCH:
         Serial.print("Approach: Green ");
         Serial.print(green_wires.avg_data);
         Serial.print(" (delta=");
         Serial.print(green_wires.avg_delta);
         Serial.print(") : Orange ");
         Serial.print(orange_wires.avg_data);
         Serial.print(" (delta=");
         Serial.print(orange_wires.avg_delta);
         Serial.print(") : Blue ");
         Serial.print(blue_wires.avg_data);
         Serial.print(" (delta=");
         Serial.print(blue_wires.avg_delta);
         Serial.println(")");

      break;
      
    case SENSE_RETRACT:
         Serial.print("Retracting: Green ");
         Serial.print(green_wires.avg_data);
         Serial.print(" (delta=");
         Serial.print(green_wires.avg_delta);
         Serial.print(") : Orange ");
         Serial.print(orange_wires.avg_data);
         Serial.print(" (delta=");
         Serial.print(orange_wires.avg_delta);
         Serial.print(") : Blue ");
         Serial.print(blue_wires.avg_data);
         Serial.print(" (delta=");
         Serial.print(blue_wires.avg_delta);
         Serial.println(")");
      break;

    case SENSE_HOLD:
         Serial.print("Holding: Green ");
         Serial.print(green_wires.avg_data);
         Serial.print(" (delta=");
         Serial.print(green_wires.avg_delta);
         Serial.print(") : Orange ");
         Serial.print(orange_wires.avg_data);
         Serial.print(" (delta=");
         Serial.print(orange_wires.avg_delta);
         Serial.print(") : Blue ");
         Serial.print(blue_wires.avg_data);
         Serial.print(" (delta=");
         Serial.print(blue_wires.avg_delta);
         Serial.println(")");
      break;

    case SENSE_IDLE:
      if (green_wires.state_changed) {
         Serial.print("Idle: Green ");
         Serial.print(results.Array[1]);
         Serial.print(" : Orange ");
         Serial.print(results.Array[5]);
         Serial.print(" : Blue ");
         Serial.print(results.Array[9]);
      }
      break;

    case SENSE_COMP:
       Serial.print("Doing comp: Green ");
       Serial.print(results.Array[1]);
       Serial.println();
    break;
    default: Serial.println();
  }
  if (green_wires.state != SENSE_COMP)
    delay(30);
  else
    delay(2);

/*************************************
 * Real code starts here
 *************************************/

  if (green_wires.state == SENSE_APPRCH)
  {
    if (green_wires.avg_data > 6000)
    {
      Serial.print("\t\tYou got bit!!!!!!!");

      if (green_wires.avg_delta > 400)
        Serial.println("\t\tYou are fast, but I am faster!");
      else if (green_wires.avg_delta < 100)
        Serial.println("\t\tYou are way too slow!");
    }

    if (green_wires.avg_data > 5000)
      myMP3.PlayTrack(1);
    else if (green_wires.avg_data > 3000)
      myMP3.PlayTrack(2);
    else if (green_wires.avg_data > 1000)
      myMP3.PlayTrack(3);
    delay(1500);
  } // end approaching
  if (green_wires.state == SENSE_RETRACT)
  {
    if (green_wires.avg_data > 500)
      myMP3.PlayTrack(4);
    else if (green_wires.avg_data < 2000)
      myMP3.PlayTrack(5);
    delay(100);
  }
}

/*****************************************
 * Runs through all BCX codes and returns the value
 * Does not account for noise very well
 */
uint8_t autocalbcx(uint8_t chan)
{
  uint8_t i;
  Serial.println();
  for (i = 0; i < 64; i++)
  {
     Comet_WriteRegister(BCXAddr+chan, i);
     Comet_StartMeasurement();
     delay(20);
     if (Comet_DataIsReady() )
      {
        Comet_ReadMeasResults(&results);
        Serial.print("Chan: ");
        Serial.print(chan);
        Serial.print(" code: ");
        Serial.print(i);
        Serial.print(" data: ");
        Serial.println(results.Array[chan]);
      }
      if ( (results.Array[chan] < 25000) && (results.Array[chan] > 20000) )
        break;
  }
  return(i);
}  // end autocal
