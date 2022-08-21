int midi2CVOctave = 0;
byte midi2CVpoly = 2;
byte roundrobin = 0;
byte bendAmount = 0;

result handleMidi2CV(eventMask event, navNode& nav, prompt &item);

SELECT(midi2CVOctave,midi2CVOctaveMenu,"OCTAVE",doNothing,noEvent,noStyle
  ,VALUE("-3",-3,doNothing,noEvent)
  ,VALUE("-2",-2,doNothing,noEvent)
  ,VALUE("-1",-1,doNothing,noEvent)
  ,VALUE("0",0,doNothing,noEvent)
  ,VALUE("1",1,doNothing,noEvent)
  ,VALUE("2",2,doNothing,noEvent)
  ,VALUE("3",3,doNothing,noEvent)
);

SELECT(midi2CVpoly,midi2CVpolyMenu,"VOICES",doNothing,noEvent,noStyle
  ,VALUE("MONO",0,doNothing,noEvent)
  ,VALUE("DUO",1,doNothing,noEvent)
  ,VALUE("POLY",2,doNothing,noEvent)
  ,VALUE("UNI 2",3,doNothing,noEvent)
  ,VALUE("UNI 4",4,doNothing,noEvent)
);

SELECT(roundrobin,roundrobinMenu,"ROBIN",doNothing,noEvent,noStyle
  ,VALUE("OFF",0,doNothing,noEvent)
  ,VALUE("FWD",1,doNothing,noEvent)
  ,VALUE("BKWD",2,doNothing,noEvent)
  ,VALUE("RAND",3,doNothing,noEvent)
);

SELECT(bendAmount,bendAmountMenu,"BEND",doNothing,noEvent,noStyle
  ,VALUE("1",0,doNothing,noEvent)
  ,VALUE("2",1,doNothing,noEvent)
  ,VALUE("3",2,doNothing,noEvent)
  ,VALUE("4",3,doNothing,noEvent)
  ,VALUE("5",4,doNothing,noEvent)
  ,VALUE("7",5,doNothing,noEvent)
  ,VALUE("12",6,doNothing,noEvent)
  ,VALUE("24",7,doNothing,noEvent)
);



MENU(subMenuMidi2CV,"CHURRO MIDI",handleMidi2CV,(Menu::eventMask)(enterEvent|exitEvent),wrapStyle
  ,SUBMENU(midi2CVOctaveMenu)
  ,SUBMENU(midi2CVpolyMenu)
  ,SUBMENU(roundrobinMenu)
  ,SUBMENU(bendAmountMenu)
  ,EXIT("<BACK")
  
);
