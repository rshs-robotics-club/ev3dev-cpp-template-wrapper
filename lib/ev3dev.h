/*
 * C++ API to the sensors, motors, buttons, LEDs and battery of the ev3dev
 * Linux kernel for the LEGO Mindstorms EV3 hardware
 *
 * Copyright (c) 2014 - Franz Detro
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Modification:
 *  Add new button management for ev3dev Release 02.00.00 (ev3dev-jessie-2014-07-12) - Christophe Chaudelet
 *
 */

#pragma once

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

namespace ev3dev {

//-----------------------------------------------------------------------------
typedef std::string         device_type;
typedef std::string         mode_type;
typedef std::set<mode_type> mode_set;
typedef std::string         address_type;

//-----------------------------------------------------------------------------
const address_type INPUT_AUTO;  //!< Automatic input selection
const address_type OUTPUT_AUTO; //!< Automatic output selection

#if defined(EV3DEV_PLATFORM_BRICKPI)
constexpr char INPUT_1[]  = "ttyAMA0:in1";  //!< Sensor port 1
constexpr char INPUT_2[]  = "ttyAMA0:in2";  //!< Sensor port 2
constexpr char INPUT_3[]  = "ttyAMA0:in3";  //!< Sensor port 3
constexpr char INPUT_4[]  = "ttyAMA0:in4";  //!< Sensor port 4

constexpr char OUTPUT_A[] = "ttyAMA0:outA"; //!< Motor port A
constexpr char OUTPUT_B[] = "ttyAMA0:outB"; //!< Motor port B
constexpr char OUTPUT_C[] = "ttyAMA0:outC"; //!< Motor port C
constexpr char OUTPUT_D[] = "ttyAMA0:outD"; //!< Motor port D
#elif defined(EV3DEV_PLATFORM_BRICKPI3)
constexpr char INPUT_1[]  = "spi0.1:S1";  //!< Sensor port 1
constexpr char INPUT_2[]  = "spi0.1:S2";  //!< Sensor port 2
constexpr char INPUT_3[]  = "spi0.1:S3";  //!< Sensor port 3
constexpr char INPUT_4[]  = "spi0.1:S4";  //!< Sensor port 4

constexpr char OUTPUT_A[] = "spi0.1:MA"; //!< Motor port A
constexpr char OUTPUT_B[] = "spi0.1:MB"; //!< Motor port B
constexpr char OUTPUT_C[] = "spi0.1:MC"; //!< Motor port C
constexpr char OUTPUT_D[] = "spi0.1:MD"; //!< Motor port D
#elif defined(EV3DEV_PLATFORM_PISTORMS)
constexpr char INPUT_1[]  = "pistorms:BAS1"; //!< Sensor port 1
constexpr char INPUT_2[]  = "pistorms:BAS2"; //!< Sensor port 2
constexpr char INPUT_3[]  = "pistorms:BBS1"; //!< Sensor port 3
constexpr char INPUT_4[]  = "pistorms:BBS2"; //!< Sensor port 4

constexpr char OUTPUT_A[] = "pistorms:BAM1"; //!< Motor port A
constexpr char OUTPUT_B[] = "pistorms:BAM2"; //!< Motor port B
constexpr char OUTPUT_C[] = "pistorms:BBM1"; //!< Motor port C
constexpr char OUTPUT_D[] = "pistorms:BBM2"; //!< Motor port D
#else // assume EV3DEV_PLATFORM_EV3
/*
This code has been commented out by Eisverygoodletter
constexpr char INPUT_1[]  = "ev3-ports:in1";  //!< Sensor port 1
constexpr char INPUT_2[]  = "ev3-ports:in2";  //!< Sensor port 2
constexpr char INPUT_3[]  = "ev3-ports:in3";  //!< Sensor port 3
constexpr char INPUT_4[]  = "ev3-ports:in4";  //!< Sensor port 4

constexpr char OUTPUT_A[] = "ev3-ports:outA"; //!< Motor port A
constexpr char OUTPUT_B[] = "ev3-ports:outB"; //!< Motor port B
constexpr char OUTPUT_C[] = "ev3-ports:outC"; //!< Motor port C
constexpr char OUTPUT_D[] = "ev3-ports:outD"; //!< Motor port D
*/
#endif

//-----------------------------------------------------------------------------
// Generic device class.
//-----------------------------------------------------------------------------
class device {
    public:
        bool connect(const std::string &dir,
                const std::string &pattern,
                const std::map<std::string, std::set<std::string>> &match) noexcept;

