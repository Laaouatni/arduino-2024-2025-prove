struct PinStruct {
  int id, value;
};

class laaDisplay {
 private:
  struct thisPins {
    PinStruct rs, en, d0, d1, d2, d3, d4, d5, d6, d7;
  } pins;
  const int DELAY = 1;  // 300ns -> 0.0003ms -> 1ms

  void updatePinState(PinStruct &_pin, int _value) {
    _pin.value = _value;
    digitalWrite(_pin.id, _pin.value);
  };

  void sendCommand() {
    this->updatePinState(this->pins.rs, this->pins.rs.value);
    this->updatePinState(this->pins.d4, this->pins.d4.value);
    this->updatePinState(this->pins.d5, this->pins.d5.value);
    this->updatePinState(this->pins.d6, this->pins.d6.value);
    this->updatePinState(this->pins.d7, this->pins.d7.value);

    sendingLogic();

    void sendingLogic() {
      this->updatePinState(this->pins.en, LOW );
      this->updatePinState(this->pins.en, HIGH);
      delay(this->DELAY);
      this->updatePinState(this->pins.en, LOW);
    };
  };

 public:
  laaDisplay(int rs, int en, int d4, int d5, int d6, int d7) {
    this->pins.rs = {rs, LOW};
    this->pins.en = {en, LOW};
    this->pins.d4 = {d4, LOW};
    this->pins.d5 = {d5, LOW};
    this->pins.d6 = {d6, LOW};
    this->pins.d7 = {d7, LOW};

    this->mode.config.setConfigMode();
    this->mode.config.functionSet.bitMode.setTo4();
    this->mode.config.functionSet.setNumberOf.lines.setTo1();
  };

  struct configurations {
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
    void setBitMode(bool is8BitMode) {
      this->updatePinState(this->pins.d4, this.pins.d4.value);
      this->sendCommand();
    };
    /*
      D3:
      - LOW  = 1 LINE DISPLAY
      - HIGH = 2 LINE DISPLAY
    */
    void setNumberOfLines(bool is2lines) {
      this->updatePinState(this->pins.d3, this.pins.d3.value);
      this->sendCommand();
    };
    /*
      D2:
      - LOW  = 5x8 DOTS MODE
      - HIGH = 5x11 DOTS MODE
    */
    void setDotMode(bool is5x11) {
      this->updatePinState(this->pins.d2, this.pins.d2.value);
      this->sendCommand();
    };
  }
};

laaDisplay myDisplay(2, 3, 4, 5, 6, 7);

void setup() {};

void loop() {};