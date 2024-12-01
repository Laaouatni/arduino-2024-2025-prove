struct PinStruct {
  int id, value;
};

class laaDisplay {
 private:
  struct thisPins {
    PinStruct rs, en, d4, d5, d6, d7;
  } pins;
  const int DELAY = 1;  // 300ns -> 0.0003ms -> 1ms

  void sendCommand() {
    digitalWrite(this->pins.rs.id, this->pins.rs.value);
    digitalWrite(this->pins.d4.id, this->pins.d4.value);
    digitalWrite(this->pins.d5.id, this->pins.d5.value);
    digitalWrite(this->pins.d6.id, this->pins.d6.value);
    digitalWrite(this->pins.d7.id, this->pins.d7.value);

    this->pins.en.value = LOW;
    digitalWrite(this->pins.en.id, this->pins.en.value);

    this->pins.en.value = HIGH;
    digitalWrite(this->pins.en.id, this->pins.en.value);
    delay(this->DELAY);

    this->pins.en.value = LOW;
    digitalWrite(this->pins.en.id, this->pins.en.value);
  };

  void setConfigMode() {
    /*
      RS:
      - LOW   = CONFIG MODE
      - HIGH  = WRITING MODE
    */
    this->pins.rs.value = LOW;
    this->pins.en.value = LOW;
    this->pins.d4.value = LOW;
    this->pins.d5.value = LOW;
    this->pins.d6.value = LOW;
    this->pins.d7.value = LOW;

    sendCommand();
  };

 public:
  laaDisplay(int rs, int en, int d4, int d5, int d6, int d7) {
    this->pins.rs.id = rs;
    this->pins.en.id = en;
    this->pins.d4.id = d4;
    this->pins.d5.id = d5;
    this->pins.d6.id = d6;
    this->pins.d7.id = d7;

    this->setConfigMode();
  };

  struct Mode {
    struct Config {
      struct FunctionSet {
        struct bitMode {
          void setTo4() {
            /*
              D5:
              - HIGH = FUNCTION SET MODE
            */
            this->pins.d5.value = HIGH;
            /*
              D4:
              - LOW  = 4BIT MODE
              - HIGH = 8BIT MODE
            */
            this->pins.d4.value = LOW;
          };
          void setTo8() {
            /*
              D5:
              - HIGH = FUNCTION SET MODE
            */
            this->pins.d5.value = HIGH;
            /*
              D4:
              - LOW  = 4BIT MODE
              - HIGH = 8BIT MODE
            */
            this->pins.d4.value = HIGH;
          };
        } bitMode;
        struct SetNumberOf {
          struct lines {
            void setToOne() {};
            void setToTwo() {};
          } lines;
          struct Dots {
            void mode5x8() {
              /*
                D5:
                - HIGH = FUNCTION SET MODE
              */
              this->pins.d5.value = HIGH;
              /*
                D2:
                - LOW  = 5x8 DOTS MODE
                - HIGH = 5x11 DOTS MODE
              */
              this->pins.d2.value = LOW;
            };
            void mode5x11() {
              /*
                D5:
                - HIGH = FUNCTION SET MODE
              */
              this->pins.d5.value = HIGH;
              /*
                D2:
                - LOW  = 5x8 DOTS MODE
                - HIGH = 5x11 DOTS MODE
              */
              this->pins.d2.value = HIGH;
            };
          } dots;
        } setNumberOf;
      } functionSet;
    } config;
  } mode;
};

laaDisplay myDisplay(2, 3, 4, 5, 6, 7);

void setup() { myDisplay.mode.config.functionSet.bitMode.setTo4(); };

void loop() {};