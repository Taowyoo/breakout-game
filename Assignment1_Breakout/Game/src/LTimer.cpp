/**
 * @file LTimer.cpp
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief LTimer Class implementation
 * @version 1.0.0
 * @date 2021-02-22 23:24:41 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "LTimer.h"
/// Initializes variables
LTimer::LTimer() {
  // Initialize the variables
  mStartTicks = 0;
  mPausedTicks = 0;

  mPaused = false;
  mStarted = false;
}

/// Start or reset and restart the timer
void LTimer::start() {
  // Start the timer
  mStarted = true;

  // Unpause the timer
  mPaused = false;

  // Get the current clock time
  mStartTicks = SDL_GetTicks();
  mPausedTicks = 0;
}

/// Stop the timer
void LTimer::stop() {
  // Stop the timer
  mStarted = false;

  // Unpause the timer
  mPaused = false;

  // Clear tick variables
  mStartTicks = 0;
  mPausedTicks = 0;
}

/// Pause the timer
void LTimer::pause() {
  // If the timer is running and isn't already paused
  if (mStarted && !mPaused) {
    // Pause the timer
    mPaused = true;

    // Calculate the paused ticks
    mPausedTicks = SDL_GetTicks() - mStartTicks;
    mStartTicks = 0;
  }
}

/// Unpause the timer
void LTimer::unpause() {
  // If the timer is running and paused
  if (mStarted && mPaused) {
    // Unpause the timer
    mPaused = false;

    // Reset the starting ticks
    mStartTicks = SDL_GetTicks() - mPausedTicks;

    // Reset the paused ticks
    mPausedTicks = 0;
  }
}
/**
 * @brief Gets the timer's time
 *
 * @return Uint32 Time value
 */
Uint32 LTimer::getTicks() {
  // The actual timer time
  Uint32 time = 0;

  // If the timer is running
  if (mStarted) {
    // If the timer is paused
    if (mPaused) {
      // Return the number of ticks when the timer was paused
      time = mPausedTicks;
    } else {
      // Return the current time minus the start time
      time = SDL_GetTicks() - mStartTicks;
    }
  }

  return time;
}

/**
 * @brief Check timer is started
 *
 * @return true Started
 * @return false Not started
 */
bool LTimer::isStarted() {
  // Timer is running and paused or unpaused
  return mStarted;
}
bool isStarted();
/**
 * @brief Check timer is is paused
 *
 * @return true Paused
 * @return false Not paused
 */
bool LTimer::isPaused() {
  // Timer is running and paused
  return mPaused && mStarted;
}
