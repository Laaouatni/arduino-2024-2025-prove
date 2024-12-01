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
    this->updatePinState(this->pins.rs, this->pins.rs.value);
    for(auto _thisDataStructPin : pins.d) {
      this->updatePinState(_thisDataStructPin, _thisDataStructPin.value);
    };
    sendingLogic();

    void sendingLogic() {
      this->updatePinState(this->pins.en, LOW );
      this->updatePinState(this->pins.en, HIGH);
      delay(this->DELAY);
      this->updatePinState(this->pins.en, LOW);
    };
  };

 public:
  laaDisplay(int rs, int en, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7) {
    this->pins.rs = {rs, LOW};
    this->pins.en = {en, LOW};
    this->pins.d0 = {d0, LOW};
    this->pins.d1 = {d1, LOW};
    this->pins.d2 = {d2, LOW};
    this->pins.d3 = {d3, LOW};
    this->pins.d4 = {d4, LOW};
    this->pins.d5 = {d5, LOW};
    this->pins.d6 = {d6, LOW};
    this->pins.d7 = {d7, LOW};
  };

  struct Configurations {
    struct FunctionSet {
      /*
        RS:
        - LOW   = CONFIG MODE
        - HIGH  = WRITING MODE
      */
      void setConfigMode() { 
        this->updatePinState(this->pins.rs, LOW);
        this->sendCommand();
      };
      /*
        D4:
        - LOW  = 4BIT MODE
        - HIGH = 8BIT MODE
      */
      void setBitMode(bool _is8BitMode) {
        this->updatePinState(this->pins.d4, _is8BitMode);
        this->sendCommand();
      };
      /*
        D3:
        - LOW  = 1 LINE DISPLAY
        - HIGH = 2 LINE DISPLAY
      */
      void setNumberOfLines(bool _is2lines) {
        this->updatePinState(this->pins.d3, _is2lines);
        this->sendCommand();
      };
      /*
        D2:
        - LOW  = 5x8 DOTS MODE
        - HIGH = 5x11 DOTS MODE
      */
      void setDotMode(bool _is5x11) {
        this->updatePinState(this->pins.d2, _is5x11);
        this->sendCommand();
      };
    } functionSet;
  } configurations;
};

laaDisplay myDisplay(2, 3, 4, 5, 6, 7, 8, 9, 10, 11);

void setup() {};

void loop() {};