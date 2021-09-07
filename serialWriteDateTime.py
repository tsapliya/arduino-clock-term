#!/usr/bin/env python3
import serial
import time
import datetime
import glob, os

while 0==0:
    devList = os.listdir('/dev')
    i = ''
    whileI = 0
    for i in devList :
        if 'ttyUSB' in i:
            try:
                ser = serial.Serial('/dev/' + i, 2000000)
            except IndexError as err:
                print('error!' + err)
            else:  
                time.sleep(2)
                if ser.isOpen():
                    print ("Port Open")

                i = 800

                while whileI==0:
                    try:
                        readAR = ser.readline().decode()
                    except:
                        print('read error')
                        whileI = 1
                    else:          
                        date = datetime.datetime.today()
                        if (i == 800):
                            i = 0
                            f = open('/var/www/html/weatherData.txt', 'a')
                            f.write(date.strftime("%d.%m.%Y|%H:%M:%S~" + readAR))
                            f.close()
                        else:
                            i = i + 1
                        print(readAR)
                        time.sleep(2)   
                        try:
                            ser.write( date.strftime("%d.%m.%y %B | %H:%M:%S %A ").encode())
                        except:
                            print('write error')
                            whileI = 1    
                ser.close()
        
       

    
