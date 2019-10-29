#ifndef EncoderPCI_h
#define EncoderPCI_h

//#define LIBCALL_ENABLEINTERRUPT
#include <Arduino.h>
#include <EnableInterrupt.h>

#define IO_REG_TYPE  uint8_t
#define ENCODER_ARGLIST_SIZE 24
#define PIN_TO_BASEREG(pin)             (portInputRegister(digitalPinToPort(pin)))
#define PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define DIRECT_PIN_READ(base, mask)     (((*(base)) & (mask)) ? 1 : 0)

typedef struct {
                volatile IO_REG_TYPE * pin1_register;
                volatile IO_REG_TYPE * pin2_register;
                IO_REG_TYPE            pin1_bitmask;
                IO_REG_TYPE            pin2_bitmask;
                uint8_t                state;
                int32_t                position;
} Encoder_internal_state_t;

class Encoder
{
 public:

     /*************************************************************/
    // Define Encoder objects using this :
    // Encoder myEnc= Encoder(pinA, pinB);
    Encoder(uint8_t pin1, uint8_t pin2)
    {

    #ifdef INPUT_PULLUP
    pinMode(pin1, INPUT_PULLUP);
    pinMode(pin2, INPUT_PULLUP);
    #else
    pinMode(pin1, INPUT);
    digitalWrite(pin1, HIGH);
    pinMode(pin2, INPUT);
    digitalWrite(pin2, HIGH);
    #endif

    encoder.pin1_register = PIN_TO_BASEREG(pin1);
    encoder.pin1_bitmask  = PIN_TO_BITMASK(pin1);
    encoder.pin2_register = PIN_TO_BASEREG(pin2);
    encoder.pin2_bitmask  = PIN_TO_BITMASK(pin2);
    encoder.position = 0;

    // allow time for a passive R-C filter to charge
    // through the pullup resistors, before reading
    // the initial state
    delayMicroseconds(2000);
    uint8_t s = 0;
    if (DIRECT_PIN_READ(encoder.pin1_register, encoder.pin1_bitmask)) s |= 1;
    if (DIRECT_PIN_READ(encoder.pin2_register, encoder.pin2_bitmask)) s |= 2;
    encoder.state = s;
    interrupts_in_use = attach_interrupt(pin1, &encoder);
    interrupts_in_use += attach_interrupt(pin2, &encoder);

    }

    /*************************************************************/
    // Read encoder output
    // int32_t encoderOutput = myEnc.read
    int32_t read() {
    noInterrupts();
    int32_t tempTicks = encoder.position;
    interrupts();

    return tempTicks;
    }


    /*************************************************************/
    //  Reset encoder count to a value
    //  myEnc.write(value)
    //  myEnc.write(0) // for reseting to 0 (home position)
    void write(int32_t value) {
    noInterrupts();
    encoder.position = value;
    interrupts();
    }


    /*************************************************************/
    // Internal methods and properties:


    static void update(Encoder_internal_state_t *arg) {
        uint8_t p1val = DIRECT_PIN_READ(arg->pin1_register, arg->pin1_bitmask);
        uint8_t p2val = DIRECT_PIN_READ(arg->pin2_register, arg->pin2_bitmask);
        uint8_t state = arg->state & 3;
        if (p1val) state |= 4;
        if (p2val) state |= 8;
        arg->state = (state >> 2);
        switch (state) {
            case 1: case 7: case 8: case 14:
                arg->position++;
                return;
            case 2: case 4: case 11: case 13:
                arg->position--;
                return;
            case 3: case 12:
                arg->position += 2;
                return;
            case 6: case 9:
                arg->position -= 2;
                return;
        }
    }

    static Encoder_internal_state_t * interruptArgs[ENCODER_ARGLIST_SIZE];

