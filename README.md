## **ESP8266** & **MQTT** & **ReactJS** & **Adafruit SI1145** Kullanarak Işığın Dalga Boyunun Ölçümünün Web Ortamında Gösterilmesi

<br>

### **Web Kurulumu**

<br>

> Projenin Local'de Çalıştırılması

- Öncelikle projeyi bilgisayarınıza klonlayın.

`git clone https://github.com/elektronikDevrelerim/espDalgaBoyu.git`

- Sonrasında komut satırına sırayla aşağıdaki kodları yazın ve gerekli paketlerin kurulumunu gerçekleştirin.

```
cd Downloads/espDalgaBoyu

yarn
```

> :warning: **Burada Downloads yerine kendi bilgisayarınızdaki dosya yolunu vermeniz gerekmektedir.**

- Kurulumlar tamamlandıktan sonra, `yarn start` komutu ile web uygulamasını başlatın!

<br>

### **Arduino IDE ve Gerekli Kodların Kurulumu**

<br>

> Klonlamış Olduğunuz Proje İçindeki **esp_dalgaBoyu.ino** Adlı Arduino Projesini Açın.

> **Sonrasında [Buradan](https://codeload.github.com/adafruit/Adafruit_SI1145_Library/zip/refs/heads/master) SI1145 Sensörü İçin Gerekli Kütüphaneyi İndirin.**

> İndirdiğiniz ZIP Uzantılı Dosyayı Arduino IDE İçerisinde **Taslak > Library Ekle > ZIP Kitaplığı Ekle** Bölümünden Ekleyin.

Ekleme İşlemini Gerçekleştirdikten Sonra Kod Üzerinde Değiştirmeniz Güncellemeniz Gereken Satırları Güncelleyin.

````
const char* ssid = "Buraya Kendi WiFi Adınız!";
const char* password = "Buraya Kendi WiFi Şifreniz!";```
````

> Gerekli Güncellemeleri Yaptıktan Sonra Projeyi, ESP Kartınıza Yüklemek İçin **Araçlar** Sekmesinden **Size Uygun Olan Kartı** ve **COM Port**'u Seçin. Ve **Yükleme** İşlemini Başlatın.

<br>

**İlk Başta Başlatmış Olduğumuz Web Arayüzüne [http://localhost:3000](http://localhost:3000) Adresinden Erişebilir, Gelen Verileri Görebilirsiniz.**

<br>

**Elektronik Devrelerim © Development Team**

- **[celikdev](https://github.com/celikdev)**
- **[nerawn](https://github.com/nerawn)**
- **[virtueer](https://github.com/virtueer)**