        inline bool connected() const { return !_path.empty(); }

        int         device_index() const;

        int         get_attr_int   (const std::string &name) const;
        void        set_attr_int   (const std::string &name,
                int value);
        std::string get_attr_string(const std::string &name) const;
        void        set_attr_string(const std::string &name,
                const std::string &value);

        std::string get_attr_line  (const std::string &name) const;
        mode_set    get_attr_set   (const std::string &name,
                std::string *pCur = nullptr) const;

        std::string get_attr_from_set(const std::string &name) const;

    protected:
        std::string _path;
        mutable int _device_index = -1;
};

//-----------------------------------------------------------------------------
// The sensor class provides a uniform interface for using most of the
// sensors available for the EV3. The various underlying device drivers will
// create a `lego-sensor` device for interacting with the sensors.
// 
// Sensors are primarily controlled by setting the `mode` and monitored by
// reading the `value<N>` attributes. Values can be converted to floating point
// if needed by `value<N>` / 10.0 ^ `decimals`.
// 
// Since the name of the `sensor<N>` device node does not correspond to the port
// that a sensor is plugged in to, you must look at the `address` attribute if
// you need to know which port a sensor is plugged in to. However, if you don't
// have more than one sensor of each type, you can just look for a matching
// `driver_name`. Then it will not matter which port a sensor is plugged in to - your
// program will still work.
//-----------------------------------------------------------------------------
class sensor : protected device {
    public:
        typedef device_type sensor_type;

        static constexpr char ev3_touch[]      = "lego-ev3-touch";
        static constexpr char ev3_color[]      = "lego-ev3-color";
        static constexpr char ev3_ultrasonic[] = "lego-ev3-us";
        static constexpr char ev3_gyro[]       = "lego-ev3-gyro";
        static constexpr char ev3_infrared[]   = "lego-ev3-ir";

        static constexpr char nxt_touch[]      = "lego-nxt-touch";
        static constexpr char nxt_light[]      = "lego-nxt-light";
        static constexpr char nxt_sound[]      = "lego-nxt-sound";
        static constexpr char nxt_ultrasonic[] = "lego-nxt-us";
        static constexpr char nxt_i2c_sensor[] = "nxt-i2c-sensor";
        static constexpr char nxt_analog[]     = "nxt-analog";

        static constexpr char hitechnic_ir_seeker[] = "ht-nxt-ir-seek-v2";
        static constexpr char hitechnic_compass[] = "ht-nxt-compass";

        sensor(address_type);
        sensor(address_type, const std::set<sensor_type>&);

        using device::connected;
        using device::device_index;

        // Returns the value or values measured by the sensor. Check `num_values` to
        // see how many values there are. Values with index >= num_values will return
        // an error. The values are fixed point numbers, so check `decimals` to see
        // if you need to divide to get the actual value.
        int   value(unsigned index=0) const;

        // The value converted to float using `decimals`.
        float float_value(unsigned index=0) const;

        // Human-readable name of the connected sensor.
        std::string type_name() const;

        // Bin Data Format: read-only
        // Returns the format of the values in `bin_data` for the current mode.
        // Possible values are:
        //
        //    - `u8`: Unsigned 8-bit integer (byte)
        //    - `s8`: Signed 8-bit integer (sbyte)
        //    - `u16`: Unsigned 16-bit integer (ushort)
        //    - `s16`: Signed 16-bit integer (short)
        //    - `s16_be`: Signed 16-bit integer, big endian
        //    - `s32`: Signed 32-bit integer (int)
        //    - `float`: IEEE 754 32-bit floating point (float)
        std::string bin_data_format() const { return get_attr_string("bin_data_format"); };

