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
    mUi->addLabel("key " + std::to_string(i) + " filename:", FontSize::MEDIUM);
    inputs.push_back(mUi->addTextInput(" ", TextInput::Format()));
    mUi->addSpacer();
    mUi->addSpacer();
  }

  mUi->addLabel("use keys 1-4 to play", FontSize::MEDIUM);
  mUi->autoSizeToFitSubviews();

  ci::audio::SourceFileRef musicFile = ci::audio::load(ci::app::loadAsset("clap.wav"));
  mVoice[0] = ci::audio::Voice::create(musicFile);

}

void MyApp::update() {

}

void MyApp::draw() {}

void MyApp::keyDown(KeyEvent event) {
  if (event.getCode() == 13) {
    for (int i = 0; i < 4; i++) {
      filenames[i] = (*inputs[i]).getValue();
      if (filenames[i].front() == ' ') {
        filenames[i] = filenames[i].substr(1, filenames[i].size());
      }
      std::cout << filenames[i];
      ci::audio::SourceFileRef musicFile = ci::audio::load(ci::app::loadAsset(filenames[i]));
      mVoice[i] = ci::audio::Voice::create(musicFile);
    }
  }
  switch (event.getChar()) {
    case '1': {
      mVoice[0]->start();
      break;
    }
    case '2': {
      mVoice[1]->start();
      break;
    }
    case '3': {
      mVoice[2]->start();
      break;
    }
    case '4': {
      mVoice[3]->start();
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
