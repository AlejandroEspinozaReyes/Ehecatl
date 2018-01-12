// YL-39 + YL-69 humidity sensor
byte humidity_sensor_pin = A1;
byte humidity_sensor_vcc = 6;
int MAX_SENSOR_VALUE = 750;
int MAX_HUMIDITY_VALUE = 650;

void setup() {
    // Init the humidity sensor board
    pinMode(humidity_sensor_vcc, OUTPUT);
    digitalWrite(humidity_sensor_vcc, LOW);

    // Setup Serial
    while (!Serial);
    delay(1000);
    Serial.begin(9600);
}

int readNormalHumiditySensor() {
    digitalWrite(humidity_sensor_vcc, HIGH);
    delay(5000);
    int value = analogRead(humidity_sensor_pin);
    digitalWrite(humidity_sensor_vcc, LOW);
    delay(5000);
    return value;
}

float getHumidityPercentage() {
    float humidity = readNormalHumiditySensor();
    float humidityStandarized = MAX_SENSOR_VALUE - humidity;
    float humidityPercentage = (humidityStandarized * 100) / MAX_HUMIDITY_VALUE;

    if (humidityPercentage < 0) {
        return 0;
    } else if (humidityPercentage > 100){
        return 100;
    } else {
        return humidityPercentage;
    }
}

void loop() {
    float percentage = getHumidityPercentage();
    Serial.println(" "); 
    Serial.print("Humidity Percentge: ");
    Serial.println(percentage); 
}
