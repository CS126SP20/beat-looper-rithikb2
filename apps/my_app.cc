// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "UI.h"

#include <cinder/app/App.h>

using namespace reza::ui;
using namespace ci;
using namespace ci::app;

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() {
  mUi = SuperCanvas::create("basic");
  mUi->addSpacer();
  mUi->addLabel("type filepath here:");
  mUi->autoSizeToFitSubviews();
}

void MyApp::update() {}

void MyApp::draw() {}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getChar()) {
    case '1': {

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

} // namespace myapp
