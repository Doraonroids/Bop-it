# Bop-it

ECE1895 bop-it project


This is the c++ arduino sketch for team lambda's bop-it project.

The chip used is a atmegea328

1.Functional/ Software Requirements
The game will interact with the user as follows
User has the ability to turn the unit on or off.
Once on, the user can hit a button to start the game
The device will specify one of three commands to the user by emitting distinct, audible sounds
The user should attempt to carry out one of three corresponding actions, as defined by the game designers
The device will detect if the user carried out the appropriate action within the specified time limitoIf the user was successful,a visual cue shallinform the user of asuccessful attempt 
Everytime the user responds correctly, they score 1 point
After asuccessful attempt, the device will randomlyselect and issue a new command.  
The timeintervalbetween successive commandsbecomessmallerwith each successful attempt
After 99 successful attempts, the game ends and the user is notified of their scoreoIf the user is unsuccessfulin responding to a command either by not responding in time or by providing an incorrect response, a visual cue will inform the user of an unsuccessful attempt
The game will end and the user will be notified of their final score
1.1.Hardware Requirements
1.1.1.Power Source
The device shall beportable and battery-powered
1.1.2.User ControlledInputs
The device shall have an input that allows the user to powerthe device on or off.
The device shall have an input that allowsthe user to specify the start of a new game
The device shall have (at least)three distinctly different, tactile inputsthat can beactivated by the user in response to the device’s commands.  
1.1.3.Device Controlled Outputs
The device shall have (at least) three distinctly different, audible outputs that are used to specify commands
The device shall have an outputthat provides the user visual confirmation of successful (And unsuccessful) attempts
The device shall have a means to notify the user of their score at the end of a round1.1.4.Device Enclosure (Optional)
The device and all of its components shall be enclosed withonly the inputs and outputs made visible
The enclosure shall be small in form and portable