        // Bin Data: read-only
        // Returns the unscaled raw values in the `value<N>` attributes as raw byte
        // array. Use `bin_data_format`, `num_values` and the individual sensor
        // documentation to determine how to interpret the data.
        const std::vector<char>& bin_data() const;

        // Bin Data: read-only
        // Writes the unscaled raw values in the `value<N>` attributes into the
        // user-provided struct/buffer.  Use `bin_data_format`, `num_values` and the
        // individual sensor documentation to determine how to interpret the data.
        template <class T>
            void bin_data(T *buf) const {
                bin_data(); // fills _bin_data
                std::copy_n(_bin_data.data(), _bin_data.size(), reinterpret_cast<char*>(buf));
            }

        // Address: read-only
        // Returns the name of the port that the sensor is connected to, e.g. `ev3:in1`.
        // I2C sensors also include the I2C address (decimal), e.g. `ev3:in1:i2c8`.
        std::string address() const { return get_attr_string("address"); }

        // Command: write-only
        // Sends a command to the sensor.
        sensor& set_command(std::string v) {
            set_attr_string("command", v);
            return *this;
        }

        // Commands: read-only
        // Returns a list of the valid commands for the sensor.
        // Returns -EOPNOTSUPP if no commands are supported.
        mode_set commands() const { return get_attr_set("commands"); }

        // Decimals: read-only
        // Returns the number of decimal places for the values in the `value<N>`
        // attributes of the current mode.
        int decimals() const { return get_attr_int("decimals"); }

        // Driver Name: read-only
        // Returns the name of the sensor device/driver. See the list of [supported
        // sensors] for a complete list of drivers.
        std::string driver_name() const { return get_attr_string("driver_name"); }

        // Mode: read/write
        // Returns the current mode. Writing one of the values returned by `modes`
        // sets the sensor to that mode.
        std::string mode() const { return get_attr_string("mode"); }
        sensor& set_mode(std::string v) {
            set_attr_string("mode", v);
            return *this;
        }

        // Modes: read-only
        // Returns a list of the valid modes for the sensor.
        mode_set modes() const { return get_attr_set("modes"); }

        // Num Values: read-only
        // Returns the number of `value<N>` attributes that will return a valid value
        // for the current mode.
        int num_values() const { return get_attr_int("num_values"); }

        // Units: read-only
        // Returns the units of the measured value for the current mode. May return
        // empty string
        std::string units() const { return get_attr_string("units"); }

    protected:
        sensor() {}

        bool connect(const std::map<std::string, std::set<std::string>>&) noexcept;

        mutable std::vector<char> _bin_data;
};

//-----------------------------------------------------------------------------
// A generic interface to control I2C-type EV3 sensors.
//-----------------------------------------------------------------------------
class i2c_sensor : public sensor {
    public:
        i2c_sensor(
                address_type address = INPUT_AUTO,
                const std::set<sensor_type> &types = {}
                );

        // FW Version: read-only
        // Returns the firmware version of the sensor if available. Currently only
        // I2C/NXT sensors support this.
        std::string fw_version() const { return get_attr_string("fw_version"); }

