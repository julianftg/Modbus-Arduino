#!/usr/bin/env python
# -*- coding: utf_8 -*-
"""
 Modbus TestKit: example of a custom simulator

 (C)2009 - Luc Jean - luc.jean@gmail.com
 (C)2009 - Apidev - http://www.apidev.fr

 This is distributed under GNU LGPL license, see license.txt

"""
from modbus_tk.utils import create_logger
from modbus_tk.simulator import Simulator, LOGGER
from modbus_tk.defines import *
import modbus_tk.modbus_tcp as modbus_tcp

class MySimulator(Simulator):
    """A custom simulator"""
    def __init__(self):
        """Constructor"""
        
        Simulator.__init__(self, modbus_tcp.TcpServer())
        
        # create a slave and block
        slave = self.server.add_slave(1)
        slave.add_block("foo", HOLDING_REGISTERS, 0, 100)
        

if __name__ == "__main__":
    simu = MySimulator()
    
    try:
        LOGGER.info("'quit' for closing the server")
        simu.start()
        
    except Exception, excpt:
        print excpt
            
    finally:
        simu.close()

