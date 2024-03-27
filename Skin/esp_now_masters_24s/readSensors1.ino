
void readSensors1(){


    //-------------------sensor0-------------------------
  I2CMux1.openChannel(0);

  while (!distanceSensor10.checkForDataReady())
  {
    delay(1);
  }
  distance0 = distanceSensor10.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor10.clearInterrupt();

  I2CMux1.closeChannel(0);

  //-------------------sensor1-------------------------
  I2CMux1.openChannel(1);

  while (!distanceSensor11.checkForDataReady())
  {
    delay(1);
  }
  distance1 = distanceSensor11.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor11.clearInterrupt();

  I2CMux1.closeChannel(1);

  //-------------------sensor2-------------------------
  I2CMux1.openChannel(2);

  while (!distanceSensor12.checkForDataReady())
  {
    delay(1);
  }
  distance2 = distanceSensor12.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor12.clearInterrupt();

  I2CMux1.closeChannel(2);

  //-------------------sensor3-------------------------
  I2CMux1.openChannel(3);

  while (!distanceSensor13.checkForDataReady())
  {
    delay(1);
  }
  distance3 = distanceSensor13.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor13.clearInterrupt();

  I2CMux1.closeChannel(3);

  //-------------------sensor4-------------------------
  I2CMux1.openChannel(4);

  while (!distanceSensor14.checkForDataReady())
  {
    delay(1);
  }
  distance4 = distanceSensor14.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor14.clearInterrupt();

  I2CMux1.closeChannel(4);

  //-------------------sensor5-------------------------
  I2CMux1.openChannel(5);

  while (!distanceSensor15.checkForDataReady())
  {
    delay(1);
  }
  distance5 = distanceSensor15.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor15.clearInterrupt();

  I2CMux1.closeChannel(5);

  //-------------------sensor6-------------------------
  I2CMux1.openChannel(6);

  while (!distanceSensor16.checkForDataReady())
  {
    delay(1);
  }
  distance6 = distanceSensor16.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor16.clearInterrupt();

  I2CMux1.closeChannel(6);

  //-------------------sensor7-------------------------
  I2CMux1.openChannel(7);

  while (!distanceSensor17.checkForDataReady())
  {
    delay(1);
  }
  distance7 = distanceSensor17.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor17.clearInterrupt();

  I2CMux1.closeChannel(7);


}
