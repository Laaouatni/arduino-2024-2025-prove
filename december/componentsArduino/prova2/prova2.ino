struct PinStruct {
  int id, value;
};

class laaDisplay {
 private:
  struct thisPins {
    PinStruct rs, en, d4, d5, d6, d7;
  } pins;

 public:
  laaDisplay(int rs, int en, int d4, int d5, int d6, int d7) {
    this->pins.rs.id = rs;
    this->pins.en.id = en;
    this->pins.d4.id = d4;
    this->pins.d5.id = d5;
    this->pins.d6.id = d6;
    this->pins.d7.id = d7;
  };

  struct Mode {
    struct config {
      struct functionSet {
        struct bitMode {
          void setTo4() {};
          void setTo8() {};
        } bitMode;
        struct setNumberOf {
          struct lines {
            void setToOne() {};
            void setToTwo() {};
          } lines;
          struct dots {
            void mode5x8 () {};
            void mode5x11 () {};
          } dots;
        } setNumberOf;
      } functionSet;
    } config;
  } Mode;
};