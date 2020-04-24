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
  mUi->addSpacer();
  buttonOne.size(10000);
  buttonOne.align(Alignment::RIGHT);
  buttonOne.fontSize(static_cast<FontSize>(20));
  buttonOne.label("1");
  mUi->addButton("one", true, buttonOne);
  mUi->autoSizeToFitSubviews();

  ci::audio::SourceFileRef musicFile = ci::audio::load(ci::app::loadAsset("clap.wav"));
  mVoice = ci::audio::Voice::create(musicFile);

}

void MyApp::update() {}

void MyApp::draw() {}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getChar()) {
    case '1': {
      mVoice->start();
      buttonOne.setState( State::DOWN );
    }
    case '2': {
    }
    case '3': {
    }
    case '4': {
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
