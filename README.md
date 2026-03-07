# KRTI TD – Vajraakasha 2026 [Autonomy & Flight Systems (1)]

Repository ini adalah materi fundamental divisi software untuk alur PX4 + ROS2 offboard control (SITL).

---

# 🎯 OBJECTIVE

1. Install dan verifikasi environment:
   - ROS2 Humble
   - Gazebo
   - PX4 Autopilot
   - QGroundControl
   - Micro XRCE-DDS Agent
2. Cek integrasi PX4 ↔ QGC ↔ ROS2
3. Menjalankan misi autonomous sederhana dengan package `offboard_control`

---

# 📚 URUTAN BELAJAR (WAJIB DIKUTI)

1. Selesaikan **Phase 1** sampai semua software terpasang.
2. Jalankan **Phase 2** untuk memastikan koneksi antar sistem normal.
3. Jalankan **Phase 3** untuk offboard C++ mission.

Jika ada error, perbaiki per phase (jangan lompat ke phase berikutnya).

---

# 🚀 PHASE 1 – INSTALLATION

Ikuti dokumen resmi berikut secara berurutan:

1. [ROS2 Humble Installation](docs/installation/ros2_humble.md)
2. [Gazebo Installation](docs/installation/gazebo.md)
3. [PX4 Autopilot Installation](docs/installation/px4_autopilot.md)
4. [QGroundControl Installation](docs/installation/qgroundcontrol.md)
5. [MicroXRCEAgent Installation](docs/installation/microxrceagent.md)

---

# 🔗 PHASE 2 – INTEGRATION CHECK

Gunakan 3 terminal terpisah.

## 1️⃣ Terminal 1: PX4 SITL + Gazebo

Masuk ke folder `PX4-Autopilot`, lalu jalankan salah satu:

```bash
make px4_sitl gz_x500
```

Alternatif jika device/model berbeda:

```bash
make px4_sitl gz
```

Expected output (contoh):

```
INFO  [px4] Startup script returned successfully
INFO  [init] PX4 SIM startup
```

Gazebo harus terbuka otomatis.

## 2️⃣ Terminal 2: Micro XRCE-DDS Agent

```bash
MicroXRCEAgent udp4 -p 8888
```

Expected output:

```
Micro XRCE-DDS Agent listening on UDP port 8888
Client connected
Session established
```

## 3️⃣ Terminal 3: QGroundControl

Jalankan dari folder AppImage:

```bash
./QGroundControl.AppImage
```

Expected:

- QGC terbuka tanpa crash
- Vehicle terdeteksi otomatis
- Status siap terbang

---

# 🤖 PHASE 3 – AUTONOMOUS MISSION (OFFBOARD C++)

Phase ini fokus package ROS2 yang sudah ada di repo:

```
ros2_ws/src/offboard_control
```

Urutan run phase 3:

1. Build ROS2 workspace
2. Jalankan PX4 SITL
3. Jalankan MicroXRCEAgent
4. Jalankan QGroundControl
5. Jalankan node offboard C++
6. Verifikasi mode OFFBOARD

## 1️⃣ Build workspace (wajib ulang supaya paham alur)

```bash
cd ros2_ws
colcon build
source install/setup.bash
```

Expected output:

```
Summary: X packages finished
```

Pastikan tidak ada status `FAILED`.

## 2️⃣ Jalankan PX4 SITL

```bash
cd PX4-Autopilot
make px4_sitl gz_x500
```

Alternatif:

```bash
make px4_sitl gz
```

## 3️⃣ Jalankan MicroXRCEAgent

```bash
MicroXRCEAgent udp4 -p 8888
```

Jika command tidak dikenali, lakukan:

```bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

Lalu jalankan lagi agent.

## 4️⃣ Jalankan QGroundControl

```bash
./QGroundControl.AppImage
```

## 5️⃣ Jalankan offboard node C++

Buka terminal baru, lalu:

```bash
cd ros2_ws
source install/setup.bash
ros2 run offboard_control offboard_node
```

## 6️⃣ Verifikasi mode OFFBOARD

Di terminal lain:

```bash
ros2 topic echo /fmu/out/vehicle_status
```

Indikator yang dicari:

- `nav_state: 14` (OFFBOARD)
- `arming_state: 2` (ARMED)

---

# 🧭 CATATAN REPO

- Folder `ros2_ws/build`, `ros2_ws/install`, `ros2_ws/log` adalah artifact build/runtime lokal.
- Fokus pembelajaran utama ada di `README.md`, folder `docs/installation`, dan package `ros2_ws/src/offboard_control`.

