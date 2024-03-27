
void readSensors2(){


    //-------------------sensor0-------------------------
  I2CMux2.openChannel(0);

  while (!distanceSensor20.checkForDataReady())
  {
    delay(1);
  }
  distance0 = distanceSensor20.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor20.clearInterrupt();

  I2CMux2.closeChannel(0);

  //-------------------sensor1-------------------------
  I2CMux2.openChannel(1);

  while (!distanceSensor21.checkForDataReady())
  {
    delay(1);
  }
  distance1 = distanceSensor21.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor21.clearInterrupt();

  I2CMux2.closeChannel(1);

  //-------------------sensor2-------------------------
  I2CMux2.openChannel(2);

  while (!distanceSensor22.checkForDataReady())
  {
    delay(1);
  }
  distance2 = distanceSensor22.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor22.clearInterrupt();

  I2CMux2.closeChannel(2);

  //-------------------sensor3-------------------------
  I2CMux2.openChannel(3);

  while (!distanceSensor23.checkForDataReady())
  {
    delay(1);
  }
  distance3 = distanceSensor23.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor23.clearInterrupt();

  I2CMux2.closeChannel(3);

  //-------------------sensor4-------------------------
  I2CMux2.openChannel(4);

  while (!distanceSensor24.checkForDataReady())
  {
    delay(1);
  }
  distance4 = distanceSensor24.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor24.clearInterrupt();

  I2CMux2.closeChannel(4);

  //-------------------sensor5-------------------------
  I2CMux2.openChannel(5);

  while (!distanceSensor25.checkForDataReady())
  {
    delay(1);
  }
  distance5 = distanceSensor25.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor25.clearInterrupt();

  I2CMux2.closeChannel(5);

    //-------------------sensor6-------------------------
  I2CMux2.openChannel(6);

  while (!distanceSensor26.checkForDataReady())
  {
    delay(1);
  }
  distance6 = distanceSensor26.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor26.clearInterrupt();

  I2CMux2.closeChannel(6);

    //-------------------sensor7-------------------------
  I2CMux2.openChannel(7);

  while (!distanceSensor27.checkForDataReady())
  {
    delay(1);
  }
  distance7 = distanceSensor27.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor27.clearInterrupt();

  I2CMux2.closeChannel(7);


}
