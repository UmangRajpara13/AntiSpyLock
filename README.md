DEMO : 
https://youtu.be/xS-IQpIFpVk



The main code for the arduino chip lives in lock.ino file

Dev_Rough_Space is the directory used to try new code or logic or something else during development.

<!-- Demo & more info available at https://umangrajpara13.blogspot.com/2023/04/method-for-unlocking-digital-lock-is.html -->

Method for unlocking:

The digital lock is accessed using a alpha-numeric keypad, and the default PIN is 4545(as an example), which can be modified by the user. To initiate the unlocking procedure, first "#" key is pressed on the keypad. 

on the LCD screen, the top row contains numbers 0-9, while the bottom row contains characters A-D. collectively the top and bottom rows are grouped as A, B, C, and D.

The first step to unlock the digital lock is to identify the group in which the first digit of the PIN belongs. For example, if the first digit is 4, the user presses the ID of the corresponding group, B, on the keypad. On each key press, the numbers on the top row of the keypad will reshuffle, ensuring that the PIN is protected from observation-based attacks by immediate observers.

The same process is then repeated for the second, third, and fourth digits of the PIN, identifying the group in which each digit is located and pressing the corresponding group ID on the keypad. If the user follows these steps correctly and enters the correct group IDs representing the 4-digit PIN, access to the digital lock will be granted.

To change the PIN, the user must press the * key, enter the current PIN to confirm their identity, and then enter the new PIN on the subsequent screen. The new PIN must be confirmed by entering it again on the "Confirm PIN again" screen. If the two entries match, the PIN will be changed, and if not, the user will need to enter and confirm the new PIN again.

Why is the PIN unknown to immediate observers?

The digital lock is designed with a key feature that reshuffles the numbers on the top row of the keypad on every key press as well as on every new attempt to unlock. Thus, the combination entered is always different therfore the digital lock remains secure against visual eavesdropping.

Hardware Used:

The digital lock is built using an Arduino Uno (Atmega328p) microcontroller, a 4x4 keypad, a 16x2 LCD, a 4K resistor, and connecting wires.

Future Additions:

Future additions to the digital lock could include the incorporation of a capacitive fingerprint reader for instant access, as well as a touch and colorful display that eliminates the need for a numeric keypad.
