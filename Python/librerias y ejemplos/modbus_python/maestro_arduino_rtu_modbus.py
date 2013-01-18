#!/usr/bin/env python
# -*- coding: utf_8 -*-

import sys

#add logging capability
import logging
import threading
import time
import modbus_tk
import modbus_tk.defines as cst
import modbus_tk.modbus as modbus
import modbus_tk.modbus_rtu as modbus_rtu
import serial

logger = modbus_tk.utils.create_logger(name="console", record_format="%(message)s")

if __name__ == "__main__":
    #Create the server
    server = modbus_rtu.RtuServer(serial.Serial(port="/dev/ttyACM0", baudrate=9600))
        
    try:
        logger.info("running...")
        logger.info("enter 'quit' for closing the server")
        
        server.start()

        slave_1 = server.add_slave(1)
        slave_1.add_block('0', cst.HOLDING_REGISTERS, 40001, 1)
        while True:
            time.sleep(.1)
            dato=slave_1.get_values('0',40001,1)

            print dato[0]
            
    finally:
        server.stop()
