import serial
import win32com.client as comclt

arduino = serial.Serial("COM5", 9600) # Escuchamos en el puerto COM en el que esta el 
#arduino a 9600 baudios.

selector = 0

# Este bloque de codigo recibe una cadena de caracteres que es enviada por el arduino y
# la procesa hasta dejar en limpio solo el valor que nos interesa.
while (1):
    while (arduino.inWaiting()==0):
        pass
    dato = arduino.readline() #dato = b'1\r\n'
    a = dato.splitlines()     #a = [b'1']
    b = str(a[0])             #b = b'1'
    c = b.replace("b","")     #c = '1'
    d = c.replace("'","")     #d = 1
    e = int(d) # En esta variable se guarda el valor final enviado por el arduino.
    #print(e)

#----------------------------------------------------
# Este bloque de codigo es el encargado de manejar la funcion del encoder en base al
# valor enviado por el arduino (102 o 103) 
    if e == 102:
        selector = 'ch1'
        print('Canal 1')
        
    elif e == 103:
        selector = 'ch2'
        print('Canal 2')
 
#----------------------------------------------------


    if e == 59:
        wsh= comclt.Dispatch("WScript.Shell")
        wsh.AppActivate("launcher.exe")
        wsh.SendKeys("{RIGHT}")

    if e == 61:
        wsh= comclt.Dispatch("WScript.Shell")
        wsh.AppActivate("launcher.exe")
        wsh.SendKeys("{LEFT}")


#----------------------------------------------------
    
    if selector == 'ch1':
        if e == 49:
            wsh= comclt.Dispatch("WScript.Shell")
            wsh.AppActivate("launcher.exe")
            wsh.SendKeys("A")

        if e == 51:
            wsh= comclt.Dispatch("WScript.Shell")
            wsh.AppActivate("launcher.exe")
            wsh.SendKeys("Q")
    else:
        pass

#----------------------------------------------------
    
    if selector == 'ch2':
        if e == 49:
            wsh= comclt.Dispatch("WScript.Shell")
            wsh.AppActivate("launcher.exe")
            wsh.SendKeys("S")

        if e == 51:
            wsh= comclt.Dispatch("WScript.Shell")
            wsh.AppActivate("launcher.exe")
            wsh.SendKeys("W")
    else:
        pass

#----------------------------------------------------

    if e == 1:  #SW2   >>Run/Stop<<
        wsh= comclt.Dispatch("WScript.Shell")
        wsh.AppActivate("launcher.exe")
        wsh.SendKeys("{F5}") #F5

    if e == 2:  #SW6   >>single trigger<<
        wsh= comclt.Dispatch("WScript.Shell")
        wsh.AppActivate("launcher.exe")
        wsh.SendKeys(" ") #Espacio
        

    if e == 3:  #SW8   >>AutoSet<<
        wsh= comclt.Dispatch("WScript.Shell")
        wsh.AppActivate("launcher.exe")
        wsh.SendKeys("^~") #CTRL + ENTER

#----------------------------------------------------
# Estos botones se dejan sin ninguna funcion para una posible actualizacion
# del software con mas shortcuts o tambien para agregar cualquier otro comando
# que use necesite.

    if e == 4:  #SW1
        wsh= comclt.Dispatch("WScript.Shell")
        wsh.AppActivate("launcher.exe")
        wsh.SendKeys("")

    if e == 5:  #SW5
        wsh= comclt.Dispatch("WScript.Shell")
        wsh.AppActivate("launcher.exe")
        wsh.SendKeys("")

    if e == 6:  #SW7
        wsh= comclt.Dispatch("WScript.Shell")
        wsh.AppActivate("launcher.exe")
        wsh.SendKeys("")
        
    if e == 7:  #SW4 (Pulsador encoder horizontal)
        wsh= comclt.Dispatch("WScript.Shell")
        wsh.AppActivate("launcher.exe")
        wsh.SendKeys("")