        // Poll MS: read/write
        // Returns the polling period of the sensor in milliseconds. Writing sets the
        // polling period. Setting to 0 disables polling. Minimum value is hard
        // coded as 50 msec. Returns -EOPNOTSUPP if changing polling is not supported.
        // Currently only I2C/NXT sensors support changing the polling period.
        int poll_ms() const { return get_attr_int("poll_ms"); }
        i2c_sensor& set_poll_ms(int v) {
            set_attr_int("poll_ms", v);
            return *this;
        }
};

class normal_sensor : public sensor {
    public:
        static constexpr char INPUT_1[] = "ev3-ports:in1";
        static constexpr char INPUT_2[] = "ev3-ports:in2";
        static constexpr char INPUT_3[] = "ev3-ports:in3";
        static constexpr char INPUT_4[] = "ev3-ports:in4";
        using sensor::sensor;
        //normal_sensor(address_type a) : sensor(a) {};
        normal_sensor(address_type a, const std::set<sensor_type>& b);
};

//-----------------------------------------------------------------------------
// LEGO EV3 color sensor.
//-----------------------------------------------------------------------------
class color_sensor : public normal_sensor {
    public:
        color_sensor(address_type address = INPUT_AUTO);

        // Reflected light. Red LED on.
        static constexpr char mode_col_reflect[] = "COL-REFLECT";

        // Ambient light. Red LEDs off.
        static constexpr char mode_col_ambient[] = "COL-AMBIENT";

        // Color. All LEDs rapidly cycling, appears white.
        static constexpr char mode_col_color[] = "COL-COLOR";

        // Raw reflected. Red LED on
        static constexpr char mode_ref_raw[] = "REF-RAW";

        // Raw Color Components. All LEDs rapidly cycling, appears white.
        static constexpr char mode_rgb_raw[] = "RGB-RAW";

        // No color.
        static constexpr char color_nocolor[] = "NoColor";

        // Black color.
        static constexpr char color_black[] = "Black";

        // Blue color.
        static constexpr char color_blue[] = "Blue";

        // Green color.
        static constexpr char color_green[] = "Green";

        // Yellow color.
        static constexpr char color_yellow[] = "Yellow";

        // Red color.
        static constexpr char color_red[] = "Red";

        // White color.
        static constexpr char color_white[] = "White";

        // Brown color.
        static constexpr char color_brown[] = "Brown";


        // Reflected light intensity as a percentage. Light on sensor is red.
        int reflected_light_intensity(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_col_reflect);
            return value(0);
        }

        // Ambient light intensity. Light on sensor is dimly lit blue.
        int ambient_light_intensity(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_col_ambient);
            return value(0);
        }

        // Color detected by the sensor, categorized by overall value.
        //   - 0: No color
        //   - 1: Black
        //   - 2: Blue
        //   - 3: Green
        //   - 4: Yellow
        //   - 5: Red
        //   - 6: White
        //   - 7: Brown
        int color(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_col_color);
            return value(0);
        }

        // Red, green, and blue components of the detected color, in the range 0-1020.
        std::tuple<int, int, int> raw(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_rgb_raw);
            return std::make_tuple( value(0), value(1), value(2) );
        }

        // Red component of the detected color, in the range 0-1020.
        int red(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_rgb_raw);
            return value(0);
        }

        // Green component of the detected color, in the range 0-1020.
        int green(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_rgb_raw);
            return value(1);
        }

        // Blue component of the detected color, in the range 0-1020.
        int blue(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_rgb_raw);
            return value(2);
        }
};

//-----------------------------------------------------------------------------
// LEGO EV3 ultrasonic sensor.
//-----------------------------------------------------------------------------
class ultrasonic_sensor : public normal_sensor {
    public:
        ultrasonic_sensor(address_type address = INPUT_AUTO);

        ultrasonic_sensor(address_type address, const std::set<sensor_type>& sensorTypes);

        // Continuous measurement in centimeters.
        static constexpr char mode_us_dist_cm[] = "US-DIST-CM";

        // Continuous measurement in inches.
        static constexpr char mode_us_dist_in[] = "US-DIST-IN";

        // Listen.
        static constexpr char mode_us_listen[] = "US-LISTEN";

        // Single measurement in centimeters.
        static constexpr char mode_us_si_cm[] = "US-SI-CM";

        // Single measurement in inches.
        static constexpr char mode_us_si_in[] = "US-SI-IN";


