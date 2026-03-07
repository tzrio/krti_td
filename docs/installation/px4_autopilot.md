# PX4 Autopilot Installation Guide

Panduan ini untuk memasang PX4 Autopilot dan menyiapkan SITL untuk latihan KRTI.

---

# 1. Install PX4 Dependencies

```bash
sudo apt update
sudo apt install git python3-pip python3-jinja2 \
python3-empy python3-numpy python3-toml python3-yaml \
build-essential cmake ninja-build
```

---

# 2. Clone PX4 Repository

```bash
git clone https://github.com/PX4/PX4-Autopilot.git
cd PX4-Autopilot
```

Cek versi:

```bash
git describe --tags
```

Contoh output:

```
v1.17.0
```

---

# 3. Install PX4 Tools

```bash
bash Tools/setup/ubuntu.sh
```

Script ini menginstal dependency build dan simulator PX4.

---

# 4. Jalankan SITL (Tes Awal)

Default yang dipakai tim:

```bash
make px4_sitl gz_x500
```

Alternatif:

```bash
make px4_sitl gz
```

Expected output (contoh):

```
INFO  [px4] Startup script returned successfully
INFO  [init] PX4 SIM startup
```

Gazebo harus terbuka otomatis.

---

PX4 Autopilot siap dipakai untuk phase integrasi dan phase offboard.

