// MIT License

// Copyright (c) 2021 KangSK

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __SCHEDULER_HPP_
#define __SCHEDULER_HPP_

#include "configs.hpp"
#include "include.hpp"

class Slot;
class Scheduler;

/**
 * @brief Single slot of pending actions
 */
class Slot {
  friend Scheduler;

 private:
  bool valid;
  void (*func)(void);
  uint64_t time;

 private:  // Only Scheduler can initiate Slot
  Slot();
};

/**
 * @brief Main scheduler
 */
class Scheduler {
  // ! Global variables
 private:
  uint64_t __time;
  Slot __slots[MAX_SCHEDULE];

  // ! Setting Functions
 private:
  // Setting Helper Functions
  void __setTimerPrecision(PRECISION);

 public:
  // Setting User Functions

  // ! Scheduler Functions
 private:
  // Scheduler Helper Functions
  Slot* __allocSlot();
  void __freeSlot(Slot*);

 public:
  // Scheduler User Functions
  void schedule(uint64_t, void (*func)(void));

  // ! Constructor
 public:
  Scheduler(PRECISION);
};

/**
 * @brief Global initializer
 * @details A macro function used to initialize the scheduler.
 * This function...
 *  - Initialized the timer interrupt service routine
 *  - Calls the constructor of Scheduler, creating a global scheduler
 */
#define INITIALIZE_SCHEDULER(t) Scheduler shed(t)

#endif  // __SCHEDULER_HPP_