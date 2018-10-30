/**************************
 * Serial Port Packet information
 **************************/
#include <arduino.h>

#define RX_PIN 0
#define TX_PIN 1

#define MP3_RECEIVED_LENGTH 10
#define MP3_SEND_LENGTH 10

// Packet structure
#define PKT_HEADER 0
#define PKT_VERSION 1
#define PKT_LENGTH 2
#define PKT_COMMAND 3
#define PKT_ACK 4
#define PKT_PARAM 5
#define PKT_CHECKSUM 7
#define PKT_END 9

// Command codes
#define CMD_NEXT 0x01
#define CMD_PREV 0x02
#define CMD_PLAYTRACK 0x03
#define CMD_INCVOL 0x04
#define CMD_DECVOL 0x05
#define CMD_SELVOL 0x06
#define CMD_SELEQ 0x07
#define CMD_PBMODE 0x08
#define CMD_PBSRC 0x09
#define CMD_STANDBY 0x0A
#define CMD_PWRON 0x0B
#define CMD_RST 0x0C
#define CMD_PLAY 0x0D
#define CMD_PAUSE 0x0E
#define CMD_SELFOLDER 0x0F
#define CMD_VOLADJ 0x10
#define CMD_REPEAT 0x11

#define MP3_EQ_NORMAL 0
#define MP3_EQ_POP 1
#define MP3_EQ_ROCK 2
#define MP3_EQ_JAZZ 3
#define MP3_EQ_CLASSIC 4
#define MP3_EQ_BASS 5

#define MP3_DEVICE_U_DISK 1
#define MP3_DEVICE_SD 2
#define MP3_DEVICE_AUX 3
#define MP3_DEVICE_SLEEP 4
#define MP3_DEVICE_FLASH 5


class mp3_player
{
  private:
	bool is_busy;
	int busy_pin;
	
  public:
  //uint8_t RcvData[MP3_RECEIVED_LENGTH];
  uint8_t SendData[MP3_SEND_LENGTH] = {0x7E, 0xFF, 06, 00, 01, 00, 00, 00, 00, 0xEF};

  mp3_player() {}
  
  void Begin(int _busy_pin)
  {
	  busy_pin = _busy_pin;
	  pinMode(busy_pin, INPUT);
	  is_busy = false;
	  Send_Packet(CMD_STANDBY, 0, 0);
  }
  
  void Send_Packet(uint8_t cmd, uint8_t high, uint8_t low)
  {
    SendData[PKT_LENGTH] = (uint8_t)0x06;
    SendData[PKT_COMMAND] = cmd;
    SendData[PKT_PARAM] = high;
    SendData[PKT_PARAM+1] = low;

	uint16_t checksum = CalculateCheckSum(SendData);
    SendData[PKT_CHECKSUM] = (uint8_t)(checksum >> 8);
    SendData[PKT_CHECKSUM+1] = (uint8_t)(checksum & 0x00FF);
    for (int i = 0; i < 10; i++)
	  Serial1.write(SendData[i]);
    delay(20);
  } // end Send_Packet

  uint16_t CalculateCheckSum(uint8_t *buffer)
  {
    uint16_t sum = 0;
  for (int i=PKT_VERSION; i<PKT_CHECKSUM; i++) {
    sum += buffer[i];
  }
  return -sum;
  } // end checksum

  void PlayTrack(uint16_t track)
  {
  uint8_t track_low = (uint8_t)(track & 0xFF);
  uint8_t track_high = (uint8_t)(track >> 8);
  
  Send_Packet(CMD_PLAYTRACK, track_high, track_low);
  } // end play track

  bool IsBusy()
  {
	  return digitalRead(busy_pin) == LOW;
  }
  
};


