from graphics import*
class Item:
    def __init__(self,pid,pname,pquantity):
        self.pid = pid
        self.pname = pname
        self.pquantity = pquantity
        
def Read_Inventory(fname):
    fileIn = open(fname, 'r')
    inventory = []
    for line in fileIn:
        item = line.split('\t')
        inventory.append(Item(item[0],item[1],item[2]))
    return inventory
    fileIn.close()

def Index_Record(inventory,pid):
    i = 0
    for item in inventory:
        if item.pid==pid:
            i += 1
            return i
        else:
            return None

def Add_Record(inventory,pid,pname,pquantity):
    if Index_Record(inventory,pid) == None:
        inventory.append(Item(pid,pname,pquantity))
        return True
    else:
        return False

def Update_Record(inventory,pid,pname,pquantity):
    index = Index_Record(inventory,pid)
    if index != None:
        inventory[index-1].name = pname
        inventory[index-1].quantity = pquantity
        return True
    else:
        return False

def Write_Inventory(inventory,fname):
    fileOut = open(fname, 'w')
    stri = ''
    for item in inventory:
        fileOut.write(item.pid + '\t' + item.pname + '\t' + item.pquantity)
    fileOut.close()    

def main(): 
#gui
    win = GraphWin("Inventory Control",500,500)
    win.setCoords(0,0,400,400)
    pquantity = Text(Point(50,200), "Item Quantity: ").draw(win)
    pquantityinput = Entry(Point(125,200),10).draw(win)
    pnametext = Text(Point(50,250), "Item Name: ").draw(win)
    pnameinput = Entry(Point(125,250),10).draw(win)
    pidtext = Text(Point(50,300), "Item ID: ").draw(win)
    pidinput = Entry(Point(125,300),10).draw(win)
    fnametext = Text(Point(50,350), "File Name: ").draw(win)
    fnameinput = Entry(Point(125,350),10).draw(win)
    Id = pidinput.getText()
    Name = pnameinput.getText()
    Quantity = pquantityinput.getText()
    File = fnameinput.getText()
#buttons
    openRec = Rectangle(Point(300,370),Point(360,340)).draw(win)
    openText = Text(Point(330,355), "Open").draw(win)
    addRec = Rectangle(Point(300,310),Point(360,280)).draw(win)
    addText = Text(Point(330,295), "Add").draw(win)
    findRec = Rectangle(Point(300,250),Point(360,220)).draw(win)
    findText = Text(Point(330,235), "Find Item").draw(win)
    updateRec = Rectangle(Point(300,190),Point(360,160)).draw(win)
    updateText = Text(Point(330,175), "Update").draw(win)
    quitRec = Rectangle(Point(300,130),Point(360,100)).draw(win)
    quitText = Text(Point(330,115), "Quit").draw(win)

    msg = Text(Point(200,50), "Specify the file name of an inventory").draw(win)

#main functions
    while True:
        clk = win.getMouse()
        #read inventory
        if(300<clk.getX()<360 and 340<clk.getY()<370):
            Read_Inventory(fnameinput.getText())
            msg.setText("You opened the file")
            
            while True:
                
                clk1 = win.getMouse()
                Inventory = Read_Inventory(fnameinput.getText())
                Id = pidinput.getText()
                Name = pnameinput.getText()
                Quantity = pquantityinput.getText()
                File = fnameinput.getText()
                
                #add record
                if(300<clk1.getX()<360 and 280<clk1.getY()<310):
                    add = Add_Record(Inventory,Id,Name,Quantity)
                    if add == False:
                        msg.setText("Cannot add record")
                    else:
                        msg.setText("You added: ID: {0} Name: {1} Quantity: {2}".format(Id,Name,Quantity))
                    Add_Record(Inventory,Id,Name,Quantity)
                        
                #index record
                if(300<clk1.getX()<360 and 220<clk1.getY()<250):
                    row = Index_Record(Inventory,Id)
                    if row == None:
                        msg.setText("Item couldn't be found")
                    else:
                        msg.setText("The index is {0} and id is {1}".format(row,Id))
                        
                #update record
                if(300<clk1.getX()<360 and 160<clk1.getY()<190):
                    Update_Record(Inventory,Id,Name,Quantity)
                    update = Update_Record(Inventory,Id,Name,Quantity)
                    if update == False:
                        msg.setText("That record does not exist.")
                    else:
                        msg.setText("The record has been updated to ID: {0} Name: {1} Quantity: {2}".format(Id,Name,Quantity))   
                        
                #quit and write inventory
                if(300<clk1.getX()<360 and 100<clk1.getY()<130):
                    Write_Inventory(Inventory, File)
                    win.close()   
main()
