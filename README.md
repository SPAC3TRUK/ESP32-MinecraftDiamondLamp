# 💎 Minecraft Diamond Block — ESP32 Smart Lamp
![Arduino](https://img.shields.io/badge/Framework-Arduino-00979D?style=flat&logo=Arduino&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-E01E5A?style=for-the-badge&logo=microchip&logoColor=white)
![Espressif](https://img.shields.io/badge/Espressif-ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![Wi-Fi](https://img.shields.io/badge/Connectivity-Wi--Fi-0078D4?style=flat&logo=wifi&logoColor=white)
![License: CC BY-NC 4.0](https://licensebuttons.net/l/by-nc/4.0/88x31.png)

Ho ricreato il **Minecraft Diamond Block** con la stampante 3D e trasformato in una **lampada IoT** controllabile via **Wi‑Fi**.  
Il progetto utilizza un **ESP32 Mini**, un **LED Ring RGB** e una **Web App locale** per gestire colori, luminosità ed effetti direttamente dal browser.

---

## ✨ Caratteristiche

- 🖨️ **Struttura stampata in 3D**
- ⚡ **ESP32 Mini**
- 💡 **LED Ring RGB programmabile (NeoPixel)**
- 🌐 **Web App locale**
- 📱 **Controllo tramite Wi‑Fi**
- 🎨 **Color picker + luminosità**
- ✨ **Effetti luminosi**
- 💾 **Salvataggio impostazioni tramite LittleFS**

---

## 🛠️ Componenti

- ESP32 Mini: https://link.amazon/B00x8kVr5
- LED Ring RGB / NeoPixel: https://link.amazon/B04jFvVQS
- Pla Bianco: https://link.amazon/B065QobIY
- Jumper: https://link.amazon/B0eURkFrb
- NFC: https://link.amazon/B0h0Xi9Gp
- Fascette termorestringenti: https://link.amazon/B01QiYgsx

---

## 🖨️ Stampa 3D

La struttura è progettata per diffondere la luce del LED Ring attraverso il PLA, creando un effetto luminoso uniforme e brillante.

---

## 🌐 Web App

L’ESP32 ospita una **Web App locale**, accessibile dalla rete Wi‑Fi domestica.

Dall’interfaccia puoi controllare:

- 🎨 Colore  
- 💡 Luminosità  
- ✨ Effetti LED  
- 🔧 Impostazioni della lampada  

Non serve alcuna app esterna: basta aprire l’indirizzo IP della lampada nel browser.

---

## 💾 LittleFS

Le impostazioni della lampada (colore, luminosità, effetto, stato ON/OFF) vengono salvate nella memoria flash dell’ESP32 tramite **LittleFS**, così rimangono memorizzate anche dopo il riavvio.

---

## 📁 Struttura del progetto:

MinecraftDiamondBlockLamp/

File3d/
    DiamondBlockTop.stl
    DiamondBlockCase.stl

src/
    MinecraftDiamondBlockLamp.ino

InterfacciaWeb/
    InterfacciaWeb.html

SchemaElettrico/
    SchemaElettrico.png

LICENSE

README.md


---

## 🚀 Installazione

1. Scarica o clona il repository  
2. Carica il firmware sull’ESP32 (`src/`)  
3. Carica la Web App nella memoria LittleFS (`InterfacciaWeb/`)  
4. Collega il LED Ring all’ESP32  
5. Alimenta il dispositivo  
6. Apri la Web App tramite browser (IP locale dell’ESP32)

---

## 🎥 Video

- Instagram Reel: https://www.instagram.com/reel/DdZZKqiMZhV/?stkn=NnB2YzBtbjNwbHB1
- YouTube Short: https://www.instagram.com/p/DdZZAeKDNgT/?stkn=YmRwZjBmNWcwZnlr
- Instagram Post: https://youtube.com/shorts/xnRJrdtlhS4?is=AuE8z6JnThpuvshR

---

## 📸 Progetto

Da un semplice blocco di Minecraft a un piccolo progetto IoT completamente funzionante. 💎⚡  
Se lo ricrei, mi farebbe piacere vedere il tuo risultato!

---



## 📸 Foto
<img src="Immagini/1.png" width="350">
<img src="Immagini/4.png" width="350">

---

## 🔐 Licenza

Questo progetto è distribuito sotto licenza:

### **Creative Commons Attribution‑NonCommercial 4.0 International (CC BY‑NC 4.0)**  
![License: CC BY-NC 4.0](https://licensebuttons.net/l/by-nc/4.0/88x31.png)

Puoi:

- Condividere  
- Modificare  
- Creare progetti derivati  

Ma **non puoi usarlo per scopi commerciali**.

Testo completo della licenza:  
https://creativecommons.org/licenses/by-nc/4.0/

---

