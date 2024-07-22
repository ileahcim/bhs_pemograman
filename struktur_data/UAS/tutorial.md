# Tutorial Membuat Database perpustakaan.
# Yang belum install wsl,silahkan install dulu yaa


1. pada ubuntu ketik:
```
mkdir perpustakaan
```
2. setelah itu bikin file "docker-compose.yml" ,copas semua codingan dibawah ini
```
version: '3'

services:
  mysql_cpp:
    image: mariadb:10.2
    container_name: mysql_cpp
    restart: unless-stopped
    tty: true
    ports:
      - "31235:3306"
    volumes:
      - ./database/data:/var/lib/mysql
      - ./database/conf.d:/etc/mysql/conf.d:ro
    environment:
      MYSQL_USER: root
      MYSQL_PASSWORD: 123
      MYSQL_ROOT_PASSWORD: 123
      SERVICE_TAGS: dev
      SERVICE_NAME: mysql
    read_only: false

  # phpmyadmin:
  #   image: phpmyadmin:latest
  #   container_name: phpmyadmin
  #   restart: always
  #   ports:
  #     - 9100:80
  #   environment:
  #     - PMA_ARBITRARY=1

```
3. bikin file lagi ".env" ,copas codingan dibawah ini 
```
COMPOSE_PROJECT_NAME=perpustakaan
IMAGE_TAG=latest
```
4. setelah itu di dalam file perpustakaan (terminal) ketikan : 
```
docker compose up -d --build
```
5. setelah itu silahkan pada navicat 
```
create new connection (pilih mysql)
```
6. set : 
```
connection name: mysql (bebas mau namain apa aja)
host : 127.0.0.1
port: 31235
username: root
password : 123

PASTIKAN CONTAINER MYSQL BERJALAN , cek nya di docker
LALU "TEST CONECTION" DAHULU SEBELUM KLIK "OK"
```
7. setelah itu klik dibagian connection yang bernama mysql setelah itu :
```
create new database
```
9. isi dengan dengan nama "perpustakaan"
10. setelah itu bikin tabel admins :
```
1. Pilih database perpustakaan.
2. Klik kanan pada Tables dan pilih "New Table".
3. Buat kolom dengan konfigurasi berikut:

username: VARCHAR(255), PRIMARY KEY
password: VARCHAR(255), NOT NULL

4. Klik "Save" dan beri nama tabel admins.
```
10. lanjut bikin tabel perbukuan : 
```
1. Pilih database perpustakaan.
2. Klik kanan pada Tables dan pilih "New Table".
3. Buat kolom dengan konfigurasi berikut:

id: INT, AUTO_INCREMENT, PRIMARY KEY
judul: VARCHAR(255), NOT NULL
penulis: VARCHAR(255), NOT NULL
penerbit: VARCHAR(255), NOT NULL
tahun_terbit: VARCHAR(4), NOT NULL

4. Klik "Save" dan beri nama tabel perbukuan.
```

11. setelah itu bikin codingan nya(samplenya ada di file "crud.cc" )

12. sebelum connect to db, pada terminal silahkan ketikan : 
```
apt-get install libmysqlclient-dev
```
13. compile code : 
```
g++ -o crud_simple crud.cc -lmysqlclient
```
14. running hasil compile nya : 
```
./crud_simple
```


15. Selamat Anda telah berhasil mengikuti tutorial membuat database perpustakaan menggunakan WSL 2, Docker, dan Navicat. Jika ada kesulitan, pastikan untuk memeriksa setiap langkah dan pastikan kalo semuanya tidak typo ;).