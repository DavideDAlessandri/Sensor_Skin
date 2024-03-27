
void readSensors(){


    //-------------------sensor0-------------------------
  I2CMux.openChannel(0);

  while (!distanceSensor0.checkForDataReady())
  {
    delay(1);
  }
  distance0 = distanceSensor0.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor0.clearInterrupt();

  I2CMux.closeChannel(0);

  //-------------------sensor1-------------------------
  I2CMux.openChannel(1);

  while (!distanceSensor1.checkForDataReady())
  {
    delay(1);
  }
  distance1 = distanceSensor1.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor1.clearInterrupt();

  I2CMux.closeChannel(1);

  //-------------------sensor2-------------------------
  I2CMux.openChannel(2);

  while (!distanceSensor2.checkForDataReady())
  {
    delay(1);
  }
  distance2 = distanceSensor2.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor2.clearInterrupt();

  I2CMux.closeChannel(2);

  //-------------------sensor3-------------------------
  I2CMux.openChannel(3);

  while (!distanceSensor3.checkForDataReady())
  {
    delay(1);
  }
  distance3 = distanceSensor3.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor3.clearInterrupt();

  I2CMux.closeChannel(3);

  //-------------------sensor4-------------------------
  I2CMux.openChannel(4);

  while (!distanceSensor4.checkForDataReady())
  {
    delay(1);
  }
  distance4 = distanceSensor4.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor4.clearInterrupt();

  I2CMux.closeChannel(4);

  //-------------------sensor5-------------------------
  I2CMux.openChannel(5);

  while (!distanceSensor5.checkForDataReady())
  {
    delay(1);
  }
  distance5 = distanceSensor5.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor5.clearInterrupt();

  I2CMux.closeChannel(5);

    //-------------------sensor6-------------------------
  I2CMux.openChannel(6);

  while (!distanceSensor6.checkForDataReady())
  {
    delay(1);
  }
  distance6 = distanceSensor6.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor6.clearInterrupt();

  I2CMux.closeChannel(6);

    //-------------------sensor7-------------------------
  I2CMux.openChannel(7);

  while (!distanceSensor7.checkForDataReady())
  {
    delay(1);
  }
  distance7 = distanceSensor7.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor7.clearInterrupt();

  I2CMux.closeChannel(7);


}
