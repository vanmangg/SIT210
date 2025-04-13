import sys
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
import RPi.GPIO as GPIO

# LED CLASS
class LED():
    
    # initialise class
    def __init__(self, pin):
        self.pin = pin
        self.is_on = False
        GPIO.setup(self.pin, GPIO.OUT)
        GPIO.output(self.pin, GPIO.LOW)
        
    # function to turn on LED
    def LED_on(self):
        GPIO.output(self.pin, GPIO.HIGH)
        self.is_on = True
        
    # function to turn off LED
    def LED_off(self):
        GPIO.output(self.pin, GPIO.LOW)
        self.is_on = False
        
    # function to control LED state
    def LED_control(self):
        if self.is_on:
            self.LED_off()
        else:
            self.LED_on()
            
# LED CONTROLLER CLASS
class LED_Controller(QMainWindow):
    
    # initialise class
    def __init__(self):
        
        super(LED_Controller, self).__init__()
        
        # initialise LEDs
        GPIO.setmode(GPIO.BOARD)
        self.led = {
        "red": LED(10),
        "green": LED(11),
        "blue": LED(12)
        }
        
        # initialise user interface
        self.setGeometry(100, 100, 300, 300)
        self.setWindowTitle("LED PROGRAM")
        widget = QWidget()
        layout = QVBoxLayout()
        
        
        # initialise buttons
        for colour, led in self.led.items():
            button = QtWidgets.QPushButton(colour)
            button.clicked.connect(lambda signal, l = led: l.LED_control()) # lambda signal absorbs the bool sent by clicked
            layout.addWidget(button)
        
        # exit button
        exit_button = QtWidgets.QPushButton("Quit")
        exit_button.clicked.connect(self.closeEvent
        )
        layout.addWidget(exit_button)
        
        # set the layout
        widget.setLayout(layout)
        self.setCentralWidget(widget)
    
    # handles exit events
    def closeEvent(self, event):
        GPIO.cleanup()
        self.close()

        
            
        

def main():
    app = QApplication(sys.argv)
    win = LED_Controller()
    win.show()
    sys.exit(app.exec_())

main()