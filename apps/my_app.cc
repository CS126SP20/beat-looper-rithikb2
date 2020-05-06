// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>


#include "UI.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() {
  mUi = SuperCanvas::create("beat looper");
  mUi->addLabel("type file and track names and hit enter to map to keys 1-4", FontSize::MEDIUM);
  mUi->addSpacer();
  mUi->addSpacer();

  for (int i = 1; i < 5; i++) {
    mUi->addLabel("key " + std::to_string(i) + " filename:", FontSize::MEDIUM);
    inputs.push_back(mUi->addTextInput(" ", TextInput::Format()));
    mUi->addSpacer();
    mUi->addSpacer();
  }
  mUi->addLabel("track name:", FontSize::MEDIUM);
  trackInputRef = mUi->addTextInput(" ", TextInput::Format());
  mUi->addSpacer();
  mUi->addSpacer();
  mUi->addLabel("use keys 1-4 to play", FontSize::MEDIUM);
  sliderFormat.precision(0);
  bpmSlideRef = mUi->
      addSliderf("bpm", 60, 20.0, 260, sliderFormat);
  loopSlideRef = mUi->
      addSliderf("loop count", 5, 1, 100, sliderFormat);
  mUi->addSpacer();
  mUi->addSpacer();
  mUi->addLabel("press F1 to record your loop", FontSize::LARGE);
  mUi->addLabel("press F2 to play your loop", FontSize::LARGE);
  mUi->autoSizeToFitSubviews();

  ci::audio::SourceFileRef musicFile =
      ci::audio::load(ci::app::loadAsset("metronome.wav"));
  metronome = ci::audio::Voice::create(musicFile);
}

void MyApp::update() {}

void MyApp::draw() {}

void MyApp::play(int key) {
  if (mVoice[key - 1]->isPlaying()) {
    mVoice[key - 1]->stop();
  }
  if (isRecording) {
    if ((std::chrono::system_clock::now() - start).count() < (60000000 * 8 / bpm)) {
      events.push_back(
          event(key, (std::chrono::system_clock::now() - start).count()));
    } else {
      isRecording = false;
      saveEvents();
    }
  }
  mVoice[key - 1]->start();
}

void MyApp::loadEvents() {
  std::ifstream readFile = std::ifstream(tracksFolder + trackname + ".txt");
  std::string token1;
  int token2;
  readFile >> token1;
  readFile >> token2;
  while (!readFile.eof()) {
    readFile >> token1;
    readFile >> token2;
    fEvents.push_back(fEvent(token1, token2));
  }
}

void MyApp::saveEvents() {
  fEvents.clear();
  std::fstream checkFile;
  checkFile.open(tracksFolder + trackname + ".txt");
  if (!checkFile.fail()) {
    loadEvents();
  }
  for (event e : events) {
    fEvents.push_back(fEvent(filenames[e.key - 1], e.timestamp));
  }
  std::ofstream trackFile = std::ofstream(tracksFolder + trackname + ".txt");
  trackFile << "BPM: " << bpm << "\n";

  std::sort(fEvents.begin(), fEvents.end());

  for (fEvent e : fEvents) {
    trackFile << e.filename << " " << std::to_string(e.timestamp) << "\n";
  }
  trackFile.close();
}

void MyApp::playLoop() {
  while (loopCount < loopTotal) {
    start = std::chrono::system_clock::now();
    int previousTimestamp = 0;
    for (fEvent e : fEvents) {
      if (!isLooping) {
        return;
      }
      std::chrono::nanoseconds wait((e.timestamp - previousTimestamp) * 1000);
      ci::audio::SourceFileRef musicFile =
          ci::audio::load(ci::app::loadAsset(e.filename));
      std::this_thread::sleep_for(wait);
      for (loopVoice lV : loopVoices) {
        if (e.filename == lV.filename) {
          lV.sound->stop();
        }
      }
      previousTimestamp = e.timestamp;
      sound = ci::audio::Voice::create(musicFile);
      sound->start();
      loopVoices.push_back(loopVoice(e.filename, sound));
    }
    std::chrono::nanoseconds endWait(((60000000 * 8 / bpm) - fEvents.back().timestamp) * 1000);
    std::this_thread::sleep_for(endWait);
    loopCount++;
  }
}

void MyApp::readInputs() {
  bpm = (*bpmSlideRef).getValue();
  trackname = (*trackInputRef).getValue();
  loopTotal = (*loopSlideRef).getValue();
  if (trackname.front() == ' ') {
    trackname = trackname.substr(1, trackname.size());
  }
  for (int i = 0; i < 4; i++) {
    filenames[i] = (*inputs[i]).getValue();
    if (filenames[i] == " " || filenames[i] == "") {
      filenames[i] = "metronome.wav";
    }
    if (filenames[i].front() == ' ') {
      filenames[i] = filenames[i].substr(1, filenames[i].size());
    }

    ci::audio::SourceFileRef musicFile =
        ci::audio::load(ci::app::loadAsset(filenames[i]));
    mVoice[i] = ci::audio::Voice::create(musicFile);
  }
}

void MyApp::keyDown(KeyEvent event) {
  int key = 0;
  if (event.getCode() == 13) {
    readInputs();
  }
  if (event.getCode() == 282) {
    readInputs();
    for (int i = 0; i < 4; i++) {
      metronome->start();
      std::this_thread::sleep_for(std::chrono::milliseconds((60000 / bpm)));
      metronome->stop();
    }
    start = std::chrono::system_clock::now();
    isRecording = true;
  }
  if (event.getCode() == 283) {
    loopCount = 0;
    readInputs();
    isLooping = true;
    fEvents.clear();
    loadEvents();
    playLoop();
  }
  switch (event.getChar()) {
    case '1': {
      key = 1;
      play(1);
      break;
    }
    case '2': {
      key = 2;
      play(2);
      break;
    }
    case '3': {
      key = 3;
      play(3);
      break;
    }
    case '4': {
      key = 4;
      play(key);
      break;
    }
    case '5': {
    }
    case '6': {
    }
    case '7': {
    }
    case '8': {
    }
  }
}

void MyApp::mouseDown(MouseEvent event) {

}

}// namespace myapp
