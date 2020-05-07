// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/example.h>


TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

/*
 * I have tested the Beat Looper manually, here are the following scenarios:
 * Played simple track with 8 presses of 1 sound, file had 9 lines including BPM
 * Played 8 more presses of another sound onto the same track, file updated properly
 * Created new tracks with varying BPM and loop counts and file/looping displayed correctly
 * Track names persisted through runs, overlayed more sounds over the first track
 * Filled in none and only a few of the filenames, program used default sound file and inputs
 * All key presses work properly
 */