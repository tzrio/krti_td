# 📁 FILE 1 — README.md

# KRTI TD – Software Foundation Bootcamp

Repository ini adalah tahap fundamental untuk divisi Software (Autonomy & Flight System).

## 🎯 OBJECTIVE

Setiap anggota WAJIB mampu:

1. Install dan menjalankan:
   - ROS2 Humble
   - Gazebo (gz)
   - PX4 Autopilot (SITL)
   - QGroundControl

2. Menghubungkan:
   ROS2 ↔ PX4 SITL ↔ QGroundControl

3. Membuat node C++ Offboard:
   - ARM
   - TAKEOFF
   - HOVER (5 detik)
   - LAND
   - DISARM

4. Drone berhasil menyelesaikan misi tanpa failsafe.

---

# 🧱 SYSTEM STACK

- Ubuntu 22.04
- ROS2 Humble
- Gazebo Harmonic (gz)
- PX4 SITL
- QGroundControl

---

# 🚀 PHASE 1 – ENVIRONMENT SETUP

## 1️⃣ Install ROS2 Humble

Verifikasi:

```
ros2 topic list
```

---

## 2️⃣ Install Gazebo (gz)

Verifikasi:

```
gz sim shapes.sdf
```

---

## 3️⃣ Install QGroundControl

Pastikan bisa connect ke PX4 SITL.

---

## 4️⃣ Install PX4 Autopilot

```
git clone https://github.com/PX4/PX4-Autopilot.git
cd PX4-Autopilot
make px4_sitl gz_x500
```

Jika simulasi tidak berjalan → task dianggap gagal.

---

# 🔗 PHASE 2 – INTEGRATION CHECK

Wajib lulus semua:

```
ros2 topic echo /fmu/out/vehicle_odometry
```

Bisa publish ke:

```
/fmu/in/vehicle_command
```

---

# 💻 PHASE 3 – CODING CHALLENGE

Buat package:

```
ros2 pkg create offboard_control --build-type ament_cmake
```

State machine minimal:

INIT → ARM → TAKEOFF → HOVER → LAND → DISARM

Rules:

- Tidak boleh sleep sembarangan
- Harus cek vehicle_status
- Setpoint publish > 2Hz
- Tidak boleh failsafe

---

# ✅ VALIDATION RULES

Task dianggap berhasil jika:

- Drone takeoff stabil
- Hover tidak drift berlebihan
- Landing smooth
- Tidak ada failsafe
- Video bukti disertakan

---

# 🧠 THEORY CHECK

Anggota harus bisa menjelaskan:

1. Apa itu Offboard Mode?
2. Kenapa setpoint harus publish terus?
3. Bedanya position control dan velocity control?
4. Arsitektur komunikasi ROS2 → PX4?

---

# 📁 FILE 2 — src/offboard_control.cpp

```cpp
#include <rclcpp/rclcpp.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>
#include <px4_msgs/msg/vehicle_status.hpp>

using namespace std::chrono_literals;

class OffboardControl : public rclcpp::Node
{
public:
    OffboardControl() : Node("offboard_control")
    {
        offboard_pub_ = create_publisher<px4_msgs::msg::OffboardControlMode>(
            "/fmu/in/offboard_control_mode", 10);

        trajectory_pub_ = create_publisher<px4_msgs::msg::TrajectorySetpoint>(
            "/fmu/in/trajectory_setpoint", 10);

        command_pub_ = create_publisher<px4_msgs::msg::VehicleCommand>(
            "/fmu/in/vehicle_command", 10);

        status_sub_ = create_subscription<px4_msgs::msg::VehicleStatus>(
            "/fmu/out/vehicle_status", 10,
            std::bind(&OffboardControl::status_callback, this, std::placeholders::_1));

        timer_ = create_wall_timer(100ms, std::bind(&OffboardControl::run, this));

        state_ = State::INIT;
        counter_ = 0;
    }

private:
    enum class State
    {
        INIT,
        ARM,
        TAKEOFF,
        HOVER,
        LAND,
        DISARM,
        DONE
    };

    State state_;
    uint64_t counter_;
    px4_msgs::msg::VehicleStatus current_status_;

    rclcpp::Publisher<px4_msgs::msg::OffboardControlMode>::SharedPtr offboard_pub_;
    rclcpp::Publisher<px4_msgs::msg::TrajectorySetpoint>::SharedPtr trajectory_pub_;
    rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr command_pub_;
    rclcpp::Subscription<px4_msgs::msg::VehicleStatus>::SharedPtr status_sub_;
    rclcpp::TimerBase::SharedPtr timer_;

    void status_callback(const px4_msgs::msg::VehicleStatus::SharedPtr msg)
    {
        current_status_ = *msg;
    }

    void publish_vehicle_command(uint16_t command, float param1 = 0.0)
    {
        px4_msgs::msg::VehicleCommand msg{};
        msg.command = command;
        msg.param1 = param1;
        msg.target_system = 1;
        msg.target_component = 1;
        msg.source_system = 1;
        msg.source_component = 1;
        msg.from_external = true;
        command_pub_->publish(msg);
    }

    void publish_offboard_control_mode()
    {
        px4_msgs::msg::OffboardControlMode msg{};
        msg.position = true;
        offboard_pub_->publish(msg);
    }

    void publish_position_setpoint(float x, float y, float z)
    {
        px4_msgs::msg::TrajectorySetpoint msg{};
        msg.position = {x, y, z};
        trajectory_pub_->publish(msg);
    }

    void run()
    {
        publish_offboard_control_mode();

        switch (state_)
        {
        case State::INIT:
            if (counter_ > 20)
                state_ = State::ARM;
            break;

        case State::ARM:
            publish_vehicle_command(
                px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM,
                1.0);
            state_ = State::TAKEOFF;
            break;

        case State::TAKEOFF:
            publish_position_setpoint(0.0, 0.0, -5.0);
            if (counter_ > 100)
                state_ = State::HOVER;
            break;

        case State::HOVER:
            publish_position_setpoint(0.0, 0.0, -5.0);
            if (counter_ > 200)
                state_ = State::LAND;
            break;

        case State::LAND:
            publish_vehicle_command(
                px4_msgs::msg::VehicleCommand::VEHICLE_CMD_NAV_LAND);
            state_ = State::DISARM;
            break;

        case State::DISARM:
            publish_vehicle_command(
                px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM,
                0.0);
            state_ = State::DONE;
            break;

        case State::DONE:
            RCLCPP_INFO(get_logger(), "Mission Completed");
            break;
        }

        counter_++;
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OffboardControl>());
    rclcpp::shutdown();
    return 0;
}
```
