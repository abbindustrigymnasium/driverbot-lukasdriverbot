 <h1> Planering</h1>

 <h2> Mål </h2>

Målet är att utveckla en legobil som styrs med en mikrokontroller. Det ska gå att styra legobilen via en webbplats som är kopplad till mikrokontrollern genom MQTT. Webbsidan byggs med svelte.

<h2> Funktionalitet </h2>

<ul>
<li>Fjärrstyrning av bilens rörelser: framåt, bakåt, vänster och höger.</li>

<li>Live-uppdatering av bilens status på webbsidan (t.ex hastighet och riktning).</li>

<li>Möjlighet till anpassning av bilens hastighet via webbgränssnittet</li>
<ul>
<h2> Pseudokod </h2>
<pre>
<code>
// Setup för mikrokontroller
INITIALIZE ESP8266
CONNECT TO WIFI
SETUP MQTT CONNECTION
// Huvudloop för att lyssna på kommandon
LOOP:
    IF NEW MQTT MESSAGE:
        PARSE MESSAGE
        IF COMMAND == "FORWARD":
            MOVE CAR FORWARD
        ELSE IF COMMAND == "BACK":
            MOVE CAR BACKWARD
        ELSE IF COMMAND == "LEFT":
            TURN CAR LEFT
        ELSE IF COMMAND == "RIGHT":
            TURN CAR RIGHT
        UPDATE CAR STATUS
    END IF
    SLEEP

// Webbsida
INITIALIZE WEB APPLICATION
SETUP MQTT CLIENT
CONNECT TO MQTT BROKER

// Användargränssnitt för att skicka kommandon
USER INPUT HANDLER:
    ON "FORWARD" BUTTON CLICK:
        SEND MQTT MESSAGE "FORWARD"
    ON "BACK" BUTTON CLICK:
        SEND MQTT MESSAGE "BACK"
    ON "LEFT" BUTTON CLICK:
        SEND MQTT MESSAGE "LEFT"
    ON "RIGHT" BUTTON CLICK:
        SEND MQTT MESSAGE "RIGHT"
</pre>
</code>
<h2>Skiss av webbsida</h2>
<img src = "https://github.com/abbindustrigymnasium/driverbot-lukasdriverbot/blob/main/Skiss.jpg?raw=true"> <img>

<h2>Tidsplan</h2>
<pre>
<code>
vecka 16: Implementera mottagning av MQTT-meddelanden 
vecka 17: 3d printa motorhållaren. Börja cadda de andra delarna.
vecka 18: Bygga webbsidan
vecka 19: Integrera MQTT för att skicka styrkommandon från webbsidan.
vecka 20: 3d printa resten av delarna. börja bygga legobilen.
vecka 21: Extra funktionalitet.
vecka 22: Bli klar.
</pre>
</code>



