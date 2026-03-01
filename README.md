# KRTI TD – Vajraakasha 2026 [Autonomy & Flight Systems (1)] 

Repository ini adalah tahap fundamental divisi Software.

---

# 🎯 OBJECTIVE

1. Install & verifikasi:
   - ROS2 Humble
   - Gazebo 
   - PX4 Autopilot
   - QGroundControl

2. Integrasi PX4 ↔ QGC
3. Menjalankan misi autonomous sederhana

---

# 🚀 PHASE 1 – INSTALLATION

Semua instalasi WAJIB mengikuti panduan resmi di dalam repository ini.

Klik langsung file berikut:

- [ROS2 Humble Installation](docs/installation/ros2_humble.md)
- [Gazebo Installation](docs/installation/gazebo.md)
- [PX4 Autopilot Installation](docs/installation/px4_autopilot.md)
- [QGroundControl Installation](docs/installation/qgroundcontrol.md)

---

# 🔗 PHASE 2 – INTEGRATION CHECK

## 1️⃣ PX4 SITL Gazebo
Terminal 1. Command dari folder PX4-Autopilot:
```
make px4_sitl gz_x500
```
EXPECTED OUTPUT:
```
INFO  [px4] Startup script returned successfully
INFO  [mavlink] MAVLink only on localhost
INFO  [init] PX4 SIM startup
```
Gazebo harus terbuka otomatis.

##

## 2️⃣ QGroundControl
Terminal 2. Command di folder yang ada QGroundControl.AppImage:
```
./QGroundControl-x86_64.AppImage
```
EXPECTED OUTPUT:

- QGC terbuka tanpa crash
- Vehicle terdeteksi otomatis
- Status: Ready to Fly

Jika tidak terhubung → cek UDP link.

---

# 🤖 PHASE 3 – AUTONOMOUS MISSION (OFFBOARD CONTROL)

Pada fase ini, anggota WAJIB:
- Membuat node C++ ROS2
- Menggunakan PX4 Offboard Mode
- Mengirim setpoint secara kontinu
- Menjalankan sequence:
1. Arm
2. Takeoff
3. Hover
4. Land
   
##

##📦 ROS2 WORKSPACE STRUCTURE
```
ros2_ws/
├── src/
│   │
│   ├── offboard_cpp/
│   │   ├── CMakeLists.txt
│   │   ├── package.xml
│   │   ├── launch/
│   │   │   └── offboard.launch.py
│   │   └── src/
│   │       └── offboard_node.cpp
│   │
│   ├── offboard_py/
│   │   ├── package.xml
│   │   ├── setup.py
│   │   ├── setup.cfg
│   │   ├── launch/
│   │   │   └── offboard.launch.py
│   │   └── offboard_py/
│   │       ├── __init__.py
│   │       └── offboard_node.py
│   │
│   └── px4_msgs/   
│
├── build/
├── install/
└── log/
```
##

## 1️⃣ Build Workspace

Masuk ke ros2_ws:

```
cd ros2_ws
colcon build
source install/setup.bash
```

EXPECTED OUTPUT:

```
Summary: X packages finished
```

Tidak boleh ada tulisan:
FAILED

##

## 2️⃣ Jalankan PX4 SITL

```
cd PX4-Autopilot
make px4_sitl gz_x500
```

EXPECTED OUTPUT akhir:

```
INFO  [px4] Startup script returned successfully
INFO  [init] PX4 SIM startup
```

Gazebo harus terbuka otomatis.

##

## 3️⃣ Jalankan Offboard Node

Untuk C++:

```
ros2 launch offboard_cpp offboard.launch.py
```

Untuk Python:

```
ros2 launch offboard_py offboard.launch.py
```

##

## 4️⃣ Verifikasi Mode

```
ros2 topic echo /fmu/out/vehicle_status
```

EXPECTED OUTPUT:

nav_state: 14
arming_state: 2

nav_state 14 = OFFBOARD
arming_state 2 = ARMED

