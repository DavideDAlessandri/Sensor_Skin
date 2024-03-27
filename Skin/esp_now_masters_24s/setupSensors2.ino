
void setupSensors2() {


    //-------------------SENSOR_0----------------------
  I2CMux2.openChannel(0);

  if (distanceSensor20.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 0 online");
  }else{
    Serial.println("Sensor 0 failed to init. Please check wiring. Freezing...");
    strip2 = false;
  }

  if (distanceSensor20.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip2 = false;
  }
  
  if(strip2){
    distanceSensor20.setTimingBudgetInMs(timeBudget);
    distanceSensor20.setIntermeasurementPeriod(mesPeriod);
    distanceSensor20.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux2.closeChannel(0);

  //-------------------SENSOR_1----------------------
  I2CMux2.openChannel(1);

  if (distanceSensor21.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 1 online");
  }else{
    Serial.println("Sensor 1 failed to init. Please check wiring. Freezing...");
    strip2 = false;
  }

  if (distanceSensor21.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip2 = false;
  }

  if(strip2){
    distanceSensor21.setTimingBudgetInMs(timeBudget);
    distanceSensor21.setIntermeasurementPeriod(mesPeriod);
    distanceSensor21.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux2.closeChannel(1);

  //-------------------SENSOR_2----------------------
  I2CMux2.openChannel(2);

  if (distanceSensor22.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 2 online");
  }else{
    Serial.println("Sensor 2 failed to init. Please check wiring. Freezing...");
    strip2 = false;
  }

  if (distanceSensor22.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip2 = false;
  }

  if(strip2){
    distanceSensor22.setTimingBudgetInMs(timeBudget);
    distanceSensor22.setIntermeasurementPeriod(mesPeriod);
    distanceSensor22.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux2.closeChannel(2);

  //-------------------SENSOR_3----------------------
  I2CMux2.openChannel(3);

  if (distanceSensor23.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 3 online");
  }else{
    Serial.println("Sensor 3 failed to init. Please check wiring. Freezing...");
    strip2 = false;
  }

  if (distanceSensor23.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip2 = false;
  }

  if(strip2){
    distanceSensor23.setTimingBudgetInMs(timeBudget);
    distanceSensor23.setIntermeasurementPeriod(mesPeriod);
    distanceSensor23.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux2.closeChannel(3);

  //-------------------SENSOR_4----------------------
  I2CMux2.openChannel(4);

  if (distanceSensor24.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 4 online");
  }else{
    Serial.println("Sensor 4 failed to init. Please check wiring. Freezing...");
    strip2 = false;
  }

  if (distanceSensor24.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip2 = false;
  }

  if(strip2){
    distanceSensor24.setTimingBudgetInMs(timeBudget);
    distanceSensor24.setIntermeasurementPeriod(mesPeriod);
    distanceSensor24.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux2.closeChannel(4);

  //-------------------SENSOR_5----------------------
  I2CMux2.openChannel(5);

  if (distanceSensor25.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 5 online");
  }else{
    Serial.println("Sensor 5 failed to init. Please check wiring. Freezing...");
    strip2 = false;
  }

  if (distanceSensor25.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip2 = false;
  }

  if(strip2){
    distanceSensor25.setTimingBudgetInMs(timeBudget);
    distanceSensor25.setIntermeasurementPeriod(mesPeriod);
    distanceSensor25.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux2.closeChannel(5);

    //-------------------SENSOR_6----------------------
  I2CMux2.openChannel(6);

  if (distanceSensor26.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 6 online");
  }else{
    Serial.println("Sensor 6 failed to init. Please check wiring. Freezing...");
    strip2 = false;
  }

  if (distanceSensor26.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip2 = false;
  }

  if(strip2){
    distanceSensor26.setTimingBudgetInMs(timeBudget);
    distanceSensor26.setIntermeasurementPeriod(mesPeriod);
    distanceSensor26.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux2.closeChannel(6);

    //-------------------SENSOR_7----------------------
  I2CMux2.openChannel(7);

  if (distanceSensor27.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 7 online");
  }else{
    Serial.println("Sensor 7 failed to init. Please check wiring. Freezing...");
    strip2 = false;
  }

  if (distanceSensor27.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip2 = false;
  }

  if(strip2){
    distanceSensor27.setTimingBudgetInMs(timeBudget);
    distanceSensor27.setIntermeasurementPeriod(mesPeriod);
    distanceSensor27.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux2.closeChannel(7);


}
