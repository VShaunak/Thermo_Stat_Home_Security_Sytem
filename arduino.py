import serial
import time
import mysql.connector
mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  password="root",
  database="thermostat"
)

print(mydb)
mycursor = mydb.cursor()
ser = serial.Serial('COM6', 9800, timeout=1)
time.sleep(2)
# [heat,coller,person,humidity,temp,alert]
# res = {
#     "heat":"",
#     "cooler":"",
#     "person":"",
#     "humidity":"",
#     "temp":"",
#     "alert":""
# }
res = ["","","","","",""]
while(1):
    line = ser.readline().decode()
    print(line)
    if line.split(" ")[0] == "q:":
        res[0] = str(line.split(" ")[1])
        res[1] = str(line.split(" ")[2])
        res[2] = str(line.split(" ")[3])
        res[3] = str(line.split(" ")[4])
        res[4] = str(line.split(" ")[5])
        res[5] = str(line.split(" ")[6][0:-1])
        sql = 'INSERT INTO records (heat,cooler,person,humidity,temp,alert) VALUES (' + res[0] + "," + res[1] + ","+ res[2] + ","+ res[3] + ","+ res[4] + "," + res[5] + ')'
        mycursor.execute(sql)
        mydb.commit()


        file1 = open("output_to_text.txt","a") 
        if res[0]==1 :
            file1.write("Turn on the heaters\n")
        else :    
            file1.write("Turn on the Coolers\n")
        if res[2]==1 :
            file1.write("Person in apartment\n")
        else :
            file1.write("Apartment is empty\n")
        if res[5]==1 :
            file1.write("Alert!! Fire is in the apartment!!\n")
        file1.write(res[3]+" %\n")
        file1.write(res[4]+" C\n")
        file1.write("\n\n\n")
        file1.close()
        
        print(res)
    
    
    
ser.close()
