# arduino-scheduler

Arduino-scheduler is a simple scheduler written in C++, its purpose on aiding students to write non-blocking, timer-related actions on arduino.

## Example Scenario

Let's say we need to make a simple program that blinks the LED.
Simply looping through a logic of turning on/off and sleeping will be a solution.

Now, let's say we need to add functionality, precisely a button input, that toggles whether our system is on/off.
If we try to apply the same logic as before by simply adding a digital read in the loop, we encounter a critical problem.
While sleep()-ing, the CPU ignores any interrupts, and therefore the button input is likely to be missed.

It is not hard to fix this issue by utilizing the millis() function and keeping track of all actions' ticks, but this method has clear limitations.

- It cannot have better precision than a millisecond.
- When there is more than one type of action, the code becomes greatly cumbersome.

If the programmer also knows how to use timer interrupts, this problem is likely to be solved, but still, it takes unnecessarily much work for simple projects.

## Main Philosophy

This project aims to make a simple timer engine where the user can "reserve" a time slot and forget about it, potentially fixing the above problems.
Specifically, using the scheduler, the programmer doesn't have the responsibility to mandatory check the time, calculate any expired time slot and execute the action; the scheduler takes the burden.

For the LED-button example above, this in code will look like the below.

```c++
volatile bool running = true;

void turn_on_led(void) {
  if (running)
    digitalWrite(ledPin, HIGH);
  scheduler.schedule(turn_off_led, 100);
}
void turn_off_led(void) {
  if (running)
    digitalWrite(ledPin, LOW);
  scheduler.schedule(turn_on_led, 100);
}
setup() {
  turn_on_led(); // Or scheduler.schedule(turn_on_led, 0);
}
loop() {
  if (buttonPushed)
    running = !running;
}
```

The schedule() function takes two parameters: the pointer of the function to schedule and when to (how much time later) schedule it.
Setting the delay time to zero can make the scheduler call the function right now.
This feature may be helpful for situations where multiple actions possibly needed to be run simultaneously, but the programmer doesn't want to fix the sequence.
By scheduling functions in a loop, making functions (not necessarily two !) schedule each other as above, we can make an arbitrary-delayed, multi-function repeater.
