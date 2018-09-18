// WiiExpansions - Arduino library to control Wii Remote expansion devices.
// Copyright Julien Lebunetel 2018
// MIT License

// include Arduino core library
#include "Arduino.h"

// include this library's description file
#include "WiiExpansions.h"

// include description files for other libraries used
#include <Wire.h> // librairie pour les communications i2c

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

WiiExpansion::WiiExpansion()
{
  Wire.begin();
};


// Public Methods //////////////////////////////////////////////////////////////
// Functions available in WiiExpansions sketches, this library, and other libraries

void WiiExpansion::init()
{
  // première séquence d'initialisation
  Wire.beginTransmission(0x52);
  Wire.write(0xF0);
  Wire.write(0x55);
  Wire.endTransmission();

  // deuxième séquence d'initialisation
  Wire.beginTransmission(0x52);
  Wire.write(0xFB);
  Wire.write(0x00);
  Wire.endTransmission();
  delayMicroseconds(200);
}

void WiiExpansion::read()
{
  // handshake
  Wire.beginTransmission(0x52);
  Wire.write(0x00);
  Wire.endTransmission();

  // délai nécessaire à la stabilisation
  delayMicroseconds(200);

  // récupération des données
  Wire.requestFrom(0x52, 6);
  int i=0;
  while (Wire.available())
  {
    data[i] = Wire.read();
    i++;
  }
}



void WiiNunchuk::init()
{
  WiiExpansion::init();
};

void WiiNunchuk::read()
{
  WiiExpansion::read();

  // décodage des données
  C.set( !(data[5] & (1<<1)) ); // bouton C
  Z.set( !(data[5] & (1<<0)) ); // bouton Z

  stick_X.set( data[0] ); // joystick X : 27/126/218
  stick_Y.set( data[1] ); // joystick Y : 37/138/233

  accelerometer_X.set( (data[2] << 2) | ((data[5] >> 2) & B00000011) ); // accelerometre X : 0/1023
  accelerometer_Y.set( (data[3] << 2) | ((data[5] >> 4) & B00000011) ); // accelerometre Y : 0/1023
  accelerometer_Z.set( (data[4] << 2) | ((data[5] >> 6) & B00000011) ); // accelerometre Z : 0/1023
};

void WiiNunchuk::print()
{
  Serial.print("Button C ........ ");
  Serial.println(C.get());

  Serial.print("Button Z ........ ");
  Serial.println(Z.get());


  Serial.print("Stick X ......... ");
  Serial.println(stick_X.get());

  Serial.print("Stick Y ......... ");
  Serial.println(stick_Y.get());


  Serial.print("Accelerometer X . ");
  Serial.println(accelerometer_X.get());

  Serial.print("Accelerometer Y . ");
  Serial.println(accelerometer_Y.get());

  Serial.print("Accelerometer Z . ");
  Serial.println(accelerometer_Z.get());
};



void WiiClassicController::init()
{
  WiiExpansion::init();
};

void WiiClassicController::read()
{
  WiiExpansion::read();

  // décodage des données
  L.set( !(data[4] & (1<<5)) );
  R.set( !(data[4] & (1<<1)) );

  select.set( !(data[4] & (1<<4)) );
  home.set( !(data[4] & (1<<3)) );
  start.set( !(data[4] & (1<<2)) );

  X.set( !(data[5] & (1<<3)) );
  Y.set( !(data[5] & (1<<5)) );
  A.set( !(data[5] & (1<<4)) );
  B.set( !(data[5] & (1<<6)) );

  ZL.set( !(data[5] & (1<<7)) );
  ZR.set( !(data[5] & (1<<2)) );

  pad_L.set( !(data[5] & (1<<1)) );
  pad_R.set( !(data[4] & (1<<7)) );
  pad_U.set( !(data[5] & (1<<0)) );
  pad_D.set( !(data[4] & (1<<6)) );

  stick_LX.set( data[0] & B00111111 ); // joystick gauche X : 6/30/55
  stick_LY.set( data[1] & B00111111 ); // joystick gauche Y : 5/30/57

  stick_RX.set( ((data[0] >> 3) & B00011000) | ((data[1] >> 5) & B00000110) | (data[2] >> 7) ); // joystick doit X : 3/16/28
  stick_RY.set( data[2] & B00011111 );                                                          // joystick doit Y : 3/16/28

  bumper_L.set( ((data[2] >> 2) & B00011000) | (data[3] >> 5) ); // gachette gauche : 1/31
  bumper_R.set( data[3] & B00011111 );                           // gachette droite : 3/29
};

void WiiClassicController::print()
{
  Serial.print("Button L ...... ");
  Serial.println(L.get());

  Serial.print("Button R ...... ");
  Serial.println(R.get());


  Serial.print("Button select . ");
  Serial.println(select.get());

  Serial.print("Button home ... ");
  Serial.println(home.get());

  Serial.print("Button start .. ");
  Serial.println(start.get());


  Serial.print("Button X ...... ");
  Serial.println(X.get());

  Serial.print("Button Y ...... ");
  Serial.println(Y.get());

  Serial.print("Button A ...... ");
  Serial.println(A.get());

  Serial.print("Button B ...... ");
  Serial.println(B.get());


  Serial.print("Button ZL ..... ");
  Serial.println(ZL.get());

  Serial.print("Button ZR ..... ");
  Serial.println(ZR.get());


  Serial.print("Pad Left ...... ");
  Serial.println(pad_L.get());

  Serial.print("Pad Right ..... ");
  Serial.println(pad_R.get());

  Serial.print("Pad Up ........ ");
  Serial.println(pad_U.get());

  Serial.print("Pad Down ...... ");
  Serial.println(pad_D.get());


  Serial.print("Stick Left X .. ");
  Serial.println(stick_LX.get());

  Serial.print("Stick Left Y .. ");
  Serial.println(stick_LY.get());

  Serial.print("Stick Right X . ");
  Serial.println(stick_RX.get());

  Serial.print("Stick Right Y . ");
  Serial.println(stick_RY.get());

  Serial.print("Bumper Left ... ");
  Serial.println(bumper_L.get());

  Serial.print("Bumper Right .. ");
  Serial.println(bumper_R.get());
};

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
