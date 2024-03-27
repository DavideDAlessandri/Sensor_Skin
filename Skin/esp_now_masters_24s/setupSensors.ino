
void setupSensors() {


    //-------------------SENSOR_0----------------------
  I2CMux.openChannel(0);

  if (distanceSensor0.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 0 online");
  }else{
    Serial.println("Sensor 0 failed to init. Please check wiring. Freezing...");
    strip0 = false;
  }

  if (distanceSensor0.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip0 = false;
  }
  
  if(strip0){
    distanceSensor0.setTimingBudgetInMs(timeBudget);
    distanceSensor0.setIntermeasurementPeriod(mesPeriod);
    distanceSensor0.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux.closeChannel(0);

  //-------------------SENSOR_1----------------------
  I2CMux.openChannel(1);

  if (distanceSensor1.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 1 online");
  }else{
    Serial.println("Sensor 1 failed to init. Please check wiring. Freezing...");
    strip0 = false;
  }

  if (distanceSensor1.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip0 = false;
  }

  if(strip0){
    distanceSensor1.setTimingBudgetInMs(timeBudget);
    distanceSensor1.setIntermeasurementPeriod(mesPeriod);
    distanceSensor1.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux.closeChannel(1);

  //-------------------SENSOR_2----------------------
  I2CMux.openChannel(2);

  if (distanceSensor2.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 2 online");
  }else{
    Serial.println("Sensor 2 failed to init. Please check wiring. Freezing...");
    strip0 = false;
  }

  if (distanceSensor2.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip0 = false;
  }

  if(strip0){
    distanceSensor2.setTimingBudgetInMs(timeBudget);
    distanceSensor2.setIntermeasurementPeriod(mesPeriod);
    distanceSensor2.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux.closeChannel(2);

  //-------------------SENSOR_3----------------------
  I2CMux.openChannel(3);

  if (distanceSensor3.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 3 online");
  }else{
    Serial.println("Sensor 3 failed to init. Please check wiring. Freezing...");
    strip0 = false;
  }

  if (distanceSensor3.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip0 = false;
  }

  if(strip0){
    distanceSensor3.setTimingBudgetInMs(timeBudget);
    distanceSensor3.setIntermeasurementPeriod(mesPeriod);
    distanceSensor3.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux.closeChannel(3);

  //-------------------SENSOR_4----------------------
  I2CMux.openChannel(4);

  if (distanceSensor4.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 4 online");
  }else{
    Serial.println("Sensor 4 failed to init. Please check wiring. Freezing...");
    strip0 = false;
  }

  if (distanceSensor4.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip0 = false;
  }

  if(strip0){
    distanceSensor4.setTimingBudgetInMs(timeBudget);
    distanceSensor4.setIntermeasurementPeriod(mesPeriod);
    distanceSensor4.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux.closeChannel(4);

  //-------------------SENSOR_5----------------------
  I2CMux.openChannel(5);

  if (distanceSensor5.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 5 online");
  }else{
    Serial.println("Sensor 5 failed to init. Please check wiring. Freezing...");
    strip0 = false;
  }

  if (distanceSensor5.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip0 = false;
  }

  if(strip0){
    distanceSensor5.setTimingBudgetInMs(timeBudget);
    distanceSensor5.setIntermeasurementPeriod(mesPeriod);
    distanceSensor5.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux.closeChannel(5);

    //-------------------SENSOR_6----------------------
  I2CMux.openChannel(6);

  if (distanceSensor6.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 6 online");
  }else{
    Serial.println("Sensor 6 failed to init. Please check wiring. Freezing...");
    strip0 = false;
  }

  if (distanceSensor6.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip0 = false;
  }

  if(strip0){
    distanceSensor6.setTimingBudgetInMs(timeBudget);
    distanceSensor6.setIntermeasurementPeriod(mesPeriod);
    distanceSensor6.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux.closeChannel(6);

    //-------------------SENSOR_7----------------------
  I2CMux.openChannel(7);

  if (distanceSensor7.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 7 online");
  }else{
    Serial.println("Sensor 7 failed to init. Please check wiring. Freezing...");
    strip0 = false;
  }

  if (distanceSensor7.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip0 = false;
  }

  if(strip0){
    distanceSensor7.setTimingBudgetInMs(timeBudget);
    distanceSensor7.setIntermeasurementPeriod(mesPeriod);
    distanceSensor7.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux.closeChannel(7);


}
