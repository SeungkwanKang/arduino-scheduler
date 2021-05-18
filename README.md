# arduino-scheduler

Arduino-scheduler is a simple scheduler written in C++, it's purpose on aiding students to write non-blocking, timer-related actions on arduino.

## Example Scenario

Let's say we need to make a simple program that blinks the LED.
This is easily done by looping through a logic of turning on/off and sleeping.

Now, let's say we need to add a functionality, precisely a button input, that toggles whether out system is on/off.
If we try to apply the same logic as before, by simply adding a digital read in the loop, we com across a critical problem.
While sleep()-ing, the CPU ignores any interrupts, and therefore you button input is likely to be ignored.

This is not hard to fix this issue, by utilizing millis() functions and keeping track of all actions' ticks, but this method has clear limitations.

- It cannot have better precision than a millisecond.
- When there are more than one types of actions, the code becomes greatly cumbersome.

If the programmer also knows how to use timer interrupts, this problem is likely to be solved, but still it takes unnecessarily much work for simple projects.

## Main Philosophy

To fix the problems stated above, this project aims to make a simple timer engine where the user can simply "reserve" a time slot and forget about it.
Specifically, using the scheduler, the programmer doesn't have the responsibility to mandatory check the time, calculate whether there exists any expired time slot, and execute the action; the scheduler takes the burden.

For the LED-button example above, this in code, will look like below.

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

The schedule function is taking two parameters: the function to schedule and when to (how much time later to) schedule it.
By setting the delay time to zero, it can make the scheduler to call the function right now.
This may be useful if there are multiple actions possibly needed to be ran simultaneously.
By scheduling functions in a loop (not necessarily two !) as above, we can simply make an arbitrary-delayed, multi-function repeater.
