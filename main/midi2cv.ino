byte notecv[4];
bool robinhasrun = false;
float BendDivider[8] = {8191.00, 4096.00, 2730.66, 2048.00, 1638.40, 1170.28, 682.58, 341.33};
byte polySelect[5] = {1, 2, 4, 2, 1};

result handleMidi2CV(eventMask event, navNode& nav, prompt &item) {
  if (event == enterEvent) {
    startMidi2CV();
    activeModule = &loopMidi2CV;
  }
  if (event == exitEvent) {
    activeModule = {};
    endMidi2CV();
  }
  return proceed;
}

// called once on module enter
void startMidi2CV() {
  resetCVOut();
  resetGateOut();
  MIDI_NOTES_ACTIVE.clear();
}

// called once on module exit
void endMidi2CV() {
  resetCVOut();
  resetGateOut();
  MIDI_NOTES_ACTIVE.clear();
}

// called constantly from main loop
void loopMidi2CV() {
  //note is the last note played
  byte note = MIDI_NOTES_ACTIVE.get(MIDI_NOTES_ACTIVE.size() - 1);
  byte noteSize = MIDI_NOTES_ACTIVE.size();
  polyphony = polySelect[midi2CVpoly];
  robinMode = roundrobin;

  if (MIDI_NOTES_ACTIVE.size() == 0) {
    setLEDOff(0);
    voiceflag[0, 1, 2, 3] = false;
  }
  
  //starts when any note is played midi 0 is no notes
  if (note > 0) {
    setLEDOn(0);


    ///MONO/DUO/POLY
    if (midi2CVpoly <= 2) {
      for (int j = 0; j < polyphony; j++) {
        if (voiceflag[j] == true) {
          notecv[j] = notecvtest[j];
          setGateOutDuration(j, 10);
        }
        if (lastPlayed == j && noteSize >= polyphony && notecvtest[j] != note) {
          notecv[j] = note;
          setGateOutDuration(j, 10);
          notecvtest[j] = note;
          voiceflag[j] = true;
        }
      }
    }

    //UNI 2
    if (midi2CVpoly == 3) {
      for (int i = 0; i < 2; i++) {
        if (voiceflag[i] == true) {
          notecv[(i * 2) + 1] = notecvtest[i];
          notecv[(i * 2)] = notecvtest[i];
          setGateOutDuration((i * 2) + 1, 10);
          setGateOutDuration((i * 2), 10);
        }
        if (lastPlayed == i && noteSize >= 2 && notecvtest[i] != note) {
          notecv[(i * 2) + 1] = note;
          notecv[(i * 2)] = note;
          setGateOutDuration((i * 2) + 1, 10);
          setGateOutDuration((i * 2), 10);
          notecvtest[i] = note;
          voiceflag[i] = true;
        }
      }
    }

    ///Uni 4 this plays all 4 voices on the same note. no round robin option neccesary here
    if (midi2CVpoly == 4) {
      for (int i = 0; i < 4; i++) {
        notecv[i] = note;
        setGateOutDuration(i, 10);
      }
    }

  }

  //bendAmount
  pitchBendValue = pitchBend / BendDivider[bendAmount];

  //CV values this converts the midi data into voltage for the synths using floats
  float cv0 = getCVFromNote(notecv[0] + 12 * midi2CVOctave + pitchBendValue);
  float cv1 = getCVFromNote(notecv[1] + 12 * midi2CVOctave + pitchBendValue);
  float cv2 = getCVFromNote(notecv[2] + 12 * midi2CVOctave + pitchBendValue);
  float cv3 = getCVFromNote(notecv[3] + 12 * midi2CVOctave + pitchBendValue);
  setCVOut(0, cv0, true);
  setCVOut(1, cv1, true);
  setCVOut(2, cv2, true);
  setCVOut(3, cv3, true);

}
