// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "UI.h"

#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>

using namespace reza::ui;
using namespace ci;
using namespace ci::app;

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() {
  mUi = SuperCanvas::create("beat looper");
  mUi->addLabel("type filenames and hit enter to map to keys 1-4", FontSize::MEDIUM);
  mUi->addSpacer();
  mUi->addSpacer();

  for (int i = 1; i < 5; i++) {
    mUi->
    addLabel("key " + std::to_string(i) + " filename:", FontSize::MEDIUM);
    inputs.push_back(mUi->addTextInput(" ", TextInput::Format()));
    mUi->addSpacer();
    mUi->addSpacer();
  }

  mUi->addLabel("use keys 1-4 to play", FontSize::MEDIUM);
  sliderFormat.precision(0);
  sliderRef = mUi->
      addSliderf("BPM", 60, 20.0, 260, sliderFormat);

  mUi->autoSizeToFitSubviews();

  ci::audio::SourceFileRef musicFile =
      ci::audio::load(ci::app::loadAsset("metronome.wav"));
  metronome = ci::audio::Voice::create(musicFile);

}

void MyApp::update() {

}

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
    }
  }
  mVoice[key - 1]->start();
}

void MyApp::keyDown(KeyEvent event) {
  int key = 0;
  if (event.getCode() == 13) {
    for (int i = 0; i < 4; i++) {
      filenames[i] = (*inputs[i]).getValue();
      if (filenames[i].front() == ' ') {
        filenames[i] = filenames[i].substr(1, filenames[i].size());
      }
      //std::cout << filenames[i];
      ci::audio::SourceFileRef musicFile =
          ci::audio::load(ci::app::loadAsset(filenames[i]));
      mVoice[i] = ci::audio::Voice::create(musicFile);
    }
  }
  switch (event.getChar()) {
    case 'r': {
      bpm = (*sliderRef).getValue();
      for (int i = 0; i < 4; i++) {
        metronome->start();
        std::this_thread::sleep_for(std::chrono::milliseconds((60000 / bpm)));
        metronome->stop();
      }
      start = std::chrono::system_clock::now();
      isRecording = true;
      break;
    }
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
