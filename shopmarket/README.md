# Market code

## **Storage managment**

This is an inventory management program. The program keep track of the inventory balance (the number of items in stock) for different products. Each product should be represented by a number, name (up to 20 characters), and inventory balance. The program provide a menu to allow the user to perform the following actions as long as they desire:

1. Register new products
2. Print all products
3. Search for products
4. Modify the inventory balance of products
5. Sort products
6. Unregister products
7. Exit the program

### **Running the code**
To initiate the program, use the following command:
>gcc main.c functions.c filefunctions.c -o main.exe  

>./main.exe my_inventory.txt

change <span style="color: orange">_my_inventory_</span>.txt to desired file for reading and writing to. 

### **Running the code**
Example of file format: 

|Itemnumber|Name|In stock|
|----------|----|--------|
|101|apple|5|
|102|banana|8|
|103|orange|12|
|104|grape|15|
|120|ham|230|
|202|dress|2|


### **Trobleshooting section**
The testversion is written in swedish and have less complex logic formanaging time and space. To find the whole version of the code go into files folder. 


