# QGroundControl Installation Guide

QGroundControl digunakan untuk monitoring vehicle PX4 dan basic mission control.

---

# 1. Download QGroundControl

```bash
wget https://d176tv9ibo4jno.cloudfront.net/latest/QGroundControl.AppImage
```

---

# 2. Make Executable

```bash
chmod +x QGroundControl.AppImage
```

---

# 3. Run QGroundControl

```bash
./QGroundControl.AppImage
```

### Expected Output

- QGroundControl GUI terbuka
- Tidak crash saat startup
- Saat PX4 SITL aktif, vehicle terdeteksi otomatis

Contoh status saat terhubung:

```
Connected to Vehicle
PX4 Autopilot detected
```

---

Untuk alur praktik, jalankan QGC setelah PX4 SITL dan MicroXRCEAgent aktif.