        // Measurement of the distance detected by the sensor,
        // in centimeters.
        float distance_centimeters(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_us_dist_cm);
            return float_value(0);
        }

        // Measurement of the distance detected by the sensor,
        // in inches.
        float distance_inches(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_us_dist_in);
            return float_value(0);
        }

        // Value indicating whether another ultrasonic sensor could
        // be heard nearby.
        bool other_sensor_present(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_us_listen);
            return value(0);
        }
};

//-----------------------------------------------------------------------------
// LEGO EV3 infrared sensor.
//-----------------------------------------------------------------------------
class infrared_sensor : public normal_sensor {
    public:
        infrared_sensor(address_type address = INPUT_AUTO);

        // Proximity
        static char mode_ir_prox[];

        // IR Seeker
        static char mode_ir_seek[];

        // IR Remote Control
        static char mode_ir_remote[];

        // IR Remote Control. State of the buttons is coded in binary
        static char mode_ir_rem_a[];

        // Calibration ???
        static char mode_ir_cal[];


        // A measurement of the distance between the sensor and the remote,
        // as a percentage. 100% is approximately 70cm/27in.
        int proximity(bool do_set_mode = true) {
            if (do_set_mode) set_mode(mode_ir_prox);
            return value(0);
        }
};



//-----------------------------------------------------------------------------
// Any device controlled by the generic LED driver.
// See https://www.kernel.org/doc/Documentation/leds/leds-class.txt
// for more details.
//-----------------------------------------------------------------------------
class led : protected device {
    public:
        led(std::string name);

        using device::connected;

        // Max Brightness: read-only
        // Returns the maximum allowable brightness value.
        int max_brightness() const { return get_attr_int("max_brightness"); }

        // Brightness: read/write
        // Sets the brightness level. Possible values are from 0 to `max_brightness`.
        int brightness() const { return get_attr_int("brightness"); }
        led set_brightness(int v) {
            set_attr_int("brightness", v);
            return *this;
        }

        // Triggers: read-only
        // Returns a list of available triggers.
        mode_set triggers() const { return get_attr_set("trigger"); }

        // Trigger: read/write
        // Sets the led trigger. A trigger
        // is a kernel based source of led events. Triggers can either be simple or
        // complex. A simple trigger isn't configurable and is designed to slot into
        // existing subsystems with minimal additional code. Examples are the `ide-disk` and
        // `nand-disk` triggers.
        // 
        // Complex triggers whilst available to all LEDs have LED specific
        // parameters and work on a per LED basis. The `timer` trigger is an example.
        // The `timer` trigger will periodically change the LED brightness between
        // 0 and the current brightness setting. The `on` and `off` time can
        // be specified via `delay_{on,off}` attributes in milliseconds.
        // You can change the brightness value of a LED independently of the timer
        // trigger. However, if you set the brightness value to 0 it will
        // also disable the `timer` trigger.
        std::string trigger() const { return get_attr_from_set("trigger"); }
        led set_trigger(std::string v) {
            set_attr_string("trigger", v);
            return *this;
        }

        // Delay On: read/write
        // The `timer` trigger will periodically change the LED brightness between
        // 0 and the current brightness setting. The `on` time can
        // be specified via `delay_on` attribute in milliseconds.
        int delay_on() const { return get_attr_int("delay_on"); }
        led set_delay_on(int v) {
            set_attr_int("delay_on", v);
            return *this;
        }

        // Delay Off: read/write
        // The `timer` trigger will periodically change the LED brightness between
        // 0 and the current brightness setting. The `off` time can
        // be specified via `delay_off` attribute in milliseconds.
        int delay_off() const { return get_attr_int("delay_off"); }
        led set_delay_off(int v) {
            set_attr_int("delay_off", v);
            return *this;
        }


        // Gets the LED's brightness as a percentage (0-1) of the maximum.
        float brightness_pct() const {
            return static_cast<float>(brightness()) / max_brightness();
        }

        // Sets the LED's brightness as a percentage (0-1) of the maximum.
        led set_brightness_pct(float v) {
            return set_brightness(v * max_brightness());
        }

