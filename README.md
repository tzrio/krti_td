# 📦 KRTI TD – SOFTWARE FOUNDATION REPOSITORY STRUCTURE (UPDATED)

Struktur repository diperbarui agar:
- Setiap instalasi punya file .md sendiri
- Setiap verifikasi memiliki EXPECTED OUTPUT
- Bisa dipakai sebagai standar kelulusan internal

---

krtitd-software-foundation/
│
├── README.md
├── validation_checklist.md
├── demo_video_link.txt
│
├── docs/
│   ├── installation/
│   │   ├── ros2_humble.md
│   │   ├── gazebo_gz.md
│   │   ├── px4_autopilot.md
│   │   └── qgroundcontrol.md
│   │
│   ├── px4_ros_architecture.md
│   └── offboard_explained.md
│
└── ros2_ws/
    └── src/
        └── offboard_control/
            ├── CMakeLists.txt
            ├── package.xml
            ├── launch/
            │   └── offboard.launch.py
            └── src/
                └── offboard_control.cpp

====================================================

# 📄 README.md (UPDATED FORMAT)

# KRTI TD – Software Foundation Bootcamp

Repository ini adalah tahap fundamental divisi Software.

Semua instalasi WAJIB mengikuti file di folder:

docs/installation/

---

# 🎯 OBJECTIVE

1. Install & verifikasi:
   - ROS2 Humble
   - Gazebo (gz)
   - PX4 Autopilot
   - QGroundControl

2. Integrasi ROS2 ↔ PX4 ↔ QGC
3. Menjalankan misi autonomous sederhana

---

# 🚀 PHASE 1 – INSTALLATION

Semua detail ada di:

- docs/installation/ros2_humble.md
- docs/installation/gazebo_gz.md
- docs/installation/px4_autopilot.md
- docs/installation/qgroundcontrol.md

Setiap file berisi:
- Step instalasi
- Command verifikasi
- EXPECTED OUTPUT (yang harus muncul di terminal)

Jika output berbeda → dianggap gagal setup.

---

# 🔗 PHASE 2 – INTEGRATION CHECK

## 1️⃣ Cek PX4 Running

Command:

ros2 topic list

EXPECTED OUTPUT minimal mengandung:

/fmu/in/vehicle_command
/fmu/in/offboard_control_mode
/fmu/out/vehicle_odometry
/fmu/out/vehicle_status

Jika topic /fmu tidak muncul → XRCE-DDS tidak terhubung.

---

## 2️⃣ Cek Odometry

Command:

ros2 topic echo /fmu/out/vehicle_odometry

EXPECTED OUTPUT:

Header:
  stamp:
    sec: ...
position:
  - 0.0
  - 0.0
  - ...

Data harus terus update (tidak berhenti).

---

## 3️⃣ Cek PX4 SITL

Command dari folder PX4:

make px4_sitl gz_x500

EXPECTED OUTPUT:

INFO  [px4] Startup script returned successfully
INFO  [mavlink] MAVLink only on localhost
INFO  [init] PX4 SIM startup

Gazebo harus terbuka otomatis.

---

# 📄 docs/installation/ros2_humble.md

## Verifikasi

Command:

ros2 doctor

EXPECTED OUTPUT:

All checks passed

Command:

ros2 topic list

EXPECTED OUTPUT:

/parameter_events
/rosout

Jika command tidak dikenali → ROS belum tersource.

====================================================

# 📄 docs/installation/gazebo_gz.md

Command:

gz sim shapes.sdf

EXPECTED OUTPUT:

Gazebo window terbuka
Terminal menampilkan:

[Msg] Loaded world

Jika error "command not found" → Gazebo belum terinstall.

====================================================

# 📄 docs/installation/px4_autopilot.md

Command:

make px4_sitl gz_x500

EXPECTED OUTPUT akhir:

INFO  [px4] Startup script returned successfully

Jika muncul dependency error → setup belum valid.

====================================================

# 📄 docs/installation/qgroundcontrol.md

EXPECTED BEHAVIOR:

- QGC terbuka tanpa crash
- Vehicle terdeteksi otomatis
- Status: Ready to Fly

Jika tidak terhubung → cek UDP link.

====================================================

# 🔥 KENAPA FORMAT INI LEBIH BAGUS?

- Tidak ada alasan "di laptopku bisa"
- Semua verifikasi ada standar output
- Bisa jadi standar kelulusan internal
- Memaksa anggota benar-benar paham setup

====================================================

Kalau mau next upgrade:
- Tambahin screenshot contoh output
- Tambahin section troubleshooting detail
- Atau bikin auto validation script bash
