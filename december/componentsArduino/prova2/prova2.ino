struct PinStruct {
  int id, value;
};

class laaDisplay {
 private:
  struct thisPins {
    PinStruct rs, en, d[8];
  } pins;
  const int DELAY = 1;  // 300ns -> 0.0003ms -> 1ms

  void updatePinState(PinStruct &_pin, int _value) {
    _pin.value = _value;
    digitalWrite(_pin.id, _pin.value);
  };

  void sendCommand() {
    this->updatePinState(this->pins.en, LOW);
    this->updatePinState(this->pins.en, HIGH);
    delay(this->DELAY);
    this->updatePinState(this->pins.en, LOW);
  };

  void init() {
    this->pins.rs.value = LOW;
    this->pins.en.value = LOW;
    this->pins.d0.value = LOW;
    this->pins.d1.value = LOW;
    this->pins.d2.value = LOW;
    this->pins.d3.value = LOW;
    this->pins.d4.value = LOW;
    this->pins.d5.value = LOW;
    this->pins.d6.value = LOW;
    this->pins.d7.value = LOW;
  };

  struct Configurations {
    struct FunctionSet {
      /*
        D5:
        - LOW  = OFF FUNCTION SET
        - HIGH = ON  FUNCTION SET
      */
      void setFunctionSetMode(bool _isOn) {
        this->updatePinState(this->pins.d5, _isOn);
        // this->sendCommand();
      };
      /*
        D4:
        - LOW  = 4BIT MODE
        - HIGH = 8BIT MODE
      */
      void setBitMode(bool _is8BitMode) {
        this->configurations.functionSet.setFunctionSetMode(true);
        this->updatePinState(this->pins.d4, _is8BitMode);
        // this->sendCommand();
      };
      /*
        D3:
        - LOW  = 1 LINE DISPLAY
        - HIGH = 2 LINE DISPLAY
      */
      void setNumberOfLines(bool _is2lines) {
        this->configurations.functionSet.setFunctionSetMode(true);
        this->updatePinState(this->pins.d3, _is2lines);
        // this->sendCommand();
      };
      /*
        D2:
        - LOW  = 5x8 DOTS MODE
        - HIGH = 5x11 DOTS MODE
      */
      void setDotMode(bool _is5x11) {
        this->configurations.functionSet.setFunctionSetMode(true);
        this->updatePinState(this->pins.d2, _is5x11);
        // this->sendCommand();
      };
    } functionSet;
    /*
      RS:
      - LOW   = CONFIG MODE
      - HIGH  = WRITING MODE
    */
    void setConfigMode() {
      this->updatePinState(this->pins.rs, LOW);
      // this->sendCommand();
    };
    struct Methods {
      void clear() {
        this->init();
        this->updatePinState(this->pins.d0, HIGH);
        this->sendCommand();
      };
      void home() {
        this->init();
        this->updatePinState(this->pins.d1, HIGH);
        this->sendCommand();
      };
      /*
        D2:
        - LOW   = LCD SPENTO
        - HIGH  = LCD ACCESSO

        D1:
        - LOW   = CURSOR OFF
        - HIGH  = CURSOR ON

        D0:
        - LOW   = CURSOR_BLINK OFF
        - HIGH  = CURSOR_BLINK ON
      */
      void backlightCursorRegister(bool _isBacklightOn, bool _isCursorOn = false, bool _isCursorBlinking = false) {
        this->init();
        this->updatePinState(this->pins.d3, HIGH);
        this->updatePinState(this->pins.d2, _isBacklightOn);
        this->updatePinState(this->pins.d1, _isCursorOn);
        this->updatePinState(this->pins.d0, _isCursorBlinking);
      };
    } methods;
  } configurations;

 public:
  laaDisplay(int rs, int en, int d0, int d1, int d2, int d3, int d4, int d5,
             int d6, int d7) {
    this->pins.rs.id = rs;
    this->pins.en.id = en;
    this->pins.d0.id = d0;
    this->pins.d1.id = d1;
    this->pins.d2.id = d2;
    this->pins.d3.id = d3;
    this->pins.d4.id = d4;
    this->pins.d5.id = d5;
    this->pins.d6.id = d6;
    this->pins.d7.id = d7;

    this->init();
    this->configurations.setConfigMode();
    this->configurations.setFunctionSetMode(true);
    this->configurations.functionSet.setBitMode(true);
    this->configurations.functionSet.setNumberOfLines(false);
    this->configurations.functionSet.setDotMode(false);
    this->configurations.methods.clear();
    this->configurations.methods.home();
    this->configurations.methods.backlightCursorRegister(true, false, false);
  };
};

laaDisplay myDisplay(2, 3, 4, 5, 6, 7, 8, 9, 10, 11);

void setup() {};

void loop() {};