        // Turns the led on by setting its brightness to the maximum level.
        void on()  { set_brightness(max_brightness()); }

        // Turns the led off.
        void off() { set_brightness(0); }

        // Enables timer trigger and sets delay_on and delay_off attributes to the
        // provided values (in milliseconds).
        void flash(unsigned on_ms, unsigned off_ms);

#if defined(EV3DEV_PLATFORM_BRICKPI)
        static led blue_led1;
        static led blue_led2;

        static std::vector<led*> led1;
        static std::vector<led*> led2;

        static std::vector<float> black;
        static std::vector<float> blue;
#elif defined(EV3DEV_PLATFORM_BRICKPI3)

        static led amber_led1;

        static std::vector<led*> led1;

        static std::vector<float> black;
        static std::vector<float> blue;

#elif defined(EV3DEV_PLATFORM_PISTORMS)
        static led red_left;
        static led red_right;
        static led green_left;
        static led green_right;
        static led blue_left;
        static led blue_right;

        static std::vector<led*> left;
        static std::vector<led*> right;

        static std::vector<float> black;
        static std::vector<float> red;
        static std::vector<float> green;
        static std::vector<float> blue;
        static std::vector<float> yellow;
        static std::vector<float> purple;
        static std::vector<float> cyan;
        static std::vector<float> white;
        static std::vector<float> orange;
#else
        static led red_left;
        static led red_right;
        static led green_left;
        static led green_right;

        static std::vector<led*> left;
        static std::vector<led*> right;

        static std::vector<float> black;
        static std::vector<float> red;
        static std::vector<float> green;
        static std::vector<float> amber;
        static std::vector<float> orange;
        static std::vector<float> yellow;
#endif

        // Assigns to each led in `group` corresponding brightness percentage from `color`.
        static void set_color(const std::vector<led*> &group, const std::vector<float> &color);

        static void all_off();

    protected:
        int _max_brightness = 0;
};

//-----------------------------------------------------------------------------
// A generic interface to read data from the system's power_supply class.
// Uses the built-in legoev3-battery if none is specified.
//-----------------------------------------------------------------------------
class power_supply : protected device {
    public:
        power_supply(std::string name);

        using device::connected;

        // Measured Current: read-only
        // The measured current that the battery is supplying (in microamps)
        int measured_current() const { return get_attr_int("current_now"); }

        // Measured Voltage: read-only
        // The measured voltage that the battery is supplying (in microvolts)
        int measured_voltage() const { return get_attr_int("voltage_now"); }

        // Max Voltage: read-only
        int max_voltage() const { return get_attr_int("voltage_max_design"); }

        // Min Voltage: read-only
        int min_voltage() const { return get_attr_int("voltage_min_design"); }

        // Technology: read-only
        std::string technology() const { return get_attr_string("technology"); }

        // Type: read-only
        std::string type() const { return get_attr_string("type"); }

        float measured_amps()       const { return measured_current() / 1000000.f; }
        float measured_volts()      const { return measured_voltage() / 1000000.f; }

        static power_supply battery;
};

//-----------------------------------------------------------------------------
// EV3 buttons
//-----------------------------------------------------------------------------
class button {
    public:
        button(int bit);

        // Check if the button is pressed.
        bool pressed() const;

        // Gets called whenever the button state changes.
        // The user has to call the process() function to check for state change.
        std::function<void(bool)> onclick;

        // Check if the button state has changed,
        // call onclick function in case it has.
        // Returns true if the state has changed since the last call.
        bool process();

        static button back;
        static button left;
        static button right;
        static button up;
        static button down;
        static button enter;

        // Call process() for each of the EV3 buttons.
        // Returns true if any of the states have changed since the last call.
        static bool process_all();

    private:
        int _bit;
        bool _state = false;
        std::vector<unsigned long> _buf;

        struct file_descriptor {
            int _fd;

