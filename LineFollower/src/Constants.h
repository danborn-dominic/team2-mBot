namespace Constants {
    // mMot Mega Constants in inches
    constexpr double length = 9.21;
    constexpr double width = 4.17;
    constexpr double height = 6.57;
    constexpr double wheelRaidus = 2.3622; 
    constexpr double wheelBase = 4.75;
    constexpr double trackWidth = 5.25;
    // Motor Constants
    MeMegaPiDCMotor motor_1(1);
    MeMegaPiDCMotor motor_2(2);
    MeMegaPiDCMotor motor_9(9);
    MeMegaPiDCMotor motor_10(10);
    MeMegaPiDCMotor motor_3(3);
    MeMegaPiDCMotor motor_11(11);
    MeMegaPiDCMotor motor_4(4);
    MeMegaPiDCMotor motor_12(12);
    // Encoder Constants
        MeNewRGBLed rgbled_67(67,4);
    MeNewRGBLed rgbled_68(68,4);
    MeSingleLineFollower linefollower_63(63);
    MeSingleLineFollower linefollower_64(64);
    MeBarrierSensor barrier_60(60);
    MeBarrierSensor barrier_61(61);
    MeBarrierSensor barrier_62(62);
}