// WiiExpansions - Arduino library to control Wii Remote expansion devices.
// Copyright Julien Lebunetel 2018
// MIT License

// ensure this library description is only included once
#ifndef WiiExpansions
#define WiiExpansions

// include description files for other libraries used

// library interface description
class Button
{
  // user-accessible "public" interface
  public:
    Button() { value = false; previousValue = false; };
    void set(bool value) { this->previousValue = this->value; this->value = value; };
    bool get() { return value; };
    bool isPressed() { return value; };
    bool isReleased() { return !value; };
    bool hasChanged() { return (value != previousValue); };
    bool isJustPressed() { return (hasChanged() && isPressed()); };
    bool isJustReleased() { return (hasChanged() && isReleased()); };

  // library-accessible "private" interface
  protected:
    bool value;
    bool previousValue;
};


class Potentiometer
{
  // user-accessible "public" interface
  public:
    Potentiometer() { value = 0; previousValue = 0; };
    void set(uint16_t value) { this->previousValue = this->value; this->value = value; };
    uint16_t get() { return value; };
    bool hasChanged() { return (value != previousValue); };

  // library-accessible "private" interface
  protected:
    uint16_t value;
    uint16_t previousValue;
};


class WiiExpansion
{
  // user-accessible "public" interface
  public:
    WiiExpansion();
    void init();
    void read();

  // library-accessible "protected" interface
  protected:
    byte data[6];
};


class WiiNunchuk : public WiiExpansion
{
  // user-accessible "public" interface
  public:
    // WiiNunchuk();
    void init();
    void read();
    void print();

    Button C;
    Button Z;

    Potentiometer stick_X;
    Potentiometer stick_Y;

    Potentiometer accelerometer_X;
    Potentiometer accelerometer_Y;
    Potentiometer accelerometer_Z;
};


class WiiClassicController : public WiiExpansion
{
  // user-accessible "public" interface
  public:
    //WiiClassicController();
    void init();
    void read();
    void print();

    Button L;
    Button R;

    Button select;
    Button home;
    Button start;

    Button X;
    Button Y;
    Button A;
    Button B;

    Button ZL;
    Button ZR;

    Button pad_L;
    Button pad_R;
    Button pad_U;
    Button pad_D;

    Potentiometer stick_LX;
    Potentiometer stick_LY;
    Potentiometer stick_RX;
    Potentiometer stick_RY;
    Potentiometer bumper_L;
    Potentiometer bumper_R;
};



class WiiGuitar : public WiiExpansion
{
  // user-accessible "public" interface
  public:
    // WiiGuitar();
    void init();
    void read();
    void print();

    Button strum_bar_down;
    Button strum_bar_up;

    Button bridge;
    Button plus_button;

    Button green;
    Button red;
    Button yellow;
    Button blue;
    Button orange;

    Potentiometer stick_X;
    Potentiometer stick_Y;

    Potentiometer touch_bar;

    Potentiometer whammy_bar;

    Button touch_bar_0;
    Button touch_bar_1;
    Button touch_bar_2;
    Button touch_bar_3;
    Button touch_bar_4;
    Button touch_bar_5;
    Button touch_bar_6;
    Button touch_bar_7;
    Button touch_bar_8;
};

#endif
