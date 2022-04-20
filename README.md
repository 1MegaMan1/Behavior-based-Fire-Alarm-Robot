Behavior-based Fire Alarm Robot


Contents
1	Introduction:	2
2	Design:	2
3	New Design	4
3.1	Advantages:	4
3.2	Disadvantages:	4
3.3	What are some of the difficulties we have faced?	5
3.4	How does Robot work?	6
3.4.1	Turning	7
4	Implementation	9
4.1	Wandering:	9
4.2	Wall Following:	10
4.3	Searching:	10
4.4	Extinguish	11









1	Introduction:
Behavior-based Fire Alarm Robot navigate through unknown/unexplored maze of obstacles and find “fire” and “extinguish” it. 
2	Design:
Why the design change?
I decided to change the design from my first project because our old design was not stable nor was it able to stay in a straight path easily. The old design was not rigid and required constant repairs. We had to do extensive software control development and test, so we decided to retire the design.
The initial design was initially to make something creative and crazy to navigate a certain path planning maze. I wanted to use tracks instead of the standard design and added some “ornaments” to the robot. Like the scorpion tail, makeshift cannons, and the ultrasonic sensor for its eyes. 
Some of the follow flaws in the design:
Problem: Initial design was too narrow
Failed Solution: Rotate one track clockwise and the other counterclockwise. Often track would come off or something would break. The design was not rigid enough to withstand the torques.
Solution: Widen the tracks
Problem: Too wide and axles extensions would fall out
Solution: Applied glue
Problem: Tracks would fall off rims after extended use
Solution: Clean the tracks and rims and put them back together. Attempted to move the center of mass more centralized. 
Problem: Widen the gap between the tracks would make it difficult to turn
Solution: Fine tune the gap between the tracks so it will go straight and turn somewhat accurately.
This was a difficult task because of the fraction of the tracks was variable depending on the surface of the ground. The tracks required to slip on every turn. Because of this the variances in every turn were too inconsistent. This introduced me into the dead recking problem. Gyroscope/digital compass was introduced and helped a lot, but the greater amount of distance traveled the more apparent the errors were. 








   
Old Design 1








3	New Design
What is the advantage from the new design vs the old?
 
New Design 1
3.1	Advantages:
•	Holonomic
•	Stable
•	Rigid
•	3 separate frame orientations 
•	Capable to stay in constant motion
•	Has a relative fast velocity
•	Differential
3.2	Disadvantages:
•	Complexity
•	Bulky






3.3	What are some of the difficulties we have faced?
Because of the challenges of the previous design of requirement of slippage to turn a holonomic the base frame solution was chosen. A of turntable gear (see below) was required. This gear made it possible to make this project holonomic. As seen below to secure the gear is the need of cross axles (plastic shafts). These are not rigid and has a lot of play to it. This effects the whole bot turning ability and how straight its path can be.
 
Turntable Gear 1


Due to my nature of Legos, the design required a lot of revisions. A lot of the stress of the holonomic turns of the gear and other Lego parts the bot self-destroyed itself. The bot way too tall at its early revision and many other spacing and logistic issues. However, through perseverance the design became very rigid.
I initially had a lot of issues with turning accuracy. When commanding the turning motors to 90 degrees there was a lot of error because of the amount of friction the system had to overcome. Gearing was required. A 5:1 gearing ratio solve this issue. Extra gears was required because too much stress for a single plastic wheel thus two were required to spread out the torque.
 

3.4	How does Robot work?
Sensors
The design took 3 sonar sensors, encoders, and a lot of software logic. One of the goals was to keep the robot in motion and which required distance sensors on front, left, and right of the bot. This will assist in keeping the bot a lot more flexible. It can wall follow on either side, avoid unexpected walls, and keep a relative high velocity.
Holonomic
The bot possesses 3 orientation independent frames. Front, center, and rear frames. The center top (Base/Body Orientation) holds the brick (CPU, Main board, IO, battery) and the three sonar sensors (not shown below). This is the reference frame. 
Both rear and front wheelbase contain the driver motors, differential, and the wheels. The wheels are not shown to simplify the diagram. Because of the 3 orientated independent frames the wheels will need a differential to greatly reduce skidding while turning. 
 
Body Orientation 1

 
Differential 1





3.4.1	Turning
My method to turn the bot was to turn the front frame and then back frame in opposing 45-degree angles to create a 90-degree turn when it detected an obstacle with the ultrasonic sensor 25 cm away (around 10 inches).
To determine which way to turn logic was implemented to check the left and right ultrasonic sensors. If no object was in either sensor it would pick a random direction. No path planning was implemented. If all three sensors detected an obstacle the platform would back up until one of the left or right sensors did not detect an obstacle and turn in that direction.
Due to the hardware limitations the front motor was turned first then the back motor. The locomotive motors were run at 19% of power and over geared at 1:1.43. The motor was ran on a 40 teeth gear to 28 teeth differential gear that drives the axles connected to Wheel 43.2mm D. x 26mm Technic Racing Small, 3 Pin Holes with Black Tire 56 x 28 ZR Street (41896 / 41897). 

 



 
New Design 2









4	Implementation 









There are 4 modes that have been implemented within the system.
1.	Wandering
2.	Wall Following
3.	Searching
4.	Extinguish
4.1	Wandering:
The moment you activate the bot, it goes into wandering mode basically this checks to see if the front, left and right sonars have anything in front of them. The threshold value selected for this is 25 cms; choice of such a high value is considering the size of the bot and the way our rotate function works.
When the threshold is not being breached, it moves forward 90% of the time with a chance of 5% of either left turns and 5% of right turns in best case scenarios. All of this has been implemented using a randomizer and priority has been given to forward movement this is considering the inside a closed environment task. 
Once the ultrasonic distance threshold has been breached, the bot knows that there is going to be a wall/obstacle in front of it, and the next course of action is to avoid hitting that wall / obstacle. It does this by randomly selecting whether to go in the left or the right direction once the randomizer comes up with its answer; it activates the required function to go in the direction it chooses to. Why randomly? This is because the bot has no idea where the flame is.


4.2	Wall Following:







The solid black line represents the wall, light brown bar represents the inner threshold, the 3D darker blue block (nominal threshold) represents the path the bot will be wall following on and the lighter blue region represents the outer region.
Let’s explain this with an example, the bot starts off in wandering mode where it just moves around and will eventually encounters something and when it does, it either makes a orientation correction to align itself to be parallel with the wall depending on the values received by the left and right ultrasonic sensors. 
4.3	Searching:
 
Light Sensor Table 1
While the bot is switching between wall following and wandering mode, it continuously looks for light intensity values of the floor using a light sensor. We know the floor is black; the reading for this on the sensor is 1 and we also know the flame is on a bluish colored tile; the reading is 2 on the sensor. Once the light sensor outputs 2 value the goal has been achieved the program will progress to the extinguish state.

4.4	Extinguish
Once it’s done with searching for the flame (looking at the tile color using a light sensor), the bot now goes into extinguish mode. Here the front and rear wheels of the bot rotate in opposite direction of each other and both motors get powered on at full speed (throttle), this action makes the bot spin around very fast and blow the candle out using air (that’s what we hoped it would do but nothing, even at full throttle it’s not that fast to generate wind turbulence).

