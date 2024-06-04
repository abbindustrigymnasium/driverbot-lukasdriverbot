// MQTT Client Configuration
const clientId = 'mqttjs_' + Math.random().toString(16).substr(2, 8);
const host = 'ws://broker.emqx.io:8083/mqtt'; // Use 'wss://' and port 8084 for secure connection

// MQTT Client Options
const options = {
  keepalive: 60,
  clientId: clientId,
  protocolId: 'MQTT',
  protocolVersion: 4,
  clean: true,
  reconnectPeriod: 1000,
  connectTimeout: 30 * 1000,
  will: {
    topic: 'WillMsg',
    payload: 'Connection Closed abnormally..!',
    qos: 0,
    retain: false
  },
};

// MQTT Client Connection
function connectMqttClient() {
  try {
    console.log('Connecting MQTT client');
    const client = mqtt.connect(host, options);
    return client;
  } catch (error) {
    console.error('Error connecting to MQTT broker:', error);
    return null;
  }
}

// Event Handlers
function onClientError(error) {
  console.log('Connection error:', error);
}

function onClientReconnect() {
  console.log('Reconnecting...');
}

function onClientConnect() {
  console.log(`Client connected: ${clientId}`);
  document.getElementById("status").textContent = "Status: Connected";
  logMessage("Connected to MQTT broker");

  // Subscribe to the control topic
  client.subscribe('control/topic', { qos: 0 });
}

function onClientMessage(topic, message) {
  console.log(`Received Message: ${message.toString()} on topic: ${topic}`);
  document.getElementById("log").innerHTML += `<div>Received: ${message.toString()}</div>`;
}

// Log Message Function
function logMessage(message) {
  document.getElementById("log").innerHTML += `<div>${message}</div>`;
}

// Send Command Function
function sendCommand(command) {
  if (client && client.connected) {
    client.publish('control/topic', command, { qos: 0, retain: false });
    logMessage(`Command sent: ${command}`);
  } else {
    logMessage("Error: MQTT client is not connected");
  }
}

// Event Listeners for Buttons
document.getElementById('upButton').addEventListener('click', () => sendCommand('Forward'));
document.getElementById('downButton').addEventListener('click', () => sendCommand('Backwards'));
document.getElementById('leftButton').addEventListener('click', () => sendCommand('Left'));
document.getElementById('rightButton').addEventListener('click', () => sendCommand('Right'));
document.getElementById('stopButton').addEventListener('click', () => sendCommand('Stop'));

// Connect to MQTT Broker
const client = connectMqttClient();

if (client) {
  client.on('error', onClientError);
  client.on('reconnect', onClientReconnect);
  client.on('connect', onClientConnect);
  client.on('message', onClientMessage);
} else {
  logMessage("Error: Unable to connect to MQTT broker");
}
