/// @file	AP_MotorsKestrel.h
/// @brief	Motor control class for the Kestrel
#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_Math/AP_Math.h>        // ArduPilot Mega Vector/Matrix math Library
#include "AP_MotorsMulticopter.h"

// vane servos use channels 5, 6, and 7
#define AP_MOTORS_CH_VN_1   CH_4
#define AP_MOTORS_CH_VN_2   CH_5
#define AP_MOTORS_CH_VN_3   CH_6

#define AP_MOTORS_KES_SERVO_RANGE_DEG_MIN   20   // minimum angle movement of vane servos in degrees
#define AP_MOTORS_KES_SERVO_RANGE_DEG_MAX   200  // maximum angle movement of vane servos in degrees

/// @class      AP_MotorsKestrel
class AP_MotorsKestrel : public AP_MotorsMulticopter {
public:

    /// Constructor
    AP_MotorsKestrel(uint16_t speed_hz = AP_MOTORS_SPEED_DEFAULT) :
        AP_MotorsMulticopter(speed_hz)
    {
    };

    // init
    void init(motor_frame_class frame_class, motor_frame_type frame_type) override;

    // set frame class (i.e. quad, hexa, heli) and type (i.e. x, plus)
    void set_frame_class_and_type(motor_frame_class frame_class, motor_frame_type frame_type) override;

    // set update rate to motors - a value in hertz
    void                set_update_rate( uint16_t speed_hz ) override;

    // output_to_motors - sends minimum values out to the motors
    virtual void        output_to_motors() override;

    // get_motor_mask - returns a bitmask of which outputs are being used for motors or servos (1 means being used)
    //  this can be used to ensure other pwm outputs (i.e. for servos) do not conflict
    uint32_t            get_motor_mask() override;

    // output a thrust to all motors that match a given motor
    // mask. This is used to control tiltrotor motors in forward
    // flight. Thrust is in the range 0 to 1
    // rudder_dt applys diffential thrust for yaw in the range 0 to 1
    void                output_motor_mask(float thrust, uint32_t mask, float rudder_dt) override;

    // return the roll factor of any motor, this is used for tilt rotors and tail sitters
    // using copter motors for forward flight
    float               get_roll_factor(uint8_t i) override;

    // return the pitch factor of any motor, this is used for AP_Motors_test
    float               get_pitch_factor_json(uint8_t i);

    // Run arming checks
    bool arming_checks(size_t buflen, char *buffer) const override;

    // Get the testing order for the motors, this is used for AP_Motors_test
    uint8_t get_motor_test_order(uint8_t i);

    // static const struct AP_Param::GroupInfo var_info[];

protected:
    // output - sends commands to the motors
    void                output_armed_stabilizing() override;

    // call vehicle supplied thrust compensation if set
    void                thrust_compensation(void) override;

    const char* _get_frame_string() const override { return "KES"; }
    const char*  get_type_string() const override { return _pitch_reversed ? "pitch-reversed" : ""; }

    // output_test_seq - spin a motor at the pwm value specified
    //  motor_seq is the motor's sequence number from 1 to the number of motors on the frame
    //  pwm value is an actual pwm value that will be output, normally in the range of 1000 ~ 2000
    virtual void _output_test_seq(uint8_t motor_seq, int16_t pwm) override;

    // parameters

    float _vane_right;
    float _vane_fore;
    float _vane_left;

    float _thrust_right;
    float _thrust_fore;
    float _thrust_left;

    // reverse pitch
    bool _pitch_reversed;

    bool _has_vane_right;
    bool _has_vane_fore;
    bool _has_vane_left;

    bool _have_tail_servo = true;

    // Kestrel Stuff
    // AP_Int8 kes_vane_bias;
    // AP_Float kes_vane_max_angle;

    // AP_Int16 vane_left_offset;
    // AP_Int16 vane_fore_offset;
    // AP_Int16 vane_right_offset;

};
