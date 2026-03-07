# Micro XRCE-DDS Agent Installation

Micro XRCE-DDS Agent diperlukan untuk komunikasi antara PX4 dan ROS2 (`px4_msgs`).

---

# 1. Install Dependencies

```bash
sudo apt update
sudo apt install git cmake build-essential
```

---

# 2. Clone Repository

```bash
git clone https://github.com/eProsima/Micro-XRCE-DDS-Agent.git
cd Micro-XRCE-DDS-Agent
```

---

# 3. Build Agent

```bash
mkdir -p build
cd build
cmake ..
make
sudo make install
```

---

# 4. Run Agent

```bash
MicroXRCEAgent udp4 -p 8888
```

Jika command tidak dikenali, jalankan:

```bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

Lalu ulangi command `MicroXRCEAgent`.

### Expected Output

```
Micro XRCE-DDS Agent listening on UDP port 8888
```

Saat PX4 tersambung:

```
Client connected
Session established
```

---

Urutan saat praktik: jalankan PX4 SITL dulu, lalu Agent ini, kemudian QGroundControl dan node ROS2.

