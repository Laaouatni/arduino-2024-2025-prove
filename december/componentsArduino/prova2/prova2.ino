struct PinStruct {
  int id, value;
};

class laaDisplay {
  private:
    struct thisPins {
      PinStruct rs, en, d4, d5, d6, d7;
    };

  public:
    laaDisplay(rs, en, d4, d5, d6, d7) {
      this->rs = rs;
      this->en = en;
      this->d4 = d4;
      this->d5 = d5;
      this->d6 = d6;
      this->d7 = d7;
    };

    struct config {
      struct functionSet {
        struct setBitMode {
          void 4bit;
          void 8bit;
        };
        struct setNumberOf {
          struct lines {
            void one;
            void two;
          };
          struct dots {
            void 5per8;
            void 5per11;
          };
        };
      };
    };
};