#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>

modbusDevice regBank;

modbusSlave slave;

void setup()
{  
  regBank.setId(1);
  
  regBank.add(30001); //añade un registro de entrada analogica.
  regBank.add(40001); //Añade un registro de salida analgica.
  
  slave._device = &regBank;
  
  slave.setBaud(9600);
}
  
 void loop()
 {
   regBank.set(30001,1);
   regBank.set(40001,1);
 }
