# Gazebo Garden Installation Guide (Ubuntu 22.04)

Gazebo is used for simulation with ROS2 and PX4.

---

# 1. Add Gazebo Repository

```bash
sudo apt update
sudo apt install lsb-release wget gnupg
```

Add key:

```bash
sudo wget https://packages.osrfoundation.org/gazebo.gpg \
-O /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg
```

Add repository:

```bash
echo "deb [signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] \
http://packages.osrfoundation.org/gazebo/ubuntu-stable \
$(lsb_release -cs) main" | \
sudo tee /etc/apt/sources.list.d/gazebo-stable.list
```

---

# 2. Install Gazebo

```bash
sudo apt update
sudo apt install gz-garden
```

---

# 3. Test Gazebo

Run:

```bash
gz sim
```

### Expected Output

Gazebo GUI window opens with:

```
Gazebo Garden Simulation Environment
```

Terminal log example:

```
[GUI] Loaded plugin
[Sim] Gazebo Sim started successfully
```

---

Gazebo installation completed successfully.