 private:
  static uint8_t attach_interrupt(uint8_t pin, Encoder_internal_state_t *state) {
    switch (pin) {
        case 0:
            interruptArgs[0] = state;
            enableInterrupt(0, isr0, CHANGE);
            break;
        case 1:
            interruptArgs[1] = state;
            enableInterrupt(1, isr1, CHANGE);
            break;
        case 2:
            interruptArgs[2] = state;
            enableInterrupt(2, isr2, CHANGE);
            break;
        case 3:
            interruptArgs[3] = state;
            enableInterrupt(3, isr3, CHANGE);
            break;
        case 4:
            interruptArgs[4] = state;
            enableInterrupt(4, isr4, CHANGE);
            break;
        case 5:
            interruptArgs[5] = state;
            enableInterrupt(5, isr5, CHANGE);
            break;
        case 6:
            interruptArgs[6] = state;
            enableInterrupt(6, isr6, CHANGE);
            break;
        case 7:
            interruptArgs[7] = state;
            enableInterrupt(7, isr7, CHANGE);
            break;
        case 8:
            interruptArgs[8] = state;
            enableInterrupt(8, isr8, CHANGE);
            break;
        case 9:
            interruptArgs[9] = state;
            enableInterrupt(9, isr9, CHANGE);
            break;
        case 10:
            interruptArgs[10] = state;
            enableInterrupt(10, isr10, CHANGE);
            break;
        case 11:
            interruptArgs[11] = state;
            enableInterrupt(11, isr11, CHANGE);
            break;
        case 12:
            interruptArgs[12] = state;
            enableInterrupt(12, isr12, CHANGE);
            break;
        case 13:
            interruptArgs[13] = state;
            enableInterrupt(13, isr13, CHANGE);
            break;
        case 14:
            interruptArgs[14] = state;
            enableInterrupt(14, isr14, CHANGE);
            break;
        case 15:
            interruptArgs[15] = state;
            enableInterrupt(15, isr15, CHANGE);
            break;
        case 16:
            interruptArgs[16] = state;
            enableInterrupt(16, isr16, CHANGE);
            break;
        case 17:
            interruptArgs[17] = state;
            enableInterrupt(17, isr17, CHANGE);
            break;
        case 18:
            interruptArgs[18] = state;
            enableInterrupt(18, isr18, CHANGE);
            break;
        case 19:
            interruptArgs[19] = state;
            enableInterrupt(19, isr19, CHANGE);
            break;
        case 20:
            interruptArgs[21] = state;
            enableInterrupt(20, isr20, CHANGE);
            break;
        case 21:
            interruptArgs[21] = state;
            enableInterrupt(21, isr21, CHANGE);
            break;
        case 22:
            interruptArgs[22] = state;
            enableInterrupt(22, isr22, CHANGE);
            break;
        case 23:
            interruptArgs[23] = state;
            enableInterrupt(23, isr23, CHANGE);
            break;
        default:
            return 0;
    }
    return 1;
  }

  Encoder_internal_state_t encoder;
  uint8_t interrupts_in_use;

  static void isr0(void) { update(interruptArgs[0]); }
  static void isr1(void) { update(interruptArgs[1]); }
  static void isr2(void) { update(interruptArgs[2]); }
  static void isr3(void) { update(interruptArgs[3]); }
  static void isr4(void) { update(interruptArgs[4]); }
  static void isr5(void) { update(interruptArgs[5]); }
  static void isr6(void) { update(interruptArgs[6]); }
  static void isr7(void) { update(interruptArgs[7]); }
  static void isr8(void) { update(interruptArgs[8]); }
  static void isr9(void) { update(interruptArgs[9]); }
  static void isr10(void) { update(interruptArgs[10]); }
  static void isr11(void) { update(interruptArgs[11]); }
  static void isr12(void) { update(interruptArgs[12]); }
  static void isr13(void) { update(interruptArgs[13]); }
  static void isr14(void) { update(interruptArgs[14]); }
  static void isr15(void) { update(interruptArgs[15]); }
  static void isr16(void) { update(interruptArgs[16]); }
  static void isr17(void) { update(interruptArgs[17]); }
  static void isr18(void) { update(interruptArgs[18]); }
  static void isr19(void) { update(interruptArgs[19]); }
  static void isr20(void) { update(interruptArgs[20]); }
  static void isr21(void) { update(interruptArgs[21]); }
  static void isr22(void) { update(interruptArgs[22]); }
  static void isr23(void) { update(interruptArgs[23]); }
};

#endif //FlexibleEncoder_h
