#include <rclcpp/rclcpp.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>

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

        timer_ = create_wall_timer(100ms, std::bind(&OffboardControl::run, this));

        counter_ = 0;

        RCLCPP_INFO(get_logger(), "Offboard FORCE MODE Started");
    }

private:
    rclcpp::Publisher<px4_msgs::msg::OffboardControlMode>::SharedPtr offboard_pub_;
    rclcpp::Publisher<px4_msgs::msg::TrajectorySetpoint>::SharedPtr trajectory_pub_;
    rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr command_pub_;
    rclcpp::TimerBase::SharedPtr timer_;

    uint64_t counter_;

    uint64_t get_timestamp()
    {
        return this->get_clock()->now().nanoseconds() / 1000;
    }

    void publish_vehicle_command(uint16_t command, float param1 = 0.0, float param2 = 0.0)
    {
        px4_msgs::msg::VehicleCommand msg{};
        msg.timestamp = get_timestamp();
        msg.command = command;
        msg.param1 = param1;
        msg.param2 = param2;
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
        msg.timestamp = get_timestamp();
        msg.position = true;
        msg.velocity = false;
        msg.acceleration = false;
        offboard_pub_->publish(msg);
    }

    void publish_position_setpoint(float x, float y, float z)
    {
        px4_msgs::msg::TrajectorySetpoint msg{};
        msg.timestamp = get_timestamp();
        msg.position = {x, y, z};
        trajectory_pub_->publish(msg);
    }

    void run()
    {
        // STREAM WAJIB sebelum dan selama offboard
        publish_offboard_control_mode();
        publish_position_setpoint(0.0, 0.0, -5.0);

        // setelah 5 detik
        if (counter_ == 50)
        {
            RCLCPP_INFO(get_logger(), "FORCE OFFBOARD");
            publish_vehicle_command(
                px4_msgs::msg::VehicleCommand::VEHICLE_CMD_DO_SET_MODE,
                1,
                6); // OFFBOARD
        }

        // setelah 30 detik
        if (counter_ == 300)
        {
            RCLCPP_INFO(get_logger(), "FORCE ARM");
            publish_vehicle_command(
                px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM,
                1.0);
        }

        // landing setelah 400 detik
        if (counter_ == 400)
        {
            RCLCPP_INFO(get_logger(), "LAND");
            publish_vehicle_command(
                px4_msgs::msg::VehicleCommand::VEHICLE_CMD_NAV_LAND);
        }

        // disarm
        if (counter_ == 500)
        {
            RCLCPP_INFO(get_logger(), "DISARM");
            publish_vehicle_command(
                px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM,
                0.0);
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
