# ROS 2 Humble Installation Guide (Ubuntu 22.04)

This guide installs **ROS 2 Humble Hawksbill** on Ubuntu 22.04.
https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html

---

# 1. Setup Locale

```bash
sudo apt update
sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
```

### Expected Output

```
Generating locales...
Generation complete.
```

---

# 2. Add ROS2 Repository

```bash
sudo apt install software-properties-common
sudo add-apt-repository universe
```

Add ROS key:

```bash
sudo apt update
sudo apt install curl
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key \
-o /usr/share/keyrings/ros-archive-keyring.gpg
```

Add repository:

```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | \
sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```

---

# 3. Install ROS2

```bash
sudo apt update
sudo apt install ros-humble-desktop
```

### Expected Output

```
Setting up ros-humble-desktop ...
Processing triggers for libc-bin ...
```

---

# 4. Setup Environment

```bash
source /opt/ros/humble/setup.bash
```

Optional permanent setup:

```bash
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

---

# 5. Test ROS2 Installation

Run:

```bash
ros2 run demo_nodes_cpp talker
```

Open another terminal:

```bash
ros2 run demo_nodes_cpp listener
```

### Expected Output

Talker:

```
[INFO] Publishing: 'Hello World: 1'
```

Listener:

```
[INFO] I heard: 'Hello World: 1'
```

---

ROS2 Humble installation is now complete.

