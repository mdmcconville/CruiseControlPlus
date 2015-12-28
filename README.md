# CruiseControlPlus
What if cruise control also maintained safe following distance?

## Version 1
There were some assumptions made and restrictions for this particular version:
- The weather is always fair
- The cars drive for 800 feet; this can't be altered dynamically yet
- The terrain is completely flat
- The car always decelerates at a constant rate of approximately 15 ft/s
- The car decelerates to the speed of the car it is following. It doesn't decelerate further if necessary yet, but will in Version 2
- The car being followed does not change speed

## Rationale 
Self-driving cars aren't used outside of testing environments yet, but cruise-control is widely used. We have the technology to read license plates accurately--if cars could scan the car in front of them to determine approximate distance, it would be possible to adjust speeds as necessary for safety. 


