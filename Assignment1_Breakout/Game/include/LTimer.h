/**
 * @file LTimer.h
 * @author Yuxiang Cao (cao.yux@northeastern.edu)
 * @brief Simple Timer Class
 * @version 1.0.0
 * @date 2021-02-22 23:22:12 -08:00
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#if defined(LINUX) || defined(MINGW) || defined(__linux__)
#include <SDL2/SDL.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL.h>
#endif

/**
 * @brief The application time based timer
 *
 */
class LTimer {
 public:
  /// Initializes variables
  LTimer();

  /// Start or reset and restart the timer
  void start();
  /// Stop the timer
  void stop();
  /// Pause the timer
  void pause();
  /// Unpause the timer
  void unpause();

  /**
   * @brief Gets the timer's time
   *
   * @return Uint32 Time value
   */
  Uint32 getTicks();

  /**
   * @brief Check timer is started
   *
   * @return true Started
   * @return false Not started
   */
  bool isStarted();
  /**
   * @brief Check timer is is paused
   *
   * @return true Paused
   * @return false Not paused
   */
  bool isPaused();

 private:
  /// The clock time when the timer started
  Uint32 mStartTicks;

  /// The ticks stored when the timer was paused
  Uint32 mPausedTicks;

  /// Whether paused
  bool mPaused;

  /// Whether started
  bool mStarted;
};