            file_descriptor(const char *path, int flags);
            ~file_descriptor();
            operator int() { return _fd; }
        };

        std::shared_ptr<file_descriptor> _fd;
};

//-----------------------------------------------------------------------------
// EV3 Sound
//-----------------------------------------------------------------------------
class sound {
    public:
        static void beep(const std::string &args = "", bool bSynchronous = false);
        static void tone(float frequency, float ms, bool bSynchronous = false);
        static void tone(const std::vector< std::vector<float> > &sequence, bool bSynchronous = false);
        static void play(const std::string &soundfile, bool bSynchronous = false);
        static void speak(const std::string &text, bool bSynchronous = false);
};

//-----------------------------------------------------------------------------
// The `lego-port` class provides an interface for working with input and
// output ports that are compatible with LEGO MINDSTORMS RCX/NXT/EV3, LEGO
// WeDo and LEGO Power Functions sensors and motors. Supported devices include
// the LEGO MINDSTORMS EV3 Intelligent Brick, the LEGO WeDo USB hub and
// various sensor multiplexers from 3rd party manufacturers.
// 
// Some types of ports may have multiple modes of operation. For example, the
// input ports on the EV3 brick can communicate with sensors using UART, I2C
// or analog validate signals - but not all at the same time. Therefore there
// are multiple modes available to connect to the different types of sensors.
// 
// In most cases, ports are able to automatically detect what type of sensor
// or motor is connected. In some cases though, this must be manually specified
// using the `mode` and `set_device` attributes. The `mode` attribute affects
// how the port communicates with the connected device. For example the input
// ports on the EV3 brick can communicate using UART, I2C or analog voltages,
// but not all at the same time, so the mode must be set to the one that is
// appropriate for the connected sensor. The `set_device` attribute is used to
// specify the exact type of sensor that is connected. Note: the mode must be
// correctly set before setting the sensor type.
// 
// Ports can be found at `/sys/class/lego-port/port<N>` where `<N>` is
// incremented each time a new port is registered. Note: The number is not
// related to the actual port at all - use the `address` attribute to find
// a specific port.
//-----------------------------------------------------------------------------
class lego_port : protected device {
    public:
        lego_port(address_type);

        using device::connected;
        using device::device_index;

        // Address: read-only
        // Returns the name of the port. See individual driver documentation for
        // the name that will be returned.
        std::string address() const { return get_attr_string("address"); }

        // Driver Name: read-only
        // Returns the name of the driver that loaded this device. You can find the
        // complete list of drivers in the [list of port drivers].
        std::string driver_name() const { return get_attr_string("driver_name"); }

        // Modes: read-only
        // Returns a list of the available modes of the port.
        mode_set modes() const { return get_attr_set("modes"); }

        // Mode: read/write
        // Reading returns the currently selected mode. Writing sets the mode.
        // Generally speaking when the mode changes any sensor or motor devices
        // associated with the port will be removed new ones loaded, however this
        // this will depend on the individual driver implementing this class.
        std::string mode() const { return get_attr_string("mode"); }
        lego_port set_mode(std::string v) {
            set_attr_string("mode", v);
            return *this;
        }

        // Set Device: write-only
        // For modes that support it, writing the name of a driver will cause a new
        // device to be registered for that driver and attached to this port. For
        // example, since NXT/Analog sensors cannot be auto-detected, you must use
        // this attribute to load the correct driver. Returns -EOPNOTSUPP if setting a
        // device is not supported.
        lego_port set_set_device(std::string v) {
            set_attr_string("set_device", v);
            return *this;
        }

        // Status: read-only
        // In most cases, reading status will return the same value as `mode`. In
        // cases where there is an `auto` mode additional values may be returned,
        // such as `no-device` or `error`. See individual port driver documentation
        // for the full list of possible values.
        std::string status() const { return get_attr_string("status"); }

    protected:
        lego_port() {}

        bool connect(const std::map<std::string, std::set<std::string>>&) noexcept;
};

} // namespace ev3dev
