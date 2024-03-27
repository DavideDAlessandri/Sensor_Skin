
void setupSensors1() {


    //-------------------SENSOR_0----------------------
  I2CMux1.openChannel(0);

  if (distanceSensor10.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 0 online");
  }else{
    Serial.println("Sensor 0 failed to init. Please check wiring. Freezing...");
    strip1 = false;
  }

  if (distanceSensor10.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip1 = false;
  }
  
  if(strip1){
    distanceSensor10.setTimingBudgetInMs(timeBudget);
    distanceSensor10.setIntermeasurementPeriod(mesPeriod);
    distanceSensor10.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux1.closeChannel(0);

  //-------------------SENSOR_1----------------------
  I2CMux1.openChannel(1);

  if (distanceSensor11.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 1 online");
  }else{
    Serial.println("Sensor 1 failed to init. Please check wiring. Freezing...");
    strip1 = false;
  }

  if (distanceSensor11.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip1 = false;
  }

  if(strip1){
    distanceSensor11.setTimingBudgetInMs(timeBudget);
    distanceSensor11.setIntermeasurementPeriod(mesPeriod);
    distanceSensor11.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux1.closeChannel(1);

  //-------------------SENSOR_2----------------------
  I2CMux1.openChannel(2);

  if (distanceSensor12.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 2 online");
  }else{
    Serial.println("Sensor 2 failed to init. Please check wiring. Freezing...");
    strip1 = false;
  }

  if (distanceSensor12.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip1 = false;
  }

  if(strip1){
    distanceSensor12.setTimingBudgetInMs(timeBudget);
    distanceSensor12.setIntermeasurementPeriod(mesPeriod);
    distanceSensor12.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux1.closeChannel(2);

  //-------------------SENSOR_3----------------------
  I2CMux1.openChannel(3);

  if (distanceSensor13.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 3 online");
  }else{
    Serial.println("Sensor 3 failed to init. Please check wiring. Freezing...");
    strip1 = false;
  }

  if (distanceSensor13.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip1 = false;
  }

  if(strip1){
    distanceSensor13.setTimingBudgetInMs(timeBudget);
    distanceSensor13.setIntermeasurementPeriod(mesPeriod);
    distanceSensor13.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux1.closeChannel(3);

  //-------------------SENSOR_4----------------------
  I2CMux1.openChannel(4);

  if (distanceSensor14.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 4 online");
  }else{
    Serial.println("Sensor 4 failed to init. Please check wiring. Freezing...");
    strip1 = false;
  }

  if (distanceSensor14.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip1 = false;
  }

  if(strip1){
    distanceSensor14.setTimingBudgetInMs(timeBudget);
    distanceSensor14.setIntermeasurementPeriod(mesPeriod);
    distanceSensor14.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux1.closeChannel(4);

  //-------------------SENSOR_5----------------------
  I2CMux1.openChannel(5);

  if (distanceSensor15.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 5 online");
  }else{
    Serial.println("Sensor 5 failed to init. Please check wiring. Freezing...");
    strip1 = false;
  }

  if (distanceSensor15.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip1 = false;
  }

  if(strip1){
    distanceSensor15.setTimingBudgetInMs(timeBudget);
    distanceSensor15.setIntermeasurementPeriod(mesPeriod);
    distanceSensor15.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux1.closeChannel(5);

    //-------------------SENSOR_6----------------------
  I2CMux1.openChannel(6);

  if (distanceSensor16.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 6 online");
  }else{
    Serial.println("Sensor 6 failed to init. Please check wiring. Freezing...");
    strip1 = false;
  }

  if (distanceSensor16.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip1 = false;
  }

  if(strip1){
    distanceSensor16.setTimingBudgetInMs(timeBudget);
    distanceSensor16.setIntermeasurementPeriod(mesPeriod);
    distanceSensor16.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux1.closeChannel(6);

    //-------------------SENSOR_7----------------------
  I2CMux1.openChannel(7);

  if (distanceSensor17.init() == false) //Begin returns 0 on a good init
  {
    Serial.println("Sensor 7 online");
  }else{
    Serial.println("Sensor 7 failed to init. Please check wiring. Freezing...");
    strip1 = false;
  }

  if (distanceSensor17.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    strip1 = false;
  }

  if(strip1){
    distanceSensor17.setTimingBudgetInMs(timeBudget);
    distanceSensor17.setIntermeasurementPeriod(mesPeriod);
    distanceSensor17.startRanging(); //Write configuration bytes to initiate measurement
  }

  I2CMux1.closeChannel(7);


}
