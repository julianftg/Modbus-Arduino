/*

  Basic.pde - example using ModbusMaster library
  
  This file is part of ModbusMaster.
  
  ModbusMaster is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  ModbusMaster is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with ModbusMaster.  If not, see <http://www.gnu.org/licenses/>.
  
  Written by Doc Walker (Rx)
  Copyright © 2009-2011 Doc Walker <dfwmountaineers at gmail dot com>
  
*/

#include <ModbusMaster.h>


// instantiate ModbusMaster object as slave ID 2
// defaults to serial port 0 since no port was specified
ModbusMaster node(1);


void setup()
{
  // initialize Modbus communication baud rate
  node.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}


void loop()
{
  static uint32_t i;
  uint8_t j, result;
  uint16_t data[6];
  
  i++;
  
  node.setTransmitBuffer(0, lowWord(i));                                            //Introduce el dati i en la direccion 0 del buffer.
  node.setTransmitBuffer(1, lowWord(i+1));                                          //Introduce el dato i+1 en la direccion 1 del buffer.
  
  result = node.writeMultipleRegisters(100, 2);                                     //Introduce el contenido del buffer en el registro 100 en las 2 primeras direcciones.
  
  result = node.readHoldingRegisters(100, 2);                                       //Lee las dos primeras direcciones del registro 100.
  
  if (result == node.ku8MBSuccess)                                                  //Si la lectura ha sido correcta hace lo siguiente.
  {
    for (j = 0; j < 2; j++)                                                         //Recorremos las dos primeras direcciones del buffer.
    {
      data[j] = node.getResponseBuffer(j);                                          //Introduce los datos del buffer en el array data[].
    }
    
    if (data[0]%2==0)                                                               //Si el primer dato del registro es par enciende la salida 12.
    {
      digitalWrite(12,HIGH);
    }
    else
    {
      digitalWrite(12,LOW);
    }
    
    if (data[1]%2==0)                                                               ////Si el segundo dato del registro es par enciende la salida 13.
    {
      digitalWrite(13,HIGH);
    }
    else
    {
      digitalWrite(13,LOW);
    }
  }
}

