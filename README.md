💎 Minecraft Diamond Block — ESP32 Smart Lamp

Un blocco di diamanti di Minecraft ricreato con la stampante 3D e trasformato in una lampada IoT controllabile via Wi-Fi.
Il progetto utilizza un ESP32 Mini, un LED Ring RGB e una Web App locale per controllare la lampada direttamente dallo smartphone o dal browser.

✨ Caratteristiche:
    • 🖨️ Struttura stampata in 3D
    • ⚡ ESP32 Mini
    • 💡 LED Ring RGB programmabile
    • 🌐 Web App locale
    • 📱 Controllo tramite Wi-Fi
    • 🎨 Controllo di colori e luminosità
    • ✨ Effetti luminosi
    • 💾 Salvataggio delle impostazioni tramite LittleFS
    
🛠️ Componenti:
    • ESP32 Mini
    • LED Ring RGB / NeoPixel
    • Struttura stampata in 3D
    
🖨️ Stampa 3D:
La struttura è stata progettata per permettere alla luce del LED Ring di diffondersi attraverso il PLA.

🌐 Web App:
L'ESP32 crea una Web App accessibile dalla rete locale.
Dall'interfaccia è possibile controllare:
    • Colore
    • Luminosità
    • Effetti LED
    • Impostazioni della lampada
Non è necessario utilizzare un'applicazione esterna: è sufficiente collegarsi alla Web App tramite browser.

💾 LittleFS:
Le impostazioni della lampada vengono salvate nella memoria flash dell'ESP32 utilizzando LittleFS.
In questo modo le impostazioni possono essere mantenute anche dopo il riavvio della scheda.

📁 Struttura del progetto:

MinecraftDiamondBlockLamp/
├── File3d/
│   ├── DiamondBlockTop.stl
│   ├── DiamondBlockCase.stl
│  
│
├── src/
│   ├── MinecraftDiamondBlockLamp.ino
│
│
├── InterfacciaWeb/
│   ├── InterfacciaWeb.html
│
│
├── SchemaElettrico/
│   ├── SchemaElettrico.png
│   └── README.md
│
├── LICENSE
│
└── README.md


🚀 Installazione:
    1. Scarica o clona il repository.
    2. Carica il firmware sull'ESP32.
    3. Carica i file della Web App nella memoria LittleFS.
    4. Collega il LED Ring all'ESP32.
    5. Accendi il dispositivo.
    6. Collegati alla Web App tramite browser.
    
🎥 Video:

📸 Progetto
Da un semplice blocco di Minecraft a un piccolo progetto IoT completamente funzionante. 💎⚡
Se lo ricrei, mi farebbe piacere vedere il tuo risultato!
