#include <arduino.h>

#define SENSE_OFF 0x00
#define SENSE_COMP 0x01
#define SENSE_IDLE 0x02
#define SENSE_APPRCH 0x03
#define SENSE_RETRACT 0x04
#define SENSE_HOLD 0x05

class Sensor
{
  private:
  int16_t data[10];
  int16_t delta[10];
  
  public:
  uint8_t channel = 0;
  uint16_t hysteresis = 50;
  bool sense_start = false;
  uint8_t bcx = 0x20;
  uint8_t bcx_lpf = 15;
  uint8_t cag = 1;
  uint8_t state = SENSE_OFF;
  int32_t avg_data;
  int16_t avg_delta;
  uint16_t comp;
  uint16_t cntr;
  uint16_t start_idle_time;
  bool state_changed = false;
  Sensor() {
    state = SENSE_OFF;
    channel = 0;
  };

  void begin(uint8_t _ch, uint16_t _hysteresis) {
    channel = _ch;
    comp = 0;
    hysteresis = _hysteresis;
    sense_start = true;
  }

  void set_hysteresis(uint16_t _hysteresis)
  {
    hysteresis = _hysteresis;
  }

  void recomp() 
  {
    state = SENSE_OFF;
    sense_start = true;
  }
  void update( uint16_t *alldata) {
    int32_t sum = 0;
    int32_t sum_delta = 0;
    for (int i = 1; i < 10; i++) {
      data[i] = data[i-1];
      delta[i] = delta[i-1];
      sum = sum + data[i];
      sum_delta = sum_delta + delta[i];
    }
    
    data[0] = alldata[channel] - comp;
    delta[0] = data[0] - data[1];
  	uint8_t old_state = state;
    switch (state) {
      case SENSE_OFF:
          for (int i = 1; i < 10; i++) {
             data[i] = 0;
             delta[i] = 0;
          }
          avg_data = alldata[channel];
          if (sense_start) {
            state = SENSE_COMP;
            sense_start = false;
          }
          cntr = 0;
          comp = 0;
          break;
      case SENSE_COMP:
            avg_data = (avg_data * 31 + data[0]) / 32;
            if (cntr++ > 200) {
              cntr = 0;
              state = SENSE_IDLE;
              comp = (uint16_t)avg_data;
              avg_data = 0;
              avg_delta = 0;
			}
            break;
      case SENSE_IDLE:
      case SENSE_APPRCH:
      case SENSE_RETRACT:
      case SENSE_HOLD:
           avg_data = (sum + data[0]) / 10; //(avg_data * 15 + data) / 16;
	         avg_delta = (sum_delta + delta[0]) / 10;
           if (abs(avg_data) < 600) {
             if (state != SENSE_IDLE)
               start_idle_time = millis();
             state = SENSE_IDLE;
/*             uint16_t idle_time = millis() - start_idle_time;
             if (idle_time > 5000) {
                comp = avg_data + comp;
                avg_data = 0;
                avg_delta = 0;
                for (int i = 0; i < 10; i++) {
                  data[i] = 0;
                  delta[i] = 0;
                }
             } */
           }
           else {
             if (avg_delta > hysteresis)
               state = SENSE_APPRCH; 
             else if (avg_delta < -hysteresis)
               state = SENSE_RETRACT; 
             else
               state = SENSE_HOLD;
           } // end else
			break;
      default:
            state = SENSE_OFF;
			//Serial.println("how did we get here?");
            break;
    } // end switch
	if (old_state == state)
		state_changed = false;
	else
		state_changed = true;
  } // end update

  void end()
  {
    state = SENSE_OFF;
  }
}; // end class Sensor
