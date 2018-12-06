#include "robot-config.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
    using vex::task;
    using vex::directionType;
    task::sleep(1000);
    int wheelDiameterCM = 5;   
    double travelTargetCM = 23.333333333333;
    
    double circumference = wheelDiameterCM * M_PI;
    double degreesToRotate = (360 * travelTargetCM) / circumference;
    
    //Prints text on the screen//
    Brain.Screen.print("This program was written by Adi's mom!^TM");
    //Brain.Screen.newLine();
    //Brain.Screen.print("");
    
    //Sets the velocity to 100 and sets the degrees in which the wheels rotate for.//
    frontLeftMotor.rotateFor(degreesToRotate,vex::rotationUnits::deg,100,vex::velocityUnits::pct); 
    rearRightMotor.rotateFor(degreesToRotate,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
    frontRightMotor.rotateFor(degreesToRotate,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
    rearLeftMotor.rotateFor(degreesToRotate,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
    task::sleep(3000);
    //Stops the motor.//
    frontLeftMotor.stop();
    rearRightMotor.stop();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
  int armSpeedPCT = 30;
  while (1) {
        frontLeftMotor.spin(vex::directionType::fwd,Controller1.Axis3.value(),vex::velocityUnits::pct);
        rearLeftMotor.spin(vex::directionType::fwd,Controller1.Axis3.value(),vex::velocityUnits::pct);
        frontRightMotor.spin(vex::directionType::fwd,Controller1.Axis2.value(),vex::velocityUnits::pct);
        rearRightMotor.spin(vex::directionType::fwd,Controller1.Axis2.value(),vex::velocityUnits::pct);
        
        
        if(Controller1.ButtonL2.pressing()){
            ArmMotorLeft.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
            ArmMotorRight.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL1.pressing())
        {
            ArmMotorLeft.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
            ArmMotorRight.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
        } 
        else 
        { //If the the up or down button is not pressed...
            //...Stop the arm motor.
            ArmMotorRight.stop(vex::brakeType::hold);
            ArmMotorLeft.stop(vex::brakeType::hold);
        }
        
        
        if(Controller1.ButtonR2.pressing()){
            climberRight.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
            climberLeft.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonR1.pressing())
        {
            climberRight.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
            climberLeft.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
        } 
        else 
        { //If the the up or down button is not pressed...
            //...Stop the arm motor.
            climberRight.stop(vex::brakeType::hold);
            climberLeft.stop(vex::brakeType::hold);
        }
        //Flip Control//
        /*if(Controller1.ButtonR1.pressing()) { //If the A button is pressed...
            //...Spin the claw motor forward.
            FlipMotor.rotateFor(270,vex::rotationUnits::deg,50,vex::velocityUnits::pct,false);
        }
        else { //If the A or Y button are not pressed...        
            //...Stop the claw motor.
            FlipMotor.stop(vex::brakeType::brake);        
        }*/
		vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
        
    }
 
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }

//
// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
   // while(1) {
     // vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    //}    
       
}
